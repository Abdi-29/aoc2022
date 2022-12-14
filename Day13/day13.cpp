#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <stack>

using namespace std;

enum items {
    NUMBER,
    OBJECT
};

struct packet {
    packet() {}
    packet(vector<packet>& tmp): packets(tmp) {}
    ~packet() {}
    packet& operator=(const packet& other) {
        if (this != &other) {
            if(other.type == NUMBER) {
                this->number = other.number;
            } else {
                new (&packets) vector<packet>(other.packets);
            }
        }
        return *this;
    }
    packet(const packet& rh) {}
    union {
        vector<packet> packets;
        int number;
    };
    items type;
};

class Day13 {
public:
    packet parse(string_view line) {
       packet test;
       if(line[0] == '[') {
           test.type = OBJECT;
           while(line[0] != ']') {
               test.packets.push_back(parse(line.substr(1)));
           }
           line = line.substr(1);
       } else if(isdigit(line[0])) {
           while
       }
        return test;
    }

    packet parse_list(string& line, int index) {

    }

    void solve(ifstream& file) {
        _packets.reserve(2);
        string line;
        while(getline(file, line)) {
            if(!line.length()) {
                parse(_packets[0]);
                _packets.clear();
                _packets.reserve(2);
            }
            _packets.push_back(line);
        }
    }

private:
    vector<string> _packets;
//    pair<int, vector<vector<int>>> _result[2];
};

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
    Day13 puzzle;
    puzzle.solve(file);
}