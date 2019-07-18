// LCA em log usando binary lifting

#include <bits/stdc++.h>

using namespace std;

#define N 1010100
#define LOG 22

int n, val[N], acc[N], h[N], p[N][LOG], min_lca[N][LOG];
vector<int> adj[N];

void dfs(int u, int pai){
	
	h[u] = h[pai]+1;
	acc[u] = acc[pai]+val[u];
	
	p[u][0] = pai;
	min_lca[u][0] = val[u];
	for(int i=1; i<LOG; i++){
		p[u][i] = p[ p[u][i-1] ][i-1];
		min_lca[u][i] = min(min_lca[u][i-1], min_lca[p[u][i-1]][i-1]);
		
	}
	
	for(int v : adj[u]){
		if(v == pai) continue;
		dfs(v, u);
	}
}

int lca(int u, int v){
	if(h[u] < h[v]) swap(u, v);
	//u eh o mais baixo
	
	int d = h[u]-h[v];
	for(int i=0; i<LOG; i++){
		if(d&(1<<i)) u = p[u][i];
	}
	
	if(u == v) return u;//um eh ancestral do outro
	
	for(int k=LOG-1; k>=0; k--){
		if(p[u][k] != p[v][k]){
			u = p[u][k];
			v = p[v][k];
		}
	}
	return p[u][0];//o ancestral eh o pai
}

int sum_path(int u, int v){
	int lc = lca(u,v);
	return acc[u] + acc[v] - 2*acc[lc] + val[lc];
}


int main(){
	
	scanf("%d", &n);
	
	for(int i=1; i<=n; i++) scanf("%d", &val[i]);
	int a, b;
	for(int i=1; i<n; i++){
		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	dfs(1, 0);
	
}
