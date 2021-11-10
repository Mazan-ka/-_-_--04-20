//Решение СЛАУ методом ортогонализации
#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

#define N 3

double A[N][N];                 //Массив для A
double F[N];                   //Массив для F
double U[N][N] = { 0 };         //U с N=3 значениями
double V[N][N] = { 0 };         //Функция V с N=3 значениям;
double L[N] = { 0 };            //L с N=3 значениями
double temp[N];
double H[N];


// скалярное произведение
double scalar(double* a, double* b) {
    double P = 0;
    for (int j = 0; j < N; j++) {
        P += a[j] * b[j];
    }
    return P;

}


int main() {
    setlocale(LC_ALL, "RUS");
    //Заполняем массив A

    cout << "Значения матрицы A: \n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << "Введите элемент A[" << i << "," << j << "]: ";
            cin >> A[i][j];
        }
    }

    //Заполняем массив F
    cout << "\n\nЗначения вектора F: \n";
    for (int l = 0; l < N; l++) {
        cout << "Введите элемент F[" << l << "]: ";
        cin >> F[l];
    } //1
    //Вывод матриц:
    cout << "Матрица A:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << A[i][j] << "  ";
        }
        cout << endl;
    }

    cout << "\nВектор F:" << endl;
    for (int l = 0; l < N; l++) {
        cout << F[l] << endl;
    }
    cout << endl;

    //Начальная иттерация:

    for (int i = 0; i < N; i++) {
        U[0][i] = (A[0][i]);               //U[0]
    }
    L[0] = sqrt(scalar(U[0], U[0]));       //L[0]
    for (int i = 0; i < N; i++) {
        V[0][i] = U[0][i] * (1 / L[0]);    //V[0]
    }
    double T[N];
    T[0] = F[0] / L[0];                     //H[0]



                                            //Последующие иттерации
    int count = 1; //Счетчик переменных для которых уже найдены первые значения 
    int n = 0;
    double t;


    do {
        double temp_h;
        temp_h = 0;

        for (int i = 0; i < N; i++) {
            temp[i] = 0;
        }
        //U_i
        for (int j = 0; j <= count - 1; j++) {
            t = scalar(A[count], V[j]); //Получили c[i,j] 

            for (int i = 0; i < N; i++) {
                temp[i] = temp[i] + (t * V[j][i]); //Получили c[i,j]*v[k]

            }
            temp_h += t * T[j];
        }


        //Нашли U
        for (int i = 0; i < N; i++) {
            U[count][i] = A[count][i] - temp[i];
        }

        //Нашли L
        L[count] = sqrt(scalar(U[count], U[count]));

        //Нашли H
        T[count] = (F[count] - temp_h) / (L[count]);

        //V_[i]
        for (int i = 0; i < N; i++) {
            V[count][i] = (1 / L[count]) * (U[count][i]);
        }

        n++;
        count++;

    } while (count < N);


    /*******************************PRINT*******************************/
    cout << "\n\n";

    double x = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            x += V[j][i] * T[j];
        }
        cout << "X_" << i + 1 << " = " << x << endl;
        x = 0;
    }

    system("pause");
}