#include "stdafx.h"
#include <math.h>
#include "Astar.h"
#include <iostream>

using namespace std;

void Astar::InitAstar(std::vector<std::vector<int>> &_maze)
{
	maze = _maze;
}

float Astar::calcG(my_Point *temp_start, my_Point *point, std::vector<std::vector<int>> maze)
{
	float extraG = ((abs(point->y - temp_start->y) + abs(point->x - temp_start->x)) == 1) ? kCost1 : kCost2;
	extraG += maze[temp_start->x][temp_start->y];
	float parentG = point->parent == NULL ? 0 : point->parent->G; //如果是初始节点，则父节点为空
	return parentG + extraG;
}


float Astar::calcH(my_Point *point, bool isIgnoreCorner, std::vector<std::vector<int>> maze)
{
	float min_h = 99999;
	auto surroundPoints = getSurroundPoints(point, isIgnoreCorner, closeList);
	for (auto &target : surroundPoints)
	{
		//cout << "point:" << point->x << " " << point->y << endl;
		if (!isInList(closeList, target)) {
			if ((abs(target->x - point->x) + abs(target->y - point->y)) == 1) {//1
				if ((kCost1 + maze[point->x][point->y]) < min_h) min_h = kCost1 + maze[point->x][point->y];
			}
			else {
				if (kCost2 + maze[point->x][point->y] < min_h) min_h = kCost2 + maze[point->x][point->y];
			}
			//cout << "target:" << target->x << " " << target->y << endl;
		}
	}
	return min_h;
}

float Astar::calcF(my_Point *point)
{
	return point->G + point->H;
}

my_Point *Astar::getLeastFpoint(std::list<my_Point *> openList_temp)
{
	if (!openList_temp.empty())
	{
		auto resPoint = openList_temp.front();
		for (auto &point : openList_temp)
			if (point->F<resPoint->F)
				resPoint = point;
		return resPoint;
	}
	return NULL;
}

my_Point *Astar::findPath(my_Point &startPoint, my_Point &endPoint, bool isIgnoreCorner, std::vector<std::vector<int>> maze)
{
	openList.push_back(new my_Point(startPoint.x, startPoint.y));
	while (!openList.empty())
	{
		auto curPoint = getLeastFpoint(openList); 
		cout << "(" << curPoint->x << "," << curPoint->y << ") ";
		cout << "F:" << curPoint->F << "," << "G:" << curPoint->G << ",H:" << curPoint->H << endl;;
		openList.remove(curPoint); 
		closeList.push_back(curPoint); 
		auto surroundPoints = getSurroundPoints(curPoint, isIgnoreCorner, closeList);
		for (auto &target : surroundPoints)
		{
			
			if (!isInList(openList, target))
			{
				target->parent = curPoint;

				target->G = calcG(curPoint, target, maze);
				target->H = calcH(target, isIgnoreCorner, maze);
				target->F = calcF(target);
				
				openList.push_back(target);
			}
			
			else
			{
				//int tempG = calcG(curPoint, target, maze);
				float tempF = calcF(curPoint);
				if (tempF < target->F)
				{
					target->parent = curPoint;
					target->F = calcF(target);
				}

			}
			my_Point *resPoint = isInList(openList, &endPoint);
			if (resPoint)
				return resPoint; 		
		}
	}
	return NULL;
}

