/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sstream>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "PHTmessage.pb.h"
#include "soci.h"
#include "mysql/soci-mysql.h"

using namespace std;
using namespace PHT; // namespace for using google protocol buffer
using namespace soci; // namespace for using soci library 

void processing(int sock);
void error(string msg)
{
    perror(msg.c_str());
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    pid_t pid;
    socklen_t clilen;
     
    string buffer; // a vector<char> should be better...
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    // Checking the calling statement of the program is correct:
    // server port
    if (argc < 2)
    {
        //error("ERROR, no port provided\n");
        cerr<<"usage: "<<argv[0]<<" port\n";
        exit(1);
    }
    // Opening the socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
       error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0) 
             error("ERROR on binding");
    listen(sockfd,5);
     
    clilen = sizeof(cli_addr);

    // starting the listening loop. It has a brutal stop: Ctrl-C....
    while (1)
    {
    	newsockfd = accept(sockfd, 
                          (struct sockaddr *) &cli_addr, 
              	           &clilen);
        if (newsockfd < 0) 
           error("ERROR on accept");

        signal(SIGCHLD,SIG_IGN); // this is needed to avoid zombies until the parent is dead

        // The following fork() is used to allow different client to connect to the server
        pid = fork();
	if (pid>0) cout<<"Forking with child PID "<<pid<<endl; // Parent process
 	if (pid<0)
            error("ERROR on fork");
	 if (pid==0)
	 {
	    close(sockfd); // why here??
	    processing(newsockfd);
	    exit(0);
	 }
	 else close(newsockfd);
    } /* end of while for server listening */
    
    //Closing the socket
    close(sockfd);
    return 0; /* never here */
}	    

void processing(int sock)
{
    // The message is received in two parts: 1) its lengths 2) the message
    // 1) The length of the message to be received
    uint32_t mLength;
    read(sock,&mLength,sizeof(uint32_t)); // Receive the message length
    mLength = ntohl(mLength); // Ensure host system byte order
    int dataLength = static_cast<int>(mLength);
    cout<<"Message of "<<dataLength<<" elements arrived!\n";
	
    // 2) The message itself. It is stored in a char [], however a vector<char> could and should be used.
    vector<uint8_t> msg; // Allocating a buffer of approriate length
    msg.resize(mLength,0x00);

    int n;
    n = read(sock,&(msg[0]),mLength); // Receive the string data

    string message;   // Convert message data into a string for de-serialization
    message.assign(reinterpret_cast<const char*>(&(msg[0])),msg.size());

    // De-serialization starts here
    PHTmessage pht_data;
    // The following check should fail only if the message is corrupted.
    if (!pht_data.ParseFromString(message))
    {
        cerr<<"ERROR. Can not parse the received message.";
	exit(-1);
    }
    // parsing the data and printing to screen the proposal submitted. The loop allows for more than one submission.
    for (int i=0; i<pht_data.proposal_size(); i++)
    {
        const Proposals& proposal = pht_data.proposal(i);
	//cout<<"ID: "<<proposal.id()<<endl;
	cout<<"ABSTRACT: "<<proposal.abstract()<<endl;
	//if (proposal.reviewer_size()==0)
	//{
	//	cout<<"No reviewers assigned"<<endl;
	//}
    }
    cout<<"done\n";

	// Inserting the data into the DB with SOCI. I know it is only ONE data. The following part of the code
	// should be put in the for(i) above.
	session sql(mysql, "db=PHT user=marco password=Marco74");
	const Proposals& proposal = pht_data.proposal(0); // ad-hoc retrieving of the only data present in the message

	// before inserting, printing the currente number of Proposals
	int count;
	sql<<"select count(*) from Proposals", into(count);
	cout<<"Table Proposals has "<<count<<" entries"<<endl;


	// Inserting the data
	sql<<"insert into Proposals (abstract) values(:abstractp)", use(proposal.abstract());
	sql<<"select count(*) from Proposals", into(count);
	cout<<"Table Proposals now has "<<count<<" entries"<<endl;

	// Printing the new table on screen
	rowset<row> rs = (sql.prepare << "select proposal_id, abstract from Proposals");

	// iteration through the resultset:
	int r = 1;
	for (rowset<row>::const_iterator it = rs.begin(); it != rs.end(); ++it)
	{
    	row const& row = *it;

    	// dynamic data extraction from each row:
    	cout << r <<") " << "Id: " << row.get<int>(0)
        	 << " Abstract: " << row.get<string>(1)  << endl;
		r++;
	}
}
