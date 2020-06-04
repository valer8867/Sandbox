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

void move_Zero(Table& arr, const int size, Coords const& N, int x, int y) { // size for n*n table, should use second size for m*n
    auto zero = find_N(arr, 0);
    // 1. for moving right to ot left to N, use left-right first, then use top
    // 2 .for moveing top to N, use top-down first, then left-right
    // so first is to check case 1 or 2
    bool version = (x == N.first? 0 : 1);
    
    if (version == 0) {  //  -N-
        if (zero.second > y) { // move left
            while (zero.second != y) {
                if (zero.second - 1 == N.second) {
                    if (zero.first != size - 1) {
                        swap(arr[zero.first][zero.second], arr[zero.first + 1][zero.second]);
                        ++zero.first;
                    }
                    else {
                        swap(arr[zero.first][zero.second], arr[zero.first - 1][zero.second]);
                        --zero.first;
                    }
                }
                swap(arr[zero.first][zero.second], arr[zero.first][zero.second - 1]);
                --zero.second;
            }
        }
        else if (zero.second < y) { // move right
            while (zero.second != y) {
                if (zero.second + 1 == N.second) {
                    if (zero.first != size - 1) {
                        swap(arr[zero.first][zero.second], arr[zero.first + 1][zero.second]);
                        ++zero.first;
                    }
                    else {
                        swap(arr[zero.first][zero.second], arr[zero.first - 1][zero.second]);
                        --zero.first;
                    }
                }
                swap(arr[zero.first][zero.second], arr[zero.first][zero.second + 1]);
                ++zero.second;
            }
        }
        if (zero.first < x) {  // move up or down after right-left
            while (zero.first != x) {
                swap(arr[zero.first][zero.second], arr[zero.first + 1][zero.second]);
                ++zero.first;
            }
        }
        else if (zero.first > x) {
            while (zero.first != x) {
                swap(arr[zero.first][zero.second], arr[zero.first - 1][zero.second]);
                --zero.first;
            }
        }
    }
    ////////////////////////////  better as second function  ////////////////////////////////////
    else {

        if (zero.first > x) { // move up
            if ((zero.second == y - 1)&& (zero.first != size - 1)) {  // cant move top, when there are sorted parts, so go other side: down, right == under N
                swap(arr[zero.first][zero.second], arr[zero.first + 1][zero.second]);
                ++zero.first;
                swap(arr[zero.first][zero.second], arr[zero.first][zero.second + 1]);
                ++zero.second;
            }
            while (zero.first != x) {
                if (zero.first - 1 == N.first) {
                    if (zero.second != size - 1) {
                        swap(arr[zero.first][zero.second], arr[zero.first][zero.second + 1]);
                        ++zero.second;
                    }
                    else {
                        swap(arr[zero.first][zero.second], arr[zero.first][zero.second - 1]);
                        --zero.second;
                    }
                }
                swap(arr[zero.first][zero.second], arr[zero.first - 1][zero.second]);
                --zero.first;
            }
        }
        else if (zero.first < x) { // move down !!!!!!!!!!!! unchecked
            /*if ((zero.second == y - 1) && (zero.first != size - 1)) {  // cant move top, when there are sorted parts, so go other side: down, right == under N
                swap(arr[zero.first][zero.second], arr[zero.first + 1][zero.second]);
                ++zero.first;
                swap(arr[zero.first][zero.second], arr[zero.first][zero.second + 1]);
                ++zero.second;
            }*/
            while (zero.first != x) {
                if (zero.first + 1 == N.first) {
                    if (zero.second != size - 1) {
                        swap(arr[zero.first][zero.second], arr[zero.first][zero.second + 1]);
                        ++zero.second;
                    }
                    else {
                        swap(arr[zero.first][zero.second], arr[zero.first][zero.second - 1]);
                        --zero.second;
                    }
                }
                swap(arr[zero.first][zero.second], arr[zero.first + 1][zero.second]);
                ++zero.first;
            }
        }

        while (zero.second != y) {
            if (zero.second < y) {  // move up or down after right-left
                swap(arr[zero.first][zero.second], arr[zero.first][zero.second + 1]);
                ++zero.second;
            }
            else if (zero.second > y) {
                swap(arr[zero.first][zero.second], arr[zero.first][zero.second - 1]);
                --zero.second;
            }
        }
    }

    /*while (zero.first != x) {
        if (zero.first - 1 == N.first) {

        }
        swap(arr[zero.first][zero.second], arr[zero.first - 1][zero.second]);
        --zero.first;
    }*/


}
std::vector<int> slide_puzzle(Table arr) {
    const int ZERO = 0;
    auto sizeR = arr.size(), sizeC = arr[0].size();
    int count_of_numbers = sizeR * sizeC;

    Coords zero = find_N(arr, ZERO);
    Coords curr;
    Coords shouldbe;
    int i, j;
    for (int N = 1; N <= count_of_numbers - 2 * sizeR; ++N) {  //exept 2 last rows
        i = (N - 1) / sizeR; // should be I
        j = (N - 1) % sizeC; // should be J

        if (i == sizeR - 2) curr = find_N(arr, N + 1);
        else if (i == sizeR - 1) curr == find_N(arr, N - 1);
        else curr == find_N(arr, N);

        //compare to decide how to move

        ////////////////////////////////////////////////
        if (curr.second > j) { //move left
            while (curr.second != j) {
                //move zero to (curr.j - 1)
                move_Zero(arr, sizeR, { curr.first, curr.second }, curr.first, curr.second - 1);
                swap (arr[curr.first][curr.first], arr[curr.first][curr.second - 1]);
                --curr.second;
            }
        }
        else if (curr.second < j) { //move right
            while (curr.second != j) {
                //move zero to (curr.j + 1)
                //swap (arr[curr.i][curr.j], arr[curr.i][curr.j + 1]);
                move_Zero(arr, sizeR, { curr.first, curr.second }, zero.first, zero.second + 1);
                swap(arr[curr.first][curr.first], arr[curr.first][curr.second + 1]);
                ++curr.second;
            }
        }
        if (curr.first > i) { //move up
            while (curr.first != i) {
                //move zero to (curr.i - 1)
                //swap (arr[curr.i][curr.j], arr[curr - 1][curr.j]);
                move_Zero(arr, sizeR, { curr.first, curr.second }, zero.first - 1, zero.second);
                swap(arr[curr.first][curr.first], arr[curr.first - 1][curr.second]);
                --curr.first;
            }
            if (i == sizeR - 1) {
                swap(arr[zero.first][zero.second], arr[zero.first][zero.second + 1]);
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



