#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <queue>
#include <bits/stdc++.h>

using namespace std;

class Day12 {
public:
    void solve(ifstream& file) {
        parse(file);
        cout << "part_one: " << bfs() << endl;
        int shortest_path = INT_MAX;
        for(size_t i = 0; i < _graph.size(); ++i) {
            for(size_t j = 0; j < _graph[0].size(); ++j) {
                if(_graph[i][j] == 'a') {
                    _queues = {};
                    _position = {i, j};
                    shortest_path = min(shortest_path, bfs());
                }
            }
        }
        cout << "second_part: " << shortest_path << endl;
    }

    int bfs() {
        int x = _graph.size(), y = _graph[0].size();
        bool **visited = new bool*[_graph.size()];
        for(size_t i = 0; i < x; i++) {
            visited[i] = new bool[y];
            for(size_t j = 0; j < y; ++j) {
                visited[i][j] = false;
            }
        }
        _queues.push(make_pair(_position, 0));
        while(!_queues.empty()) {
            pair<pair<int, int>, int> current = _queues.front();
            _queues.pop();
            if(visited[current.first.first][current.first.second]) {
                continue;
            }
            visited[current.first.first][current.first.second] = true;
            if(current.first.first == _destination.first && current.first.second == _destination.second) {
               return current.second;
            }
            update_neighbours(current, visited);
        }
        return INT_MAX;
    }

    void update_neighbours(const pair<pair<int, int>, int>& current, bool **visited) {
        const vector<pair<int, int>> neighbours = {
            {1, 0},
            {-1, 0},
            {0, 1},
            {0, -1}
        };
        int col = _graph.size();
        int raw = _graph[0].size();
        for(auto& neighbour: neighbours) {
            int x = current.first.first + neighbour.first;
            int y = current.first.second + neighbour.second;
            if (x < 0 || y < 0 || x >= col || y >= raw) {
                continue;    
            } 
            if (_graph[x][y] <= _graph[current.first.first][current.first.second] + 1) {
                _queues.emplace(make_pair(x, y), current.second + 1);
            }
    }
    }

    void parse(ifstream& file) {
        int x = 0, y = 0;
        bool start = false, end = false;
        string line;
        while(getline(file, line)) {
            if(!start || !end) {
                if((y = line.find("S")) != string::npos) {
                    _position.first = x;
                    _position.second = y;
                    start = true;
                } if((y = line.find("E")) != string::npos){
                    _destination.first = x;
                    _destination.second = y;
                    end = true;
                }
            }
            x++;
            _graph.push_back(line);
        }
        _graph[_position.first][_position.second] = 'a';
        _graph[_destination.first][_destination.second] = 'z';
    }

private:
    vector<string> _graph;
    pair<int, int>  _position, _destination;
    queue<pair<pair<int, int>, int> > _queues;
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