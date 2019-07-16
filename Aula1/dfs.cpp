#include <bits/stdc++.h>

using namespace std;

#define NMAX 100
#define AMARELO 1
#define ROSA 2
#define BRANCO 0


int n, m, visitados[NMAX], distancia[NMAX], comp[NMAX];
vector<int> adj[NMAX];//lista de adjacencia
queue<int> fila;

void dfs(int u, int c){
	
	visitados[u] = AMARELO;
	comp[u] = c;
	for(int v : adj[u]){
		if(visitados[v] == BRANCO) 
			dfs(v, c);
	}
	visitados[u] = ROSA;
}

int conta_componentes(){
	int contador=0;
	memset(visitados, BRANCO, sizeof visitados);
	
	for(int i=1; i<=n; i++){
		if(!visitados[i]){
			dfs(i, contador);
			contador++;
		}
	}
	return contador;
}

int main(){
	
	scanf("%d %d", &n, &m);
	int a, b;
	for(int i=0; i<m; i++){
		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	printf("%d componentes conexas\n", conta_componentes());
	
}
