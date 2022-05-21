#include <bizcocho.h>

#define LASTCOLUMN 80
#define LASTLINE 25
#define CANTPROGRAMAS 10
#define COLOROPTIONS 3

#define BUFFER_DIM 50

int addMessage(unsigned char x, unsigned char y, const char*message, unsigned char screen[][80]);
int changeColor(const unsigned char * buffer, const unsigned char * colors[], color_t colorValues[]);

int bizcocho(){
    //Podemos usar un solo puntero y hacer %80 y %25 para acceder a la matriz
    static unsigned char screen[25][80];
    static unsigned char column=0;
    static unsigned char line=24;
    static color_t colorValues[COLOROPTIONS] = {L_GRAY, BLACK, MAGENTA};
    static const unsigned char * colors[COLOROPTIONS] = {(const unsigned char *)"letter",(const unsigned char *) "background",(const unsigned char *)"user"};
    unsigned char buffer[BUFFER_DIM]={0};
    //set cursor al inicio de todo
    while(1){

        column += addMessage(line,0,"Usuario N1: ~ ",screen);
        
        //Se puede eficientizar un poco, pero no conviene porque quizás hay cosas escritas arriba
        for(int i=0; i<LASTLINE;i++){
            for(int j=0; j<LASTCOLUMN;j++){ //podemos fijarnos si es distinto de 0 el elemento del vector y cambiar los colores si lo es
                                            // si es 0, habria que imprimir en negro sobre negro
                //printKey(screen[i][j],color1,color2);
            }
        }
        
        unsigned char key;
        int counter = 0;
    
        do{
            //sys_read(&key, 1);
            if(key!='\b'){
                buffer[counter++] = key;
                //printChar(key,color,color); Hay que poner también dónde queremos que lo imprime con line y column
                screen[line][column++]=key;
            }else if(counter>0){
                buffer[--counter] ='\0';
                //cambiar el puntero a uno con un x menos
                //printChar(algo,black,black);
                screen[line][--column] = '\0';
            }
        } while(key!='\n' && counter < BUFFER_DIM); 
        line--; //line = 23
        column=0;
        buffer[counter-1]='\0'; //en lugar de la \n
        unsigned char foundFlag=0;
        int index;
        for(index=0; index<CANTPROGRAMAS && foundFlag ; index++){
    /*      if(strcompare(buffer,programas[index])){
                programsPointers[index](); Algo como esto tiene que ser con punteros a funciones
                foundFlag++;
            }
    */
        }
        if(!foundFlag){
            foundFlag = changeColor(buffer, colors, colorValues);
        }
        for(int i=2; i<LASTLINE;i++){
            for(int j=2; j<LASTCOLUMN;j++){ //podemos fijarnos si es distinto de 0 el elemento del vector y cambiar los colores si lo es
                                            // si es 0, habria que imprimir en negro sobre negro
                screen[i-2][j-2]=screen[i][j];
            }
        }
        if(foundFlag){
           // addMessage(line++,0,programas[index],screen); //lo agrego en la 23
        }else{
            addMessage(line++,0,"Hey! That's not a valid command!",screen);
        } //line = 24
        
        for(int i=0; i<counter; i++){
            buffer[i]='\0';
        }
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
