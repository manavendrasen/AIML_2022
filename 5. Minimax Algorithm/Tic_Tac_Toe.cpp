#include <bits/stdc++.h>
using namespace std;

#define X_WIN +1
#define O_WIN -1
#define X 'X'
#define O 'O'
#define BLANK '_'

class Board
{
private:
	vector<vector<char>> board;

public:
	Board()
	{
		board.resize(3);
		for (int i = 0; i < 3; i++)
		{
			board[i].resize(3);
			for (int j = 0; j < 3; j++)
				board[i][j] = BLANK;
		}
	}

	Board(vector<vector<char>> &board)
	{
		this->board = board;
	}

	void makeMove(int row, int col, char player)
	{
		board.at(row).at(col) = player;
	}

	bool isMoveLeft()
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (board.at(i).at(j) == BLANK)
					return true;
		return false;
	}

	int calculateScore()
	{
		// Checking for Rows for X or O victory.
		for (int row = 0; row < 3; row++)
		{
			if (board.at(row).at(0) == board.at(row).at(1) &&
					board.at(row).at(1) == board.at(row).at(2))
			{
				if (board.at(row).at(0) == X)
					return X_WIN;
				else if (board.at(row).at(0) == O)
					return O_WIN;
			}
		}

		// Checking for Columns for X or O victory.
		for (int col = 0; col < 3; col++)
		{
			if (board.at(0).at(col) == board.at(1).at(col) &&
					board.at(1).at(col) == board.at(2).at(col))
			{
				if (board.at(0).at(col) == X)
					return X_WIN;
				else if (board.at(0).at(col) == O)
					return O_WIN;
			}
		}

		// Checking for Diagonals for X or O victory.
		if (board.at(0).at(0) == board.at(1).at(1) &&
				board.at(1).at(1) == board.at(2).at(2))
		{
			if (board.at(0).at(0) == X)
				return X_WIN;
			else if (board.at(0).at(0) == O)
				return O_WIN;
		}

		if (board.at(0).at(2) == board.at(1).at(1) &&
				board.at(1).at(1) == board.at(2).at(0))
		{
			if (board.at(0).at(2) == X)
				return X_WIN;
			else if (board.at(0).at(2) == O)
				return O_WIN;
		}

		return 0;
	}

	int minimax(char player)
	{
		int score = calculateScore();
		if (score == X_WIN || score == O_WIN)
			return score;

		else if (!isMoveLeft())
			return 0;

		if (player == X)
		{
			int best = -1000;
			for (int row = 0; row < 3; row++)
				for (int col = 0; col < 3; col++)
					if (board.at(row).at(col) == BLANK)
					{
						makeMove(row, col, player);
						best = max(best, minimax(O));
						board.at(row).at(col) = BLANK;
					}
			return best;
		}
		else
		{
			int best = 1000;
			for (int row = 0; row < 3; row++)
				for (int col = 0; col < 3; col++)
					if (board.at(row).at(col) == BLANK)
					{
						makeMove(row, col, player);
						best = min(best, minimax(X));
						board.at(row).at(col) = BLANK;
					}
			return best;
		}
	}

	pair<int, int> findBestMove()
	{
		int best_score = -1000;
		pair<int, int> best_move = make_pair(-1, -1);

		// Traverse all cells, evaluate minimax function for
		// all empty cells. And return the cell with optimal
		// value.

		for (int row = 0; row < 3; row++)
			for (int col = 0; col < 3; col++)
				if (board.at(row).at(col) == BLANK)
				{
					makeMove(row, col, X);
					int score = minimax(O);

					// reset board
					board.at(row).at(col) = BLANK;

					if (score > best_score)
					{
						best_score = score;
						best_move = make_pair(row, col);
					}
				}
		return best_move;
	}
};

int main()
{
	vector<vector<char>> input_board =
			{
					{'X', '_', 'O'},
					{'_', 'O', '_'},
					{'_', '_', 'X'}};

	Board board(input_board);

	pair<int, int> move = board.findBestMove();
	cout << "Best Move: " << move.first << " " << move.second << endl;

	return 0;
}