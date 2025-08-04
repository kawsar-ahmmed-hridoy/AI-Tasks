#include <bits/stdc++.h>
using namespace std;
/*#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T>using pbds=tree<T,null_type, less <T>,rb_tree_tag,tree_order_statistics_node_update>;
// less_equal=for ordered multiset.
#define ofk(x) order_of_key(x)//returns number of item stricly smaller than k;
#define fbk(x) find_by_order(x)//return x'th element & count from 0.*/
#define ll long long int
#define vi vector<ll>
#define vc vector<char>
#define ump unordered_map<ll, int>
#define ump2 unordered_map<char, int>
#define pi pair<ll, ll>
#define vp vector<pair<ll, ll>>
#define faster_hridoy            \
    ios::sync_with_stdio(false); \
    cin.tie(NULL);               \
    cout.tie(NULL)
#define yes cout << "Yes\n"
#define no cout << "No\n"
#define rep(i, d, n) for (auto i = d; i < n; i++)
#define pb push_back
#define ft first
#define sd second
#define lcm(a, b) (a * b / __gcd(a, b))
#define rall(a) (a).rbegin(), (a).rend()
#define all(a) (a).begin(), (a).end()
#define mem(x, a) memset(x, a, sizeof(x))
#define input(a)       \
    for (auto &it : a) \
    cin >> it
#define print(a)          \
    for (auto &x : a)     \
    {                     \
        cout << x << ' '; \
    }                     \
    cout << endl
#define endl '\n'
#define PI 3.1415926535897932384
const ll sz = 1e5 + 7;
const int MX = 1e9 + 7;
const ll inf = 1e18 + 7;
const ll mod = 998244353;
// if(x&1==1)odd else even
// if(x&(x-1)==0)power of two else not.(00100-1=00011&00100=00000)
bool dls(char cur, char dst, int lim, unordered_map<char, vc> &adj, unordered_map<char, char> &par, unordered_set<char> &vis){
    if(cur==dst)return 1;
    if(lim==0)return 0;
    vis.insert(cur);
    for(char it:adj[cur]){
        if(!vis.count(it)){
            par[it]=cur;
            if(dls(it,dst,lim-1,adj,par,vis))return 1;
        }
    }
    return 0;
}

void ids(unordered_map<char,vc> &adj, char src, char dst, int mxdpth){
    for(int j=0;j<=mxdpth;j++){
        unordered_map<char, char> par;
        unordered_set<char> vis;

        bool flag=dls(src,dst,j,adj,par,vis);

        if(flag){
            vc path;
            char xn=dst;
            while(xn!=src){
                path.pb(xn);
                xn=par[xn];
            }
            path.pb(src);
            reverse(all(path));

            cout<<"IDS path: ";
            for(int i=0; i<path.size(); i++){
                cout<<path[i];
                if(i+1<path.size())cout<< " -> ";
            }
            cout<<endl;
            return;
        }
    }
    cout << "Not reachable."<<endl;
}
int main(){
    faster_hridoy;
    int n;
    cin >> n;
    unordered_map<char, vc> adj;
    for(int i=0;i<n;i++){
        char u,v;
        cin >>u>>v;
        adj[u].pb(v);
    }

    char src,dst;
    int mxdpth;
    cin>>src>>dst>>mxdpth;
    ids(adj,src,dst,mxdpth);
}
