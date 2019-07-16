#include <bits/stdc++.h>

using namespace std;

#define N 1010100

int n, bit[N], v[N];
//vetor bit deve começar com 0. Como é global, ja inicia com 0 automaticamente
//a bit também exige que o vetor esteja 1-indexado

int sum(int pos){// soma do prefixo [1, pos]
	int ans = 0;
	for(; pos; pos-=pos&(-pos)) ans+=bit[pos];
	return ans;
}

void update(int pos, int val){//soma val na posicao pos
	for(; pos<=n; pos+=pos&(-pos)) bit[pos]+=val;
}

int main(){
	
	scanf("%d", &n);
	
	for(int i=1; i<=n; i++){
		scanf("%d", &v[i]);
		update(i, v[i]);
	}
	
	printf("soma(3, %d) = %d\n", n, sum(n) - sum(2));
}
