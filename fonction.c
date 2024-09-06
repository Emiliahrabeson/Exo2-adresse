#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "proto.h"

int dec ()
{
    int n=1;
    printf("\nEntrer le nombre de découpe : ");
    scanf("%d", &n);
    return n;
}
void entrer(char adresse[100]) 
{
    printf("CIDR : vous allez entrer un CIDR x.x.x.x/a\n\n");
    printf("Avec a le nombre de bit pur le réseau et x.x.x.x l'adresse IP.\n\nOKEY");
    printf("\n\nEntrer une adresse IP : ");
    scanf("%s", adresse);
}

int bit() 
{
    int reseau;
    printf("\nEntrer le nombre de bits pour le réseau : ");
    scanf("%d", &reseau);
    return reseau;
}

void separer(char adresse[100], int reseau) 
{
    int i = 0;
    int chiffre1, chiffre2, chiffre3, chiffre4;
    char *token = strtok(adresse, ".");

    if (token != NULL) 
    {
        chiffre1 = atoi(token);
        i++;
    }

    token = strtok(NULL, ".");
    if (token != NULL) 
    {
        chiffre2 = atoi(token);
        i++;
    }

    token = strtok(NULL, ".");
    if (token != NULL) 
    {
        chiffre3 = atoi(token);
        i++;
    }

    token = strtok(NULL, ".");
    if (token != NULL) 
    {
        chiffre4 = atoi(token);
        i++;
    }

    if (i != 4 || chiffre1 > 255 || chiffre2 > 255 || chiffre3 > 255 || chiffre4 > 255) 
    {
        printf("Ce n'est pas une adresse IP valide !");
        exit(1);
    }

    msr(adresse, reseau, chiffre1, chiffre2, chiffre3, chiffre4);
    ad_broadcast(chiffre1, chiffre2, chiffre3, chiffre4, reseau);
}

void ad_broadcast(int chiffre1, int chiffre2, int chiffre3, int chiffre4, int reseau)
{
    int ip_bin[32];
    int masque_inverse[32];
    int broadcast_bin[32];
    binaire_inverse(reseau, masque_inverse);

    decimal(chiffre1, &ip_bin[0]);
    decimal(chiffre2, &ip_bin[8]);
    decimal(chiffre3, &ip_bin[16]);
    decimal(chiffre4, &ip_bin[24]);

    for (int i = 0; i < 32; i++) 
    {
        broadcast_bin[i] = ip_bin[i] | masque_inverse[i];
    }

    int broadcast1 = binaire(&broadcast_bin[0]);
    int broadcast2 = binaire(&broadcast_bin[8]);
    int broadcast3 = binaire(&broadcast_bin[16]);
    int broadcast4 = binaire(&broadcast_bin[24]);

    printf("\nAdresse de broadcast : %d.%d.%d.%d\n", broadcast1, broadcast2, broadcast3, broadcast4);
}

void binaire_inverse(int sous_reseau, int *chaine1) 
{   
    for (int i = 0; i < 32; i++) 
    {   
        chaine1[i] = (i < sous_reseau) ? 1 : 0;
    }
}

void adresse_reseau(int chiffre1, int chiffre2, int chiffre3, int chiffre4, char bin1[9], char bin2[9], char bin3[9], char bin4[9]) 
{
    int ip1[8], ip2[8], ip3[8], ip4[8];
    int masque1[8], masque2[8], masque3[8], masque4[8];

    decimal(chiffre1, ip1);
    decimal(chiffre2, ip2);
    decimal(chiffre3, ip3);
    decimal(chiffre4, ip4);

    char_int(bin1, masque1);
    char_int(bin2, masque2);
    char_int(bin3, masque3);
    char_int(bin4, masque4);

    for (int i = 0; i < 8; i++) {
        masque1[i] = (ip1[i] & masque1[i]);
        masque2[i] = (ip2[i] & masque2[i]);
        masque3[i] = (ip3[i] & masque3[i]);
        masque4[i] = (ip4[i] & masque4[i]);
    }

    int dec_res1 = binaire(masque1);
    int dec_res2 = binaire(masque2);
    int dec_res3 = binaire(masque3);
    int dec_res4 = binaire(masque4);

    printf("\n\nAdresse réseau : %d.%d.%d.%d\n", dec_res1, dec_res2, dec_res3, dec_res4);
}

