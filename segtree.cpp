#include <bits/stdc++.h>

using namespace std;

#define N 101010

int n, st[N<<2], v[N];

void build(int idx, int l, int r){
	if(l == r){//intervalo de tamanho 1
		st[idx] = v[l];
		return;
	}
	
	int mid = (l+r)>>1, nxt = idx<<1;// mid = (l+r)/2, nxt = idx*2
	
	/*
	 
	 árvore binária estática, pra um nó i:
	 
	 leftChild(i) = 2*i
	 rightChild(i) = 2*i + 1
	 
	 */
	
	build(nxt, l, mid);//filho da esquerda
	build(nxt+1, mid+1, r);//filho da esquerda
	
	st[idx] = min(st[nxt], st[nxt+1]);//calcula valor do nó atual
}

int query(int idx, int l, int r, int a, int b){//query minimo no range [a, b]
	if(r<a || l>b) return INT_MAX;//disjunto
	if(a<=l && r<= b) return st[idx];//inteiramente contido
	
	int mid = (l+r)>>1, nxt = idx<<1;
	return min(query(nxt, l, mid, a, b),
			   query(nxt+1, mid+1, r, a, b)
			  );
}

void update(int idx, int l, int r, int pos, int val){
	if(l == r){//folha
		st[idx] = val;
		v[pos] = val;
		return;
	}
	
	int mid = (l+r)>>1, nxt = idx<<1;
	
	if(pos <= mid) update(nxt, l, mid, pos, val);//ta pra esquerda
	else update(nxt+1, mid+1, r, pos, val);
	
	st[idx] = min(st[nxt], st[nxt+1]);//atualiza os ancestrais
}

int main(){
	
	scanf("%d", &n);
	
	for(int i=1; i<=n; i++){
		scanf("%d", &v[i]);
	}
	
	build(1, 1, n); //idx da raiz da segtree deve ser 1, mas o intervalo pode começar em 0 sem problemas
	
	printf("query(3, 6) = %d\n", query(1, 1, n, 3, 6));
	update(1, 1, n, 4, 10);//muda o valor da posicao 4
	printf("query(3, 6) = %d\n", query(1, 1, n, 3, 6));
}
