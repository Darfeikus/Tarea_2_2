#include <stdio.h>
#include <stdlib.h>

struct Frac{
	int num,den;
};

void simplify(struct Frac *indFrac){
	int x = indFrac -> num > indFrac -> den ? indFrac->num : indFrac->den;
	for (int i = 0; i < x; ++i)
		if(indFrac->num % x == 0 && indFrac->den % x == 0 ){
			indFrac->num /= x;
			indFrac->den /= x;
		}
	/*if (indFrac->den<0){
		indFrac->den*=-1;
		indFrac->num*=-1;
	}
	for (int i = indFrac->den; i > 1; --i)
		if(indFrac->num%i==0 && indFrac->den%i==0){
			indFrac->num/=i;
			indFrac->den/=i;
			i=1;
		}
	for (int i = indFrac->num; i > 1; --i)
		if(indFrac->num%i==0 && indFrac->den%i==0){
			indFrac->num/=i;
			indFrac->den/=i;
			i=1;
		}*/
}

void printFrac(struct Frac *indFrac){
	printf("| %8d / %8d | ",indFrac->num,indFrac->den);
}

void printMatrix(struct Frac *indFrac, int r,int c){
	printf("\n");
	int x=0;
	for (int i = 0; i < r*c; ++i){
		printFrac(indFrac);
		x++;
		if(x==c){
			printf("\n\n");
			x=0;
		}
		indFrac++;
	}
	printf("\n");
}

struct Frac mult(struct Frac f1,struct Frac f2){
	struct Frac res;
	res.num=f1.num * f2.num;
	res.den= f1.den * f2.den;
	struct Frac *p1;
	p1 = &res;
	simplify(p1);
	return res;
}

struct Frac sum(struct Frac f1,struct Frac f2){
	struct Frac res;
	res.num=(f2.den*f1.num)+(f1.den*f2.num);
	res.den=f1.den * f2.den;
	struct Frac *p1;
	p1 = &res;
	simplify(p1);
	return res;
}

int main(){
	int fr,fc,sr,sc;
	printf("Write number of rows of the first matrix\n");
	scanf("%d",&fr);
	printf("Write number of columns of the first matrix\n");
	scanf("%d",&fc);
	printf("Write number of rows of the second matrix\n");
	scanf("%d",&sr);
	printf("Write number of columns of the second matrix\n\n");
	scanf("%d",&sc);

	if(fc!=sr){
		printf("The operation is impossible\n");
		return -1;
	}

	struct Frac res[fr][sc];
	struct Frac firstFrac[fr][fc];
	struct Frac secondFrac[sr][sc];

	struct Frac *indRes = (struct Frac*)malloc(sizeof(struct Frac) * (fr*sc));
	struct Frac *indFrac = (struct Frac*)malloc(sizeof(struct Frac) * (fr*fc));
	struct Frac *indFrac2 = (struct Frac*)malloc(sizeof(struct Frac) * (sr*sc));

	for (int i = 0; i < fr*fc; ++i){
		printf("Input fraction %d of the first matrix\n", i+1);
		scanf("%d%d\n",&indFrac->num,&indFrac->den);
		if (indFrac->den == 0){
			printf("Invalid Fraction\n");
			return-1;
		}
		simplify(indFrac);
		indFrac++;
	}
	for (int i = 0; i < sr*sc; ++i){
		printf("Input fraction %d of the second matrix\n", i+1);
		scanf("%d%d\n",&(*indFrac2).num,&(*indFrac2).den);
		if (indFrac2->den == 0){
			printf("Invalid Fraction\n");
			return-1;
		}
		simplify(indFrac2);
		indFrac2++;
	}

	int r,c;
	for (int i = 0; i < fr*sc; ++i){
		indRes->num=0;
		indRes->den=1;
		indFrac = &firstFrac[r][0];
		indFrac2 = &secondFrac[0][c];
		for (int i = 0; i < fc; ++i){
			*indRes=sum(mult(*indFrac,*indFrac2),*indRes);
			simplify(indRes);
			indFrac++;
			indFrac2+=sr;
		}
		if(c<sc)
			c++;
		if(c==sc){
			r++;
			c=0;
		}
		indRes++;
	}

	indFrac = &firstFrac[0][0];
	indFrac2 = &secondFrac[0][0];
	indRes = &res[0][0];
	printMatrix(indFrac,fr,fc);
	printf(" X \n\n");
	printMatrix(indFrac2,sr,sc);
	printf(" = \n\n");
	printMatrix(indRes,sr,sc);
}