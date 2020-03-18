#include "functions.h"
#include <algorithm>
#include <vector>
using namespace std;

// split into n/5 groups of 5 and find median of each group
// find the median of medians recursively
int findMedOfMeds(vector<int>& inp, int l, int r) {
	if (inp.size() == 1) return inp[0];

	vector<int> aux;
	vector<int> out;
	int j = 0; 
	for (int i = l; i <= r; i += 5) {
		j = i;
		// add the next five elements to aux 
		while (j <= r && j < i + 5) {
			aux.push_back(inp[j]);
			++j;
		}

		sort(aux.begin(), aux.end()); // sort the <=5 element array
		out.push_back(aux[aux.size() / 2]); // store the median
		aux.clear(); // clear the aux array
	}

	return findMedOfMeds(out, 0, out.size() - 1); // recurse to find medOfMeds
}

// compute rank of median of medians (index where it would belong)
int rankOf(vector<int>& inp, int medOfMeds, int l, int r) {
	int rank = -1;
	for (int i = l; i <= r; ++i) {
		if (inp[i] <= medOfMeds) rank += 1;
	}
	return rank;
}

// partition using median of medians (assuming no duplicates)
int myPartition(vector<int>& v, int medOfMeds, int l, int r) {
	/* medOfMeds used as pivot, places pivot
	at correct position in sorted array-
	<= pivot on the left, >= pivot on the right */

	int i = l; // index of smaller element

	for (int j = l; j <= r; ++j) {
		if (v[j] <= medOfMeds) {
			swap(v[i], v[j]);
			++i;
		}
	}
	
	// final swap to put pivot in correct position
	auto it = find(v.begin(), v.end(), medOfMeds);
	int medianInd = distance(v.begin(), it);
	swap(v[i - 1], v[medianInd]);

	return i - 1;
}

// rank-finding determinstic selection in O(n) time
int deterministicSelect(vector<int>& inp, int rank, int l, int r) {
	int x = findMedOfMeds(inp, l , r); // recursively compute median of medians
	int p = rankOf(inp, x, l, r); // compute rank of median of medians

	// found the rank we wanted, return the element of that rank
	if (p == rank) return x;
	else {
		int pI = myPartition(inp, x, l, r); // otherwise, partition using x

		// rank we found was greater, recurse on left portion of pivot
		if (p > rank) {
			return deterministicSelect(inp, rank, l, pI - 1);
		}
		// rank we found was lower, recurse on right portion of pivot
		else {
			return deterministicSelect(inp, rank - p - 1, pI + 1, r);
		}
	}
}