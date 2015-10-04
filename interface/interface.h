#ifndef _INTERFACE_H_
#define _INTERFACE_H_


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

namespace API_ODA {

    enum messageType_data
    {
        DATA = 1,
        QUERY,
        ANSWER,
        ERROR
    };
    string insertNewProposal(Proposals &, string &error_message);
    void modifyProposal(Proposals &, string &error_message );
    vector<Proposals *> requestProposalsWithStatus(int );
    messageType_data checkMessageType(PHTmessage *);
}

#endif
