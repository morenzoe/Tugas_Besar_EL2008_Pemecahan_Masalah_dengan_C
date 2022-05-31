/*EL2008 Pemecahan Masalah dengan C 2021/2022
*Tugas              : Tugas Besar 2022
*Kelompok           : 2
*Hari dan Tanggal   : Kamis, 19 Mei 2022
*Dosen              : 
*Nama File          : minimize.h
*Deskripsi          : Header file untuk minimize.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 255         // ukuran maksimal string input 

typedef struct Node{
    int* mintermDec;    // minterm dalam desimal
    int* mintermBin;    // minterm dalam  biner
    int numOnes;        // jumlah bit 1 minterm biner
    int isImplicant;    // indikator minterm implicant, 1 atau 0
    struct Node* next;  // pointer ke node berikutnya
} Node;

typedef struct LinkedList{
    Node* head; // pointer ke node pertama linked list
} LinkedList;

void red();

void reset();

void printLinkedList(LinkedList* list, int numVariables);

int isInteger(char* token);

int countOnes(Node* node, int numVariables);

void insertNode(LinkedList* list, Node* node);

void saveMinterm(LinkedList* list, int numMinterms, int numVariables, int minterm);

void groupByOnes(LinkedList* list, int numVariables);

void displayImplicant(LinkedList* list, int numVariables);

void minimize(LinkedList* list, int numMinterms, int numVariables);

void deleteDuplicate(LinkedList* list, int numVariables);

int countPrimeImplicant(LinkedList* list);

void fillPrimeImplicant(LinkedList* list, int numMinterms, int numVariables, int* arrayMinterm, int* arrayPrimeImplicant);

void displayPrimeImplicant(LinkedList* list, int numMinterms, int numVariables, int* arrayMinterm, int* arrayPrimeImplicant);

void findEssential(LinkedList* list, int numMinterms, int numPrimeImplicant, int* arrayPrimeImplicant);

void printResult(LinkedList* list, int numVariables);









