#ifndef MAZE_MAZE_H
#define MAZE_MAZE_H

#include <stack>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

struct M_Point
{
	int row;
	int col;

	bool operator== (const M_Point &p)
	{
		return ((this->row == p.row) && (this->col == p.col));
	}
	friend ostream& operator<< (ostream &os, M_Point &point)
	{
		os << '(' << point.row << ',' << point.col << ')';
		return os;
	}
};

struct Grid
{
	M_Point place;
	int direction = 0;
	bool isWay;
	bool isPassed = false;
};

struct Maze
{
	int row;
	int col;
	M_Point start;
	M_Point end;
	Grid** map = NULL;

	Maze(int m, int n) :row(m), col(n)
	{
		if (m == 0 || n == 0)
			return;
		map = new Grid*[m];
		for (int i = 0; i < m; ++i)
		{
			map[i] = new Grid[n];
		}
	}

	~Maze()
	{
		if (map == NULL || row == 0 || col == 0)
			return;
		else
		{
			for (int i = 0; i < row; ++i)
			{
				delete[](map[i]);
			}
			delete[](map);
		}
	}
};

const Scalar wall_color(255, 255, 255);
const Scalar way_color(120, 120, 120);
const Scalar pass_color(100, 150, 100);
const Scalar pass_color2(200, 5, 100);
const Scalar start_color(0, 0, 255);
const Scalar end_color(0, 255, 0);

const Scalar color2(219, 165, 0);
const Scalar color4(0, 176, 240);
const int gap = 2;
const int delay = 200;

void drawBlock(Mat &img, int row, int col, int height, int width, Scalar color)
{
	Point p1 = Point(col * width + gap, row * height + gap);
	Point p2 = Point((col + 1) * width - gap, (row + 1) * height - gap);
	rectangle(img, p1, p2, color, -1);
}

bool isWay(int i, int j, list<my_Point *> path){
	for (auto &p : path) {
		if (i == p->x&&j == p->y) return true;
	}
	return false;
}

void drawMaze(Mat &img, vector<vector<int>> maze, list<my_Point *> path, my_Point start, my_Point end)
{
	int row = maze.size();
	int col = maze[0].size();
	int height = img.rows / row;
	int width = img.cols / col;
	
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (i == start.x&&j == start.y)
			{
				drawBlock(img, i, j, height, width, start_color);
			}
			else if (i == end.x&&j == end.y) {
				drawBlock(img, i, j, height, width, end_color);
			}
			else
			{
				if (isWay(i, j, path))
					drawBlock(img, i, j, height, width, pass_color);								
				else if(maze[i][j]==0)
					drawBlock(img, i, j, height, width, wall_color);
				else if (maze[i][j] == 2)
					drawBlock(img, i, j, height, width, color2);
				else if (maze[i][j] == 4)
					drawBlock(img, i, j, height, width, color4);
				else if (maze[i][j] == 1)
					drawBlock(img, i, j, height, width, way_color);
			}
		}
	}
	//drawBlock(img, start.x, start.y, height, width, start_end_color);
	//drawBlock(img, end.x, end.y, height, width, start_end_color);
	int row_count = row/5;
	for(int i = 0; i<=row_count; i++){
		if (i <=1 ) {
			putText(img, to_string(i*5), Point(0 * width + 5, (i * 5) * height + 15), 1, 0.8, Scalar(0, 0, 0), 1, 1);
		}
		else {
			putText(img, to_string(i*5), Point(0 * width + 2, (i * 5) * height + 15), 1, 0.8, Scalar(0, 0, 0), 1, 1);
		}
	}
	int col_count = col / 5;
	for (int i = 0; i <= col_count; i++) {
		if (i <= 1) {
			putText(img, to_string(i * 5), Point((i * 5) * width + 5, 0 * height + 15), 1, 0.8, Scalar(0, 0, 0), 1, 1);
		}
		else {
			putText(img, to_string(i * 5), Point((i * 5) * width + 2,0 * height + 15), 1, 0.8, Scalar(0, 0, 0), 1, 1);
		}
	}

	imshow("maze", img);
	waitKey(0);
}

