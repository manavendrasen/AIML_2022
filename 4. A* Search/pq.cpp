// C++ program to create a priority queue of pairs.
// By default a max heap is created ordered
// by first element of pair.
#include <bits/stdc++.h>

using namespace std;

// Driver program to test methods of graph class
int main()
{
	// By default a max heap is created ordered
	// by first element of pair.
	auto comparator = [](const pair<int, int> &a, const pair<int, int> &b)
	{
		return a.second > b.second;
	};
	priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comparator)> pq(comparator);

	pq.push(make_pair(10, 200));
	pq.push(make_pair(20, 100));
	pq.push(make_pair(15, 400));
	pq.push(make_pair(10, 200));

	while (!pq.empty())
	{
		cout << pq.top().first << " " << pq.top().second << endl;
		pq.pop();
	}

	return 0;
}
