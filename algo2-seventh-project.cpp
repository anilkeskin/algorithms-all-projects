/* * * * * * * * * * * * * * * * * * * * * * * * * *
 * BLG 336E Analysis of Algorithms II
 * Spring 2021
 * Student Name: ANIL KESKÝN
 * Student ID: 150170801
 * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
using namespace std;
class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) 
	{
		int v =graph.size();
    	int *visited=new int[v];
   		for(int i=0;i<v;i++)visited[i]=-1;
    	visited[0]=1;
    	queue<int>q;
    	q.push(0);
    	while(!q.empty())
		{
        	int curr=q.front();
        	q.pop();
        	for(auto it=graph[curr].begin();it!=graph[curr].end();it++)
			{
            	if(visited[*it]==-1)
				{
                	visited[*it]=1-visited[curr];
                	q.push(*it);
            	}
            	else if(visited[*it]==visited[curr])	return false;
        	}
    	}
    	return true;
	}
};
void printv(vector <vector <int> > v) {
    for (unsigned int i = 0; i < v.size(); i++) {
        for (unsigned int j = 0; j < v[i].size(); j++)
            cout << v[i][j] << " ";
        cout << endl;
    }
}

int main()
{
    Solution s;
    string fname;
    cin >> fname;
    ifstream graphFileHandler(fname);
    vector <int> adj;
    vector<vector <int> > graph;
    string line;
    while (graphFileHandler >> line) {
        stringstream ss(line);
        string substr;
        while (ss.good()) {
            getline(ss, substr, ',');
            adj.push_back(stoi(substr));
        }
        graph.push_back(adj);
        adj.clear();
    }
    bool answer = s.isBipartite(graph);
    if (answer == 1)
        cout << "True" <<endl;
    else
        cout << "False" << endl;
    return 0;
}
