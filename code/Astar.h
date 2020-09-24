#include "stdafx.h"
#include <vector>
#include <list>


const float kCost1 = 1; //ֱ��һ������
const float kCost2 = 1.414; //б��һ������

struct my_Point
{
	int x, y;
	float F, G, H; //F=G+H
	my_Point *parent; //parent����
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
	bool isCanreach(const my_Point *point, const my_Point *target, bool isIgnoreCorner, std::list<my_Point *> closeList_temp) const; //�ж�ĳ���Ƿ����������һ���ж�
	my_Point *isInList(const std::list<my_Point *> &list, const my_Point *point) const; //�жϿ���/�ر��б����Ƿ����ĳ��
	my_Point *Astar::isInList_not_const(std::list<my_Point *> &list, my_Point *point); //�жϿ���/�ر��б����Ƿ����ĳ��
	my_Point *getLeastFpoint(std::list<my_Point *> openList_temp); //�ӿ����б��з���Fֵ��С�Ľڵ�
							 //����FGHֵ
	float calcG(my_Point *temp_start, my_Point *point, std::vector<std::vector<int>> maze);
	float calcH(my_Point *point, bool isIgnoreCorner, std::vector<std::vector<int>> maze);
	float calcF(my_Point *point);
public:
	std::vector<std::vector<int>> maze;
	std::list<my_Point *> openList;  //�����б�
	std::list<my_Point *> closeList; //�ر��б�
	std::list<my_Point *> openList1;  //�����б�
	std::list<my_Point *> closeList1; //�ر��б�
	std::list<my_Point *> openList2;  //�����б�
	std::list<my_Point *> closeList2; //�ر��б�
};