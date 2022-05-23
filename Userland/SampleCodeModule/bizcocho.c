#include <bizcocho.h>

#define LASTCOLUMN 80
#define LASTLINE 25
#define CANTPROGRAMAS 10
#define COLOROPTIONS 3

#define BUFFER_DIM 50

#define WIDTH 80
#define HEIGHT 25

int addMessage(unsigned char x, unsigned char y, const char*message, unsigned char screen[][80]);
int changeColor(const unsigned char * buffer, const unsigned char * colors[], color_t colorValues[]);

void bizcocho()
{
    point_t promptCursor = {HEIGHT-1, 0};
    point_t printingCursor = {0,0};
    unsigned char promptBuffer[BUFFER_DIM]={0};
    
    sys_clear_screen();
    
    /* COLORES
    static color_t colorValues[COLOROPTIONS] = {L_GRAY, BLACK, MAGENTA};
    static const unsigned char * colors[COLOROPTIONS] = {(const unsigned char *)"letter",(const unsigned char *) "background",(const unsigned char *)"user"};
    */
    
    
    //set cursor al inicio de todo
    while(1){
   
        
        sys_set_cursor(&promptCursor);//Reseteamos la linea del prompt
        
        for(int i = 0; i<WIDTH;i++){
            putChar(' ');
        }

        sys_set_cursor(&promptCursor);
        printStringColor("Usuario N1 >§", BLACK, MAGENTA);

        unsigned char key;
        int counter = 0; //cuantas letras van en este mensaje
    
        do{ //repite hasta un enter o que hayan BUFFER_DIM letras
            sys_read_printables(&key, 1); //leemos la letra y la dejamos en key
            if(key=='\n') //si es un enter, no printeamos nada y va a salir del while
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
		        
		        sys_get_cursor(&point);	//se mueve uno para atras para borrarlo
		        point.column--;
		        sys_set_cursor(&point);
		        
		        //y printeamos un vacio
		        putChar(' ');
		        
		        
		        sys_get_cursor(&point);	//se mueve uno para atras para reemplazar lo que se borro
		        point.column--;
		        sys_set_cursor(&point);
            	}
            }
            
        } while(key!='\n' && counter < BUFFER_DIM);  
        
        
        unsigned char foundFlag=0; //si reconocio algun comando
        int index;
        for(index=0; index<CANTPROGRAMAS && foundFlag ; index++){
    /*      if(strcompare(readingBuffer,programas[index])){
                programsPointers[index](); Algo como esto tiene que ser con punteros a funciones
                foundFlag++;
            }
    */
        }
        
        /* COLORES
        
        if(!foundFlag){ // quizas era para cambiar el color?
            foundFlag = changeColor(readingBuffer, colors, colorValues);
        }
        
        */
        /*
        for(int i=2; i<LASTLINE;i++){ //empieza en 2 porq se pierden las primeras 2 lineas
            for(int j=0; j<LASTCOLUMN;j++){                                          
                screen[i-2][j]=screen[i][j]; //mueve todo 2 para arriba
            }
        }
        */

/*						BORRAR?
        column = 0;
        
        printStringColor("Usuario N1: ~> ", BLACK, MAGENTA);
        printString(readingBuffer);

        point_t point; //Esto es un asco
        sys_get_cursor(&point);
        point.row++;
        sys_set_cursor(&point);
*/


        if(foundFlag)
        {
            
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
    sys_new_line();
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
