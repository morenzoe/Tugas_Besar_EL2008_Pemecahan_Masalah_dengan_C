#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 255

int countVar(char *equation){
    int i, j;
    int var = 0;
    int unique;
    
    //debug printf("%s\n", equation);
    
    // Memeriksa semua karakter dalam string equation
    for(i=0; i<strlen(equation); ++i){
        // Mengasumsikan karakter tersebut unik sebelum dibandingkan
        unique = 1;
        // Membandingkan karakter tersebut dengan karakter sebelumnya
        // Hanya membandingkan alfabet
        // A = 65, Z = 90, a = 97, z = 122
        //debug printf("%d\n",(int)equation[i]);
        if((((int)equation[i]>64)&&((int)equation[i]<91))||(((int)equation[i]>96)&&((int)equation[i]<123))){
            // Memeriksa karakter sebelumnya
            //debug printf("abjad\n");
            for(j=0; j<i; ++j){
                // Jika karakter sudah pernah ada sebelumnya, maka bukan karakter unik yang diinginkan
                // Jika karakter kapitalisasi sudah ada, maka bukan karakter unik yang diinginkan
                if((equation[j] == equation[i])||(abs((int)equation[j]-(int)equation[i])==32)){
                  unique = 0;
                  break;
                }
            }

        // Jika bukan alfabet, maka bukan karakter unik yang diinginkan
        } else{
            unique = 0;
        }
        
        // Jika unik, maka merupakan karakter unik yang diinginkan
        if(unique){
            var += 1;
        }
    }
    
    return var;
}

int main(){
    
    char eq[MAX_LEN];
    
    scanf("%s", eq);
    //debug printf("%s\n", eq);
    
    int var = countVar(eq);
    
    printf("%d\n", var);
    
    return 0;
}