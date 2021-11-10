//������� ���� ������� ���������������
#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

#define N 3

double A[N][N];                 //������ ��� A
double F[N];                   //������ ��� F
double U[N][N] = { 0 };         //U � N=3 ����������
double V[N][N] = { 0 };         //������� V � N=3 ���������;
double L[N] = { 0 };            //L � N=3 ����������
double temp[N];
double H[N];


// ��������� ������������
double scalar(double* a, double* b) {
    double P = 0;
    for (int j = 0; j < N; j++) {
        P += a[j] * b[j];
    }
    return P;

}


int main() {
    setlocale(LC_ALL, "RUS");
    //��������� ������ A

    cout << "�������� ������� A: \n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << "������� ������� A[" << i << "," << j << "]: ";
            cin >> A[i][j];
        }
    }

    //��������� ������ F
    cout << "\n\n�������� ������� F: \n";
    for (int l = 0; l < N; l++) {
        cout << "������� ������� F[" << l << "]: ";
        cin >> F[l];
    } //1
    //����� ������:
    cout << "������� A:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << A[i][j] << "  ";
        }
        cout << endl;
    }

    cout << "\n������ F:" << endl;
    for (int l = 0; l < N; l++) {
        cout << F[l] << endl;
    }
    cout << endl;

    //��������� ���������:

    for (int i = 0; i < N; i++) {
        U[0][i] = (A[0][i]);               //U[0]
    }
    L[0] = sqrt(scalar(U[0], U[0]));       //L[0]
    for (int i = 0; i < N; i++) {
        V[0][i] = U[0][i] * (1 / L[0]);    //V[0]
    }
    double T[N];
    T[0] = F[0] / L[0];                     //H[0]



                                            //����������� ���������
    int count = 1; //������� ���������� ��� ������� ��� ������� ������ �������� 
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
            t = scalar(A[count], V[j]); //�������� c[i,j] 

            for (int i = 0; i < N; i++) {
                temp[i] = temp[i] + (t * V[j][i]); //�������� c[i,j]*v[k]

            }
            temp_h += t * T[j];
        }


        //����� U
        for (int i = 0; i < N; i++) {
            U[count][i] = A[count][i] - temp[i];
        }

        //����� L
        L[count] = sqrt(scalar(U[count], U[count]));

        //����� H
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