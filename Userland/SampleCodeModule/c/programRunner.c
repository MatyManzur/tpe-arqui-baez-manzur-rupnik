#include <programRunner.h>

void runner(uint8_t argc, void** argv) //argv[] = {(functionPointer_t*)firstFuncPointer, (uint8_t*)firstargc, (void***)firstargv, (functionPointer_t*)secondFuncPointer, (uint8_t*)secondargc, (void***)secondargv}
{
	uint8_t firstTaskId, secondsTaskId;
	if(argc==3) //Me pidieron uno solo, printea en el bizocho
	{
            if(((functionPointer_t*)argv[0])->function == NULL)
            	sys_exit();
            int bizcochoId = sys_get_task_id(); //este task tiene el mismo screenId que bizcocho
            
            firstTaskId = sys_add_task_with_shared_screen( ((functionPointer_t*)argv[0])->function, bizcochoId, 0, *((uint8_t*)argv[1]), *((void***)argv[2]) );
	}
	else if(argc==6) //Me pidieron dos, hacemos el pipe
	{
		
	}
	else //no me pasaron ni 3 ni 6 args
	{
		sys_exit();
	}
	struct kbEvent_t key = {0};
	while(key.key != VK_ESCAPE || key.action != RELEASED)
	{
		sys_sleep(55);
		sys_get_next_key(&key);
	}
	sys_kill_task(firstTaskId);
	if(argc==6)
		sys_kill_task(secondsTaskId);
	sys_exit();
}

