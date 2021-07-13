/***********************************************************
STUDENT INFORMATION
Full Name : ANIL KESKÝN
Student ID:  150170801
Q1
**********************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <stdlib.h> 
#define INT_MAX 1000


using namespace std;
int min_func(int a, int b) { return (a > b) ? b : a; }
class Graph{
public:
	int node_count;
	int edge_count;
	int** adjacency_matrix;
	Graph(){
	};
	void read_file(char* filename);
	void print_adjacency_matrix();
	int weight(int i, int j){return this->adjacency_matrix[i][j];}
	~Graph();
};
Graph::~Graph(){
	for(int i = 0; i < node_count; i++){
		delete [] adjacency_matrix[i];
	}
}
void Graph::print_adjacency_matrix(){	
	for(int i = 0; i < this->node_count; i++){
		for(int j = 0; j < this->node_count; j++){
			cout<<this->adjacency_matrix[i][j]<<", ";
		}
		cout<<endl;
	}
}
void Graph::read_file(char* filename){
	
	ifstream input(filename);

	if (!input.is_open()) {
		cerr << "File named \"" << filename << "\" could not open!" << endl;
	}
	string line;
	if (getline(input, line)) {
		this->node_count = stoi(line);
	}
	int count=0;
	adjacency_matrix = new int*[node_count];
    for (int row = 0; row < node_count; row++) {
        adjacency_matrix[row] = new int[node_count];
        for (int column = 0; column < node_count; column++) {
            adjacency_matrix[row][column] = 0;
        }
    }
    int w;
	while (!input.eof()) {
		count++;
		getline(input, line, '\t');
		int i=stoi(line);
		getline(input, line, '\t');
		int j=stoi(line);
		input>>w;
		adjacency_matrix[i][j]=w;
		adjacency_matrix[j][i]=w;
		getline(input, line, '\n');
	}
    this->edge_count = count;
}
bool IsFinger(Graph* graph,int *arr)
{
	for(int i =0;i<graph->node_count;i++)
	{
		if(arr[i]==1)
			return true;
	}
	return false;
}
void Modified_Dijkstra(Graph* graph){
	
	int *status= new int[graph->node_count];
	int wt[graph->node_count];
	int dad[graph->node_count];
	
	for(int v =0;v<graph->node_count;v++)
	{
		status[v]=0;
		wt[v]=-1;
		dad[v]=-1;
	}
	status[0]=2;
	wt[0]=INT_MAX;
	for(int w =0; w<graph->node_count;w++)
	{
		if(graph->weight(0,w)>0)
		{
			status[w]=1;
			wt[w]=graph->weight(0,w);
			dad[w]=0;
		}
	}
	while(IsFinger(graph,status))
	{
		int v = 0;
		int temp;
		for(int i=0;i<graph->node_count;i++)
		{
			if(status[i]==1)
			{
				v=i;
				temp=wt[i];
				break;
			}
		}
		for(int i=v+1;i<graph->node_count;i++)
		{
			if(wt[i]>temp && status[i]==1)
			{
				v=i;
				temp=wt[i];
			}
		}
		status[v]=2;
		for(int w =0;w<graph->node_count;w++)
		{
			if(graph->weight(v,w)>0)
			{
				if(status[w]==0)
				{
					status[w]=1;
					wt[w]=min_func(wt[v], graph->weight(v,w));
					dad[w] = v;
				}
				else if(status[w] == 1 && wt[w] <min_func(wt[v], graph->weight(v,w)))
				{
					wt[w] = min_func(wt[v], graph->weight(v,w));
					dad[w] = v;
				}
			}
		}
	}
	cout<<"###########RESULTS###########"<<endl;
	cout<<endl;
	
	cout<<"1. WT ARRAY"<<endl;
	cout<<"------------------------"<<endl;
	cout<<"  ";
	for(int i = 0; i < graph->node_count - 1; i++){
		cout << wt[i] << ", ";
	}
	cout << wt[graph->node_count - 1] << endl;
	
	// The following lines print the final path.
	// Do not change anything in the following lines.
	int iterator = graph->node_count - 1;
	vector<int> path_info;
	path_info.push_back(iterator);
	while(iterator != 0){
		path_info.push_back(dad[iterator]);
		iterator = dad[iterator];
	}
	cout<<endl;
	cout<<"2. MAXIMUM CAPACITY PATH"<<endl;
	cout<<"------------------------"<<endl;
	cout<<"  ";
	vector<int>::iterator it;
    for (it = path_info.end() - 1; it > path_info.begin(); it--)
        cout << *it << " -> ";
    cout<<*path_info.begin()<<endl;
    
    cout<<endl;
    cout<<"3. MAXIMUM CAPACITY"<<endl;
    cout<<"------------------------"<<endl;
    cout<<"  ";
    cout<<wt[graph->node_count - 1]<<endl;
    cout<<"#############################"<<endl;
    
    return;
    
}

int main(int argc, char **argv){
	Graph* graph = new Graph();
	graph->read_file(argv[1]);
	Modified_Dijkstra(graph);
//	graph->print_adjacency_matrix();
	return 0;	
}
