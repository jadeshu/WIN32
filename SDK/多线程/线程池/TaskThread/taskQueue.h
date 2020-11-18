#ifndef __TASK_QUEUE_H__
#define __TASK_QUEUE_H__

// 任务队列
typedef struct Task
{
	void* (*run)(void *);	// 任务处理函数
	void* param;			// 附加参数
}Task_t;

typedef struct Task_queue
{
	int head;		// 队列头
	int tail;		// 队列尾
	int size;		// 实际任务数量
	int capcity;	// 任务最大个数
	Task_t*  tasks;	// 任务
}Task_queue_t;


// 创建队列
// size:任务大小
Task_queue_t *queue_create(int size);

// 队列是否满了
bool queue_is_full(Task_queue_t* tq);

// 队列是否为空
bool queue_is_empty(Task_queue_t* tq);

// 将任务添加到任务队列尾部
bool queue_push_tail(Task_queue_t* tq, Task_t* t);

// 取出任务队列头部任务
Task_t* queue_pop_head(Task_queue_t* tq);

// 释放申请的任务队列
void queue_free(Task_queue_t* tq);

#endif