#pragma once
#define IFINITY 100000
#include<math.h>
#include<vector>
#include<deque>
#include<algorithm>
using std::vector;
using std::deque;
#define RANGE 30
#define POINT_WAGE 5
#define POINT_COLOR RGB(255,0,0)
#define EDGE_COLOR RGB(0,255,0)
#define PATH_COLOR RGB(255,0,0)
#define DFSPRINT_PLACE_X 0
#define DFSPRINT_PLACE_Y 20
#define BFSPRINT_PLACE_X 0
#define BFSPRINT_PLACE_Y 40
#define PRINT_RANGE 22

#define SPACE_X 80//列间距
#define SPACE_Y 80//行间距
#define START_Y 50//从此处开始画

class Graph
{
public:
	void AddEdge(wchar_t start, wchar_t end, int weight);//加入边
	void AddVex(wchar_t name);//加入点
	void print(CDC * pDC);//输出函数
	void print(void(*print_vex)(wchar_t vexs, int code), void(*print_edge)(int start, int end, int weight));//输出
	void Dijkstraprint(CDC * pDC, wchar_t start_name);
	void Floyedprint(CDC * pDC, wchar_t start_name, wchar_t end_name);
	void DFS(CDC*pDC);
	void BFS(CDC*pDC);
	void Primprint(CDC*pDC, wchar_t start_name);
	void Kruskalprint(CDC*pDC, wchar_t start_name);

private:
	void trans(int n, int&x, int &y);
	void Kruskal(int vex_start, vector<int>& path);
	void Prim(int vex_start, vector<int>& path);
	int translate(wchar_t name);
	void Dijkstra(int vex_start, vector<int>& path, vector<int>& length);
	void DFSPrint(int vex_start, vector<bool>& visited, CString & str);
	void Floyd(vector<vector<int>>& length, vector<vector<int>>& path);
	void BFSPrint(int vex_start, vector<bool>& visited, CString&str);
	void printpath(CDC * pDC, int vex_start, vector<int>&path);
	int vexnum, edgenum;//点数和边数
	vector<vector<int>>edge;//邻接矩阵
	vector<wchar_t>vexs;//存储点名
};

inline void Graph::AddEdge(wchar_t name_start, wchar_t name_end, int weight)//添加边
{
	int start = translate(name_start);//找到起点
	int end = translate(name_end);//找到终点
	edge[start][end] = edge[end][start] = weight;//对应矩阵位置赋权值
	edgenum++;//边数加一
}

inline void Graph::AddVex(wchar_t name)//添加点
{
	for (wchar_t v : vexs)//检查重名
		if (name == v)throw"重名";
	vexs.push_back(name);//添加节点
	vexnum++;//节点数加一
	edge.resize(vexnum, vector<int>(vexnum, IFINITY));//邻接矩阵加一行
	for (int i = 0; i<vexnum; i++)
		edge[i].resize(vexnum, IFINITY);//邻接矩阵加一列
	edge[vexnum - 1][vexnum - 1] = 0;//自身到自身路径长度为0
}

inline void Graph::print(CDC*pDC)
{
	CString temp;
	CString str=L"共有";
	temp.Format(_T("%d"),vexnum);
	str += temp + L"个点和";
	temp.Format(_T("%d"), edgenum);
	str += temp + L"条边";
	pDC->TextOutW(0, 0, str);//统计点数和边数并输出
	for (int i = 0; i < vexnum; i++)
	{
		CString name(vexs[i]);
		int xi, yi;
		trans(i, xi, yi);//指定点位置
		pDC->SetBkMode(NULL);
		pDC->SelectStockObject(NULL_BRUSH);//设置透明
		pDC->Ellipse(xi, yi, xi + RANGE, yi + RANGE);//绘制点
		pDC->TextOutW(xi, yi, name);//绘制点名
		for (int j = 0; j < vexnum; j++)
		{
			if (edge[i][j] < IFINITY&&i != j)
			{
				int xj, yj;
				CString weight;
				weight.Format(_T("%d"), edge[i][j]);
				pDC->MoveTo(xi + RANGE / 2, yi + RANGE / 2);//绘制从此节点出发的各节点
				trans(j, xj, yj);//指定点位置
				pDC->LineTo(xj + RANGE / 2, yj + RANGE / 2);
				pDC->TextOutW((xi + xj + RANGE) / 2, (yi + yj + RANGE) / 2, weight);//绘制边权值
			}
		}
	}
}

