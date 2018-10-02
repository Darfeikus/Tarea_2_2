#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct Frac{
	int num,den;
};

void simplify(struct Frac *indFrac){
	if (indFrac->den<0){
		indFrac->den*=-1;
		indFrac->num*=-1;
	}
	int x = abs(indFrac->num) < abs(indFrac->den) ? indFrac->num : indFrac->den;
	for (int i = abs(x); i > 1; --i)
		if(indFrac->num % i == 0 && indFrac->den % i == 0 ){
			indFrac->num /= i;
			indFrac->den /= i;
			i=1;
		}
	}

	void printFrac(struct Frac *indFrac,int *max){
		printf("|%*d/%*d|",*max+1,indFrac->num,*max+1,indFrac->den);
	}

	int length(int x){
		if (x!=0)
			return floor(log10(abs(x))) + 1;
		return 1;
	}

	int lengthFr(struct Frac *indFrac){
		return length(indFrac->num) > length(indFrac->den) ? length(indFrac->num):length(indFrac->den);
	}

	void printMatrix(struct Frac *indFrac, int r,int c, int *max){
		printf("\n");
		for (int i = 0; i < r*c; i++){
			printFrac(indFrac, max);
			if((i+1)%c==0)
				printf("\n\n");
			indFrac++;
		}
		printf("\n");
	}

	struct Frac * mult(struct Frac *f1,struct Frac *f2){
		struct Frac *res = (struct Frac*)malloc(sizeof(struct Frac));
		res->num= f1->num * f2->num;
		res->den= f1->den * f2->den;
		simplify(res);
		return res;
	}

	struct Frac * sum(struct Frac* f1,struct Frac* f2){
		struct Frac *res = (struct Frac*)malloc(sizeof(struct Frac));
		res->num=(f2->den * f1->num) + (f1->den * f2->num);
		res->den=f1->den * f2->den;
		simplify(res);	
		return res;
	}

	void fillMatrix(struct Frac *indFrac,int r,int c,int *maxLength){
		for (int i = 0; i < r*c; ++i){
			printf("Input fraction %d of the first matrix\n", i+1);
			scanf("%d%d",&indFrac->num,&indFrac->den);
			if (indFrac->den == 0){
				printf("Invalid Fraction\n");
				i=r*c;
				*maxLength=-1;
			}
			simplify(indFrac);
			*maxLength = *maxLength > lengthFr(indFrac) ? *maxLength:lengthFr(indFrac);
			indFrac++;
		}
	}

	void multMatrix(struct Frac *indFrac,struct Frac *indFrac2,struct Frac *indRes,int fr,int fc,int sr,int sc,struct Frac *base1,struct Frac *base2,int *maxLength){
		int c=0;
		indFrac = base1;
		indFrac2 = base2;
		for (int i = 0; i < fr*sc;i++){
			indRes->num=0;
			indRes->den=1;
			for (int i = 0; i < fc; i++){
				*indRes=*sum(mult(indFrac,indFrac2),indRes);
				indFrac++;
				indFrac2+=sc;
			}
			c++;
			*maxLength = *maxLength > lengthFr(indRes) ? *maxLength:lengthFr(indRes);
			indFrac2=base2+c;
			indFrac-=fc;
			if(c==sc){
				indFrac += fc;
				indFrac2=base2;
				c=0;
			}
			indRes++;
		}
	}

	int main(){
		int fr,fc,sr,sc,maxl;
		int *max = &maxl;
		printf("Write number of rows of the first matrix\n");
		scanf("%d",&fr);
		printf("Write number of columns of the first matrix\n");
		scanf("%d",&fc);
		printf("Write number of rows of the second matrix\n");
		scanf("%d",&sr);
		printf("Write number of columns of the second matrix\n");
		scanf("%d",&sc);

		if(fc!=sr){
			printf("The operation is impossible\n");
			return -1;
		}

		struct Frac *indRes = (struct Frac*)malloc(sizeof(struct Frac) * (fr*sc));
		struct Frac *indFrac = (struct Frac*)malloc(sizeof(struct Frac) * (fr*fc));
		struct Frac *indFrac2 = (struct Frac*)malloc(sizeof(struct Frac) * (sr*sc));
		struct Frac *base1 = indFrac;
		struct Frac *base2 = indFrac2;
		struct Frac *base3 = indRes;

		fillMatrix(indFrac,fr,fc,max);
		if(*max==-1)
			return-1;
		fillMatrix(indFrac2,sr,sc,max);
		if(*max==-1)
			return-1;

		multMatrix(indFrac,indFrac2,indRes,fr,fc,sr,sc,base1,base2,max);

		indFrac = base1;
		indRes = base3;
		printMatrix(indFrac,fr,fc,max);
		printf(" X \n\n");
		printMatrix(indFrac2,sr,sc,max);
		printf(" = \n\n");
		printMatrix(indRes,fr,sc,max);
	}