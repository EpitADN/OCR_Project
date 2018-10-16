//
// Created by Gireg Roussel on 06/10/2018.
//

#include "SaveAndLoad.h"

#include <string.h>

/// This function will save a double array on a binary file.
/// \param Heigth
/// \param Weigth
/// \param Data , double[]data

void SaveNetwork(T_Network* network)
{
    FILE *fp;

    /*char *path = malloc(strlen(directory)+strlen(name)+1);

    if (path == NULL)
    {
        printf("Malloc impossible");
        exit(1);
    }

    strcat(path, directory);
    strcat(path, name);
*/
    if ((fp = fopen("../SaveConnections.bin","wb")) == NULL)
    {
        printf("Error! opening file");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    printf("Gireg");

    SaveNetworkInfo(network->nbLayers, network->sizeLayers, fp);
    //SaveTransitions(network->nbLayers, network->Transitions, fp);

    fclose(fp);
}

void SaveNetworkInfo(int* nbLayers, int** sizeLayers, FILE* fp)
{
    fwrite(nbLayers, sizeof(int), 1, fp);
    for (int i = 0; i < *nbLayers; ++i)
        fwrite(sizeLayers[i], sizeof(int), 1, fp);
}

void SaveTransitions(int* nbLayers, T_Transition** transitions, FILE* fp)
{
    for (int i = 0; i < *nbLayers-1; ++i)
    {
        SaveTransition(transitions[i], fp);
    }
}

void SaveTransition(T_Transition* transition, FILE* fp)
{
    double** matrix = transition->Matrix;

    for (int i = 0; i < transition->height; ++i)
    {
        for (int j = 0; j < transition->width; ++j)
        {
            fwrite(&matrix[i][j], sizeof(double), 1, fp);
        }
    }
}

/// This function will load a binary file
/// \return An array of double.
T_Network* LoadNetwork()
{
    FILE *fp;

/*    char *path = malloc(strlen(directory)+strlen(name)+1);

    if (path == NULL)
    {
        printf("Malloc impossible");
        exit(1);
    }

    strcat(path, directory);
    strcat(path, name);
*/
    if ((fp = fopen("../SaveConnections.bin","rb")) == NULL)
    {
        printf("Error! opening file");

        // Program exits if the file pointer returns NULL.
        exit(1);
    }
    T_Network* network = LoadNetworkInfo(fp);
    //LoadNetworkTransitions(network, fp);

    fclose(fp);

    return network;
}

T_Network* LoadNetworkInfo(FILE* fp)
{
    int* nbLayers = malloc(sizeof(int));
    fread(nbLayers, sizeof(int), 1, fp);

    int** sizeLayers = malloc(*nbLayers * sizeof(int));
    for (int i = 0; i < *nbLayers; ++i)
        fread(sizeLayers[i], sizeof(int), 1, fp);

    return CreateNetwork_Auto(nbLayers, sizeLayers);
}

void LoadNetworkTransitions(T_Network* network, FILE* fp)
{
    for (int i = 0; i < *network->nbLayers-1; ++i)
    {
        LoadNetworkTransition(network->Transitions[i], fp);
    }
}

void LoadNetworkTransition(T_Transition* transition, FILE* fp)
{
    double** matrix = transition->Matrix;

    for (int i = 0; i < transition->height; ++i)
    {
        for (int j = 0; j < transition->width; ++j)
        {
            fread(&matrix[i][j], sizeof(double), 1, fp);
        }
    }
}