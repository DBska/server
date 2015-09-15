#ifndef _SOCI_H_
#define _SOCI_H_

#include <vector>
#include <string>
#include <iostream>
// Soci header files. Required!
#include "soci.h"
#include "mysql/soci-mysql.h"

using namespace std;
using namespace soci; // namespace for using soci library 

void writeToDB(vector<string> );
void readFromDB();

#endif



