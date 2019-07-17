// input de teste:
// 13
// 1 3 2 4 5 1 3 4 2 5 6 3 1

#include <bits/stdc++.h>

using namespace std;

#define N 1010100

int n, bit[N], v[N];

int sum(int pos){
	int ans = 0;
	for(; pos; pos-=pos&(-pos)) ans+=bit[pos];
	return ans;
}

void update(int pos, int val){
	for(; pos<=n; pos+=pos&(-pos)) bit[pos]+=val;
}

int kth(int k){//retorna o késimo menor elemento na bit.(lembre-se que a bit é uma bit de frequencia)
	int pos=0;
	for(int lg = 30; lg>=0; lg--){//atencao no for decrescente
		if(pos+(1<<lg) > n) continue;
		
		if(bit[pos+(1<<lg)] < k){//tenta andar nas maiores potencias de 2 possiveis sem atingir o k
			k-=bit[pos+(1<<lg)];
			pos+=(1<<lg);
		}
	}
	return pos+1;
}

int main(){
	
	scanf("%d", &n);
	
	for(int i=1; i<=n; i++){
		scanf("%d", &v[i]);
		update(v[i], 1);//bit de frequencia
	}
	printf("%d-esimo menor elemento do conjunto = %d\n", 4, kth(4));
}
