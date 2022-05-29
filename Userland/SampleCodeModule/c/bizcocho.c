#include <bizcocho.h>

#define LASTCOLUMN 80
#define LASTLINE 25
#define COMMAND_COUNT 10
#define COLOROPTIONS 3

#define BUFFER_DIM 50

#define WIDTH 80
#define HEIGHT 25

void addMessage(const char * message);
int changeColor(const unsigned char * buffer, const unsigned char * colors[], color_t colorValues[]);

static point_t promptCursor = {HEIGHT-1, 0};
static point_t printingCursor = {0,0};

typedef struct command_t
{
	char* name; //el string que tiene que leer del prompt
	uint8_t runnable;
	void (*programFunction) (uint8_t argc, void** argv); //a quien tiene que llamar
	uint8_t argc;
	void** argv;
}command_t;

static command_t commands[COMMAND_COUNT] = {
{.name="help", .runnable = 0, .programFunction = help, .argc = 0, .argv = NULL}, 
{.name="inforeg", .runnable = 0, .programFunction = printRegisters, .argc = 0, .argv = NULL},
{.name="time", .runnable = 0, .programFunction = time, .argc = 0, .argv = NULL}, 
{.name="fibonacci", .runnable = 1, .programFunction = fibonacci, .argc = 0, .argv = NULL},
{.name="prime", .runnable = 1, .programFunction = prime, .argc = 0, .argv = NULL},
{.name="clear", .runnable = 0, .programFunction = clear, .argc = 0, .argv = NULL},
{.name="prueba", .runnable = 2, .programFunction = NULL, .argc = 0, .argv = NULL}
};

static color_t colorValues[COLOROPTIONS] = {L_GRAY, BLACK, MAGENTA};
static const unsigned char * colors[COLOROPTIONS] = {(const unsigned char *)"letter",(const unsigned char *) "background",(const unsigned char *)"user"};
    


