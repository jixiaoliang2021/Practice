// MathClient.cpp : Client app for MathLibrary DLL.
// #include "pch.h" Uncomment for Visual Studio 2017 and earlier
#include <iostream>
#include "Graph.h"
#include <regex>
using namespace std;


void show_import_progress(int length) // 回调函数
{
	cout << "开始读取文件" << '\n';
	cout << "读取第" << length <<"行" << endl;
}

void show_export_progress(string type,int n) // 回调函数
{
	cout << "类型： " << type << " 总计" << n << "个" << endl;
}


int main()
{
	string file_path = "D:\\02_SRC\\WIN_Practice\\Test_ReadObj\\test.obj";
	Graph* graph_obj = new Graph();
	graph_obj->regesiter_import(show_import_progress);
	graph_obj->regesiter_export(show_export_progress);
	graph_obj->import_obj_ex(file_path);
	graph_obj->export_obj_ex();
	system("pause");
	return 0;
}
