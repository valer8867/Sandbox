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
using Coords = std::pair<int, int>;

Coords find_N(const Table& arr, int N) {
    int i = 0;
    int j = 0;
    auto sizeR = arr.size(), sizeC = arr[0].size();
    for (; i < sizeR; ++i) {
        for (j = 0; j < sizeC; ++j)
            if (arr[i][j] == 0) return { i, j };
    }
    return { -1,-1 };
}
std::vector<int> slide_puzzle(const Table& arr) {
    const int ZERO = 0;
    auto sizeR = arr.size(), sizeC = arr[0].size();
    int count_of_numbers = sizeR * sizeC;

    Coords zero = find_N(arr, ZERO);
    Coords curr;
    Coords shouldbe;
    int i, j;
    for (int N = 1; N < count_of_numbers; ++N) {  //move top

        curr = find_N(arr, N);
        i = (N - 1) / sizeR; // should be I
        j = (N - 1) % sizeC; // should be J
        //compare to decide how to move
        if (i < curr.first) {
            while (curr.first != i) {
                //move zero to (curr.i - 1)
                //swap (arr[curr.i][curr.j], arr[curr - 1][curr.j]);
            }
        } 

        if (j < curr.second) { //move right
            while (curr.second != j) {
                //move zero to (curr.j - 1)
                //swap (arr[curr.i][curr.j], arr[curr.i][curr.j - 1]);
            }
        } 
        else if (j > curr.second) { //move left
            while (curr.second != j) {
                //move zero to (curr.j + 1)
                //swap (arr[curr.i][curr.j], arr[curr.i][curr.j + 1]);
            }
        } 
        
    }
    return { 0 };
}



int main() {


    vector<vector<int>> v = { {10, 3, 6, 4},
        { 1, 5, 8, 0},
        { 2,13, 7,15},
        {14, 9,12,11} };
    vector<vector<int>> z = {   {1,  2, 3,  4},
                                {5,  0, 6,  8},
                                {9, 10, 7, 11},
                                {13,14,15, 12} };
    Table h = {
        {4,1,3},
        {2,8,0},
        {7,6,5} };
    //cout << (Stage{ v, { 1, 2 } } == Stage{ z, { 1, 2 } });
    //cout << (z == v);
    //auto x = slide_puzzle(h);

   
    return 0;
    
    
}



