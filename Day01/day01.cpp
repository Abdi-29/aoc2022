#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<int> part_one(ifstream& file) {
    string line;
    vector<int> result;
    int value = 0;

    while (getline(file, line)) {
        if (isdigit(line[0])) {
            value += stoi(line);
        } else {
            if (value)
                result.push_back(value);
            value = 0;
        }
    }
    result.push_back(value);
    return result;
}

vector<int> part_two(vector<int> result) {
    std::sort(result.begin(), result.end());
    vector<int> tmp(result.end() - 3, result.end());
    return tmp;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "expected 2 file\n";
        return 1;
    }
    ifstream file(argv[1]);
    if (!file) {
        cout << "error on opening the file\n";
        return 1;
    }
    vector<int> result = part_one(file);
    cout << "part_one = " << *std::max_element(result.begin(), result.end())  << endl;
    vector<int> result2 = part_two(result);
    int sum = 0;
    for (auto &n: result2) {
        sum += n;
    }
    cout << "part_two = " << sum << endl;
}