void bizcocho(uint8_t argc, void** argv)
{
    
    unsigned char promptBuffer[BUFFER_DIM]={0};
    
    sys_clear_screen(BLACK);
    
    //set cursor al inicio de todo
    while(1){	//esta 2da opcion es por si el programa no tiene un newline al final
   	 if(printingCursor.row >= HEIGHT || (printingCursor.row == HEIGHT-1 && printingCursor.column > 0))
        {	sys_set_cursor(&printingCursor);
			sys_move_cursor(-1,0);
			sys_get_cursor(&printingCursor);
        	sys_scroll_up(1);
        }
     
        sys_set_cursor(&promptCursor);	//Reseteamos la linea del prompt
       
       	sys_new_line(colorValues[1]);
       	
        sys_set_cursor(&promptCursor);
        
        setColor(colorValues[1],colorValues[2]);
        printString((unsigned char*)"Usuario N1 ");
        putChar(2); 
        putChar(' '); 
        putChar(16); //para el chirimbolito
        
        setColor(colorValues[1],colorValues[0]);

        unsigned char key;
        int counter = 0; //cuantas letras van en este mensaje
        uint8_t pipe = 0;

        do{ //repite hasta un enter o que hayan BUFFER_DIM letras
            sys_read_printables(&key, 1); //leemos la letra y la dejamos en key
            if(key!='\n') //si es un enter, no printeamos nada y va a salir del while
            {
            	if(key!='\b')
            	{ //si no es un backspace
                if(key=='|'){
                    pipe=1;
                }
		        promptBuffer[counter++] = key; //la ponemos en el promptBuffer
		        putChar(key); // printeamos la key, porq sino no va a aparecer hasta que apretemos enter
            	}
            	else if(counter>0)
            	{ //si se apreto backspace y no habia nada para borrar no hace nada
		        promptBuffer[--counter] ='\0'; //borramos del buffer
		       
		        point_t point;
		        
		        sys_move_cursor(0,-1);	//se mueve uno para atras para borrarlo
		        
		        //y printeamos un vacio
		        putChar(' ');
		        
		        sys_move_cursor(0,-1);	//se mueve uno para atras para reemplazar lo que se borro
            	}
            }
            
        } while(key!='\n' && counter < BUFFER_DIM);
        
        promptBuffer[counter] = '\0';
        
        addMessage(promptBuffer);
        
        char* progs[2];
        int index[2]={0,0};
        unsigned char foundFlag=0; //si reconocio algun comando

        if(!pipe){
            for(index[0]=0; index[0]<COMMAND_COUNT && !foundFlag ; index++)
            {
                if(strCmp(promptBuffer, commands[index].name)==0)
                {
                    foundFlag++;
                }
            }
        }else{
            // tokenización en dos strings del promptBuffer
            char* progs[2];
            int problem=0; // no encontro nada
            for(int i =0; i<2 && !problem;i++){
                foundFlag=0;
                for(index[i]=0;index[i]<COMMAND_COUNT && !foundFlag ; index[i]++){
                    if(strCmp(progs[0], commands[index[i]].name)==0)
                    {
                        foundFlag++;
                    }
                }
                if(!foundFlag){
                    problem=1;
                }
            }
            index[1]--;
        }
        index[0]--; //asi commands[index] tiene lo que queremos ejecutar si foundFlag quedó = 1
        
        int colorChange=0;
        
        if(!foundFlag && !pipe){ // No hace falta preguntar !problem
            colorChange= changeColor(promptBuffer, colors, colorValues);
        }
        


        if(foundFlag) // No hace falta preguntar !problem, porque si problem=1, foundFlag==0
        {
            sys_set_cursor(&printingCursor);
            
            int bizcochoId = sys_get_task_id();
            
            if(!pipe){
                if(commands[index[0]].runnable) 
                {
                    functionPointer_t function = {commands[index[0]].programFunction};
                    void* args[3] = {&function, &(commands[index[0]].argc), &(commands[index[0]].argv)};
                    sys_add_task_with_shared_screen(runner, bizcochoId, 0, 3, &args);
                }
                else
                {
            	    sys_add_task_with_shared_screen(commands[index[0]].programFunction, bizcochoId, 0, 0, NULL);
                }
            }
            else{
                functionPointer_t function1 = {commands[index[0]].programFunction};
                functionPointer_t function2 = {commands[index[1]].programFunction};
                void* args[6] = {&function1, &(commands[index[0]].argc), &(commands[index[0]].argv), &function2, &(commands[index[1]].argc), &(commands[index[1]].argv)};
                sys_add_task_with_shared_screen(runner, bizcochoId, 0, 6, &args);
            }

/*
            if(commands[index[0]].runnable==2)	//borrar esta primera condicion
            {				///PRUEBA DEL PIPE escribirndo "prueba"
            	functionPointer_t function1 = {commands[3].programFunction};
            	functionPointer_t function2 = {commands[4].programFunction};
            	void* args[6] = {&function1, &(commands[3].argc), &(commands[3].argv), &function2, &(commands[4].argc), &(commands[4].argv)};
            	sys_add_task_with_shared_screen(runner, bizcochoId, 0, 6, &args);
            }
            else if(commands[index[0]].runnable) //borrar el "else" del "else if"
            {
            	functionPointer_t function = {commands[index[0]].programFunction};
            	void* args[3] = {&function, &(commands[index[0]].argc), &(commands[index[0]].argv)};
            	sys_add_task_with_shared_screen(runner, bizcochoId, 0, 3, &args);
            }
            else
            {
            	sys_add_task_with_shared_screen(commands[index[0]].programFunction, bizcochoId, 0, 0, NULL);
            }
*/         
            sys_deactivate_task(bizcochoId);
            
            sys_get_cursor(&printingCursor);
        }
        else
        {
            if(!colorChange)
                addMessage("Hey! That's not a valid command!");
            else{
                addMessage("Color changed!");
            }
        }
        
        for(int i=0; i<counter; i++)	 //limpia el buffer, ni hace falta en realidad
        {
            promptBuffer[i]='\0';
        }
        
    }
}


void addMessage(const char * message) //sería mejor que reciba los colores por parámetro
{
    sys_set_cursor(&printingCursor);
    printStringColor(message, colorValues[1], colorValues[0]);
    sys_new_line(colorValues[1]);
    sys_get_cursor(&printingCursor);
}


int changeColor(const unsigned char * buffer, const unsigned char * colors[], color_t colorValues[]){
    for(int i=0; i<COLOROPTIONS;i++)
    {
        if(strPrefix(colors[i],buffer))
        {
            unsigned char aux=0x00;
            if((aux=strToNum(buffer+strLength(colors[i])+1))<15 && aux>=0)
            {
                colorValues[i] = aux;
                return 1;
            }
            else
            {
            	return 0;
            }
        }
    }
    if(strCmp(buffer,"boca")==0){
        colorValues[0]=14;
        colorValues[1]=1;
        return 1;
    }
    return 0;
}
