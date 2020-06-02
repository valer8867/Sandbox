#include <string>
#include <iostream>
#include <thread>
#include <vector>
#include <numeric>
#include <algorithm>
#include <string_view>

using namespace std;

//string integer_square_root(string n) {
//    auto size = n.size();
//    if (size < 10) return to_string(sqrt(stoi(n)));
//
//    string res;
//    string ost(size / 2, '0');
//    auto i = n.begin();
//    if (n.size() % 2 == 1) {
//        ost(*i);
//        ++i;
//    }
//    else {
//        ost.push_back(*i++);
//        ost.push_back(*i++);
//    }
//    res += to_string(sqrt(stoi(ost)));
//
//
//
//    return "";
//}


string multiply(string num1, string num2);
std::string sum_strings(const std::string& a, const std::string& b);
string divide_strings(string a, string b);



string floorSqrt(string x)
{
    if (x == "0" || x == "1")
        return x;

    // Staring from 1, try all numbers until 
    // i*i is greater than or equal to x. 
    string start = "1", end = x, ans;
    while (start <= end)
    {
        string mid = (start + end) / 2;

        // If x is a perfect square 
        if (mid * mid == x)
            return mid;

        if (mid * mid < x)
        {
            start = mid + 1;
            ans = mid;
        }
        else 
            end = mid - 1;
    }
    return ans;
}




int main() {
   

    
}





std::string sum_strings(const std::string& a, const std::string& b) {
    std::string res;
    int extra = 0;
    int ai = 0, bj = 0;
    auto i = a.rbegin(), j = b.rbegin();
    for (int curr; i != a.rend() || j != b.rend(); ) {
        if (i != a.rend()) {
            ai = *i - '0';
            ++i;
        }
        else ai = 0;
        if (j != b.rend()) {
            bj = *j - '0';
            ++j;
        }
        else bj = 0;
        curr = ai + bj + extra;
        if (curr > 9) {
            curr -= 10;
            extra = 1;
        }
        else extra = 0;
        res.push_back(curr + '0');
    }
    if (extra) res.push_back('1');
    std::reverse(res.begin(), res.end());
    return res;
}


bool more_or_equal(const string& a, int current, int last, const string& b) {
    for (int i = 0; current <= last; ++current, ++i) {
        if (a[current] > b[i]) return true;
        if (a[current] < b[i]) return false;
    }
    return true;
}

void substract(string& a, int left, int i, const string& b) {
    for (int j = b.size() - 1; i >= left; --i, --j) {
        if (a[i] >= b[j]) a[i] -= b[j] - '0';
        else {
            a[i] -= b[j] - 10 - '0';
            --a[i - 1];
        }
    }
}

string divide(int extra, string& a, int left, int right, const string& b) {
    string res = "0";
    while (extra > 0 || more_or_equal(a, left, right, b)) {
        substract(a, left, right, b);
        ++res[0];
        if (left > 0) extra = a[left - 1] - '0';
        else extra = 0;
    }
    return res;
}

string multiply(string num1, string num2) {
    int len1 = num1.size();
    int len2 = num2.size();
    if (len1 == 0 || len2 == 0) return "0";
    vector<int> result(len1 + len2, 0);
    int i_n1 = 0;
    int i_n2 = 0;
    for (int i = len1 - 1; i >= 0; i--) {
        int carry = 0;
        int n1 = num1[i] - '0';
        i_n2 = 0;
        for (int j = len2 - 1; j >= 0; j--) {
            int n2 = num2[j] - '0';
            int sum = n1 * n2 + result[i_n1 + i_n2] + carry;
            carry = sum / 10;
            result[i_n1 + i_n2] = sum % 10;
            i_n2++;
        }
        if (carry > 0)
            result[i_n1 + i_n2] += carry;
        i_n1++;
    }
    int i = result.size() - 1;
    while (i >= 0 && result[i] == 0) --i;
    if (i == -1)
        return "0";
    string s;
    while (i >= 0) s += std::to_string(result[i--]);
    return s;
}

string divide_strings(string a, string b) {
    if (a.size() < b.size()) return "0";
    string quotient;
    int extra = 0;
    for (size_t i = 0, j = b.size() - 1; j < a.size(); ++i, ++j) {
        if (extra || more_or_equal(a, i, j, b)) quotient += divide(extra, a, i, j, b);
        else quotient += "0";
        extra = a[i] - '0';
    }
    auto remainder = string(a.end() - b.size(), a.end());
    remainder.erase(0, remainder.find_first_not_of('0', 0));
    quotient.erase(0, quotient.find_first_not_of('0', 0));
    if (quotient == "") quotient += "0";
    if (remainder == "") remainder += "0";
    return  quotient;
}