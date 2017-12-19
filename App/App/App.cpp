//Вычислить средние арифметические значения неотрицательных элементов каждой строки матрицы [N;M].
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

int N;

using namespace std;
void inputm(double **matr);//Заполнение матрицы
void outputm (double **matr,double *sum);//Вывод результата
void sumofline(double **matr,double *sum);//Сумма ряда матрицы

int main()
{
    cout << "Enter matrix N x N" << endl;
    cin >> N;
    double **matr = new double *[N];
    for (int i = 0; i < N; i++)
    {
        matr[i] = new double [N];
    }
    double *sum = new double [N];
    cout << "Matrix random filling" << endl ;
    inputm(matr);
    sumofline(matr,sum);
    return 0;
}

void inputm(double **matr)
{
    int i, j;
    srand (time(0));
    for (i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            matr[i][j] =  (0.03 * (i+1) * (i+1) - 1.18 * (j + 1) +1.12) * cos(((j+1) + 5.1 * (i+1) )/ 19 );
        }
    }
}

void outputm(double **matr,double *sum)
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        cout << endl;
        for(j = 0; j < N; j++)
            printf("%2d  ",matr[i][j]);
    }
    cout << endl;
    for (i = 0; i < N; i++){
        cout << i << " line elements arithmetic average:" << sum[i] << endl;
    }
}

void sumofline(double **matr,double *sum)
{
    int k,io = 0,jo =0 ;
    double s = 0 ;
		for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
					if (((i+1)+(j+1) == 46 && (i+1)-(j+1) == 2) || (j == 0 && i <= 2) || (i == 1 && j <= 45) )
            {
                if (matr[i][j] > s)
                {
                    s=matr[i][j];
                    io = i;
                    jo = j;
                }
            }
        }
    }
    cout << "\n\n\n\n\n sum      " ;
    printf ("%0.4f",s);
    cout << endl << ";   " << io << endl;
    cout << endl << ";   " << jo << endl;
}
