#include<iostream>
using namespace std;

int sortfew(int*a,int m,int n){
	int min;
	int mark=0;
	for(int k=0;k<(n-m);k++){
		min=INT_MAX;
		for(int i=m+k;i<n;i++){
			if(p[i]<min){
				min=p[i];
				mark=i;
			}
		}
		p[mark]=p[m+k];
		p[m+k]=min;
	}
	return m+(n-m+1)/2;
}

int search(int* a,int m,int n,int p){
	
}
int main(){
	int n=0;
	int* line=new int[n];
	for(int i=0;i<n;i++){
		cin>>line[i];
	}




	return 0;
}