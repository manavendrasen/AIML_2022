#include <bits/stdc++.h>
using namespace std;

class Graph
{
private:
	int **adj;
	int noOfNodes;

public:
	Graph(int n)
	{
		noOfNodes = n;
		adj = (int **)malloc(noOfNodes * sizeof(int *));
		for (int i = 0; i < noOfNodes; i++)
			adj[i] = (int *)malloc(noOfNodes * sizeof(int));

		// n is number of nodes
		for (int i = 0; i < noOfNodes; i++)
		{
			for (int j = 0; j < noOfNodes; j++)
				adj[i][j] = 0;
		}
	}
	~Graph()
	{
		free(adj);
	};

	void addEdge(int startingIndex, int endIndex)
	{
		if (startingIndex >= noOfNodes && endIndex >= noOfNodes && startingIndex < 0 && endIndex < 0)
			cout << "Out of bound";
		else
		{
			// undirected graph
			adj[startingIndex][endIndex] = 1;
			adj[endIndex][startingIndex] = 1;
		}
	}

	void removeEdge(int startingIndex, int endIndex)
	{
		if (startingIndex >= noOfNodes && endIndex >= noOfNodes && startingIndex < 0 && endIndex < 0)
			cout << "Out of bound";
		else
		{
			// undirected graph
			adj[startingIndex][endIndex] = 0;
			adj[endIndex][startingIndex] = 0;
		}
	}

	int at(int r, int c)
	{
		if (r >= noOfNodes && c >= noOfNodes && r < 0 && c < 0)
		{
			cout << "Out of bound";
			return -1;
		}
		else
			return adj[r][c];
	}

	void print()
	{
		for (int i = 0; i < noOfNodes; i++)
		{
			for (int j = 0; j < noOfNodes; j++)
				cout << adj[i][j];
			cout << endl;
		}

		cout << endl;
	}

	void dfs(int i, int *visited)
	{
		visited[i] = 1;
		cout << i << " ";
		for (int j = 0; j < noOfNodes; j++)
		{
			if (adj[i][j] == 1 && visited[j] == 0)
				dfs(j, visited);
		}
	}
};

int main()
{
	// number of nodes in graph
	int n = 6;
	int visited[] = {0, 0, 0, 0, 0, 0};
	Graph adj = Graph(n);
	// adding edges
	adj.addEdge(0, 1);
	adj.addEdge(0, 2);
	adj.addEdge(1, 3);
	adj.addEdge(1, 4);
	adj.addEdge(2, 5);
	adj.print();

	adj.dfs(0, visited);
}