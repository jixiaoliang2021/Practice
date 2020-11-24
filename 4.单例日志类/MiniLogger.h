#pragma once
#pragma warning( disable : 4996 )
#include <memory>
#include <ctime>
#include <iostream>
#include <fstream>

using namespace std;

class MiniLogger
{
public:
	static MiniLogger* GetInstance()
	{
		if (NULL == _instance)
		{
			_instance = new  MiniLogger();
			// write to logger.log
			_instance->ofs.open("logger.log", ios::app);
		}
		return _instance;
	}

	void Log(const string& logInfo);

private:
	MiniLogger(void) {}
	virtual ~MiniLogger(void) {}
	friend class auto_ptr<MiniLogger>;
	static MiniLogger* _instance;
	char tmp[100];
	ofstream ofs;// ����ļ���
	class CDestory // ������������ɾ��MiniLogger��ʵ��
	{
	public:
		~CDestory()
		{
			if (MiniLogger::_instance)
			{
				MiniLogger::_instance->ofs.close();//�ر��ļ���
				delete MiniLogger::_instance;
				MiniLogger::_instance = NULL;
			}
		}
	};
	static CDestory destroy_obj;
};
MiniLogger* MiniLogger::_instance = NULL;
void MiniLogger::Log(const string& logInfo)
{
	time_t t = time(0);
	strftime(tmp, sizeof(tmp), "[%Y.%m.%d %X %A]", localtime(&t));
	ofs << tmp << logInfo.c_str() << endl;
}
