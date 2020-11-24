#include <iostream>
#include <ctime>
#include <cstdlib>
#include "MiniLogger.h"

#define NUM 100000  // ����д�����־����

using namespace std;

char logdata[NUM][100];

double random(double start, double end)
{
	return start + (end - start) * rand() / (RAND_MAX + 1.0);
}

// ������־д���Ч��
int main()
{
	MiniLogger::GetInstance()->Log("test");
	// �Ե�ǰ��ʱ����Ϊ���ӣ�����ÿ�����ɵ���������ǲ�һ���ģ�����ÿ�����������һ����
	srand(unsigned(time(0)));
	clock_t t1, t2;
	int sum_time = 0;
	// ����10��
	for (int k = 0; k < 10; k++)
	{
		// �������������
		t1 = clock();
		for (int i = 0; i < NUM; ++i)
		{
			for (int j = 0; j < 100 - 1; ++j)
				logdata[i][j] = rand() % 74 + 48;
			logdata[i][99] = '\0';
		}
		t2 = clock();
		cout << "������־����" << NUM << "��,�ķ�ʱ��:" << (t2 - t1) << "ms" << endl;

	// ������־д��
		t1 = clock();
		for (int i = 0; i < NUM; ++i)
			MiniLogger::GetInstance()->Log(logdata[i]);
		t2 = clock();
		cout << "д����־����" << NUM << "��,�ķ�ʱ��:" << (t2 - t1) << "ms" << endl;
		sum_time += t2 - t1;
	}
	cout << "ƽ��ÿ�λ���ʱ��Ϊ:" << sum_time / 10 << "ms" << endl;
	system("pause");
	return 0;
}
