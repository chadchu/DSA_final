#include <bits/stdc++.h>
#define pb push_back
using namespace std;
struct node{
	vector<int> query_no;
	node *next[27];
	node(){for(int i=0;i<27;i++) next[i] = NULL;}
};
inline bool cmp(pair<unsigned int, string> a, pair<unsigned int, string> b);
struct ANS{
	string query;
	vector< pair<unsigned int,string> > q;
	void print(){
		cout << "query: " << query << endl;
		sort(q.begin(),q.end(),cmp);
		auto it = unique(q.begin(),q.end());
		q.resize( distance(q.begin(),it) );
		int m = q.size();
		if(m > 10) m = 10;
		cout << "output: " << m << endl;
		for(int j=0;m>0;j++,m--) cout << q[j].second << '\t' << q[j].first << endl;
	}
};
inline int read();
inline bool isprep(string a);
inline bool ok(string s);
inline vector< vector<string> > tokenize(char s[]);
inline vector<string> generate(vector<string> s);
inline vector<string> cartPr(vector< vector<string> > s);
inline vector<string> ed1n2(vector<string> s);
inline void insert(string s, int k);
inline node* create();
char buf[1045472810];
char *b = buf, *bend = buf + 1045472810;
const string prep[20] = {"of","to","in","for","with","on","at","by","from","up",
						"about","than","after","before","down","between","under",
						"since","without","near"};
