#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

struct pairs {
    string left;
    string right;
    string sign;
    int64_t value;
    bool value_set;
};

class Day21 {
public:
    vector<string> split(string& s, const string& del) {
        vector<string> result;
        size_t pos;
        while((pos = s.find(del)) != string::npos) {
            result.push_back(s.substr(0, pos));
            s.erase(0, pos + del.length());
        }
        result.push_back(s);
        return result;
    }

    int64_t recurse(const string& name) {
      if(_parse[name].value_set) {
          return _parse[name].value;
      }
        int64_t left_value = recurse(_parse[name].left);
        int64_t right_value = recurse(_parse[name].right);
        switch (_parse[name].sign[0]) {
            case '+':
                return left_value + right_value;
            case '-':
                return left_value - right_value;
            case '/':
                return left_value / right_value;
            case '*':
                return left_value * right_value;
            default:
                return -1;
        }
    }

    void solve(ifstream& file) {
        string line;
        while(getline(file, line)) {
           vector<string> res = split(line, ": ");
           vector<string> monkeys = split(res[1], " ");
            pairs monkey;
            monkey.left = monkeys[0];
            monkey.value_set = false;
            if(isdigit(monkey.left[0])) {
                monkey.value_set = true;
                monkey.value = stoi(monkey.left);
            }
            if (monkeys.size() > 1) {
                monkey.sign = monkeys[1];
                monkey.right = monkeys[2];
            }
            _parse.insert({res[0], monkey});
        }
        cout << "part_one: " << recurse("root") << endl;
    }
private:
    map<string, pairs> _parse;
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
    Day21 puzzle;
    puzzle.solve(file);
}
