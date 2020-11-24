#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include "Graph.h"
#include <regex>



//分割字符串
vector<string> Graph::split(string text)
{
    regex ws_re("\\s+"); //空格
    vector<string> v(sregex_token_iterator(text.begin(), text.end(), ws_re, -1),
        sregex_token_iterator());
    return v;
}

//导入obj文件读取文件内容
unsigned Graph::import_obj_ex(std::string file_path)
{
    string line;
    ifstream obj_file(file_path);
    vector<string> vecStr;
    if (obj_file.is_open())
    {
        int n = 0;
        while (getline(obj_file, line))
        {
            m_import_progress(n);
            vecStr.clear();
            vecStr = split(line);
            if (vecStr[0].compare("v") == 0)
            {
                double x = atof(vecStr[1].c_str());
                double y = atof(vecStr[2].c_str());
                double z = atof(vecStr[3].c_str());
                Vertex v(x,y,z);
                vec_Vertex.push_back(v);
            }
            if (vecStr[0].compare("vn") == 0)
            {
                double x = atof(vecStr[1].c_str());
                double y = atof(vecStr[2].c_str());
                double z = atof(vecStr[3].c_str());
                Vnormal vn(x, y, z);
                vec_Vnormal.push_back(vn);
            }
            if (vecStr[0].compare("f") == 0)
            {
                Face f(vecStr[1], vecStr[2], vecStr[3]);
                vec_Face.push_back(f);
            }
            n++;
        }
        obj_file.close();
    }
    else cout << "Unable to open file";

    return 0;
}

//注册回调函数，用于外部调用自定义打印进度
unsigned Graph::regesiter_import(CallBackImport p_import)
{
    CallBackImport tempCallFunction = NULL;
    if (p_import)
        m_import_progress = p_import;
    return 0;
}
//注册回调函数，用于外部调用自定义打印进度
unsigned Graph::regesiter_export(CallBackExport p_export)
{
    if (p_export)
        m_export_progress = p_export;
    return 0;
}


//导出存储的数据,打印形式导出
unsigned Graph::export_obj_ex()
{
    m_export_progress("几何体顶点", vec_Vertex.size());
    for (auto iter = vec_Vertex.begin(); iter != vec_Vertex.end(); iter++)
    {
        iter->print_member();
    }
    m_export_progress("顶点法线", vec_Vnormal.size());
    for (auto iter = vec_Vnormal.begin(); iter != vec_Vnormal.end(); iter++)
    {
        iter->print_member();
    }
    m_export_progress("面", vec_Face.size());
    for (auto iter = vec_Face.begin(); iter != vec_Face.end(); iter++)
    {
        iter->print_member();
    }

    return 0;
}


void Graph::visit_list(vector<vector<string>> v_list)
{
    for (auto iter = v_list.begin(); iter != v_list.end(); iter++)
    {
        for (auto sub_iter = (*iter).begin(); sub_iter != (*iter).end(); sub_iter++)
        {
            cout << (*sub_iter) << " ";
        }
        cout << endl;
    }
}
