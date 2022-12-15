#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <utility>

using namespace std;

struct pair_hash {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return v.first*31+v.second;
    }
};

class Day14 {
public:
    void create_file(void) {
        _outfile.open("outfile.csv", ios_base::trunc);
        for(int i = 0; i < 200; ++i) {
           for(int j = 0; j < 600; ++j) {
               _outfile << _map[j][i];
           }
           _outfile << "\n";
        }
    }
    void solve(ifstream& file) {
        string line;
        for(size_t i = 0; i < 200; ++i) {
            for(size_t j = 0; j < 600; ++j) {
                _map[j][i] = '.';
            }
        }
        _map[500][0] = '+';
        while(getline(file, line)) {
            draw_rock(line);
        }
        int x = 500, y = 0, result = 0;
        while(true) {
            if(y == _row) break;
            //check down
            if(_map[x][y + 1] == '.') {
                y++;
                continue;
            }
            //check down left
            if(x == 0) break;
//            if((_map[x][y + 1] == 'o' && _map[x - 1][y + 1] == '.') || (_map[x][y + 1] == '#' && _map[x - 1][y + 1] == '.')) {
            if((_map[x][y + 1] != '.' && _map[x - 1][y + 1] == '.')) {
                cout << "im here\n";
                x--;
                y++;
                continue;
            }
            if(x + 1 == _col) break;
            //check down right
//            if((_map[x][y + 1] == 'o' && _map[x + 1][y + 1] == '.') || (_map[x][y + 1] == '#' && _map[x + 1][y + 1] == '.')) {
            if((_map[x][y + 1] != '.' && _map[x + 1][y + 1] == '.')) {
                cout << "im here1\n";
                x++;
                y++;
                continue;
            }
            _map[x][y] = 'o';
            cout << "x: " << x << " and y" << y << endl;
            if(x == 500 && y == 0) break;
            static int d = 0;
//            if(d++ == 24) {
//                create_file();
//                exit(0);
//            }
            result++;
            x = 500;
            y = 0;
        }
        create_file();
        cout << "part_one: " << result << endl;
    }

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


    void draw_rock(int x, int x2, int y, int y2) {
        if (x == x2) {
            if (y > y2) {
                while(y2 <= y) {
                    _map[x][y2] = '#';
                    _pairs.insert({x, y2});
                    y2++;
                }
            }
            if(y2 > y) {
                while(y <= y2) {
                    _map[x][y] = '#';
                    _pairs.insert({x, y});
                    y++;
                }
            }
        } else if(x > x2) {
            while(x2 <= x) {
                _map[x2][y2] = '#';
                _pairs.insert({x2, y2});
                x2++;
            }
        } else {
            while (x <= x2) {
                _map[x][y] = '#';
                _pairs.insert({x, y});
                x++;
            }
        }
        (x > x2) ? _col = x : _col = x2;
        (y > y2) ? _row = y : _row = y2;
    }

    void draw_rock(string& line) {
        vector<string> items;
        items = split(line, " -> ");
        vector<pair<int, int>> lists;
        for(auto& x: items) {
            vector<string> tmp = split(x, ",");
            lists.push_back({stoi(tmp[0]), stoi(tmp[1])});
        }
        int len = 0;
        while(len < lists.size() - 1) {
            draw_rock(lists[len].first, lists[len + 1].first, lists[len].second, lists[len + 1].second);
            len++;
        }
    }
private:
    char _map[600][200];
    unordered_set<pair<int, int>, pair_hash> _pairs;
    ofstream _outfile;
    int _col, _row;
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
    Day14 puzzle;
    puzzle.solve(file);
}

//tested 787 too low