#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

#define EXIT 21

struct Human {
    int r;
    int c;
    bool alive;
};

int N, M, K;
int R, C;
int map[12][12] = { 0, };
int mapH[12][12] = { 0, };
int dy[4] = {1, 0, -1, 0};
int dx[4] = {0, 1, 0, -1};
int numH;
int score = 0;

unordered_map<int, Human> H;

void printMap(int a[][12]) {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    return;
}

void move() {
    for (int m = 0; m < M; m++) {
        if (!H[m].alive) continue;

        int curD = abs(R - H[m].r) + abs(C - H[m].c);

        for (int i = 0; i < 4; i++) {
            int ny = H[m].r + dy[i];
            int nx = H[m].c + dx[i];

            if (map[ny][nx] == 0 || map[ny][nx] == EXIT) {                
                int nD = abs(R - ny) + abs(C - nx);

                if (nD < curD) {
                    score++;
                    mapH[H[m].r][H[m].c] -= 1;
                    H[m].r = ny;
                    H[m].c = nx;

                    if (ny == R && nx == C) {
                        numH--;
                        H[m].alive = false;
                    }
                    else {
                        mapH[ny][nx]++;
                    }

                    break;
                }
            }
        }
    }

    return;
}

bool canRotate(int r, int c, int s) {
    if (r < 1 || c < 1 || r + s - 1> N || c + s - 1 > N) {
        return false;
    }

    for (int k = r; k < r + s; k++) {
        for (int l = c; l < c + s; l++) {
            if (mapH[k][l] != 0) return true;
        }
    }

    return false;
}

void rotateMap(int r, int c, int s) {
    int tmp[s][s];
    int tmpH[s][s];
    queue<int> q;

    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            tmp[j][s - 1 - i] = map[r + i][c + j];
            tmpH[j][s - 1 - i] = mapH[r + i][c + j];
            
            if (tmp[j][s - 1 - i] > 0 && tmp[j][s - 1 - i] != EXIT) {
                tmp[j][s - 1 - i]--;
            }
            if (mapH[r + i][c + j] == 1) {
                for (auto& it: H) {
                    if (r + i == it.second.r && c + j == it.second.c && it.second.alive) {
                        q.push(it.first);
                    }
                }
            }
        }
    }

    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            map[r + i][c + j] = tmp[i][j];
            mapH[r + i][c + j] = tmpH[i][j];

            if (tmp[i][j] == EXIT) {
                R = r + i;
                C = c + j;
                // cout << R << " " << C << endl;
            }
            if (tmpH[i][j] == 1) {
                int n = q.front();
                q.pop();
                
                H[n].r = r + i;
                H[n].c = c + j;
            }
        }
    }

    return;
}

void checkAndRotate() {
    bool f = false;
    int curR = -1;
    int curC = -1;
    int l = -1;

    for (int n = 1; n < N; n++) {
        for (int i = R - n; i <= R; i++) {
            for (int j = C - n; j <= C; j++) {
                f = canRotate(i, j, n+1);

                if (f) {
                    curR = i;
                    curC = j;
                    l = n + 1;
                    break;
                }
            }
            if (f) break;
        }
        if (n == 2) break;
        if (f) break;
    }

    // cout << curR << " " << curC << " " << l << endl << endl;

    rotateMap(curR, curC, l);

    // printMap(map);

    return;
}

int main() {
    cin >> N >> M >> K;

    numH = M;

    for (int i = 0; i <= N + 1; i++) {
        for (int j = 1; j <= N + 1; j++) {
            if (i == 0 || j == 0 || i == N + 1 || j == N + 1) {
                map[i][j] = -1;
            }
            else {                    
                int n;
                cin >> n;

                map[i][j] = n;
            }            
        }
    }

    for (int m = 0; m < M; m++) {
        int r, c;
        cin >> r >> c;

        H[m] = {r, c, true};

        mapH[r][c] += 1;
    }

    cin >> R >> C;
    map[R][C] = EXIT;

    // printMap(map);

    for (int k = 0; k < K; k++) {
        // cout << k << endl << endl;
        move();
        // printMap(mapH);
        if (numH == 0) break;
        // printMap(map);
        checkAndRotate();
    }

    cout << score << endl << R << " " << C;

    return 0;
}