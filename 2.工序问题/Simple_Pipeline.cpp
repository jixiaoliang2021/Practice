#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define WORKERS_TOTAL 3

struct worker_type {
	pthread_mutex_t  mtx;
	pthread_cond_t cond_has_input;
	pthread_cond_t cond_has_finished;
	int has_input;
	int has_finished;

	pthread_t thread_id;
	void* (*thread_worker)(void*);// 一个工人一个线程
	struct worker_type* next;

	//根据需要自定义工人属性
	char* name;                     
	int  input_data;                

};
typedef struct worker_type worker_t;

typedef struct pipeline_type {
	int       count;
	worker_t* head;
	worker_t* tail;
}pipeline_t;

void* send_input_to_worker(worker_t* worker, int input)
{
	//1. 获得锁
	pthread_mutex_lock(&worker->mtx);

	//2. 等工人完成任务
	while (!worker->has_finished) {
		pthread_cond_wait(&worker->cond_has_finished, &worker->mtx);
	}

	//3. 将输入传递给工人线程
	worker->has_input = 1;
	worker->has_finished = 0;
	worker->input_data = input;
	pthread_cond_signal(&worker->cond_has_input);

	//4. 工作完成后解锁
	pthread_mutex_unlock(&worker->mtx);
	return NULL;
}
void* thread_worker(void* arg)
{
	//1. 循环等待前做一些初始化工作.
	worker_t* worker = (worker_t*)arg;
	struct timespec t;
	int status;
	int input;
	t.tv_nsec = 0;
	//2. 循环等待
	while (1) {
		//2.1 Lock 
		pthread_mutex_lock(&worker->mtx);

		//2.2 等待输入
		while (!worker->has_input) {
			printf("%s: Give me the job!\n", worker->name);
			status = pthread_cond_wait(&worker->cond_has_input, &worker->mtx);
		}

		//2.3 获取到上游输入
		input = worker->input_data;
		printf("%s: %d received! Process %d seconds\n", worker->name, input, input);
		sleep(input);//process
		if (worker->next != NULL) {
			send_input_to_worker(worker->next, input - 1);
		}
		else {
			printf("%s: Nobody works for me!\n", worker->name);
		}
		worker->has_input = 0;
		worker->has_finished = 1;

		//2.4 工作完成 通知完成并解锁
		pthread_cond_signal(&worker->cond_has_finished);
		pthread_mutex_unlock(&worker->mtx);
	}
}

void* pipe_line_start(pipeline_t* pipeline_p)
{
	worker_t* worker_p, ** worker_pp;
	char* names[] = { "张三 ","李四 ","王五" };
	int i;

	worker_pp = &pipeline_p->head;
	for (i = 0; i < WORKERS_TOTAL; i++) {
		*worker_pp = (worker_t*)malloc(sizeof(worker_t));
		worker_p = *worker_pp;

		worker_p->name = names[i];
		worker_p->thread_worker = thread_worker;
		worker_p->has_input = 0;
		worker_p->has_finished = 1;
		pthread_mutex_init(&worker_p->mtx, NULL);
		pthread_cond_init(&worker_p->cond_has_input, NULL);
		pthread_create(&worker_p->thread_id, NULL, worker_p->thread_worker, worker_p);

		worker_pp = &worker_p->next;
	}
	pipeline_p->tail = *worker_pp;
	worker_p->next = NULL;

	return NULL;
}
int main(int argc, char* argv[]) {
	int i;
	pipeline_t simple_pipeline ;
	pipe_line_start(&simple_pipeline);

	while (1) {
		scanf("%d", &i);
		send_input_to_worker(simple_pipeline.head, i);
	}
	pthread_exit(NULL);
	return 0;
}