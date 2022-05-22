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

void bizcocho(){
    //Podemos usar un solo puntero y hacer %80 y %25 para acceder a la matriz
    //static unsigned char screen[HEIGHT][WIDTH]; No hace falta
    static unsigned char column=0;
    static unsigned char line=0;
    static unsigned char printColumn=0;
    static unsigned char printRow=0;
    
    /* COLORES
    static color_t colorValues[COLOROPTIONS] = {L_GRAY, BLACK, MAGENTA};
    static const unsigned char * colors[COLOROPTIONS] = {(const unsigned char *)"letter",(const unsigned char *) "background",(const unsigned char *)"user"};
    */
    
    unsigned char readingBuffer[BUFFER_DIM]={0};
    //set cursor al inicio de todo
    while(1){
    
        //column += addMessage(line,0,"Usuario N1: ~ ",screen);
        
        //REFRESCO DE TODA LA PANTALLA
        struct point_t cursor = {HEIGHT-1, 0}; //Imprimimos abajo
        
        sys_set_cursor(&cursor);
        
        for(int i = 0; i<80;i++){
            putChar(' '); // esto va a dejarlo todo con el color de la letra en lugar del color del background :/
        }

        sys_set_cursor(&cursor);
        printStringColor("Usuario N1: ~> ", BLACK, MAGENTA);
        

        //Se puede eficientizar un poco, pero no conviene porque quizás hay cosas escritas arriba
      /*  for(int i=0; i<LASTLINE;i++){
            for(int j=0; j<LASTCOLUMN;j++){ //podemos fijarnos si es distinto de 0 el elemento del vector y cambiar los colores si lo es
                                            // si es 0, habria que imprimir en negro sobre negro
                putChar(screen[i][j]);
            }
        }
        */
        
        /*
        cursor = (struct point_t){line, column};
        
        sys_set_cursor(&cursor);
        */

        unsigned char key;
        int counter = 0; //cuantas letras van en este mensaje
    
        do{ //repite hasta un enter o que hayan BUFFER_DIM letras
            sys_read_printables(&key, 1); //leemos la letra y la dejamos en key
            if(key!='\b'){ //si no es un backspace
                readingBuffer[counter++] = key; //la ponemos en el readingBuffer
                putChar(key); // printeamos la key, porq sino no va a aparecer hasta que apretemos enter
             //   screen[line][column++]=key; //la ponemos en la pantalla para que despues lo levante dos rengloones
            }else if(counter>0){ //si se apreto backspace y no habia nada para borrar no hace nada
                readingBuffer[--counter] ='\0'; //borramos del buffer
                //atrasamos uno el cursor
                point_t point; //Esto es un asco, habría que reemplazar por sys_reduce_cursor_by_one();
                sys_get_cursor(&point);
                point.column--;
                sys_set_cursor(&point);
                //y printeamos un vacio
                putChar(' ');
                //screen[line][--column] = '\0'; //lo borramos para que no aparezca despues
            }
        } while(key!='\n' && counter < BUFFER_DIM);  
        

        readingBuffer[counter-1]='\0'; //borramos el \n que nos quedo al final
        
        
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

        column = 0;
        
        printStringColor("Usuario N1: ~> ", BLACK, MAGENTA);
        printString(readingBuffer);

        point_t point; //Esto es un asco
        sys_get_cursor(&point);
        point.row++;
        sys_set_cursor(&point);

        if(foundFlag){ //printea en la anteultima linea
            //addMessage(line,0,programas[index],screen);
           // printString(programas[index]);
        }else{
            //addMessage(line,0,"Hey! That's not a valid command!",screen);
            printString("Hey! That's not a valid command!");
        }
        
        line++;
        
        for(int i=0; i<counter; i++){ //limpia el buffer
            readingBuffer[i]='\0';
        }
        

        //Esto lo hacemos arriba
        /*for(int j=0 ; j< WIDTH -1 ; j++) //limpia la ultima linea
        {
        	screen[HEIGHT-1][j] = '\0';
        }
        */
        
    }
}


int addMessage(unsigned char x, unsigned char y, const char * message, unsigned char screen[][80]){
    //la programación defensiva sirve!
    int i;
    for(i=0; message[i];i++,y++)
    {
        screen[x][y] = message[i];
        x=(y>=80)? x+1:x;
        y=y%80;
    }
    return i; // Para saber cuánto se movió hacia la derecha
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
