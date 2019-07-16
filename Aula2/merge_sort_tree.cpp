#include <bits/stdc++.h>

using namespace std;

#define N 101010

int n, v[N];
vector<int> st[N<<2];

void build(int idx, int l, int r){
	if(l == r){
		st[idx].push_back(v[l]);
		printf("push (%d)\n", v[l]);
		return;
	}
	
	int mid = (l+r)>>1, nxt = idx<<1;
	
	build(nxt, l, mid);
	build(nxt+1, mid+1, r);
	
	st[idx].resize(r-l+1);
	merge(st[nxt].begin(), st[nxt].end(), st[nxt+1].begin(), st[nxt+1].end(), st[idx].begin());
	
	printf("\nst[%d], range[%d, %d]\n", idx, l, r);
	for(int x : st[idx]) printf("    x: %d\n", x);
}

int query(int idx, int l, int r, int a, int b, int k){//quantos elementos <= k existem no range [a, b]
	if(r<a || l>b) return 0;//disjunto
	if(a<=l && r<= b){
		return upper_bound(st[idx].begin(), st[idx].end(), k) - st[idx].begin();//inteiramente contido
	}
	
	int mid = (l+r)>>1, nxt = idx<<1;
	return query(nxt, l, mid, a, b, k) +
		   query(nxt+1, mid+1, r, a, b, k);
}

int main(){
	
	scanf("%d", &n);
	
	for(int i=1; i<=n; i++){
		scanf("%d", &v[i]);
	}
	
	build(1, 1, n); //idx da raiz da segtree deve ser 1, mas o intervalo pode começar em 0 sem problemas
	printf("query(3, 9, 3) = %d\n", query(1, 1, n, 3, 9, 3));
}
