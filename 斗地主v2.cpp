#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,m,k;
/*
3~17 
14 15 ==> 1 2 
16 17 ==> 小王 大王 
2不包含在连对顺子，飞机
飞机只能带同种类型的牌或者不带 

函数内x为上家出牌，若没有置为0既可以 

*/

void print(vector<vector<int>>& z){
	for(auto& i:z){
		for(auto& j:i) cout << j << " ";cout << "\n";
	}
	cout << "\n"; 
}

map<int,int> p[2],mp;
vector<vector<int>> danpai(int x,int c){ //打单牌 
	vector<vector<int>> ans;
	for(int i=x+1;i<=17;i++){
		vector<int> t;
		if(p[c][i]==0) continue;
		t.push_back(i);
		ans.push_back(t); 
	}
	//print(ans);
	return ans;
}

vector<vector<int>> duizi(int x,int c){ //打对子 
	vector<vector<int>> ans;
	for(int i=x+1;i<=15;i++){
		vector<int> t;
		if(p[c][i]<2) continue;
		t.push_back(i);t.push_back(i);
		ans.push_back(t); 
	}
	return ans;
}

vector<vector<int>> san(int x,int c){ //打三不带 
	vector<vector<int>> ans;
	for(int i=x+1;i<=15;i++){
		vector<int> t;
		if(p[c][i]<3) continue;
		t.push_back(i);t.push_back(i);t.push_back(i);
		ans.push_back(t);
	}
	return ans;
}

vector<vector<int>> sandaiyi(int x,int c){ //打三带一 
	vector<vector<int>> ans;
	for(int i=x+1;i<=15;i++){
		vector<int> t;
		if(p[c][i]<3) continue;
		t.push_back(i);t.push_back(i);t.push_back(i);
		for(int j=1;j<=17;j++){
			if(j==i) continue;
			if(p[c][j]<1) continue;
			auto tt = t;
			tt.push_back(j);
			ans.push_back(tt);
		}
	}
	return ans;
}

vector<vector<int>> sandaidui(int x,int c){ //打三带对 
	vector<vector<int>> ans;
	for(int i=1;i<=15;i++){
		vector<int> t;
		if(p[c][i]<3) continue;
		t.push_back(i);t.push_back(i);t.push_back(i);
		for(int j=1;j<=17;j++){
			if(j==i) continue;
			if(p[c][j]<2) continue;
			auto tt = t;
			tt.push_back(j);tt.push_back(j);
			ans.push_back(tt);
		}
	}
	return ans;
}

vector<vector<int>> tmp;
vector<int> temp;

void dfs(int l,vector<int>& z,int s,int c){
	if(l==0){
		tmp.push_back(temp);
		return;
	}
	if(s==z.size()) return;
	dfs(l,z,s+1,c);
	for(int i=s;i<z.size();i++){
		for(int j=0;j<c;j++)
		temp.push_back(z[i]);
		dfs(l-1,z,s+1,c);
		for(int j=0;j<c;j++)
		temp.pop_back();
	}
}

void feijidan(int l,int r,int e,int c){
	temp.clear();
	tmp.clear();
	for(int i=l;i<=r;i++){
		for(int j=0;j<3;j++) temp.push_back(i);
	}
	vector<vector<int>> ans;
	vector<int> z;
	for(int i=3;i<=17;i++){
		int d = p[c][i];
		if(i>=l&&i<=r) d -= 3;
		for(int j=0;j<d/e;j++) z.push_back(i);
	}
	if(r-l+1>z.size()) return ;
	dfs(l,z,0,e);
	
}

vector<vector<int>> feiji(int x,int len,int type,int c){ //飞机  指定长度，类型  
	vector<vector<int>> ans;
	for(int i=x+1;i<=15;i++){
		vector<int> t;
		if(p[c][i]<3) continue;
		t.push_back(i);t.push_back(i);t.push_back(i);
		for(int j=i+1;j<=15;j++){
			if(p[c][j]<3) break;
			int l = j-i+1;
			if(l!=len) continue;
			t.push_back(j);t.push_back(j);t.push_back(j);
			if(type==0)
			ans.push_back(t);
			if(type==1){
				feijidan(i,j,1,c);
				ans.insert(ans.end(),tmp.begin(),tmp.end());
			}
			if(type==2){
				feijidan(i,j,2,c);
				ans.insert(ans.end(),tmp.begin(),tmp.end());
			}
		}
	}
	return ans;
}

