# 求解迷宫路径
	寻路问题，输入一个方格表示的地图，要求用A*算法找到并输出从起点(再放各种标示字母S)到终点(在方格中标示字母T)的代价最小的路径，有如下条件及要求:
	1.每一步都落在方格中,而不是横竖线的交叉点
	2.灰色格子表示障碍,无法通行
	3.在每个格子处,若无障碍,下一步可以达到八个相邻的格子,并且可以到达无障碍的相邻格子。其中，向上、下、左、右四个方向移动的代价为1，向四个斜角方向移动的代价为√2
	4.在一些特殊格子上行走要花费额外的地形代价，比如黄色格子代表沙漠，经过它的代价为4；蓝色格子代表溪流，经过它的代价为2；白色格子为普通地形，经过它的代价为0
	5.经过一条路径的总代价为移动代价+地形代价。其中移动代价是路径上所做的所有移动的代价的总和；地形代价为路径上除起点外所有格子的地形代价的总和。
##### 详细过程可参考pdf文档或代码。
## 单向A*算法
算法A* single(D, S, T)
<br>输入 :平面上n个点的二维数组D，起始点S，终点T
<br>输出 :从S到T的路径
<br>1:  openlist.push(S)
<br>2:  While(true)
<br>3:     寻找openlist中F值最低的格，称为当前格P
<br>4:      closelist.push(P)
<br>5:      If   它不可通过||已经在closelist中   Then ;
<br>6:      If   它不在openlsit中 
<br>7:         Then   openlist.push(P)，把P作为该格的父节点，计算FGH值
<br>8:      If   它已在openlist中
<br>9:         Then   If   它的F值更低
<br>10:          Then   把P作为该格的父节点，重新计算FGH值
<br>11:    If   目标格已经在openlist中
<br>12:       Then break
<br>13:  从T开始，沿着每一格的父节点回溯，直到回到S，输出路径
## 双向A*算法
### 双向A*算法无法保证最优解
算法A* bidirection(D, S, T)
<br>输入 :平面上n个点的二维数组D，起始点S，终点T
<br>输出 :从S到T的路径
<br>1:  openlist1.push(S)
<br>2:  openlist2.push(T)
<br>3:  While(true)
<br>4:     寻找openlist1中F值最低的格，称为当前格P1
<br>5:        寻找openlist2中F值最低的格，称为当前格P2
<br>6:           If   P1不可通过||已经在closelist1中   Then ;
<br>7:           If   它已在openlist1中
<br>8:              Then   If   它的F值更低
<br>9:                 Then   把P1作为该格的父节点，重新计算FGH值
<br>10:         If   P2不可通过||已经在closelist2中   Then ;
<br>11:         If   它已在openlist2中
<br>12:            Then   If   它的F值更低
<br>13:               Then   把P2作为该格的父节点，重新计算FGH值
<br>14:     If openlist1和openlist2中存在相同点
<br>15:        Then   break
<br>16:  从S和T分别开始，沿着每一格的父节点回溯，直到回到相遇点，输出路径

## 结果展示
### 初始地图
![](https://github.com/HuiyanWen/Maze_Astar/blob/master/pic/%E5%8D%95%E5%90%91A*%E5%88%9D%E5%A7%8B.png)

### 单向A*结果
![](https://github.com/HuiyanWen/Maze_Astar/blob/master/pic/%E5%8D%95%E5%90%91A*.png)

### 双向A*结果
![](https://github.com/HuiyanWen/Maze_Astar/blob/master/pic/%E5%8F%8C%E5%90%91A*.png)

### 初始地图2
![](https://github.com/HuiyanWen/Maze_Astar/blob/master/pic/%E5%88%9D%E5%A7%8B.png)

### 单向A*结果
![](https://github.com/HuiyanWen/Maze_Astar/blob/master/pic/%E5%88%9D%E5%A7%8B1.png)

### 双向A*结果
![](https://github.com/HuiyanWen/Maze_Astar/blob/master/pic/%E5%88%9D%E5%A7%8B2.png)
