#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Team {
    int hR, hC;
    int tR, tC;
    int num;
};

int n, m, k;
int score = 0;
int map[22][22];
int mapT[22][22];
int trace[22][22];
bool visit[22][22];
int dy[4] = {1, 0, -1, 0};
int dx[4] = {0, 1, 0, -1};
unordered_map<int, Team> T;

void printMap(int a[][22]) {
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
    for (int i = 0; i < 22; i++) {
        for (int j = 0; j < 22; j++) {
            map[i][j] = -1;
            mapT[i][j] = -1;
        }
    }

    return;
}

void initTrace() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            trace[i][j] = 0;
            visit[i][j] = false;
        }
    }

    return;
}

void checkTeam() {
    for (int i = 1; i <= m; i++) {
        int curR, curC;
        queue<pair<int, int> > q;

        q.push(make_pair(T[i].hR, T[i].hC));
        visit[T[i].hR][T[i].hC] = true;

        while (!q.empty()) {
            curR = q.front().first;
            curC = q.front().second;
            q.pop();
            
            if (map[curR][curC] == 3) {
                T[i].tR = curR;
                T[i].tC = curC;
                mapT[curR][curC] = i;
                break;
            }

            for (int j = 0; j < 4; j++) {
                int ny = curR + dy[j];
                int nx = curC + dx[j];

                if ((map[ny][nx] == 2 || map[ny][nx] == 3) && !visit[ny][nx]) {
                    q.push(make_pair(ny, nx));
                    visit[ny][nx] = true;
                    T[i].num++;
                }
            }
        }

        // cout << i << " " << T[i].num << endl;
    }

    return;
}

void move() {
    for (int i = 1; i <= m; i++) {
        int cy = T[i].hR;
        int cx = T[i].hC;
        int py, px, ny, nx;

        map[cy][cx] = 5;
        for (int j = 0; j < 4; j++) {
            ny = cy + dy[j];
            nx = cx + dx[j];

            if (map[ny][nx] == 4) {
                map[ny][nx] = 1;
                mapT[ny][nx] = i;
                T[i].hR = ny;
                T[i].hC = nx;
            }
            else if (map[ny][nx] == 2) {
                py = ny;
                px = nx;
            }
        }

        for (int j = 0; j < T[i].num - 1; j++) {
            cy = py;
            cx = px;
            mapT[cy][cx] = -1;

            int cur = map[cy][cx];

            if (map[cy][cx] == 3) {
                map[cy][cx] = 4; 
                }
            else {
                map[cy][cx] = 5;
            } 
            for (int l = 0; l < 4; l++) {
                ny = cy + dy[l];
                nx = cx + dx[l];

                if (map[ny][nx] == 5) {
                    map[ny][nx] = cur;
                    mapT[ny][nx] = i;
                    if (cur == 3) {
                        T[i].tR = ny;
                        T[i].tC = nx;
                    }
                }
                else if (map[ny][nx] == 2 || map[ny][nx] == 3) {
                    py = ny;
                    px = nx;
                }
            }
        }
    }

    return;
}

int calcScore(int idx, int r, int c) {
    initTrace();

    int num;
    int curR, curC;
    queue<pair<int, int> > q;

    q.push(make_pair(T[idx].hR, T[idx].hC));    
    visit[T[idx].hR][T[idx].hC] = true;
    trace[T[idx].hR][T[idx].hC] = 1;

    while (!q.empty()) {
        curR = q.front().first;
        curC = q.front().second;
        q.pop();

        if (curR == r && curC == c) break;

        for (int i = 0; i < 4; i++) {
            int ny = curR + dy[i];
            int nx = curC + dx[i];

            if (map[ny][nx] == 4 || map[ny][nx] == 0) continue;
            if (visit[ny][nx]) continue;

            q.push(make_pair(ny, nx));
            visit[ny][nx] = true;
            trace[ny][nx] = trace[curR][curC] + 1;
        }
    }

    return trace[r][c] * trace[r][c];
}

void throwBall(int r, int d) {
    int idx = 0;
    int tmpy, tmpx;

    if (d == 0) {
        for (int i = 1; i <= n; i++) {
            if (mapT[r][i] > 0) {
                idx = mapT[r][i];

                score += calcScore(idx, r, i);

                tmpy = T[idx].tR;
                tmpx = T[idx].tC;
                T[idx].tR = T[idx].hR;
                T[idx].tC = T[idx].hC;
                T[idx].hR = tmpy;
                T[idx].hC = tmpx;

                break;
            }
        }
    }
    else if (d == 1) {
        for (int i = n; i > 0; i--) {
            if (mapT[i][r] > 0) {
                idx = mapT[i][r];

                score += calcScore(idx, i, r);

                tmpy = T[idx].tR;
                tmpx = T[idx].tC;
                T[idx].tR = T[idx].hR;
                T[idx].tC = T[idx].hC;
                T[idx].hR = tmpy;
                T[idx].hC = tmpx;

                break;
            }
        }
    }
    else if (d == 2) {
        for (int i = n; i > 0; i--) {
            if (mapT[n - r + 1][i] > 0) {
                idx = mapT[n - r + 1][i];

                score += calcScore(idx, n - r + 1, i);

                tmpy = T[idx].tR;
                tmpx = T[idx].tC;
                T[idx].tR = T[idx].hR;
                T[idx].tC = T[idx].hC;
                T[idx].hR = tmpy;
                T[idx].hC = tmpx;

                break;
            }
        }
    }
    else {
        for (int i = 1; i <= n; i++) {
            if (mapT[i][n - r + 1] > 0) {
                idx = mapT[i][n - r + 1];
                
                score += calcScore(idx, i, n - r + 1);

                tmpy = T[idx].tR;
                tmpx = T[idx].tC;
                T[idx].tR = T[idx].hR;
                T[idx].tC = T[idx].hC;
                T[idx].hR = tmpy;
                T[idx].hC = tmpx;

                break;
            }
        }
    }

    if (idx > 0) {
        // cout << "Hit " << idx << endl;
        map[T[idx].hR][T[idx].hC] = 1;
        map[T[idx].tR][T[idx].tC] = 3;
        // printMap(map);
    }

    return;
}

int main() {
    cin >> n >> m >> k;

    int M = 1;
    initMap();

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> map[i][j];
            
            if (map[i][j] == 1) {
                T[M] = {i, j, 0, 0, 1};
                M++;
            }
        }
    }

    checkTeam();

    // printMap(map);

    for (int i = 0; i < k; i++) {
        move();

        // cout << i << endl << endl;
        // printMap(map);
        // printMap(mapT);

        int q = (i / n) % 4;
        int r = (i % n);

        throwBall(r + 1, q);
        // cout << score << endl << endl;

        // printMap(mapT);
    }

    cout << score << endl;


    return 0;
}