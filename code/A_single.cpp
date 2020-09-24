#include "stdafx.h"
#include "utils.h"
#include "init.h"
#include "A_single.h"
#include "Astar.h"
#include "maze.h"

using namespace std;

void A_single(char* init_path) {
	const char *data_path;
	int row, col, whether_bidirection;
	map<string, string>fname;
	CParseIniFile config;
	bool flag = config.ReadConfig(init_path, fname, "0");
	if (flag) {
		row = stoi(fname["row"]);
		col = stoi(fname["col"]);
		whether_bidirection = stoi(fname["whether_bidirection"]);
		data_path = fname["data_path"].c_str();
	}
	else {
		cout << "Loading ini 0 error!" << endl;
		return;
	}

	int *temp = (int*)malloc((row * col + 6) * sizeof(int));
	fstream file;
	file.open(data_path, ios::in);
	if (!file)
	{
		cout << "Loading 0 error！" << endl;
		exit(1);
	}
	int num = 0;
	while (!file.eof()) {
		file >> temp[num];
		num++;
	}
	file.close();
	cout << num << endl;
	vector<vector<int>> maze(temp[4], vector<int>(temp[5]));
	for (int i = 0; i < temp[4]; i++) {
		if (i == 5) {
			;
		}
		for (int j = 0; j < temp[5]; j++) {
			maze[i][j] = temp[i*temp[5] + j + 6];
		}
	}

	
	//设置起始和结束点
	my_Point start(temp[0], temp[1]);
	my_Point end(temp[2], temp[3]);
	Astar astar;
	astar.InitAstar(maze);

	list<my_Point *> path;
	list<my_Point *> path1;
	list<my_Point *> path2;
	if(!whether_bidirection)
		path = astar.GetPath(start, end, true, maze);
	else {
		astar.GetPath_bidirection(start, end, true, maze, path1, path2);
	}
	//打印
	for (auto &p : path1)
		cout << '(' << p->x << ',' << p->y << ')' << endl;
	Mat img = Mat::zeros(20 * maze.size(), 20 * maze[0].size(), CV_8UC3);
	
	if (!whether_bidirection) drawMaze(img, maze, path, start, end);
	else	drawMaze_bidirection(img, maze, path1, path2, start, end);
	system("pause");
	return ;
}