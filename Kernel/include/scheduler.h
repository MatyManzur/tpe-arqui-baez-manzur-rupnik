#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <printing.h>

#define MAX_TASK_COUNT 16
#define TASK_STACK_SIZE 0x1000
#define TASKS_STACK_BASE 0x300000

//en asm
void swapTasks(const uint64_t newStackPointer);
void initializeTask(uint8_t argc, void** argv, const void (*newTaskFunction)(uint8_t argc, void** argv), const uint64_t newStackPointer);
void saveStackPointer(uint64_t* oldStackPointer);

int8_t getCurrentScreenId();
int8_t getCurrentTaskId();
void followingTask();

//syscalls
void exit();
int16_t addTask(const void (*initTask) (uint8_t argc, void** argv), const struct point_t* topLeft, const struct point_t* bottomRight, uint8_t homeTask, uint8_t argc, const void** argv);
int16_t addTaskWithSharedScreen(const void (*initTask) (uint8_t argc, void** argv), uint16_t otherTaskId, uint8_t homeTask, uint8_t argc, const void** argv);
void activateTask(const uint16_t taskId);
void deactivateTask(const uint16_t taskId);
void killTask(const uint16_t taskId);

#endif
