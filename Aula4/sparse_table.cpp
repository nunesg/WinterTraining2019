#include <bits/stdc++.h>

using namespace std;

#define N 1101010
#define LOG 22

int n, v[N], table[N][LOG];

void build_table(){
	
	for(int i=0; i<n; i++) table[i][0] = v[i];
	
	for(int j=1; j<LOG; j++){
		for(int i=0; i+(1<<j)-1 < n; i++){
			table[i][j] = min( table[i][j-1], table[i+(1<<(j-1))][j-1] );
		}  
	}
}

//__builtin_ctz - quantos 0s à direita
//__builtin_clz - quantos 0s à esquerda
//__builtin_popcount - quantos 1s

int query_min(int l, int r){
	int d = r-l+1;//tamanho do range
	int k = 32 - __builtin_clz(d) - 1;//builtin_clz retorna #bits à esquerda em O(1)
	return min( table[l][k], table[r - (1<<k) + 1][k] );
}

int main(){
	
	scanf("%d", &n);
	
	for(int i=0; i<n; i++){
		scanf("%d", &v[i]);
	}
	
	build_table();
}
