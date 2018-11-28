//
// Created by root on 10/11/18.
//

#include "TrainingResource.h"

/// Transforms (initializes) and organizes the training material
/// WARNING : Folder must contain a '_config.txt' file and be correctly structured
/// \param folder Path to the folder containing the sample
/// \return A pointer to the initialized Training Resource
T_TrainingResource* TransformTrainingResource(char* folder) {

    // Allocating memory for config path
    char* config = "_config.txt";

    char* pathConfig = malloc( (strlen(folder)+strlen(config)) * sizeof(char));
    pathConfig[0] = '\0';

    // Concatening path
    strcat(pathConfig, folder);
    strcat(pathConfig, config);

    // Open config file
    FILE* fp;
    if ((fp = fopen(pathConfig, "r")) == NULL){
        printf("Error opening for config file at %s\n", pathConfig);
        exit(1);
    }

    char buffer[60];
    int index;

    // Reading height
    int height = 0;
    if (fgets(buffer, 60, fp) == NULL){
        printf("Error reading height\n");
        exit(1);
    }
    height = atoi(buffer);

    // Reading width
    int width = 0;
    if (fgets(buffer, 60, fp) == NULL){
        printf("Error reading width\n");
        exit(1);
    }
    width = atoi(buffer);

    // Reading number of targets
    int nbTargets = 0;
    if (fgets(buffer, 60, fp) == NULL){
        printf("Error reading number of targets\n");
        exit(1);
    }
    nbTargets = atoi(buffer);

    // Reading targets
    index = 0; char* Targets = malloc(nbTargets * sizeof(char));
    if (fgets(buffer, 60, fp) == NULL){
        printf("Error reading targets\n");
        exit(1);
    }
    while (buffer[index] != '\n'){
        Targets[index] = buffer[index];
        index++;
    }

    // Reading number of duplicates
    int* nbDuplicates = malloc(nbTargets * sizeof(int));
    for (int i = 0; i < nbTargets; ++i) {

        // Reading number of duplicate for target i
        nbDuplicates[i] = 0;
        if (fgets(buffer, 60, fp) == NULL){
            printf("Error reading number of duplicates for target %c\n", Targets[i]);
            exit(1);
        }
        int tmp = atoi(buffer);
        nbDuplicates[i] = tmp;

    }


    // Initialize Training Resource
    T_TrainingResource* trainingResource = malloc(sizeof(T_TrainingResource));
    trainingResource->TrainingChars = malloc(nbTargets * sizeof(T_TrainingChar*));
    trainingResource->size = height*width;
    trainingResource->nbTargets = nbTargets;
    trainingResource->Targets = Targets;
    trainingResource->nbDuplicates= nbDuplicates;

    // Closing config file
    free(pathConfig);
    fclose(fp);



    // Initializing SDL
    init_sdl();
    SDL_Surface* image;

    // Initializing path of duplicates
    char targetPath[] = "X/";
    buffer[0] = '\0';
    strcat(buffer, folder);
    strcat(buffer, targetPath);
    size_t len = strlen(folder);

    // Loading Images
    for (int j = 0; j < nbTargets; ++j) {

        // Allocating memory for the duplicates
        trainingResource->TrainingChars[j] = malloc(nbDuplicates[j] * sizeof(T_TrainingChar));

        // Setting path of duplicates
        buffer[len] = Targets[j];
        printf("Looking in directory %s :\n", buffer);

        // Loading duplicates
        TransformTrainingChars(buffer, trainingResource->TrainingChars[j], nbDuplicates[j], trainingResource->size, image);
    }

    SDL_FreeSurface(image);

    return trainingResource;
}

/// Transforms Training Chars associated with a training resource
/// \param duplicatesPath Path to the training folder containing duplicates
/// \param trainingChars Pointer to the concerned trainingChars
/// \param maxChars Expected number of duplicates
/// \param charSize Size (h*w) of a training char
/// \param image Surface to load upon
void TransformTrainingChars(char* duplicatesPath, T_TrainingChar* trainingChars, int maxChars, int charSize, SDL_Surface* image){

    // Opening duplicates directory
    DIR* targetDir;
    if ((targetDir = opendir(duplicatesPath)) == NULL){
        printf("Error opening directory %s :\n", duplicatesPath);
        exit(1);
    }

    // Initializing path to training char
    char buffer[60] = {'\0',};
    strcat(buffer, duplicatesPath);
    size_t len = strlen(duplicatesPath);

    // Initializing variables
    int nbfiles = 0;
    struct dirent* dir;

    // Iterating on files in directory
    while ((dir = readdir(targetDir)) != NULL && nbfiles < maxChars) {

        // If t's not a file
        if (dir->d_type != DT_REG)
            continue;

        // Setting up path to training char
        buffer[len] = '\0';
        strcat(buffer, dir->d_name);
        printf(" -- Treating %s\n", buffer);

        // Loading training char
        trainingChars[nbfiles] = TransformTrainingChar(buffer, charSize, image);
        nbfiles++;
    }

    printf("Total number of files treated : %d\n\n", nbfiles);
    closedir(targetDir);
}


