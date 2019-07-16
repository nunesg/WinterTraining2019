#include <bits/stdc++.h>

using namespace std;

#define NMAX 100

int n, m, visitados[NMAX], distancia[NMAX];
vector<int> adj[NMAX];//lista de adjacencia
queue<int> fila;

void bfs(int inicio){
	fila.push(inicio);
	visitados[inicio] = 1;
	distancia[inicio]=0;
	while(fila.size()){
		
		int u = fila.front();
		fila.pop();
		
		for(int v : adj[u]){
			if(!visitados[v]){
				fila.push(v);
				visitados[v]=1;
				distancia[v] = distancia[u]+1;
			}
		}
	}
	
}

int conta_componentes(){
	int contador=0;
	memset(visitados, 0, sizeof visitados);
	
	for(int i=1; i<=n; i++){
		if(!visitados[i]){
			bfs(i);
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
