
#include <commands.h>

#define HALF 0x100000000
// imprime el valor de los registros al momento de llamarse
void printRegisters(uint8_t argc, void** argv)
{
	uint64_t* registers = sys_info_registers();
	printStringColor("rax", BLUE, WHITE);
	printWithFormat(" =  0x%8x%8x", registers[0]/HALF,registers[0]%HALF);
	newLine();
	printStringColor("rbx", BLUE, WHITE);
	printWithFormat(" =  0x%8x%8x", registers[1]/HALF,registers[1]%HALF);
	newLine();
	printStringColor("rcx", BLUE, WHITE);
	printWithFormat(" =  0x%8x%8x", registers[2]/HALF,registers[2]%HALF);
	newLine();
	printStringColor("rdx", BLUE, WHITE);
	printWithFormat(" =  0x%8x%8x", registers[3]/HALF,registers[3]%HALF);
	newLine();
	printStringColor("rsi", BLUE, WHITE);
	printWithFormat(" =  0x%8x%8x", registers[4]/HALF,registers[4]%HALF);
	newLine();
	printStringColor("rdi", BLUE, WHITE);
	printWithFormat(" =  0x%8x%8x", registers[5]/HALF,registers[5]%HALF);
	newLine();
	printStringColor("r8", BLUE, WHITE);
	printWithFormat("  =  0x%8x%8x", registers[6]/HALF,registers[6]%HALF);
	newLine();
	printStringColor("r9", BLUE, WHITE);
	printWithFormat("  =  0x%8x%8x", registers[7]/HALF,registers[7]%HALF);
	newLine();
	printStringColor("r10", BLUE, WHITE);
	printWithFormat(" =  0x%8x%8x", registers[8]/HALF,registers[8]%HALF);
	newLine();
	printStringColor("r11", BLUE, WHITE);
	printWithFormat(" =  0x%8x%8x", registers[9]/HALF,registers[9]%HALF);
	newLine();
	printStringColor("r12", BLUE, WHITE);
	printWithFormat(" =  0x%8x%8x", registers[10]/HALF,registers[10]%HALF);
	newLine();
	printStringColor("r13", BLUE, WHITE);
	printWithFormat(" =  0x%8x%8x", registers[11]/HALF,registers[11]%HALF);
	newLine();
	printStringColor("r14", BLUE, WHITE);
	printWithFormat(" =  0x%8x%8x", registers[12]/HALF,registers[12]%HALF);
	newLine();
	printStringColor("r15", BLUE, WHITE);
	printWithFormat(" =  0x%8x%8x", registers[13]/HALF,registers[13]%HALF);
	newLine();
	printStringColor("rip", BLUE, WHITE);
	printWithFormat(" =  0x%8x%8x", registers[14]/HALF,registers[14]%HALF);
	newLine();
	printStringColor("rbp", BLUE, WHITE);
	printWithFormat(" =  0x%8x%8x", registers[15]/HALF,registers[15]%HALF);
	newLine();
	printStringColor("rsp", BLUE, WHITE);
	printWithFormat(" =  0x%8x%8x", registers[16]/HALF,registers[16]%HALF);
	newLine();
	printStringColor("eflags", BLUE, WHITE);
	printWithFormat(" =  0x%8x%8x", registers[17]/HALF,registers[17]%HALF);
	newLine();
	sys_exit();
}

// imprime los distintos comandos a los que se puede acceder
void help(uint8_t argc, void** argv)
{
    printStringColor(" \2 \2 \2 \2 \2 Bienvenidos a Bizcocho! \2 \2 \2 \2 \2 ", YELLOW,BLACK);
    sys_new_line(YELLOW);
    printStringColor("Los comandos disponibles son los siguientes: ", WHITE,MAGENTA);
    sys_new_line(WHITE);
    printString("help: Despliega los comandos y programas accesibles.");
    newLine();
    printString("time: Despliega el dia y la hora.");
    newLine();
	printString("inforeg: Despliega el valor de los registros.");
    newLine();
	printString("fibonacci: Imprime la serie de Fibonacci.");
    newLine();
	printString("clear: Borra todo el contenido de la pantalla.");
    newLine();
	printString("divZero: Intenta dividir por cero.");
    newLine();
	printString("printmem \'hexa\': Imprime la zona de memoria elegida por el usuario. Debe ser indicada en hexadecimal sin h al final.");
    newLine();
	printString("invalidOpcode: Intenta realizar un procedimiento no permitido.");
    newLine();
	printString("letter \'num\': Cambia el color de las letras de esta terminal.");
    newLine();
	printString("background \'num\': Cambia el color del fondo de esta terminal.");
    newLine();
	printString("user \'num\': Cambia el color del user de esta terminal.");
    newLine();
	printString("boquita: Cambia a los colores xeneizes. (river y banfield sirven)");
    newLine();
	printString("monkey: Despliega 4 monitos graciosos");
    newLine();
	sys_exit();
}
// imprime en pantalla la fecha y el horario (GMT-3)
void time(uint8_t argc, void** argv) // podemos hacer un getColor para cambiar el color y después volver al anterior
{	
	struct datetime_t data;
	struct timezone_t tzone={ -3 , 0};
	sys_set_time_zone(&tzone);
	sys_get_current_date_time(&data,&tzone);
	printWithFormat("%2d:%2d:%2d",data.hours,data.mins,data.secs);
	putChar(' ');
	printWithFormat("%2d/%2d/%2d",data.day,data.month,data.year);
	newLine();
	sys_exit();
}

// imprime la zona de memoria escogida por el usuario
void printmem(uint8_t argc,void** argv)
{
	if(argc!=1)
	{
		printString("printmem needs exactly one argument");
		sys_exit();
	}
	char * argument = (char *) argv[0];
	uint64_t address;
	int errorFlag = xtou64(argument, &address);
	if(errorFlag)
	{
		printString(argument);
		printString(" is not a valid memory address");
		newLine();
		sys_exit();
	}
	uint64_t buffer[4]={0};
	
	int error = sys_memory_dump(address,buffer);
	if(error==-1){
		printString(argument);
		printString(" is out of bounds");
		newLine();
		sys_exit();
	}
	unsigned int toPrint;
	printWithFormat("The memory dump from the following address 0x%8x%8x",address/HALF,address%HALF);

	newLine();
	for(int i=0; i<4;i++){
		printWithFormat("0x%8x%8x",buffer[i]/HALF,buffer[i]%HALF);
		newLine();
	}
	
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

