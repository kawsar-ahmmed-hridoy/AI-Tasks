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
#define vs vector<string>
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

const vs COLORS = {"Red", "Green", "Blue"};
unordered_map<char, vc> neighbors;
unordered_map<char, string> assignment;
set<char> all_nodes;

bool isSafe(char node, const string &color)
{
    for (char neighbor : neighbors[node])
    {
        if (assignment.count(neighbor) && assignment[neighbor] == color)
            return false;
    }
    return true;
}

bool backtrack()
{
    if (assignment.size() == all_nodes.size())
        return true;

    for (char node : all_nodes)
    {
        if (!assignment.count(node))
        {
            for (const string &color : COLORS)
            {
                if (isSafe(node, color))
                {
                    assignment[node] = color;

                    if (backtrack())
                        return true;

                    assignment.erase(node);
                }
            }
            return false;
        }
    }
    return false;
}

int main()
{
    faster_hridoy;
    int t = 1;
    // cin>>t;
    while (t--)
    {
        ll n, e;
        cout << "Enter number of nodes and edges: ";
        cin >> n >> e;

        cout << "Enter edges in format: u v" << endl;
        rep(i, 0, e)
        {
            char u, v;
            cin >> u >> v;
            neighbors[u].pb(v);
            neighbors[v].pb(u);
            all_nodes.insert(u);
            all_nodes.insert(v);
        }

        if (backtrack())
        {
            cout << "Solution exists:\n";
            for (auto it : assignment)
            {
                char city = it.first, color = it.second[0];
                cout << city << " -> " << color << endl;
            }
        }
        else
        {
            cout << "No valid coloring exists.\n";
        }
    }
}
