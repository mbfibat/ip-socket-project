#ifndef RANDOM_H
#define RANDOM_H

#include <algorithm>
#include <random>
#include <unordered_set>
#include <vector>

extern std::vector<int> pick(int N, int k);
extern std::unordered_set<int> pickSet(int N, int k, std::mt19937 &rng);

#endif  // RANDOM_H