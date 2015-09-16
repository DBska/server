#ifndef _DATA_STRUCT_H_
#define _DATA_STRUCT_H_

#include <string>
#include <vector>
#include <map>

using namespace std;

// This data structure is filled after a message from PHT is parsed. It is used
// for building mySQL commands. The way the parser works, the first entry is the
// proposal main table Proposals.
struct data_s 
{
    vector<string> table; // t table name
    map< int, vector<string> > name; // name[t][n] names (int n) in table t
    map< int, vector<string> > value; // value[t][v] values (int v) in table t corresponding to name[t][n]
};

#endif



