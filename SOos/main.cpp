#include <string>
#include <iostream>
#include <thread>
#include <vector>
#include <numeric>
#include <algorithm>
#include <unordered_set>

using namespace std;
using Table = std::vector<std::vector<int>>;

std::vector<int> slide_puzzle(const Table& arr)
{
    unordered_set<Table> tables;
    tables.insert(arr);
    for (auto& table : tables) {

    }
    return std::vector<int>();
}



int main() {


    vector<vector<int>> v = { { 4,1,3 },
                            { 2,8,0 },
                            { 7,6,5 } };
    
    
}



