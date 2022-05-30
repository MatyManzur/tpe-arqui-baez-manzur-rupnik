#include <bizcocho.h>

#define LASTCOLUMN 80
#define LASTLINE 25
#define COMMAND_COUNT 10
#define COLOROPTIONS 3

#define BUFFER_DIM 50

#define WIDTH 80
#define HEIGHT 25

void printMonkey();
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
{.name="divZero", .runnable = 0, .programFunction = divZero, .argc = 0, .argv = NULL}, 
{.name="invalidOpcode", .runnable = 0, .programFunction = invalidOpcode, .argc = 0, .argv = NULL},
{.name="printmem", .runnable = 0, .programFunction = printmem, .argc = 1, .argv = NULL}
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
        
        char* progForPipe;
        
        
        int colorChange=0;
        int index[2]={0,0};
        
        int argvFlag[2]={0,0};
        void* argv1[1] = {NULL}; 
        char arg1[18];
        char** arg1Pointer= arg1;
        void* argv2[1] = {NULL};
        char arg2[18];
        char** arg2Pointer=arg2;
        
        int monkey=0;

        unsigned char foundFlag=0; //si reconocio algun comando
		char tokensPipe[4][30];
		char tokens[4][30];
		int tokenCount=parser(promptBuffer,tokensPipe,'|');
		if(tokenCount==1){
			tokenCount=parser(tokensPipe[0],tokens,' ');
			if(tokenCount==1){
				for(index[0]=0;index[0]<COMMAND_COUNT && !foundFlag; index[0]++){
				if(strCmp(tokens[0], commands[index[0]].name)==0)
            	{
                	foundFlag++;
           		}
				}
			}
			if(tokenCount==2){
				if(strCmp(tokens[0],"printmem")==0){
					foundFlag=1;
					strCopy(tokens[1],arg1);
					argv1[0] = &arg1; 
					argvFlag[0]=1;
				}else{
					colorChange=changeColor(promptBuffer, colors, colorValues);	
				}		
			}else if(!strCmp(tokens[0],"monkey")){
                monkey++;
                printMonkey();
            }
		}else if(tokenCount==2){
			tokenCount=parser(tokensPipe[0],tokens,' ');
			if(tokenCount==1){
				for(index[0]=0;index[0]<COMMAND_COUNT && !foundFlag; index[0]++){
					if(strCmp(tokens[0], commands[index[0]].name)==0)
            		{
                		foundFlag++;
           			}
				}
			}
			if(tokenCount==2 && strCmp(tokens[0],"printmem")==0){
					foundFlag=1;
					strCopy(tokens[1],arg1);
						argv1[0] = &arg1; 
					argvFlag[0]=1;

			}
			if(foundFlag){
				foundFlag=0;
				tokenCount=parser(tokensPipe[1],tokens,' ');
				if(tokenCount==1){
					for(index[1]=0;index[1]<COMMAND_COUNT && !foundFlag; index[1]++){
						if(strCmp(tokens[0], commands[index[1]].name)==0)
            			{
                			foundFlag++;
                			pipe=1;
           				}
           			}
           		}
           		if(tokenCount==2 && strCmp(tokens[0],"printmem")==0){
           			foundFlag=1;
					strCopy(tokens[1],arg2);
						argv2[0] = &arg2; 
					argvFlag[1]=1;
           		}
           		
			}
			
			
		}
		index[1]--;
        index[0]--; 
         
        //hacer que funcione el monkey
	/*
        // se tiene que poder mejorar para no estar recorriendo el promptBuffer 2 veces
        
        for(int i=0; promptBuffer[i];i++){
            if(promptBuffer[i]=='|'){
                progForPipe = promptBuffer+i+1;
                pipe=1;
                promptBuffer[i--]='\0'; // Para poder comparar con el anterior
            }
        }

        for(index[0]=0; index[0]<COMMAND_COUNT && !foundFlag ; index[0]++)
        {
            if(strCmp(promptBuffer, commands[index[0]].name)==0)
            {
                foundFlag++;
            }
        }

        if(pipe){
            foundFlag=0;
            for(index[1]=0;index[1]<COMMAND_COUNT && !foundFlag; index[1]++){
                if(strCmp(progForPipe, commands[index[1]].name)==0)
                {
                    foundFlag++;
                }
            }
        }

        index[1]--;
        index[0]--; //asi commands[index] tiene lo que queremos ejecutar si foundFlag quedó = 1
        
        int colorChange=0;
        int monkey=0;
        
        if(!foundFlag && !pipe){ // No hace falta preguntar !problem
            colorChange= changeColor(promptBuffer, colors, colorValues);
            if(!colorChange && strCmp(promptBuffer,"monkey")==0){
                printMonkey();
                monkey=1;
            }
        }
        */
        
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
            	    sys_add_task_with_shared_screen(commands[index[0]].programFunction, bizcochoId, 0, commands[index[0]].argc,&argv1);
                }
            }
            else{
                functionPointer_t function1 = {commands[index[0]].programFunction};
                functionPointer_t function2 = {commands[index[1]].programFunction};
                void* args[6] = {&function1, &(commands[index[0]].argc), &(commands[index[0]].argv), &function2, &(commands[index[1]].argc), &(commands[index[1]].argv)};
                if(argvFlag[0]){
                    args[2] = &argv1;
                }// eso es un detalle
                if(argvFlag[1]){
                    args[5] = &argv2;
                }
                
                sys_add_task_with_shared_screen(runner, bizcochoId, 0, 6, &args);
            }
                 
            sys_deactivate_task(bizcochoId);
            
            sys_get_cursor(&printingCursor);
        }
        else
        {
            if(!colorChange && !monkey)
                addMessage("Hey! That's not a valid command!");
            else if(colorChange){
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
            if((aux=strToNum(buffer+strLength(colors[i])+1))<=15 && aux>=0)
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
    if(strCmp(buffer,"boquita")==0){
        colorValues[0]=14;
        colorValues[1]=1;
        return 1;
    }else if(strCmp(buffer,"river")==0){
        colorValues[0]=15;
        colorValues[1]=5;
        return 1;
    }
    return 0;
}

//https://www.asciiart.eu/animals/monkeys
void printMonkey(){
    sys_set_cursor(&printingCursor);
    printStringColor("       .-\"-.            .-\"-.            .-\"-.           .-\"-.",GREEN,YELLOW);
    sys_new_line(GREEN);
    printStringColor("     _/_-.-_\\_        _/.-.-.\\_        _/.-.-.\\_       _/.-.-.\\_",GREEN,YELLOW);
    sys_new_line(GREEN);
    printStringColor("    / __} {__ \\      /|( o o )|\\      ( ( o o ) )     ( ( o o ) )",GREEN,YELLOW);  
    sys_new_line(GREEN);
    printStringColor("   / //  \"  \\ \\     | //  \"  \\ |       |/  \"  \\|       |/  \"  \\|",GREEN,YELLOW);  
    sys_new_line(GREEN); 
    printStringColor("  / / \\'---'/ \\ \\  / / \\'---'/ \\ \\      \\'/^\\'/         \\ .-. /",GREEN,YELLOW);  
    sys_new_line(GREEN); 
    printStringColor("  \\ \\_/`\"\"\"`\\_/ /  \\ \\_/`\"\"\"`\\_/ /      /`\\ /`\\         /`\"\"\"`\\",GREEN,YELLOW);
    sys_new_line(GREEN); 
    printStringColor("   \\           /    \\           /      /  /|\\  \\       /       \\",GREEN,YELLOW);
    sys_new_line(GREEN); 
    printStringColor("-={ see no evil }={ hear no evil }={ speak no evil }={ have no fun }=-",GREEN,YELLOW);
    sys_new_line(GREEN); 
    sys_get_cursor(&printingCursor);
}
