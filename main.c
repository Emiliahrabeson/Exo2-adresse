#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "proto.h"

int main() 
{
    int reseau;
    int n;
    char adresse[100];
    entrer(adresse);
    reseau = bit();
    separer(adresse, reseau);
    machine(reseau); 
    n = dec ();
    decoupe(n, reseau);
    return 0;
}
