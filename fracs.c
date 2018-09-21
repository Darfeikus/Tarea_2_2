#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[])
{
	int x;
	scanf("%d",&x);
	printf("%d\n",x);
	printf("%d\n",x);
	printf("%d\n",x);	
	printf("%d\n",x);
	srand(time(NULL));
	for (int i = 0; i < x*x*2; ++i){
		int num = rand() % 101;
		int den = rand() % 101;
		printf("%d\n%d\n",num,den);
	}
	return 0;
}