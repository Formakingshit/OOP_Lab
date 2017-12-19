#include <iostream>
#include <iomanip>
#include <fstream>

#define EPS 0.001
#define K 0.05

using namespace std;

long long fact(int i){
	long long fact_in = i; 
	
	if(i == 0){
		return 1;
	}

	while(i > 1){
		i--;
		fact_in *= i;
	}

	return fact_in;
}

double *sum(double x){
	int i = 0;
	double	result,
					result_end = 0;
	double *res = new double [2];
	long double pi = acos((long double) -1);
	
	do{
		result = pow(x, i) * cos(1 + (i * pi) / 2) / fact(i);
		result_end += result; 
		i++;
	}
	while(fabs(result) > EPS);
	*res = i;
	*(res + 1) = result_end;
	return res;
}



double accurate(double x){
	return cos(x + 1);
}


int main(){
	double x = 0;
	
	cout<<setw(6)<<"x  |"<<"   f(x)   |"<<"  facc(x)  |"<<"   100%   |"<<" N |"<<endl;
	double	*fx,
					ftx,
					rang;
	string file = "fi.txt";
	ofstream output(file);

	while(x < 1 + EPS){ 	
		fx = sum(x);
		ftx = accurate(x);
		rang = fabs((*(fx + 1) - ftx) / *(fx + 1) * 100);
	
		output<<ftx<<", ";

		if(ftx >= 0){
			printf("%0.3lf|  %0.3lf   |  %0.4lf   |  %0.4lf  | %0.0lf |  \n", x, ftx, *(fx+ 1), rang, *fx );
		}

		else {
				printf("%0.3lf| %0.3lf   | %0.4lf   |  %0.4lf  | %0.0lf |  \n", x, ftx, *(fx+ 1), rang, *fx );
		}
		x += K; 
	}
}