#include <stdio.h>

int main(){
	unsigned char c =0;
	int i;
	for(i =0; i < 300; i++)
		printf("%uc\n",c-- );
	return 0;
	
}
