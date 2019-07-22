#include <bits/stdc++.h>

using namespace std;

#define ALF 30

string s;

struct no{
	
	no *nxt[ALF];
	int cont, fim;
	char c;
	
	no(char k){
		c = k;
		for(int i=0; i<ALF; i++) nxt[i] = NULL;
		cont = fim = 0;
	}
	
	void insert(int i){
		cont++;
		if(i == s.size()){
			fim=1;
			return;
		}
		if(!nxt[s[i]-'a'])	nxt[s[i]-'a'] = new no(s[i]);
		
		return nxt[s[i]-'a']->insert(i+1);
	}
	
	void destroy(){
		for(int i=0; i<ALF; i++){
			if(nxt[i]) {
				nxt[i]->destroy();
				delete nxt[i];
			}
		}
	}
	
};

no *root;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	root = new no('$');
	int n;
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> s;
		root->insert(0);
	}
	
	// resolve problema
	
	root->destroy();
	delete root;
}