vector<vector<int>> sidai(int x,int c){ //打四带 
	vector<vector<int>> ans;
	for(int i=x+1;i<=15;i++){
		vector<int> t;
		if(p[c][i]<4) continue;
		t.push_back(i);t.push_back(i);t.push_back(i);t.push_back(i); 
		for(int j=1;j<=17;j++){
			if(j==i) continue;
			if(p[c][j]<1) continue;
			t.push_back(j);
			for(int l=j;l<=17;l++){
				if(l==i) continue;
				if(p[c][l]<1) continue;
				if(l==j&&p[c][l]<2) continue;
				t.push_back(l);
				ans.push_back(t);
				t.pop_back();
			}
			t.pop_back();
		}
		
		for(int j=1;j<=17;j++){
			if(j==i) continue;
			if(p[c][j]<2) continue;
			t.push_back(j);t.push_back(j);
			for(int l=j;l<=17;l++){
				if(l==i) continue;
				if(p[c][l]<2) continue;
				if(l==j&&p[c][l]<4) continue;
				t.push_back(l);t.push_back(l);
				ans.push_back(t);
				t.pop_back();t.pop_back();
			}
			t.pop_back();t.pop_back();
		}
	}
	return ans;
}

vector<vector<int>> shunzi(int x,int c){ //打顺子 
	vector<vector<int>> ans;
	for(int i=x+1;i<=10;i++){
		vector<int> t;
		if(p[c][i]<1) continue;
		t.push_back(i);
		for(int j=i+1;j<=14;j++){
			if(p[c][j]==0) break;
			t.push_back(j);
			if(t.size()>=5) ans.push_back(t);
		}
	}
	return ans;
}

vector<vector<int>> liandui(int x,int c){ //打连对 
	vector<vector<int>> ans;
	for(int i=x+1;i<=12;i++){
		vector<int> t;
		if(p[c][i]<2) continue;
		t.push_back(i);t.push_back(i);
		for(int j=i+1;j<=14;j++){
			if(p[c][j]<2) break;
			t.push_back(j);t.push_back(j);
			if(j-i+1>=3) ans.push_back(t);
		}
	}
	return ans;
}

vector<vector<int>> zhadan(int x,int c){ //打炸弹 
	vector<vector<int>> ans;
	for(int i=x+1;i<=15;i++){
		vector<int> t;
		if(p[c][i]<4) continue;
		for(int j=0;j<4;j++) t.push_back(i);
		ans.push_back(t);
	}
	if(x<16&&p[c][16]*p[c][17]) ans.push_back({16,17});
	return ans;
}
string t[] = {"","danpai","duizi","san","sandaiyi","sandaidui","feiji","sidai","shunzi","liandui","zhadan"};
int cnt[2];

int get(int type,vector<int> i){
	if(type==0||type==1||type==2||type==7||type==8||type==9){
		return *min_element(i.begin(),i.end());
	}
	map<int,int> z;
	for(auto& j:i) z[j]++;
	int mn1 = -1,mn2 = -1;
	for(auto it=z.begin();it!=z.end();it++){
		if(it->second==3){
			if(mn1==-1)
			mn1 = it->first;
		}
		if(it->second==4) mn2 = it->first;
	}
	if(type==3||type==4||type>10){
		return mn1;
	}
	if(type==6)
	return mn2;
}

int mytype;
int first = 1;
vector<int> step;
map<pair<vector<int>,vector<int>>,int> dp[2];

int all(int c,int fst);

