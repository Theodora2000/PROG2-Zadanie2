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

    srnd(seed);

    return 0;
}
