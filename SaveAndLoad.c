//
// Created by Gireg Roussel on 06/10/2018.
//

#include "SaveAndLoad.h"
#include <stdio.h>
#include <stdlib.h>

/// This function will save a double array on a binary file.
/// \param Heigth
/// \param Weigth
/// \param Data , double[]data
void Save(int nbLayers, int sizeLayers)
{
    FILE *fp;

    if ((fp = fopen("../SaveConnections.bin","wb")) == NULL)
    {
        printf("Error! opening file");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }
    fwrite(&nbLayers, sizeof(int), 1, fp);
    fwrite(&sizeLayers, sizeof(int), 1, fp);

    //fwrite(&Data, sizeof(double), LenMatrix, fp);

    fclose(fp);
}


/// This function will load a binary file
/// \return An array of double.
int Load(int Heigth, int Weigth)
{
    FILE *fp;

    if ((fp = fopen("../SaveConnections.bin","rb")) == NULL)
    {
        printf("Error! opening file");

        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    fread(&Heigth, sizeof(int), 1, fp);
    printf("%i\n", Heigth);

    fread(&Weigth, sizeof(int), 1, fp);
    printf("%i\n", Weigth);

    //fread(&fp, sizeof(double), LenMatrix, fp);

    fclose(fp);
}