//
// Created by root on 05/10/18.
//

#include "Node.h"

#ifndef OCR_LAYER_H
#define OCR_LAYER_H

typedef struct S_Layer {
    int* nbNodes;
    T_Node** nodes;
} T_Layer;


/// Create a new layer with n nodes
/// \param nbNodes number of nodes of the layer
/// \return New layer
T_Layer* InitializeLayer(int* nbNodes);


/// Free the memory occupied by a layer.
/// \param layer Pointer to the layer to delete.
void FreeLayer(T_Layer* layer);

#endif //OCR_LAYER_H
