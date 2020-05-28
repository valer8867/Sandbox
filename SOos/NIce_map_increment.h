#include <iostream>
#include <map>
#include <vector>
#include <algorithm> 
#include <iomanip>
#include <string>
using namespace std;

void foo() {
	vector<string>sts = { "asdsad","asd","asd","bv","bv","cbg","cgb", "cgb" };
	map<string, int> m;
	for (auto& i : sts) {
		++m[i];
	}
	for (auto& i : m) {
		cout << i.first << "\t" << i.second << endl;
	}
}