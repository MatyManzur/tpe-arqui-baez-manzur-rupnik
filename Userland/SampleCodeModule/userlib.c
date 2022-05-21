#include <userlib.h>

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

void printNormal(char * str){
    sys_write(str,strLength(str)); //Podríamos hacer un for para no recorrer dos veces
}

int putChar(char c){
    return sys_write(&c,1);
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
                        printNormal(convert(i,10));
                        break; 

            case 'o': i = va_arg(arg,unsigned int); //Fetch Octal representation
                        printNormal(convert(i,8));
                        break; 

            case 's': s = va_arg(arg,char *);       //Fetch string
                        printNormal(s); 
                        break; 

            case 'x': i = va_arg(arg,unsigned int); //Fetch Hexadecimal representation
                        printNormal(convert(i,16));
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
