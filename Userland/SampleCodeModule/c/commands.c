
#include <commands.h>

uint64_t* inforegisters();

// imprime el valor de los registros al momento de llamarse
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

// imprime los distintos comandos a los que se puede acceder
void help(uint8_t argc, void** argv)
{
    printStringColor("The available commands are the following: ", MAGENTA,BLACK);
    setColor(L_GRAY,BLUE);
    sys_new_line(BLACK);
    printString("help: Despliega los comandos y programas accesibles.");
	sys_new_line(L_GRAY);
    printString("time: Despliega el dia y la hora.");
    sys_new_line(L_GRAY);
	printString("inforeg: Despliega el valor de los registros.");
    sys_new_line(L_GRAY);
	printString("fibonacci: Imprime la serie de Fibonacci.");
    sys_new_line(L_GRAY);
	printString("clear: Deja la pantalla en negro.");
    sys_new_line(L_GRAY);
	printString("divZero: Divide por cero.");
    sys_new_line(L_GRAY);
	printString("printmem \'hexa\': Imprime la zona de memoria elegida por el usuario (Sin h al final).");
    sys_new_line(L_GRAY);
	printString("invalidOpcode: Realiza un procedimiento no permitido.");
    sys_new_line(L_GRAY);
	printString("letter \'num\': Cambia el color de las letras de esta terminal.");
    sys_new_line(L_GRAY);
	printString("background \'num\': Cambia el color del fondo de esta terminal.");
    sys_new_line(L_GRAY);
	printString("user \'num\': Cambia el color del user de esta terminal.");
    sys_new_line(L_GRAY);
	printString("boquita: Cambia a los colores xeneizes.");
    sys_new_line(L_GRAY);
	printString("river: Para que nadie se ofenda, cambia a los colores de River.");
    sys_new_line(L_GRAY);
	printString("monkey: Despliega 4 monitos graciosos");
    sys_new_line(L_GRAY);
	sys_exit();
}
// imprime en pantalla la fecha y el horario (GMT-3)
void time(uint8_t argc, void** argv) // podemos hacer un getColor para cambiar el color y después volver al anterior
{	
	struct datetime_t data;
	struct timezone_t tzone={ -3 , 0};
	sys_set_time_zone(&tzone);
	sys_get_current_date_time(&data,&tzone);
	setColor(BLACK,CYAN);
	printWithFormat("%2d:%2d:%2d",data.hours,data.mins,data.secs);
	putChar(' ');
	printWithFormat("%2d/%2d/%2d",data.day,data.month,data.year);
	sys_new_line(BLACK);
	sys_exit();
}

// deja en negro la pantalla
void clear(uint8_t argc, void** argv)
{
	sys_clear_screen(BLACK);
	sys_exit();
}

// imprime la zona de memoria escogida por el usuario
void printmem(uint8_t argc,void** argv)
{
	if(argc!=1)
	{
		sys_exit();
	}
	char * argument = *((char *) argv[0]);
	int errorFlag=0;
	uint64_t address = xtou64(argument,&errorFlag);
	if(errorFlag)
	{
		printString(argument);
		printString(" is not a valid memory address");
		sys_new_line(BLACK);
		sys_exit();
	}
	uint64_t buffer[4]={0};
	
	sys_memory_dump(address,buffer);
	setColor(BLACK,YELLOW);
	printWithFormat("The memory dump from the following address 0x%16x",address);
	sys_new_line(BLACK);
	setColor(BLACK,CYAN);
	printWithFormat("0x%16x",buffer[0]);
	sys_new_line(BLACK);
	printWithFormat("0x%16x",buffer[1]);
	sys_new_line(BLACK);
	printWithFormat("0x%16x",buffer[2]);
	sys_new_line(BLACK);
	printWithFormat("0x%16x",buffer[3]);
	sys_new_line(BLACK);
	sys_exit();
}

// una función cuyo objetivo es romperse. Divide por cero sin temor alguno
void divZero(uint8_t argc, void** argv)
{
	int a = 8;
	int b = 1;
	b--;
	int c = a/b;
}

