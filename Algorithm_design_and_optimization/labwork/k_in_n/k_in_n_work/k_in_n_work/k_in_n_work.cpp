#include<iostream>
#include<fstream>
#include<random>
#include<ctime>
using namespace std;

int comp(int*b, int l) {
	l++;
	for (int p = l;; p++) {
		if (b[p] != -1) {
			return p;
		}
	}
}
void search(int* a, int k, int i) {
	for (int t = 0; t < k; t++) {
		for (int m = 0;; m++) {
			if (a[m] != -1 && a[m] > a[comp(a, m)]) {
				a[m] = -1;
				break;
			}
		}
	}
}
int main() {
	{
		std::ofstream fout("data.dat");
		int T = 1000;
		srand(time(0));
		fout << T << endl;
		for (int i = 0; i < T; i++) {
			int a = rand() % 1000;
			fout << a << endl;
			for (int j = 0; j < a; j++) {
				static int b = rand() % 10;
				fout << b;
			}
			fout << rand() % a;
		}
		fout.close();
	}
	{
		ifstream fin("data.dat");
		int T;
		fin >> T;
		for (int round = 0; round < T; round++) {
			long long n; int k;
			int a[1000];
			int line[1000];
			fin >> n >> k;
			for (int j = 0; j < 1000; j++) {
				a[j] = -1;
				line[j] = -1;
			}
			int i;
			for (i = 0; n > 0; i++) {
				a[i] = n % 10;
				n /= 10;
			}
			int t = i - 1;
			for (int j = 0; j < i; j++, t--) {
				line[j] = a[t];
			}
			search(line, k, i);
			for (t = 0; t < i; t++) {
				if (line[t] != -1) {
					cout << line[t];
				}
			}
		}
	}
	
	return 0;
}