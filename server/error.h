#ifndef _ERROR_H_
#define _ERROR_H_

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <time.h>
#include <stdio.h>

using namespace std;

class Error
{
    private:
        stringstream lerr;
        streambuf *old_cerr;
        ofstream out;

    public:
        Error(string file_name);
        ~Error();
        void writeErrorMessage(string message);
        string ErrorMessages();
};

void print(string file, string what);

#endif 
