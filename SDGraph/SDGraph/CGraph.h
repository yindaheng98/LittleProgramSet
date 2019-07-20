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

#define SPACE_X 80//�м��
#define SPACE_Y 80//�м��
#define START_Y 50//�Ӵ˴���ʼ��

class Graph
{
public:
	void AddEdge(wchar_t start, wchar_t end, int weight);//�����
	void AddVex(wchar_t name);//�����
	void print(CDC * pDC);//�������
	void print(void(*print_vex)(wchar_t vexs, int code), void(*print_edge)(int start, int end, int weight));//���
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
	int vexnum, edgenum;//�����ͱ���
	vector<vector<int>>edge;//�ڽӾ���
	vector<wchar_t>vexs;//�洢����
};

inline void Graph::AddEdge(wchar_t name_start, wchar_t name_end, int weight)//��ӱ�
{
	int start = translate(name_start);//�ҵ����
	int end = translate(name_end);//�ҵ��յ�
	edge[start][end] = edge[end][start] = weight;//��Ӧ����λ�ø�Ȩֵ
	edgenum++;//������һ
}

inline void Graph::AddVex(wchar_t name)//��ӵ�
{
	for (wchar_t v : vexs)//�������
		if (name == v)throw"����";
	vexs.push_back(name);//��ӽڵ�
	vexnum++;//�ڵ�����һ
	edge.resize(vexnum, vector<int>(vexnum, IFINITY));//�ڽӾ����һ��
	for (int i = 0; i<vexnum; i++)
		edge[i].resize(vexnum, IFINITY);//�ڽӾ����һ��
	edge[vexnum - 1][vexnum - 1] = 0;//��������·������Ϊ0
}

inline void Graph::print(CDC*pDC)
{
	CString temp;
	CString str=L"����";
	temp.Format(_T("%d"),vexnum);
	str += temp + L"�����";
	temp.Format(_T("%d"), edgenum);
	str += temp + L"����";
	pDC->TextOutW(0, 0, str);//ͳ�Ƶ����ͱ��������
	for (int i = 0; i < vexnum; i++)
	{
		CString name(vexs[i]);
		int xi, yi;
		trans(i, xi, yi);//ָ����λ��
		pDC->SetBkMode(NULL);
		pDC->SelectStockObject(NULL_BRUSH);//����͸��
		pDC->Ellipse(xi, yi, xi + RANGE, yi + RANGE);//���Ƶ�
		pDC->TextOutW(xi, yi, name);//���Ƶ���
		for (int j = 0; j < vexnum; j++)
		{
			if (edge[i][j] < IFINITY&&i != j)
			{
				int xj, yj;
				CString weight;
				weight.Format(_T("%d"), edge[i][j]);
				pDC->MoveTo(xi + RANGE / 2, yi + RANGE / 2);//���ƴӴ˽ڵ�����ĸ��ڵ�
				trans(j, xj, yj);//ָ����λ��
				pDC->LineTo(xj + RANGE / 2, yj + RANGE / 2);
				pDC->TextOutW((xi + xj + RANGE) / 2, (yi + yj + RANGE) / 2, weight);//���Ʊ�Ȩֵ
			}
		}
	}
}

inline void Graph::print(
	void(*print_vex)(wchar_t vexs, int code),
	void(*print_edge)(int start, int end, int weight))//���
{
	for (int i = 0; i < vexnum; i++)
		print_vex(vexs[i], i);//�����
	for (int i = 0; i < vexnum; i++)
		for (int j = 0; j < vexnum; j++)
			if (edge[i][j] < IFINITY)
				print_edge(i, j, edge[i][j]);//�����
}

