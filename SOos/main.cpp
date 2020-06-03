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
    template <class T1, class T2>
    std::size_t operator () (std::pair<T1, T2> const& pair) const {
        return std::hash<T1>()(pair.first);
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



