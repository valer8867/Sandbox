#pragma once
#include <iostream>
void sortt(int mass[], int left, int right) {
	using namespace std;
	if (right - left < 1) return;
	int pivot = mass[left];
	int m = left + 1, n = right;
	while (1) {
		while (mass[m] < pivot && m != n) m++;
		if (m == n) {
			if (mass[m] < pivot) {
				swap(mass[m], mass[left]);
				break;
			}
			else {
				swap(mass[--m], mass[left]);
				break;
			}
		}
		while (mass[n] > pivot&& m != n) n--;
		if (m == n) {
			if (mass[m] > pivot) {
				swap(mass[m - 1], mass[left]);
				--m;
				break;
			}
			else {
				swap(mass[m], mass[left]);
				m--;
				n++;
				break;
			}
		}
		swap(mass[m], mass[n]);
	}
	for (int i = 0; i < 33; ++i) cout << mass[i] << ' ';
	cout << endl;
	//Sleep(100);
	sortt(mass, left, m);
	sortt(mass, n, right);

}