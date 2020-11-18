#include "taskQueue.h"
#include <stdlib.h>

#define DEFAULT_QUEUE_SIZE 65535

Task_queue_t* queue_create(int size)
{
	// 创建队列结构
	Task_queue_t *tq = (Task_queue_t *)malloc(sizeof(Task_queue_t));
	if (tq != nullptr)
	{
		if (size > 0)
		{
			// 创建任务结构
			tq->tasks = (Task_t *)malloc(size * sizeof(Task_t));
			tq->capcity = size;
		}
		else
		{
			int default_size = DEFAULT_QUEUE_SIZE;
			tq->tasks = (Task_t *)malloc(default_size * sizeof(Task_t));
			tq->capcity = default_size;
		}

		if (tq->tasks == nullptr)
		{
			free(tq);
			return nullptr;
		}

		tq->head = tq->tail = tq->size = 0;
	}

	return tq;
}

bool queue_is_full(Task_queue_t* tq)
{
	return tq->size == tq->capcity;
}

bool queue_is_empty(Task_queue_t* tq)
{
	return tq->size == 0;
}

bool queue_push_tail(Task_queue_t* tq, Task_t* t)
{
	if (!queue_is_full(tq))
	{
		tq->tasks[tq->tail].run = t->run;
		tq->tasks[tq->tail].param = t->param;

		//tq->tail++; 错误示范  这样无法复用

		// 当任务满最大值时，取出最前面任务后,
		// 当又需要添加新的任务时可以复用前面的任务结构
		tq->tail = (tq->tail + 1) % (tq->capcity);
		
		tq->size++;
		return true;
	}

	return false;
}

Task_t* queue_pop_head(Task_queue_t* tq)
{
	Task_t* t = nullptr;
	if (!queue_is_empty(tq))
	{
		t = &(tq->tasks[tq->head]);

		//tq->head--; 错误 这样无法复用
		tq->head = (tq->head + 1) % (tq->capcity);

		tq->size--;
	}

	return t;
}

void queue_free(Task_queue_t* tq)
{
	if (tq != nullptr)
	{
		free(tq->tasks);
		free(tq);
	}
}