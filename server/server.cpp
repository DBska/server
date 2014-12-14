/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "oda.pb.h"

using namespace std;
using namespace oda; // namespace for using google protocol buffer

void processing(int sock);
void error(string msg)
{
    perror(msg.c_str());
    exit(1);
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
        error("ERROR, no port provided\n");

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

	// starting the listening loop. It is a brutal stop: Ctrl-Z....
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
	    	close(sockfd);
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
	/*
    string buffer;
    char string_tmp[256];
    int n;

    bzero(string_tmp,256);
    n = read(sock,string_tmp,255);
    buffer = string_tmp;
    if (n < 0) cerr<<"ERROR reading from socket";
    cout<<"Here is the message: "<<buffer<<endl;
    n = write(sock,"I got your message",18);
    if (n < 0) cerr<<"ERROR writing to socket";
	*/

	uint32_t mLength;
	read(sock,&mLength,sizeof(uint32_t)); // Receive the message length
	mLength = ntohl(mLength); // Ensure host system byte order
	int dataLength = static_cast<int>(mLength);

	cout<<"Message of "<<dataLength<<" elements arrived!\n";
	char* buff[dataLength];
	read(sock,buff,dataLength); // Receive the string data

	//string receivedString;                        // assign buffered data to a 
	//receivedString.assign(&(rcvBuf[0]),rcvBuf.size()); // string
	string message(buff[0],buff[0]+dataLength);    // Allocate a receive buffer
	cout<<dataLength<<endl;
	//message.assign(buff[0],dataLength); // with the necessary size
	cout<<"2\n";
	cout<<message.size()<<endl;
	Oda oda_data;
	if (!oda_data.ParseFromString(message))
		error("ERROR. Can not parse the received message.");

	// parsing the data
	for (int i=0; i<oda_data.proposal_size(); i++)
	{
		const Proposal& proposal = oda_data.proposal(i);
		cout<<"ID: "<<proposal.id()<<endl;
		cout<<"TITLE: "<<proposal.title()<<endl;
		if (proposal.reviewer_size()==0)
		{
			cout<<"No reviewers assigned"<<endl;
		}
	}
	cout<<"done\n";
}
