#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

struct Human {
    int r, c;
    int dR, dC;
    bool arrive;
};

int n, m;
int curM;
int map[17][17];
int traceR[17][17];
int traceC[17][17];
bool visit[17][17];
int dy[4] = {-1, 0, 0, 1};
int dx[4] = {0, -1, 1, 0};
unordered_map<int, Human> H;
unordered_map<int, pair<int, int>> B;

void printMap(int a[][17]) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    return;
}

void initMap() {
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 17; j++) {
            map[i][j] = -1;
        }
    }

    return;
}

void initVisit() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            visit[i][j] = false;
        }
    }

    return;
}

void move(int t) {
    int I = min(t, m + 1);

    // printMap(map);
    
    for (int i = 1; i < I; i++) {
        if (H[i].arrive) continue;

        initVisit();

        int curR, curC;

        queue<pair<int, int>> q;

        q.push(make_pair(H[i].r, H[i].c));

        visit[H[i].r][H[i].c] = true;

        while (!q.empty()) {
            curR = q.front().first;
            curC = q.front().second;
            q.pop();

            if (curR == H[i].dR && curC == H[i].dC) {
                break;
            }

            for (int j = 0; j < 4; j++) {
                int ny = curR + dy[j];
                int nx = curC + dx[j];

                if (map[ny][nx] != 0) continue;
                if (visit[ny][nx]) continue;

                q.push(make_pair(ny, nx));
                visit[ny][nx] = true;
                traceR[ny][nx] = curR;
                traceC[ny][nx] = curC;
            }
        }

        // printMap(traceR);
        // printMap(traceC);

        curR = H[i].dR;
        curC = H[i].dC;

        while (1) {
            int ny = traceR[curR][curC];
            int nx = traceC[curR][curC];

            if (ny == H[i].r && nx == H[i].c) {
                H[i].r = curR;
                H[i].c = curC;
                // cout << i << curR << curC << endl;
                break;
            }

            curR = ny;
            curC = nx;
        }
    }

    return;
}

void checkArrive(int t) {
    int I = min(t, m + 1);

    for (int i = 1; i < I; i++) {
        if (H[i].arrive) continue;
        if (H[i].r == H[i].dR && H[i].c == H[i].dC) {
            // cout << i << " arrive" << endl;
            H[i].arrive = true;
            map[H[i].r][H[i].c] = -1;
            curM--;
        }
    }

    return;
}

int main() {
    cin >> n >> m;

    curM = m;

    int b = 0;

    initMap();

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> map[i][j];
            if (map[i][j] == 1) {
                b++;
                B[b] = make_pair(i, j);
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        int a, b;

        cin >> a >> b;

        H[i] = {16, 16, a, b, false};
    }

    // printMap(map);

    int t = 1;

    while (1) {
        move(t);

        checkArrive(t);

        if (curM == 0) break;

        if (t > m) continue;

        int min = 100;
        int idx = 0;
        for (int i = 1; i <= b; i++) {
            int dis = abs(H[t].dR - B[i].first) + abs(H[t].dC - B[i].second);
            if (dis < min) {
                min = dis;
                H[t].r = B[i].first;
                H[t].c = B[i].second;
                idx = i;
            }
            else if (dis == min) {
                if (B[i].second < H[t].c) {
                    min = dis;
                    H[t].r = B[i].first;
                    H[t].c = B[i].second;
                    idx = i;
                }
            }
        }
        map[H[t].r][H[t].c] = -1;
        B.erase(idx);        

        t++;
    }

    // printMap(map);

    cout << t << endl;
    
    return 0;
}