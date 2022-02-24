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
	state newState;

	// Rule 1:
	// Fill the first jug
	newState = (state){capacity_x, current.y};
	if (visited[newState] != true)
	{
		printf("Fill the first jug - State : (%d, %d)  \n", capacity_x, current.y);
		return newState;
	}

	// Rule 2:
	// Fill the second jug
	newState = (state){current.x, capacity_y};
	if (visited[newState] != true)
	{
		printf("Fill the second jug - State : (%d, %d)\n", current.x, capacity_y);
		return newState;
	}

	// Rule 3:
	// Empty the first jug
	newState = (state){0, current.y};
	if (visited[newState] != true)
	{
		printf("Empty the first jug - State : (%d, %d)\n", 0, current.y);
		return newState;
	}

	// Rule 4:
	// Empty the second jug
	newState = (state){current.x, 0};
	if (visited[newState] != true)
	{
		printf("Empty the second jug - State : (%d, %d)\n", current.x, 0);
		return newState;
	}

	// Rule 5:
	// Pour water from the second jug into the first jug until the first jug is full
	// or the second jug is empty
	if (current.y < capacity_y && current.x != 0)
	{
		int d = capacity_y - current.y;
		if (d >= current.x)
			newState = (state){0, current.x + current.y};
		else
			newState = (state){current.x - d, current.y + d};

		printf("Pour from second jug into first jug - State : (%d, %d)\n", min(current.x + current.y, capacity_x), max(0, current.x + current.y - capacity_x));
		return newState;
	}

	if (current.x < capacity_x && current.y != 0)
	{
		int d = capacity_x - current.x;
		if (d >= current.y)
			newState = (state){current.x + current.y, 0};
		else
			newState = (state){current.x + d, current.y - d};

		printf("Pour from second jug into first jug - State : (%d, %d)\n", min(current.x + current.y, capacity_x), max(0, current.x + current.y - capacity_x));
		return newState;
	}

	printf("Could not generate new state");
	exit(0);
	return newState;
}

void dfs(state start)
{
	stack<state> dfs_stack;
	map<state, bool> visited;

	bool foundTarget = false;

	dfs_stack.push(start);
	visited[start] = true;
	printf("Initial State : (%d, %d)\n", 0, 0);

	while (!dfs_stack.empty())
	{
		// Get the state at the front of the stack
		state current = dfs_stack.top();
		dfs_stack.pop();

		// If the target state has been found, break
		if (current.x == target_x && current.y == target_y)
		{
			foundTarget = true;
			break;
		}

		state newState = genNewState(current, visited);
		dfs_stack.push(newState);
		visited[newState] = true;
	}

	if (!foundTarget)
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

	state initialState = (state){0, 0};

	dfs(initialState);
}