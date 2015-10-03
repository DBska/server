#ifndef _ERROR_H_
#define _ERROR_H_

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <fstream>


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


#endif 
