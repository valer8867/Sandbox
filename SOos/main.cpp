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

void printTable(const Table& arr) {
    static int counter = 0;
    cout  << "----------------------------------" << ++counter << "---------------------------------------------" << endl;
    for (auto const& i : arr) {
        for (auto const& j : i) {
            cout << j << "\t";
        }
        cout << endl;
    }
}

Coords find_N(const Table& arr, int N) {
    int i = 0;
    int j = 0;
    auto sizeR = arr.size(), sizeC = arr[0].size();
    for (; i < sizeR; ++i) {
        for (j = 0; j < sizeC; ++j)
            if (arr[i][j] == N) return { i, j };
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
                if (zero.second - 1 == N.second && zero.first == N.first) {
                    if (zero.first != size - 1) {
                        swap(arr[zero.first][zero.second], arr[zero.first + 1][zero.second]);
                        ++zero.first;
                        printTable(arr);
                    }
                    else {
                        swap(arr[zero.first][zero.second], arr[zero.first - 1][zero.second]);
                        --zero.first;
                        printTable(arr);
                    }
                }
                swap(arr[zero.first][zero.second], arr[zero.first][zero.second - 1]);
                --zero.second;
                printTable(arr);

            }
        }
        else if (zero.second < y) { // move right
            while (zero.second != y) {
                if (zero.second + 1 == N.second && zero.first == N.first) {
                    if (zero.first != size - 1) {
                        swap(arr[zero.first][zero.second], arr[zero.first + 1][zero.second]);
                        ++zero.first;
                        printTable(arr);
                    }
                    else {
                        swap(arr[zero.first][zero.second], arr[zero.first - 1][zero.second]);
                        --zero.first;
                        printTable(arr);
                    }
                }
                swap(arr[zero.first][zero.second], arr[zero.first][zero.second + 1]);
                ++zero.second;
                printTable(arr);
            }
        }
        if (zero.first < x) {  // move up or down after right-left
            while (zero.first != x) {
                swap(arr[zero.first][zero.second], arr[zero.first + 1][zero.second]);
                ++zero.first;
                printTable(arr);
            }
        }
        else if (zero.first > x) {
            while (zero.first != x) {
                swap(arr[zero.first][zero.second], arr[zero.first - 1][zero.second]);
                --zero.first;
                printTable(arr);
            }

        }
    }
    ////////////////////////////  better as second function  ////////////////////////////////////
    else {

        if (zero.first > x) { // move up
            if ((zero.second == y - 1)&& (zero.first != size - 1)) {  // cant move top, when there are sorted parts, so go other side: down, right == under N
                swap(arr[zero.first][zero.second], arr[zero.first + 1][zero.second]);
                ++zero.first;
                printTable(arr);
                swap(arr[zero.first][zero.second], arr[zero.first][zero.second + 1]);
                ++zero.second;
                printTable(arr);
            }
            while (zero.first != x) {
                if (zero.first - 1 == N.first && zero.second == N.second) {
                    if (zero.second != size - 1) {
                        swap(arr[zero.first][zero.second], arr[zero.first][zero.second + 1]);
                        ++zero.second;
                        printTable(arr);
                    }
                    else {
                        swap(arr[zero.first][zero.second], arr[zero.first][zero.second - 1]);
                        --zero.second;
                        printTable(arr);
                    }
                }
                swap(arr[zero.first][zero.second], arr[zero.first - 1][zero.second]);
                --zero.first;
                printTable(arr);

            }
        }
        else if (zero.first < x) { // move down !!!!!!!!!!!! unchecked
            /*if ((zero.second == y - 1) && (zero.first != size - 1)) {  // cant move top, when there are sorted parts, so go other side: down, right == under N
                swap(arr[zero.first][zero.second], arr[zero.first + 1][zero.second]);
                ++zero.first;
                printTable(arr);
                swap(arr[zero.first][zero.second], arr[zero.first][zero.second + 1]);
                ++zero.second;
                printTable(arr);
            }*/
            while (zero.first != x) {
                if (zero.first + 1 == N.first) {
                    if (zero.second != size - 1) {
                        swap(arr[zero.first][zero.second], arr[zero.first][zero.second + 1]);
                        ++zero.second;
                        printTable(arr);
                    }
                    else {
                        swap(arr[zero.first][zero.second], arr[zero.first][zero.second - 1]);
                        --zero.second;
                        printTable(arr);
                    }
                }
                swap(arr[zero.first][zero.second], arr[zero.first + 1][zero.second]);
                ++zero.first;
                printTable(arr);

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
            printTable(arr);

        }
    }
}

