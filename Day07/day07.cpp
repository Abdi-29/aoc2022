#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

void add_cd(const string& line, stack<string>& cd) {
    stringstream ss(line.substr(5));
    string dir;
    ss >> dir;
    string path;
    if(!cd.empty()) {
        path = cd.top() + dir + "/";
    } else {
        path = dir;
    }
    cd.push(path);
}

int get_value(const string& line) {
    stringstream ss(line);
    string num;
    ss >> num;
    return stoi(num);
}

void solve(ifstream& file) {
    string line;
    map<string, int> devices;
    stack<string> cd;
    int value = 0;
    while(getline(file, line)) {
        if(line.find("$ cd") != string::npos && line[5] != '.') {
            add_cd(line, cd);
        } else if(line.find("$ cd ..") != string::npos) {
            string tmp = cd.top();
            cd.pop();
            devices[cd.top()] += devices[tmp];
        } else if(isdigit(line[0])) {
            value += get_value(line);
            if(!isdigit(file.peek())) {
                if(devices.find(cd.top()) != devices.end())
                    devices[cd.top()] += value;
                else
                    devices[cd.top()] = value;
                value = 0;
            }
        }
    }
    int part_one = 0;
    while(cd.size() > 1) {
        string tmp = cd.top();
        cd.pop();
        devices["/"] += devices[tmp];
    }
    int tot = 70000000 - devices["/"];
    tot = 30000000 - tot;
    vector<int> list;
    for(auto& x: devices) {
        if (x.second < 100000) {
            part_one += x.second;
        }
        if(x.second >= tot) {
            list.push_back(x.second);
        }
    }
    sort(list.begin(), list.end());
    cout << "part_one: " << part_one << endl;
    cout << "part_two: " << list[0] << endl;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "expected 2 arguments\n";
        return 1;
    }
    ifstream file(argv[1]);
    if (!file) {
        cout << "error on opening the file\n";
        return 1;
    }
    solve(file);
}