/// Transform a Training Char from path (bmp image)
/// \param charPath Path of the Training char
/// \param charSize Size (h*w) of a training char
/// \param image Surface to load upon
/// \return the Training char
T_TrainingChar TransformTrainingChar(char* charPath, int charSize, SDL_Surface* image) {

    image = load_image(charPath);

    int height = image->h;
    int width = image->w;

    if (height * width != charSize) {
        printf("Image %s has a unexpected size of %d pixels ! (Expected %d)", charPath, height*width, charSize);
        exit(1);
    }

    double* values = malloc(charSize * sizeof(double));

    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            values[i*height + j] = get_pixel(image, i, j);
            printf("%d", (int)values[i*height + j]);
        }
        printf("\n");
    }

    T_TrainingChar trainingChar = {values};

    return trainingChar;
}


/// Prints info on a training resource
/// \param trainingResource Pointer to the training resource
void PrintTrainingResource(T_TrainingResource* trainingResource) {

    printf("Printing info on training resource : \n\n");

    printf("Resource contains %d different targets of size %d, which are :\n", trainingResource->nbTargets, trainingResource->size);
    for (int i = 0; i < trainingResource->nbTargets; ++i)
        printf("%3c", trainingResource->Targets[i]);

    printf("\n\nNumber of duplicates per target :\n");
    for (int j = 0; j < trainingResource->nbTargets; ++j)
        printf("- '%c' : %d\n", trainingResource->Targets[j], trainingResource->nbDuplicates[j]);

    printf("\n");
}


/// Saves the training resource in one unique binary file
/// \param trainingResource Pointer to the training resource
/// \param path Folder/name to save in
void SaveTrainingResource(T_TrainingResource* trainingResource, char* path) {

    FILE* fp;

    if ((fp = fopen(path, "wb")) == NULL) {
        printf("Error saving for resource at path %s\n", path);
        exit(1);
    }

    int nbTargets = trainingResource->nbTargets;

    fwrite(&trainingResource->size, sizeof(int), 1, fp);
    fwrite(&nbTargets, sizeof(int), 1, fp);

    for (int i = 0; i < nbTargets; ++i)
        fwrite(&trainingResource->Targets[i], sizeof(char), 1, fp);

    for (int j = 0; j < nbTargets; ++j)
        fwrite(&trainingResource->nbDuplicates[j], sizeof(int), 1, fp);

    for (int k = 0; k < nbTargets; ++k) {
        for (int l = 0; l < trainingResource->nbDuplicates[k]; ++l) {
            SaveTrainingChar(&trainingResource->TrainingChars[k][l], trainingResource->size, fp);
        }
    }

}


/// Save a training char to specified file
/// \param trainingChar Pointer to the training char to be saved
/// \param size Size of the training char (height*width)
/// \param fp Save file pointer
void SaveTrainingChar(T_TrainingChar* trainingChar, int size, FILE* fp){
    for (int i = 0; i < size; ++i) {
        fwrite(&trainingChar->values[i], sizeof(double), 1, fp);
    }
}


/// Loads the Training Resource from a unique file
/// \param path Path to the file to load
/// \return A pointer to the loaded Training Resource
T_TrainingResource* LoadTrainingResource(char* path) {

    FILE* fp;
    if ((fp = fopen(path, "rb")) == NULL) {
        printf("Error opening for resource save at path %s\n", path);
        exit(1);
    }

    T_TrainingResource* trainingResource;
    if ((trainingResource = malloc(sizeof(trainingResource))) == NULL)
        exit(1);

    int size; int nbTargets;
    fread(&size, sizeof(int), 1, fp);
    fread(&nbTargets, sizeof(int), 1, fp);
    trainingResource->size = size;
    trainingResource->nbTargets = nbTargets;


    trainingResource->Targets = malloc(nbTargets * sizeof(char));
    for (int i = 0; i < nbTargets; ++i)
        fread(&trainingResource->Targets[i], sizeof(char), 1, fp);

    trainingResource->nbDuplicates = malloc(nbTargets * sizeof(int));
    for (int j = 0; j < nbTargets; ++j)
        fread(&trainingResource->nbDuplicates[j], sizeof(int), 1, fp);

    trainingResource->TrainingChars = malloc(nbTargets * sizeof(T_TrainingChar**));
    for (int k = 0; k < nbTargets; ++k) {
        trainingResource->TrainingChars[k] = malloc(trainingResource->nbDuplicates[k] * sizeof(T_TrainingChar));
        for (int l = 0; l < trainingResource->nbDuplicates[k]; ++l)
            trainingResource->TrainingChars[k][l] = LoadTrainingChar(size, fp);
    }

    return trainingResource;
}


/// Loads a training char from a file
/// \param size Size of the training file
/// \param fp File pointer to the save
/// \return The training char as double array
T_TrainingChar LoadTrainingChar(int size, FILE* fp) {

    double* values = malloc(size * sizeof(double));
    for (int i = 0; i < size; ++i)
        fread(&values[i], sizeof(double), 1, fp);

    T_TrainingChar trainingChar = {values};
    return trainingChar;

}

/// Free the memory occupied by a training resource
/// \param trainingResource Pointer to the resource to delete
void FreeTrainingResource(T_TrainingResource* trainingResource) {


    for (int i = 0; i < trainingResource->nbTargets; ++i) {
        for (int j = 0; j < trainingResource->nbDuplicates[i]; ++j) {
            free(trainingResource->TrainingChars[i][j].values);
        }
        free(trainingResource->TrainingChars[i]);
    }
    free(trainingResource->Targets);
    free(trainingResource->nbDuplicates);
    free(trainingResource->TrainingChars);
    free(trainingResource);

}