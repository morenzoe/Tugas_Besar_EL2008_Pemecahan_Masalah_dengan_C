#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Fungsi untuk mengkonversi bilangan desimal menjadi biner, digunakan untuk 0-(pow(2, var)-1) dalam truth table
void decToBinary(int decimal, int var, int *matVar)
{
    // Kamus
    int i; 
    
    // Modulo desimal oleh 2 karena biner berbasis 2
    // Indeks dimulai dari belakang
    for(i=var-1; i>=0; i--)
    {
        matVar[i] = decimal%2;
        decimal = decimal/2;        // Sisa pembagian kemudian akan dimodulo 2 lagi terus menerus sampai bernilai nol
    }

    return;
}

/*
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
    
   printf("%d\n", comb);

    for (int i=0; i<comb; i++)
    {
        printf("%d\n", arr[i]);
    }
    

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
    
    for (i=0; i<comb; i++)
    {
        for (j=0; j<var; j++)
        {
            printf("%d", matrix[i][j]);
        }
        printf("\n");
    }
    

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
*/

// Fungsi utama
int main()
{
    int var = 3; // jumlah variabel
    int *matVar = malloc(var*sizeof(int)); // matriks variabel
    
    // membuat truth table
    int i,j;
    for(i=0; i<pow(2,var); ++i){
        // konversi desimal ke biner
        decToBinary(i, var, matVar);
        // mencetak hasil biner
        printf("%d\t", i);
        for(j=0; j<var; ++j){
            printf("%d", matVar[j]);
        }
        printf("\n");
    }
    

    return 0;
}
