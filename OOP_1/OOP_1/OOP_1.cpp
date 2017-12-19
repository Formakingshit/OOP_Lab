#include <stdio.h>
#include <iostream>
using namespace std;

#define S_L 0xB0

struct Somestruct{
	double *f;
	double x1, x2, dx;
	int a, b;
}Head_struct; 

int ReadPar();
void Tab(int);
int New_Arr(int);
int Size_new(int);

int main(){
	int size_of_arr;

	size_of_arr = ReadPar();
	//printf("%d", size_of_arr);
	
	Head_struct.f = new double [size_of_arr]; 
	
	double x;
	x = Head_struct.x1; 

	for(int i = 0; i < size_of_arr; i++){
		if(x >= 2){
			Head_struct.f[i] = -(Head_struct.a * x * x) - Head_struct.b; 
		}

		else{
			Head_struct.f[i] = (x - Head_struct.b) / x ; 
		}
		x += Head_struct.dx;
	}

	Tab(size_of_arr);

	int size_new_arr = Size_new(size_of_arr);

	int *intf = new int[size_new_arr];

	for(int i = 0; i < size_new_arr; i++){
		printf("%d\n", *(intf + i));
	}

}

int ReadPar(){
	printf("Input a = ");
	scanf_s("%d", &Head_struct.a);
	printf("Input b = ");
	scanf_s("%d", &Head_struct.b);

	printf("Input x1 = ");
	scanf_s("%lf", &Head_struct.x1);
	printf("Input x2 = ");
	scanf_s("%lf", &Head_struct.x2);
	printf("Input dx = ");
	scanf_s("%lf", &Head_struct.dx);

	return ((Head_struct.x2 - Head_struct.x1) / Head_struct.dx) + 1; 
}

void Tab(int size_of_arr){
	double x;
	x = Head_struct.x1;

	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 187);
	printf("%c    x    %c   F(x) %c\n", 186, 179, 186);
	for(int i = 0; i < size_of_arr; i++){
		printf("%c %6.2lf  %c %7.2lf%c\n", 186, x, 179, Head_struct.f[i], 186);
		x += Head_struct.dx;
	}
	
		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 200, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 188);
}

int New_Arr(int size_of_arr){
	int size = 0;

	for(int i = 0; i < size_of_arr; i++){
		if(Head_struct.f[i] >= 0 && Head_struct.f[i] <= Head_struct.a)
			size++;
	}

	return size; 
}

int Size_new(int size_of_arr){
	int size = 0;

	for(int i = 0; i < size_of_arr; i++){
		if(Head_struct.f[i] >= 0 && Head_struct.f[i] <= Head_struct.a){
			size++;
		} 
	}
	return size;
}