void Astar::findPath_bidirection(my_Point &startPoint, my_Point &endPoint, bool isIgnoreCorner, std::vector<std::vector<int>> maze, std::list<my_Point *> &path1, std::list<my_Point *> &path2)
{
	openList1.push_back(new my_Point(startPoint.x, startPoint.y));
	openList2.push_back(new my_Point(endPoint.x, endPoint.y)); 
	while ((!openList1.empty())&&(!openList2.empty()))
	{
		auto curPoint1 = getLeastFpoint(openList1); //找到F值最小的点
		auto curPoint2 = getLeastFpoint(openList2); //找到F值最小的点
		cout << "(" << curPoint1->x << "," << curPoint1->y << ") ";
		cout << "F:" << curPoint1->F << "," << "G:" << curPoint1->G << ",H:" << curPoint1->H << endl;
		cout << "2(" << curPoint2->x << "," << curPoint2->y << ") ";
		cout << "F:" << curPoint2->F << "," << "G:" << curPoint2->G << ",H:" << curPoint2->H << endl;
		openList1.remove(curPoint1);
		closeList1.push_back(curPoint1); 
		openList2.remove(curPoint2);
		closeList2.push_back(curPoint2); 
									  
		auto surroundPoints1 = getSurroundPoints(curPoint1, isIgnoreCorner, closeList1);
		auto surroundPoints2 = getSurroundPoints(curPoint2, isIgnoreCorner, closeList2);

		for (auto &target : surroundPoints1)
		{
			
			if (!isInList(openList1, target))
			{
				target->parent = curPoint1;
				target->G = calcG(curPoint1, target, maze);
				target->H = calcH(target, isIgnoreCorner, maze);
				target->F = calcF(target);
				openList1.push_back(target);
			}
			
			else
			{
				float tempF = calcF(curPoint1);
				if (tempF < target->F)
				{
					target->parent = curPoint1;
					target->F = calcF(target);
				}
			}		

			for (auto &target2 : surroundPoints2)
			{
				
				if (!isInList(openList2, target2))
				{
					target2->parent = curPoint2;
					target2->G = calcG(curPoint2, target2, maze);
					target2->H = calcH(target2, isIgnoreCorner, maze);
					target2->F = calcF(target2);
					openList2.push_back(target2);
				}
				
				else
				{
					float tempF = calcF(curPoint2);
					if (tempF < target2->F)
					{
						target2->parent = curPoint2;
						target2->F = calcF(target2);
					}
				}

				for (auto &temp1 : openList1) {
					for (auto &temp2 : openList2) {
						if (temp1->x == temp2->x&&temp1->y == temp2->y) {			
							my_Point *result1 = isInList_not_const(openList1, temp1);
							my_Point *result2 = isInList_not_const(openList2, temp1);
							while (result1)
							{
								path1.push_front(result1);
								result1 = result1->parent;
							}
							while (result2)
							{
								path2.push_front(result2);
								result2 = result2->parent;
							}
							return;
						}
					}
				}		
			}
		}
		
	}
	return ;
}

std::list<my_Point *> Astar::GetPath(my_Point &startPoint, my_Point &endPoint, bool isIgnoreCorner, vector<vector<int>> maze)
{
	my_Point *result = findPath(startPoint, endPoint, isIgnoreCorner, maze);
	std::list<my_Point *> path;	
	while (result)
	{
		path.push_front(result);
		result = result->parent;
	}	
	openList.clear();
	closeList.clear();

	return path;
}

void Astar::GetPath_bidirection(my_Point &startPoint, my_Point &endPoint, bool isIgnoreCorner, std::vector<std::vector<int>> maze, std::list<my_Point *> &path1, std::list<my_Point *> &path2)
{
	
	findPath_bidirection(startPoint, endPoint, isIgnoreCorner, maze, path1, path2);
	openList1.clear();
	closeList1.clear();
	openList2.clear();
	closeList2.clear();
	return ;
}

my_Point *Astar::isInList(const std::list<my_Point *> &list, const my_Point *point) const
{
	
	for (auto p : list)
		if (p->x == point->x&&p->y == point->y)
			return p;
	return NULL;
}

my_Point *Astar::isInList_not_const(std::list<my_Point *> &list, my_Point *point)
{
	
	
	for (auto p : list)
		if (p->x == point->x&&p->y == point->y)
			return p;
	return NULL;
}

bool Astar::isCanreach(const my_Point *point, const my_Point *target, bool isIgnoreCorner, std::list<my_Point *> closeList_temp) const
{
	if (target->x<0 || target->x>maze.size() - 1
		|| target->y<0 || target->y>maze[0].size() - 1
		|| maze[target->x][target->y] == 1
		|| target->x == point->x&&target->y == point->y
		|| isInList(closeList_temp, target)) //如果点与当前节点重合、超出地图、是障碍物、或者在关闭列表中，返回false
		return false;
	else
	{
		if (abs(point->x - target->x) + abs(point->y - target->y) == 1) 
			return true;
		else
		{
			
			if (maze[point->x][target->y] == 0 && maze[target->x][point->y] == 0)
				return true;
			else
				return isIgnoreCorner;
		}
	}
}

std::vector<my_Point *> Astar::getSurroundPoints(const my_Point *point, bool isIgnoreCorner, std::list<my_Point *> closeList_temp) const
{
	std::vector<my_Point *> surroundPoints;

	for (int x = point->x - 1; x <= point->x + 1; x++)
		for (int y = point->y - 1; y <= point->y + 1; y++)
			if (isCanreach(point, new my_Point(x, y), isIgnoreCorner, closeList_temp))
				surroundPoints.push_back(new my_Point(x, y));

	return surroundPoints;
}