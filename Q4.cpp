#include<iostream>
#include<list>
#include<string.h>
using namespace std;

int c_time = 1;

void dfs(int s, list<int>* adjl, bool *visited, int *parent, int *disc_time, int *low, bool *articulation, bool pf)
{
	cout<<"\ncalled for vertex "<<s<<endl;
	int pc  =0;
	for(auto nebar:adjl[s])
	{
		if(visited[nebar] == false)
		{
			if(pf == true)
			{
				++pc;
				if(pc >1)
				{
					articulation[s] = true;
					cout<<"setting true "<<s<<endl;
				}
			}
			visited[nebar] = true;
			parent[nebar] = s;
			disc_time[nebar] = c_time;
			++c_time;
			low[nebar] = disc_time[nebar];
			dfs(nebar, adjl, visited, parent, disc_time, low, articulation, false);
		}
	}

	cout<<"\nrec end for "<<s<<endl;

	for(auto nebar:adjl[s])
	{
		cout<<"\n neighbour is "<<nebar<<endl;
		if(parent[s] != -1)
		{
			if(disc_time[nebar] > disc_time[s])
			{
				cout<<"descendant: compareing "<<low[s]<<' '<<low[nebar]<<endl;
				low[s] = min(low[s], low[nebar]);

			}

			else
			{
				cout<<"ancestor: compareing "<<low[s]<<' '<<disc_time[nebar]<<endl;
				low[s] = min(low[s], disc_time[nebar]);
			}
		}
	}

	cout<<"\nreturning from "<<s<<endl;
}

int main()
{
	int vertices, u, v, e, lv, lv1, lv2;
	cout<<"No. of vertices ?\n";
	cin>>vertices;
	cout<<"\nNo. of edges ?\n";
	cin>>e;

	list<int> *adjl = new list<int>[vertices+1];
	cout<<"Enter "<<e<<" edges\n";
	lv = e;
	while(e--)
	{
		cin>>u>>v;
		adjl[u].push_back(v);
		adjl[v].push_back(u);
	}

	bool articulation[vertices+1];
	memset(articulation, false, sizeof(bool)*(vertices+1));

	bool visited[vertices+1];
	memset(visited, 0, sizeof(bool)*(vertices+1));

	int parent[vertices+1];
	memset(parent, -1, sizeof(int)*(vertices+1));

	int disc_time[vertices+1];
	memset(disc_time, 0, sizeof(int)*(vertices+1));

	int low[vertices+1];
	memset(low, 0, sizeof(int)*(vertices+1));


	for(lv = 1; lv<=vertices; lv++)
	{
		if(visited[lv] == false)
		{
			disc_time[lv] = c_time;
			++c_time;
			visited[lv] = true;
			dfs(lv, adjl, visited, parent, disc_time, low, articulation, true);		
		}
	}

	cout<<"\narticulation loop\n";
	for(lv=1;lv<= vertices; lv++)
	{
		cout<<"\nvertex "<<lv<<endl;
		if(parent[parent[lv]] != -1)
		{
			if(low[lv] >= disc_time[parent[lv]])
			{
				cout<<"\ncompare "<<low[lv]<<' '<<disc_time[parent[lv]]<<endl;
				articulation[parent[lv]] = true;
			}
		}

	}
	cout<<"\narticulation :";
	for(lv=1;lv<=vertices;lv++)
		cout<<articulation[lv]<<' ';
	cout<<endl;

	cout<<"\nvisited :";
	for(lv=1;lv<=vertices;lv++)
		cout<<visited[lv]<<' ';
	cout<<endl;

	cout<<"\ndiscovery :";
	for(lv=1;lv<=vertices;lv++)
		cout<<disc_time[lv]<<' ';
	cout<<endl;

	cout<<"\nlow :";
	for(lv=1;lv<=vertices;lv++)
		cout<<low[lv]<<' ';
	cout<<endl;

	cout<<"\nThe articulation points are :";
	for(lv=1;lv<=vertices;lv++)
		if(articulation[lv] == true)
			cout<<lv<<' ';
	cout<<endl;
	

}