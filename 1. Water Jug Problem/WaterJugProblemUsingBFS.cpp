#include <bits/stdc++.h>
using namespace std;

// Representation of a state (x, y)
// x and y are the amounts of water in litres in the two jugs respectively
struct state
{
	int x, y;

	// c++ maps work on red black trees, and operations such as
	// insertion, deletion, update are done on the basis of comparision,
	bool operator<(const state &that) const
	{
		if (x != that.x)
			return x < that.x;
		return y < that.y;
	}
};

// Capacities of the two jugs respectively and the target amounts
int capacity_x, capacity_y, target_x, target_y;

state genNewState(const state current, map<state, bool> &visited)
{
	state new_state;

	// Rule 1:
	// Fill the first jug
	new_state = (state){capacity_x, current.y};
	if (visited[new_state] != true)
	{
		printf("Fill the first jug - State : (%d, %d)  \n", capacity_x, current.y);
		return new_state;
	}

	// Rule 2:
	// Fill the second jug
	new_state = (state){current.x, capacity_y};
	if (visited[new_state] != true)
	{
		printf("Fill the second jug - State : (%d, %d)\n", current.x, capacity_y);
		return new_state;
	}

	// Rule 3:
	// Empty the first jug
	new_state = (state){0, current.y};
	if (visited[new_state] != true)
	{
		printf("Empty the first jug - State : (%d, %d)\n", 0, current.y);
		return new_state;
	}

	// Rule 4:
	// Empty the second jug
	new_state = (state){current.x, 0};
	if (visited[new_state] != true)
	{
		printf("Empty the second jug - State : (%d, %d)\n", current.x, 0);
		return new_state;
	}

	// Rule 5:
	// Pour water from the second jug into the first jug until the first jug is full
	// or the second jug is empty
	if (current.y < capacity_y && current.x != 0)
	{
		int d = capacity_y - current.y;
		if (d >= current.x)
			new_state = (state){0, current.x + current.y};
		else
			new_state = (state){current.x - d, current.y + d};

		printf("Pour from second jug into first jug - State : (%d, %d)\n", min(current.x + current.y, capacity_x), max(0, current.x + current.y - capacity_x));
		return new_state;
	}

	if (current.x < capacity_x && current.y != 0)
	{
		int d = capacity_x - current.x;
		if (d >= current.y)
			new_state = (state){current.x + current.y, 0};
		else
			new_state = (state){current.x + d, current.y - d};

		printf("Pour from second jug into first jug - State : (%d, %d)\n", min(current.x + current.y, capacity_x), max(0, current.x + current.y - capacity_x));
		return new_state;
	}

	printf("Could not generate new state");
	exit(0);
	return new_state;
}

void bfs(state start)
{
	queue<state> bfs_queue;
	map<state, bool> visited;

	bool found_target = false;

	bfs_queue.push(start);
	visited[start] = true;
	printf("Initial State : (%d, %d)\n", 0, 0);

	while (!bfs_queue.empty())
	{
		// Get the state at the front of the stack
		state current = bfs_queue.front();
		bfs_queue.pop();

		// If the target state has been found, break
		if (current.x == target_x && current.y == target_y)
		{
			found_target = true;
			break;
		}

		state new_state = genNewState(current, visited);
		bfs_queue.push(new_state);
		visited[new_state] = true;
	}

	if (!found_target)
	{
		printf("\nTarget cannot be reached.\n");
		return;
	}
}

int main()
{
	printf("Enter the capacities of the two jugs : ");
	scanf("%d %d", &capacity_x, &capacity_y);
	printf("Enter the target capacities of the two jugs : ");
	scanf("%d %d", &target_x, &target_y);

	state initial_state = (state){0, 0};

	bfs(initial_state);
}