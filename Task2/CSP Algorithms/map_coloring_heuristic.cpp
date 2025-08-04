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

bool isConsistent(char var, const string &value)
{
    for (char neighbor : neighbors[var])
    {
        if (assignment.count(neighbor) && assignment[neighbor] == value)
            return false;
    }
    return true;
}

char selectUnassignedVariable()
{
    char best_var = 0;
    size_t min_domain_size = 1000;
    int max_degree = -1;

    for (char var : all_nodes)
    {
        if (assignment.count(var))
            continue;

        size_t domain_size = domains[var].size();
        int degree = neighbors[var].size();

        if (domain_size < min_domain_size ||
            (domain_size == min_domain_size && degree > max_degree))
        {
            min_domain_size = domain_size;
            max_degree = degree;
            best_var = var;
        }
    }

    return best_var;
}

vector<string> orderDomainValues(char var)
{
    map<string, int> constraint_count;
    for (const string &val : domains[var])
    {
        int count = 0;
        for (char neighbor : neighbors[var])
        {
            if (!assignment.count(neighbor) && domains[neighbor].count(val))
                count++;
        }
        constraint_count[val] = count;
    }

    vector<pair<string, int>> ordered(constraint_count.begin(), constraint_count.end());
    sort(all(ordered), [](const auto &a, const auto &b)
         { return a.second < b.second; });

    vector<string> result;
    for (auto &it : ordered)
        result.pb(it.first);
    return result;
}

bool backtrack()
{
    if (assignment.size() == all_nodes.size())
        return true;

    char var = selectUnassignedVariable();
    if (var == 0)
        return false;

    vector<string> values = orderDomainValues(var);
    for (const string &value : values)
    {
        if (isConsistent(var, value))
        {
            assignment[var] = value;

            unordered_map<char, set<string>> domains_backup = domains;
            for (char neighbor : neighbors[var])
            {
                domains[neighbor].erase(value);
            }

            if (backtrack())
                return true;

            assignment.erase(var);
            domains = domains_backup;
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

        if (backtrack())
        {
            cout << "Solution found:\n";
            for (auto it : assignment)
            {
                cout << it.first << " -> " << it.second << endl;
            }
        }
        else
        {
            cout << "No valid coloring exists.\n";
        }
    }
}
