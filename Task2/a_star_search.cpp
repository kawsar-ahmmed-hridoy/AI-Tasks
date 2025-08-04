#include <bits/stdc++.h>
using namespace std;
// #include<ext/pb_ds/assoc_container.hpp>
// #include<ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// template<class T>using pbds=tree<T,null_type, less <T>,rb_tree_tag,tree_order_statistics_node_update>;
// #define ofk(x) order_of_key(x)
// #define fbk(x) find_by_order(x)
#define ll long long int
#define vi vector<ll>
#define vc vector<char>
#define ump unordered_map<ll, ll>
#define ump2 unordered_map<char, ll>
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

void aStarSearch(unordered_map<char, vp> &adj, ump2 &h, char start, char goal, set<char> &nodes){

    ump2 g;
    unordered_map<char, char> parent;
    set<char> visited;

    for (char c : nodes)
        g[c] = inf;
    g[start] = 0;
    priority_queue<vi, vector<vi>, greater<>> pq;
    pq.push({h[start], 0, (ll)start, -1});

    while (!pq.empty())
    {
        vi curr = pq.top();
        pq.pop();

        ll f = curr[0];
        ll curr_g = curr[1];
        char u = (char)curr[2];
        char par = (char)curr[3];

        if (visited.count(u))
            continue;
        visited.insert(u);
        parent[u] = par;

        if (u == goal)
            break;

        for (auto edge : adj[u])
        {
            ll cost = edge.first;
            char v = (char)edge.second;

            if (visited.count(v))
                continue;
            ll new_g = g[u] + cost;
            if (new_g < g[v])
            {
                g[v] = new_g;
                ll f_new = new_g + h[v];
                pq.push({f_new, new_g, (ll)v, (ll)u});
            }
        }
    }

    if (!visited.count(goal))
    {
        cout << "Not reachable." << endl;
    }
    else
    {
        vc path;
        char cur = goal;
        while (cur != start)
        {
            path.pb(cur);
            cur = parent[cur];
        }
        path.pb(start);
        reverse(all(path));

        cout << "Path: ";
        rep(i, 0, path.size())
        {
            cout << path[i];
            if (i + 1 < path.size())
                cout << " -> ";
        }
        cout << endl;
        cout << "Total Cost: " << g[goal] << endl;
    }
}

int main()
{
    faster_hridoy;
    int t = 1;
    // cin>>t;
    while (t--)
    {
        ll n, m;
        cout << "Enter number of nodes and edges: ";
        cin >> n >> m;

        unordered_map<char, vp> adj;
        set<char> nodes;

        cout << "Enter: from to cost" << endl;
        rep(i, 0, m)
        {
            char u, v;
            ll w;
            cin >> u >> v >> w;
            adj[u].pb({w, v});
            adj[v].pb({w, u});
            nodes.insert(u);
            nodes.insert(v);
        }

        unordered_map<char, ll> h;
        cout << "Enter heuristic values of " << (ll)nodes.size() << " cities: city val" << endl;
        for (ll i = 0; i < (ll)nodes.size(); i++)
        {
            char city;
            ll val;
            cin >> city >> val;
            h[city] = val;
        }

        char start, goal;
        cout << "Enter start and goal node: ";
        cin >> start >> goal;

        aStarSearch(adj, h, start, goal, nodes);
    }
}
