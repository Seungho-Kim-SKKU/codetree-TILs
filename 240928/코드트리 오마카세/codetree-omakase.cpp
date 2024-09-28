#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define endl "\n"

struct Query {
    int cmd;
    int t;
    int x;
    int n;
    string name;
};

struct Sushi {
    int time;
    int loc;
};

struct Human {
    int time;
    int loc;
    int num;
};

int L, Q;
vector<Query> queries;
unordered_map<string, vector<Sushi>> S;
unordered_map<string, Human> H;
int curS = 0;
int curH = 0;

bool cmp(Query q1, Query q2) {
    if (q1.t != q2.t) {
        return q1.t < q2.t;
    }
    return q1.cmd < q2.cmd;    
}

int main() {
    cin >> L >> Q;

    for (int i = 0; i < Q; i++) {
        int cmd = -1;
        int t = -1;
        int x = -1;
        int n = -1;
        string name;

        cin >> cmd;

        if (cmd == 100) {
            cin >> t >> x >> name;

            Sushi s = {t, x};
            S[name].push_back(s);
        }
        else if (cmd == 200) {
            cin >> t >> x >> name >> n;

            Human h = {t, x, n};
            H[name] = h;
        }
        else {
            cin >> t;
        }

        queries.push_back({cmd, t, x, n, name});
    }

    for (auto& itH: H) {
        int exitTime = 0;
        // cout << itH.first << endl;

        for (auto& itS: S[itH.first]) {
            int timeH = itH.second.time; 
            int locH = itH.second.loc; 
            int timeS = itS.time; 
            int locS = itS.loc;
            int diffLoc = 0;
            // cout << time << " " << timeH <<endl;
            // cout << timeS << endl;
            if (timeH < timeS) {
                diffLoc = (locH - locS) % L
            }
            else {
                int nowLocS = timeH - timeS;
                locH += (locH + nowLocS) % L;
                diffLoc = (locH - locS) % L;                
            }
            timeS += diffLoc;

            queries.push_back({101, timeS, -1, -1, itH.first});
            // cout << timeS << endl;
            exitTime = max(exitTime, timeS);
        }
        // cout << "EXIT " << exitTime << endl;
        queries.push_back({201, exitTime, -1, -1, itH.first});
    }

    sort(queries.begin(), queries.end(), cmp);

    for (auto& it: queries) {
        if (it.cmd == 100) {
            curS++;
        }
        else if (it.cmd == 101) {
            curS--;
        }
        else if (it.cmd == 200) {
            curH++;
        }
        else if (it.cmd == 201) {
            curH--;
        }
        else {
            cout << curH << " " << curS << endl;
        }
    }

    return 0;
}