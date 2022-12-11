#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <utility>
#include <cmath>

using namespace std;

class Day11 {
private:
    vector<Day11> _monkeys;
    vector<int> _items;
    int _left;
    int _right;
    int _test;
    string _operation;
    string  _name;
    char _sign;
    int _result;

public:
    void	skipWhiteSpaces(std::istream& file) {
        file >> std::ws;
    }

    void get_items(const string& items) {
        string num;
        for(auto& x: items) {
            if(isdigit(x)) {
                num += x;
            } else if(!num.empty()){
                _items.push_back(stoi(num));
                num = string();
            }
        }
        if(!num.empty()) {
             _items.push_back(stoi(num));
        }
    }

    void solve(ifstream& file) {
        string line;
        Day11 monkey;
        monkey._name = _name;
        while(getline(file, line)) {
            parse(line[0], line, monkey);
            skipWhiteSpaces(file);
        }
        monkey._result = 0;
        _monkeys.push_back(monkey);
        for(auto& x: _monkeys) {

            cout << x._sign << endl;
        }
        rounds();
        for(auto &x: _monkeys) {
            cout << x._result << " ";
        }
    }

    void do_math(Day11& monkey) {
        int operation;
        for(auto& x: monkey._items) {
        monkey._operation.find("old") != string::npos ? operation = x : operation = stoi(monkey._operation);
            monkey._sign == '*' ? x *= operation : x += operation;
            double tmp = (x / 3);
            tmp = round(tmp);
            x = tmp;
            if(x % monkey._test == 0) {
                _monkeys[monkey._left]._items.push_back(x);
                _monkeys[monkey._left]._result++;
            } else {
                _monkeys[monkey._right]._items.push_back(x);
                _monkeys[monkey._right]._result++;
            }
        }
        monkey._items.clear();
    }
    void rounds() {
        for(size_t i = 0; i < 20; ++i) {
            for(size_t j = 0; j < _monkeys.size(); ++j) {
                if (_monkeys[j]._items.empty()) {
                    continue;
                }
                do_math(_monkeys[j]);
            }
        }
    }

    void parse(char c, const string& line, Day11& monkey) {
        switch (c) {
            case 'M':
                if(!monkey._name.empty()) {
                    monkey._result = 0;
                    _monkeys.push_back(monkey);
                    _name = string();
                    monkey = Day11();
                    _items.clear();
                }
                _name = string();
                _name.reserve(8);
                monkey._name = line.substr(7,  line.length() - 1);
                break;
            case 'S':
                get_items(line);
                monkey._items = _items;
                break;
            case 'O':
                monkey._operation = line.substr(23);
                monkey._sign = line[21];
                break;
            case 'T':
                monkey._test = stoi(line.substr(19));
                break;
            default:
              if(line.find("true") != string::npos) {
                  monkey._left = stoi(line.substr(24, line.length()));
              }  else{
                  monkey._right = stoi(line.substr(25, line.length()));
              }
        }
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
    Day11 puzzle;
    puzzle.solve(file);
}