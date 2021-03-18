//Zadanie2 - Angry Rockets
#include <stdbool.h>
#include <stdio.h>
#define R_MAX 2147483647 // vsetky generovane cisla su mensie ako R_MAX
static long long unsigned int SEED = 0x1; // seed generatora

int funk_na_zotredenie(int pole[], int typ, int zostalo, int zmensi){
    do{
        zostalo = 0;
        for(int i=0;i<(typ-zmensi);i++){
            if(pole[i]>pole[i+1]){
                int temp = pole[i];
                pole[i]=pole[i+1];
                pole[i+1]=temp;
                zostalo = 1;
            }
        }
        zmensi++;
    }while(zostalo);
}

void srnd(int seed) {
    SEED = seed;
}

int rnd(int from, int to) {
    SEED = SEED * 16807 % R_MAX;
    return from + (int) SEED % (to - from + 1);
}

int main() {

    int seed;
    int n;
    int m1;
    int m2;
    int N_min=10;
    int N_max=100;


    scanf("%d %d %d %d", &seed, &n, &m1, &m2);

    if(seed<=0 || n<N_min || n> N_max || ((m1+m2)>(n/2)) ){
        return 1;
    }

    int zavodna_draha[n];

    for(int i=0;i<n;i++){
        zavodna_draha[i]=0;
    }

    srnd(seed);

    int pBooster=0;
    int pBlocker=0;
    int pozicia;
    int pozecieBlocker[m1];
    int pozecieBooster[m2];

    while(pBlocker!=m1){
        pozicia = rnd(1,n-1);
        if(zavodna_draha[pozicia-1]==0){
            zavodna_draha[pozicia-1]= 1;
            pozecieBlocker[pBlocker]= pozicia;
            pBlocker++;
        }else{
            do{
                pozicia = rnd(1,n-1);
            }while(zavodna_draha[pozicia-1]==1);
            zavodna_draha[pozicia-1]= 1;
            pozecieBlocker[pBlocker]= pozicia;
            pBlocker++;

        }
    }

    //bouble sort
    int zostalo;
    int zmensi= 1;
    funk_na_zotredenie(pozecieBlocker, pBlocker, zostalo, zmensi);

    while(pBooster!=m2){
        pozicia = rnd(1,n-1);
        if(zavodna_draha[pozicia-1]==0 && zavodna_draha[pozicia-1]!=1 && zavodna_draha[pozicia-1]!=2){
            zavodna_draha[pozicia-1]= 2;
            //printf("%d ", pozicia);
            pozecieBooster[pBooster]= pozicia;
            pBooster++;
        }else{
            do{
                pozicia = rnd(1,n-1);
            }while(zavodna_draha[pozicia-1]==1 || zavodna_draha[pozicia-1]==2);
            zavodna_draha[pozicia-1]= 2;
            pozecieBooster[pBooster]= pozicia;
            pBooster++;

        }
    }

    funk_na_zotredenie(pozecieBooster, pBooster, zostalo, zmensi);

    printf("BLOCK:");
    for(int i=0;i<pBlocker;i++){
        printf("%d ", pozecieBlocker[i]);
    }

    printf("\nBOOST:");
    for(int i=0;i<pBooster;i++){
        printf("%d ", pozecieBooster[i]);
    }






    return 0;
}
