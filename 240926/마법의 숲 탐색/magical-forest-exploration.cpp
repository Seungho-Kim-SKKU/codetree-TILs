#include <iostream>
#include <utility>

using namespace std;

#define endl '\n'
#define MAX 80
#define WALL 9
#define CENTER 5
#define EXIT 4
#define OCC 3

short maze[MAX][MAX];
short mazeTrav[MAX][MAX];
int curMax = 0;

void printMaze(int row, int col) {
    for (int r = 0; r < row+4; r++) {
        for (int c = 0; c < col+2; c++) {
            cout << maze[r][c] << " ";            
        }
        cout << endl;
    }
}

void initMaze(int row, int col) {
    for (int r = 0; r < row+4; r++) {
        for (int c = 0; c < col+2; c++) {
            if (c == 0 || r == row + 3 || c == col + 1) {
                maze[r][c] = WALL;
            }
            else {
                maze[r][c] = 1;
            }            
        }
    }    

    return;
}

void initMazeTrav(int row, int col) {
    for (int r = 0; r < row+4; r++) {
        for (int c = 0; c < col+2; c++) {
            if (c == 0 || r == row + 3 || c == col + 1) {
                mazeTrav[r][c] = WALL;
            }
            else {
                mazeTrav[r][c] = 0;
            }            
        }
    }    

    return;
}

bool checkMaze() {
    int c;
    for (int r = 0; r < 3; r++) {
        c = 1;
        while (maze[r][c] != WALL) {
            if (maze[r][c] != 1) {
                return true;
            }
            c++;
        }
    }
    return false;
}

void setGol(int mid, int exit) {
    int centerRow = 1;
    int centerCol = mid;

    maze[centerRow][centerCol] = CENTER;

    switch(exit) {
        case 0:
            maze[centerRow - 1][centerCol] = EXIT;
            maze[centerRow][centerCol - 1] = OCC;
            maze[centerRow + 1][centerCol] = OCC;
            maze[centerRow][centerCol + 1] = OCC;
            break;
        case 1:
            maze[centerRow - 1][centerCol] = OCC;
            maze[centerRow][centerCol - 1] = OCC;
            maze[centerRow + 1][centerCol] = OCC;
            maze[centerRow][centerCol + 1] = EXIT;
            break;
        case 2:
            maze[centerRow - 1][centerCol] = OCC;
            maze[centerRow][centerCol - 1] = OCC;
            maze[centerRow + 1][centerCol] = EXIT;
            maze[centerRow][centerCol + 1] = OCC;
            break;
        case 3:
            maze[centerRow - 1][centerCol] = OCC;
            maze[centerRow][centerCol - 1] = EXIT;
            maze[centerRow + 1][centerCol] = OCC;
            maze[centerRow][centerCol + 1] = OCC;
            break;
        default:
            break;
    }
}

bool checkDown(pair<int, int> center) {
    if (maze[center.first+1][center.second-1] == 1 
    && maze[center.first+2][center.second] == 1 
    && maze[center.first+1][center.second+1] == 1) {
        return true;
    }
    else {
        return false;
    }
}

bool checkLeft(pair<int, int> center) {
    if (maze[center.first-1][center.second-1] == 1 
    && maze[center.first][center.second-2] == 1 
    && maze[center.first+1][center.second-1] == 1
    && maze[center.first+1][center.second-2] == 1
    && maze[center.first+2][center.second-1] == 1) {
        return true;
    }
    else {
        return false;
    }
}

bool checkRight(pair<int, int> center) {
    if (maze[center.first-1][center.second+1] == 1 
    && maze[center.first][center.second+2] == 1 
    && maze[center.first+1][center.second+1] == 1
    && maze[center.first+1][center.second+2] == 1
    && maze[center.first+2][center.second+1] == 1) {
        return true;
    }
    else {
        return false;
    }
}

void moveDown(pair<int, int> center) {
    //left
    maze[center.first+1][center.second-1] = maze[center.first][center.second-1];
    maze[center.first][center.second-1] = 1;
    //bottom
    maze[center.first+2][center.second] = maze[center.first+1][center.second];
    //right
    maze[center.first+1][center.second+1] = maze[center.first][center.second+1];
    maze[center.first][center.second+1] = 1;
    //center
    maze[center.first+1][center.second] = maze[center.first][center.second];
    //top
    maze[center.first][center.second] = maze[center.first-1][center.second];
    maze[center.first-1][center.second] = 1;

    return;
}

void moveLeft(pair<int, int> center) {
    //left
    maze[center.first+1][center.second-1] = maze[center.first][center.second-1];
    //top
    maze[center.first][center.second-2] = maze[center.first-1][center.second];
    maze[center.first-1][center.second] = 1;
    //right
    maze[center.first-1][center.second-1] = maze[center.first][center.second+1];
    maze[center.first][center.second+1] = 1;
    //center
    maze[center.first][center.second-1] = maze[center.first][center.second];
    //bottom
    maze[center.first][center.second] = maze[center.first+1][center.second];
    maze[center.first+1][center.second] = 1;

    return;
}

