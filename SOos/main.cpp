#include <string>
#include <iostream>
#include <thread>
#include <vector>
#include <numeric>
#include <algorithm>
#include <unordered_set>

using namespace std;
using Line = std::vector<int>;
using Table = std::vector<Line>;
using Stage = std::tuple<Table, std::pair<int, int>, Line>;


std::vector<int> slide_puzzle(const Table& arr) {
    //// find zero coords
    int i = 0;
    int j = 0;
    auto sizeR = arr.size(), sizeC = arr[0].size();
    for (; i < sizeR; ++i) {
        for (j = 0; j < sizeC; ++j)
            if (arr[i][j] == 0) goto endLoop;
    }
    endLoop:
    ///// create answer
    auto answer = Table(sizeR, vector<int>(sizeC, 0));
    size_t counter = 1;
    for (auto& i : answer) {
        for (auto& j : i) {
            j = counter++;
        }
    }
    answer.back().back() = 0;
    /////
    vector<Stage> stages;
    stages.push_back({ arr, {i,j}, {} });
    Table tmp;
    for (int k = 0; k < stages.size(); ++k) {
        auto stage = stages[k];
        if (std::get<0>(stage) == answer) 
            return get<2>(stage);

        int x = get<1>(stage).first;
        int y = get<1>(stage).second;
        if (x > 0) {
            tmp = std::get<0>(stage);
            std::swap(tmp[x][y], tmp[x - 1][y]);
            if (find_if(stages.begin(), stages.end(), [&tmp](auto const& item) { return tmp == get<0>(item); }) == stages.end()) {
                vector<int> path = get<2>(stage);
                path.push_back(tmp[x][y]);
                stages.push_back({ tmp, {x - 1, y}, path });
            }
        }
        if (x < sizeR - 1) {
            tmp = std::get<0>(stage);
            std::swap(tmp[x][y], tmp[x + 1][y]);
            if (find_if(stages.begin(), stages.end(), [&tmp](auto const& item) { return tmp == get<0>(item); }) == stages.end()) {
                vector<int> path = get<2>(stage);
                path.push_back(tmp[x][y]);
                stages.push_back({ tmp, {x + 1, y}, path });
            }
        }
        if (y > 0) {
            tmp = std::get<0>(stage);
            std::swap(tmp[x][y], tmp[x][y - 1]);
            if (find_if(stages.begin(), stages.end(), [&tmp](auto const& item) { return tmp == get<0>(item); }) == stages.end()) {
                vector<int> path = get<2>(stage);
                path.push_back(tmp[x][y]);
                stages.push_back({ tmp, {x, y - 1}, path });
            }
        }
        if (y < sizeC - 1) {
            tmp = std::get<0>(stage);
            std::swap(tmp[x][y], tmp[x][y + 1]);
            if (find_if(stages.begin(), stages.end(), [&tmp](auto const& item) { return tmp == get<0>(item); }) == stages.end()) {
                vector<int> path = get<2>(stage);
                path.push_back(tmp[x][y]);
                stages.push_back({ tmp, {x, y + 1}, path });
            }
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
    auto x = slide_puzzle(v);
    return 0;
    
    
}



