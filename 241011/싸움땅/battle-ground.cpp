#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define endl "\n"

struct Human {
    int r;
    int c;
    int d;
    int s;
    int g;
    int score;
};

int n, m, k;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
int mapH[22][22];
vector<int> G[22][22];
unordered_map<int, Human> H;

void printGun() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << G[i][j].front() << " ";
        }
        cout << endl;
    }
    cout << endl;

    return;
}

void printMap(int a[][22]) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool cmp(int a, int b) {
    return a > b;
}

void initMapH() {
    for (int i = 0; i < 22; i++) {
        for (int j = 0; j < 22; j++) {
            if (i > 0 && i <= n && j > 0 && j <= n) mapH[i][j] = 0;
            else mapH[i][j] = -1;
        }
    }
}

void changeGun(int i, int r, int c) {
    if (G[r][c].size() == 0) return;

    if (H[i].g == 0) {
        H[i].g = G[r][c].front();
        G[r][c].erase(G[r][c].begin());
    }
    else if (H[i].g < G[r][c].front()) {
        G[r][c].push_back(H[i].g);
        H[i].g = G[r][c].front();
        G[r][c].erase(G[r][c].begin());
        sort(G[r][c].begin(), G[r][c].end(), cmp);
    }

    return;
}

void simulate() {
    for (int i = 1; i <= m; i++) {
        mapH[H[i].r][H[i].c] = 0;

        int ny = H[i].r + dy[H[i].d];
        int nx = H[i].c + dx[H[i].d]; 

        if (ny > n) {
            ny -= 2;
            H[i].d = 0;
        }
        else if (ny < 1) {
            ny += 2;
            H[i].d = 2;
        }
        if (nx > n) {
            nx -= 2;
            H[i].d = 3;
        }
        else if (nx < 1) {
            nx += 2;
            H[i].d = 1;
        }

        if (mapH[ny][nx] == 0) {
            mapH[ny][nx] = i;
            H[i].r = ny;
            H[i].c = nx;

            changeGun(i, ny, nx);
        }
        else {
            int curD = H[i].s + H[i].g;
            int oriD = H[mapH[ny][nx]].s + H[mapH[ny][nx]].g;

            int winIdx, loseIdx;

            if (curD > oriD) {
                winIdx = i;
                loseIdx = mapH[ny][nx];
            }
            else if (curD < oriD) {
                winIdx = mapH[ny][nx];
                loseIdx = i;
            }
            else {
                if (H[i].s > H[mapH[ny][nx]].s) {
                    winIdx = i;
                    loseIdx = mapH[ny][nx];
                }
                else {
                    winIdx = mapH[ny][nx];
                    loseIdx = i;
                }
            }

            // cout << winIdx << " " << loseIdx << endl;

            // cout << H[winIdx].s << " " << H[loseIdx].s << endl;
            // cout << H[winIdx].g << " " << H[loseIdx].g << endl;

            G[ny][nx].push_back(H[loseIdx].g);
            sort(G[ny][nx].begin(), G[ny][nx].end(), cmp);
            H[loseIdx].g = 0;

            int nny = ny + dy[H[loseIdx].d];
            int nnx = nx + dx[H[loseIdx].d];

            while (mapH[nny][nnx] != 0) {
                H[loseIdx].d = (H[loseIdx].d + 1) % 4;
                nny = ny + dy[H[loseIdx].d];
                nnx = nx + dx[H[loseIdx].d];
            }

            mapH[nny][nnx] = loseIdx;
            H[loseIdx].r = nny;
            H[loseIdx].c = nnx;
            changeGun(loseIdx, nny, nnx);                
            
            H[winIdx].score = abs(curD - oriD);
            mapH[ny][nx] = winIdx;
            H[winIdx].r = ny;
            H[winIdx].c = nx;
            changeGun(winIdx, ny, nx);
        }
        // cout << i << endl;
        // printMap(mapH);
    }

    return;
}


int main() {
    cin >> n >> m >> k;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int num;
            cin >> num;
            G[i][j].push_back(num);
        }
    }

    initMapH();

    for (int i = 1; i <= m; i++) {
        int r, c, d, s;
        cin >> r >> c >> d >> s;
        H[i] = {r, c, d, s, 0, 0};
        mapH[r][c] = i;
    }

    // printMap(mapH);

    for (int K = 0; K < k; K++) {
        simulate();
    }

    for (int i = 1; i <= m; i++) {
        cout << H[i].score <<  " ";
    }
    
    return 0;
}