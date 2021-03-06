#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
using namespace std;


void Select(int n, int c, ofstream &fout, int *weight, int *value, int*bag) {
	for (int i = 1; i < n; i++)
	{
		for (int j = c; j >= weight[i]; j--)
		{
			if (bag[j - weight[i]] + value[i] > bag[j])
				bag[j] = bag[j - weight[i]] + value[i];
		}
	}
	fout << n << " : " << c << " : " << bag[c] << ":";
}


int main()
{
	{
		ofstream fout("data");
		int T = 100;
		fout << T << endl;
		srand(time(0));
		for (int i = 0; i < T; i++) {
			int a = rand() % 3000 + 1;
			fout << a << ' ';
			int b = rand() % 10000;
			fout << b << endl;
			for (int j = 0; j < a; j++) {
				int n = rand() % 10;
				fout << n << ' ';
				int k = rand() % 900;
				fout << k << ' ';
			}
			fout << endl;
		}
		fout.close();
	}
	{
		ifstream fin("data");
		int T = 0;
		fin >> T;
		ofstream fout("res.txt");
		for (int i = 0; i < T; i++) {
			int n, w;
			fin >> n >> w;
			int *weight = new int[n];
			int *value = new int[n];
			int *bag = new int[w];
			for (int t = 0; t < w; t++) {
				bag[w] = 0;
			}
			for (int j = 0; j < n; j++)
			{
				fin >> weight[j] >> value[j];
			}
			int t0 = clock();
			Select(n, w, fout, weight, value, bag);
			int t1 = clock();
			fout << t1 - t0 << endl;
		}
		fout.close();
	}
	return 0;
}