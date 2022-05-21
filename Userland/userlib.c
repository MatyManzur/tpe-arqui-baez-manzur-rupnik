
#include <userlib.h>

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
int strCmp(const char* str1,const char* str2){
	int i;
	for(i=0;*str1 && *str1 == *str2;str1++,str2++){
	}
	return *(const unsigned char *)str1-*(const unsignes char*) s2;
}