int slv(int c,int type,int x,int fst){
//	cout << "c: " << c << "\n";

	vector<int> fg[2];
	for(int h=0;h<2;++h){
		for(auto it=p[h].begin();it!=p[h].end();it++){
			//cout << it->first << " " << it->second << " ";
			for(int l=0;l<it->second;l++) fg[h].push_back(it->first);
		}
		sort(fg[h].begin(),fg[h].end());
	}
//	cout << "\n";
	int res = 1;
	if(type==-1){
		if(fst==0&&dp[c].count({fg[0],fg[1]})) return dp[c][{fg[0],fg[1]}];
		res &= all(c,fst);
		if(dp[c].size()<1e6)
		dp[c][{fg[0],fg[1]}] = 1-res;
		//cout << "res: " << res << "\n";
	} else{
		vector<vector<int>> ans;
		switch(type){
			case 0:
				ans = danpai(x,c);
				break;
			case 1:
				ans = duizi(x,c);
				break;
			case 2:
				ans = san(x,c);
				break;
			case 3:
				ans = sandaiyi(x,c);
				break;
			case 4:
				ans = sandaidui(x,c);
				break;
			case 6:
				ans = sidai(x,c);
				break;
			case 7:
				ans = shunzi(x,c);
				break;
			case 8:
				ans = liandui(x,c);
				break;
			case 9:
				ans = zhadan(x,c);
				break;
			default:
				int i = type%10,j = type/10;
				ans = feiji(x,i,j,c);
		}
		if(type!=9) {
			auto z = zhadan(0,c);
			//print(z);
			for(auto& i:z){
				for(auto& j:i){
					p[c][j]--;
				}
				cnt[c] -= i.size();
				if(cnt[c]==0) res = 0;
				else res &= slv(1-c,9,get(9,i),0);
				cnt[c] += i.size();
				for(auto& j:i){
					p[c][j]++;
				}
				if(fst&&res==0) step = i,mytype = 9; 
				if(res==0) return 1;
			}
		}
		for(auto& i:ans){
			for(auto& j:i){
				p[c][j]--;
			}
			cnt[c] -= i.size();
			if(cnt[c]==0) res = 0;
			else res &= slv(1-c,type,get(type,i),0);
			cnt[c] += i.size();
			for(auto& j:i){
				p[c][j]++;
			}
			if(fst&&res==0) step = i,mytype = type; 
			if(res==0) return 1;
		}
		if(fst==0)
		res &= slv(1-c,-1,-1,0);//不要 
		//cout << "res: " << res << " " << x  << "\n";
		if(res==0) return 1;
	}
	return 1-res;
}