inline void Graph::Dijkstra(int vex_start, vector<int>& path, vector<int>& length)
{
	if (vexnum > 0)//ͼ��������һ�������Ҫ��ʼ��
	{
		vector<bool>visit(vexnum,false);//���Ҽ�¼
		length = edge[vex_start];//���·�����ȼ�¼
		path.resize(vexnum);//���·��ָ���¼
		for (int i = 0; i < vexnum; i++)
			path[i] = (edge[vex_start][i] < IFINITY) ? vex_start : -1;//��ʼ��·��ָ���¼
		length[vex_start] = 0;//��������
		visit[vex_start] = true;//������Ҫ����
		path[vex_start] = vex_start;//������������·������һ���ڵ��������
		if (vexnum >= 2)//ͼ��������������ſ����б�
		{
			for (int i = 1; i < vexnum; i++)//ѡ��������
			{
				int k = vex_start;//��ʼ��������¼
				int min = IFINITY;//��ʼ��minΪ����
				for (int w = 0; w < vexnum; w++)
					if ((!visit[w]) && (length[w] <= min))//�����㵽δ�ҹ����·����w��·��С����Сֵ
						min = length[k = w];//�ҵ�����¼�����
				visit[k] = true;//����k���ҹ���Сֵ
				for (int w = 0; w < vexnum; w++)
					if ((min + edge[k][w]) < length[w])//�����k��w��·��С��֮ǰ��¼�ĵ�w��·��
					{
						length[w] = min + edge[k][w];//�޸ĵ�ǰ���·��
						path[w] = k;//����ָ��w����һ����·��Ϊk
					}
			}			
		}
	}
}

inline void Graph::DFSPrint(int vex_start, vector<bool>& visited,CString&str)
{
	str += vexs[vex_start];//�������
	str += "->";
	visited[vex_start] = true;
	for (int w = 0; w < vexnum; w++)//�������������������ͼ
		if (edge[vex_start][w] < IFINITY)
			if (!visited[w])
				DFSPrint(w, visited, str);
}

inline void Graph::BFSPrint(int vex_start, vector<bool>&visited, CString&str)
{
	deque<int>queue;//��������
	int start = vex_start;//��������ʼ��
	bool finish = false;//������ɱ�ʶ��ʼ��
	do
	{
		queue.push_back(start);//�洢�������
		visited[start] = true;//��ͷ�����
		while (!queue.empty())//�����в�Ϊ��
		{
			int this_vex = queue.front();
			queue.pop_front();//ȡ����ͷ
			str += vexs[this_vex];
			str += "->";//�洢������ַ�����
			for (int w = 0; w < vexnum; w++)
				if (edge[this_vex][w] < IFINITY && !visited[w])//��·����δ���
				{
					visited[w] = true;//�����
					queue.push_back(w);//��˽ڵ������Ľڵ����
				}
		}
		for (int w = 0; w < vexnum; w++)//����δ�����Ľڵ�
		{
			if (!visited[w])//����ҵ����ٴν����α���
			{
				finish = false;//����δ���
				start = w;//�޸ı������
				break;
			}
			else finish = true;
		}
	} while (!finish);//ֱ��ȫ���������
}

inline void Graph::Dijkstraprint(CDC*pDC, wchar_t start_name)
{
	int vex_start = translate(start_name);//������ĵ������ҵ����
	vector<int>path, length;//·���볤��
	Dijkstra(vex_start, path, length);//ִ��Dijkstra�㷨
	for (int i = 0; i < vexnum; i++)//��ʾ·���ĳ���
	{
		CString str;
		if(length[i]<IFINITY)str.Format(_T("%c->%c=%d"), vexs[vex_start], vexs[i], length[i]);//�����·�������·��
		else str.Format(_T("%c->%c=Inf"), vexs[vex_start], vexs[i]);//���û��·����������
		pDC->TextOutW(0, 60 + 20 * i, str);//ÿ���������ǰһ������һ��
	}
	printpath(pDC, vex_start, path);
}

