#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <linux/limits.h>
#include <map>
#include <cstdio>

using namespace std;

struct pid_stat
{
    long long int pid;
    char tcomm[PATH_MAX];
    char state;
};


int main()
{
    map< long long int, pid_stat> proc_info;

    boost::filesystem::directory_iterator it("/proc");
    boost::filesystem::directory_iterator end;
    for ( ; it != end ; ++it)
    {
        boost::filesystem::path p = it->path();

        long long int pid = atoi( p.filename().c_str() );

        if (pid)
        {
            p = p / "stat";   // /proc/2345678/stat

            ifstream f( p.string() );

            if( f.is_open() )
            {
                pid_stat curr;
                f >> curr.pid >> curr.tcomm >> curr.state;
                f.close();

                proc_info[ pid ] = curr;
            }
        }
    }

    for( auto &element : proc_info)
    {
        cout << "PID: " << element.second.pid;
        cout << " tcomm: " << element.second.tcomm << endl;
    }

    return 0;
}