int all(int c,int fst){
	int ans = 1;
	auto z = danpai(0,c);
	for(auto& i:z){
		for(auto& j:i){
			p[c][j]--;
		}
		cnt[c] -= i.size();
		if(cnt[c]==0) ans = 0;
		else ans &= slv(1-c,0,i[0],0);
		cnt[c] += i.size();
		for(auto& j:i){
			p[c][j]++;
		}
		if(fst&&ans==0) step = i,mytype = 0; 
		if(ans==0) return 0;
	}
	//cout << ans << "\n";
	z = duizi(0,c);
	for(auto& i:z){
		for(auto& j:i){
			p[c][j]--;
		}
		cnt[c] -= i.size();
		if(cnt[c]==0) ans = 0;
		else ans &= slv(1-c,1,i[0],0);
		cnt[c] += i.size();
		for(auto& j:i){
			p[c][j]++;
		}
		if(fst&&ans==0) step = i,mytype = 1; 
		if(ans==0) return 0;
	}
	//cout << ans << "\n";
	z = san(0,c);
	for(auto& i:z){
		for(auto& j:i){
			p[c][j]--;
		}
		cnt[c] -= i.size();
		if(cnt[c]==0) ans = 0;
		else ans &= slv(1-c,2,i[0],0);
		cnt[c] += i.size();
		for(auto& j:i){
			p[c][j]++;
		}
		if(fst&&ans==0) step = i,mytype = 2; 
		if(ans==0) return 0;
	}
	z = sandaiyi(0,c);
	for(auto& i:z){
		int mn = 20;
		int prev = -1;
		for(auto& j:i){
			p[c][j]--;
			if(j==prev) mn = prev;
			prev = j;
		}
		cnt[c] -= i.size();
		if(cnt[c]==0) ans = 0;
		else ans &= slv(1-c,3,mn,0);
		cnt[c] += i.size();
		for(auto& j:i){
			p[c][j]++;
		}
		if(fst&&ans==0) step = i,mytype = 3; 
		if(ans==0) return 0;
	}
	z = sandaidui(0,c);
	for(auto& i:z){
		int mn = 0;
		for(auto& j:i){
			p[c][j]--;
			mn ^= j;
		}
		cnt[c] -= i.size();
		if(cnt[c]==0) ans = 0;
		else ans &= slv(1-c,4,mn,0);
		cnt[c] += i.size();
		for(auto& j:i){
			p[c][j]++;
		}
		if(fst&&ans==0) step = i,mytype = 4; 
		if(ans==0) return 0;
	}
	for(int ii=2;ii<=5;ii++){
		for(int jj=0;jj<3;jj++){
			z = feiji(0,ii,jj,c);
			for(auto& i:z){
				int w;
				map<int,int> mn;
				for(auto& j:i){
					p[c][j]--;
					mn[j]++;
				}
				for(auto it=mn.begin();it!=mn.end();it++){
					if(it->second==3) {
						w = it->first;
						break;
					}
				}
				cnt[c] -= i.size();
				if(cnt[c]==0) ans = 0;
				else ans &= slv(1-c,ii + 10*jj,w,0);
				cnt[c] += i.size();
				for(auto& j:i){
					p[c][j]++;
				}
				if(fst&&ans==0) step = i,mytype = 5; 
				if(ans==0) return 0;
			}
		}
	}
	z = sidai(0,c);
	for(auto& i:z){
		int ans;
		map<int,int> mn;
		for(auto& j:i){
			p[c][j]--;
			mn[j]++;
		}
		for(auto it=mn.begin();it!=mn.end();it++){
			if(it->second==4) {
				ans = it->first;
				break;
			}
		}
		cnt[c] -= i.size();
		if(cnt[c]==0) ans = 0;
		else ans &= slv(1-c,6,ans,0);
		cnt[c] += i.size();
		for(auto& j:i){
			p[c][j]++;
		}
		if(fst&&ans==0) step = i,mytype = 6; 
		if(ans==0) return 0;
	}
	z = shunzi(0,c);
	for(auto& i:z){
		int mn = 20;
		for(auto& j:i){
			p[c][j]--;
			mn = min(mn,j);
		}
		cnt[c] -= i.size();
		if(cnt[c]==0) ans = 0;
		else ans &= slv(1-c,7,mn,0);
		cnt[c] += i.size();
		for(auto& j:i){
			p[c][j]++;
		}
		if(fst&&ans==0) step = i,mytype = 7; 
		if(ans==0) return 0;
	}
	//cout << ans << "\n";
	z = liandui(0,c);
	//print(z);
	for(auto& i:z){
		int mn = 20;
		for(auto& j:i){
			mn = min(mn,j);
			p[c][j]--;
		}
		cnt[c] -= i.size();
		if(cnt[c]==0) ans = 0;
		else ans &= slv(1-c,8,mn,0);
		cnt[c] += i.size();
		for(auto& j:i){
			p[c][j]++;
		}
		if(fst&&ans==0) step = i,mytype = 8; 
		if(ans==0) return 0;
	}
	//cout << ans << "\n";
	z = zhadan(0,c);
	for(auto& i:z){
		for(auto& j:i){
			p[c][j]--;
		}
		cnt[c] -= i.size();
		if(cnt[c]==0) ans = 0;
		else ans &= slv(1-c,9,i[0],0);
		cnt[c] += i.size();
		for(auto& j:i){
			p[c][j]++;
		}
		if(fst&&ans==0) step = i,mytype = 9; 
		if(ans==0) return 0;
	}
	//cout << ans << "\n";
	return ans;
}

bool isboom(vector<int> z){
	if(z.size()==2){
		if(z[0]>z[1]) swap(z[0],z[1]);
		if(z[0]==16&&z[1]==17) return 1;
	}
	if(z.size()==4&&z[0]==z[1]&&z[0]==z[2]&&z[0]==z[3]) return 1;
	return 0;
}

