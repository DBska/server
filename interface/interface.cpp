/*! \file client.cpp
	\brief Client code.

	This file contains the Client code for connecting to a remote server and sending or requesting data from a mySQL database.

	Copyright (C) 2014 Marco Messina
*/

#include "interface.h"
#include "socket.h"

namespace API_ODA {


int insertNewProposal(Proposals &proposal)
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    int n;

    // setting up the socket and opening the connection
    Connect connection;
    if ( connection.openSocket()<0 )
        cerr<<"ERROR: problems with socket\n";

    /* Connection with the Server is now established */
    // Preparing the message to send
    PHTmessage *pht_data = new PHTmessage;
    pht_data->set_type(PHTmessage::DATA);
    pht_data->set_allocated_proposal(&proposal);

    // Serializing to a string the data to send
    string message;
    if (!pht_data->SerializeToString(&message))
	    cerr<<"ERROR: Can not serialize the message.\n";

    connection.sendMessage(message);

    // Closing connection
    connection.Close();

    //delete pht_data;

    return 0;
}


int modifyProposal()
{

    return 0;
}


}
