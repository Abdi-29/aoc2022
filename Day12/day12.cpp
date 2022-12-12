#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

class Day12 {
public:
    void solve(ifstream& file) {
        parse(file);
        bfs();
    }

    void bfs() {
        int x = _graph[0].size(), y = _graph.size();
        bool **visited = new bool*[_graph.size()];
        for(size_t i = 0; i < x; i++) {
            visited[i] = new bool[x];
            for(size_t j = 0; j < y; ++j) {
                visited[i][j] = false;
            }
        }
        _queues.push(make_pair(_position, 0));
        while(!_queues.empty()) {
            pair<pair<int, int>, int> current = _queues.front();
            _queues.pop();
            update_neighbours(current, visited);
        }
    }

    void update_neighbours(const pair<pair<int, int>, int>& current, bool **visited) {
        _x = current.first.first, _y = current.first.second;
        int count = current.second;
        visited[_x][_y] = true;
        cout << _x << " " << _y << endl;
        pair<int, int> tmp = make_pair(_x, _y);
        if(_x - 1 >= 0 && !visited[_x - 1][_y]) {
            tmp.first--;
            cout << "boolean: " << visited[_x - 1][_y] << endl;
            _queues.push(make_pair(tmp, count++));
            cout << "neighbours: " << _x - 1 << " " << _y << endl;
        }
        if (_x + 1 < _graph.size() && !visited[_x + 1][_y]) {
            tmp.first++;
            _queues.push(make_pair(tmp, count++));
            cout << "nei: " << _x + 1 << " " << _y << endl;
        }
        if(_y - 1 > 0 && !visited[_x][_y - 1]) {
            tmp.second--;
            _queues.push(make_pair(tmp, count++));
            cout << "neighbours2222: " << _x << " " << _y - 1 << endl;
        }
        if (_y + 1 < _graph[0].size() && !visited[_x][_y + 1]) {
            tmp.second++;
            _queues.push(make_pair(tmp, count++));
            cout << "nei222: " << _x << " " << _y + 1 << endl;
        }
        cout << "testing\n";
        static int n = 0;
        if(n++ == 2)
        exit(0);
    }

    void parse(ifstream& file) {
        int x = 0, y = 0;
        bool find = false;
        string line;
        while(getline(file, line)) {
            if(!find) {
                if((y = line.find("S")) != string::npos) {
                    _position.first = x;
                    _position.second = y;
                    find = true;
                }
            }
            x++;
            _graph.push_back(line);
        }
    }

private:
    vector<string> _graph;
    pair<int, int>  _position;
    queue<pair<pair<int, int>, int> > _queues;
    int _x, _y;
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
    Day12 puzzle;
    puzzle.solve(file);
}