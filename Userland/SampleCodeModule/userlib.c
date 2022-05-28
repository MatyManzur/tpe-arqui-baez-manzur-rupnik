#include <userlib.h>


static struct format_t format = { BLACK, L_GRAY };

int strToNum(const unsigned char* str){
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

char strLength(const unsigned char * str){
    int i=0;
    while(str[i++]);
    return i;
}

char strPrefix(const unsigned char*prefix, const unsigned char*str){
    int i;
    for(i=0;prefix[i] && str[i];i++){
        if(prefix[i]!=str[i]){
            return 0;
        }
    }
    return !prefix[i];
}

int strCmp(const unsigned char* str1,const unsigned char* str2){
	while(*str1 != 0 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1) - (*str2);
}

void setColor(color_t backgroundColor, color_t characterColor)
{
	format.backgroundColor = backgroundColor;
	format.characterColor = characterColor;
}

void printString(unsigned char * str)
{
    unsigned char* overload=NULL;
    overload=sys_print(str, &format);
    if(overload!=NULL){
        sys_scroll_up(2);
        sys_move_cursor(-2,0);
        printString(overload);
    }
}

void putChar(unsigned char c)
{
    int overload=0;
	overload=sys_print_char(c, &format);
    if(overload){
        sys_scroll_up(1);
        sys_move_cursor(-1,0);
        putChar(c);
    }
}

void printStringColor(unsigned char * str, color_t backgroundColor, color_t characterColor)
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

void putCharColor(unsigned char c, color_t backgroundColor, color_t characterColor)
{
    struct format_t format = {.backgroundColor = backgroundColor % 16, .characterColor = characterColor % 16};
    sys_print_char(c, &format);
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
