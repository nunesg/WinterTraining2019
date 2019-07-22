#include <bits/stdc++.h>

using namespace std;

#define N 1010010

string s;
int z[N];

void calc_z(){
	
	memset(z, 0, sizeof z);
	
	int n = s.size();
	int l=0, r=0;
	
	for(int i=1; i<n; i++){
		if(i<=r)  z[i] = min(r-i+1, z[i-l]);
		
		while(i+z[i] < n && s[z[i]] == s[i+z[i]])
			z[i]++;
		
		if(i+z[i]-1 > r){
			l=i;
			r = i+z[i]-1;
		}
	}
}

int main(){
	
	while(getline(cin, s), s!=""){
		
		calc_z();
		
		for(int i=0; i<s.size(); i++) printf("z[%d] = %d\n", i, z[i]);
		printf("\n");
		
	}
	
}
