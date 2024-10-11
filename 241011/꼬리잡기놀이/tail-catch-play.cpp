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

            int cur = map[cy][cx];

            if (map[cy][cx] == 3) {
                map[cy][cx] = 4; 
                mapT[cy][cx] = -1;
                }
            else {
                map[cy][cx] = 5;
            } 
            for (int l = 0; l < 4; l++) {
                ny = cy + dy[l];
                nx = cx + dx[l];

                if (map[ny][nx] == 5) {
                    map[ny][nx] = cur;
                    if (cur == 3) {
                        T[i].tR = ny;
                        T[i].tC = nx;
                        mapT[ny][nx] = i;
                    }
                }
                else if (map[ny][nx] == 2 || map[ny][nx] == 3) {
                    py = ny;
                    px = nx;
                }
            }
        }

        // cout << T[i].hR << " " << T[i].hC << " " << T[i].tR << " " << T[i].tC << endl;

        // printMap();
    }

    return;
}

void throwBall(int r, int d) {
    if (d == 0) {
        for (int i = 1; i <= n; i++) {
            if (mapT[r][i] > 0) {
                score += T[mapT[r][i]].num * T[mapT[r][i]].num;
                return;
            }
        }
    }
    else if (d == 1) {
        for (int i = n; i > 0; i--) {
            if (mapT[i][r] > 0) {
                score += T[mapT[i][r]].num * T[mapT[i][r]].num;
                return;
            }
        }
    }
    else if (d == 2) {
        for (int i = n; i > 0; i--) {
            if (mapT[n - r + 1][i] > 0) {
                score += T[mapT[n - r + 1][i]].num * T[mapT[n - r + 1][i]].num;
                return;
            }
        }
    }
    else {
        for (int i = 1; i <= n; i++) {
            if (mapT[i][n - r + 1] > 0) {
                score += T[mapT[i][n - r + 1]].num * T[mapT[i][n - r + 1]].num;
                return;
            }
        }
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

        int q = (i / n) % 4;
        int r = (i % n);

        throwBall(r + 1, q);
    }

    cout << score << endl;


    return 0;
}