void msr(char adresse[100], int reseau, int chiffre1, int chiffre2, int chiffre3, int chiffre4) 
{
    char masque_bin[36] = "";
    int j = 0;
    char bin1[9], bin2[9], bin3[9], bin4[9];

    for (int i = 0; i < 32; i++) 
    {
        if (i > 0 && i % 8 == 0) 
        {
            masque_bin[j++] = '.';
        }
        masque_bin[j++] = (i < reseau) ? '1' : '0';
    }
    masque_bin[j] = '\0';
    printf("\n\nMasque de sous-réseau : %s", masque_bin);
    sscanf(masque_bin, "%8s.%8s.%8s.%8s", bin1, bin2, bin3, bin4);

    int msr1[8], msr2[8], msr3[8], msr4[8];
    for (int a = 0; a < 8; a++) 
    {
        msr1[a] = bin1[a] - '0';
        msr2[a] = bin2[a] - '0';
        msr3[a] = bin3[a] - '0';
        msr4[a] = bin4[a] - '0';
    }

    int dec1 = binaire(msr1);
    int dec2 = binaire(msr2);
    int dec3 = binaire(msr3);
    int dec4 = binaire(msr4);

    printf("\n\nMasque de sous-réseau : %d.%d.%d.%d\n", dec1, dec2, dec3, dec4);

    adresse_reseau(chiffre1, chiffre2, chiffre3, chiffre4, bin1, bin2, bin3, bin4);
}

void decimal(int x, int *chaine) 
{
    int puissances_de_2[8] = {128, 64, 32, 16, 8, 4, 2, 1};
    for (int i = 0; i < 8; i++) 
    {
        if (x / puissances_de_2[i] % 2 == 1) 
        {
            chaine[i] = 1;
        }
        else 
        {
            chaine[i] = 0;
        }
    }
}

int binaire(int *tab) 
{
    int s = 0;
    int puissances_de_2[8] = {128, 64, 32, 16, 8, 4, 2, 1};

    for (int i = 0; i < 8; i++) 
    {
        if (tab[i] == 1) 
        {
            s += puissances_de_2[i];
        }
    }
    return s;
}

void char_int(char *chaine, int tableau[8]) 
{
    for (int i = 0; i < 8; i++) 
    {
        tableau[i] = chaine[i] - '0';
    }
}


void decoupe(int n, int reseau) 
{
    int sous_reseau = 0;
    int temp = 1;

    while (temp < n) 
    {
        temp *= 2;
        sous_reseau++;
    }

    int total_bit = reseau + sous_reseau;
    int nb_sreseaux = pow(2, sous_reseau);
    int a = pow(2, 32 - total_bit);

    for (int i = 0; i < n; i++) 
    {
        int avant = i * a;
        int apres = avant + a - 1;

        int reseau1 = avant / (256 * 256 * 256);
        int reseau2 = (avant % (256 * 256 * 256)) / (256 * 256);
        int reseau3 = (avant % (256 * 256)) / 256;
        int reseau4 = avant % 256;

        int broadcast1 = apres / (256 * 256 * 256);
        int broadcast2 = (apres % (256 * 256 * 256)) / (256 * 256);
        int broadcast3 = (apres% (256 * 256)) / 256;
        int broadcast4 = apres % 256;

        printf("\nDécoupe %d :\n  Adresse réseau : %d.%d.%d.%d\n  Adresse de broadcast : %d.%d.%d.%d\n",
            i + 1, reseau1, reseau2, reseau3, reseau4, broadcast1, broadcast2, broadcast3, broadcast4);
    }
}
void machine(int reseau) 
{
    int bits_host = 32 - reseau;
    int result = (int)pow(2, bits_host) - 2;
    printf("Nombre de machines connectées : %d\n", result);
}
