#ifndef GEEKS_FILE_PROCS_H
#define GEEKS_FILE_PROCS_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

namespace FileProcs
{
    int firstCharacterPos(const string& str, int start)
	{
        for(unsigned i = start; i < str.length() ; ++i)
            if(isalpha(str[i]))
                return i;
        return str.length();
    }

    string lower(const string& str)
	{
        string ret = "";
        for(unsigned i = 0; i < str.length() ; ++i)
            ret += tolower(str[i]);
        return ret;
    }

    bool readFile(const string& filename, vector<string> &words)
	{
        string line;
        string contents = "";
        ifstream file(filename);
        if(file.is_open())
		{
            while( getline(file, line))
                contents += (line + "\n");
            file.close();
        }
        else{
            cout<<"Can not open "<<filename<<" !!!"<<endl;
            return false;
        }

        int start = firstCharacterPos(contents, 0);
        for(unsigned i = start + 1; i <= contents.length(); )
		{
            if(i == contents.length() || !isalpha(contents[i]))
			{
                words.push_back(lower(contents.substr(start,i - start)));
                start = firstCharacterPos(contents, i);
                i = start + 1;
            }
            else
			{
                ++i;
            }
        }

        return true;
    }
}

#endif //GEEKS_FILE_PROCS_H
