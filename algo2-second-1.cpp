/*
	ANIL KESKÝN - 150170801 - Q1
*/
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
map<string, int> myList;
typedef pair<int, int> iPair;
string sArray1[100];
string sArray2[100];
int stringSize=0;
class Graph
{
	int V; 
	list< pair<int, int> > *adj;
public:
	Graph(int V);
	void addEdge(int u, int v, int w);
	void primMST();
};
Graph::Graph(int V)
{
	this->V = V;
	adj = new list<iPair> [V];
}
void Graph::addEdge(int u, int v, int w)
{
	adj[u].push_back(make_pair(v, w));
	adj[v].push_back(make_pair(u, w));
}
string MapValue(int value)
{
	string deger="";
	for (auto it = myList.begin(); it != myList.end(); ++it)
    if (it->second == value) deger=it->first;
       
    return deger;
}
void doSwap (string &string1, string &string2) {
    string temp;
    temp = string1;
    string1 = string2;
    string2 = temp;
}
void Graph::primMST()
{
	priority_queue< iPair, vector <iPair> , greater<iPair> > pq;
	int src = 0;
	vector<int> key(V, INF);
	vector<int> parent(V, -1);
	vector<bool> inMST(V, false);
	pq.push(make_pair(0, src));
	key[src] = 0;
	int _first_value=-1;
	int _second_value=-1;
	list< pair<int, int> >::iterator i;
	int u1 = pq.top().second;
	// GP CH
	for (i=adj[0].begin(); i != adj[0].end(); ++i)
	{
		int v = (*i).first;
		int weight = (*i).second;
		int case4 = MapValue(u1).substr(0,2).compare("GP");
		int case5 = MapValue(v).substr(0,2).compare("Ch");
		if((case4==0 && case5==0))
		{
		//	cout<<MapValue(u1)<<" : "<<MapValue(v)<<" : "<<weight<<" : "<<v<<endl;
			key[v] = weight;
			pq.push(make_pair(key[v], v));
			parent[v] = u1;
			_first_value=v;
			break;													
 		}	
	}
	// GP HÝPP
	//u1 = pq.top().second;
	for (i=adj[0].begin(); i != adj[0].end(); ++i)
	{
		int v = (*i).first;
		int weight = (*i).second;
		int case4 = MapValue(u1).substr(0,2).compare("GP");
		int case5 = MapValue(v).substr(0,4).compare("Hipp");
		
		if((inMST[v] == false) && (key[v] > weight) && (case4==0 && case5==0))
		{
		//	cout<<MapValue(u1)<<" : "<<MapValue(v)<<" : "<<weight<<" : "<<v<<endl;
			key[v] = weight;
			pq.push(make_pair(key[v], v));
			parent[v] = u1;
			_second_value=v;
			break;													
 		}	
	}
	while (!pq.empty())
	{
		int u = pq.top().second;
		pq.pop();
		inMST[u] = true;
		list< pair<int, int> >::iterator i;

		for (i=adj[u].begin(); i != adj[u].end(); ++i)
		{
			int v = (*i).first;
			int weight = (*i).second;
			int case1 = MapValue(u).substr(0,2).compare(MapValue(v).substr(0,2));
			int case2 = MapValue(u).substr(0,4).compare("Hipp");
			int case3 = MapValue(v).substr(0,3).compare("Bas");
			if((inMST[v] == false) && (key[v] > weight) && (case1!=0) && (case2!=0 || case3!=0))
			{
				if(_first_value!=v && _second_value!=v ) 
				{
				//	cout<<MapValue(u)<<" : "<<MapValue(v)<<" : "<<weight<<" : "<<v<<endl;
					key[v] = weight;
					pq.push(make_pair(key[v], v));
					parent[v] = u;
				}												
 			}	
		}
	}
	/*
	for (int i = 1; i < V;i++)
	{
		cout<<MapValue(parent[i])<<" "<<MapValue(i)<<" "<<key[i]<<endl;			
	}
	*/
	//cout<<"---"<<endl;
	
	string V1[100];
	string V2[100];
	int _key[100];
	int cost=0;
	for (int i = 1; i < V;i++)
	{
		V1[i]=MapValue(parent[i]);
		V2[i]=MapValue(i);
		_key[i]=key[i];
		cost+=_key[i];	
		//cout<<V1[i]<<" "<< V2[i]<<" " << _key[i]<<endl;		
	}
	//cout<<cost<<endl;
	
	int temp;
	for(int i=1;i<V;i++) 
	{
		for(int j=1;j<V;j++) 
		{ 
			if(_key[j]>_key[j+1] && _key[j+1]!=0) 
			{ 
				temp=_key[j]; 
				_key[j]=_key[j+1]; 
				_key[j+1]=temp; 
				doSwap(V1[j], V1[j+1]);
				doSwap(V2[j], V2[j+1]);			
			} 
		}
	}
	int deger=0;
	for (int i = 1; i <= V;i++)
	{
		for(int j =1;j<=stringSize;j++)
		{
			if(V1[i]==sArray1[j] && V2[i]==sArray2[j])
			{
				if(_key[i]!=0 && V1[i]!="" && V2[i]!="")
				cout<< V1[i] << " " << V2[i]<<" "<<_key[i] <<endl;
				deger=1;
			}
		}
		if(deger==0)
		{
			if(_key[i]!=0 && V1[i]!="" && V2[i]!="")
			cout<< V2[i] << " " << V1[i]<<" "<<_key[i] <<endl;
		}
		deger=0;			
	}
	if(cost>0)
		cout<<cost<<endl;
	
}
int main()
{
	int count=0;
	ifstream file;
	string fileName;
	cin>>fileName;
	file.open(fileName);
	string line,line1,line2;
	int weight;
	int firstline=0;
	while(!file.eof()){
		stringSize++;
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
    int im=1;
	Graph g(myList.size());
	ifstream file1;
	file1.open(fileName);
	while(!file1.eof()){
		
		getline(file1, line, ',');
		line1=(string)line;
		getline(file1, line, ',');
		line2=(string)line;
		file1 >> weight;
		sArray1[im]=line1;
		sArray2[im]=line2;
		im++;
		int int_line1= myList.find(line1)->second;
		int int_line2= myList.find(line2)->second;
		g.addEdge(int_line2, int_line1, weight);
	    getline(file1, line, '\n');
	} 
	g.primMST();
	
	
	return 0;
}

