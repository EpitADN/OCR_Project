//
// Created by root on 05/10/18.
//

#ifndef OCR_LAYER_H
#define OCR_LAYER_H

#include "Node.h"

typedef enum E_Position{
    FIRST,
    MIDDLE,
    LAST
} T_Position;


typedef struct S_Layer {
    T_Position position;
    int* nbNodes;
    T_Node** nodes;
} T_Layer;


/// Create a new layer with n nodes.
/// \param nbNodes number of nodes of the layer
/// \return New layer
T_Layer* InitializeLayer(T_Position position, int* nbNodes);


/// Free the memory occupied by a layer.
/// \param layer Pointer to the layer to delete.
void FreeLayer(T_Layer* layer);


#endif //OCR_LAYER_H
