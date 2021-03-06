#include"stdafx.h"
#include<iostream>
#include<fstream>
#include<random>
#include<ctime>
#include<Windows.h>
using namespace std;

int sortfew(float* a, int m, int n) {
	float min;
	int mark = 0;
	for (int k = 0; k < (n - m); k++) {
		min = INT_MAX;
		for (int i = m + k; i < n; i++) {
			if (a[i] < min) {
				min = a[i];
				mark = i;
			}
		}
		a[mark] = a[m + k];
		a[m + k] = min;
	}
	return m + (n - m + 1) / 2;
}

int sortbylabel(float* a, int label, int s, int n) {
	float tem = a[label];
	int mark = label;
	int flag = 0;
	int record = 0;
	for (int i = s, j = n - 1; i != j;) {
		if (flag == 0) {
			if (i >= mark) {
				flag = 1;
				continue;
			}
			if (a[i] <= tem) {
				i++;
			}
			else {
				a[mark] = a[i];
				mark = i;
				flag = 1;
			}
		}
		else {
			if (j <= mark) {
				flag = 0;
				continue;
			}
			if (a[j] >= tem) {
				j--;
			}
			else {
				a[mark] = a[j];
				mark = j;
				flag = 0;
			}
		}
	}
	a[mark] = tem;
	return mark;
}

int searchlabel(float* a, int s, int n/*总数*/, int k) {
	int n_label = n - 1;
	if (n - s <= 5) {
		sortfew(a, s, n);
		return s + k - 1;
	}
	int i = (n - s) / 5;
	for (int j = 0; j <= i; j++) {
		int t;
		if (s + j * 5 + 4 < n) {
			t = sortfew(a, s + j * 5, s + j * 5 + 4);
		}
		else {
			t = sortfew(a, s + j * 5, n - 1);
		}
		float temp = a[s + j];
		a[s + j] = a[t];
		a[t] = temp;
	}
	int r = (i + 3) / 2;
	Sleep(1);
	int t = searchlabel(a, s, s + i + 1, r);
	int label = sortbylabel(a, t, s, n);
	if (label == k - 1) {
		return label;
	}
	else if (label > k - 1) {
		return searchlabel(a, s, label, k);
	}
	else {
		return searchlabel(a, label + 1, n, k - label - 1);
	}
}

int main() {
	{
		std::ofstream fout("data");
		int T = 100;
		fout << T << endl;
		srand(time(0));
		int a;
		for (int i = 0; i < T; i++) {
			a = rand() % (200000);
			fout << a << endl;
			for (int j = 0; j < a; j++) {
				int b = rand() % 400000;
				fout << b << ' ';
			}
			fout << endl;
		}
		fout.close();
	}
	{
		ifstream fin("data");
		ofstream fout("res.txt");
		int T = 0;
		fin >> T;
		for (int i = 0; i < T; i++) {
			int n;
			fin >> n;
			float *a = new float[n];
			for (int m = 0; m < n; m++) {
				fin >> a[m];
			}
			int m = (n + 1) / 2;
			if (n % 2 == 1) {
				double t0 = clock();
				int ww = searchlabel(a, 0, n, m);
				double t1 = clock();
				fout << i << ' ' << n << ' ' << t1 - t0 << ' ' << a[ww] << endl;
			}
			else {
				double t0 = clock();
				double w = (a[searchlabel(a, 0, n, m)] + a[searchlabel(a, 0, n, m + 1)]) / 2;
				double t1 = clock();
				fout << i << ' ' << n << ' ' << t1 - t0 << ' ' << w << endl;
			}
		}
		fin.close();
		fout.close();
	}
	return 0;
}