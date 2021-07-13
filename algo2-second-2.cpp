/*
	ANIL KESKİN - 150170801 - Q2
*/
#include<bits/stdc++.h>
#define MAXV 1000
using namespace std;
map<string, int> myList;
string MapValue(int value)
{
	string deger="";
	for (auto it = myList.begin(); it != myList.end(); ++it)
    if (it->second == value) deger= it->first;
    
    return deger;
}
class MyNode{
    public:
        int key;
        int weight;
        MyNode *next;
        MyNode(int key, int weight)
        {
        	this->key = key;
   		    this->weight = weight;
    		this->next = NULL;
		}
};
class Graph{
    bool directed;
    public:
        MyNode *edges[MAXV + 1];
        Graph(bool directed)
        {
        	this->directed = directed;
   			for(int i = 1; i < (MAXV + 1); i ++)this->edges[i] = NULL;
		}
        void add_edge(int x, int y, int weight, bool directed)
        {
        	if((x < (MAXV + 1))&& (y < (MAXV + 1))&& (x > 0)&&  (y > 0) )
			{
        		MyNode *edge = new MyNode(y, weight);
        		edge->next = this->edges[x];
        		this->edges[x] = edge;
        		if(!directed)add_edge(y, x, weight, true);
    		}
		}
};
void init_vars(bool discovered[], int distance[], int parent[]){
    for(int i = 1; i < (MAXV + 1); i++)
	{
		parent[i] = -1;
        discovered[i] = false;
        distance[i] = std::numeric_limits<int>::max();
    }
}
string ptr[8];
int i =0;
void find_shortest_path(int v, int parent[]){
	
    if((parent[v] != -1) && (v > 0) && (v < (MAXV + 1)) )
	{
		ptr[i]=MapValue(parent[v]);
		i++;
        find_shortest_path(parent[v], parent);
    }
}
void shortest_path_algo_dijkstra(Graph *graph, int parent[], int distance[], int start){

    bool discovered[MAXV + 1];
    MyNode *currrent;
    int v_c;
    int v_n;
    int weight;
    int s_distance;
	init_vars(discovered, distance, parent);
    distance[start] = 0;
    v_c = start;
    while(discovered[v_c] == false)
	{
        discovered[v_c] = true;
        currrent = graph->edges[v_c];
        while(currrent != NULL)
		{
            v_n = currrent->key;
            weight = currrent->weight;
            if((distance[v_c] + weight) < distance[v_n])
			{
                distance[v_n] = distance[v_c] + weight;
                parent[v_n] = v_c;
            }
            currrent = currrent->next;
        }
        s_distance = std::numeric_limits<int>::max();
        for(int i = 1; i < (MAXV + 1); i ++)
		{
            if(!discovered[i] && (distance[i] < s_distance))
			{
                v_c = i;
                s_distance = distance[i];
            }
        }
    }
}

int main()
{
	Graph *g = new Graph(false);
    int parent[MAXV + 1];
    int distance[MAXV + 1];
    int start = 1;
	int count=1;
	ifstream file;
	string fileName;
	cin>>fileName;
	file.open(fileName);
	string line,line1,line2;
	int weight;
	int firstline=0;
	while(!file.eof())
	{
		getline(file, line, ',');
		line1=(string)line;
		getline(file, line, ',');
		line2=(string)line;
		file >> weight; 
		if(firstline!=0)
		{
			if (myList.find(line1) == myList.end())
			{
				myList.insert(pair<string, int>(line1,count));
				count++;
			}
			if (myList.find(line2) == myList.end())
			{
				myList.insert(pair<string, int>(line2,count));
				count++;
			}
			
		}
		else
		{
			firstline=1;
			myList.insert(pair<string, int>(line1, count));
			count++;
			myList.insert(pair<string, int>(line2, count));
			count++;
		}
	    getline(file, line, '\n');
	}
    int im=0;
	ifstream file1;
	file1.open(fileName);
	while(!file1.eof())
	{	
		getline(file1, line, ',');
		line1=(string)line;
		getline(file1, line, ',');
		line2=(string)line;
		file1 >> weight;
		im++;
		int int_line1= myList.find(line1)->second;
		int int_line2= myList.find(line2)->second;
		int case1 = MapValue(int_line1).substr(0,1).compare("E");
		int case2 = MapValue(int_line2).substr(0,1).compare("E");
		
		int case3 = MapValue(int_line1).substr(0,1).compare("S");
		int case4 = MapValue(int_line2).substr(0,1).compare("E");
		if (case3==0 && case4==0 && weight>=5 )
		{
			//Do not add
			//cout<<MapValue(int_line1)<<" : "<<MapValue(int_line2)<<endl;
		}
		if(case1==0 || case2==0)
		{
			//Do not add
			//cout<<MapValue(int_line1)<<" : "<<MapValue(int_line2)<<endl;
		}
		else
		{
			g->add_edge(int_line1,int_line2,weight, false);
		}
		
	    getline(file1, line, '\n');
	} 
	shortest_path_algo_dijkstra(g, parent, distance, start);
    int value =myList.find("Mo")->second;
    find_shortest_path(value, parent);
    for(int j=7;j >= 0;j--)
    {
    	if(ptr[j]!="")
    	cout<<ptr[j]<<" ";
	}
    cout<<MapValue(value)<<" ";
    cout<<distance[value]<<endl;
    return 0;
}