void moveRight(pair<int, int> center) {
    //right
    maze[center.first+1][center.second+1] = maze[center.first][center.second+1];
    //top
    maze[center.first][center.second+2] = maze[center.first-1][center.second];
    maze[center.first-1][center.second] = 1;
    //left
    maze[center.first-1][center.second+1] = maze[center.first][center.second-1];
    maze[center.first][center.second-1] = 1;
    //center
    maze[center.first][center.second+1] = maze[center.first][center.second];
    //bottom
    maze[center.first][center.second] = maze[center.first+1][center.second];
    maze[center.first+1][center.second] = 1;

    return;
}

pair<int, int> moveGol(pair<int, int> center) {
    if (checkDown(center)) {
        moveDown(center);
        center = make_pair(center.first+1, center.second);

        center = moveGol(center);
    }
    else if (checkLeft(center)) {
        moveLeft(center);
        center = make_pair(center.first, center.second-1);
        moveDown(center);
        center = make_pair(center.first+1, center.second);

        center = moveGol(center);
    }
    else if (checkRight(center)) {
        moveRight(center);
        center = make_pair(center.first, center.second+1);
        moveDown(center);
        center = make_pair(center.first+1, center.second);

        center = moveGol(center);
    }
    
    return center;
}

void calculate(pair<int, int> center) {
    // cout << center.first << center.second << endl;
    mazeTrav[center.first][center.second] = 1;
    if (center.first-2 > curMax) {
        curMax = center.first-2;
    }    
    if (maze[curMax + 1][1] == WALL) {
        return;
    }

    if (maze[center.first][center.second] == CENTER) {
        //down
        if (mazeTrav[center.first+1][center.second] == 0) {
            calculate(make_pair(center.first+1, center.second));
        }
        //left
        if (mazeTrav[center.first][center.second-1] == 0) {
            calculate(make_pair(center.first, center.second-1));
        }
        //right
        if (mazeTrav[center.first][center.second+1] == 0) {
            calculate(make_pair(center.first, center.second+1));
        }
        //up
        if (mazeTrav[center.first-1][center.second] == 0) {
            calculate(make_pair(center.first-1, center.second));
        }
    }
    else if (maze[center.first][center.second] == EXIT) {
        //down
        if (mazeTrav[center.first+1][center.second] == 0 && maze[center.first+1][center.second] != 1 ) {
            calculate(make_pair(center.first+1, center.second));
        }
        //left
        if (mazeTrav[center.first][center.second-1] == 0 && maze[center.first][center.second-1] != 1) {
            calculate(make_pair(center.first, center.second-1));
        }
        //right
        if (mazeTrav[center.first][center.second+1] == 0 && maze[center.first][center.second+1] != 1) {
            calculate(make_pair(center.first, center.second+1));
        }
        //up
        if (mazeTrav[center.first-1][center.second] == 0 && maze[center.first-1][center.second] != 1) {
            calculate(make_pair(center.first-1, center.second));
        }
    }
    else if (maze[center.first][center.second] == OCC){
        //down
        if (mazeTrav[center.first+1][center.second] == 0 && maze[center.first+1][center.second] == CENTER) {
            calculate(make_pair(center.first+1, center.second));
        }
        //left
        if (mazeTrav[center.first][center.second-1] == 0 && maze[center.first][center.second-1] == CENTER) {
            calculate(make_pair(center.first, center.second-1));
        }
        //right
        if (mazeTrav[center.first][center.second+1] == 0 && maze[center.first][center.second+1] == CENTER) {
            calculate(make_pair(center.first, center.second+1));
        }
        //up
        if (mazeTrav[center.first-1][center.second] == 0 && maze[center.first-1][center.second] == CENTER) {
            calculate(make_pair(center.first-1, center.second));
        }
    }

    return;
}

int main() {
    int row, col;
    int numGol;
    int sumRow = 0;
    int mid;
    int exit;
    pair<int, int> center;

    cin >> row >> col >> numGol;

    initMaze(row, col);

    for (int i = 0; i < numGol; i++) {
        cin >> mid >> exit;

        // cout << i << mid << exit << endl;
        
        setGol(mid, exit);

        // printMaze(row, col);

        center = make_pair(1, mid);
        center = moveGol(center);

        // cout << endl;
        // printMaze(row, col);
        // cout << endl;

        if (checkMaze()) {
            initMaze(row, col);
            continue;
        }
        curMax = 0;
        initMazeTrav(row, col);
        calculate(center);

        // cout << curMax << endl << endl;

        sumRow += curMax;
    }

    cout << sumRow << endl;

    return 0;
}