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

int N;
vi board;
vector<set<int>> conflict_sets;
bool solution_found = false;

bool isSafe(int row, int col)
{
    for (int prev = 0; prev < row; prev++)
    {
        if (board[prev] == col || abs(prev - row) == abs(board[prev] - col))
            return false;
    }
    return true;
}

set<int> getConflictRows(int row, int col)
{
    set<int> conflict;
    for (int prev = 0; prev < row; prev++)
    {
        if (board[prev] == col || abs(prev - row) == abs(board[prev] - col))
            conflict.insert(prev);
    }
    return conflict;
}

int backjump(int row)
{
    if (row == N)
    {
        solution_found = true;
        return -1;
    }

    for (int col = 0; col < N; col++)
    {
        set<int> conflict = getConflictRows(row, col);

        if (conflict.empty())
        {
            board[row] = col;
            conflict_sets[row].clear();
            int result = backjump(row + 1);
            if (solution_found)
                return -1;
            if (result == -1)
                continue;
            if (result < row)
                return result;
            conflict_sets[row].insert(result);
        }
        else
        {
            conflict_sets[row].insert(all(conflict));
        }
    }

    if (conflict_sets[row].empty())
        return row - 1;
    return *conflict_sets[row].rbegin();
}

int main()
{
    faster_hridoy;
    int t = 1;
    // cin>>t;
    while (t--)
    {
        cout << "Enter number of queens: ";
        cin >> N;

        board.assign(N, -1);
        conflict_sets.resize(N);

        backjump(0);

        if (solution_found)
        {
            cout << "One valid solution to " << N << "-Queens:\n";
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    cout << (board[i] == j ? "Q " : ". ");
                }
                cout << "\n";
            }
        }
        else
        {
            cout << "No solution found.\n";
        }
    }
}
