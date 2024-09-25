#include <iostream>
#include <unordered_map>
using namespace std;

short root;
short colorSet[6] = { 0, };

typedef struct treeNode {
    short pid;
    short color;
    short max;
    short lid;
    short rid;
} Node;

void addNode(unordered_map<short, Node> &tree, short mid, short pid, short color, short max) {
    if (pid == -1) {
        root = mid;

        Node n = {pid, color, max, 0, 0};
        
        tree[mid] = n;
    }
    else {
        short depth = 1;
        short parent = pid;

        while (parent != -1) {
            depth++;

            if (depth > tree[parent].max) {
                return;
            }

            parent = tree[parent].pid;
        }

        if (tree[pid].lid == 0) {
            tree[pid].lid = mid;
        }
        else if (tree[pid].rid == 0) {
            tree[pid].rid = mid;
        }
        else {
            return;
        }

        Node n = {pid, color, max, 0, 0};
        
        tree[mid] = n;
    }

    return;
}

void changeColor(unordered_map<short, Node> &tree, short mid, short color) {
    if (tree[mid].lid != 0) {
        changeColor(tree, tree[mid].lid, color);
    }
    if (tree[mid].rid != 0) {
        changeColor(tree, tree[mid].rid, color);
    }

    tree[mid].color = color;

    return;
}

bool checkColorSet() {
    short check = 0;

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

void calculate(unordered_map<short, Node> &tree, short mid) {
    if (checkColorSet()) {
        return;
    }

    if (tree[mid].lid != 0) {
        calculate(tree, tree[mid].lid);
    }
    if (tree[mid].rid != 0) {
        calculate(tree, tree[mid].rid);
    }

    colorSet[tree[mid].color] = 1;

    return;
}

short calcScore(unordered_map<short, Node> &tree) {
    short score = 0;

    for (auto& it: tree) {
        short num = 0;

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
    short numOp;
    short op;
    short mid;
    short pid;
    short color;
    short max;
    short score;

    unordered_map<short, Node> tree;

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