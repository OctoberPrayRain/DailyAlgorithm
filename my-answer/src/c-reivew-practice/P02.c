#include <stdio.h>
#include <string.h>

int main(){
    int count = 0; //count the number's appearance time.
    char str[1000];
    if(fgets(str,sizeof(str),stdin) != NULL){
        size_t len = strlen(str);
        for(int i = 0 ; i < len ; i++){
            if(str[i]<= '9' && str[i] >= '0')
                count++;
        }
    }
    printf("%d",count);
    return 0;
}