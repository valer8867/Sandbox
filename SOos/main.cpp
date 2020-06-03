#include <string>
#include <iostream>
#include <thread>
#include <vector>
#include <numeric>
#include <algorithm>
#include <unordered_set>

using namespace std;
using Table = std::vector<std::vector<int>>;
using Stage = std::pair<Table, std::pair<int, int>>;


struct stage_hash
{
    template <class table, class coords>
    std::size_t operator () (std::pair<table, coords> const& pair) const {
        size_t hsh = 0;
        for (auto& i : pair.first) {
            for (auto j : i) {
                hsh ^= std::hash<int>()(j);
            }
        }
        return hsh;
    }
};

std::vector<int> slide_puzzle(const Table& arr)
{
    int i = 0;
    int j = 0;
    for (auto sizeR = arr.size(), sizeC = arr[0].size(); i < sizeR; ++i) {
        for (; j < sizeC; ++j)
            if (arr[i][j] == 0) goto endLoop;
    }
endLoop:
    
    unordered_set<Stage, stage_hash> tables;
    tables.insert({ arr, {i, j} });

    for (auto& table : tables) {
        //move_one();

    }
    return std::vector<int>();
}



int main() {


    vector<vector<int>> v = { { 4,1,3 },
                            { 2,8,0 },
                            { 7,6,5 } };
    
    
}



