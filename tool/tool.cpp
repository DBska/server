/*! \file tool.cpp
	\brief Tool code.

	This file contains the Tool code for connecting to a remote server and sending or requesting data from a mySQL database.

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
#include "Proposals.pb.h"

using namespace std;
using namespace PHT;

void setProposal(Proposals *);
void setFullProposal(Proposals *);

void setFullProposal(Proposals *proposal)
{
    proposal->set_abstract("Milky-way galaxy radio detection in X-band");
    proposal->set_proposal_status(PHT::DRAFT);
    proposal->set_proposal_type(PHT::TOOproposal);
    proposal->set_more_info("bla bla");	
    

    CoAuthors *coa = new CoAuthors;
    coa->set_author_id(56);
    proposal->set_allocated_m_coauthors(coa);
    
}



void setProposal(Proposals *proposal)
{
    proposal->set_abstract("Milky-way galaxy radio detection in X-band");
    proposal->set_proposal_status(PHT::DRAFT);
    proposal->set_proposal_type(PHT::TOOproposal);
    proposal->set_more_info("bla bla");	
}


int main(int argc, char *argv[])
{
    cout<<"Building a test proposal\n";
    
    // Setting up the message to send
    Proposals *proposal= new Proposals;
    
    // Setting up a new proposal:
    //setProposal(proposal);
    
    // Setting up full proposal:
    setFullProposal(proposal);

    // Cleaning up memory
    delete proposal;

    return 0;
}