vector<ANS> ans;
node *root;
int main(int argc, char **argv){
	root = create();
	char s[110];
	int n = 0;
	while( fgets(s,105,stdin) != NULL ){
		string ss(s);
		ss.pop_back();
		vector< vector<string> > tok = tokenize(s);
		if(tok.size() == 1 && !isprep(tok[0][0])){
			vector<string> candi = ed1n2(tok[0]);
			//oringinal
			candi.pb(ss);
			for(int i=0;i<candi.size();i++){
				if( ok(candi[i]) ){
					insert(candi[i], n);
				}
			}
		}
		else{
			for(int i=0;i<tok.size();i++){
				if( !isprep(tok[i][0]) ){
					string tmp;
					for(int j=0;j<tok[i].size();j++) tmp += (tok[i][j]+' ');
					tmp.pop_back();
					tok[i].clear();
					tok[i].pb(tmp);
					continue;
				}
				tok[i] = generate(tok[i]);
			}
			vector<string> candi = cartPr(tok);
			//oringinal
			candi.pb(ss);
			for(int i=0;i<candi.size();i++){
				if( ok(candi[i]) ){
					insert(candi[i], n);
				}
			}
		}
		vector< pair<unsigned int,string> > e;
		ans.pb( ANS{ss,e} );
		n++;
	}
	register char c;
	FILE *fp;
	fp = fopen(argv[1],"rb");
	fread(buf,1,1045472806,fp);
	assert(fp != NULL);
	fclose(fp);
	node *tmp = root;
	string str;
	while((c = read()) != EOF){
		if( islower(c) ){
			str += c;
			if( tmp->next[ c - 'a' ] == NULL){
				while( (c = read()) != EOF) if(c == '\n') break;
				tmp = root;
				str.clear();
			}
			else tmp = tmp->next[ c - 'a' ];
		}
		else if(c == ' '){
			str += c;
			if( tmp->next[26] == NULL){
				while( (c = read()) != EOF) if(c == '\n') break;
				tmp = root;
				str.clear();
			}
			else tmp = tmp->next[26];
		}
		else if( c == '\t'){
			c = read();
			unsigned int a = 0;
			while( c != '\n'){
				a  = 10*a + (c-'0');
				c = read();
			}
			for(int i=0;i< tmp->query_no.size() ; i++) ans[tmp->query_no[i]].q.pb( make_pair(a, str) );
			tmp = root;
			str.clear();
		}
	}
	for(int i=0;i<n;i++){
		ans[i].print();
	}
}
inline int read(){
	if(b >= bend) return EOF;
	return *b++;
}
inline bool isprep(string a){
	if(a == "of" || a == "to" || a == "in" || a == "for" || a == "with" || a == "on"
	 || a == "at" || a == "by" || a == "from" || a == "up" || a == "about" || a == "than"
 	 || a == "after" || a == "before" || a == "down" || a == "between" || a == "under" || a == "since"
	 || a == "without" || a == "near") return true;
	 else return false;
}
inline bool ok(string s){
	int cnt = 0;
	for(int i=0;i<s.size();i++) if(s[i] == ' ') cnt++;
	if(cnt >= 5) return false;
	return true;
}
inline vector< vector<string> > tokenize(char s[]){
	vector<string> in;
	char *tk;
	tk = strtok(s," \n");
	while(tk != NULL){
		string tmp(tk);
		in.push_back(tmp);
		tk = strtok(NULL," \n");
	}
	vector< vector<string> > ret;
	vector<string> tmp;
	vector<bool> rec;
	tmp.pb(in[0]);
	rec.pb( isprep(in[0]) );
	for(int i=1;i<in.size();i++){
		rec.pb( isprep(in[i]) );
		if( rec[i] != rec[i-1] ){
			ret.pb(tmp);
			tmp.clear();
		}
		tmp.pb(in[i]);
	}
	ret.pb(tmp);
	return ret;
}
inline vector<string> generate(vector<string> s){
	vector<string> ret;
	string tmp;
	//insert
	for(int i=0;i<s.size();i++){
		tmp.clear();
		for(int j=0;j<i;j++) tmp += (s[j] + ' ');
		string a = tmp;
		for(int j=0;j<20;j++){
			tmp = a;
			tmp += prep[j];
			for(int k=i;k<s.size();k++) tmp += (' '+s[k]);
			ret.pb(tmp);
		}
	}
	tmp.clear();
	for(int i=0;i<s.size();i++) tmp += (s[i]+' ');
	string a = tmp;
	for(int k=0;k<20;k++){
		tmp = a;
		tmp += prep[k];
		ret.pb(tmp);
	}
	//for(int i=0;i<ret.size();i++) cout << ret[i] << endl;
	//delete
	for(int i=0;i<s.size();i++){
		tmp.clear();
		for(int j=0;j<s.size();j++){
			if(j==i) continue;
			tmp += (s[j]+' ');
		}
		if( s.size()!=1 ) tmp.pop_back();
		ret.pb(tmp);
	}
	//for(int i=0;i<ret.size();i++) cout << ret[i] << endl;
	//substitute
	for(int i=0;i<s.size();i++){
		tmp.clear();
		for(int j=0;j<i;j++) tmp += (s[j]+' ');
		string a = tmp;
		for(int j=0;j<20;j++){
			tmp = a;
			tmp += prep[j];
			for(int k=i+1;k<s.size();k++) tmp += (' '+s[k]);
			ret.pb(tmp);
		}
	}
	//for(int i=0;i<ret.size();i++) cout << ret[i] << endl;
	return ret;
}
inline vector<string> cartPr(vector< vector<string> > s){
	vector<string> ret;
	string tmp;
	int n = 1;
	for(int i=0;i<s.size();i++) n*=s[i].size();
	for(int i=0;i<n;i++){
		int j = 1;
		for(int k=0;k<s.size();k++){
			tmp += (s[k][(i/j)%s[k].size()]);
			if( s[k][(i/j)%s[k].size()] != "" ) tmp += ' ';
			j *= s[k].size();
		}
		tmp.pop_back();
		ret.pb(tmp);
		tmp.clear();
	}
	return ret;
}
inline vector<string> ed1n2(const vector<string> s){
	vector<string> ret;
	string tmp;
	//ED1
	for(int i=0;i<s.size();i++){
		tmp.clear();
		for(int j=0;j<i;j++) tmp += (s[j] + ' ');
		string a = tmp;
		for(int j=0;j<20;j++){
			tmp = a;
			tmp += prep[j];
			for(int k=i;k<s.size();k++) tmp += (' '+s[k]);
			ret.pb(tmp);
		}
	}
	tmp.clear();
	for(int i=0;i<s.size();i++) tmp += (s[i]+' ');
	string a = tmp;
	for(int k=0;k<20;k++){
		tmp = a;
		tmp += prep[k];
		ret.pb(tmp);
	}
	//ED2
	int n = ret.size();
	vector< vector<string> > p;
	for(int i=0;i<n;i++){
		char str[1000];
		strcpy(str,ret[i].c_str());
		char *tk;
		vector<string> in;
		tk = strtok(str," \n");
		while(tk != NULL){
			string tmpp(tk);
			in.push_back(tmpp);
			tk = strtok(NULL," \n");
		}
		p.pb( in );
	}
	for(int l=0;l<n;l++){
		for(int i=0;i<p[l].size();i++){
			tmp.clear();
			for(int j=0;j<i;j++) tmp += (p[l][j] + ' ');
			string a = tmp;
			for(int j=0;j<20;j++){
				tmp = a;
				tmp += prep[j];
				for(int k=i;k<p[l].size();k++) tmp += (' '+p[l][k]);
				ret.pb(tmp);
			}
		}
		tmp.clear();
		for(int i=0;i<p[l].size();i++) tmp += (p[l][i]+' ');
		string a = tmp;
		for(int k=0;k<20;k++){
			tmp = a;
			tmp += prep[k];
			ret.pb(tmp);
		}
	}
	return ret;
}
inline void insert(string s, int k){
	node *cur = root;
	for(int i=0;i<s.size();i++){
		if(s[i] == ' '){
			if(cur->next[26] == NULL) cur->next[26] = create();
			cur = cur->next[26];
		}
		else{
			if(cur->next[ s[i] - 'a' ] == NULL) cur->next[ s[i] - 'a' ] = create();
			cur = cur->next[ s[i] - 'a' ];
		}
	}
	cur->query_no.pb(k);
}
inline node* create(){
	static node *memory = new node[999999], *z = memory, *zend = memory + 999999;
	if(z == zend){
		memory = new node[999999];
		z = memory;
		zend = memory + 999999;
	}
	return z++;
}
inline bool cmp(pair<unsigned int, string> a, pair<unsigned int, string> b){
	if( a.first != b.first) return a.first>b.first;
	bool c = (a.second < b.second);
	return c;
}
