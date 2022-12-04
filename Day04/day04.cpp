#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int fully_contains_2(const string& ids) {
    int first_dash = ids.find('-');
    int comma = ids.find(',');
    int second_dash = ids.find('-', comma);
    vector<int> vec;
    vec.push_back(atoi(ids.substr(0, first_dash).c_str()));
    vec.push_back(atoi(ids.substr(first_dash + 1, comma - first_dash).c_str()));
    vec.push_back(atoi(ids.substr(comma + 1, second_dash - comma).c_str()));
    vec.push_back(atoi(ids.substr(second_dash + 1).c_str()));      
    return ((vec[0] >= vec[2] && vec[1] <= vec[3]) ||
            (vec[1] >= vec[2] && vec[0] <= vec[3]));
}

int fully_contains(const string& ids) {
    int first_dash = ids.find('-');
    int comma = ids.find(',');
    int second_dash = ids.find('-', comma);
    vector<int> vec;
    vec.push_back(atoi(ids.substr(0, first_dash).c_str()));
    vec.push_back(atoi(ids.substr(first_dash + 1, comma - first_dash).c_str()));
    vec.push_back(atoi(ids.substr(comma + 1, second_dash - comma).c_str()));
    vec.push_back(atoi(ids.substr(second_dash + 1).c_str()));      
    return ((vec[0] >= vec[2] && vec[1] <= vec[3]) || 
            (vec[0] <= vec[2] && vec[1] >= vec[3]));
}

int part_one(ifstream& file) {
    string line;
    size_t pairs = 0;
    while(getline(file, line)) {
        pairs += fully_contains(line);
    }
    return pairs;
}

int part_two(ifstream& file) {
    string line;
    size_t pairs = 0;
    while(getline(file, line)) {
        pairs += fully_contains_2(line);
    }
    return pairs;
}

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
    cout << "part_one: " << part_one(file) << "\n";
    file.clear();
    file.seekg(0, std::ios::beg);
    cout << "part_two: " << part_two(file) << "\n";
}