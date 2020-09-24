#include <iostream>

using namespace std;

#pragma once
/*产生等概率随机数*/
bool happened(double probability);
long myrandom(long n);

/*产生n个二维随机点*/
void generate_dot_set(int *dot, int n);

//计算m在xy两点所确定直线哪一边
int f_value(int *x, int *y, int *m);

//bool cmp(int x, int y);

void Print_process(int total_num, int cur_num, int process);

template <typename T>
void Load_file(const char* file_path, T *temp) {
	fstream file;
	file.open(file_path, ios::in);
	if (!file)
	{
		cout << "Loading error！" << endl;
		exit(1);
	}
	int num = 0;
	while (!file.eof()) {
		file >> temp[num];
		num++;
	}
	file.close();
}

void Load_tf(const char* file_path, vector<int> &S, vector<int> &S_num, int num, vector<int> &X);