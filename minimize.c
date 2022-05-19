/*EL2008 Pemecahan Masalah dengan C 2021/2022
*Tugas              : Tugas Besar 2022
*Kelompok           : 2
*Hari dan Tanggal   : Senin, 2 Mei 2022
*Dosen              : 
*Nama File          : minimize.c
*Deskripsi          : Program untuk minimisasi logic dengan
*                     Quine-McCluskey Tabular Method. Program
*                     meminta input minterm dalam desimal
*                     dan mengembalikan persamaan hasil penyederhanaan.
*/

#include <stdio.h>
#include <stdlib.h>

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

int countOnes(Node* node, int numVariables){
    int i;
    int sum = 0;
    
    // Memeriksa semua bit
    for(i=0; i<numVariables; ++i){
        // Menambahkan jumlah bit 1
        if(node->mintermBin[i]==1){
            sum += 1;
        }
    }
    
    return sum;
}

void saveMinterm(LinkedList* list, int numMinterms, int numVariables, int minterm){
    int i;
    
    // Mengalokasikan memori node baru
    Node* new = (Node*) malloc(sizeof(Node));
    
    // Mengisi data node baru
    // data minterm dalam desimal
    new->mintermDec = malloc(numMinterms*sizeof(int));
    new->mintermDec[0] = minterm;
    
    // data minterm dalam biner
    new->mintermBin = malloc(numVariables*sizeof(int));
    // Konversi dan simpan minterm dalam bentuk biner
    for(i=numVariables-1; i>=0; --i){
        new->mintermBin[i] = minterm%2;
        minterm = minterm/2;        
    }
    
    // data jumlah bit 1
    new->numOnes = countOnes(new, numVariables);
    
    // data indikator implicant, asumsi setiap minterm adalah implicant
    new->isImplicant = 1;
    
    // data node berikutnya
    new->next = NULL;
    
    // Jika linked list kosong, assign new sebagai head
    if(list->head==NULL){
        list->head = new;
    } else{
        // Membuat pointer sementara untuk menyusuri linked list
        struct Node* temp = list->head;
        
        // Menyusuri linked list hingga node terakhir
        while(temp->next!=NULL){
            temp = temp->next;
        }
        
        // Menghubungkan node terakhir dengan node baru
        temp->next = new;
    }  
    
    return;
}

void printLinkedList(LinkedList* list, int numVariables) {
    int i;
    
    Node* temp = list->head;
    
    printf("\n");
    while (temp != NULL) {
        printf("mintermDec: %d\n", temp->mintermDec[0]);
        printf("mintermBin: ");
        for(i=0; i<numVariables; ++i){
            printf("%d", temp->mintermBin[i]);
        }
        printf("\n");
        printf("numOnes: %d\n", temp->numOnes);
        printf("isImplicant: %d\n", temp->isImplicant);
        printf("\n");
        temp = temp->next;
    }
    printf("\n");
    
    free(temp);
    
    return;
}

int main()
{
    int i;
    
    int numVariables;
    int numMinterms;
    int minterm;
    
    // Meminta input data
    printf("\nEnter the number of variables : ");       
    scanf("%d",&numVariables);
    printf("\nEnter the number of numMinterms : ");
    scanf("%d",&numMinterms);
    
    // Membuat linked list untuk menyimpan minterm
    LinkedList* mintermList = (LinkedList*) malloc(sizeof(LinkedList));
    mintermList->head = NULL;
    
    // Meminta input minterm dalam desimal dan menyimpannya ke mintermList
    // asumsi input terurut dari minterm terkecil
    for(i=0; i<numMinterms; ++i){
        printf("minterm ke-%d: ", i+1);
        scanf("%d", &minterm);
        
        saveMinterm(mintermList, numMinterms, numVariables, minterm);
        
    }
    
    // debugging
    printLinkedList(mintermList, numVariables);

    return 0;
    
}