//URI - 1500 - Consultas Horríveis usando SQRT pra range update / range queries

#include <bits/stdc++.h>

using namespace std;

#define N 101010
#define BLOCK 333

typedef long long ll;

int block_size;
int n, q, blc[N], ini[BLOCK], fim[BLOCK];
ll sum[BLOCK], lazy[BLOCK], v[N];

void build(){
	block_size = sqrt(n)+1;
	for(int i=1, b=1; i<=n; b++){
		ini[b] = i;//inicio do bloco b
		sum[b] = lazy[b] = 0;
		for(int k=0; k<block_size && i<=n; k++, i++){
			blc[i] = b;//bloco pra cada posicao do vetor
			v[i] = 0;
		}
		fim[b] = i-1;//fim do bloco
	}
}

void update_bruta(int l, int r, int x){
	for(int i=l; i<=r; i++) {
		v[i]+=x;
		sum[blc[i]]+=x;
	}
}

void update_range(int l, int r, int x){
	if(blc[l] == blc[r]){
		update_bruta(l, r, x);
		return;
	}
	
	update_bruta(l, fim[blc[l]], x);
	update_bruta(ini[blc[r]], r, x);
	for(int b = blc[l]+1; b<blc[r]; b++) lazy[b]+=x;
}

ll query_bruta(int l, int r){
	ll answer=0;
	for(int i=l; i<=r; i++) answer+= v[i]+lazy[blc[i]];
	return answer;
}

ll query_range(int l, int r){
	if(blc[l] == blc[r]) return query_bruta(l, r);
	
	ll answer = query_bruta(l, fim[blc[l]]) + query_bruta(ini[blc[r]], r);
	for(int b = blc[l]+1; b<blc[r]; b++){
		answer+= (ll)(fim[b]-ini[b]+1)*lazy[b] + sum[b];
	}
	return answer;
}

int main(){
	int tc;
	scanf("%d", &tc);
	
	while(tc--){
		
		scanf("%d %d", &n, &q);
		build();
		
		int op, l, r, x;
		
		while(q--){
			scanf("%d %d %d", &op, &l, &r);
			if(r<l) swap(l, r);
			
			if(op == 0){
				scanf("%d", &x);
				update_range(l, r, x);
			}else{
				printf("%lld\n", query_range(l, r));
			}
		}
	}
}
