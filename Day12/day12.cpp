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
            if(visited[current.first.first][current.first.second]) {
                continue;
            }
            visited[current.first.first][current.first.second] = true;
            if(current.first.first == _destination.first && current.first.second == _destination.second) {
                cout << "found it: ========================= " << current.second << endl;
                return;
            }
            update_neighbours(current, visited);
        }
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
                } else if((y = line.find("E")) != string::npos){
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