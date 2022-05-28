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
	char* name;
	void (*programFunction) (void);
	uint8_t args;
}command_t;

static command_t commands[COMMAND_COUNT] = {{.name="help", .programFunction = help, .args = 0}, {.name="inforeg", .programFunction = printRegisters, .args = 0}};

void bizcocho()
{
    
    unsigned char promptBuffer[BUFFER_DIM]={0};
    
    sys_clear_screen(BLACK);
    
    /* COLORES
    static color_t colorValues[COLOROPTIONS] = {L_GRAY, BLACK, MAGENTA};
    static const unsigned char * colors[COLOROPTIONS] = {(const unsigned char *)"letter",(const unsigned char *) "background",(const unsigned char *)"user"};
    */
    
    
    //set cursor al inicio de todo
    while(1){				     //esta 2da opcion es por si el programa no tiene un newline al final
   	 if(printingCursor.row >= HEIGHT || (printingCursor.row == HEIGHT-1 && printingCursor.column > 0))
        {	sys_set_cursor(&printingCursor);
			sys_move_cursor(-1,0);
			sys_get_cursor(&printingCursor);
        	sys_scroll_up(1);
        }
     
        sys_set_cursor(&promptCursor);//Reseteamos la linea del prompt
       
       	sys_new_line(BLACK);
       	
        sys_set_cursor(&promptCursor);
        
        setColor(BLACK,MAGENTA);
        printString((unsigned char*)"Usuario N1 ");
        putChar(2); 
        putChar(' '); 
        putChar(16); //para el chirimbolito
        
        setColor(BLACK,L_GRAY);
        
        /*		BORRAR DPS, ES PARA VER LOS ASCIIS Q HAY 
        sys_set_cursor(&printingCursor);
       for(int k=0;k<255;k++)
       {
       	printWithFormat("%d", k);
       	putChar('=');
       	putChar(k);
       	printStringColor(" | ", WHITE, RED);
       }
    	sys_new_line(BLACK);
    	sys_get_cursor(&printingCursor);
    	*/

        unsigned char key;
        int counter = 0; //cuantas letras van en este mensaje
    
        do{ //repite hasta un enter o que hayan BUFFER_DIM letras
            sys_read_printables(&key, 1); //leemos la letra y la dejamos en key
            if(key!='\n') //si es un enter, no printeamos nada y va a salir del while
            {
            	if(key!='\b')
            	{ //si no es un backspace
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
        
        
        unsigned char foundFlag=0; //si reconocio algun comando
        int index;
        for(index=0; index<COMMAND_COUNT && !foundFlag ; index++)
        {
        	if(strCmp(promptBuffer, commands[index].name)==0)
        	{
		        foundFlag++;
            	}
        }
        index--; //asi commands[index] tiene lo que queremos ejecutar si foundFlag quedó = 1
        
        /* COLORES
        
        if(!foundFlag){ // quizas era para cambiar el color?
            foundFlag = changeColor(readingBuffer, colors, colorValues);
        }
        
        */


        if(foundFlag)
        {
            sys_set_cursor(&printingCursor);
            
            int bizcochoId = sys_get_task_id();
            
            sys_add_task_with_shared_screen(commands[index].programFunction, bizcochoId, 0);
            sys_deactivate_task(bizcochoId);
            
            sys_get_cursor(&printingCursor);
        }
        else
        {
            addMessage("Hey! That's not a valid command!");
        }
        
        for(int i=0; i<counter; i++)	 //limpia el buffer
        {
            promptBuffer[i]='\0';
        }
        
    }
}


void addMessage(const char * message)
{
    sys_set_cursor(&printingCursor);
    printStringColor(message, BLACK, L_GRAY);
    sys_new_line(BLACK);
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
    return 0;
}
