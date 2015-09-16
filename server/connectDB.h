#ifndef _CONNECTDB_H_
#define _CONNECTDB_H_

#include <vector>
#include <string>
#include <iostream>
#include "data_struct.h"
// Soci header files. Required!
#include "soci.h"
#include "mysql/soci-mysql.h"

using namespace std;
using namespace soci; // namespace for using soci library 

//void writeToDB(vector<string> );
void writeToDB(data_s );
void readFromDB();

#endif



