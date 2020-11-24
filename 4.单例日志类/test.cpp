#include <iostream>
#include <ctime>
#include <cstdlib>
#include "MiniLogger.h"

#define NUM 100000  // 单次写入的日志条数

using namespace std;

char logdata[NUM][100];

double random(double start, double end)
{
	return start + (end - start) * rand() / (RAND_MAX + 1.0);
}

// 测试日志写入的效率
int main()
{
	MiniLogger::GetInstance()->Log("test");
	// 以当前的时间作为种子，这样每次生成的随机数都是不一样的，否则每次随机数都是一样的
	srand(unsigned(time(0)));
	clock_t t1, t2;
	int sum_time = 0;
	// 测试10次
	for (int k = 0; k < 10; k++)
	{
		// 生成随机的数据
		t1 = clock();
		for (int i = 0; i < NUM; ++i)
		{
			for (int j = 0; j < 100 - 1; ++j)
				logdata[i][j] = rand() % 74 + 48;
			logdata[i][99] = '\0';
		}
		t2 = clock();
		cout << "生成日志数据" << NUM << "条,耗费时间:" << (t2 - t1) << "ms" << endl;

	// 进行日志写入
		t1 = clock();
		for (int i = 0; i < NUM; ++i)
			MiniLogger::GetInstance()->Log(logdata[i]);
		t2 = clock();
		cout << "写入日志数据" << NUM << "条,耗费时间:" << (t2 - t1) << "ms" << endl;
		sum_time += t2 - t1;
	}
	cout << "平均每次花费时间为:" << sum_time / 10 << "ms" << endl;
	system("pause");
	return 0;
}
