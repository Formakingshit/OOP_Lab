#include <iostream>
#include <math.h>

using namespace std;

#define A 65
#define DELTA 0.04

struct SomeStruct {
	float *masFx;
	float x1;
	float x2;
	float dx;
};

void ReadPar(SomeStruct *param, float *a, float *b){
	float c = 0.0;
	printf("Print a: ");
	scanf("%f", a);
	printf("Print b: ");
	scanf("%f", b);
	printf("Print x1: ");
	scanf("%f", &param->x1);
	printf("Print x2: ");
	scanf("%f", &param->x2);
	do {
		printf ("Print dx(>0): ");
		scanf("%f", &param->dx);
	} while (param->dx <= 0);
	if (param->x1 > param->x2) {
		c  = param->x1;
		param->x1 = param->x2;
		param->x2 = c;
	}
}

void Somefunc(SomeStruct *param, float a, float b, int n){
	float x = param->x1;
	for (int i = 0; i < n; i++){
		if ( x < 2 ){
			param->masFx[i] = (x - b) / x;
		} else {
			param->masFx[i] = -a * x * x - b;
		}
		x += param->dx;
	}
}

void Tab(int n, SomeStruct *param){
	float x = param->x1;

	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 209, 205, 205, 205, 205, 205, 205, 205, 205, 187);
	printf("%c    x    %c   F(x) %c\n", 186, 179, 186);
	
	for(int i = 0; i < n; i++){
		printf("%c %6.2lf  %c %7.2lf%c\n", 186, x, 179, (*param).masFx[i], 186);
		x += param->dx;
	}

	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 200, 205, 205, 205, 205, 205, 205, 205, 205, 205, 207, 205, 205, 205, 205, 205, 205, 205, 205, 188);

}

void Tab2(int n, SomeStruct *param, float *rnd){
float x = param->x1;

printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 209, 205, 205, 205, 205, 205, 205, 205, 205, 187);
printf("%c    x    %c   F(x) %c\n", 186, 179, 186);
	
for(int i = 0; i < n; i++){
	printf("%c %6.2lf  %c %7.2lf%c\n", 186, x, 179, *(rnd + i), 186);
	x += param->dx;
}

printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 200, 205, 205, 205, 205, 205, 205, 205, 205, 205, 207, 205, 205, 205, 205, 205, 205, 205, 205, 188);

}

void Norm(float *arr, int *intf, int n){
	int k = 0;
	float max, min;
	

	min = arr[0];
	for (int j = 0; j < n; j++){
		if (arr[j] < min){
			min = arr[j];
		}
	}
	for (int j = 0; j < n; j++){
		arr[j] = arr[j] - min;
	}
		max = arr[0];
	for (int j = 1; j < n; j++){
		if (arr[j]>max){
			max = arr[j];
		}
	}
	for (int j = 0; j < n; j++){
		arr[j] = (arr[j] / max) * A;
	}
	for (int j = 0; j < n; j++){
		intf[j] = int(arr[j]);
	}

}

void Print(int *intf, int n){
	char symbol = 0xB0;
	int k = 0;
	for (int i = 0; i < n; i++){

		printf("%4d ", intf[i]);
		while (k < intf[i]){
			printf("%c", symbol);
			k++;
		}
		printf("\n");
		k = 0;
	}
}


void S1S2(SomeStruct *param, int n, float *s1, float *s2){
	int count = 0;
	*s2 = param->masFx[0];

	for (int i = 0; i < n; i++){
		if ( i%2 && *s1 > param->masFx[i]){
			*s1 = param->masFx[i];
		}
		if (*s2 < 0){
			*s2 += param->masFx[i];
			count++;
		}
	}

	*s2 /= count;
}

void Rndfunc(float *rnd, int n, float s1, float s2){
	float smin = 0, smax = 0, step = 0, valueRnd = 0;
	
	if (s1 > s2){
		smin = s2;
		smax = s1;
	} else {
		smax = s2;
		smin = s1;
	}

	step = fabs(DELTA * smax);

	cout << "Smax: " << smax << " Smin: " << smin << " Step " << step << endl;
	valueRnd = smax - smin ;
	
	for (int i = 0; i < n; i++){
		rnd[i] = (rand() %  (int(valueRnd/step) + 1)) * step + smin;
	}

}

int main(){
	SomeStruct S_obj;
	float a = 0, b = 0, x = 0;

	ReadPar(&S_obj, &a, &b);

	int n = (S_obj.x2 - S_obj.x1) / S_obj.dx + 1.5;
	S_obj.masFx = new float [n];
	
	int *intf = new int [n];
	Somefunc(&S_obj, a, b, n);

	Tab(n, &S_obj);

	printf("\n\n");
	
	float *objArr = new float [n];
	for (int i = 0 ; i < n; i++){
		objArr[i] = S_obj.masFx[i];
	}

	Norm(objArr, intf, n);
	Print(intf, n);

	printf("\n\n");
	float s1 = 0, s2 = 0;
	S1S2(&S_obj, n, &s1, &s2);

	float *rnd = new float [n];
	Rndfunc(rnd, n, s1, s2);

	Tab2(n, &S_obj, rnd);

	printf("\n\n");
	Norm(rnd, intf, n);
	Print(intf, n);

	printf("\n Pointer value: %p, Pointer adress: %p;\n", rnd, &rnd);
	system("pause");
	delete [] rnd;
	delete [] objArr;

	return 0;
}