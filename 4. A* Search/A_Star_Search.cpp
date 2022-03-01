#include <bits/stdc++.h>
using namespace std;

class Graph
{
	int **adj;
	int no_of_nodes;
	vector<int> heuristic_values;

public:
	Graph(int n)
	{
		no_of_nodes = n;
		adj = (int **)malloc(no_of_nodes * sizeof(int *));
		for (int i = 0; i < no_of_nodes; i++)
			adj[i] = (int *)malloc(no_of_nodes * sizeof(int));

		// n is number of nodes
		for (int i = 0; i < no_of_nodes; i++)
		{
			for (int j = 0; j < no_of_nodes; j++)
				adj[i][j] = 0;
		}

		heuristic_values = vector<int>(no_of_nodes);
	}
	~Graph()
	{
		free(adj);
	}

	void add_edge(int u, int v, int cost)
	{
		adj[u][v] = cost;
	}

	void set_heuristic_values(vector<int> h)
	{
		heuristic_values = h;
	}

	int get_fn(int index, int dist)
	{
		return heuristic_values[index] + dist;
	}

	void a_star_search(int source, int goal)
	{
		auto comparator = [](const pair<int, int> &a, const pair<int, int> &b)
		{
			return a.second > b.second;
		};
		priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comparator)> pq(comparator);
		vector<bool> visited(no_of_nodes, false);
		vector<int> distance_from_source(no_of_nodes, INT_MAX);
		vector<int> parent(no_of_nodes, -1);
		pq.push(make_pair(source, get_fn(source, 0)));
		distance_from_source[source] = 0;

		while (!pq.empty())
		{
			int current = pq.top().first;
			pq.pop();

			if (current == goal)
				break;

			cout << "current node visited: " << current << endl;
			cout << "possible paths: " << endl;
			for (int next = 0; next < no_of_nodes; next++)
			{
				if (adj[current][next] != 0)
				{
					distance_from_source[next] = min(distance_from_source[next], distance_from_source[current] + adj[current][next]);
					int fn = get_fn(next, distance_from_source[next]);
					pq.push(make_pair(next, fn));
					parent[next] = current;
					cout << current << "->" << next << " f(N) = " << fn << endl;
				}
			}
			visited[current] = true;
		}

		int current = goal;
		while (current != -1)
		{
			cout << current << " <- ";
			current = parent[current];
		}
	}
};

int main()
{
	Graph g = Graph(6);
	g.add_edge(0, 1, 1);
	g.add_edge(0, 2, 4);
	g.add_edge(1, 2, 2);
	g.add_edge(1, 3, 5);
	g.add_edge(1, 4, 12);
	g.add_edge(2, 3, 2);
	g.add_edge(3, 4, 3);

	vector<int> heuristic_values = {7, 6, 2, 1, 0};
	g.set_heuristic_values(heuristic_values);

	int start = 0;
	int goal = 4;

	g.a_star_search(start, goal);
}