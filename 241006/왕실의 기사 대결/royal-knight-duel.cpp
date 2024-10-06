#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

#define endl "\n"
#define MAXL 42

struct Knight {
    int r;
    int c;
    int h;
    int w;
    int k;
    int d;
};

int L;
int N;
int Q;
int chess[MAXL][MAXL] = { 0, };
int knight[MAXL][MAXL] = { 0, };
bool visited[31] = { 0, };
bool flag = true;
unordered_map<int, Knight> Knights;

int damage = 0;
int curI = 0;

void printChess() {
    for (int i = 0; i < L + 2; i++) {
        for (int j = 0; j < L + 2; j++) {
            cout << chess[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    return;
}

void printKnight() {
    for (int i = 0; i < L + 2; i++) {
        for (int j = 0; j < L + 2; j++) {
            cout << knight[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    return;
}

void checkUp(int i) {
    visited[i] = true;

    for (int j = Knights[i].c; j < Knights[i].c + Knights[i].w; j++) {
        if (flag == false) return;

        // cout << i << " " << Knights[i].r - 1 << " " << j << " " << chess[Knights[i].r - 1][j] << endl;
        
        if (knight[Knights[i].r - 1][j] != 0 && visited[knight[Knights[i].r - 1][j]] == false) {
            checkUp(knight[Knights[i].r - 1][j]);
        }

        if (chess[Knights[i].r - 1][j] == 2) {
            flag = false;
            return;
        }
    }

    return;
}

void checkRight(int i) {
    visited[i] = true;

    for (int j = Knights[i].r; j < Knights[i].r + Knights[i].h; j++) {        
        if (flag == false) return;

        // cout << i << " " << j << " " << Knights[i].c + Knights[i].w << " " << chess[j][Knights[i].c + Knights[i].w] << endl;
        
        if (knight[j][Knights[i].c + Knights[i].w] != 0 && visited[knight[j][Knights[i].c + Knights[i].w]] == false) {
            checkRight(knight[j][Knights[i].c + Knights[i].w]);
        }

        if (chess[j][Knights[i].c + Knights[i].w] == 2) {
            flag = false;
            return;
        }
    }

    return;
}

void checkDown(int i) {
    visited[i] = true;

    for (int j = Knights[i].c; j < Knights[i].c + Knights[i].w; j++) {
        if (flag == false) return;

        // cout << i << " " << Knights[i].r + Knights[i].h << " " << j << " " << chess[Knights[i].r + Knights[i].h][j] << endl;
        
        if (knight[Knights[i].r + Knights[i].h][j] != 0 && visited[knight[Knights[i].r + Knights[i].h][j]] == false) {
            checkDown(knight[Knights[i].r + Knights[i].h][j]);
        }

        if (chess[Knights[i].r + Knights[i].h][j] == 2) {
            flag = false;
            return;
        }
    }

    return;
}

void checkLeft(int i) {
    visited[i] = true;

    for (int j = Knights[i].r; j < Knights[i].r + Knights[i].h; j++) {        
        if (flag == false) return;

        // cout << i << " " << j << " " << Knights[i].c - 1<< " " << chess[j][Knights[i].c - 1] << endl;
        
        if (knight[j][Knights[i].c - 1] != 0 && visited[knight[j][Knights[i].c - 1]] == false) {
            checkLeft(knight[j][Knights[i].c - 1]);
        }

        if (chess[j][Knights[i].c - 1] == 2) {
            flag = false;
            return;
        }
    }

    return;
}

void moveUp(int i) {
    visited[i] = true;

    for (int j = Knights[i].c; j < Knights[i].c + Knights[i].w; j++) {
        // cout << i << " " << Knights[i].r - 1 << " " << j << " " << chess[Knights[i].r - 1][j] << endl;
        
        if (knight[Knights[i].r - 1][j] != 0 && visited[knight[Knights[i].r - 1][j]] == false) {
            moveUp(knight[Knights[i].r - 1][j]);
        }
    }

    Knights[i].r--;

    for (int j = Knights[i].r; j < Knights[i].r + Knights[i].h + 1; j++) {
        for (int k = Knights[i].c; k < Knights[i].c + Knights[i].w; k++) {
            if (k == Knights[i].r + Knights[i].h) {
                knight[j][k] = 0;
            }
            else {
                knight[j][k] = i;
                if (chess[j][k] == 1 && i != curI) {
                    Knights[i].d++;
                }
            }
        }
    }

    if (Knights[i].k - Knights[i].d <= 0) {
        for (int j = Knights[i].r; j < Knights[i].r + Knights[i].h; j++) {
            for (int k = Knights[i].c; k < Knights[i].c + Knights[i].w; k++) {
                knight[j][k] = 0;
            }
        }
        
        Knights.erase(i);
    }

    return;
}

void moveRight(int i) {
    visited[i] = true;

    for (int j = Knights[i].r; j < Knights[i].r + Knights[i].h; j++) {
        // cout << i << " " << j << " " << Knights[i].c + Knights[i].w << " " << chess[j][Knights[i].c + Knights[i].w] << endl;
        
        if (knight[j][Knights[i].c + Knights[i].w] != 0 && visited[knight[j][Knights[i].c + Knights[i].w]] == false) {
            moveRight(knight[j][Knights[i].c + Knights[i].w]);
        }
    }

    Knights[i].c++;

    for (int j = Knights[i].r; j < Knights[i].r + Knights[i].h; j++) {
        for (int k = Knights[i].c - 1; k < Knights[i].c + Knights[i].w; k++) {
            if (k == Knights[i].c - 1) {
                knight[j][k] = 0;
            }
            else {
                knight[j][k] = i;
                if (chess[j][k] == 1 && i != curI) {
                    Knights[i].d++;
                }
            }
        }
    }

    if (Knights[i].k - Knights[i].d <= 0) {
        for (int j = Knights[i].r; j < Knights[i].r + Knights[i].h; j++) {
            for (int k = Knights[i].c; k < Knights[i].c + Knights[i].w; k++) {
                knight[j][k] = 0;
            }
        }
        
        Knights.erase(i);
    }

    return;
}

void moveDown(int i) {
    visited[i] = true;

    for (int j = Knights[i].c; j < Knights[i].c + Knights[i].w; j++) {
        // cout << i << " " << Knights[i].r + Knights[i].h << " " << j << " " << chess[Knights[i].r + Knights[i].h][j] << endl;
        
        if (knight[Knights[i].r + Knights[i].h][j] != 0 && visited[knight[Knights[i].r + Knights[i].h][j]] == false) {
            moveDown(knight[Knights[i].r + Knights[i].h][j]);
        }
    }

    Knights[i].r++;

    for (int j = Knights[i].r - 1; j < Knights[i].r + Knights[i].h; j++) {
        for (int k = Knights[i].c; k < Knights[i].c + Knights[i].w; k++) {
            if (k == Knights[i].r - 1) {
                knight[j][k] = 0;
            }
            else {
                knight[j][k] = i;
                if (chess[j][k] == 1 && i != curI) {
                    Knights[i].d++;
                }
            }
        }
    }

    if (Knights[i].k - Knights[i].d <= 0) {
        for (int j = Knights[i].r; j < Knights[i].r + Knights[i].h; j++) {
            for (int k = Knights[i].c; k < Knights[i].c + Knights[i].w; k++) {
                knight[j][k] = 0;
            }
        }
        
        Knights.erase(i);
    }

    return;
}

void moveLeft(int i) {
    visited[i] = true;

    for (int j = Knights[i].r; j < Knights[i].r + Knights[i].h; j++) {
        // cout << i << " " << j << " " << Knights[i].c - 1 << " " << chess[j][Knights[i].c - 1] << endl;
        
        if (knight[j][Knights[i].c - 1] != 0 && visited[knight[j][Knights[i].c - 1]] == false) {
            moveLeft(knight[j][Knights[i].c - 1]);
        }
    }

    Knights[i].c--;

    for (int j = Knights[i].r; j < Knights[i].r + Knights[i].h; j++) {
        for (int k = Knights[i].c; k < Knights[i].c + Knights[i].w + 1; k++) {
            if (k == Knights[i].c + Knights[i].w) {
                knight[j][k] = 0;
            }
            else {
                knight[j][k] = i;
                if (chess[j][k] == 1 && i != curI) {
                    Knights[i].d++;
                }
            }
        }
    }

    if (Knights[i].k - Knights[i].d <= 0) {
        for (int j = Knights[i].r; j < Knights[i].r + Knights[i].h; j++) {
            for (int k = Knights[i].c; k < Knights[i].c + Knights[i].w; k++) {
                knight[j][k] = 0;
            }
        }
        
        Knights.erase(i);
    }

    return;
}

void moveKnight(int i, int d) {
    flag = true;
    curI = i;
    for (int j = 1; j <= N; j++) {
        visited[j] = false;
    }

    if (d == 0) checkUp(i);
    else if (d == 1) checkRight(i);
    else if (d == 2) checkDown(i);
    else checkLeft(i);

    for (int j = 1; j <= N; j++) {
        visited[j] = false;
    }

    if (flag == true) {
        if (d == 0) moveUp(i);
        else if (d == 1) moveRight(i);
        else if (d == 2) moveDown(i);
        else moveLeft(i);
    }

    return;
}

int main() {
    cin >> L >> N >> Q;

    for (int i = 0; i < L + 2; i++) {
        int a;
        for (int j = 0; j < L + 2; j++) {
            if (i == 0 || i == L + 1 || j == 0 || j == L + 1) {
                chess[i][j] = 2;
            }
            else {
                cin >> a;
                chess[i][j] = a;
            }
        }
    }

    // printChess();

    for (int n = 1; n < N + 1; n++) {
        int row, col, height, width, hp;
        cin >> row >> col >> height >> width >> hp;

        Knights[n] = {row, col, height, width, hp, 0};

        for (int i = row; i < row + height; i++) {
            for (int j = col; j < col + width; j++) {
                knight[i][j] = n;
            }
        }
    }

    // printKnight();

    for (int q = 0; q < Q; q++) {
        int i, d;
        cin >> i >> d;
        moveKnight(i, d);
        // printKnight();
    }

    for (auto& it: Knights) {
        damage += it.second.d;
    }

    cout << damage << endl;
    
    return 0;
}