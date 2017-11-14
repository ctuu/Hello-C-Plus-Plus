#include <algorithm>
#include <array>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int N = 1e6 + 7;
const int M = 1e6 + 7;
const long long INF = (long long)1 << 62;
using G = vector<vector<int>>; //save index
array<long long, N> d, cd;
array<int, M> pth;
struct Node
{
    long long d;
    int u;
    Node(long long d, int u) : d(d), u(u) {}
    bool operator<(const Node &a) const { return d > a.d; }
};
struct Edge
{
    int fr, to;
    long long di;
    Edge() = default;
    Edge(int u, int v, long long w) : fr(u), to(v), di(w) {}
};
using E = vector<Edge>;
void dijkstra(G &gr, E &edg, int s)
{
    priority_queue<Node> pq;
    pq.push(Node(0, s));
    while (!pq.empty())
    {
        Node x = pq.top();
        pq.pop();
        int u = x.u;
        if (cd[u] < x.d)
            continue;
        for (auto i : gr[u])
        {
            Edge &e = edg[i];
            int to = (e.fr == u) ? e.to : e.fr;
            long long tc = x.d + e.di;
            if (d[to] >= tc)
            {
                swap(tc, d[to]);
                pth[to] = i;
                pq.push(Node(d[to], to));
            }
            if (cd[to] >= tc && d[to] <= tc)
            {
                cd[to] = tc;
                pq.push(Node(cd[to], to));
            }
        }
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        G gr;
        E edg;
        gr.resize(n + 1);
        edg.resize(m + 1);
        for (int i = 0; i < m; ++i)
        {
            int fr, to;
            long long di;
            cin >> fr >> to >> di;
            edg[i] = Edge(fr, to, di);
            gr[fr].push_back(i);
            gr[to].push_back(i); // if Two-Way
        }
        d.fill(INF);
        cd.fill(INF);
        d[1] = 0;
        dijkstra(gr, edg, 1);
        cout << cd[n] << endl;
    }
    return 0;
}