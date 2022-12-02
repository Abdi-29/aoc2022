#include <iostream>
#include <fstream>

using namespace std;

enum strategy {ROCK = 0, PAPER = 1, SCISSORS = 2};
enum round {LOST = 0, DRAW = 3, WON = 6};

strategy get_shape_selected(char shape) {
	switch (shape) {
		case 'A':
		case 'X':	
			return ROCK;
		case 'B':
		case 'Y':	
			return PAPER;
		default:
			return SCISSORS;
	}
}

round part_one(strategy opponent, strategy mine) {
	switch (opponent) {
		case ROCK:
			if (mine == PAPER) {
				return WON;
			}
			break;
		case SCISSORS:
			if (mine == ROCK) {
				return WON;
			}
			break;
		default:
			if (mine == SCISSORS)
				return WON;
	}
	return LOST;
}

strategy part_two_winning(strategy opponent) {
	switch (opponent) {
		case ROCK:
			return PAPER;
		case PAPER:
			return SCISSORS;
		default:
			return ROCK;
	}
}

strategy part_two_losing(strategy opponent) {
	switch (opponent) {
		case ROCK:
			return SCISSORS;
		case PAPER:
			return ROCK;
		default:
			return PAPER;
	}
}

int part_two(strategy opponent, strategy mine) {
	switch (mine) {
		case ROCK:
			return LOST + part_two_losing(opponent);
		case PAPER:
			return DRAW + opponent;
		default:
			return WON + part_two_winning(opponent);
	}
}

int *solve(ifstream &file) {
	string line;
	int *result = new int[2];
	result[0] = 0, result[1] = 0;
	while(getline(file, line)) {
		strategy opponent = get_shape_selected(line[0]);
		strategy mine = get_shape_selected(line[2]);
		result[1] += part_two(opponent, mine) + 1;
		if (opponent == mine) {
			result[0] += mine + 1 + DRAW;
		} else {
			result[0] += part_one(opponent, mine) + mine + 1;
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
	int *result = solve(file); 
	cout << "part 1 " << result[0] << endl; 
	cout << "part two " << result[1] << endl;
}
