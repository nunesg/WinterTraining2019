//URI 2223 - Inventário de Pomekon usando Persistent Segment Tree

#include <bits/stdc++.h>

using namespace std;

#define N 201010

typedef long long ll;

struct no{
	ll val;
	int filhoEsq, filhoDir;
	no(){
		val = 0;
		filhoDir = filhoEsq = 0;
	}
}st[10010101];

int n, q, v[N], cntNo=1, root[N];

void build(int idx, int l, int r){
	if(l == r){
		st[idx].val = v[l];
		return;
	}

	int mid = (l+r)>>1, nxt = idx<<1;
	
	st[idx].filhoEsq = cntNo++;
	st[idx].filhoDir = cntNo++;
	
	
	build(st[idx].filhoEsq, l, mid);
	build(st[idx].filhoDir, mid+1, r);
	
	st[idx].val = st[ st[idx].filhoEsq ].val + st[ st[idx].filhoDir ].val;
}

int update(int no1, int l, int r, int pos, int valor){
	
	int no2 = cntNo++;//cria um nó clone
	st[no2] = st[no1];

	if(l == r){
		st[no2].val = valor;
		return no2;
	}
	
	int mid = (l+r)>>1;
	
	if(pos <= mid) st[no2].filhoEsq = update(st[no1].filhoEsq, l, mid, pos, valor);
	else st[no2].filhoDir = update(st[no1].filhoDir, mid+1, r, pos, valor);
	
	st[no2].val = st[ st[no2].filhoEsq ].val + st[ st[no2].filhoDir ].val;
	return no2;
}

ll query(int idx, int l, int r, int a, int b){
	if(r<a || l>b) return 0;
	if(a<=l && r<=b) return st[idx].val;
	
	int mid = (l+r)>>1;
	return query(st[idx].filhoEsq, l, mid, a, b) +
		   query(st[idx].filhoDir, mid+1, r, a, b);
} 


int main(){
	
	int tc;
	
	scanf("%d", &tc);
	
	while(tc--){
		scanf("%d", &n);
		
		root[0] = 0;
		cntNo = 1;
		for(int i=1; i<=n; i++){
			scanf("%d", &v[i]);
			root[0] = update(root[0], 1, n, i, v[i]);
		}
		
		//~ build(root[0], 1, n);//nunca uso
		
		scanf("%d", &q);
		
		int op, x, y, k, cntUp=0;
		
		while(q--){
			scanf("%d %d %d", &op, &x, &y);
			if(op == 1){
				scanf("%d", &k);
				printf("%lld\n", query(root[k], 1, n, x, y));
			}else{
				root[cntUp+1] = update(root[cntUp], 1, n, x, y);
				cntUp++;
			}
		}
		
	}
}
