#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> next_cost;

class Graph
{
private:
	/**
	 * the graph is stored as
	 * index: 0, 1, 2, 3 ...  no_of_nodes - 1;
	 * value: [[(next, cost), (next, cost)...], [(next, cost), (next, cost)], ...]
	 **/
	vector<vector<next_cost>> graph;
	int no_of_nodes;

public:
	Graph(int n)
	{
		graph.resize(n);
		no_of_nodes = n;
	}

	void addedge(int x, int y, int cost)
	{
		// 2 way connection
		graph[x].push_back(make_pair(y, cost));
		graph[y].push_back(make_pair(x, cost));
	}

	void best_first_search(int source, int target)
	{
		vector<bool> visited(no_of_nodes, false);
		auto comparator = [](const next_cost &a, const next_cost &b)
		{
			return a.second > b.second;
		};
		priority_queue<next_cost, vector<next_cost>, decltype(comparator)> pq(comparator);
		pq.push(make_pair(source, 0));
		visited[source] = true;
		while (!pq.empty())
		{
			int current = pq.top().first;
			cout << current << " ";
			pq.pop();
			if (current == target)
				break;

			for (int next = 0; next < graph[current].size(); next++)
			{
				if (!visited[graph[current][next].first])
				{
					visited[graph[current][next].first] = true;
					pq.push(make_pair(graph[current][next].first, graph[current][next].second));
				}
			}
		}
	}
};

int main()
{
	int no_of_nodes = 14;

	Graph graph(no_of_nodes);

	graph.addedge(0, 1, 3);
	graph.addedge(0, 2, 6);
	graph.addedge(0, 3, 5);
	graph.addedge(1, 4, 9);
	graph.addedge(1, 5, 8);
	graph.addedge(2, 6, 12);
	graph.addedge(2, 7, 14);
	graph.addedge(3, 8, 7);
	graph.addedge(8, 9, 5);
	graph.addedge(8, 10, 6);
	graph.addedge(9, 11, 1);
	graph.addedge(9, 12, 10);
	graph.addedge(9, 13, 2);

	int source = 0;
	int target = 9;

	// Function call
	graph.best_first_search(source, target);

	return 0;
}
