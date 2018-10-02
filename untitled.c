/*int max(struct Frac *p1, int l1, struct Frac *p2, int l2){
	int max = 0;
	for (int i = 0; i < l1; ++i){
		int length = floor(log10(abs(p1->den))) + 1;
		if (length>max)
			max=length;
		p1++;
	}
	for (int i = 0; i < l2; ++i){
		int length = floor(log10(abs(p2->den))) + 1;
		if (length>max)
			max=length;
		p2++;
	}
	
	return max;
}*/


//printf("Max is = %d\n",max(indFrac,fr*fc,indFrac2,sr*sc));