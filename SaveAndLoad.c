//
// Created by Gireg Roussel on 06/10/2018.
//

#include "SaveAndLoad.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    double matrix[4][3] = { { 1.2 , 2.2 , 3.2 } , { 4.2 , 5.2 , 6.2} , { 1.2 , 2.2 , 3.2 } , { 4.2 , 5.2 , 6.2} };
    Save(4, 3, matrix);
    Load(4, 3);
    return 0;
}

/// This function will save a double array on a binary file.
/// \param Heigth
/// \param Weigth
/// \param Data
void Save(int Heigth, int Weigth, double Data[])
{
    FILE *fp;

    if ((fp = fopen("C:\\program.bin","wb")) == NULL){
        printf("Error! opening file");

        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    int LenMatrix = Weigth*Heigth;

    fwrite(&Heigth, sizeof(int), 1, fp);
    fwrite(&Weigth, sizeof(int), 1, fp);

    fwrite(&Data, sizeof(double), LenMatrix, fp);

    fclose(fp);
}


/// This function will load a binary file
/// \return An array of double.
int Load(int Heigth, int Weigth)
{
    FILE *fp;

    int buff;

    if ((fp = fopen("C:\\program.bin","rb")) == NULL){
        printf("Error! opening file");

        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    //int LenMatrix = Weigth*Heigth;

    fread(&Heigth, sizeof(int), 1, fp);

    printf("%i\n", buff);

    fread(&Weigth, sizeof(int), 1, fp);

    printf("%i\n", buff);

    //fread(&fp, sizeof(double), LenMatrix, fp);

    fclose(fp);
}