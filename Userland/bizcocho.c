
#define LASTCOLUMN 80
#define LASTLINE 25
#define CANTPROGRAMAS 10


int bizcocho(){
    //Podemos usar un solo puntero y hacer %80 y %25 para acceder a la matriz
    static unsigned char screen[25][80];
    static unsigned char column=79;
    static unsigned char line=24;
    unsigned char buffer[50]={0};
    //set cursor al inicio de todo
    for(int i=0; i<LASTLINE;i++){
        for(int j=0; j<LASTCOLUMN;j++){ //podemos fijarnos si es distinto de 0 el elemento del vector y cambiar los colores si lo es
                                        // si es 0, habria que imprimir en negro sobre negro
            //printKey(screen[i][j],color1,color2);
        }
    }
    //set cursor en la fila N 25 y columna N 80
    //print("UsuarioN1: ~ ",color,color);
    unsigned char key;
    int counter =0;
    while(1){
        do{
            //key = getLastKey();
            buffer[counter++] = key;
            //printChar(key,color,color);
        } while(key!='\n' && counter < 50); 
        buffer[counter-1]='\0'; //en lugar de la n
        unsigned char foundFlag=0;
        for(int i=0; i<CANTPROGRAMAS && foundFlag;i++){
    /*      if(strcompare(buffer,programas[i])){
                programsPointers[i](); Algo como esto tiene que ser con punteros a funciones
                foundFlag = foundFlag || 0x01; Joda re al pedo
                foundFlag++;
            }
    */
        }

        if(!foundFlag){
            //newLine() pasamos a la fila de abajo
            //print("Hey! That's not a valid command!");
        }  
        foundFlag=0;
        //newLine()
        //print("UsuarioN1: ~ ",color,color);
        for(int i=0; i<counter; i++){
            buffer[i]='\0';
        }
    }
}