#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

#define endl "\n"

typedef struct Sushi {
    int time;
    int loc;
    bool eat;
} sushi;

typedef struct Human {
    int time;
    int loc;
    int num;
} human;

int L, Q;
int op;
int t;
int x;
string name;
int n;
unordered_map<string, vector<Sushi>> S;
unordered_map<string, Human> H;
int curS = 0;
int curH = 0;

void printMap() {
    cout << "Sushi" << endl;
    for (auto& it_1: S) {
        cout << it_1.first << ": ";
        for (auto& it_2: it_1.second) {
            cout << it_2.time << " " << it_2.loc << ", ";
        }
        cout << endl;
    }
    cout << endl << "Human" << endl;
    for (auto& it: H) {
        if (it.second.num != 0) {
            cout << it.first << " " << it.second.time << " " << it.second.loc << " " << it.second.num << endl;
        }
        
    }
    cout << endl;
}

bool eat(int time, string name) {
    int timeH = H[name].time;
    int locH = H[name].loc;
    for (auto& it: S[name]) {
        // cout << name << endl;
        if (H[name].num == 0) {
            return true;
        }
        if (it.eat) {
            continue;
        }
        int timeS = it.time;
        int locS = it.loc;
        // cout << time << " " << timeH <<endl;
        // cout << timeS << " " << locS << endl;
        int diffLoc = (locH - locS) % L; 
        locS = (locS + diffLoc) % L;
        timeS += diffLoc;
        if (timeS < timeH) {
            timeS += L;
        }
        // cout << timeS << " " << locS << endl;

        if (timeS <= time) {
            // cout << "Eat " << name << endl;
            H[name].num--;
            curS--;
            it.eat = true;
        }
        if (H[name].num == 0) {
            curH--;
            return true;
        }
    }
    return false;
}

void eatSushi(int time) {
    for (auto it = H.begin(); it != H.end();) {
        bool flag = eat(time, it->first);

        if (flag == true) {
            it = H.erase(it);
        }
        else {
            it++;
        }
    }
}

int main() {
    cin >> L >> Q;

    for (int i = 0; i < Q; i++) {
        cin >> op;
        if (op == 100) {
            cin >> t >> x >> name;

            sushi s = {t, x, false};
            S[name].push_back(s);
            curS++;
        }
        else if (op == 200) {
            cin >> t >> x >> name >> n;

            human h = {t, x, n};
            H[name] = h;
            curH++;
        }
        else if (op == 300) {
            cin >> t;

            // printMap();
           
            eatSushi(t);
                      
            // printMap();

            cout << curH << " " << curS << endl;
        }
        else {

        }
    }

    return 0;
}