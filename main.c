//Zadanie2 - Angry Rockets
#include <stdbool.h>
#include <stdio.h>
#define pMAX 100
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

int max(int num1, int num2)
{
    return (num1 > num2 ) ? num1 : num2;
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
        if(zavodna_draha[pozicia]==0){
            zavodna_draha[pozicia]= 1;
            pozecieBlocker[pBlocker]= pozicia;
            pBlocker++;
        }else{
            do{
                pozicia = rnd(1,n-1);
            }while(zavodna_draha[pozicia]==1);
            zavodna_draha[pozicia]= 1;
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
        if(zavodna_draha[pozicia]==0 && zavodna_draha[pozicia]!=1 && zavodna_draha[pozicia]!=2){
            zavodna_draha[pozicia]= 2;
            //printf("%d ", pozicia);
            pozecieBooster[pBooster]= pozicia;
            pBooster++;
        }else{
            do{
                pozicia = rnd(1,n-1);
            }while(zavodna_draha[pozicia]==1 || zavodna_draha[pozicia]==2);
            zavodna_draha[pozicia]= 2;
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
    printf("\n");
    for(int i=0;i<n;i++){
        printf("%d ", zavodna_draha[i]);
    }

    int hrac_1=1;
    int hrac_2=2;
    int hrac1[pMAX]={-1};
    int p_h1=0;
    int hrac2[pMAX]={-1};
    int p_h2=0;
    int booster1[pMAX]={0};
    int p_b1=0;
    int pocet_nazbieranych_b1=0;
    int booster2[pMAX]={0};
    int p_b2=0;
    int pocet_nazbieranych_b2=0;
    int tah=1;
    int R1=0;
    int R2=0;
    int d=0;
for(int i=0;i<12;i++){
    if(tah%2==1){
        R1= rnd(1,6);
        R2=rnd(1,6);

        if(hrac1[p_h1]==-1 && ((R1+R2>7))){
            p_h1++;
            hrac1[p_h1]=zavodna_draha[0];
            d=(R1+R2-7);
        }else{
            p_h1++;
            hrac1[p_h1]=hrac1[p_h1-1];
        }

        if((hrac1[p_h1]>0 && hrac1[p_h1]<n-1)) {
            if ((hrac1[p_h1] < hrac2[p_h2]) && (hrac2[p_h2] > 0 && hrac2[p_h2] < n - 1) && (R1 == R2 == 6)) {
                p_h1++;
                p_h2++;
                hrac1[p_h1] = hrac1[p_h1 - 1];
                hrac2[p_h2] = hrac2[p_h2 - 1];
                int temp = hrac1[p_h1];
                hrac1[p_h1] = hrac2[p_h2];
                hrac2[p_h2]=temp;
                d = 0;
            } else if ((hrac1[p_h1] > hrac2[p_h2]) && (hrac2[p_h2] > 0 && hrac2[p_h2] < n - 1) && (R1 == R2 == 1)) {
                p_h1++;
                p_h2++;
                hrac1[p_h1] = hrac1[p_h1 - 1];
                hrac2[p_h2] = hrac2[p_h2 - 1];
                int temp = hrac1[p_h1];
                hrac1[p_h1] = hrac2[p_h2];
                hrac2[p_h2]=temp;
                d = 0;
            } else {
                d = max(R1, R2);

            }
        }



        if(d>0){
            p_h1++;
            hrac1[p_h1]=hrac1[p_h1-1]+d+booster1[p_b1];
        }

        if(zavodna_draha[hrac1[p_h1]]==2){
            pocet_nazbieranych_b1++;
            p_b1++;
            booster1[p_b1]= pocet_nazbieranych_b1;
            zavodna_draha[hrac1[p_h1]]=0;
        }
        /*else if(zavodna_draha[hrac1[p_h1]]==1){
            if(booster1[p_b1]>0){
                //p_b1++;
                //pocet_nazbieranych_b1=0;
                booster1[p_b1++]=0;
                hrac1[p_b1++]=zavodna_draha[hrac1[p_h1-1]];
            }else{
                hrac1[p_h1++]=-1;
            }
        }

*/      if(tah==1 && p_h1==2){
            printf("\n[%d,%d] [%d,%d] [%d,%d] [%d,%d]", tah, hrac_1, hrac1[0], booster1[p_b1-1], R1, R2, hrac1[p_h1], booster1[p_b1] );

        }else{

            printf("\n[%d,%d] [%d,%d] [%d,%d] [%d,%d]", tah, hrac_1, hrac1[p_h1-1], booster1[p_b1-1], R1, R2, hrac1[p_h1], booster1[p_b1] );

        }
        if(hrac1[p_h1]>n){
            break;
        }
    }else{
        d=0;
        R1= rnd(1,6);
        R2=rnd(1,6);

        if(hrac2[p_h2]==-1 && ((R1+R2>7))){
            p_h2++;
            hrac2[p_h2]=zavodna_draha[0];
            d=(R1+R2-7);
        }else{
            p_h2++;
            hrac2[p_h2]=hrac2[p_h2-1];
            //printf("\n%d",hrac2[p_h2]);
        }

        if((hrac2[p_h2]>0 && hrac2[p_h2]<n-1)) {
            if ((hrac2[p_h2] < hrac1[p_h1]) && (hrac1[p_h1] > 0 && hrac1[p_h1] < n - 1) && (R1 == R2 == 6)) {
                p_h1++;
                p_h2++;
                hrac1[p_h1] = hrac1[p_h1 - 1];
                hrac2[p_h2] = hrac2[p_h2 - 1];

                int temp = hrac2[p_h2];
                hrac2[p_h2] = hrac1[p_h1];
                hrac1[p_h1]=temp;
                d = 0;
            } else if ((hrac2[p_h2] > hrac1[p_h1]) && (hrac1[p_h1] > 0 && hrac1[p_h1] < n - 1) && (R1 == R2 == 1)) {
                p_h1++;
                p_h2++;
                hrac1[p_h1] = hrac1[p_h1 - 1];
                hrac2[p_h2] = hrac2[p_h2 - 1];
                int temp = hrac2[p_h2];
                hrac2[p_h2] = hrac1[p_h1];
                hrac1[p_h1]=temp;
                d = 0;
            } else {
                d = max(R1, R2);

            }
        }


        if(d>0){

            p_h2++;

            hrac2[p_h2]=hrac2[p_h2-1]+d+booster2[p_b2];


        }

        if(zavodna_draha[hrac2[p_h2]]==2){
            p_b2++;
            pocet_nazbieranych_b2++;
            booster2[p_b2]= pocet_nazbieranych_b2;
            zavodna_draha[hrac2[p_h2]]==0;
        }
        /*else if(zavodna_draha[hrac1[p_h1]]==1){
            if(booster1[p_b1]>0){
                //p_b1++;
                //pocet_nazbieranych_b1=0;
                booster1[p_b1++]=0;
                hrac1[p_b1++]=zavodna_draha[hrac1[p_h1-1]];
            }else{
                hrac1[p_h1++]=-1;
            }
        }

*/

        if(tah==2 && p_h2==2){
            printf("\n[%d,%d] [%d,%d] [%d,%d] [%d,%d]", tah, hrac_2, hrac2[0], booster2[p_b2-1], R1, R2, hrac2[p_h2], booster2[p_b2] );

        }else{
            printf("\n[%d,%d] [%d,%d] [%d,%d] [%d,%d]", tah, hrac_2, hrac2[p_h2-1], booster2[p_b2-1], R1, R2, hrac2[p_h2], booster2[p_b2] );

        }

    }
    if(hrac2[p_h2]>n){
        break;
    }




    tah++;
}
    for(int i=0;i<n;i++){
        printf("%d ", zavodna_draha[i]);
    }
    return 0;
}
