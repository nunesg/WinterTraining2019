#include <bits/stdc++.h>

using namespace std;

#define NMAX 100

int n, tempo=1, p[NMAX], vet[NMAX], in[NMAX], out[NMAX], d[NMAX], h[NMAX], soma[NMAX], val[NMAX];
vector<int> adj[NMAX];

void dfs(int u, int pai){
	in[u] = tempo++;//euler tour
	
	vet[in[u]] = u;//passar a arvore pro vetor

	p[u] = pai;
	soma[u] = val[u];//soma de subarvore
	d[u] = d[pai]+1;//profundidade, distancia da raiz

	int maior=-1;//altura da subarvore
	for(int v : adj[u]){
		if(v == pai) continue;
		dfs(v, u);
		soma[u]+= soma[v];
		maior = max(maior, h[v]);
	}
	h[u] = maior+1;
	
	out[u] = tempo++;
}

bool isAncestral(int u, int v){//checa se u é ancestral do v em O(1)
	return in[u] <= in[v] && out[v] <= out[u];
}


int lca(int u, int v){//LCA O(n)
	if(d[u] < d[v]) swap(u, v);//u tem q ser o mais abaixo
	
	while(d[u] != d[v]) u = p[u];
	//u e v estao no mesmo nivel na arvore
	
	while(u!=v){//sobe com os dois ao mesmo tempo
		u = p[u];
		v = p[v];
	}
	return u;
}


int main(){
	
	scanf("%d", &n);
	int a, b;
	for(int i=1; i<n; i++){
		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for(int i=1; i<=n; i++){
		scanf("%d", &val[i]);
	}

	dfs(1, 0);//enraiza a arvore no vertice 1
	
	for(int u=1; u<=n; u++){
		printf("\nu = %d\nsoma = %d\nh = %d\nd = %d\n", u, soma[u], h[u], d[u]);
		printf("in = %d, out = %d\n", in[u], out[u]);
	}
}
