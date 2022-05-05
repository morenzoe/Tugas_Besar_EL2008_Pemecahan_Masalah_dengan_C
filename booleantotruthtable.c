#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MAX_LEN 10                  // Asumsikan jumlah variabel tidak pernah mencapai jumlah 10
#define MAX 255                     // Asumsikan maksimal jumlah variabel adalah 8, yaitu berjumlah 8 bit

// Fungsi untuk mengkonversi bilangan desimal menjadi biner, digunakan untuk 0-(pow(2, var)-1) dalam truth table
int *decToBinary(int decimal, int var)
{
    // Kamus
    static int binary[MAX_LEN];     // Penampungan bilangan biner
    int i, a[var];                  // Indeks dan penampungan hasil pembagian dan modulo desimal
    // Inisialisasi array a
    for (i=0; i<var; i++)
    {
        a[i] = 0;
    }

    // Modulo desimal oleh 2 karena biner berbasis 2
    for(i=0; decimal>0; i++)
    {
        a[i] = decimal%2;
        decimal = decimal/2;        // Sisa pembagian kemudian akan dimodulo 2 lagi terus menerus sampai bernilai nol
    }

    // Jika desimal bernilai 0, harus diinisialisasi manual supaya isi array binary ada nilainya
    if (decimal == 0)
    {
        for (i=0; i<var; i++)
        {
            binary[i] = 0;
        }
    }

    // Karena pembagian dilakukan dari belakang, array a harus dibalik urutannya untuk mendapatkan urutan biner yang benar
    for(i=i-1;i>=0;i--)
    {
        binary[var-i-1] = a[i];
    }

    // Debugging
    /*
    for(i=0; i<var; i++)
    {
        printf("%d",binary[i]);
    }
    */

    return binary;
}

// Fungsi membentuk truth table template
int *truthTable(int var, int fx)
{
    // Kamus
    int i,j;                        // Variabel indeks
    int comb = pow(2, var);         // Jumlah kombinasi biner yang dapat dibentuk
    int *temp;                      // Penampungan sementara untuk array biner

    int matrix[comb][var];          // Matrix penampungan biner
    static int arr[MAX];            // Array hasil truth table

    // Debugging
    /*
   printf("%d\n", comb);

    for (int i=0; i<comb; i++)
    {
        printf("%d\n", arr[i]);
    }
    */

    // Pengulangan konversi decToBinary dengan nilai i = 0 sampai i = comb-1
    for (i=0; i<comb; i++)
    {
        // Penggunaan fungsi konversi decToBinary
        temp = decToBinary(i, var);
        for (j=0; j<var; j++)
        {
            // Inputan hasil konversi biner ke dalam matrix biner
            matrix[i][j] = *(temp+j);
        }
        // Overwrite array temp
        temp = 0;
    }

    // Debugging
    /*
    for (i=0; i<comb; i++)
    {
        for (j=0; j<var; j++)
        {
            printf("%d", matrix[i][j]);
        }
        printf("\n");
    }
    */

    // Memasukkan matrix[i] ke dalam fungsi fx, kemudian dimasukkan ke dalam arr sebagai hasil dari truth table
    for (i=0; i<comb; i++)
    {
        arr[i] = fx;
    }

    // Debugging

    printf("\n");
    for (i=0; i<comb; i++)
    {
        printf("%d", arr[i]);
    }


    return arr;
}

// Fungsi utama
int main()
{
    // Kamus
    // Input user untuk fungsi ini
    int **matrix;
    int i;
    // Boolean algebra equation, fx = w(x'+y)
    int fx = (matrix[i][0])&&(!(matrix[i][1])||(matrix[i][2]));
    int var = 3;                     // Jumlah variabel yang digunakan

    // Lokal variable
    int *p;

    p = truthTable(var, fx);

    return 0;
}
