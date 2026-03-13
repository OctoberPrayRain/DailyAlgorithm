#include <stdio.h>

long long func(long long i){
	if(i >= 1 ){
	   return  i * func( i - 1);
	}else if(i == 0){
	   return 1;
	}
}

int main(){
	long long i;
	scanf("%lld",&i);
	printf("%lld",func(i));
	return 0;
}
