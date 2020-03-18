#ifndef FUNCTIONS
#define FUNCTIONS

#include <algorithm>
#include <vector>

// split into n/5 groups of 5 and find median of each group
// find the median of medians recursively
int findMedOfMeds(std::vector<int>& inp, int l, int r);

// compute rank of median of medians
int rankOf(std::vector<int>& inp, int medOfMeds, int l, int r);

// partition using median of medians
int myPartition(std::vector<int>& v, int medOfMeds, int l, int r);

// rank-finding determinstic selection in O(n) time
int deterministicSelect(std::vector<int>& inp, int rank, int l, int r);

#endif