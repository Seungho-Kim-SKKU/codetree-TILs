#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int root;
int colorSet[6] = { 0, };

typedef struct treeNode {
    int pid;
    int color;
    int max;
    vector<int> child;
} Node;

void addNode(unordered_map<int, Node> &tree, int mid, int pid, int color, int max) {
    if (pid == -1) {
        root = mid;

        Node n = {pid, color, max};
        
        tree[mid] = n;
    }
    else {
        int depth = 1;
        int parent = pid;

        while (parent != -1) {
            depth++;

            if (depth > tree[parent].max) {
                return;
            }

            parent = tree[parent].pid;
        }
        
        tree[pid].child.push_back(mid);

        Node n = {pid, color, max};
        
        tree[mid] = n;
    }

    return;
}

void changeColor(unordered_map<int, Node> &tree, int mid, int color) {
    for (auto& it: tree[mid].child) {
        changeColor(tree, it, color);
    }

    tree[mid].color = color;

    return;
}

bool checkColorSet() {
    int check = 0;

    for (int i = 1; i < 6; i++) {
        if (colorSet[i] == 1) {
            check++;
        }
    }

    if (check == 5) {
        return true;
    }
    else {
        return false;
    }
}

void calculate(unordered_map<int, Node> &tree, int mid) {
    if (checkColorSet()) {
        return;
    }

    for (auto& it: tree[mid].child) {
        calculate(tree, it);
    }

    colorSet[tree[mid].color] = 1;

    return;
}

int calcScore(unordered_map<int, Node> &tree) {
    int score = 0;

    for (auto& it: tree) {
        int num = 0;

        calculate(tree, it.first);

        for (int i = 1; i < 6; i++) {
            if (colorSet[i] == 1) {
                num++;
            }
            colorSet[i] = 0;
        }
        score += num * num; 
    }

    return score;
}

int main() {
    int numOp;
    int op;
    int mid;
    int pid;
    int color;
    int max;
    int score;

    unordered_map<int, Node> tree;

    cin >> numOp;

    for (int i = 0; i < numOp; i++) {
        cin >> op;

        if (op == 100) {
            cin >> mid >> pid >> color >> max;

            addNode(tree, mid, pid, color, max);
        }
        else if (op == 200) {
            cin >> mid >> color;

            changeColor(tree, mid, color);
        }
        else if (op == 300) {
            cin >> mid;

            cout << tree[mid].color << endl;
        }
        else if (op == 400) {
            score = calcScore(tree);
            
            cout << score << endl;
        }
        else {
            continue;
        }
    }

    return 0;
}