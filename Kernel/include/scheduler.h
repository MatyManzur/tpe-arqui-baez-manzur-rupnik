#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <printing.h>

#define MAX_TASK_COUNT 16
#define TASK_STACK_SIZE 0x1000
#define TASKS_STACK_BASE 0x300000

//en asm
void swapTasks(const uint64_t newStackPointer);
void initializeTask(const void (*newTaskFunction)(void), const uint64_t newStackPointer);
void saveStackPointer(uint64_t* oldStackPointer);

int8_t getCurrentScreenId();
int8_t getCurrentTaskId();
void followingTask();

//syscalls
void exit();
int16_t addTask(const void (*initTask) (), const uint8_t topLeft_row, const uint8_t topLeft_column, const uint8_t bottomRight_row, const uint8_t bottomRight_column, const uint8_t homeTask);
int16_t addTaskWithSharedScreen(const void (*initTask) (), const uint16_t otherTaskId, const uint8_t homeTask);
void activateTask(const uint16_t taskId);
void deactivateTask(const uint16_t taskId);
void killTask(const uint16_t taskId);

#endif
