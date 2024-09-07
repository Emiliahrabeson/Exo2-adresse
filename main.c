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
    int chiffre1, chiffre2, chiffre3, chiffre4;  

    entrer(adresse);            
    reseau = bit();             

    separer(adresse, reseau, &chiffre1, &chiffre2, &chiffre3, &chiffre4);

    machine(reseau);            
    n = dec();                  
    
   decoupe(n, reseau, chiffre1, chiffre2, chiffre3, chiffre4);

    return 0;
}
