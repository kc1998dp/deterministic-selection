#include "functions.h"
#include <algorithm>
#include <chrono>
#include <iostream>
using namespace std;
using namespace chrono;

bool verifyRank(vector<int>& inp, int x, int rank) {
	sort(inp.begin(), inp.end());
	if (inp[rank] == x) return true;
	return false;
}


int main() {
	vector<int> arr;
	for (int i = 0; i < 1000; ++i) arr.push_back(i);
	random_shuffle(arr.begin(), arr.end()); // randomize the array

	auto start = chrono::high_resolution_clock::now(); // start timer
	int x = deterministicSelect(arr, 499, 0, 999); // run selection
	auto stop = high_resolution_clock::now(); // stop timer
	auto elapsed = duration_cast<milliseconds>(stop - start);

	cout << "time elapsed: " << elapsed.count() << " ms" << endl;
	cout << boolalpha << verifyRank(arr, x, 499); // verify correctness
}