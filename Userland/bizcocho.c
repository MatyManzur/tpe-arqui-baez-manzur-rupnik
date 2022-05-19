
#define LASTCOLUMN 80
#define LASTLINE 25
#define CANTPROGRAMAS 10

int addMessage(signed char x, signed char y, char*message, unsigned char screen[][80]);


int bizcocho(){
    //Podemos usar un solo puntero y hacer %80 y %25 para acceder a la matriz
    static unsigned char screen[25][80];
    static unsigned char column=0;
    static unsigned char line=24;
    unsigned char buffer[50]={0};
    //set cursor al inicio de todo
    while(1){

        //print("UsuarioN1: ~ ",color,color);
        column += addMessage(line++,0,"Usuario N1: ~ ",screen);
        

        for(int i=0; i<LASTLINE;i++){
            for(int j=0; j<LASTCOLUMN;j++){ //podemos fijarnos si es distinto de 0 el elemento del vector y cambiar los colores si lo es
                                            // si es 0, habria que imprimir en negro sobre negro
                //printKey(screen[i][j],color1,color2);
            }
        }
        
        unsigned char key;
        int counter =0;
    
        do{
            //key = getLastKey();
            buffer[counter++] = key;
            //printChar(key,color,color); Hay que poner también dónde queremos que lo imprime con line y column
            screen[line][column++]=key;
        } while(key!='\n' && counter < 50); 
        line--;
        column=0;
        buffer[counter-1]='\0'; //en lugar de la n
        unsigned char foundFlag=0;
        int index;
        for(index=0; i<CANTPROGRAMAS && foundFlag;index++){
    /*      if(strcompare(buffer,programas[index])){
                programsPointers[index](); Algo como esto tiene que ser con punteros a funciones
                foundFlag = foundFlag | 0x01; Joda re al pedo
                foundFlag++;
            }
    */
        }
        for(int i=2; i<LASTLINE;i++){
            for(int j=2; j<LASTCOLUMN;j++){ //podemos fijarnos si es distinto de 0 el elemento del vector y cambiar los colores si lo es
                                            // si es 0, habria que imprimir en negro sobre negro
                screen[i-2][j-2]=screen[i][j];
            }
        }
        if(foundFlag){
            addMessage(line++,0,programas[index],screen);
        }else{
            addMessage(line++,0,"Hey! That's not a valid command!",screen);
        }
        foundFlag=0;
        
        for(int i=0; i<counter; i++){
            buffer[i]='\0';
        }
    }
}


int addMessage(signed char x, signed char y,char * message, unsigned char screen[][80]){
    //la programacion defensiva sirve!
    int i;
    for(i=0; message[i];i++,y++){
        screen[x][y] = message[i];
        x=(y>=80)? x+1:x;
        y=y%80;
    }
    return i; // Para saber cuánto se movió hacia la derecha
}