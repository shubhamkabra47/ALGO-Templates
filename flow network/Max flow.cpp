// Implementation of max flow algorithm using adjacency matrix. 
// This implementation keeps track of forward and backward edges seperately, (directed weighted graph).
// For regular max flow, set all edge cost to 0.

// Running time, 
// 	max flow: O(E*|V|^3) augmentations

// INPUT: 
// 	- graph, constructed using buildGraph
// 	- source - 1
// 	- sink - V

// OUTPUT:
// 	- (maximum flow value)
// 	- To get the actual value of flow see the weight matrix positive value

#include "bits/stdc++.h"
using namespace std;

#define FF first
#define SS second

typedef long long int LL;
typedef pair< int, int > pii;
typedef vector< int > VI;


const static int MAX = 5e3;
LL weight[MAX+5][MAX+5] = {{0}};

class MAXFLOW{
	const static LL INF = 1e15;
	int V, E;

public: 
	vector< VI > graph;
	VI temp;
	int path_capacity;

	MAXFLOW(int N, int M){ // Vertices and Edges
		V = N;
		E = M;

		graph.resize(V+2);
	}

	void buildGraph(){
		int x, y; LL wt;

		for(int i = 0;i<E;i++){
			cin>>x>>y>>wt;
			graph[x].push_back(y);
			weight[x][y] += wt;
		}
	}

	bool dfs(int id, vector<bool> &seen, bool found){
		if(id==V){
			temp.push_back(V);
			return true; // Found a path from source to V
		}

		for(auto it: graph[id]){
			if(!seen[it] and weight[id][it]){
				seen[it] = true;
				if(dfs(it, seen, found)){
					temp.push_back(id);
					return true;
				}
			}
		}
	}

	LL max_flow(){
		LL result = 0;

		while(true){
			// Continue untill augmenting path is found
			LL resutl = 0;
			vector<bool> seen(V+2, false);
			seen[1] = true;

			temp.clear();
			path_capacity = 0;
			if(!dfs(1, seen, false)) break;
			
			vector< LL > capacity(temp.size()+2);

			LL mini = INF;

			for(int i = 1;i<temp.size();i++){
				capacity[i-1] = weight[temp[i]][temp[i-1]]; // forward edge
				mini = min(mini, capacity[i-1]);
			}

			// Updating... The network... Adding back edges

			for(int i = 1;i<temp.size();i++){
				weight[temp[i]][temp[i-1]]-=mini;
				weight[temp[i-1]][temp[i]]+=mini;

				graph[temp[i-1]].push_back(temp[i]);
			}

			result+=mini;
		}
		return result;
	}
};

