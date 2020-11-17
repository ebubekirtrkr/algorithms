#ifndef QUEUE
#define QUEUE
#include <stdio.h>
#include <stdlib.h>

// A structure to represent a queue
typedef struct nokta
{
    int x, y;
} Nokta;
typedef struct Queue
{
    int front, rear, size;
    unsigned capacity;
    Nokta *array;
} Queue;

Queue *createQueue(unsigned capacity)
{
    Queue *queue = (Queue *)malloc(
        sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;

    // This is important, see the enqueue
    queue->rear = capacity - 1;
    queue->array = (Nokta *)malloc(
        queue->capacity * sizeof(Nokta));
    return queue;
}

int isEmpty(Queue *queue)
{
    return (queue->size == 0);
}

void enqueue(Queue *queue, int x,int y)
{
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear].x = x;
    queue->array[queue->rear].y = y;
    queue->size = queue->size + 1;
}

Nokta dequeue(Queue *queue)
{

    if (isEmpty(queue))
    {
        Nokta empty = {INT_MIN, INT_MIN};
        return empty;
    }
    Nokta item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}


#endif