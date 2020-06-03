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

std::vector<int> slide_puzzle(const Table& arr) {
    int i = 0;
    int j = 0;
    auto sizeR = arr.size(), sizeC = arr[0].size();
    for (; i < sizeR; ++i) {
        for (j = 0; j < sizeC; ++j)
            if (arr[i][j] == 0) goto endLoop;
    }
endLoop:
    /////
    auto answer = Table(sizeR, vector<int>(sizeC, 0));
    size_t counter = 1;
    for (auto& i : answer) {
        for (auto& j : i) {
            j = counter++;
        }
    }
    answer.back().back() = 0;
    /////
    unordered_set<Stage, stage_hash> tables_coords;
    tables_coords.insert({ arr, {i, j} });
    Table tmp;
    for (auto const& table_coord : tables_coords) {
        if (table_coord.first == answer) return { 1,1,1 };
        int x = table_coord.second.first;
        int y = table_coord.second.second;
        if (x > 0) {
            tmp = table_coord.first;
            std::swap(tmp[x][y], tmp[x - 1][y]);

            tables_coords.insert({ tmp, {i - 1, j} });
        }
        if (x < sizeR - 1) {

        }
        if (y > 0) {

        }
        if (y < sizeC) {

        }

    }
    return {0,0,0};
}



int main() {


    vector<vector<int>> v = { { 4,1,3 },
                            { 2,8,0 },
                            { 7,6,5 } };
    vector<vector<int>> z = { { 4,1,3 },
                            { 2,8,0 },
                            { 7,6,5 } };
    //cout << (Stage{ v, { 1, 2 } } == Stage{ z, { 1, 2 } });
    //cout << (z == v);
    slide_puzzle(v);
    
    
}



