#include <bits/stdc++.h>

using namespace std;

#define N 101010

struct no{
	int val, lazy;
	no() : val(0), lazy(0) {}
}st[N<<2];

int n, v[N];

no join(no a, no b){
	no ans;
	ans.val = a.val + b.val;
	ans.lazy = a.lazy + b.lazy;
	return ans;
}

void push(int idx, int l, int r){
	
	if(st[idx].lazy == 0) return;
	
	st[idx].val += (r-l+1)*st[idx].lazy;

	int nxt = idx<<1;
	if(l != r){//se nao for folha
		st[nxt].lazy+=st[idx].lazy;
		st[nxt+1].lazy+=st[idx].lazy;
	}

	st[idx].lazy = 0;
}

void build(int idx, int l, int r){
	
	if(l == r){
		st[idx].val = v[l];
		return;
	}
	
	int mid = (l+r)>>1, nxt = idx<<1;
	
	build(nxt, l, mid);
	build(nxt+1, mid+1, r);
	
	st[idx] = join(st[nxt], st[nxt+1]);
}

no query(int idx, int l, int r, int a, int b){//query minimo no range [a, b]
	push(idx, l, r);
	
	if(r<a || l>b) return no();
	if(a<=l && r<= b) return st[idx];
	
	int mid = (l+r)>>1, nxt = idx<<1;
	return join(query(nxt, l, mid, a, b),  query(nxt+1, mid+1, r, a, b));
}

void update(int idx, int l, int r, int a, int b, int val){
	push(idx, l, r);
	if(r<a || l>b) return;//disjunto
	
	if(a<=l && r<=b){//contido
		st[idx].lazy = val;
		push(idx, l, r);
		return;
	}
	
	int mid = (l+r)>>1, nxt = idx<<1;
	
	update(nxt, l, mid, a, b, val);
	update(nxt+1, mid+1, r, a, b, val);
	
	st[idx] = join(st[nxt], st[nxt+1]);
}

int main(){
	
	scanf("%d", &n);
	
	for(int i=1; i<=n; i++){
		scanf("%d", &v[i]);
	}
	
	build(1, 1, n);
	
	//faça updates e queries pra testar as funções
	
}
