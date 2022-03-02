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
	int goal_state[N][N] = {
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
		int heuristic_value = 0;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (temp[i][j] != goal_state[i][j])
				{
					heuristic_value++;
				}
			}
		}
		cout << "Heuristic Value: " << heuristic_value << endl;
		cout << endl;
		return heuristic_value;
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
		int heuristic_value = calculateHeuristicValue(temp);
		for (int i = 0; i < N; i++)
			delete temp[i];
		delete temp;
		return heuristic_value;
	}

	void HillClimbing(int **state, int former_move, int current_heuristic)
	{
		int child_heuristics[4] = {100, 100, 100, 100};
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (state[i][j] == 0)
				{
					if (i > 0 && former_move != down)
					{
						cout << "Checking child state (moving 0 up) " << endl;
						child_heuristics[0] = generateNextState(state, up);
					}
					if (i < N - 1 && former_move != up)
					{
						cout << "Checking child state (moving 0 down) " << endl;
						child_heuristics[1] = generateNextState(state, down);
					}
					if (j > 0 && former_move != right)
					{
						cout << "Checking child state (moving 0 left) " << endl;
						child_heuristics[2] = generateNextState(state, left);
					}
					if (j < N - 1 && former_move != left)
					{
						cout << "Checking child state (moving 0 right) " << endl;
						child_heuristics[3] = generateNextState(state, right);
					}
				}
			}
			cout << endl;
		}
		int local_optimum = current_heuristic;
		int move = 0;
		for (int i = 0; i < 4; i++)
		{
			if (child_heuristics[i] < local_optimum)
			{
				local_optimum = child_heuristics[i];
				move = i + 1;
				break;
			}
		}
		// move and update state
		makeMove(state, move);
		cout << "Moved to state using Hill Climbing: " << endl;
		printGrid(state);

		// base case
		if (local_optimum == 0)
		{
			cout << "Reached Goal!" << endl;
			return;
		}
		else
			HillClimbing(state, move, local_optimum);
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
		int **initial_state = new int *[N];
		for (int i = 0; i < N; i++)
		{
			initial_state[i] = new int[N];
			for (int j = 0; j < N; j++)
			{
				cin >> initial_state[i][j];
			}
		}

		Solution s = Solution();
		cout << "Initial State: " << endl;
		s.printGrid(initial_state);
		int initial_heuristic = s.calculateHeuristicValue(initial_state);
		s.HillClimbing(initial_state, 0, initial_heuristic);
		cout << "----------------------------------" << endl;
	}
}