inline void Graph::print(
	void(*print_vex)(wchar_t vexs, int code),
	void(*print_edge)(int start, int end, int weight))//输出
{
	for (int i = 0; i < vexnum; i++)
		print_vex(vexs[i], i);//输出点
	for (int i = 0; i < vexnum; i++)
		for (int j = 0; j < vexnum; j++)
			if (edge[i][j] < IFINITY)
				print_edge(i, j, edge[i][j]);//输出边
}

inline void Graph::Dijkstra(int vex_start, vector<int>& path, vector<int>& length)
{
	if (vexnum > 0)//图中至少有一个点才需要初始化
	{
		vector<bool>visit(vexnum,false);//查找记录
		length = edge[vex_start];//最短路径长度记录
		path.resize(vexnum);//最短路径指向记录
		for (int i = 0; i < vexnum; i++)
			path[i] = (edge[vex_start][i] < IFINITY) ? vex_start : -1;//初始化路径指向记录
		length[vex_start] = 0;//自身到自身
		visit[vex_start] = true;//自身不需要查找
		path[vex_start] = vex_start;//连接自身的最短路径的上一个节点就是自身
		if (vexnum >= 2)//图中至少有两个点才可能有边
		{
			for (int i = 1; i < vexnum; i++)//选择其他点
			{
				int k = vex_start;//初始化最近点记录
				int min = IFINITY;//初始化min为无穷
				for (int w = 0; w < vexnum; w++)
					if ((!visit[w]) && (length[w] <= min))//如果起点到未找过最短路径的w的路径小于最小值
						min = length[k = w];//找到并记录最近点
				visit[k] = true;//设置k已找过最小值
				for (int w = 0; w < vexnum; w++)
					if ((min + edge[k][w]) < length[w])//如果从k到w的路径小于之前记录的到w的路径
					{
						length[w] = min + edge[k][w];//修改当前最短路径
						path[w] = k;//设置指向w的上一个的路径为k
					}
			}			
		}
	}
}

inline void Graph::DFSPrint(int vex_start, vector<bool>& visited,CString&str)
{
	str += vexs[vex_start];//自身输出
	str += "->";
	visited[vex_start] = true;
	for (int w = 0; w < vexnum; w++)//输出与其相连的所有子图
		if (edge[vex_start][w] < IFINITY)
			if (!visited[w])
				DFSPrint(w, visited, str);
}

inline void Graph::BFSPrint(int vex_start, vector<bool>&visited, CString&str)
{
	deque<int>queue;//辅助队列
	int start = vex_start;//遍历起点初始化
	bool finish = false;//遍历完成标识初始化
	do
	{
		queue.push_back(start);//存储遍历起点
		visited[start] = true;//队头已入队
		while (!queue.empty())//当队列不为空
		{
			int this_vex = queue.front();
			queue.pop_front();//取出队头
			str += vexs[this_vex];
			str += "->";//存储在输出字符串中
			for (int w = 0; w < vexnum; w++)
				if (edge[this_vex][w] < IFINITY && !visited[w])//有路径且未入队
				{
					visited[w] = true;//已入队
					queue.push_back(w);//与此节点相连的节点入队
				}
		}
		for (int w = 0; w < vexnum; w++)//搜索未遍历的节点
		{
			if (!visited[w])//如果找到则再次进入层次遍历
			{
				finish = false;//遍历未完成
				start = w;//修改遍历起点
				break;
			}
			else finish = true;
		}
	} while (!finish);//直到全部遍历完成
}

