//
// Created by root on 24/11/18.
//

#include <TrainingResource.h>

int main(){

    char* path = "../Resource/";

    T_TrainingResource* trainingResource = TransformTrainingResource(path);

    FreeTrainingResource(trainingResource);

}