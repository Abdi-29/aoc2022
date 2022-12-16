#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <utility>
#include <algorithm>

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
        for(int i = 0; i < 600; ++i) {
           for(int j = 0; j < 600; ++j) {
               _outfile << _map[i][j];
           }
           _outfile << "\n";
        }
    }
    void solve(ifstream& file) {
        string line;
        _row = 0;
        _col = 0;
        for(size_t i = 0; i < 600; ++i) {
            for(size_t j = 0; j < 600; ++j) {
                _map[i][j] = '.';
            }
        }
        _map[0][500] = '+';
        while(getline(file, line)) {
            draw_rock(line);
        }
        int x = 500, y = 0, result = 0;
        while(true) {
            // cout << "lol: " << _row << "    " << y << endl;
            if(y == _row + 1) {
                _map[y][x] = 'o';
                x = 500;
                y = 0;
                result++;
            }
            //check down
            if(_map[y + 1][x] == '.') {
                y++;
            }
            //check down left
            else if(_map[y + 1][x - 1] == '.') {
                x--;
                y++;
            }
            //check down right
            else if(_map[y + 1][x + 1] == '.') {
                x++;
                y++;
            } else {
                result++;
                if(x == 500 && y == 0) break;
                _map[y][x] = 'o';
                x = 500;
                y = 0;
            }
        }
        create_file();
        cout << "part_two: " << result << endl;
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
        _row = max(_row, max(y, y2));
        _col = max(_col, max(x, x2));
        pair<int, int> mm; 
        if (x == x2) {
            mm = minmax(y, y2);
            for(int i = mm.first; i <= mm.second; i++) {
                _map[i][x2] = '#';
            }
        } else {
            mm = minmax(x, x2);
            for(int i = mm.first; i <= mm.second; i++) {
                _map[y2][i] = '#';
            }
        }
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
    char _map[600][600];
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