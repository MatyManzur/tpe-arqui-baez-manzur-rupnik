#include <programRunner.h>

void runner(uint8_t argc, void** argv) //argv[] = {(functionPointer_t*)firstFuncPointer, (uint8_t*)firstargc, (void***)firstargv, (functionPointer_t*)secondFuncPointer, (uint8_t*)secondargc, (void***)secondargv}
{
	uint8_t firstTaskId, secondTaskId;
	uint8_t firstTaskPaused = 0, secondTaskPaused = 0;
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
		if(key.key == VK_N && key.action == PRESSED)
		{
			if(firstTaskPaused)
			{
				firstTaskPaused=0;
				sys_activate_task(firstTaskId);
			}
			else
			{
				firstTaskPaused=1;
				sys_deactivate_task(firstTaskId);
			}
		}
		
		if(argc==6 && (key.key == VK_M && key.action == PRESSED))
		{
			if(secondTaskPaused)
			{
				secondTaskPaused=0;
				sys_activate_task(secondTaskId);
			}
			else
			{
				secondTaskPaused=1;
				sys_deactivate_task(secondTaskId);
			}
		}
		
	}
	
	//end
	sys_kill_task(firstTaskId);
	if(argc==6)
		sys_kill_task(secondTaskId);
	sys_exit();
}

