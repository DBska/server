#ifndef _MESSAGE_H_
#define _MESSAGE_H_

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
//#include <ctime>
//#include <algorithm>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#include "PHTmessage.pb.h"
#include "data_struct.h"
#include "soci.h"
#include "error.h"
#include "connectDB.h"

using namespace std;
using namespace PHT;
using namespace soci;


enum messageType_data
{
    DATA = 1,
    QUERY,
    ANSWER,
    ERROR
};

messageType_data selectMessageType();
void insertProposal(int sock, data_s dat, Error &err); // either new or updating an existing one
void allProposalsWithStatus(int sock);
void replyToClient(int sock, string reply_msg);


#endif
