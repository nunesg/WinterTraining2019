//URI - 1500 - Consultas Horríveis usando SQRT nas queries

#include <bits/stdc++.h>

using namespace std;

#define N 101010
#define BLOCK 333

typedef long long ll;

struct qry{
	int l, r, x;
};

int block_size;
int n, q;
ll v[N], acc[N], prefix_sum[N];

void build(){
	for(int i=1; i<=n; i++) {
		acc[i] += acc[i-1];
		v[i] += acc[i];
	}
	for(int i=1; i<=n; i++) acc[i] = 0;

	for(int i=1; i<=n; i++) prefix_sum[i] = prefix_sum[i-1]+v[i];
}

int intersecao(int a, int b, int l, int r){
	if(b<l || a>r) return 0;//disjunto
	
	return min(b, r) - max(a, l) + 1;
}

int main(){
	int tc;
	scanf("%d", &tc);
	
	while(tc--){
		
		scanf("%d %d", &n, &q);
		
		block_size = sqrt(n)+1;
		
		for(int i=0; i<=n; i++){
			v[i] = acc[i] = prefix_sum[i] = 0;
		}
		
		int op, l, r, x;
		vector<qry> vet;
		
		
		for(int b=1, i=1; i<=q; b++){
			
			build();//preprocessa
			
			for(int k=0; k<block_size && i<=q; i++, k++){
				scanf("%d %d %d", &op, &l, &r);
				
				if(op == 0){//update
					scanf("%d", &x);
					vet.push_back({l, r, x});
				}else{//query
					
					ll answer = prefix_sum[r] - prefix_sum[l-1];//resposta considerando os updates dos blocos anteriores
					
					for(qry aux : vet){//updates anteriores no mesmo bloco
						answer+= (ll)intersecao(aux.l, aux.r, l, r)*aux.x;
					}
					printf("%lld\n", answer);
				}
			}
			
			for(qry aux : vet){//faz os updates do bloco
				acc[aux.l]+=aux.x;
				acc[aux.r+1]-=aux.x;
			}
			vet.clear();
		}
	}
}
