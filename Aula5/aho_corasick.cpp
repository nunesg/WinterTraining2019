// conta quantas ocorrencias dos padroes ocorrem no texto

#include <bits/stdc++.h>

using namespace std;

#define N 1010101


string s, txt;
int cont;

struct no{
	#define ALF 130
	
	no *pai, *suffix_link, *nxt[ALF];
	char c;
	int fim, num;
	
	no(char letra, int id){
		c = letra;
		for(int i=0; i<ALF; i++) nxt[i] = NULL;
		pai = suffix_link = NULL;
		fim = 0;
		num = id;
	}
	
	
	void insert(int i){
		if(i == s.size()){
			fim++;
			return;
		}
		
		int letra = s[i]-'A';
		if(!nxt[letra]){
			nxt[letra] = new no(s[i], cont++);
			nxt[letra]->pai = this;
		}
		nxt[letra]->insert(i+1);
	}
	
	void build_sf(){
		
		queue<no*> q;
		for(int i=0; i<ALF; i++)
			if(nxt[i]) q.push(nxt[i]);
		
		while(q.size()){
			no *u = q.front(); q.pop();
			
			no *tmp = u->pai->suffix_link;

			char letra = u->c - 'A';

			while(tmp && !tmp->nxt[letra]) 	tmp = tmp->suffix_link;

			u->suffix_link = (tmp) ? tmp->nxt[letra] : this;
			u->fim += u->suffix_link->fim;
			
			for(int i=0; i<ALF; i++)
				if(u->nxt[i]) q.push(u->nxt[i]);
		}
	}
	
	void destroy(){
		for(int i=0; i<ALF; i++){
			if(nxt[i]){
				nxt[i]->destroy();
				delete nxt[i];
			}
		}
	}
	
};

no *root;

no *climb(no *u, char letra){
	no *tmp = u;
	while(tmp && !tmp->nxt[letra]) tmp = tmp->suffix_link;
	return tmp ? tmp->nxt[letra] : root;
}

int query(int pos, no *u){
	if(pos==txt.size()) return u->fim;
	return u->fim + query(pos+1, climb(u, txt[pos]-'A'));
}


int main(){
	
	int n;
	cin >> n;
	cont=0;
	root = new no('$', cont++);
	
	for(int i=0; i<n; i++){
		cin >> s;
		root->insert(0);
	}
	root->build_sf();
	cin >> txt;
	cout << query(0, root) << endl;
	
}
