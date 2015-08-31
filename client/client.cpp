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
void error(string msg)
{
    perror(msg.c_str());
    exit(0);
}

int main(int argc, char *argv[])
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    // Checking is the command is called with the appropriate sintax:
    // $ client hostname port
    if (argc < 3) 
    {
       cerr<<"usage: "<<argv[0]<<" hostname port\n";
       exit(0);
    }

    // Setting up the socket
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
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

    // Setting up a new proposal without any reviewer:
    PHTmessage pht_data;
    Proposals* proposal = pht_data.add_proposal();
    proposal->set_abstract("Milky-way galaxy radio detection in X-band");
    proposal->set_proposal_status(PHT::DRAFT);
    proposal->set_proposal_type(PHT::TOOproposal);
    proposal->set_more_info("bla bla");	
    // Serializing to a string the data to send
    string message;
    if (!pht_data.SerializeToString(&message))
	    error("ERROR. Can not serialize the message.\n");

    /* Fake sending */
    bool fake_test = false;
    if (fake_test)
    {
        uint32_t msgLength = message.size();
        string messageRecv;
        messageRecv.assign(&(message[0]),message.size());
        if (!pht_data.ParseFromString(messageRecv))
        {
            cerr<<"ERROR. Can not parse the received message.\n";
	    exit(-1);
        }
    }

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
