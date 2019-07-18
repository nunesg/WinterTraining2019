// LCA em O(1).
// Problema do spoj: https://www.spoj.com/problems/LCA/

#include <bits/stdc++.h>

using namespace std;

#define N 1010
#define LOG 14

int n, h[N], table[N<<1][LOG], in[N], tempo=0, vet[N<<1];//table ta 2n pq é feita no vetor vet
int grau[N];
vector<int> adj[N];

void dfs(int u, int pai){
	
	h[u] = h[pai]+1;
	vet[tempo] = u;
	in[u] = tempo++;
	
	for(int v : adj[u]){
		if(v == pai) continue;
		dfs(v, u);
		vet[tempo++] = u;
	}
}

void build_table(){
	for(int i=0; i<tempo; i++) table[i][0] = vet[i];
	
	for(int j=1; j<LOG; j++){
		for(int i=0; i+(1<<j)<=tempo; i++){
			if(h[ table[i][j-1] ] < h[ table[i+(1<<(j-1))][j-1] ])
				table[i][j] = table[i][j-1];
			else
				table[i][j] = table[i+(1<<(j-1))][j-1];
		}
	}
}

int lca(int u, int v){//lca em O(1)
	int l = in[u], r = in[v];
	if(l > r) swap(l,r);
	int k = 31 - __builtin_clz(r-l+1);
	if(h[ table[l][k] ] < h[ table[r-(1<<k)+1][k] ])
		return table[l][k];
	else
		return table[r-(1<<k)+1][k];
}

int main(){
	
	int tc,caso=1;
	
	scanf("%d", &tc);
	
	while(tc--){
		scanf("%d", &n);
		
		int a, b, q;
		for(int i=1; i<=n; i++){
			scanf("%d", &a);
			adj[i].clear();
			for(int j=0; j<a; j++){
				scanf("%d", &b);
				grau[b]++;
				adj[i].push_back(b);
			}
		}
		int root;
		for(int i=1; i<=n; i++) if(!grau[i]) root = i;//acha a raiz da arvore. Se a arvore nao for enraizada pode ser qualquer raiz
		tempo=0;
		
		dfs(root, 0);//euler tour
		build_table();//constroi a sparse table
		
		scanf("%d", &q);
		printf("Case %d:\n", caso++);
		while(q--){
			scanf("%d %d", &a, &b);
			printf("%d\n", lca(a, b));
		}
		
	}
}
