
#include "error.h"

void Error::writeErrorMessage(string &message)
{
    time_t now = time(0);
    //string dt = ctime(&now);
    //dt.erase( remove(dt.begin(), dt.end(), '\n'), dt.end() );
    struct tm *timeinfo;
    char dt[80];
    time(&now);
    timeinfo = localtime(&now);
    strftime(dt,80,"%x %T ",timeinfo);
    cerr<<dt<<" "<<message<<endl;
    lerr<<dt<<" "<<message<<endl;
}
        

string Error::ErrorMessages()
{
    return lerr.str();
}


Error::Error(string file_name)
{
    // Redirecting cerr output to file file_name in server/server
    // directory:
    out.open(file_name.c_str(),ios_base::app);
    //old_cerr = new streambuf;
    old_cerr = cerr.rdbuf();
    cerr.rdbuf( out.rdbuf() );
}

Error::~Error()
{
    // Redirecting cerr to original stream and closing local output file
    out.close();
    cerr.rdbuf(old_cerr);
    delete old_cerr;
}
