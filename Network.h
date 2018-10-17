//
// Created by root on 05/10/18.
//

#include "Layer.h"
#include "Transition.h"

#ifndef OCR_NETWORK_H
#define OCR_NETWORK_H


typedef struct S_Network {
    int* nbLayers;
    int** sizeLayers;
    T_Layer** Layers;
    T_Transition** Transitions;
} T_Network;


/// Manual creation of a neural network
/// \return Network following the user criteria
T_Network* CreateNetwork_Manual();


/// Automatic creation of a neural network
/// \return Network following the specified arguments
T_Network* CreateNetwork_Auto(int* nbLayers, int** sizeLayers, int addBias);


/// Initialize all the network layers following already established variables.
/// \param network Pointer to the network to work on
void InitializeNetworkLayers(T_Network* network, int addBias);


/// Initialize all the network transitions following already established layers.
/// \param network Pointer to the network to work on
void InitializeNetworkTransitions(T_Network* network);


/// Print all the network related variables, including all of its layers and nodes.
/// \param network Pointer to the network to print.
void PrintAllNetworkInfos(T_Network* network);


/// Free the memory occupied by a network.
/// \param network Pointer to the network to delete.
void FreeNetwork(T_Network* network);


/// Set the network inputs according to the user criteria
/// \param network Pointer to the network to set
void SetNetworkInputs_Manual(T_Network* network);


/// Set the network inputs according to the given array.
/// \param network Pointer to the network to set
/// \param inputs Double array setting the value of the input layer
void SetNetworkInputs_Auto(T_Network* network, double* inputs);


/// Do a full propagation cycle, inputs needs to be set.
/// \param network Pointer to the network to run
void RunNetwork(T_Network* network);

#endif //OCR_NETWORK_H
