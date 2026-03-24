#include <stdio.h>
define int long long

int main(){
	int n;
	int max,min;
	scanf("%lld",&n);
	int nums[n];
	for(int i = 0 ; i < n ;i++){
		if(i == 0){
		  max = nums[i];
		  min = nums[i];
		}
		if(nums[i] > max)
			max = nums[i]
		if(nums[i] < min)
			min = nums[i]
	}
	printf("%lld",max-min);
	return 0;

}
