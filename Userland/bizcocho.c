
#define LASTCOLUMN 80
#define LASTLINE 25
#define CANTPROGRAMAS 10
#define COLOROPTIONS

int addMessage(signed char x, signed char y, char*message, unsigned char screen[][80]);
void changeColor(const char * buffer, const char * colors[], unsigned char colorValues[]);
int strToNum(const char* str);
char strLength(const char * str);
char strPrefix(const char*prefix, const char*str);

int bizcocho(){
    //Podemos usar un solo puntero y hacer %80 y %25 para acceder a la matriz
    static unsigned char screen[25][80];
    static unsigned char column=0;
    static unsigned char line=24;
    static unsigned char colorValues[COLOROPTIONS] = {0x02,0x00,0x04};
    static char * colors[COLOROPTIONS] = {"letter", "background","user"};
    unsigned char buffer[50]={0};
    //set cursor al inicio de todo
    while(1){

        //print("UsuarioN1: ~ ",color,color);
        column += addMessage(line,0,"Usuario N1: ~ ",screen);
        
        //Se puede eficientizar un poco, pero no conviene porque quizás hay cosas escritas arriba
        for(int i=0; i<LASTLINE;i++){
            for(int j=0; j<LASTCOLUMN;j++){ //podemos fijarnos si es distinto de 0 el elemento del vector y cambiar los colores si lo es
                                            // si es 0, habria que imprimir en negro sobre negro
                //printKey(screen[i][j],color1,color2);
            }
        }
        
        unsigned char key;
        int counter =0;
    
        do{
            //key=getLastKey();
            if(key!='\b'){
                buffer[counter++] = key;
                //printChar(key,color,color); Hay que poner también dónde queremos que lo imprime con line y column
                screen[line][column++]=key;
            }else if(counter>0){
                buffer[counter-1] ='\0';
                //cambiar el puntero a uno con un x menos
                //printChar(algo,black,black);
                screen[line][--column] = '\0';
            }
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
        if(!foundFlag){
            changeColor(buffer, colors, colorValues);
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
    //la programación defensiva sirve!
    int i;
    for(i=0; message[i];i++,y++){
        screen[x][y] = message[i];
        x=(y>=80)? x+1:x;
        y=y%80;
    }
    return i; // Para saber cuánto se movió hacia la derecha
}


void changeColor(const char * buffer, const char * colors[], unsigned char colorValues[]){
    int found=0;
    for(int i=0; i<COLOROPTIONS && !found;i++){
        if(strPrefix(colors[i],buffer)){
            found=1;
            unsigned char aux=0x00;
            if((aux=strToNum(buffer+strLength(colors[i])+1))<15 && aux>=0){
                colorValues[i] = aux;
            }
        }
    }
}

int strToNum(const char* str){
    int i = 0;
    int neg = 0;
    if(str[i]=='-'){
         neg=1;
         i++;
    }
    int ans = 0;
    for(;str[i]!='\0';i++){
        if(str[i]<'0' || str[i]>'9'){
            return -1;
        }
        ans = ans*10 + (str[i]-'0');
    }
    if(neg) ans*=-1;
    return ans;
}

char strLength(const char * str){
    int i=0;
    while(str[i++]);
    return i;
}

char strPrefix(const char*prefix, const char*str){
    int i;
    for(i=0;prefix[i] && str[i];i++){
        if(prefix[i]!=str[i]){
            return 0;
        }
    }
    return !prefix[i];
}
