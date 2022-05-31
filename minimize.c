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

#include "minimize.h"

int main()
{
    int i;                      // variabel iterasi
    int j;                      // variabel iterasi
    int numVariables=0;         // variabel penyimpan jumlah variabel, inisialisasi 0
    int numMinterms;            // variabel penyimpan jumlah minterm
    char input[MAX];            // variabel untuk menyimpan input pengguna
    
    int* binary;                // array hasil konversi desimal ke biner
    int result;                 // variabel penyimpan input hasil truth table
    int* arrayResult;           // array penyimpan semua input hasil truth table
    int tableOK=0;              // variabel indikator truth table sudah benar, inisialisasi 0
    
    int minterm;                // variabel penyimpan minterm input
    int* arrayMinterm;          // array penyimpan semua minterm input
    int numPrimeImplicant;      // variabel penyimpan jumlah prime implicant
    int* arrayPrimeImplicant;   // matriks penyimpan semua prime implicant dan mintermnya    
    
    // Mencetak informasi awal
    red();
    printf("Selamat datang di Algebra Boolean Calculator!\n\n");
    reset();
    printf("Program ini dapat menyederhanakan\n");
    printf("persamaan boolean dari input truth table\n\n");
    
    // Meminta input jumlah variabel   
    // valdasi input jumlah variabel
    do{
        printf("Jumlah variabel adalah integer yang\n");
        printf("lebih besar dari 0 dan kurang dari 27\n");
        printf("Masukkan jumlah variabel: ");
        fgets(input, MAX, stdin);
        
        // Jika input bukan integer
        if(!isInteger(input)){
            printf("Jumlah variabel harus integer.\n\n");
         
        // Jika input adalah integer
        } else if(isInteger(input)){
            numVariables = atoi(input);
            
            // Jika input terlalu besar
            if(numVariables>26){
                printf("Jumlah variabel terlalu besar.\n\n");
            
            // Jika input terlalu kecil
            } else if(numVariables<1){
                printf("Jumlah variabel terlalu kecil.\n\n");
            }
        }
    } while((numVariables<1)||(numVariables>26)); 
    
    // Mengalokasikan memori array biner
    binary = malloc(numVariables*sizeof(int));
    
    // Mengalokasikan memori array result
    arrayResult = malloc(pow(2,numVariables)*sizeof(int));
    
    // Membuat linked list untuk menyimpan minterm
    LinkedList* mintermList = (LinkedList*) malloc(sizeof(LinkedList));
    mintermList->head = NULL;
    
    // Meminta input truth table hingga benar
    while(1){
        // Inisialisasi jumlah minterm nol
        numMinterms = 0;
        
        // Menampilkan judul tabel
        // menampilkan variabel
        red();
        printf("\nTruth Table\n");
        reset();
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
        
        // meminta input hasil truth table
        for(i=0; i<pow(2,numVariables); ++i){
            
            // Mencetak input truth table
            minterm = i;
            
            // konversi integer menjadi biner
            for(j=numVariables-1; j>=0; --j){
                binary[j] = minterm%2;
                minterm = minterm/2;        
            }
            
            // mencetak input truth table dalam biner
            for(j=0; j<numVariables; ++j){
                printf("%d ", binary[j]);
            }
            printf("| ");
            
            // Meminta input
            fgets(input, MAX, stdin);
            
            // Validasi input
            // jika input bukan integer
            if(!isInteger(input)){
                printf("\nHasil truth table harus integer.\n");
                break;
         
            // jika input adalah integer
            } else if(isInteger(input)){
                result = atoi(input);
                
                if((result!=0)&&(result!=1)){
                    printf("\nHasil truth table harus 0 atau 1.\n");
                    break;
                }
            }
            
            // Menyimpan input
            arrayResult[i] = result;
            
            // Menambahkan jumlah minterm jika input sama dengan 1
            if(result){
                numMinterms += 1;
            }
            
            // Jika tabel sudah terisi penuh,
            if(i==pow(2,numVariables)-1){
                // ubah nilai indikator
                tableOK = 1;
            }
        }
        
        // Jika tabel sudah terisi dengan benar, 
        if(tableOK){
            // keluar dari while loop
            break;
        }
    }
    printf("\n");
    
    // Jika minterm sebanyak baris truth table
    if(numMinterms==pow(2,numVariables)){
        red();
        printf("Hasil Akhir Penyederhanaan\n");
        reset();
        printf("1\n");
        
        return 0;
        
    // Jika tidak ada minterm
    } else if(numMinterms==0){
        red();
        printf("Hasil Akhir Penyederhanaan\n");
        reset();
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
    
    // Mengurutkan mintermList berdasarkan jumlah bit 1 minterm dalam biner
    groupByOnes(mintermList, numVariables);
    
    // Menampilkan tabel minterm sebelum penyederhanaan
    red();
    printf("Tabel Hasil Pengelompokkan\n");
    reset();
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
    red();
    printf("Tabel Implikan Prima\n");
    reset();
    displayPrimeImplicant(mintermList, numMinterms, numVariables, arrayMinterm, arrayPrimeImplicant);
    
    // Mencari essential prime implicant
    findEssential(mintermList, numMinterms, numPrimeImplicant, arrayPrimeImplicant);
    
    // Mencetak hasil akhir penyederhanaan
    red();
    printf("\nHasil Akhir Penyederhanaan\n");
    reset();
    printResult(mintermList, numVariables);
    
    return 0;
    
}

void red()
{
  // Mengatur warna font command line menjadi merah
  printf("\033[1;31m");
  
  return;
}

void reset()
{
  // Mengatur warna font command line menjadi default
  printf("\033[0m");
  
  return;
}

int isInteger(char* token)
{
    // Melakukan typecasting token menjadi float
    double asFloat = atof(token);
    // Melakukan typecasting token dalam float menjadi integer
    int asInteger = (int)asFloat;
    
    // Jika token char
    if((asInteger==0)&&(*token!='0')){
        // Hasil atof() dari variabel char atau string mengembalikan 0
        // Sehingga, token adalah char atau string jika bukan hanya berisi 0
        return 0;
    // Jika token float
    } else if(asFloat!=asInteger){
        // Nilai token adalah bilangan desimal jika tidak sama dengan pembulatannya
        return 0;
    // Jika token integer
    } else{   
        return 1;
    }
}

int countOnes(Node* node, int numVariables)
{
    int i;          // variabel iterasi
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

void insertNode(LinkedList* list, Node* node)
{
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

void saveMinterm(LinkedList* list, int numMinterms, int numVariables, int minterm)
{
    int i;  // variabel iterasi
    
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

void groupByOnes(LinkedList* list, int numVariables)
{
    int i;      // variabel iterasi
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

void displayImplicant(LinkedList* list, int numVariables)
{
    int i;                                  // variabel iterasi
    int numGroup = list->head->numOnes;     // variabel nomor baris, inisialisasi jumlah bit 1 implicant pertama
    
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
    printf("==================================================\n\n");
    
    return;
}

void minimize(LinkedList* list, int numMinterms, int numVariables)
{
    int i;              // variabel iterasi
    int j;              // variabel iterasi
    int simplified;     // variabel penanda adanya implicant yang disederhanakan
    int notSimplified;  // variabel penanda adanya implicant yang tidak disederhanakan
    int idxChange;      // variabel indeks bit yang berubah
    int sumChange;      // variabel jumlah perubahan
    int step=1;         // variabel tahap penyederhanaan, inisialisasi 1
    
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
            red();
            printf("Tabel Penyederhanaan ke-%d\n", step);
            reset();
            displayImplicant(list, numVariables);
            
            // Menambahkan jumlah 
            step += 1;
        }
    }
    
    return;
}

void deleteDuplicate(LinkedList* list, int numVariables)
{
    int i;      // variabel iterasi
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
    red();
    printf("Tabel Hasil Penghapusan Duplikat\n");
    reset();
    displayImplicant(list, numVariables);
    
    return;
}

int countPrimeImplicant(LinkedList* list)
{
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

void fillPrimeImplicant(LinkedList* list, int numMinterms, int numVariables, int* arrayMinterm, int* arrayPrimeImplicant)
{
    int i=0;        // variabel indeks, inisialisasi 0
    int j;          // variabel indeks
    int k;          // variabel indeks
    
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

void displayPrimeImplicant(LinkedList* list, int numMinterms, int numVariables, int* arrayMinterm, int* arrayPrimeImplicant)
{
    int i;      // variabel iterasi
    int j;      // variabel iterasi  
    
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
    
    // Mencetak pembatas tabel
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
        
        // Melanjutkan perbandingan ke node berikutnya        
        temp = temp->next;
    }
    
    // Mencetak pembatas tabel
    for(i=0; i<numMinterms*11; ++i){
        printf("=");
    }
    printf("\n");
    
    return;
}

void findEssential(LinkedList* list, int numMinterms, int numPrimeImplicant, int* arrayPrimeImplicant)
{
    int i=0;            // variabel indeks, inisialisasi 0
    int j;              // variabel indeks
    int k;              // variabel indeks
    int count;          // variabel jumlah minterm yang ditangani suatu prime implicant
    int isEssential;    // variabel indikator apakah suatu prime implicant esensial
    
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
        
        // Menambahkan indeks
        i += 1;
        
        // Melanjutkan perbandingan ke node berikutnya        
        temp = temp->next;
    }
    
    return;
}

void printResult(LinkedList* list, int numVariables)
{
    int i;  // variabel iterasi
    
    // Membuat pointer sementara untuk menyusuri linked list
    Node* temp = list->head;
    
    // Menyusuri linked list
    while(temp!=NULL){
        // Jika prime implicant adalah essential
        if(temp->isImplicant==1){
            // Menampilkan minterm dalam huruf variabel
            for(i=0; i<numVariables; ++i){
                if(temp->mintermBin[i]==1){
                    printf("%c", (char)91-(numVariables-i));
                } else if(temp->mintermBin[i]==0){
                    printf("%c'", (char)91-(numVariables-i));
                }
            }
            
            // Menampilkan tanda tambah diantara minterm
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