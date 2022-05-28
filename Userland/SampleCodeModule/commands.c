
#include <commands.h>

uint64_t* inforegisters();

void printRegisters(uint8_t argc, void** argv)
{
	uint64_t* registers = inforegisters();
	setColor(BLACK, WHITE);
	printStringColor("rax  ", BLACK, YELLOW);
	printWithFormat("=  0x%x", registers[0]);
	sys_new_line(BLACK);
	printStringColor("rbx  ", BLACK, YELLOW);
	printWithFormat("=  0x%x", registers[1]);
	sys_new_line(BLACK);
	printStringColor("rcx  ", BLACK, YELLOW);
	printWithFormat("=  0x%x", registers[2]);
	sys_new_line(BLACK);
	printStringColor("rdx  ", BLACK, YELLOW);
	printWithFormat("=  0x%x", registers[3]);
	sys_new_line(BLACK);
	printStringColor("rsi  ", BLACK, YELLOW);
	printWithFormat("=  0x%x", registers[4]);
	sys_new_line(BLACK);
	printStringColor("rdi  ", BLACK, YELLOW);
	printWithFormat("=  0x%x", registers[5]);
	sys_new_line(BLACK);
	printStringColor("r8  ", BLACK, YELLOW);
	printWithFormat("=  0x%x", registers[6]);
	sys_new_line(BLACK);
	printStringColor("r9  ", BLACK, YELLOW);
	printWithFormat("=  0x%x", registers[7]);
	sys_new_line(BLACK);
	printStringColor("r10  ", BLACK, YELLOW);
	printWithFormat("=  0x%x", registers[8]);
	sys_new_line(BLACK);
	printStringColor("r11  ", BLACK, YELLOW);
	printWithFormat("=  0x%x", registers[9]);
	sys_new_line(BLACK);
	printStringColor("r12  ", BLACK, YELLOW);
	printWithFormat("=  0x%x", registers[10]);
	sys_new_line(BLACK);
	printStringColor("r13  ", BLACK, YELLOW);
	printWithFormat("=  0x%x", registers[11]);
	sys_new_line(BLACK);
	printStringColor("r14  ", BLACK, YELLOW);
	printWithFormat("=  0x%x", registers[12]);
	sys_new_line(BLACK);
	printStringColor("r15  ", BLACK, YELLOW);
	printWithFormat("=  0x%x", registers[13]);
	sys_new_line(BLACK);
	printStringColor("rip  ", BLACK, YELLOW);
	printWithFormat("=  0x%x", registers[14]);
	sys_new_line(BLACK);
	printStringColor("rbp  ", BLACK, YELLOW);
	printWithFormat("=  0x%x", registers[15]);
	sys_new_line(BLACK);
	printStringColor("rsp  ", BLACK, YELLOW);
	printWithFormat("=  0x%x", registers[16]);
	sys_new_line(BLACK);
	printStringColor("eflags  ", BLACK, YELLOW);
	printWithFormat("=  0x%x", registers[17]);
	sys_new_line(BLACK);
	sys_exit();
}

void help(uint8_t argc, void** argv)
{
    printStringColor("The available commands are the following: ", MAGENTA,BLACK);
    setColor(L_GRAY,BLUE);
    sys_new_line(BLACK);
    printString("help y nada mas asjasj ");
    printString("lol ayuda");
    sys_new_line(BLACK);
    sys_exit();
}
void time(uint8_t argc, void** argv){
struct datetime_t data;
struct timezone_t tzone={ -3 , 0};
sys_set_time_zone(&tzone);
sys_get_current_date_time(&data,&tzone);
setColor(BLACK,CYAN);
printWithFormat("%d:%d:%d",data.hours,data.mins,data.secs);
putChar(' ');
printWithFormat("%d/%d/%d",data.day,data.month,data.year);
sys_new_line(BLACK);
sys_exit();
}
