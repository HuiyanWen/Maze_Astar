#include "stdafx.h"
#include <iostream>
#include "A_single.h"
#include "fstream"
#include "init.h"
#include "utils.h"

using namespace std;

int main()
{
	map<string, string>fname;
	CParseIniFile config;
	char* config_path = "config.ini";
	bool flag = config.ReadConfig(config_path, fname, "method");
	if (!flag) return -1;
	switch (stoi(fname["method"])) {
	case 0:
		A_single(config_path);
		break;
	}
	cout << "Please click enter to exit." << endl;
	char ch;
	while (1) {
		if ((ch = getchar()) == '\n')
			break;
	}
	
}
//
//#include "stdafx.h"
//#include <iostream>
//#include "maze.h"
//
//using std::cin;
//using std::cout;
//using std::endl;
//
//int main()
//{
//	FILE *stream1;
//	if (freopen_s(&stream1, "L:/why_workspace/maze.dat", "r", stdin) != 0)
//	{
//		std::cout << "freopen failed" << std::endl;
//		exit(0);
//	}
//	int m, n;    //m,n 表示迷宫的规模，m行n列
//	cin >> m >> n;
//	cout << m << " " << n << endl;
//	Maze maze(m, n);
//	cin >> maze.start.row >> maze.start.col;
//	cin >> maze.end.row >> maze.end.col;
//	for (int i = 0; i < m; ++i)
//	{
//		for (int j = 0; j < n; ++j)
//		{
//			cin >> maze.map[i][j].isWay;
//			maze.map[i][j].place.row = i;
//			maze.map[i][j].place.col = j;
//		}
//	}
//
//	Mat img = Mat::zeros(40 * maze.row, 40 * maze.col, CV_8UC3);
//	drawMaze(img, maze);
//
//	stack<Grid*> t_solution = maze_solution(maze, img);
//	stack<Grid*> solution;
//	while (!t_solution.empty())
//	{
//		solution.push(t_solution.top());
//		t_solution.pop();
//	}
//	if (solution.empty())
//	{
//		cout << "No solution";
//	}
//	else
//	{
//		while (!solution.empty())
//		{
//			cout << solution.top()->place;
//			solution.pop();
//			if (!solution.empty())
//				cout << "->";
//		}
//		cout << endl;
//	}
//
//	return 0;
//}
