/*EL2008 Pemecahan Masalah dengan C 2021/2022
*Tugas              : Tugas Besar 2022
*Kelompok           : 2
*Hari dan Tanggal   : Kamis, 19 Mei 2022
*Dosen              : 
*Nama File          : minimize.c
*Deskripsi          : Program untuk minimisasi logic dengan
*                     Quine-McCluskey Tabular Method. Program
*                     meminta input minterm dalam desimal
*                     dan mengembalikan persamaan hasil penyederhanaan.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

void printLinkedList(LinkedList* list, int numVariables) {
    int i;
    
    Node* temp = list->head;
    
    printf("\n");
    while (temp != NULL) {
        i = 1;
        printf("mintermDec: %d", temp->mintermDec[0]);
        while((temp->mintermDec[i]!=-1)&&(i<(numVariables*numVariables))){
            printf(", %d", temp->mintermDec[i]);
            i += 1;
        }
        printf("\n");
        printf("mintermBin: ");
        for(i=0; i<numVariables; ++i){
            if(temp->mintermBin[i]==-2){
                printf("-");
            } else{
                printf("%d", temp->mintermBin[i]);
            }
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

int countOnes(Node* node, int numVariables){
    int i;
    int sum = 0;    // variabel jumlah bit 1
    
    // Memeriksa semua bit
    for(i=0; i<numVariables; ++i){
        // Menambahkan jumlah bit 1
        if(node->mintermBin[i]==1){
            sum += 1;
        }
    }
    
    return sum;
}

void insertNode(LinkedList* list, Node* node){
    // Jika linked list kosong, assign node sebagai head
    if(list->head==NULL){
        list->head = node;
    } else{
        // Membuat pointer sementara untuk menyusuri linked list
        struct Node* temp = list->head;
        
        // Menyusuri linked list hingga node terakhir
        while(temp->next!=NULL){
            temp = temp->next;
        }
        
        // Menghubungkan node terakhir dengan node baru
        temp->next = node;
    }
    
    return;
}

void saveMinterm(LinkedList* list, int numMinterms, int numVariables, int minterm){
    int i;
    
    // Mengalokasikan memori node baru
    Node* new = (Node*) malloc(sizeof(Node));
    
    // Mengisi data node baru
    // data minterm dalam desimal
    new->mintermDec = malloc(numMinterms*sizeof(int));
    new->mintermDec[0] = minterm;
    // Menginisialisasi sisa array minterm dengan -1
    for(i=1; i<numMinterms; ++i){
        new->mintermDec[i] = -1;
    }
    
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
    
    // Menambahkan node baru ke linked list minterm
    insertNode(list, new);
    
    return;
}

void groupByOnes(LinkedList* list, int numVariables){
    int i;
    int temp;   // variabel sementara untuk pertukaran
    
    // Membuat pointer sementara untuk menyusuri linked list
    Node* temp1 = list->head;
    Node* temp2;
    
    // Menyusuri linked list
    while(temp1!=NULL){
        // Membandingkan temp1 dengan semua node setelahnya
        temp2 = temp1->next;
        while(temp2!=NULL){
            // Menukar data kedua node
            if((temp1->numOnes)>(temp2->numOnes)){
                // data minterm dalam desimal
                temp = temp1->mintermDec[0];
                temp1->mintermDec[0] = temp2->mintermDec[0];
                temp2->mintermDec[0] = temp;
                
                // data minterm dalam biner
                for(i=0; i<numVariables; ++i){
                    temp = temp1->mintermBin[i];
                    temp1->mintermBin[i] = temp2->mintermBin[i];
                    temp2->mintermBin[i] = temp;
                }
                
                // data jumlah bit 1
                temp = temp1->numOnes;
                temp1->numOnes = temp2->numOnes;
                temp2->numOnes = temp;
            }
            
            // Melanjutkan perbandingan ke node berikutnya
            temp2 = temp2->next;
        }
        
        // Melanjutkan perbandingan ke node berikutnya
        temp1 = temp1->next;
    }
    
    return;
}

void displayImplicant(LinkedList* list, int numVariables){
    int i;
    int numGroup = list->head->numOnes;   // variabel nomor baris, inisialisasi jumlah bit 1 implicant pertama
    
    // Membuat pointer sementara untuk menyusuri linked list
    Node* temp = list->head;    
    
    // Mencetak judul tabel
    printf("Group No.\tMinterms\tBinary of Minterms\n");
    printf("==================================================\n");
    // Mencetak nomor grup
    printf("     %d:\n", numGroup);
    
    // Menyusuri linked list
    while(temp!=NULL){
        // Jika mencapai implicant dengan jumlah bit 1 berbeda
        if(numGroup!=temp->numOnes){
            // Mengubah nomor grup
            numGroup = temp->numOnes;
            
            // Mencetak pembatas grup
            printf("--------------------------------------------------\n");
            
            // Mencetak nomor grup
            printf("     %d:\n", numGroup);
        }
        
        // Mencetak isi grup
        // mencetak minterm dalam desimal
        printf("\t\t%d", temp->mintermDec[0]);
        i = 1;
        while((temp->mintermDec[i]!=-1)&&(i<(numVariables*numVariables))){
            printf(",%d", temp->mintermDec[i]);
            i += 1;
        }
        printf("\t\t");
        
        // mencetak minterm dalam biner
        for(i=0; i<numVariables; ++i){
            if(temp->mintermBin[i]==-2){
                printf("-");
            } else{
                printf("%d", temp->mintermBin[i]);
            }
        }
        printf("\n");
        
        // Melanjutkan perbandingan ke node berikutnya        
        temp = temp->next;
    }
    printf("==================================================\n\n\n\n\n");
    
    return;
}

void minimize(LinkedList* list, int numMinterms, int numVariables){
    int i;
    int j;
    int simplified;     // variabel penanda adanya implicant yang disederhanakan
    int notSimplified;  // variabel penanda adanya implicant yang tidak disederhanakan
    int idxChange;      // variabel indeks bit yang berubah
    int sumChange;      // variabel jumlah perubahan
    
    int test=1;         // debugging
    
    while(simplified){
        // Menginisialisasi penanda
        simplified = 0;
        notSimplified = 0;
        
        // Membuat linked list untuk menyimpan minterm hasil penyederhanaan
        LinkedList* mintermGroupList = (LinkedList*) malloc(sizeof(LinkedList));
        mintermGroupList->head = NULL;
        
        // Membuat pointer sementara untuk menyusuri linked list
        Node* temp1 = list->head;
        Node* temp2;
        
        // Menyusuri linked list
        while(temp1!=NULL){      
            // debugging
            //printf("masuk while temp1\n");
            
            // Membandingkan temp1 dengan semua node setelahnya
            temp2 = temp1->next;
            while(temp2!=NULL){
                // debugging
                //printf("masuk while temp2\n");
                
                // Menginisialisasikan jumlah perubahan
                sumChange = 0;
                
                // Melakukan perbandingan dua grup yang bersebelahan
                if((temp2->numOnes)-(temp1->numOnes)==1){
                    // Melakukan perbandingan antar tiap bit
                    for(i=0; i<numVariables; ++i){
                        // Jika 1 bit berbeda
                        if((temp1->mintermBin[i])!=(temp2->mintermBin[i])){
                            // Menambah jumlah perubahan bit
                            sumChange += 1;
                            
                            // Menyimpan indeks perubahan bit
                            idxChange = i;
                        }
                    }
                }
                
                // debugging
                //printf("sumChange: %d\n", sumChange);
                
                // Jika hanya terdapat 1 perubahan bit
                if(sumChange==1){
                    // debugging
                    //printf("hanya 1 perubahan bit\n");
                    
                    // Menandai ada penyederhanaan
                    simplified = 1;
                    
                    // Mengubah indikator minterm bukan implicant
                    temp1->isImplicant = 0;
                    temp2->isImplicant = 0;
                    
                    // Menambahkan node penyederhanaan ke linked list
                    Node* new = (Node*) malloc(sizeof(Node));
                    
                    // Mengisi data node baru
                    // data minterm dalam desimal
                    new->mintermDec = malloc(numMinterms*sizeof(int));
                    
                    // dari node pertama
                    i=0;
                    while(temp1->mintermDec[i]!=-1){
                        new->mintermDec[i] = temp1->mintermDec[i];
                        i += 1;
                    }
                    
                    // dari node kedua
                    j=0;
                    while(temp2->mintermDec[j]!=-1){
                        new->mintermDec[i] = temp2->mintermDec[j];
                        i += 1;
                        j += 1;
                    }
                    
                    // Mengisi sisa array minterm dengan -1
                    for(j=i; j<numMinterms; ++j){
                        new->mintermDec[j] = -1;
                    }                
                    
                    // data minterm dalam biner
                    new->mintermBin = malloc(numVariables*sizeof(int));
                    for(i=0; i<numVariables; ++i){
                        new->mintermBin[i] = temp1->mintermBin[i];
                    }
                    // Menandai bit yang berubah
                    new->mintermBin[idxChange] = -2;
                    
                    // data jumlah bit 1
                    new->numOnes = temp1->numOnes;
                    
                    // data node berikutnya
                    new->next = NULL;
                    
                    // Menambahkan node baru ke linked list penyederhanaan
                    insertNode(mintermGroupList, new);
                } 

                // Melanjutkan perbandingan ke node berikutnya
                temp2 = temp2->next;
            }
            
            // Melanjutkan perbandingan ke node berikutnya
            temp1 = temp1->next;
        }
        
        // Menambahkan minterm yang tidak disederhanakan
        temp1 = list->head;
        while(temp1!=NULL){
            // Jika minterm implicant
            if(temp1->isImplicant==1){
                notSimplified = 1;
                // Mengalokasikan memori node baru
                Node* new = (Node*) malloc(sizeof(Node));
                
                // Mengisi data node baru
                // data minterm dalam desimal
                new->mintermDec = malloc(numMinterms*sizeof(int));
                new->mintermDec[0] = temp1->mintermDec[0]; ;
                // Menginisialisasi sisa array minterm dengan -1
                for(i=1; i<numMinterms; ++i){
                    new->mintermDec[i] = -1;
                }
                
                // data minterm dalam biner
                new->mintermBin = malloc(numVariables*sizeof(int));
                // Konversi dan simpan minterm dalam bentuk biner
                for(i=numVariables-1; i>=0; --i){
                    new->mintermBin[i] = temp1->mintermBin[i];      
                }
                
                // data jumlah bit 1
                new->numOnes = temp1->numOnes;
                
                // data indikator implicant, asumsi setiap minterm adalah implicant
                new->isImplicant = 1;
                
                // data node berikutnya
                new->next = NULL;
                
                // Menambahkan node baru ke linked list minterm
                insertNode(mintermGroupList, new);
            }
            
            // Melanjutkan pengisian node berikutnya
            temp1 = temp1->next;
        }
        
        // Jika mintermGroupList terisi
        if(simplified||notSimplified){
            // Mengubah linked list minterm menjadi linked list hasil penyederhanaan
            list->head = mintermGroupList->head;
            
            // Menampilkan tabel hasil penyederhanaan
            displayImplicant(list, numVariables);
        }
    }
    
    return;
}

void deleteDuplicate(LinkedList* list, int numVariables){
    int i;
    int same;   // variabel penanda dua prime implicant sama
    
    // Membuat pointer sementara untuk menyusuri linked list
    Node* temp = list->head;
    
    // Menyusuri linked list
    while((temp!=NULL)&&(temp->next!=NULL)){   
        // Menginisialisasi penanda
        same = 1;
        
        // Melakukan perbandingan antar tiap bit
        for(i=0; i<numVariables; ++i){
            // Jika terdapat bit yang berbeda
            if((temp->mintermBin[i])!=(temp->next->mintermBin[i])){
                // Mengubah penanda
                same = 0;
            }
        }
        
        // Jika kedua prime implicant sama
        if(same){
            // Lewati prime implicant yang sama
            temp->next = temp->next->next;
        }

        // Melanjutkan perbandingan ke node berikutnya        
        temp = temp->next;
    }
    
    // Menampilkan tabel hasil penyederhanaan
    displayImplicant(list, numVariables);
    
    return;
}

int countPrimeImplicant(LinkedList* list){
    int count = 0;  // variabel penyimpan jumlah prime implicant
    
    // Membuat pointer sementara untuk menyusuri linked list
    Node* temp = list->head;
    
    // Menyusuri linked list
    while(temp!=NULL){        
        // Menambah jumlah prime implicant
        count += 1;
        
        // Melanjutkan perbandingan ke node berikutnya        
        temp = temp->next;
    }
    
    return count;
}

void fillPrimeImplicant(LinkedList* list, int numMinterms, int numVariables, int* arrayMinterm, int* arrayPrimeImplicant){
    int i=0;
    int j;
    int k;
    
    // Membuat pointer sementara untuk menyusuri linked list
    Node* temp = list->head;
    
    // Menyusuri linked list
    while(temp!=NULL){
        // Mengisi matriks prime implicant 
        j = 0;
        while((temp->mintermDec[j]!=-1)&&(j<(numVariables*numVariables))){
            k = 0;
            while(temp->mintermDec[j]!=arrayMinterm[k]){
                k += 1;
            }
            arrayPrimeImplicant[i*numMinterms+k] = 1;
        
            j += 1;
        }
        i += 1;
    
        // Melanjutkan perbandingan ke node berikutnya        
        temp = temp->next;
    }
    
    return;
}

void displayPrimeImplicant(LinkedList* list, int numMinterms, int numVariables, int* arrayMinterm, int* arrayPrimeImplicant){
    int i;
    int j;
    int k=0;
    
    // Membuat pointer sementara untuk menyusuri linked list
    Node* temp = list->head;
    
    // Mencetak minterm dalam desimal
    printf("  ");
    for(i=0; i<numMinterms; ++i){
        printf("%d\t", arrayMinterm[i]);
    }
    printf("|");
    
    // Mencetak judul tabel
    printf("\tMinterms\n");
    
    for(i=0; i<numMinterms*11; ++i){
        printf("=");
    }
    printf("\n");
    
    // Menyusuri linked list
    while(temp!=NULL){
        // Mencetak minterm di dalam prime implicant
        printf("  ");
        for(i=0; i<numMinterms; ++i){
            if(arrayPrimeImplicant[k*numMinterms+i]==1){
                printf("X\t");
            } else{
                printf(" \t");
            }
        }
        printf("|\t");
        
        // Mencetak prime implicant
        printf("%d", temp->mintermDec[0]);
        i = 1;
        while((temp->mintermDec[i]!=-1)&&(i<(numVariables*numVariables))){
            printf(",%d", temp->mintermDec[i]);
            i += 1;
        }
        
        printf("\n");
        
        k += 1;
        
        // Melanjutkan perbandingan ke node berikutnya        
        temp = temp->next;
    }
     for(i=0; i<numMinterms*7; ++i){
        printf("=");
    }
    printf("\n");
    
    return;
}

void findEssential(LinkedList* list, int numMinterms, int numPrimeImplicant, int* arrayPrimeImplicant){
    int i=0;
    int j;
    int k;
    int count;
    int isEssential;
    
    // Membuat pointer sementara untuk menyusuri linked list
    Node* temp = list->head;
    
    // Menyusuri linked list
    while(temp!=NULL){
        isEssential = 0;
        // cek semua baris
        for(j=0; j<numMinterms; ++j){
            count = 0;
            // jika ada isi 1, cek kolom
            if(arrayPrimeImplicant[i*numMinterms+j]==1){
                for(k=0; k<numPrimeImplicant; ++k){
                    if(arrayPrimeImplicant[k*numMinterms+j]==1){
                        count += 1;
                    }
                }
                
                // kalau dalam satu kolom hanya ada 1 bit 1, prime implicant adalah essential
                if(count==1){
                        temp->isImplicant = 1;
                    }
            }
        }
        
        i += 1;
        
        // Melanjutkan perbandingan ke node berikutnya        
        temp = temp->next;
    }
    
    return;
}

void printResult(LinkedList* list, int numVariables){
    int i;
    
    // Membuat pointer sementara untuk menyusuri linked list
    Node* temp = list->head;
    
    // Menyusuri linked list
    while(temp!=NULL){
        // Jika prime implicant adalah essential
        if(temp->isImplicant==1){
            for(i=0; i<numVariables; ++i){
                if(temp->mintermBin[i]==1){
                    printf("%c", (char)91-(numVariables-i));
                } else if(temp->mintermBin[i]==0){
                    printf("%c'", (char)91-(numVariables-i));
                }
            }
            
            if(temp->next!=NULL){
                printf(" + ");
            }
        }            
        
        // Melanjutkan perbandingan ke node berikutnya        
        temp = temp->next;
    }
    
    printf("\n");
    
    return;
}

int main()
{
    int i;
    int j;
    int numVariables;           // variabel penyimpan jumlah variabel
    int numMinterms=0;            // variabel penyimpan jumlah minterm
    
    int* binary;                // array hasil konversi desimal ke biner
    int result;                 // variabel penyimpan input hasil truth table
    int* arrayResult;           // array penyimpan semua input hasil truth table
    
    int minterm;                // variabel penyimpan minterm input
    int* arrayMinterm;          // array penyimpan semua minterm input
    int numPrimeImplicant;      // variabel penyimpan jumlah prime implicant
    int* arrayPrimeImplicant;   // matriks penyimpan semua prime implicant dan mintermnya    
    
    // Meminta input data
    printf("\nEnter the number of variables : ");       
    scanf("%d",&numVariables);
    
    // Mengalokasikan memori array biner
    binary = malloc(numVariables*sizeof(int));
    
    // Mengalokasikan memori array result
    arrayResult = malloc(pow(2,numVariables)*sizeof(int));
    
    // Membuat linked list untuk menyimpan minterm
    LinkedList* mintermList = (LinkedList*) malloc(sizeof(LinkedList));
    mintermList->head = NULL;
    
    // Menampilkan judul tabel
    // menampilkan variabel
    for(i=0; i<numVariables; ++i){
        printf("%c ", (char)91-(numVariables-i));
    }
    printf("| f");
    printf("\n");
    
    // menampilkan pembatas
    for(i=0; i<numVariables*2+3; ++i){
        printf("=");
    }
    printf("\n");
    
    for(i=0; i<pow(2,numVariables); ++i){
        int minterm = i;
        for(j=numVariables-1; j>=0; --j){
            binary[j] = minterm%2;
            minterm = minterm/2;        
        }
        
        for(j=0; j<numVariables; ++j){
            printf("%d ", binary[j]);
        }
        printf("| ");
        
        scanf("%d", &result);
        arrayResult[i] = result;
        
        if(result){
            numMinterms += 1;
        }
    }
    printf("\n");
    
    if(numMinterms==pow(2,numVariables)){
        printf("Hasil Akhir Penyederhanaan\n");
        printf("1\n");
        
        return 0;
    } else if(numMinterms==0){
        printf("Hasil Akhir Penyederhanaan\n");
        printf("0\n");
        
        return 0;
    }
    
    // Meminta input minterm dalam desimal
    // asumsi input terurut dari minterm terkecil
    arrayMinterm =  malloc(numMinterms*sizeof(int));
    j =0;
    for(i=0; i<pow(2,numVariables); ++i){
        if(arrayResult[i]){
            
            // Menyimpan minterm ke array
            arrayMinterm[j] = i;
            
            // Menyimpan minterm ke mintermList
            saveMinterm(mintermList, numMinterms, numVariables, i);
            
            j += 1;
        }
    }
    
    // debugging
    printf("---------------------Setelah saveMinterm---------------------\n");
    printLinkedList(mintermList, numVariables);
    
    // Mengurutkan mintermList berdasarkan jumlah bit 1 minterm dalam biner
    groupByOnes(mintermList, numVariables);
    
    // Menampilkan tabel minterm sebelum penyederhanaan
    displayImplicant(mintermList, numVariables);
    
    // Melakukan penyederhanaan dengan Quine-McCluskey Tabular Method
    minimize(mintermList, numMinterms, numVariables);
       
    // Menghapus prime implicant duplikat
    deleteDuplicate(mintermList, numVariables);
    
    // Menghitung jumlah prime implicant
    numPrimeImplicant = countPrimeImplicant(mintermList);
    
    // Mengisi tabel prime implicant
    arrayPrimeImplicant = malloc(numMinterms*numPrimeImplicant*sizeof(int));
    fillPrimeImplicant(mintermList, numMinterms, numVariables, arrayMinterm, arrayPrimeImplicant);
    
    // Menampilkan tabel prime implicant
    displayPrimeImplicant(mintermList, numMinterms, numVariables, arrayMinterm, arrayPrimeImplicant);
    
    // Mencari essential prime implicant
    findEssential(mintermList, numMinterms, numPrimeImplicant, arrayPrimeImplicant);
    
    // Mencetak hasil akhir penyederhanaan
    printResult(mintermList, numVariables);
    
    return 0;
    
}