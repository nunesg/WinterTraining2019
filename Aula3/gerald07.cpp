#include <bits/stdc++.h>

using namespace std;


#define N 201010
#define BLOCK 333

struct qry{
	int l, r, id;
	qry(){}
	qry(int a, int b, int c) : l(a), r(b), id(c) {}
};

struct edge{
	int u, v;
};


struct dsu{
	
	vector<int> comp;
	int n, qtd;
	
	dsu(){}
	
	dsu(int x){
		n = x;
		qtd = n;
		comp.resize(n+1);
		
		for(int i=0; i<=n; i++) comp[i] = i;
	}
	
	int find(int i){ return i == comp[i] ? i : comp[i] = find(comp[i]); }
	
	bool same(int i, int j){ return find(i) == find(j); }
	
	void join(int i, int j){
		if(same(i, j)) return;
		comp[find(i)] = find(j);
		qtd--;
	}
	
	void clear(){
		comp.clear();
		n = 0;
		qtd = 0;
	}
};


int n, m, q, ini[N], fim[N], blc[N], answer[N];
dsu global, small;
edge E[N];
vector<qry> vet[N/BLOCK+10];
unordered_map<int, int> mapa;

int solve_small(int l, int r){
	small.clear();
	mapa.clear();
	int c=0, u, v;
	for(int i=l; i<=r; i++){
		u = global.find(E[i].u), v = global.find(E[i].v);
		if(!mapa.count(u)) mapa[u] = ++c;
		if(!mapa.count(v)) mapa[v] = ++c;
	}
	
	small = dsu(c);

	int ans = global.qtd - c;
	
	for(int i=l; i<=r; i++){
		u = global.find(E[i].u), v = global.find(E[i].v);
		u = mapa[u];
		v = mapa[v];
		small.join(u, v);
	}
	ans+= small.qtd;
	return ans;
}

void solve_block(int b){
	
	sort(vet[b].begin(), vet[b].end(), [](qry a, qry b){ return a.r < b.r; });
	
	global = dsu(n);
	int u, v;
	for(int k=0, i = ini[b+1]; k<vet[b].size(); k++){
		
		
		for(; i<=vet[b][k].r; i++){
			u = E[i].u;
			v = E[i].v;
			global.join(u, v);
		}
		
		answer[vet[b][k].id] = solve_small(vet[b][k].l, fim[b]);
	}
	
}


int main(){
	
	int tc;
	scanf("%d", &tc);
	
	while(tc--){
		scanf("%d %d %d", &n, &m, &q);
		
		for(int b=0, i=1; i<=m; b++){
			ini[b] = i;
			vet[b].clear();
			for(int j=0; j<BLOCK && i<=m; j++, i++){
				blc[i] = b;
			}
			fim[b] = i-1;
		}
		
		for(int i=1; i<=m; i++){
			scanf("%d %d", &E[i].u, &E[i].v);
		}
		int a, b;
		global = dsu(n);
		for(int i=0; i<q; i++){
			scanf("%d %d", &a, &b);
			if(b-a >= BLOCK*2){
				vet[blc[a]].push_back(qry(a, b, i));
			}else answer[i] = solve_small(a, b);
		}
		
		for(int b=0; b<blc[m]; b++){
			solve_block(b);
		}

		for(int i=0; i<q; i++){
			printf("%d\n", answer[i]);
		}
	}
	
}
