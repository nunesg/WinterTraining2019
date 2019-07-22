#define MAXN 100100
const ll A = 1009;
const ll MOD = 9LL + 1e18;
ll pot[MAXN];

ll normalize(ll r){
	while(r<0) r+=MOD;
	while(r>=MOD) r-=MOD;
	return r;
}

ll mul(ll a, ll b){//(a*b)%MOD
	ll q = ll((long double)a*b/MOD);
	ll r = a*b - MOD*q;
	return normalize(r);
}

ll add(ll hash, ll c){
	return (mul(hash, A) + c)%MOD;
}

void buildPot(){
	for (int i = 0; i < MAXN; i++)
	{
		pot[i] = i ? mul(pot[i-1], A) : 1LL;
	}
}

struct Hash{
	string s;
	ll hashNormal, hashInvertida;
	ll accNormal[MAXN], accInvertida[MAXN];
	
	Hash(){}
	Hash(string _s){
		s = _s;
	}
	
	void build(){
		accNormal[0] = 0LL;
		for (int i = 1; i <= (int)s.size(); i++){
			accNormal[i] = add(accNormal[i-1], s[i-1]-'a'+1);
		}
		hashNormal = accNormal[(int)s.size()];
		
		accInvertida[s.size()] = 0LL;
		for (int i = s.size()-1; i >= 0; i--){
			accInvertida[i] = add(accInvertida[i+1], s[i]-'a'+1);
		}
		hashInvertida = accInvertida[0];
		
	}
	
	ll getRangeNormal(int l, int r){//pega a hash da substring (l, r) na string normal (abcd - [0, 2] = abc)
		if(l>r) return 0LL;
		ll ans = (accNormal[r+1] - mul(accNormal[l], pot[r-l+1]))%MOD;
		return normalize(ans);
	}
	
	ll getRangeInvertido(int l, int r){//pega a hash da substring (l, r) na string invertida (abcd - [0, 2] = cba)
		if(l>r) return 0LL;
		ll ans = (accInvertida[l] - mul(accInvertida[r+1], pot[r-l+1]))%MOD;
		return normalize(ans);
	}
};

int main () {
	buildPot();//cuidado com o limite do MAXN
	//resolve o problema
	Hash H = Hash(str);
	H.build();
	
	return 0;
}
