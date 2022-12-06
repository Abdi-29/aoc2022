#include <iostream>
#include <fstream>

using namespace std;

bool c_in_string(const string& str, char c) {

    for (const auto& x: str){
        if (x == c) {
            return true;
        }
    }
    return false;
}

bool no_doublicate(const string& str) {
    int checker = 0;
    for(const auto& x: str) {
        int val = x - 'a';
        if ((checker & (1 << val))) {
            return true;
        }
        checker |= (1 << val);
    }
    return false;
}


int get_position(const string& line, int c) {
    size_t i = 0;
    for(;i < line.length(); ++i) {
        string sub = line.substr(i, c);
        char marker = line[c + i];
        if(!c_in_string(sub, marker) && !no_doublicate(sub)) {
                return c + i + 1;
        }
    }
    return i;
}

void solve(ifstream& file) {
    string line;
    while(getline(file, line)) {
        cout << "first part: " << get_position(line, 3) << "\n";
        cout << "second part: " << get_position(line, 13) << "\n";
    }
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