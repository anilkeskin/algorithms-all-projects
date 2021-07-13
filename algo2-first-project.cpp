/*
ANIL KESKÝN - 150170801

Please use g++ -std=c++11 main.cpp -o main
./main DFS TWO TWO FOUR outputfile

*/
#include <bits/stdc++.h>
#include<string>
using namespace std;
class Node{
    public:
        int layer;
        int *array;
        Node *child[10];
        Node(int* arr,int num);
};

Node::Node(int* arr,int num)
{
	array= new int [num];
	for(int i =0;i<num;i++) array[i]=arr[i];
}

int visited_nodes=0;
int all_nodes=0;
void AddAllCases(int currlayer,int num,Node* head,int id){
  
	if(currlayer>num)
	{
		for(int i=0;i<num;i++)
		{
            head->layer = num;
            head->child[i] = NULL;
        }
    }
    else
	{
        if(id != -1) head->array[currlayer-1]  = id;
        int control=0;
        for(int i =0;i<num;i++)
        {
        	for(int j=0;j<num;j++)
        	{
        		if(head->array[j]==head->array[i] && head->array[j]!=-1 && i!=j)
        		{
        			control=1;
        			break;
				}
			}
		}
		if(head->array[0]==0)control=1;
		if(control==0)
		{
			for(int i=0;i<10;i++)
			{
				all_nodes++;
            	head->child[i] = new Node(head->array,num); 
            	head->layer = currlayer;
            	AddAllCases((currlayer+1),num,head->child[i],i);
			}
		}
		else
		{	
			for(int i=0;i<10;i++)
			{
				head->layer=currlayer;
            	head->child[i] = NULL; 
			}
		}
    }
}
int l_line1=0,l_line2=0,l_line3=0;
int *LINE_1;
int *LINE_2;
int *LINE_3;
int *VALUES;
int num=0;
string outputFileName;
string un;
int IsSolution() {
    int number1 = 0, number2 = 0, result = 0, i, l;
    if ((VALUES[LINE_1[0]] == 0) || (VALUES[LINE_2[0]] == 0) || (VALUES[LINE_3[0]] == 0)) {
        return 0;
    }
    for(i=0,l=l_line1; i<l; ++i) number1 = number1*10 + VALUES[LINE_1[i]];
    for(i=0,l=l_line2; i<l; ++i) number2 = number2*10 + VALUES[LINE_2[i]];
    for(i=0,l=l_line3;i<l; ++i) result = result*10 + VALUES[LINE_3[i]];
    i = (number1 + number2) == result;
    int farkli=0;
    for(int i =0;i<num;i++)
    {
    	for(int j =i+1;j<num;j++)
			if(VALUES[i]==VALUES[j])
				farkli=1;
	}
	
    if(i && farkli==0) return 1;//Solution found.
    
    return 0;//it is not a solution
}
int elemansayisi=0;
int FindUniqueCharacters(string str){
	int m=0;
    int count = 0;
    for (int i = 0; i < str.length(); i++)
	{
         bool appears = false;
         for (int j = 0; j < i; j++)
		 {
            if (str[j] == str[i])
			{
                appears = true;
                break;
            }
         }
         if (!appears)
		 {
            count++;
            un[m]=str[i];
            m++;
         }
    }
    return count;
}

