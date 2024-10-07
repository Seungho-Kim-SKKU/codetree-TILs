#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

int K, M;
int map[7][7];
int curMap[7][7];
int bestMap[7][7];
bool visit[7][7];
int di[4] = {1, 0, -1, 0};
int dj[4] = {0, 1, 0, -1};
queue<int> qUmul;

void printArray(int a[][7]) {
    for (int i = 1; i < 6; i++) {
        for (int j = 1; j < 6; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void initVisit() {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (i == 0 || i == 6 || j == 0 || j == 6) {
                visit[i][j] = true;
            }
            else {
                visit[i][j] = false;
            }
        }
    }
}

void rotateMap(int i, int j, int d) {
    copy(&map[0][0], &map[0][0] + 7 * 7, &curMap[0][0]);

    if (d == 0) {
        curMap[i-1][j-1] = map[i+1][j-1];
        curMap[i-1][j] = map[i][j-1];
        curMap[i-1][j+1] = map[i-1][j-1];
        curMap[i][j-1] = map[i+1][j];
        curMap[i][j+1] = map[i-1][j];
        curMap[i+1][j-1] = map[i+1][j+1];
        curMap[i+1][j] = map[i][j+1];
        curMap[i+1][j+1] = map[i-1][j+1];
    }
    else if (d == 1) {
        curMap[i-1][j-1] = map[i+1][j+1];
        curMap[i-1][j] = map[i+1][j];
        curMap[i-1][j+1] = map[i+1][j-1];
        curMap[i][j-1] = map[i][j+1];
        curMap[i][j+1] = map[i][j-1];
        curMap[i+1][j-1] = map[i-1][j+1];
        curMap[i+1][j] = map[i-1][j];
        curMap[i+1][j+1] = map[i-1][j-1];
    }
    else {
        curMap[i-1][j-1] = map[i-1][j+1];
        curMap[i-1][j] = map[i][j+1];
        curMap[i-1][j+1] = map[i+1][j+1];
        curMap[i][j-1] = map[i-1][j];
        curMap[i][j+1] = map[i+1][j];
        curMap[i+1][j-1] = map[i-1][j-1];
        curMap[i+1][j] = map[i][j-1];
        curMap[i+1][j+1] = map[i+1][j-1];
    }

    return;
}

int calcScore() {
    int score = 0;
    initVisit();

    for (int i = 1; i < 6; i++) {
        for (int j = 1; j < 6; j++) {
            if (!visit[i][j]) {
                queue<pair<int, int>> q, trace;
                q.push(make_pair(i, j));
                trace.push(make_pair(i, j));

                while(!q.empty()) {
                    visit[i][j] = true;
                    pair<int, int> cur = q.front();
                    q.pop();

                    for (int k = 0; k < 4; k++) {
                        int ni = cur.first + di[k];
                        int nj = cur.second + dj[k];

                        if (!visit[ni][nj] && curMap[cur.first][cur.second] == curMap[ni][nj]) {
                            q.push(make_pair(ni, nj));
                            trace.push(make_pair(ni, nj));
                            visit[ni][nj] = true;
                        }
                    }
                }

                if (trace.size() >= 3) {
                    while (!trace.empty()) {
                        score++;
                        pair<int, int> cur = trace.front();
                        trace.pop();
                        curMap[cur.first][cur.second] = 0;
                    }
                }
            }
        }
    }

    return score;
}

int main() {
    cin >> K >> M;

    for (int i = 1; i < 6; i++) {
        for (int j = 1; j < 6; j++) {
            int a;
            cin >> a;
            map[i][j] = a;
        }
    }

    // printArray(map);

    for (int i = 0; i < M; i++) {
        int a;
        cin >> a;
        qUmul.push(a);
    }

    for (int k = 0; k < K; k++) {
        int sum = 0;
        int bestScore = 0;
        // pair<int, int> bestIndex;
        for (int d = 0; d < 3; d++) {
            for (int j = 2; j < 5; j++) {
                for (int i = 2; i < 5; i++) {
                    // if (i == 3 && j ==3) printArray(curMap);

                    int score = 0;

                    rotateMap(i, j, d);

                    score = calcScore();

                    // cout << i << " " << j << " " << score << endl;

                    if (score > bestScore) {
                        bestScore = score;
                        copy(&curMap[0][0], &curMap[0][0] + 7 * 7, &bestMap[0][0]);
                        // printArray(bestMap);
                        // bestIndex = make_pair(i, j);
                    }
                }
            }
        }
        if (bestScore == 0) break;
        // cout << bestIndex.first << bestIndex.second << endl;
        sum += bestScore;

        while (1) {
            copy(&bestMap[0][0], &bestMap[0][0] + 7 * 7, &map[0][0]);

            for (int j = 1; j < 6; j++) {
                for (int i = 5; i > 0; i--) {
                    if (map[i][j] == 0) {
                        int cur = qUmul.front();
                        map[i][j] = cur;
                        qUmul.pop();
                    }
                }
            }
            // printArray(map);

            copy(&map[0][0], &map[0][0] + 7 * 7, &curMap[0][0]);

            int score = calcScore();
            
            if (score == 0) {
                break;
            }

            sum += score;
            // cout << score << endl;
            // printArray(curMap);
            copy(&curMap[0][0], &curMap[0][0] + 7 * 7, &bestMap[0][0]);
        }
        cout << sum << " ";
    }

    return 0;
}