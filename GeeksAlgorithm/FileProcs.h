#ifndef GEEKS_FILE_PROCS_H
#define GEEKS_FILE_PROCS_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Graph\DenseGraph.h"
#include "Graph\SparseGraph.h"

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

	template <typename Graph>
    void readGraph(Graph &graph, const string &filename)
	{
        ifstream file(filename);
        string line;
        int V, E;

		assert(file.is_open());

        assert(getline(file, line));
        stringstream ss(line);
        ss >> V >> E;

        assert(V == graph.V());

        for(int i = 0 ; i < E ; ++i)
		{
            assert(getline(file, line));
            stringstream ss(line);

            int a, b;
            ss >> a >> b;
            assert(a >= 0 && a < V);
            assert(b >= 0 && b < V);
            graph.addEdge(a , b);
        }
    }

}

#endif //GEEKS_FILE_PROCS_H
