//
// Created by root on 05/10/18.
//

#include "Layer.h"

#ifndef OCR_NETWORK_H
#define OCR_NETWORK_H


typedef struct S_Network {
    int* nbLayers;
    int** sizeLayers;
    T_Layer** Layers;
} T_Network;


/// Manual creation of a neural network
/// \return Network following the user criteria
T_Network* CreateNetwork_Manual();


/// Print all the network related variables, including all of its layers and nodes.
/// \param network Pointer to the network to print.
void PrintAllNetworkInfos(T_Network* network);


/// Free the memory occupied by a network.
/// \param network Pointer to the network to delete.
void FreeNetwork(T_Network* network);


#endif //OCR_NETWORK_H
