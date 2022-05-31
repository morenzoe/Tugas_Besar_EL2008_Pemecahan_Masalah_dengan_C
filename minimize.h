/**EL2008 Pemecahan Masalah dengan C 2021/2022
*Tugas              : Tugas Besar 2022
*Kelompok           : 2
*Hari dan Tanggal   : Kamis, 19 Mei 2022
*Dosen              : 
*Nama File          : minimize.h
*Deskripsi          : Header file untuk minimize.c, berisi macros dan prototypes
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 255         // ukuran maksimal string input 

/**
 * elemen dari LinkedList.
 * 
 * @param mintermDec    minterm dalam desimal
 * @param mintermBin    minterm dalam  biner
 * @param numOnes       jumlah bit 1 minterm biner
 * @param isImplicant   indikator minterm implicant, 1 atau 0
 * @param next          pointer ke node berikutnya
 */
typedef struct Node{
    int* mintermDec;
    int* mintermBin;
    int numOnes;
    int isImplicant;
    struct Node* next;
} Node;

/** 
 * representasi dari singly-linked list
 *
 * @param head pointer menuju node paling pertama dalam singly-linked list
 */
typedef struct LinkedList{
    Node* head;
} LinkedList;

/**
 * prosedur untuk membuat warna font command line menjadi merah
 */
void red();

/** 
 * prosedur untuk mengembalikan warna font command line menjadi default
 */
void reset();

/** 
 * fungsi untuk memeriksa apakah suatu string hanya berisi integer
 *
 * @param token : string yang akan diperiksa
 * @return 1 jika string hanya berisi integer, 0 sebaliknya
 */
int isInteger(char* token);

/** 
 * fungsi untuk memeriksa apakah suatu string hanya berisi integer
 *
 * @param node : node yang ingin dihitung
 * @param numVariables : jumlah variabel persamaan boolean
 * @return 1 jika string hanya berisi integer, 0 sebaliknya
 */
int countOnes(Node* node, int numVariables);

/** 
 * prosedur untuk menambahkan node ke akhir singly-linked list
 *
 * @param list : singly-linked list yang ingin ditambahkan
 * @param node : node yang ingin ditambahkan
 * @result node berada di akhir list
 */
void insertNode(LinkedList* list, Node* node);

/** 
 * prosedur untuk menyimpan minterm dalam desimal ke dalam node baru
 *
 * @param list : singly-linked list yang ingin ditambahkan
 * @param numMinterms : jumlah minterm persamaan boolean
 * @param numVariables : jumlah variabel persamaan boolean 
 * @param minterm : minterm dalam desimal
 * @result minterm dalam desimal dan biner tersimpan di akhir list
 */
void saveMinterm(LinkedList* list, int numMinterms, int numVariables, int minterm);

/** 
 * prosedur untuk mengurutkan singly-linked list
 *
 * @param list : singly-linked list yang ingin dikelompokkan
 * @param numVariables : jumlah variabel persamaan boolean
 * @result list terurut berdasarkan nilai numOnes tiap node
 */
void groupByOnes(LinkedList* list, int numVariables);

/** 
 * prosedur untuk menampilkan tabel hasil pengelompokkan
 *
 * @param list : singly-linked list yang ingin ditampilkan
 * @param numVariables : jumlah variabel persamaan boolean
 * @result tercetak tabel hasil pengelompokan list oleh groupByOnes
 */
void displayImplicant(LinkedList* list, int numVariables);

/** 
 * prosedur untuk menyederhanakan singly-linked list
 *
 * @param list : singly-linked list yang ingin disederhanakan
 * @param numMinterms : jumlah minterm persamaan boolean
 * @param numVariables : jumlah variabel persamaan boolean
 * @result list berisi hasil penyederhanaan persamaan boolean dan tercetak tabel tahap penyederhanaan
 */
void minimize(LinkedList* list, int numMinterms, int numVariables);

/** 
 * prosedur untuk menghapus node duplikat dari singly-linked list
 *
 * @param list : singly-linked list yang ingin disederhanakan 
 * @param numVariables : jumlah variabel persamaan boolean
 * @result list tidak memiliki node dengan minterm dalam biner duplikat
 */
void deleteDuplicate(LinkedList* list, int numVariables);

/** 
 * fungsi untuk menghitung panjang singly-linked list
 *
 * @param list : singly-linked list yang ingin diperiksa
 * @return panjang list
 */
int countPrimeImplicant(LinkedList* list);

/** 
 * prosedur untuk mengisi matriks
 *
 * @param list : singly-linked list yang ingin diperiksa
 * @param numMinterms : jumlah minterm persamaan boolean
 * @param numVariables : jumlah variabel persamaan boolean
 * @param arrayMinterm : array penyimpan semua minterm input
 * @param arrayPrimeImplicant : matriks penyimpan semua prime implicant dan mintermnya
 * @result arrayPrimeImplicant terisi dengan minterm yang ditangani masing-masing prime implicant
 */
void fillPrimeImplicant(LinkedList* list, int numMinterms, int numVariables, int* arrayMinterm, int* arrayPrimeImplicant);

/** 
 * prosedur untuk menampilkan matriks
 *
 * @param list : singly-linked list yang ingin dibaca
 * @param numMinterms : jumlah minterm persamaan boolean
 * @param numVariables : jumlah variabel persamaan boolean
 * @param arrayMinterm : array penyimpan semua minterm input
 * @param arrayPrimeImplicant : matriks penyimpan semua prime implicant dan mintermnya
 * @result tercetak tabel prime implicant
 */
void displayPrimeImplicant(LinkedList* list, int numMinterms, int numVariables, int* arrayMinterm, int* arrayPrimeImplicant);

/** 
 * prosedur untuk mencari essential prime implicant
 *
 * @param list : singly-linked list yang ingin diperiksa
 * @param numMinterms : jumlah minterm persamaan boolean
 * @param numPrimeImplicant : jumlah prime implicant hasil penyederhanaan
 * @param arrayPrimeImplicant : matriks penyimpan semua prime implicant dan mintermnya
 * @result isImplicant di dalam node di dalam list berisi info apakah prime implicant esensial atau tidak
 */
void findEssential(LinkedList* list, int numMinterms, int numPrimeImplicant, int* arrayPrimeImplicant);

/** 
 * prosedur untuk menampilkan hasil akhir
 *
 * @param list : singly-linked list yang ingin dibaca 
 * @param numVariables : jumlah variabel persamaan boolean
 * @result tercetak persamaan boolean hasil penyederhanaan
 */
void printResult(LinkedList* list, int numVariables);









