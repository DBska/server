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
#include "mysql/soci-mysql.h"
#include "error.h"
#include "connectDB.h"

using namespace std;
using namespace PHT;
using namespace soci;

const int BUF_SIZE = 4;

enum messageType_data
{
    DATA = 1,
    QUERY,
    ANSWER,
    ERROR,
    PST
};

messageType_data selectMessageType();
void insertProposal(int sock, data_s dat, Error &err, session &sql); // either new or updating an existing one
void allProposalsWithStatus(int sock, int p_stat, Error &err, session &sql);
bool readFromSocket(int sock, string &answer, Error &err);
void writeToSocket(int sock, string message, Error &err);
void proposalWithID(int sock, int pid, Error &err, session &sql);
void uploadFile(string file_name, string file_data);

#endif
