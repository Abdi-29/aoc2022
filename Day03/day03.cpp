#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int priority(char c) {
    if (islower(c)) {
        return c - 'a' + 1;
    } else {
        return c - 'A' + 27;
    }
}

bool c_in_string(string str, char c) {
    return str.find(c) != string::npos;
}

char get_rucksack_1(vector<string> vec) {
    string corrent = vec[0];
    for (auto &c: corrent) {
        if (c_in_string(vec[1], c) && c_in_string(vec[2], c)) {
            return c;
        }
    }
    return 64;
}

char get_rucksack(string part_one, string part_two) {
    for(auto &c: part_one) {
        if (c_in_string(part_two, c)){
            return c;
        }
    }
    return 64;
}

int part_one(ifstream& file) {
    string line;
    int result = 0;
    while (getline(file, line)) {
        int len = line.length();
        string part_one = line.substr(0, len / 2);
        string part_two = line.substr(len / 2);
        char c = get_rucksack(part_one, part_two);
        result += priority(c);
    }
    return result;
}

int part_two(ifstream& file) {
    string line;
    vector<string> vec;
    int result = 0;
    while (getline(file, line)) {
        vec.push_back(line);
        if (vec.size() == 3) {
            char c = get_rucksack_1(vec);
            result += priority(c);
            vec.clear();
        }
    }
    return result;
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