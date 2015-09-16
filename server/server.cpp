/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "PHTmessage.pb.h"
#include "soci.h"
#include "mysql/soci-mysql.h"
#include "connectDB.h"
#include "parser.h"

using namespace std;
using namespace PHT; // namespace for using google protocol buffer
using namespace soci; // namespace for using soci library 

void processing(int sock);


int main(int argc, char *argv[])
{
    // Redirecting cerr to a stringstream. It is then possible to sent it back
    // to the client.
    //stringstream error_message;
    ofstream out("server_error.txt",ios_base::app);
    streambuf *old_cerr = cerr.rdbuf();
    cerr.rdbuf( out.rdbuf() );

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
        cout<<"usage: "<<argv[0]<<" port\n";
        exit(1);
    }
    // Opening the socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
       cerr<<"ERROR opening socket";
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0) 
             cerr<<"ERROR on binding";
    listen(sockfd,5);
     
    clilen = sizeof(cli_addr);

    // starting the listening loop. It has a brutal stop: Ctrl-C....
    while (1)
    {
    	newsockfd = accept(sockfd, 
                          (struct sockaddr *) &cli_addr, 
              	           &clilen);
        cout<<newsockfd<<endl;
        if (newsockfd < 0)
        {
            time_t now = time(0);
            string dt = ctime(&now);
            dt.erase( remove(dt.begin(), dt.end(), '\n'), dt.end() );
            cerr<<dt<<" "<<"ERROR on accept\n";
            exit(1);
        }

        signal(SIGCHLD,SIG_IGN); // this is needed to avoid zombies until the parent is dead

        // The following fork() is used to allow different client to connect to the server
        pid = fork();
	if (pid>0) cout<<"Forking with child PID "<<pid<<endl; // Parent process
 	if (pid<0)
            cerr<<"ERROR on fork";
	 if (pid==0)
	 {
	    close(sockfd);
            // The following try-catch block prints error from DB operations to
            // cerr.
            try
            {
	        processing(newsockfd);
	        exit(0);
            }
            catch (mysql_soci_error const &e)
            {
                cerr<<"MySQL error: "<<e.err_num_<<" "<<e.what()<<endl;
            }
            catch (exception const &e)
            {
                cerr<<"Soci error: "<<e.what()<<endl;
            }
	 }
	 else close(newsockfd);
    } /* end of while for server listening */

    //Closing the socket
    close(sockfd); // Should also be moved into try-catch block (?)
    // Redirecting cerr to original stream
    out.close();
    cerr.rdbuf(old_cerr);

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
    PHTmessage *p_oda = new PHTmessage;
    // The following check should fail only if the message is corrupted.
    cout<<"Parsing...\n"<<endl;
    if (!p_oda->ParseFromString(message))
    {
        cerr<<"ERROR. Can not parse the received message.";
	exit(-1);
    }
    // Parsing the message. Only one proposal at a time can be inserted.
    //vector<string> command;
    //command = parsingMessage(p_oda);
    data_s dat;
    dat = parsingMessage(p_oda);
    //cout<<"Command(s) detected:"<<endl;
    //for (int i=0; i<command.size(); i++)
    //    cout<<command[i]<<endl;

    // inserting the data into the DB
    //writeToDB(command);
    writeToDB(dat);
    
    // Cleaning memory
    delete p_oda;


    cout<<"done\n";

}
