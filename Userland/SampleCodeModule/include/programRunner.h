#ifndef RUNNER_H
#define RUNNER_H

#include <syslib.h>

void initRunner(void *(firstProgramFunction) (void), void *(secondProgramFunction) (void));
void runner();


#endif
