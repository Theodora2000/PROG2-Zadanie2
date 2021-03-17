//Zadanie2 - Angry Rockets

#include <stdio.h>
#define R_MAX 2147483647 // vsetky generovane cisla su mensie ako R_MAX
static long long unsigned int SEED = 0x1; // seed generatora



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


    while(pBlocker!=m1){
        pozicia = rnd(1,n-1);
        if(zavodna_draha[pozicia-1]==0){
            zavodna_draha[pozicia-1]= 1;
            //printf("%d ", pozicia);
            pozecieBlocker[pBlocker]= pozicia;
            pBlocker++;
        }else{
            do{
                pozicia = rnd(1,n-1);
                //printf("\npozicia %d\n", pozicia);
            }while(zavodna_draha[pozicia-1]==1);
            zavodna_draha[pozicia-1]= 1;
            //printf("%d ", pozicia);
            pozecieBlocker[pBlocker]= pozicia;
            pBlocker++;

        }
    }

    //sort
    for(int i=0;i<pBlocker-1;i++){
        for(int j=1;j<pBlocker;j++){
            if(i!=j){
            if(pozecieBlocker[i]>pozecieBlocker[j]){
                int temp = pozecieBlocker[i];
                pozecieBlocker[i]  = pozecieBlocker[j];
                pozecieBlocker[j] = temp;
            }
        }

        }
        printf("%d ", pozecieBlocker[i]);
    }

    return 0;
}
