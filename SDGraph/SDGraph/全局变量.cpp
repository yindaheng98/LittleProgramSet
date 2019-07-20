#pragma once
#include"stdafx.h"
#include"CGraph.h"
Graph graph;
enum condition
{
	none, mini_tree_prim, mini_tree_kruskal, dijkstra, floyed
}cdt;
wchar_t find_path_start = L'\0';
wchar_t point_start = L'\0';
wchar_t point_end = L'\0';


void test()
{
	extern wchar_t find_path_start;
	for (wchar_t c = L'A'; c<L'Z'; c+=1)
		graph.AddVex(c);
	for (wchar_t c1 = L'A'; c1 < L'Z'; c1+=2)
		for (wchar_t c2 = L'A'; c2 < L'Z'; c2+=3)
		if(rand()%13>9)graph.AddEdge(c1, c2, rand() % 13);
}

/**/

/*
void test()
{
	extern wchar_t find_path_start;
	for (wchar_t c = L'A'; c<L'Z'; c += 2)
		graph.AddVex(c);
	for (wchar_t c1 = L'A'; c1 < L'Z'; c1 += 4)
		for (wchar_t c2 = L'A'; c2 < L'Z'; c2 += 6)
			graph.AddEdge(c1, c2, c2 % 13);
}*/