inline void Graph::Dijkstraprint(CDC*pDC, wchar_t start_name)
{
	int vex_start = translate(start_name);//按输入的点名字找到起点
	vector<int>path, length;//路径与长度
	Dijkstra(vex_start, path, length);//执行Dijkstra算法
	for (int i = 0; i < vexnum; i++)//显示路径的长度
	{
		CString str;
		if(length[i]<IFINITY)str.Format(_T("%c->%c=%d"), vexs[vex_start], vexs[i], length[i]);//如果有路径则输出路径
		else str.Format(_T("%c->%c=Inf"), vexs[vex_start], vexs[i]);//如果没有路径输出无穷大
		pDC->TextOutW(0, 60 + 20 * i, str);//每次输出都在前一个下面一行
	}
	printpath(pDC, vex_start, path);
}

inline void Graph::printpath(CDC * pDC, int vex_start, vector<int>&path)
{
	int x, y;
	CPen pen(PS_SOLID, 3, PATH_COLOR);//设置标记路径的颜色
	CPen*oldpen = pDC->SelectObject(&pen);
	trans(vex_start, x, y);//画起点
	pDC->Ellipse(x + RANGE / 2 - POINT_WAGE, y + RANGE / 2 - POINT_WAGE, x + RANGE / 2 + POINT_WAGE, y + RANGE / 2 + POINT_WAGE);
	for (int i = 0; i < vexnum; i++)//画路径
	{

		if (path[i] != -1)//有路径就画出来
		{
			trans(i, x, y);
			pDC->MoveTo(x + RANGE / 2, y + RANGE / 2);
			trans(path[i], x, y);
			pDC->LineTo(x + RANGE / 2, y + RANGE / 2);
		}
	}
	pDC->SelectObject(oldpen);
}

struct Edge
{
	int s, e;
	int weight;
	bool operator<(Edge r)
	{
		return weight < r.weight;
	}
};

inline void Graph::Kruskal(int vex_start, vector<int>& path)
{
	vector<Edge>all_edge;//边数据
	vector<Edge>tree;//树数据
	vector<int>components;
	for (int i = 0; i < vexnum; i++)
	{
		for (int j = 0; j < i; j++)
			if (edge[i][j] < IFINITY)
				all_edge.push_back({ i,j,edge[i][j] });//写入边数据
		components.push_back(i);//写入点数据
	}
	std::sort(all_edge.begin(), all_edge.end());//升序排列
	for (unsigned i = 0; i < all_edge.size() - 1; i++)
	{
		int cs = components[all_edge[i].s], ce = components[all_edge[i].e];
		if (cs != ce)//如果起点终点不在同一集合中
		{
			tree.push_back(all_edge[i]);//则加入边
			for (int j = 0; j < vexnum; j++)
				if (components[j] == ce)components[j] = cs;//更新components数组,合并两集合
		}
	}
	//写入路径数据
	vector<bool>find(vexnum, false);//记录是否已找到
	for (Edge e : tree)
	{
		if (!find[e.s])//如果对应起点未找到
		{
			path[e.s] = e.e;
			find[e.s] = true;
		}
		else if(!find[e.e])
		{
			path[e.e] = e.s;
			find[e.e] = true;
		}
	}
}


inline void Graph::trans(int n, int & x, int & y)
{
	{
		int i;
		for (i = 0; (i + 1)*i / 2 <= n; i++);//判断n应在第i列输出
		int j = n - i*(i - 1) / 2;//判断n应在第i列的第i项输出
		x = i * SPACE_X + sin(j)*SPACE_X / 2;//n输出到x列
		y = (j + 1) * SPACE_Y + sin(i) * SPACE_Y + START_Y;//n输出到第y行
	}
}