void BFS(Node* head) {

  queue<Node*> queue1;
  queue1.push(head);
  Node* current ;
  bool sonuc=false;
	while(!queue1.empty() && !sonuc)
	{
		int temp=0;
		current = queue1.front();
		queue1.pop();
		visited_nodes++;
		for(int i =0;i<num;i++) 
		{
			VALUES[i]=current->array[i];
			if(VALUES[i]==-1) temp=1;
		}
		if(temp==0) sonuc=IsSolution();
		
		for(int i =0;i<10;i++)
			if(current->child[i]!=NULL) 
				queue1.push(current->child[i]);
	}

}
int sayac=0;
void DFS(Node* head)
{
	if(head!=NULL && sayac!=1)
	{
		if(head->layer<num)
		{
			int temp=0;
			for(int s=1;s<head->layer;s++)
			{
				if(head->array[s]==head->array[head->layer]) temp=1;
			}
			if(temp==0) for(int j=0;j<10;j++) DFS(head->child[j]);
		}
		else if(head->layer==num)
		{
			for(int i =0;i<num;i++) 
			{
				VALUES[i]=head->array[i];
			}
			visited_nodes++;
			sayac=IsSolution();
			if(sayac==1)
			{
				ofstream dosyaYaz(outputFileName);
				if ( dosyaYaz.is_open() )
				{
					dosyaYaz << "\t0\t1\t2\t3\t4\t5\t6\t7\t8\t9"<<endl;
					for(int i=0;i<num;i++)
					{
						dosyaYaz<<(char)un[i];
						dosyaYaz<<"\t";
						for(int j=0;j<10;j++)
						{
							if(VALUES[i]==j)dosyaYaz<<"1\t";
							else dosyaYaz<<".\t";
						}
						dosyaYaz<<endl;
					}
    				dosyaYaz.close();
				}
			}
		}
		else for(int j=0;j<10;j++) DFS(head->child[j]);
	}
}
int main(int argc, char** argv)
{
	outputFileName=argv[5];
	outputFileName+=".txt";
	
	string birinci=argv[2];
	string ikinci=argv[3];
	string ucuncu=argv[4];
	
	string secenek=argv[1];
	
	LINE_1=new int[birinci.length()];//ilk kelimebin karakter sayýsý
	l_line1=birinci.length();
	LINE_2=new int[ikinci.length()];//ikinci kelimenin karakter sayýsý
	l_line2=ikinci.length();
	LINE_3=new int[ucuncu.length()];//üçüncü kelimenin karakter sayýsý
	l_line3=ucuncu.length();
	
	string a = birinci+ikinci+ucuncu;
    num= FindUniqueCharacters(a);
    VALUES=new int[num];
    for(int i=0;i<num;i++)
    {
    	for(int j=0;j<birinci.length();j++)
    	{
    		if(un[i]==birinci[j])
    		{
    			LINE_1[j]=i;
			}
		}
		
		for(int j=0;j<ikinci.length();j++)
    	{
			if(un[i]==ikinci[j])
    		{
    			LINE_2[j]=i;
			}
		}
		
		for(int j=0;j<ucuncu.length();j++)
    	{
    		if(un[i]==ucuncu[j])
    		{
    			LINE_3[j]=i;
			}
		}	
	}
	int* matrix=new int[num];
	for(int i =0;i<num;i++)matrix[i]=-1;
	Node* root = new Node(matrix,num);
	AddAllCases(0,num,root,-1);
	clock_t start, end;
	start = clock();
	if(secenek=="DFS")
	{
		DFS(root);
	}
	else
	{
		BFS(root);
	}
	end = clock();
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	
	if(secenek=="BFS")
	{
		ofstream dosyaYaz(outputFileName);
				if ( dosyaYaz.is_open() )
				{
					dosyaYaz << "\t0\t1\t2\t3\t4\t5\t6\t7\t8\t9"<<endl;
					for(int i=0;i<num;i++)
					{
						dosyaYaz<<(char)un[i];
						dosyaYaz<<"\t";
						for(int j=0;j<10;j++)
						{
							if(VALUES[i]==j)dosyaYaz<<"1\t";
							else dosyaYaz<<".\t";
						}
						dosyaYaz<<endl;
					}
    				dosyaYaz.close();
    			}
	}
	cout<<"Algorithm: "<<secenek<<endl;
	cout<<"Number of the visited nodes: "<<visited_nodes<<endl;
	cout<<"Maximum number of nodes kept in the memory: "<<all_nodes<<endl;
	cout<<"Running time: "<<time_taken << setprecision(2)<<" seconds"<<endl;
	cout<<"Solution: ";
	for(int i =0;i<num;i++)
	{
		if(i==num-1)cout<<un[i]<<": "<<VALUES[i];
		else cout<<un[i]<<": "<<VALUES[i]<<", ";
	}
}
