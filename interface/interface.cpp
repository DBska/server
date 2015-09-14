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
#include "PHTmessage.pb.h"

using namespace std;
using namespace PHT;

/**
* Prints the error message to cerr
* @param msg string with the error message
*/

int connect(PHTmessage &pht_data);
void error(string msg);

void error(string msg)
{
    perror(msg.c_str());
    exit(0);
}



int connect(PHTmessage &pht_data)
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    
    const int PORT = 3303;
    string host_name = "localhost";

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    // Setting up the socket
    portno = PORT;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(host_name.c_str());
    if (server == NULL) 
    {
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

    // Serializing to a string the data to send
    string message;
    if (!pht_data.SerializeToString(&message))
	    error("ERROR. Can not serialize the message.\n");

    uint32_t dataLength = htonl(message.size()); // convert int to network byte order. 
    // The size is message.size()+1 because C string terminates with '\0' character, which is missing
    // in string C++.

    // The message e is divided in two parts:
    // 1) First message sent is the length of the message with the serialization
    cout<<"Sending "<<message.size()<<" elements\n";
    n = write(sockfd,&dataLength,sizeof(uint32_t));
    if (n < 0) 
        error("ERROR writing to socket the message length");
    
    // 2) The actual message is sent. n stores the actual length sent.
    n = write(sockfd,message.c_str(),dataLength);
    if (n < 0) 
        error("ERROR writing to the message socket");
    
    /* Closing the connection */
    close(sockfd);
    
    return 0;
}
