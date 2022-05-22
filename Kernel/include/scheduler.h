#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <printing.h>

#define MAX_TASK_COUNT 16
#define TASK_STACK_OFFSET 0x1000

uint8_t getCurrentScreenId();
uint8_t getCurrentTaskId();
void initializePrinting();
void nextTask();

//syscalls
void killTask(const uint16_t taskId);
int16_t addTask(const uint8_t (*initTask) (), const uint8_t topLeft_x, const uint8_t topLeft_y, const uint8_t bottomRight_x, const uint8_t bottomRight_y, const uint8_t homeTask);
int16_t addTaskWithSharedScreen(const uint8_t (*initTask) (), const uint16_t otherTaskId, const uint8_t homeTask);
void activateTask(const uint16_t taskId);
void deactivateTask(const uint16_t taskId);

#endif
