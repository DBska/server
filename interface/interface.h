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
#include <google/protobuf/message.h>
#include "PHTmessage.pb.h"

using namespace std;
using namespace PHT;
using namespace google::protobuf;

namespace API_ODA {

/*! \file interface.h
*\brief Main operations on the ODA database.
*
* The implemented functions are:
* 1) insertNewProposal
* 2) modifyProposal
* 3) requestProposalsWithStatus
*/

/*! \fn vector<Proposals *> requestProposalsWithStatus(int status)
     * \brief Returns a list of proposals with given status.
     *
     * The available status are:
     * 0 Draft 
     * 1 Accepted
     * 2 Rejected
     * 3 Submitted
     * 4 Merged
     *
     *\param status The status required (integer starting from 0. See list)
     *\param error_message a message with information on the status of the operation.
     *\return an STL vector with all the proposals with the given status.
     */ 

    /*! \fn string insertNewProposal(Proposals *proposal, string &error_message)
    *\brief Insert a new proposal. Returns the id of the proposal.
    *
    *\param proposal the proposal to insert into ODA.
    *\param error_message a message with information on the status of the operation.
    *\return string the proposal ID. For the moment is simply an integer in string format. 
    */

    /*! \fn void modifyProposal(Proposals *proposal, string &error_message )
     * \brief Modify an existing proposal. The proposal id MUST be known and
     * set with the appropriate method.
     *
     * \param proposal The proposal that must be modified. The proposal id MUST
     * be set.
     *\param error_message a message with information on the status of the operation.
     * 
     */ 


    enum messageType_data
    {
        DATA = 1,
        QUERY,
        ANSWER,
        ERROR
    };

    string insertNewProposal(Proposals *proposal, string &error_message);
    void modifyProposal(Proposals *proposal, string &error_message );
    vector<Proposals *> requestProposalsWithStatus(int status);
    messageType_data checkMessageType(PHTmessage *);
    void setProposalData(const Message *, const Descriptor *, const Reflection *);
}

#endif
