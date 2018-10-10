//
// Created by root on 05/10/18.
//

#ifndef OCR_NODE_H
#define OCR_NODE_H


typedef enum E_Nature{
    INPUT,
    OUTPUT,
    HIDDEN,
    BIAS
} T_Nature;

typedef struct S_Node {
    T_Nature nature;
    double net; // Net(k)
    double val; // o(k)
    double error; // d(k)
} T_Node;


/// Create a new node with all it's value defaulted to 0.
/// \return New node
T_Node* InitializeNode(T_Nature nature);

/// Free the memory occupied by a node.
/// \param node Pointer to the node to delete.
void FreeNode(T_Node* node);

#endif //OCR_NODE_H