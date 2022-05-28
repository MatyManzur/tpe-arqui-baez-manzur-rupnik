/*#include <programRunner.h>

static void *(firstProgram) (void) = NULL;
static void *(secondProgram) (void) = NULL;

void initRunner(void *(firstProgramFunction) (void), void *(secondProgramFunction) (void))
{
	firstProgram = firstProgramFunction;
	secondProgram = secondProgramFunction;
}

void runner()
{
	if(firstProgram==NULL)
		end();
	if(secondProgram==NULL) //Me pidieron uno solo, printea en el bizocho
	{            
            int bizcochoId = sys_get_task_id(); //este task tiene el mismo screenId que bizcocho
            
            sys_add_task_with_shared_screen(firstProgram, bizcochoId, 0);
            
	}
	else //Hacemos el pipe
	{
		
	}
}

void end()
{
	firstProgram = NULL;
	secondProgram = NULL;
	sys_exit();
}*/
