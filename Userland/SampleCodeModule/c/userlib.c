#include <userlib.h>

static struct format_t format = { BLACK, L_GRAY };  // el formato que se utiliza para los colores

int strToNum(const unsigned char* str)
{ //Pasa un string a decimal
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

char strLength(const unsigned char * str)
{  // strlength
    int i=0;
    while(str[i]){
        i++;
    }
    return i;
}

char strPrefix(const unsigned char*prefix, const unsigned char*str)
{    // se fija si el primer string está como prefijo del segundo
    int i;
    for(i=0;prefix[i] && str[i];i++){
        if(prefix[i]!=str[i]){
            return 0;
        }
    }
    return !prefix[i];
}

int strCmp(const unsigned char* str1,const unsigned char* str2)
{    // compara strings, devuelve la diferencia entre el primero en el que difiere
	while(*str1 != 0 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1) - (*str2);
}

void setColor(color_t backgroundColor, color_t characterColor)  // cambia el format para que se empiece a imprimir con estos colores
{
	format.backgroundColor = backgroundColor;
	format.characterColor = characterColor;
}

void printString(unsigned char * str)   //imprime un string, si pisa una zona en la que no puede escribir, hace un scroll up
{                                       // utiliza el color del format
    unsigned char* overload=NULL;
    overload=sys_print(str, &format);
    if(overload!=NULL){
        sys_scroll_up(2);
        sys_move_cursor(-2,0);
        printString(overload);
    }
}

void putChar(unsigned char c)   //idem anterior, pero con un char
{
    int overload=0;
	overload=sys_print_char(c, &format);
    if(overload){
        sys_scroll_up(2);
        sys_move_cursor(-2,0);
        putChar(c);
    }
}

void printStringColor(unsigned char * str, color_t backgroundColor, color_t characterColor) //idem printString, pero se le pasa el color
{
    struct format_t format = {.backgroundColor = backgroundColor % 16, .characterColor = characterColor % 16};
    unsigned char* overload=NULL;
    overload=sys_print(str, &format);
    if(overload!=NULL){
        sys_scroll_up(2);
        sys_move_cursor(-2,0);
        printStringColor(overload,backgroundColor,characterColor);
    }
}

void putCharColor(unsigned char c, color_t backgroundColor, color_t characterColor) // idem anterior, pero para chars
{
    struct format_t format = {.backgroundColor = backgroundColor % 16, .characterColor = characterColor % 16};
    int overload=0;
	overload=sys_print_char(c, &format);
    if(overload){
        sys_scroll_up(2);
        sys_move_cursor(-2,0);
        putCharColor(c, backgroundColor, characterColor);
    }
}     

// código sacado de:
// https://stackoverflow.com/questions/1735236/how-to-write-my-own-printf-in-c 
void printWithFormat(char* format,...) 
{ 
    char *traverse; 
    unsigned int i; 
    char *s; 

    //Initializing arguments 
    va_list arg; 
    va_start(arg, format); 

    for(traverse = format; *traverse != '\0'; traverse++) 
    { 
        while( *traverse != '%' ) 
        { 
            putChar(*traverse);
            traverse++; 
        } 

        traverse++; 

        //Fetching and executing arguments
        switch(*traverse) 
        { 
            case 'c' : i = va_arg(arg,int);     //Fetch char argument
                        putChar(i);
                        break; 

            case 'd' : i = va_arg(arg,int);         //Fetch Decimal/Integer argument
                        if(i<0) 
                        { 
                            i = -i;
                            putChar('-'); 
                        } 
                        printString(convert(i,10));
                        break; 

            case 'o': i = va_arg(arg,unsigned int); //Fetch Octal representation
                        printString(convert(i,8));
                        break; 

            case 's': s = va_arg(arg,char *);       //Fetch string
                        printString(s); 
                        break; 

            case 'x': i = va_arg(arg,unsigned int); //Fetch Hexadecimal representation
                        printString(convert(i,16));
                        break; 
        }   
    } 

    //Closing argument list to necessary clean-up
    va_end(arg); 
} 

char *convert(unsigned int num, int base) 
{ 
    static char Representation[]= "0123456789ABCDEF";
    static char buffer[50]; 
    char *ptr; 

    ptr = &buffer[49]; 
    *ptr = '\0'; 

    do 
    { 
        *--ptr = Representation[num%base]; 
        num /= base; 
    }while(num != 0); 

    return(ptr); 
}

uint8_t ulongToStr(unsigned long num, char* ans)
{   // pasa un numero entero a string
    char aux[20]; //un long puede ocupar hasta 10 caracteres (sin contar - o \0)
    //podria usar numLength pero asi esta bien
    int i = 0; //puntero de ans
    int k = 0;
    while(num){
        aux[k++] = (num%10)+'0';
        num/=10;
    }
    k--; //para que apunte al ultimo numero desde donde tiene que copiar
    while(k>=0){
        ans[i++] = aux[k--];
    }
    ans[i] = '\0';
    return i;
}
///codigo sacado de:
//https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Reciprocal_of_the_square_root
int sqrt(int x)
{
	float xhalf = 0.5f * x;
    union {
        float x;
        int i;
    } u;
    u.x = x;
    u.i = 0x5f375a86 - (u.i >> 1);
    /* The next line can be repeated any number of times to increase accuracy */
    u.x = u.x * (1.5f - xhalf * u.x * u.x);
    return ((int)(u.x * x))+2;//Esto es para conseguir la raiz ademas SSE esta deshabilitado entonces truncamos y sumamos uno
}

int parser(char string[], char buffer[][30],char separator){//Se le pasa un string, un buffer donde dejara los tokens y el char separador de tokens
	int count=0;
	int j=0;
	for(int i=0;string[i]!='\0';i++){
		if(string[i]==separator) {
            if ( j != 0){
                buffer[count++][j] = '\0';
                j = 0;
            }
        }else{
			buffer[count][j++]=string[i];
		}
	}
	if(j!=0){
        buffer[count++][j]='\0';
    }
	return count;
}
//base del codigo sacado de https://stackoverflow.com/questions/10156409/convert-hex-string-char-to-int

uint64_t xtou64(const char *str)
{
    uint64_t res = 0;
    char c;

    while ((c = *str++)) {
        char v = (c & 0xF) + (c >> 6) | ((c >> 3) & 0x8);
        res = (res << 4) | (uint64_t) v;
    }

    return res;
}

