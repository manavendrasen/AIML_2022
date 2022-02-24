#include <bits/stdc++.h>
using namespace std;

#define N 3

class Solution
{
private:
	const static int up = 1;
	const static int down = 2;
	const static int left = 3;
	const static int right = 4;

	// Goal State of the puzzle
	int goalState[N][N] = {
			{1, 2, 3},
			{4, 0, 5},
			{6, 7, 8}};

public:
	// dislay the puzzle state
	void printGrid(int **state)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cout << state[i][j] << " | ";
			}
			cout << endl;
		}
	}

	// calculate the heuristic value
	int calculateHeuristicValue(int **temp)
	{
		int hValue = 0;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (temp[i][j] != goalState[i][j])
				{
					hValue++;
				}
			}
		}
		cout << "Heuristic Value: " << hValue << endl;
		cout << endl;
		return hValue;
	}

	// move the 0 tile
	void makeMove(int **state, int move)
	{
		int flag = 0;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (state[i][j] == 0)
				{
					if (move == up)
					{
						state[i][j] = state[i - 1][j];
						state[i - 1][j] = 0;
						flag = 1;
						break;
					}
					else if (move == down)
					{
						state[i][j] = state[i + 1][j];
						state[i + 1][j] = 0;
						flag = 1;
						break;
					}
					else if (move == left)
					{
						state[i][j] = state[i][j - 1];
						state[i][j - 1] = 0;
						flag = 1;
						break;
					}
					else if (move == right)
					{
						state[i][j] = state[i][j + 1];
						state[i][j + 1] = 0;
						flag = 1;
						break;
					}
				}
			}
			if (flag == 1)
			{
				break;
			}
		}
	}
	// generate new temporary state by moving the 0 tile
	int generateNextState(int **state, int move)
	{
		int **temp = new int *[N];
		for (int i = 0; i < N; i++)
		{
			temp[i] = new int[N];
			for (int j = 0; j < N; j++)
			{
				temp[i][j] = state[i][j];
			}
		}
		makeMove(temp, move);
		printGrid(temp);
		int hValue = calculateHeuristicValue(temp);
		for (int i = 0; i < N; i++)
			delete temp[i];
		delete temp;
		return hValue;
	}

	void SAHillClimbing(int **state, int formerMove)
	{
		int childrenHValues[4] = {100, 100, 100, 100};
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (state[i][j] == 0)
				{
					if (i > 0 && formerMove != down)
					{
						cout << "Checking child state (moving 0 up) " << endl;
						childrenHValues[0] = generateNextState(state, up);
					}
					if (i < N - 1 && formerMove != up)
					{
						cout << "Checking child state (moving 0 down) " << endl;
						childrenHValues[1] = generateNextState(state, down);
					}
					if (j > 0 && formerMove != right)
					{
						cout << "Checking child state (moving 0 left) " << endl;
						childrenHValues[2] = generateNextState(state, left);
					}
					if (j < N - 1 && formerMove != left)
					{
						cout << "Checking child state (moving 0 right) " << endl;
						childrenHValues[3] = generateNextState(state, right);
					}
				}
			}
			cout << endl;
		}
		int localOptimum = 99;
		int move = 0;
		for (int i = 0; i < 4; i++)
		{
			if (childrenHValues[i] < localOptimum)
			{
				localOptimum = childrenHValues[i];
				move = i + 1;
			}
		}
		// move and update state
		makeMove(state, move);
		cout << "Moved to state using Steepest Ascent: " << endl;
		printGrid(state);

		// base case
		if (localOptimum == 0)
		{
			cout << "Reached Goal!" << endl;
			return;
		}
		else
			SAHillClimbing(state, move);
	}
};

int main()
{
	// For getting input from input.txt file
	freopen("input.txt", "r", stdin);

	// Printing the Output to output.txt file
	freopen("output.txt", "w", stdout);

	int t;
	cin >> t;

	while (t--)
	{
		cout << "Test Case " << t << ": " << endl;
		int **initialState = new int *[N];
		for (int i = 0; i < N; i++)
		{
			initialState[i] = new int[N];
			for (int j = 0; j < N; j++)
			{
				cin >> initialState[i][j];
			}
		}

		Solution s = Solution();
		cout << "Initial State: " << endl;
		s.printGrid(initialState);
		s.SAHillClimbing(initialState, 0);
		cout << "----------------------------------" << endl;
	}
}