bool isliandui(vector<int> z){
	int mn = z[0],mx = z.back();
	if(n!=(mx-mn+1)*2) return 0;
	for(int i=0;i<n;i++){
		if(z[i]!=mn+i/2) return 0;
	}
	return 1;
}

bool isshunzi(vector<int> z){
	int mn = z[0],mx = z.back();
	if(n!=(mx-mn+1)) return 0;
	for(int i=0;i<n;i++){
		if(z[i]!=mn+i) return 0;
	}
	return 1;
}

bool issidai(vector<int> z){
	map<int,int> zz;
	for(auto& i:z) zz[i]++;
	int f = 0;
	for(auto it=zz.begin();it!=zz.end();it++){
		if(it->second==4){
			f = 1;
			break;
		}
		if(it->second==3) return 0; 
	}
	if(f==0) return 0;
	if(zz.size()==3) return 1;
	return 0;
}

bool issandaiyi(vector<int> z){
	if(z.size()!=4) return 0;
	map<int,int> zz;
	for(auto& i:z) zz[i]++;
	return z.size()==2;
}

bool issandaidui(vector<int> z){
	if(z.size()!=5) return 0;
	map<int,int> zz;
	for(auto& i:z) zz[i]++;
	return z.size()==2;
}

int findtype(vector<int> z){
	int n = z.size();
	if(n==1) return 0;
	if(n==2) return 1;
	if(n==3) return 2;
	if(isboom(z)) return 9;
	if(isliandui(z)) return 8;
	if(isshunzi(z)) return 7;
	if(issidai(z)) return 6;
	if(issandaiyi(z)) return 3;
	if(issandaidui(z)) return 4;
	return 5;
}

void solve()
{
	cin >> n >> m;
	vector<int> a(n),b(m);
	for(auto& i:a) cin >> i,p[0][i]++;
	for(auto& i:b) cin >> i,p[1][i]++;
	cnt[0] = n;cnt[1] = m;
	//cout << slv(0,-1,-1) << "\n";
	int x = slv(0,-1,-1,1);
	first = 0;
	if(!x) {
		cout << "无解！\n";
		return;
	}
	while(cnt[0]){
		if(step.size()==0){
			cout << "不要！\n";
		} else{
			cout << "出这个，稳了！\n";
			for(auto& i:step){
				cout << i << " ";
				p[0][i]--;
			}
			cout << "\n";
			cnt[0] -= step.size();
		}
		step.clear();
		if(cnt[0]==0){
			cout << "你赢了\n";
			return;
		}
		cin >> k;
		vector<int> ds(k);
		for(auto& i:ds) cin >> i;
		if(k==0) slv(0,-1,-1,1);
		else{
			sort(ds.begin(),ds.end());
			mytype = findtype(ds);
			for(auto& i:ds){
				p[1][i]--;
			}
			cnt[1] -= ds.size();
			if(isboom(ds)){
				slv(0,9,ds[0],1);
			} else{
				slv(0,mytype,get(mytype,ds),1);
			}
		}
	}
}
int main()
{
	//ios::sync_with_stdio(0);
	//cin.tie(0);
	int T = 1;
	//cin >> T;
	while(T--) solve();
} 
/*
12 13
3 4 4 4 6 6 7 7 8 8 13 15
4 7 9 10 10 12 12 12 13 14 14 16 17

10 9
4 6 6 7 7 8 8 12 13 15
3 3 4 4 5 5 12 13 15

9 6
4 5 5 6 7 7 10 11 14
5 6 6 9 11 11

10 7
3 3 4 8 8 9 11 12 13 16
6 6 7 11 11 12 15

12 11
3 3 4 5 6 9 9 12 13 15 16 17
5 7 9 10 10 11 11 12 13 14 15

11 9
4 5 5 7 7 8 11 11 12 13 13
3 3 5 8 11 11 12 14 15

12 12
3 3 4 5 5 7 8 10 10 12 12 14
3 4 4 5 7 8 8 8 10 13 14 17
*/
