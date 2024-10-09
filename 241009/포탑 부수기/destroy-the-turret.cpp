#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N, M, K;
int map[12][12] = { 0, };
int record[12][12] = { 0, };
bool visit[12][12] = { 0, };
bool trace[12][12] = { 0, };
int dy[8] = {0, 1, 0, -1, 1, 1, -1, -1};
int dx[8] = {1, 0, -1, 0, 1, -1, 1, -1};
int Ra, Ca;
int Da;
int Rv, Cv;
int Dv;
int traceR[12][12] = { 0, };
int traceC[12][12] = { 0, };


void printMap(int a[][12]) {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cout << a[i][j] << " "; 
        }
        cout << endl;
    }
    cout << endl;

    return;
}

void initVisit() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            visit[i][j] = false;
            trace[i][j] = false;
        }
    }

    return;
}

bool findRoute() {
    bool attack = false;

    int curR = Ra;
    int curC = Ca;

    queue<pair<int, int>> q;
    q.push(make_pair(curR, curC));
    visit[curR][curC] = true;

    while (!q.empty()) {
        curR = q.front().first;
        curC = q.front().second;
        q.pop();

        if (curR == Rv && curC == Cv) {
            attack = true;            
            break;
        }

        for (int i = 0; i < 4; i++) {
            int ny = curR + dy[i];
            int nx = curC + dx[i];

            if (ny == N + 1) ny = 1;
            else if (ny == 0) ny = N;
            if (nx == M + 1) nx = 1;
            else if (nx == 0) nx = M;

            if (map[ny][nx] != 0 && !visit[ny][nx]) {
                q.push(make_pair(ny, nx));
                traceR[ny][nx] = curR;
                traceC[ny][nx] = curC;
                visit[ny][nx] = true;
            }
        }
    }

    if (attack) {
        // cout << Rv << " " << Cv << endl;

        map[Rv][Cv] -= Da;
        if (map[Rv][Cv] < 0) map[Rv][Cv] = 0;

        curR = traceR[Rv][Cv];
        curC = traceC[Rv][Cv];
        while(!(curR == Ra && curC == Ca)) {
            // cout << curR << " " << curC << endl;

            map[curR][curC] -= Da / 2;
            if (map[curR][curC] < 0) map[curR][curC] = 0;
            trace[curR][curC] = true;

            int ny = traceR[curR][curC];
            int nx = traceC[curR][curC];

            curR = ny;
            curC = nx;
        }
    }

    return attack;
}

void attack() {
    initVisit();

    trace[Ra][Ca] = true;
    trace[Rv][Cv] = true;

    if (!findRoute()) {
        map[Rv][Cv] -= Da;
        if (map[Rv][Cv] < 0) map[Rv][Cv] = 0;

        for (int i = 0; i < 8; i++) {
            int ny = Rv + dy[i];
            int nx = Cv + dx[i];

            if (ny == Ra && nx == Ca) continue;

            if (ny == N + 1) ny = 1;
            else if (ny == 0) ny = N;
            if (nx == M + 1) nx = 1;
            else if (nx == 0) nx = M;

            map[ny][nx] -= Da / 2;
            if (map[ny][nx] < 0) map[ny][nx] = 0;
            trace[ny][nx] = true;
        }
    }

    return;
}

int main() {
    cin >> N >> M >> K;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            int n;
            cin >> n;

            map[i][j] = n;
        }
    }

    for (int k = 1; k <= K; k++) {
        // cout << k << k << k << k << endl << endl;

        Ra = -1, Ca = -1;
        Da = 10000000;
        Rv = -1, Cv = -1;
        Dv = 0;

        for (int j = M; j > 0; j--) {
            for (int i = N; i > 0; i--) {
                if (map[i][j] == 0) continue;
                if (map[i][j] < Da) {
                    Ra = i;
                    Ca = j;
                    Da = map[i][j];
                }
                if (map[i][j] == Da) {
                    if (record[i][j] > record[Ra][Ca]) {
                        Ra = i;
                        Ca = j;
                        Da = map[i][j];
                    }
                }
            }
        }

        for (int j = 1; j <= M; j++) {
            for (int i = 1; i <= N; i++) {
                if (map[i][j] == 0) continue;
                if (Ra == i && Ca == j) continue;
                if (map[i][j] > Dv) {
                    Rv = i;
                    Cv = j;
                    Dv = map[i][j];
                }
                if (map[i][j] == Dv) {
                    if (record[i][j] < record[Rv][Cv]) {
                        Rv = i;
                        Cv = j;
                        Dv = map[i][j];
                    }
                }
            }
        }

        // cout << Ra << " " << Ca << " " << Rv << " " << Cv << endl;

        if (Rv == -1 && Cv == -1) {
            break;
        }

        Da += N + M;
        map[Ra][Ca] = Da;
        record[Ra][Ca] = k;

        // cout << Ra << " " << Ca << " " << Rv << " " << Cv << endl << endl;

        // printMap(map);

        attack();

        // printMap(map);

        for (int j = 1; j <= M; j++) {
            for (int i = 1; i <= N; i++) {
                if (map[i][j] == 0) continue;
                if (trace[i][j]) continue;
                map[i][j]++;
            }
        }

        // printMap(map);
    }

    int best = 0;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (best < map[i][j]) {
                best = map[i][j];
            }
        }
    }

    cout << best << endl;

    return 0;
}