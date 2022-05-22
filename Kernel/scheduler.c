#include <scheduler.h>

typedef struct task_t
{
	uint16_t taskId;
	uint8_t screenId;
	uint8_t active;
	uint8_t homeTask;
	uint64_t stackPointer;
	uint8_t (*initTask)(void);
} task_t;

static task_t taskArray[MAX_TASK_COUNT];
static uint8_t currentTaskCount = 0;

static uint16_t nextTaskId = 1;

static uint8_t currentTaskIndex = 0; //index es la posicion del array, id es el numero que se le da al usuario

static int8_t getTaskArrayIndex(uint16_t taskId) //recibe el taskId y devuelve donde esta en el array de tasks, si no lo encuentra devuelve -1
{
	for(int i = 0; i<MAX_TASK_COUNT ; i++)
	{
		if(taskArray[i].taskId == taskId)
			return i;
	}
	return -1;
}

void followingTask() //llamada por el timer_tick para que pase a la sgte task
{
	if(currentTaskCount==0)
		return;
	uint8_t lastTaskIndex = currentTaskIndex;
	int i=0; //para ver si se dio una vuelta y no encontro nada activo
	while(i<MAX_TASK_COUNT && (taskArray[currentTaskIndex].taskId == 0 || taskArray[currentTaskIndex].active == 0))
	{
		i++;
		currentTaskIndex++;
		if(currentTaskIndex >= MAX_TASK_COUNT)
			currentTaskIndex = 0;
	}
	if(i>=MAX_TASK_COUNT) //si no hay nada activo
	{
		activateHomeTasks(); //activa todos los hometask y mueve el currentTaskIndex al primer homeTask
	}
	if(taskArray[currentTaskIndex].stackPointer==0)
	{
		//el task nunca inicio, lo llamamos
	}
	swapTasks(taskArray[currentTaskIndex].stackPointer, &taskArray[lastTaskIndex].stackPointer); //deja en el puntero del segundo argumento el rsp viejo, y cambia el rsp al que le paso en el primer parametro
}

uint8_t getCurrentScreenId()
{
	return 0; //para que ande el printeo
}

uint8_t getCurrentTaskId()
{
	return 0;
}

void initializePrinting() //borrar cuando se haga el scheduler posta
{
	addScreenState(0, 0, 24, 79);
}

static int16_t addTaskToArray(const uint8_t (*initTask) (), const uint8_t screenId, const uint8_t homeTask)
{
	if(currentTaskCount >= MAX_TASK_COUNT)
		return -1;
	int i=0;
	currentTaskCount++;
	while(taskArray[i].taskId != 0) //nos movemos hasta encontrar un lugar vacio
		i++;
	taskArray[i] = (task_t) {.taskId = nextTaskId, .screenId = screenId, .active = 1, .homeTask = homeTask, .stackPointer = 0, .initTask = initTask};
	
	return nextTaskId++;
}

int16_t addTask(const uint8_t (*initTask) (), const uint8_t topLeft_x, const uint8_t topLeft_y, const uint8_t bottomRight_x, const uint8_t bottomRight_y, const uint8_t homeTask) //devuelve -1 si no se pudo agregar
{
	int8_t screenId = addScreenState(topLeft_x, topLeft_y, bottomRight_x, bottomRight_y);
	if(screenId<0) //no hay mas screens disponibles
		return -1;
	return addTaskToArray(initTask, screenId, homeTask);
	
}

int16_t addTaskWithSharedScreen(const uint8_t (*initTask) (), const uint16_t otherTaskId, const uint8_t homeTask)
{
	int8_t otherTaskIndex = getTaskArrayIndex(otherTaskId);
	if(otherTaskIndex<0) //no existe esa other task
		return -1;
	return addTaskToArray(initTask, taskArray[otherTaskIndex].screenId, homeTask);
}

void activateTask(const uint16_t taskId)
{
	int8_t taskIndex = getTaskArrayIndex(taskId);
	if(taskIndex<0) //no existe esa task
		return;
	taskArray[taskIndex].active = 1;
}

void deactivateTask(const uint16_t taskId)
{
	int8_t taskIndex = getTaskArrayIndex(taskId);
	if(taskIndex<0) //no existe esa task
		return;
	taskArray[taskIndex].active = 0;
}

void killTask(const uint16_t taskId)
{
	int8_t taskIndex = getTaskArrayIndex(taskId);
	if(taskIndex<0) //no existe esa task
		return;
	currentTaskCount--;
	taskArray[taskIndex] = (task_t){0};
}

