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



    int poz1=-1;
    int poz2=-1;
    int bu1=0;
    int bu2=0;
    int blc1=0;
    int blc2=0;
    int R1;
    int R2;
    int d;
    int vytaz=0;
    int tah=1;
    int stara=0;
    int stara_boo=0;
    int stara_o=0;
    int stara_o_boo=0;



    while(1>0){
        R1 = rnd(1,6);
        R2= rnd(1,6);
        if(poz1==-1)
        {

            if(R1+R2>7)
            {
                poz1=0;
                stara=-1;
                d = R1+R2-7;
            }
            else
                {

                    d=0;
                    stara=poz1;

                }

        }
        else{

                if(poz1<poz2 && R1==6 && R2==6){
                    int temp = poz1;
                    poz1 = poz2;
                    temp = poz2;
                    d=0;
                }else if(poz1>poz2 && R1==1 && R2==1 && poz2>0 ){
                    int temp = poz2;
                    poz2 = poz1;
                    temp = poz1;
                    d=0;
                }else{
                    d = max(R1,R2);
                }

        }

        if(d>0){
            if(poz1==0)
            {
                poz1 = poz1+d+bu1;
            }
            else
            {
                stara= poz1;
                poz1 = stara+d+bu1;

            }

        }
        if(zavodna_draha[poz1]==2){
            stara_boo = bu1;
            bu1= stara_boo+1;
            zavodna_draha[poz1]=0;
        }
        if(zavodna_draha[poz1]==1){
            if(bu1>0){
                stara_boo = bu1;
                bu1= 0;
                stara=poz1;
            }else{

                poz1 = -1;
            }
            zavodna_draha[poz1]=0;
        }

        if(poz1==poz2){
            stara_o = poz2;
            poz2 = -1;
            stara_o_boo = bu2;

        }



        printf("\n[%d,1] [%d,%d] [%d,%d] [%d,%d]", tah, stara, stara_boo, R1, R2, poz1, bu1);
        stara_boo = bu1;
        if(poz1>=n)
            {
                vytaz=1;
                break;
            }
            tah++;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        R1 = rnd(1,6);
        R2= rnd(1,6);
        if(poz2==-1)
        {
            if(R1+R2>7)
            {
                poz2=0;
                stara_o=-1;
                d = R1+R2-7;
            }
            else
            {

                d=0;
                stara_o=poz2;
            }

        }

        else{

            if(poz2<poz1 && R1==6 && R2==6){
                int temp = poz2;
                poz2 = poz1;
                temp = poz1;
                d=0;
            }else if(poz2>poz1 && R1==1 && R2==1 && poz1>0 ){
                int temp = poz1;
                poz1 = poz2;
                temp = poz2;
                d=0;
            }else{
                d = max(R1,R2);
            }

        }

        if(d>0){
            if(poz2==0)
            {
                poz2 = poz2+d+bu2;
            }
            else
                {
                    stara_o= poz2;
                    poz2 = stara_o+d+bu2;

                }

        }
        if(poz2!=-1)
        {
            if(zavodna_draha[poz2]==2){
                stara_o_boo = bu2;
                bu2= stara_o_boo+1;
                zavodna_draha[poz2]=0;
            }
            if(zavodna_draha[poz2]==1){
                if(bu2>0){
                    stara_o_boo = bu2;
                    bu2= 0;
                    stara_o=poz2;
                }else{

                    poz2 = -1;
                }
                zavodna_draha[poz2]=0;
            }

            if(poz2==poz1){
                stara = poz1;
                poz1 = -1;
                stara_boo = bu1;

            }
        }



        printf("\n[%d,2] [%d,%d] [%d,%d] [%d,%d]", tah, stara_o, stara_o_boo, R1, R2, poz2, bu2);
        stara_o_boo = bu2;
        if(poz2>=n)
        {
            vytaz=2;
            break;
        }
        tah++;



    }






    return 0;
}
