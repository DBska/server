#ifndef _CONNECTDB_H_
#define _CONNECTDB_H_

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "data_struct.h"
// Soci header files. Required!
#include "soci.h"
#include "mysql/soci-mysql.h"
#include "ProposalStatus.pb.h"
#include "Proposals.pb.h"

using namespace std;
using namespace PHT;
using namespace soci; // namespace for using soci library 

const string use_db = "db=PHT user=marco password=Marco74"; 
//const string use_db = "db=PHT user=controls password=Wrufu6ac";

string writeToDB(data_s );
vector<Proposals *> readAllProposalsFromDB(int p_status);
string getDataValue(row &r, int i);

#endif