void drawMaze_bidirection(Mat &img, vector<vector<int>> maze, list<my_Point *> path1, list<my_Point *> path2, my_Point start, my_Point end)
{
	int row = maze.size();
	int col = maze[0].size();
	int height = img.rows / row;
	int width = img.cols / col;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (i == start.x&&j == start.y)
			{
				drawBlock(img, i, j, height, width, start_color);
			}
			else if (i == end.x&&j == end.y) {
				drawBlock(img, i, j, height, width, end_color);
			}
			else
			{
				if (isWay(i, j, path1))
					drawBlock(img, i, j, height, width, pass_color);
				else if (isWay(i, j, path2))
					drawBlock(img, i, j, height, width, pass_color2);
				else if (maze[i][j] == 0)
					drawBlock(img, i, j, height, width, wall_color);
				else if (maze[i][j] == 2)
					drawBlock(img, i, j, height, width, color2);
				else if (maze[i][j] == 4)
					drawBlock(img, i, j, height, width, color4);
				else if (maze[i][j] == 1)
					drawBlock(img, i, j, height, width, way_color);
			}
		}
	}
	int row_count = row / 5;
	for (int i = 0; i <= row_count; i++) {
		if (i <= 1) {
			putText(img, to_string(i * 5), Point(0 * width + 5, (i * 5) * height + 15), 1, 0.8, Scalar(0, 0, 0), 1, 1);
		}
		else {
			putText(img, to_string(i * 5), Point(0 * width + 2, (i * 5) * height + 15), 1, 0.8, Scalar(0, 0, 0), 1, 1);
		}
	}
	int col_count = col / 5;
	for (int i = 0; i <= col_count; i++) {
		if (i <= 1) {
			putText(img, to_string(i * 5), Point((i * 5) * width + 5, 0 * height + 15), 1, 0.8, Scalar(0, 0, 0), 1, 1);
		}
		else {
			putText(img, to_string(i * 5), Point((i * 5) * width + 2, 0 * height + 15), 1, 0.8, Scalar(0, 0, 0), 1, 1);
		}
	}
	//drawBlock(img, start.x, start.y, height, width, start_end_color);
	//drawBlock(img, end.x, end.y, height, width, start_end_color);
	imshow("maze", img);
	waitKey(0);
}
//
////m表示行，n表示列
//stack<Grid*> maze_solution(const Maze &maze, Mat &img)
//{
//	int height = img.rows / maze.row;
//	int width = img.cols / maze.col;
//
//	Grid** map = maze.map;
//	stack<Grid*> way;
//
//	//起点或终点不在迷宫内
//	if (maze.start.row >= maze.row || maze.start.col >= maze.col
//		|| maze.end.row >= maze.row || maze.end.col >= maze.col)
//		return way;
//
//	Grid *current = &map[maze.start.row][maze.start.col];
//	do
//	{
//		//当前的位置是可行路径且之前未经过
//		if (current->isWay && !current->isPassed)
//		{
//			current->isPassed = true;
//			way.push(current);
//
//			//如果到达终点，则返回该条路径
//			if (current->place == maze.end)
//			{
//				waitKey(0);
//				return way;
//			}
//			else
//			{
//				if (!(current->place == maze.start))
//					drawBlock(img, current->place.row, current->place.col, height, width, pass_color);
//				imshow("maze", img);
//				waitKey(delay);
//				//默认每次先探索右边的方向
//				current = &map[current->place.row][current->place.col + 1];
//			}
//		}
//		else
//		{
//			//当前路径非空，则继续探索当前格的其余方向直到所有方向都探索完成
//			while (true)
//			{
//				if (!way.empty())
//				{
//					current = way.top();
//					++current->direction;
//
//					//探索四个方向
//					if (current->direction != 4)
//					{
//						//direction可能值有1,2,3分别代表下，左，上
//						switch (current->direction)
//						{
//						case 1://探索下边的格子
//						{
//							current = &map[current->place.row + 1][current->place.col];
//							break;
//						}
//						case 2://探索左边的格子
//						{
//							current = &map[current->place.row][current->place.col - 1];
//							break;
//						}
//						case 3://探索上边的格子
//						{
//							current = &map[current->place.row - 1][current->place.col];
//							break;
//						}
//						}
//						break;
//					}
//					else
//					{    //此路不通
//						way.pop();
//						drawBlock(img, current->place.row, current->place.col, height, width, way_color);
//						imshow("maze", img);
//						waitKey(delay);
//					}
//				}
//				else
//					break;
//			}
//		}
//	} while (!way.empty());
//	return way;
//}
#endif //MAZE_MAZE_H
