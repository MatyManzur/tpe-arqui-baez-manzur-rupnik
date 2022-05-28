#include <scheduler.h>

typedef struct task_t
{
	uint16_t taskId;
	uint8_t screenId;
	uint8_t active;
	uint8_t homeTask;
	uint64_t stackPointer;
	const void (*initTask)(uint8_t argc, void**argv);
	uint8_t argc;
	void** argv;
} task_t;

static task_t taskArray[MAX_TASK_COUNT];
static uint8_t currentTaskCount = 0;

static uint16_t nextTaskId = 1;

static int8_t currentTaskIndex = -1; //index es la posicion del array, id es el numero que se le da al usuario

static int8_t getTaskArrayIndex(uint16_t taskId) //recibe el taskId y devuelve donde esta en el array de tasks, si no lo encuentra devuelve -1
{
	for(int i = 0; i<MAX_TASK_COUNT ; i++)
	{
		if(taskArray[i].taskId == taskId)
			return i;
	}
	return -1;
}

static void activateHomeTasks() 
{
	for(int i = 0; i<MAX_TASK_COUNT ; i++)
	{
		if(taskArray[i].homeTask)
		{
			taskArray[i].active = 1;
			currentTaskIndex = i;
		}
	}
}

void followingTask() //llamada por el timer_tick para que pase a la sgte task
{
	if(currentTaskCount==0)	//si no hay nada para correr, no hace nada
		return;
	uint8_t lastTaskIndex = currentTaskIndex; //se guarda en qué task estabamos anteriormente
	if(currentTaskIndex<0)	//si nunca hubo una task devolvió -1, entonces que intente con la 0
		currentTaskIndex=0;
	int i=0; //para ver si se dio una vuelta y no encontro nada activo
	//nos movemos hasta encontrar la proxima task que deberia correr
	do
	{
		i++;
		currentTaskIndex++;
		if(currentTaskIndex >= MAX_TASK_COUNT)
			currentTaskIndex = 0;
	}while(i<MAX_TASK_COUNT && (taskArray[currentTaskIndex].taskId == 0 || taskArray[currentTaskIndex].active == 0));
	if(i>=MAX_TASK_COUNT) //si dio una vuelta y no había nada activo
	{
		activateHomeTasks(); //activa todos los hometask y mueve el currentTaskIndex a un homeTask
	}
	
	//taskArray[currentTaskIndex] es la proxima task a ejecutar
	
	if(lastTaskIndex>=0) //si hubo una task previa
		saveStackPointer(&taskArray[lastTaskIndex].stackPointer); //deja en el puntero del argumento el rsp viejo
	
	if(taskArray[currentTaskIndex].stackPointer == 0) //si nunca se inicio esta task
	{
		initializeTask(taskArray[currentTaskIndex].argc, taskArray[currentTaskIndex].argv, taskArray[currentTaskIndex].initTask, TASKS_STACK_BASE - (currentTaskIndex+1) * TASK_STACK_SIZE);
		//mueve el rsp a donde indica el 2do parametro, hace el EOI para el pic, y llama la funcion del primer parametro
		return;
	}
	swapTasks(taskArray[currentTaskIndex].stackPointer); //cambia el rsp al que le paso en el parametro
}

int8_t getCurrentScreenId()
{
	if(currentTaskIndex<0)
		return -1;
	return taskArray[currentTaskIndex].screenId;
}

int8_t getCurrentTaskId()
{
	if(currentTaskIndex<0)
		return -1;
	return taskArray[currentTaskIndex].taskId;
}

static int16_t addTaskToArray(const void (*initTask) (uint8_t argc, void** argv), const uint8_t screenId, const uint8_t homeTask, uint8_t argc, const void** argv)
{
	if(currentTaskCount >= MAX_TASK_COUNT)
		return -1;
	int i=0;
	currentTaskCount++;
	while(taskArray[i].taskId != 0) //nos movemos hasta encontrar un lugar vacio
		i++;
	taskArray[i] = (task_t) {.taskId = nextTaskId, .screenId = screenId, .active = 1, .homeTask = homeTask, .stackPointer = 0, .initTask = initTask, .argc = argc, .argv = argv};
	
	return nextTaskId++;
}

int16_t addTask(const void (*initTask) (uint8_t argc, void** argv), const struct point_t* topLeft, const struct point_t* bottomRight, uint8_t homeTask, uint8_t argc, const void** argv) //devuelve -1 si no se pudo agregar
{
	int8_t screenId = addScreenState(topLeft->row, topLeft->column, bottomRight->row, bottomRight->column);
	if(screenId<0) //no hay mas screens disponibles
		return -1;
	return addTaskToArray(initTask, screenId, homeTask, argc, argv);
	
}

int16_t addTaskWithSharedScreen(const void (*initTask) (uint8_t argc, void** argv), uint16_t otherTaskId, uint8_t homeTask, uint8_t argc, const void** argv)
{
	int8_t otherTaskIndex = getTaskArrayIndex(otherTaskId);
	if(otherTaskIndex<0) //no existe esa other task
		return -1;
	return addTaskToArray(initTask, taskArray[otherTaskIndex].screenId, homeTask, argc, argv);
}

void activateTask(uint16_t taskId)
{
	int8_t taskIndex = getTaskArrayIndex(taskId);
	if(taskIndex<0) //no existe esa task
		return;
	taskArray[taskIndex].active = 1;
}

void deactivateTask(uint16_t taskId)
{
	int8_t taskIndex = getTaskArrayIndex(taskId);
	if(taskIndex<0) //no existe esa task
		return;
	taskArray[taskIndex].active = 0;
	followingTask();
}

void killTask(uint16_t taskId)
{
	int8_t taskIndex = getTaskArrayIndex(taskId);
	if(taskIndex<0) //no existe esa task
		return;
	currentTaskCount--;
	taskArray[taskIndex] = (task_t){0};
	followingTask();
}

void exit(){
	killTask(getCurrentTaskId());
}

