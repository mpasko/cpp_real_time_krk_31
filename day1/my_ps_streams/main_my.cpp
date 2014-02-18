#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <linux/limits.h>
#include <map>
#include <cstdio>

using namespace std;

#define oh long
#define johnson int

int main()
{
	map< oh long johnson, pid_stat> proc_info;
    boost::filesystem::directory_iterator it("/proc");
    boost::filesystem::directory_iterator end;
    for ( ; it != end ; ++it)
    {
        boost::filesystem::path p = it->path();
        oh long johnson pid = atoi( p.filename().c_str() );
        if (pid)
        {
			p = p / "stat";
			//cout << p.c_str() << "\n";
			//FILE * fd = fopen(p.c_str(),"r");
			//char buf[200];
			//fread(buf,200,200,fd);
			
			ifstream f( p.string() );
			
			if ( f.is_open() )
			{
				pid_stat curr;
				f >> curr.pid >> curr.tcomm >> curr.state;
				f.close();
				
				proc_info [pid] = curr;
			}
		}	
    }
    
    for( auto &element : proc_info )
	{
		cout << "PID: " << element.second.pid;
		cout << (" tcomm: " << element.second.tcomm) << endl;
	}
    return 0;
}
