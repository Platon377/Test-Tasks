#include <iostream>
#include <vector>
#include <random>
#include <iterator>
#include <ostream>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::shuffle;
using std::ostream;

typedef vector<vector<int>> Maze;

struct Position {
	int x, y;
};

bool isValid(int x, int y, int height, int width, const Maze& maze) {
	return (x > 0 && x < width - 1 && y > 0 && y < height - 1 && maze[y][x] == 1);
}

void carveFrom(int x, int y, int height, int width, Maze& maze) {
	vector<Position> d = { {2,0}, {0,2}, {-2,0},{0,-2} };

	std::random_device rd;
	std::mt19937 g(rd());
	shuffle(d.begin(), d.end(), g);


	for (int i = 0; i < 4; i++) {
		int newX = x + d[i].x;
		int newY = y + d[i].y;

		if (isValid(newX, newY, height, width, maze)) {
			maze[newY][newX] = 0;
			maze[y + d[i].y / 2][x + d[i].x / 2] = 0;
			carveFrom(newX, newY, height, width, maze);
		}
	}
}

Maze createMaze(int height, int width) {
	Maze maze(height, vector<int>(width, 1));
	maze[1][1] = 0;
	carveFrom(1, 1, height, width, maze);
	maze[1][0] = 0;
	maze[height - 2][width - 1] = 0;

	return maze;
}

int main() {
	int height, width;
	cout << "Enter the size of the maze (desirably odd dimensions)" << endl;
	cin >> height >> width;
	
	Maze res = createMaze(height, width);
	for (auto& row : res) {
		for (int cell : row) {
			cout << (cell ? "#" : " ");
		}
		cout << endl;
	}
	return 0;
}