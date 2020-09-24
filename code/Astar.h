#include "stdafx.h"
#include <vector>
#include <list>


const float kCost1 = 1; //直移一格消耗
const float kCost2 = 1.414; //斜移一格消耗

struct my_Point
{
	int x, y;
	float F, G, H; //F=G+H
	my_Point *parent; //parent坐标
	my_Point(int _x, int _y) :x(_x), y(_y), F(0), G(0), H(0), parent(NULL) 
	{
	}
};

class Astar
{
public:
	void InitAstar(std::vector<std::vector<int>> &_maze);
	std::list<my_Point *> GetPath(my_Point &startPoint, my_Point &endPoint, bool isIgnoreCorner, std::vector<std::vector<int>> maze);
	void GetPath_bidirection(my_Point &startPoint, my_Point &endPoint, bool isIgnoreCorner, std::vector<std::vector<int>> maze, std::list<my_Point *> &path1, std::list<my_Point *> &path2);
	//std::list<my_Point *> GetPath_bidirection(my_Point &startPoint, my_Point &endPoint, bool isIgnoreCorner, vector<vector<int>> maze, list<my_Point *> path1, list<my_Point *> path2);
	void findPath_bidirection(my_Point &startPoint, my_Point &endPoint, bool isIgnoreCorner, std::vector<std::vector<int>> maze, std::list<my_Point *> &path1, std::list<my_Point *> &path2);
private:
	my_Point *findPath(my_Point &startPoint, my_Point &endPoint, bool isIgnoreCorner, std::vector<std::vector<int>> maze);
	
	std::vector<my_Point *> getSurroundPoints(const my_Point *point, bool isIgnoreCorner, std::list<my_Point *> closeList_temp) const;
	bool isCanreach(const my_Point *point, const my_Point *target, bool isIgnoreCorner, std::list<my_Point *> closeList_temp) const; //判断某点是否可以用于下一步判断
	my_Point *isInList(const std::list<my_Point *> &list, const my_Point *point) const; //判断开启/关闭列表中是否包含某点
	my_Point *Astar::isInList_not_const(std::list<my_Point *> &list, my_Point *point); //判断开启/关闭列表中是否包含某点
	my_Point *getLeastFpoint(std::list<my_Point *> openList_temp); //从开启列表中返回F值最小的节点
							 //计算FGH值
	float calcG(my_Point *temp_start, my_Point *point, std::vector<std::vector<int>> maze);
	float calcH(my_Point *point, bool isIgnoreCorner, std::vector<std::vector<int>> maze);
	float calcF(my_Point *point);
public:
	std::vector<std::vector<int>> maze;
	std::list<my_Point *> openList;  //开启列表
	std::list<my_Point *> closeList; //关闭列表
	std::list<my_Point *> openList1;  //开启列表
	std::list<my_Point *> closeList1; //关闭列表
	std::list<my_Point *> openList2;  //开启列表
	std::list<my_Point *> closeList2; //关闭列表
};