std::vector<int> slide_puzzle(Table arr) {
    const int ZERO = 0;
    auto sizeR = arr.size(), sizeC = arr[0].size();
    int count_of_numbers = sizeR * sizeC;
    Coords curr;
    int i, j;

    int mid = count_of_numbers - 2 * sizeR;
    int end = count_of_numbers - 2;
    for (int N = 1, counter = 1; counter <= end ; ++counter) {  //exept 2 last rows
        cout << N;
        i = (N - 1) / sizeR; // should be I
        j = (N - 1) % sizeC; // should be J


        if (counter <= mid) {
            if (j == sizeC - 2) curr = find_N(arr, N + 1);
            else if (j == sizeC - 1) curr = find_N(arr, N - 1);
            else curr = find_N(arr, N);
            ++N;
        }
        else {
            if (i == sizeC - 2) {
                curr = find_N(arr, N + sizeR);
                N += sizeR;
            }
            else if (i == sizeC - 1) {
                curr = find_N(arr, N - sizeR);
                N -= sizeR;
                ++N;
            }
        }

        if (curr.second > j) { //move left
            while (curr.second != j) {
                //move zero to (curr.j - 1)
                move_Zero(arr, sizeR, { curr.first, curr.second }, curr.first, curr.second - 1);
                swap (arr[curr.first][curr.second], arr[curr.first][curr.second - 1]);
                --curr.second;
                printTable(arr);
            }
        }
        else if (curr.second < j) { //move right
            while (curr.second != j) {
                //move zero to (curr.j + 1)
                //swap (arr[curr.i][curr.j], arr[curr.i][curr.j + 1]);
                move_Zero(arr, sizeR, { curr.first, curr.second }, curr.first, curr.second + 1);
                swap(arr[curr.first][curr.second], arr[curr.first][curr.second + 1]);
                ++curr.second;
                printTable(arr);
            }
        }
        if (curr.first > i) { //move up
            while (curr.first != i) {
                //move zero to (curr.i - 1)
                //swap (arr[curr.i][curr.j], arr[curr - 1][curr.j]);
                move_Zero(arr, sizeR, { curr.first, curr.second }, curr.first - 1, curr.second);
                swap(arr[curr.first][curr.second], arr[curr.first - 1][curr.second]);
                --curr.first;
                printTable(arr);
            }
            
        } 
        if (j == sizeR - 1) {
            //rotate 
            swap(arr[i][j], arr[i + 1][j]);
            swap(arr[i][j], arr[i][j - 1]);
            swap(arr[i][j - 1], arr[i + 1][j - 1]);
            swap(arr[i + 1][j - 1], arr[i + 1][j]);

            swap(arr[i][j], arr[i + 1][j]);
            swap(arr[i][j], arr[i][j - 1]);
            swap(arr[i][j - 1], arr[i + 1][j - 1]);
            printTable(arr);
        }
    }

    

        
    if (arr[sizeC - 1][sizeR - 1] == sizeR * (sizeC - 1)) {
        swap(arr[sizeC - 1][sizeR - 1], arr[sizeC - 2][sizeR - 1]);
        printTable(arr);
        return { 1 };
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
    vector<vector<int>> sp = {   {18,  8, 25,  3,  1,  9},
                                 {4 ,  5, 15, 27, 29,  6},
                                 {10, 23, 22,  2, 28, 26},
                                 {21, 16, 13, 20, 19, 14},
                                 {24, 12, 17,  7, 11,  0} };

    vector<vector<int>> s55 = {  { 4, 23, 17, 12,  3},
                                 {21, 14, 13,  8, 19},
                                 { 9, 11, 15,  2,  5},
                                 {20,  1, 16, 24, 10},
                                 { 6, 22, 18,  7,  0} };
    Table h = {
        {4,1,3},
        {2,8,0},
        {7,6,5} };
    
    auto x = slide_puzzle(s55);

   
    return 0;
    
    
}



