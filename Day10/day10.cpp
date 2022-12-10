#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>

using namespace std;

class Day10 {
    private:
    int _registers = 1;
    int _result = 1;
    int _cycles = 20;
    int _ans = 0;
    int _p_two = 0;
    string _draw;

    public:
    Day10() {}
    ~Day10() {}
    void incrementCycles() {
        _draw += abs(_p_two - _result) <= 1 ? "#" : ".";
        _p_two++;
        if(_p_two == 40) {
            _p_two = 0;
            cout << _draw << endl;
            _draw.clear();
        }
        if(_registers++ == _cycles) {
            _ans += _result * _cycles;
            _cycles += 40;
        }
    }
    void solve(ifstream& file) {
        string line;
        while(getline(file, line)) {
            if(line[0] == 'n') {
                incrementCycles();
            } else {
                incrementCycles();
                incrementCycles();
                this->_result += stoi(line.substr(5));
            }
        }
        cout << "part_one: " << _ans << endl;
    }
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
    Day10 puzzle;
    puzzle.solve(file);
}