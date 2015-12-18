/*! \file tool.cpp
	\brief Tool code.

	This file contains the Tool code for connecting to a remote server and sending or requesting data from a mySQL database.

	Copyright (C) 2014 Marco Messina
*/

#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <algorithm>
#include "Proposals.pb.h"
#include "ProposalStatus.pb.h"
#include "interface.h"

using namespace std;
using namespace PHT;

void setProposal(Proposals *);
void setFullProposal(Proposals *);
void updateProposal(int , Proposals *);
void requestProposalsWithStatus();

void requestProposalsWithStatus()
{
    int status = PHT::Draft + 1; // NB: ENUM IN MYSQL STARTS FROM 1!!!!!!!
    //cout<<"Draft: "<<PHT::Draft<<endl;
    API_ODA::requestProposalsWithStatus(status);
}

void updateProposal(int ID, Proposals *proposal)
{
    proposal->set_proposal_id(ID);
    proposal->clear_proposal_type();
    proposal->set_proposal_type(PHT::PI);
}

void setFullProposal(Proposals *proposal)
{
    proposal->set_abstract("Milky-way galaxy radio detection in X-band");
    proposal->set_proposal_status(PHT::Draft);
    proposal->set_proposal_type(PHT::TOO);
    proposal->set_more_info("bla bla");	

    CoAuthors *coa = new CoAuthors;
    coa->set_author_id(56);
    coa->set_coauthorsid(35);
    proposal->set_allocated_m_coauthors(coa);
}



void setProposal(Proposals *proposal)
{
    // Shuffling the abstract string
    srand ( unsigned ( time(0) ) );
    string abstract = "Milky-way galaxy radio detection in X-band";
    random_shuffle(abstract.begin(),abstract.end());

    proposal->set_abstract(abstract);
    proposal->set_proposal_status(PHT::Draft);
    proposal->set_proposal_type(PHT::TOO);
    proposal->set_more_info("bla bla");	
}


int main(int argc, char *argv[])
{
    cout<<"Building a test proposal\n";
    bool set_full_proposal = false;
    bool send_proposal = true;

    // Setting up the message to send
    Proposals *proposal = new Proposals;
   
    if (send_proposal)
    {
        if ( set_full_proposal )
        {
            // Setting up full proposal:
            setFullProposal(proposal);
        }
        else
        {
            // Setting up a new proposal:
            setProposal(proposal);
        }
        cout<<"Sending the proposal to DB\n";
        cout<<proposal->DebugString();
        // Sending proposal to database via ODA_API:
        string proposal_id;
        string error_message;
        proposal_id = API_ODA::insertNewProposal(proposal, error_message);
        cout<<"Server message for insert NEW: "<<error_message<<endl;
        cout<<"Proposal ID: "<<proposal_id<<endl;


        // Updating last inserted proposal if insertion is ok
        stringstream tmp;
        tmp<<proposal_id;
        int p_id;
        tmp>>p_id;
        cout<<"INT p_id: "<<p_id<<endl;
        error_message = "";
        Proposals *proposal2 = new Proposals;


        if ( p_id > 0 )
        {
            updateProposal(p_id,proposal2);
            cout<<"Local update done\n";
            cout<<"..."<<proposal2->DebugString();
            API_ODA::modifyProposal(proposal2,error_message);
            cout<<"Server message for UPDATE: "<<error_message<<endl;
        }
    }

    // Retrieving proposals list
    requestProposalsWithStatus();

    return 0;
}
