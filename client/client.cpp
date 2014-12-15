/*! \file client.cpp
	\brief Client code.

	This file contains the Client code for connecting to a remote server and sending or requesting data from a mySQL database.

	Copyright (C) 2014 Marco Messina
*/

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "oda.pb.h"

using namespace std;
using namespace oda;

/**
* Prints the error message to cerr
* @param msg string with the error message
*/
void error(string msg)
{
    perror(msg.c_str());
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;


	// Checking is the command is called with the appropriate sintax:
	// $ client hostname port
    if (argc < 3) {
       cerr<<"usage: "<<argv[0]<<" hostname port\n";
       exit(0);
    }

	// Setting up the socket
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        cerr<<"ERROR, no such host\n";
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

	/* Connection with the Server is now established */

	/*
    string buffer;
    cout<<"Please enter the message: ";
    getline(cin,buffer);
    n = write(sockfd,buffer.c_str(),buffer.length());
    if (n < 0) 
         error("ERROR writing to socket");
    buffer.clear();
    char string_tmp[256];
    bzero(string_tmp,256); // need to zeroes the string to avoid junk stuff from read. Still not clear why...
    n = read(sockfd,string_tmp,255);
    buffer = string_tmp;
    if (n < 0) 
         error("ERROR reading from socket");
    cout<<buffer.c_str()<<endl;
	*/

	// Setting up a new proposal without any reviewer:
	Oda oda_data;
	Proposal* proposal = oda_data.add_proposal();
	proposal->set_id(5543);
	proposal->set_title("Milky-way galaxy radio detection in X-band");
	
	// Serializing to a string the data to send
	string message;
	if (!oda_data.SerializeToString(&message))
		error("ERROR. Can not serialize the message.\n");
	
	uint32_t dataLength = htonl(message.size()+1); // convert int to network byte order
    n = write(sockfd,&dataLength,sizeof(uint32_t));
	if (n < 0) 
         error("ERROR writing to socket the message length");
    n = write(sockfd,message.c_str(),message.size()+1);
	cout<<n<<endl;
	if (n < 0) 
         error("ERROR writing to the message socket");
	if (n!=message.size()+1)
		cerr<<"ERROR in sending data...\n";

	/* Closing the connection */
    close(sockfd);
    return 0;
}
