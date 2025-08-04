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
unordered_map<char, set<string>> domains;
unordered_map<char, string> assignment;
set<char> all_nodes;

bool ac3(queue<pair<char, char>> &q)
{
    while (!q.empty())
    {
        auto it = q.front();
        q.pop();
        char xi = it.first;
        char xj = it.second;

        bool revised = false;
        set<string> to_remove;

        for (const string &val_i : domains[xi])
        {
            bool has_support = false;
            for (const string &val_j : domains[xj])
            {
                if (val_i != val_j)
                {
                    has_support = true;
                    break;
                }
            }
            if (!has_support)
                to_remove.insert(val_i);
        }

        if (!to_remove.empty())
        {
            for (const string &v : to_remove)
                domains[xi].erase(v);
            revised = true;
        }

        if (domains[xi].empty())
            return false;

        if (revised)
        {
            for (char xk : neighbors[xi])
            {
                if (xk != xj)
                    q.push({xk, xi});
            }
        }
    }
    return true;
}

bool ac3_init()
{
    queue<pair<char, char>> q;
    for (auto it : neighbors)
    {
        char xi = it.first;
        const vc &list = it.second;
        for (char xj : list)
        {
            q.push({xi, xj});
        }
    }
    return ac3(q);
}

bool isConsistent(char var, const string &value)
{
    for (char neighbor : neighbors[var])
    {
        if (assignment.count(neighbor) && assignment[neighbor] == value)
            return false;
    }
    return true;
}

bool backtrack()
{
    if (assignment.size() == all_nodes.size())
        return true;

    char var = 0;
    size_t min_size = 1000;
    for (char c : all_nodes)
    {
        if (!assignment.count(c) && domains[c].size() < min_size)
        {
            min_size = domains[c].size();
            var = c;
        }
    }

    if (var == 0)
        return false;

    set<string> domain_copy = domains[var];

    for (const string &value : domain_copy)
    {
        if (isConsistent(var, value))
        {
            assignment[var] = value;

            unordered_map<char, set<string>> domains_backup = domains;

            for (char neighbor : neighbors[var])
            {
                domains[neighbor].erase(value);
            }

            if (ac3_init() && backtrack())
                return true;

            domains = domains_backup;
            assignment.erase(var);
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

        for (char node : all_nodes)
        {
            domains[node] = set<string>(all(COLORS));
        }

        if (!ac3_init())
        {
            cout << "No valid assignment possible" << endl;
            return 0;
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
