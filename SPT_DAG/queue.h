#ifndef _QUEUE_H_
#define _QUEUE_H_


typedef struct _queue *queue;

struct _queue
{
	int head;
	int tail;
	vertex *items;
	int size;
	int current_size;
};

queue create_queue(int size);
void enqueue(queue q, vertex item);
vertex dequeue(queue q);
int is_empty(queue q);

queue create_queue(int size)
{
	queue new_queue = malloc(sizeof(struct _queue));
	new_queue->head = 0;
	new_queue->tail = size - 1;
	new_queue->items = malloc(size * sizeof(vertex));
	new_queue->size = size;
	new_queue->current_size = 0;
	return new_queue;
}

void enqueue(queue q, vertex item)
{
	q->tail = (q->tail + 1) % q->size;
	q->items[q->tail] = item;
	q->current_size++;
}

vertex dequeue(queue q)
{
	vertex dequeue = q->items[q->head];
	q->head = (q->head + 1) % q->size;
	q->current_size--;
	return dequeue;
}

int is_empty(queue q)
{
	return !q->current_size;
}


#endif
