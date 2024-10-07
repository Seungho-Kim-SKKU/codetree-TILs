#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define endl "\n"

int K, M;
int sumScore;
int umul[7][7];
int curUmul[7][7];
int bestUmul[7][7];
bool visit[7][7] = { 0, };
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
queue<int> nextUmul;

void printUmul() {
    for (int i = 1; i < 6; i++) {
        for (int j = 1; j < 6; j++) {
            cout << umul[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void printCurUmul() {
    for (int i = 1; i < 6; i++) {
        for (int j = 1; j < 6; j++) {
            cout << curUmul[i][j] << " ";
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

    return;
}

void rotate90(int a, int b) {
    for (int i = 1; i < 6; i++) {
        for (int j = 1; j < 6; j++) {
            curUmul[i][j] = umul[i][j];
        }
    }
    curUmul[a-1][b-1] = umul[a+1][b-1];
    curUmul[a-1][b] = umul[a][b-1];
    curUmul[a-1][b+1] = umul[a-1][b-1];
    curUmul[a][b-1] = umul[a+1][b];
    curUmul[a][b+1] = umul[a-1][b];
    curUmul[a+1][b-1] = umul[a+1][b+1];
    curUmul[a+1][b] = umul[a][b+1];
    curUmul[a+1][b+1] = umul[a-1][b+1];

    return;
}

void rotate180(int a, int b) {
    for (int i = 1; i < 6; i++) {
        for (int j = 1; j < 6; j++) {
            curUmul[i][j] = umul[i][j];
        }
    }
    curUmul[a-1][b-1] = umul[a+1][b+1];
    curUmul[a-1][b] = umul[a+1][b];
    curUmul[a-1][b+1] = umul[a+1][b-1];
    curUmul[a][b-1] = umul[a][b+1];
    curUmul[a][b+1] = umul[a][b-1];
    curUmul[a+1][b-1] = umul[a-1][b+1];
    curUmul[a+1][b] = umul[a-1][b];
    curUmul[a+1][b+1] = umul[a-1][b-1];

    return;
}

void rotate270(int a, int b) {
    for (int i = 1; i < 6; i++) {
        for (int j = 1; j < 6; j++) {
            curUmul[i][j] = umul[i][j];
        }
    }
    curUmul[a-1][b-1] = umul[a-1][b+1];
    curUmul[a-1][b] = umul[a][b+1];
    curUmul[a-1][b+1] = umul[a+1][b+1];
    curUmul[a][b-1] = umul[a-1][b];
    curUmul[a][b+1] = umul[a+1][b];
    curUmul[a+1][b-1] = umul[a-1][b-1];
    curUmul[a+1][b] = umul[a][b-1];
    curUmul[a+1][b+1] = umul[a+1][b-1];

    return;
}

int calcScore() {
    initVisit();
    int score = 0;

    for (int i = 1; i < 6; i++) {
        for (int j = 1; j < 6; j++) {
            if (!visit[i][j]) {
                queue<pair<int, int>> q, trace;
                q.push(make_pair(i, j));
                trace.push(make_pair(i, j));
                visit[i][j] = true;

                while (!q.empty()) {
                    pair<int, int> cur = q.front();
                    q.pop();

                    for (int k = 0; k < 4; k++) {
                        int ny = cur.first + dy[k];
                        int nx = cur.second + dx[k];

                        if (!visit[ny][nx] && curUmul[cur.first][cur.second] == curUmul[ny][nx]) {
                            q.push(make_pair(ny, nx));
                            trace.push(make_pair(ny, nx));
                            visit[ny][nx] = true;
                        }
                    }
                }

                if (trace.size() >= 3) {
                    while (!trace.empty()) {
                        score++;
                        pair<int, int> cur = trace.front();
                        trace.pop();
                        curUmul[cur.first][cur.second] = 0;
                    }
                }
            }
        }
    }
    
    return score;
}

int checkUmul90(int a, int b) {    
    rotate90(a, b);
    int score = calcScore();

    return score;
}

int checkUmul180(int a, int b) {
    rotate180(a, b);
    int score = calcScore();

    return score;
}

int checkUmul270(int a, int b) {
    rotate270(a, b);
    int score = calcScore();

    return score;
}

int main() {
    cin >> K >> M;

    for (int i = 1; i < 6; i++) {
        int n;
        for (int j = 1; j < 6; j++) {
            cin >> n;
            umul[i][j] = n;
        }
    }

    // printUmul();

    for (int i = 0; i < M; i++) {
        int n;
        cin >> n;
        nextUmul.push(n);
    }

    for (int k = 0; k < K; k++) {
        int bestScore = 0;
        for (int l = 0; l < 3; l++) {
            for (int i = 2; i < 5; i++) {
                for (int j = 2; j < 5; j++) {
                    if (l == 0) {
                        int score = checkUmul90(i, j);
                        if (score > bestScore) {
                            bestScore = score;
                            copy(&curUmul[0][0], &curUmul[0][0] + 49, &bestUmul[0][0]);
                        }
                    }
                    else if (l == 1) {
                        int score = checkUmul180(i, j);
                        if (score > bestScore) {
                            bestScore = score;
                            copy(&curUmul[0][0], &curUmul[0][0] + 49, &bestUmul[0][0]);
                        }
                    }
                    else {
                        int score = checkUmul270(i, j);
                        if (score > bestScore) {
                            bestScore = score;
                            copy(&curUmul[0][0], &curUmul[0][0] + 49, &bestUmul[0][0]);
                        }
                    }
                }
            }
        }        

        if (bestScore == 0) break;

        sumScore += bestScore;        

        while (true) {
            copy(&bestUmul[0][0], &bestUmul[0][0] + 49, &umul[0][0]);

            for (int j = 1; j < 6; j++) {
                for (int i = 5; i > 0; i--) {
                    if (umul[i][j] == 0) {
                        int cur = nextUmul.front();
                        nextUmul.pop();
                        umul[i][j] = cur;
                        bestScore--;
                    }
                }
            }

            copy(&umul[0][0], &umul[0][0] + 49, &curUmul[0][0]);

            bestScore = calcScore();
            if (bestScore == 0) break;
            sumScore += bestScore;

            copy(&curUmul[0][0], &curUmul[0][0] + 49, &bestUmul[0][0]);
        }
    }

    cout << sumScore << endl;
}