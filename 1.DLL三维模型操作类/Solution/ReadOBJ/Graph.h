// MathLibrary.h - Contains declarations of math functions
#pragma once
#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
using namespace std;

#ifdef READOBJ_EXPORTS
#define READOBJ_API __declspec(dllexport)
#else
#define READOBJ_API __declspec(dllimport)
#endif

extern "C" READOBJ_API unsigned read_obj(std::string);

typedef void (*CallBackImport)(int length); // 回调函数指针
typedef void (*CallBackExport)(string type, int length); // 回调函数指针


class READOBJ_API Vertex
{
public:
	Vertex(double x, double y, double z)
    {
        m_x = x;
        m_y = y;
        m_z = z;
    };
    void print_member() {
        cout << m_x << " ";
        cout << m_x << " ";
        cout << m_x << " ";
        cout << endl;
    }
private:
    double m_x, m_y, m_z;
};

class READOBJ_API Vnormal
{
public:
    Vnormal(double nx, double ny, double nz)
    {
        m_nx = nx;
        m_ny = ny;
        m_nz = nz;
    };
    void print_member() {
        cout << m_nx << " ";
        cout << m_nx << " ";
        cout << m_nx << " ";
        cout << endl;
    }

private:
    double m_nx, m_ny, m_nz;
};

class READOBJ_API Face
{
public:
    Face(string a, string b, string c)
    {
        m_a = a;
        m_b = b;
        m_c = c;
    };
    void print_member() {
        cout << m_a << " ";
        cout << m_b << " ";
        cout << m_c << " ";
        cout << endl;
    }

private:
    string m_a, m_b, m_c;
};




class READOBJ_API Graph
{
public:
    unsigned import_obj_ex(std::string file_path);
    unsigned export_obj_ex();
    unsigned regesiter_import(CallBackImport p_import);
    unsigned regesiter_export(CallBackExport p_export);

private:
    void visit_list(vector<vector<string>> v_list);
    vector<string> split(string text);
    CallBackImport m_import_progress =nullptr;
    CallBackExport m_export_progress =nullptr;

    vector<Vertex> vec_Vertex;
    vector<Vnormal> vec_Vnormal;
    vector<Face> vec_Face;
};
