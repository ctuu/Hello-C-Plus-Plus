#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int N = 220;
const int INF = 0x3f3f3f3f;
struct Po
{
    int x, y, s;
    Po(int x, int y, int s) : x(x), y(y), s(s) {}
};
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    char mz[N][N];
    bool vn[N][N], vm[N][N];
    int sn[N][N];
    while (cin >> n >> m)
    {
        for(int i = 0; i< N; ++i)
            for(int j = 0; j < N; ++j)
            {
                vn[i][j] = vm[i][j] = 0;
                sn[i][j] = INF;
            }
        queue<Po> fn, fm;
        int ans = INF;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
            {
                cin >> mz[i][j];
                if (mz[i][j] == 'Y')
                {
                    fn.push(Po(i, j, 0));
                    vn[i][j] = 1;
                }
                if (mz[i][j] == 'M')
                {
                    fm.push(Po(i, j, 0));
                    vm[i][j] = 1;
                }
                if(mz[i][j] == '#')
                    vm[i][j] = vn[i][j] = 1;
            }
        while (!fn.empty())
        {
            Po cu = fn.front();
            fn.pop();
            int &cx = cu.x, &cy = cu.y, &cs = cu.s;
            if (mz[cx][cy] == '@')
                sn[cx][cy] = min(sn[cx][cy],cs);
            int t[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
            for (auto i : t)
                if (cx + i[0] < n && cx + i[0] > -1 && cy + i[1] < m && cy + i[1] > -1)
                    if (!vn[cx + i[0]][cy + i[1]])
                    {
                        fn.push(Po(cx + i[0], cy + i[1], cs + 1));
                        vn[cx + i[0]][cy + i[1]] = 1;
                    }
        }
        while (!fm.empty())
        {
            Po cu = fm.front();
            fm.pop();
            int &cx = cu.x, &cy = cu.y, &cs = cu.s;
            if (mz[cx][cy] == '@')
                ans = min(ans, sn[cx][cy] + cs);
            int t[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
            for (auto i : t)
                if (cx + i[0] < n && cx + i[0] > -1 && cy + i[1] < m && cy + i[1] > -1)
                    if (!vm[cx + i[0]][cy + i[1]])
                    {
                        fm.push(Po(cx + i[0], cy + i[1], cs + 1));
                        vm[cx + i[0]][cy + i[1]] = 1;
                    }
        }
        cout << ans * 11 << endl;
    }
    return 0;
}