inline void Graph::printpath(CDC * pDC, int vex_start, vector<int>&path)
{
	int x, y;
	CPen pen(PS_SOLID, 3, PATH_COLOR);//���ñ��·������ɫ
	CPen*oldpen = pDC->SelectObject(&pen);
	trans(vex_start, x, y);//�����
	pDC->Ellipse(x + RANGE / 2 - POINT_WAGE, y + RANGE / 2 - POINT_WAGE, x + RANGE / 2 + POINT_WAGE, y + RANGE / 2 + POINT_WAGE);
	for (int i = 0; i < vexnum; i++)//��·��
	{

		if (path[i] != -1)//��·���ͻ�����
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
	vector<Edge>all_edge;//������
	vector<Edge>tree;//������
	vector<int>components;
	for (int i = 0; i < vexnum; i++)
	{
		for (int j = 0; j < i; j++)
			if (edge[i][j] < IFINITY)
				all_edge.push_back({ i,j,edge[i][j] });//д�������
		components.push_back(i);//д�������
	}
	std::sort(all_edge.begin(), all_edge.end());//��������
	for (unsigned i = 0; i < all_edge.size() - 1; i++)
	{
		int cs = components[all_edge[i].s], ce = components[all_edge[i].e];
		if (cs != ce)//�������յ㲻��ͬһ������
		{
			tree.push_back(all_edge[i]);//������
			for (int j = 0; j < vexnum; j++)
				if (components[j] == ce)components[j] = cs;//����components����,�ϲ�������
		}
	}
	//д��·������
	vector<bool>find(vexnum, false);//��¼�Ƿ����ҵ�
	for (Edge e : tree)
	{
		if (!find[e.s])//�����Ӧ���δ�ҵ�
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
		for (i = 0; (i + 1)*i / 2 <= n; i++);//�ж�nӦ�ڵ�i�����
		int j = n - i*(i - 1) / 2;//�ж�nӦ�ڵ�i�еĵ�i�����
		x = i * SPACE_X + sin(j)*SPACE_X / 2;//n�����x��
		y = (j + 1) * SPACE_Y + sin(i) * SPACE_Y + START_Y;//n�������y��
	}
}


inline void Graph::Prim(int vex_start, vector<int>& path)
{
	vector<bool>find(vexnum, false);//��ʼ�����ּ�¼
	vector<int>length(edge[vex_start]);//��ʼ����������
	path.resize(vexnum, -1);
	path[vex_start] = vex_start;
	for (int i = 0; i < vexnum; i++)
		path[i] = length[i] == IFINITY ? -1 : vex_start;//��ʼ��·����¼
	find[vex_start] = true;//������
	for (int i = 1; i < vexnum; i++)//ȡ������
	{
		int now = 0;//���ڼ�¼��Сֵ��
		for (int j = 0, min = length[j]; j < vexnum; j++)
			if ((!find[j]) && length[j] < min)//�ҳ���Сֵ
				min = length[now = j];//��¼��Сֵ
		find[now] = true;//����Сֵ��������
		for (int j = 0; j < vexnum; j++)//���¾���
			if ((!find[j])&&edge[now][j]<length[j])//���δ�����ұȽ϶�
			{
				length[j] = edge[now][j];//����������ϵ��j�ľ���
				path[j] = now;//����
			}
	}
}

inline int Graph::translate(wchar_t name)//�����Ʋ��ҵ�
{
	if (vexnum)
	{
		for (int i = 0; i < vexnum; i++)
			if (vexs[i] == name)return i;
		throw L"���޴˵�";
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
	int vex_end = translate(end_name);//������ĵ������ҵ�����յ�
	vector<vector<int>>path_whole;//·��
	vector<vector<int>>length;
	Floyd(length,path_whole);//ִ��Floyd�㷨,�ó����·������
	CString str;
	if (length[vex_start][vex_end] < IFINITY)
	{
		str.Format(_T("%c->%c=%d"), start_name, end_name, length[vex_start][vex_end]);//�����·�������
		pDC->TextOutW(0, 60, str);//���·����
		vector<int>path(vexnum, -1);//��ʼ��·������
		path[vex_start] = vex_start;//����·��ָ������
		for (int i = vex_start; i != vex_end; i = path_whole[i][vex_end])
			path[path_whole[i][vex_end]] = i;//ѭ���洢ָ��·��
		printpath(pDC, start_name, path);//���
	}
	else str.Format(_T("%c->%c=Inf"), start_name, end_name);//���û��·����������
}

inline void Graph::DFS(CDC * pDC)//������ȱ����������������
{
	vector<bool>visited(vexnum, false);//��¼�ѱ�������
	CString str;
	str = L"������ȱ�������Ϊ:";
	for (int i = 0; i < vexnum; i++)
		if (!visited[i])
			DFSPrint(i, visited,str);//�������
	pDC->TextOutW(DFSPRINT_PLACE_X, DFSPRINT_PLACE_Y, str);
}

inline void Graph::BFS(CDC * pDC)
{
	vector<bool>visited(vexnum, false);//��¼�ѱ�������
	CString str;
	str += L"������ȱ�������Ϊ:";
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