inline void Graph::Prim(int vex_start, vector<int>& path)
{
	vector<bool>find(vexnum, false);//初始化发现记录
	vector<int>length(edge[vex_start]);//初始化辅助数组
	path.resize(vexnum, -1);
	path[vex_start] = vex_start;
	for (int i = 0; i < vexnum; i++)
		path[i] = length[i] == IFINITY ? -1 : vex_start;//初始化路径记录
	find[vex_start] = true;//起点加入
	for (int i = 1; i < vexnum; i++)//取其他点
	{
		int now = 0;//用于记录最小值点
		for (int j = 0, min = length[j]; j < vexnum; j++)
			if ((!find[j]) && length[j] < min)//找出最小值
				min = length[now = j];//记录最小值
		find[now] = true;//把最小值点加入进来
		for (int j = 0; j < vexnum; j++)//更新距离
			if ((!find[j])&&edge[now][j]<length[j])//如果未发现且比较短
			{
				length[j] = edge[now][j];//更新已有体系到j的距离
				path[j] = now;//连接
			}
	}
}

inline int Graph::translate(wchar_t name)//按名称查找点
{
	if (vexnum)
	{
		for (int i = 0; i < vexnum; i++)
			if (vexs[i] == name)return i;
		throw L"查无此点";
	}
	return -1;
}

inline void Graph::Floyd(vector<vector<int>>& length, vector<vector<int>>& path)
{
	length.resize(vexnum, vector<int>(vexnum, IFINITY));
	path.resize(vexnum, vector<int>(vexnum, -1));
	for (int i = 0; i < vexnum; i++)
		for (int j = 0; j < vexnum; j++)
			path[i][j] = (length[i][j] = edge[i][j]) < IFINITY ? j : -1;
	for (int k = 0; k < vexnum; k++)
	{
		for (int i = 0; i < vexnum; i++)
			for (int j = 0; j < vexnum; j++)
				if (length[i][k] + length[k][j] < length[i][j])
				{
					length[i][j] = length[i][k] + length[k][j];
					path[i][j] = path[i][k];
				}
	}
}

inline void Graph::Floyedprint(CDC * pDC, wchar_t start_name, wchar_t end_name)
{
	int vex_start = translate(start_name);
	int vex_end = translate(end_name);//按输入的点名字找到起点终点
	vector<vector<int>>path_whole;//路径
	vector<vector<int>>length;
	Floyd(length,path_whole);//执行Floyd算法,得出最短路径长度
	CString str;
	if (length[vex_start][vex_end] < IFINITY)
	{
		str.Format(_T("%c->%c=%d"), start_name, end_name, length[vex_start][vex_end]);//如果有路径则输出
		pDC->TextOutW(0, 60, str);//输出路径长
		vector<int>path(vexnum, -1);//初始化路径向量
		path[vex_start] = vex_start;//自身路径指向自身
		for (int i = vex_start; i != vex_end; i = path_whole[i][vex_end])
			path[path_whole[i][vex_end]] = i;//循环存储指定路径
		printpath(pDC, start_name, path);//输出
	}
	else str.Format(_T("%c->%c=Inf"), start_name, end_name);//如果没有路径输出无穷大
}

inline void Graph::DFS(CDC * pDC)//深度优先遍历并输出遍历序列
{
	vector<bool>visited(vexnum, false);//记录已遍历序列
	CString str;
	str = L"深度优先遍历序列为:";
	for (int i = 0; i < vexnum; i++)
		if (!visited[i])
			DFSPrint(i, visited,str);//输出函数
	pDC->TextOutW(DFSPRINT_PLACE_X, DFSPRINT_PLACE_Y, str);
}

inline void Graph::BFS(CDC * pDC)
{
	vector<bool>visited(vexnum, false);//记录已遍历序列
	CString str;
	str += L"广度优先遍历序列为:";
	for (int i = 0; i < vexnum; i++)
		if (!visited[i])
			BFSPrint(i, visited, str);
	pDC->TextOutW(BFSPRINT_PLACE_X, BFSPRINT_PLACE_Y, str);
}

inline void Graph::Primprint(CDC * pDC, wchar_t start_name)
{
	vector<int>path;
	Prim(translate(start_name), path);
	printpath(pDC, translate(start_name), path);
}

inline void Graph::Kruskalprint(CDC * pDC, wchar_t start_name)
{
	vector<int>path;
	Prim(translate(start_name), path);
	printpath(pDC, translate(start_name), path);
}
