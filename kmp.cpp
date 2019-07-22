#include <bits/stdc++.h>

using namespace std;

#define N 101010

string s, txt;
int n, m, p[N];

void kmp(){
	
	p[0] = 0;
	for(int i=1; i<n; i++){
		
		p[i] = p[i-1];
		while(txt[p[i]] != txt[i] && p[i]) p[i] = p[p[i]-1];
		
		if(txt[p[i]] == txt[i]) p[i]++;
		
	}
	for(int i=0; i<n; i++) printf("p[%d] = %d\n", i, p[i]);
}


int main(){
	
	getline(cin, s);
	txt = s+"$";
	getline(cin, s);
	txt+=s;
	
	n = txt.size();
	cout << txt << endl;
	kmp();
	
}
