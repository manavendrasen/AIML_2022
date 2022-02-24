
#include <bits/stdc++.h>
using namespace std;

class Queue
{
private:
	int *val;
	int size;
	int rear;
	int front;

public:
	Queue(int n, int initialValue = 0)
	{
		size = n;
		val = (int *)malloc(sizeof(int) * size);
		for (int i = 0; i < size; i++)
		{
			val[i] = initialValue;
		}
		rear = -1;
		front = -1;
	}

	~Queue()
	{
		size = 0;
		rear = front = -1;
		free(val);
	}

	bool isEmpty()
	{
		if (front > rear || front == rear == -1)
			return true;
		return false;
	}

	void enqueue(int elem)
	{
		if (rear == size - 1)
		{
			cout << "Overflow" << endl;
			return;
		}

		if (rear == -1)
		{
			// cout << "enqueue " << elem << " first elem at " << 0 << endl;
			front = 0;
			rear = 0;
			val[rear] = elem;
		}

		else
		{
			rear++;
			// cout << "enqueue " << elem << " at " << rear << endl;
			val[rear] = elem;
		}
	}

	int dequeue()
	{
		if (front == -1 || front > rear)
		{
			cout << "Underflow" << endl;
			return -1;
		}

		int elem = val[front];
		// cout << "dequeue" << elem << " at " << front << endl;
		front++;
		return elem;
	}

	void print()
	{
		for (int i = front; i <= rear; i++)
			cout << val[i];

		cout << endl;
	}

	void printAll()
	{
		for (int i = 0; i < size; i++)
			cout << val[i];

		cout << endl;
	}
};

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
};

int main()
{
	// number of nodes in graph
	int n = 6;
	int visited[] = {0, 0, 0, 0, 0, 0};
	Queue q = Queue(100);
	Graph adj = Graph(n);
	// adding edges
	adj.addEdge(0, 1);
	adj.addEdge(0, 2);
	adj.addEdge(1, 3);
	adj.addEdge(1, 4);
	adj.addEdge(2, 5);
	adj.print();

	// visit first node
	int startingIndex = 0;
	q.enqueue(startingIndex);
	visited[startingIndex] = 1;
	cout << "visited - " << startingIndex << endl;
	while (!q.isEmpty())
	{
		int node = q.dequeue();
		for (int j = 0; j < n; j++)
		{
			if (adj.at(node, j) == 1 && visited[j] == 0)
			{
				cout << "visited - " << j << endl;
				visited[j] = 1;
				q.enqueue(j);
			}
		}
	}
}