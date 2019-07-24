#include <bits/stdc++.h>

using namespace std;

#define N 101010

typedef long long ll;

int n, val[N], sz[N], freq[N], contf[N], Fmax;
ll answer[N], sumf[N];
vector<int> adj[N];

void dfs(int u, int p){
	sz[u] = 1;
	for(int v : adj[u]){
		if(v == p) continue;
		dfs(v, u);
		sz[u]+=sz[v];
	}
}

void upd(int u, int flag){
	
	int x = val[u];
	int old = freq[x];
	freq[x]+=flag;
	
	contf[old]--;
	contf[freq[x]]++;
	
	sumf[old]-=x;
	sumf[freq[x]]+=x;
	
	if(freq[x] > Fmax) Fmax = freq[x];
	else if(contf[Fmax] == 0) Fmax = freq[x];
}

void update(int u, int p, int flag){//flag=1 -> add, flag=-1 -> remove
	upd(u, flag);
	for(int v : adj[u]){
		if(v == p) continue;
		update(v, u, flag);
	}
}

void solve(int u, int p, int flag){//sack, flag=0 -> apaga, flag=1 -> mantem
	
	int big=-1;
	
	for(int v : adj[u]){
		if(v == p) continue;
		if(big ==-1 || sz[v] > sz[big]) big = v;
	}
	
	for(int v : adj[u]){
		if(v == p || v==big) continue;
		solve(v, u, 0);
	}
	if(big!=-1) solve(big, u, 1);
	
	for(int v : adj[u]){
		if(v == p || v==big) continue;
		update(v, u, 1);
	}
	upd(u, 1);
	answer[u] = sumf[Fmax];
	
	if(flag == 0){
		update(u, p, -1);
	}
}

int main(){
	
	scanf("%d", &n);
	
	for(int i=1; i<=n; i++) {
		scanf("%d", &val[i]);
		sumf[0]+=val[i];
	}
	contf[0] = n;
	
	int a, b;
	for(int i=1; i<n; i++){
		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	dfs(1, 0);
	solve(1, 0, 0);
	
	for(int i=1; i<=n; i++) printf("%lld\n", answer[i]);
}
