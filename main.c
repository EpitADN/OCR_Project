//
// Created by Gireg Roussel on 06/10/2018.
//

#include "SaveAndLoad.c"
#include "SaveAndLoad.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    //double matrix[4][3] = { { 1.2 , 2.2 , 3.2 } , { 4.2 , 5.2 , 6.2} , { 1.2 , 2.2 , 3.2 } , { 4.2 , 5.2 , 6.2} };
    Save(10, 3);
    Load(10, 3);
    return 0;
}