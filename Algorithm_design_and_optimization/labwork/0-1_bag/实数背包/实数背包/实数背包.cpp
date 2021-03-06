#include"stdafx.h"
#include<iostream>
#include<fstream>
#include<random>
#include<ctime>

using namespace std;
 
class Object
{
	friend class Knapsack;
	int number;
	double weight;
	double value;
};
 
class JumpNode
{
	friend class Knapsack;
	friend void Print();
	double enoughw;
	double enoughv;
	int amount;
	int *selected;
	JumpNode *next;

};

class Knapsack
{
	Knapsack(int n, double *w, double *v, double c);
	friend void Print();
public:
	void DynamicProgram();
private:
	int n;
	double c;
	Object *Ot;
	JumpNode *firstp;
	JumpNode *firstq;
	JumpNode *abandon;
};

void Knapsack::DynamicProgram()
{
	int i = n;
	for (; i >= 1; i--)
	{
		JumpNode *jptr = firstp;
		JumpNode *lastq = firstq;
		bool isfq = true;
		while (jptr != nullptr)
		{
			if (jptr->enoughw + Ot[i].weight <= c)
			{
				JumpNode *temp;
				if (abandon != nullptr)
				{
					temp = abandon;
					abandon = temp->next;
				}
				else
				{
					temp = new JumpNode;
					temp->selected = new int[n + 1];
				}
				temp->amount = jptr->amount + 1;
				temp->enoughw = jptr->enoughw + Ot[i].weight;
				temp->enoughv = jptr->enoughv + Ot[i].value;
				for (int j = 1; j < temp->amount; j++)
					temp->selected[j] = jptr->selected[j];
				temp->selected[temp->amount] = Ot[i].number;
				temp->next = nullptr;
				if (isfq)
				{
					firstq = temp;
					lastq = temp;
					isfq = false;
				}
				else
				{
					lastq->next = temp;
					lastq = temp;
				}
			}
			jptr = jptr->next;
		}
		if (!isfq)
			lastq->next = nullptr;
		if (firstq != nullptr)
		{
			JumpNode *firsttemp = nullptr;
			JumpNode *temp = nullptr;
			bool isfirst = true;
			double cmaxvalue = 0;
			while ((firstp != nullptr) && (firstq != nullptr))
			{
				if (firstp->enoughw < firstq->enoughw)
				{
					if (isfirst)
					{
						temp = firstp;
						firstp = firstp->next;
						firsttemp = temp;
						isfirst = false;
						cmaxvalue = temp->enoughv;
					}
					else
					{
						temp->next = firstp;
						temp = firstp;
						firstp = firstp->next;
						cmaxvalue = temp->enoughv;
					}
				}
				else
				{
					if (firstp->enoughw == firstq->enoughw)
					{
						if (firstp->enoughv > firstq->enoughv)
						{
							temp->next = firstp;
							temp = firstp;
							firstp = firstp->next;
							cmaxvalue = temp->enoughv;
							JumpNode *ab;
							ab = firstq->next;
							if (abandon != nullptr)
							{
								firstq->next = abandon->next;
								abandon->next = firstq;
							}
							else
								abandon = firstq;
							firstq = ab;

						}
						else
						{
							temp->next = firstq;
							temp = firstq;
							firstq = firstq->next;
							cmaxvalue = temp->enoughv;
							JumpNode *ab;
							ab = firstp->next;
							if (abandon != nullptr)
							{
								firstp->next = abandon->next;
								abandon->next = firstp;
							}
							else
								abandon = firstp;
							firstp = ab;
						}
					}
					else
					{
						if (firstq->enoughv > cmaxvalue)
						{
							temp->next = firstq;
							temp = firstq;
							firstq = firstq->next;
							cmaxvalue = temp->enoughv;
						}
						else
						{
							JumpNode *ab;
							ab = firstq->next;
							if (abandon != nullptr)
							{
								firstq->next = abandon->next;
								abandon->next = firstq;
							}
							else
								abandon = firstq;
							firstq = ab;
						}
					}
				}

			}
			if (firstq == nullptr)
				while (firstp != nullptr)
				{
					if (firstp->enoughv <= cmaxvalue)
					{
						JumpNode *ab;
						ab = firstp->next;
						if (abandon != nullptr)
						{
							firstp->next = abandon->next;
							abandon->next = firstp;
						}
						else
							abandon = firstp;
						firstp = ab;
					}
					else
					{
						temp->next = firstp;
						temp = firstp;
						firstp = firstp->next;
						cmaxvalue = temp->enoughv;
					}
				}
			else
			{
				while (firstq != nullptr)
				{
					if (firstq->enoughv <= cmaxvalue)
					{
						JumpNode *ab;
						ab = firstq->next;
						if (abandon != nullptr)
						{
							firstq->next = abandon->next;
							abandon->next = firstq;
						}
						else
							abandon = firstq;
						firstq = ab;
					}
					else
					{
						temp->next = firstq;
						temp = firstq;
						firstq = firstq->next;
						cmaxvalue = temp->enoughv;
					}
				}
			}
			temp->next = nullptr;
			firstp = firsttemp;
		}
	}
}

Knapsack::Knapsack(int n, double *w, double *v, double c) :n(n), c(c)
{
	Ot = new Object[n + 1];
	for (int i = 1; i <= n; i++)
	{
		Ot[i].number = i;
		Ot[i].weight = w[i - 1];
		Ot[i].value = v[i - 1];
	}
	JumpNode *newNode = new JumpNode;
	newNode->amount = 0;
	newNode->enoughv = 0;
	newNode->enoughw = 0;
	newNode->next = nullptr;
	newNode->selected = new int[n + 1];
	firstp = newNode;
	firstq = nullptr;
}

void Print()
{
	{
		int T = 5;
		ofstream fout("data");
		srand(time(0));
		for (int i = 0; i < T; i++) {
			int n, c;
			n = rand() % 20;
			c = rand() % 100;
			fout << n << ' ' << c << endl;
			for (int j = 0; j < n; j++) {
				int a, b;
				a = (rand() % 80);
				b = (rand() % 100);
				double c, d;
				c = a / 10;
				d = b / 10;
				fout << c << ' ' << d << ' ';
			}
			fout << endl << endl;
		}
		fout.close();
	}
	{
		ifstream fin("data");
		ofstream fout("res");
		int T;
		fin >> T;
		for (int i = 0; i < T;i++) {
			int N;
			fin >> N;
			int c;
			fin >> c;
			double *w = new double[N];
			double *v = new double[N];
			for (int j = 0; j < N; j++) {
				fin >> w[j] >> v[j];
			}
			int t0 = clock();
			Knapsack *K = new Knapsack(N, w, v, c);
			K->DynamicProgram();
			JumpNode *scan = K->firstp;
			int *selarr;
			int count = 0;
			double selvalue = 0;
			JumpNode *oldscan = scan;
			while (scan != nullptr)
			{
				if (scan->enoughw > c)
					break;
				oldscan = scan;
				scan = scan->next;
			}
			selarr = oldscan->selected;
			selvalue = oldscan->enoughv;
			count = oldscan->amount;
			int t1 = clock();
			for (int i = count; i > 0; i--) {
				fout << selarr[i] << " ";
			}
			fout << N << ' ' << c << ' ';
			fout << selvalue << t1 - t0 << endl;
		}
	}
}

int main()
{
	Print();
	return 0;
}