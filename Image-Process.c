
//#include <stdio.h>
#include <stdlib.h>
#include "Image-Process.h"
#include "stdlib.h"


int main(int argc, char const *argv[])
{
    FILE *path = NULL;
    printf("Hello world !");
    path =  fopen("../Bitmap.bmp", "r" );
    if (path == NULL) {
        printf("Cant open file.");
        exit(-1);
    }
    printf( "%d",gettingimage(path).Height);

    return 0;
}


Bmp gettingimage(FILE *path){

    char readhead[30];
    for (int i = 0; i < 30; ++i) {
        fread(&readhead[i], sizeof(char), 1, path);
    }



    Header head;
    head.Width =*((int *) (readhead + 18));  //initialisation of param
    head.Height =*((int *) (readhead + 22));   //int = 4 byte
    head.Size =(head.Width * head.Height);
    head.startimage = *((int *) (readhead + 10));



    fseek(path ,head.startimage,SEEK_SET); // met le pointeur a la valeur de startimage donc on peux lire les couleurs

    int nbPixel = head.Size * 3;
    char Colors[nbPixel]; // nombre de pixels * 3(RVB)

    for (int j = 0; j < nbPixel; ++j) {
        fread(&Colors[j], sizeof(char), 1, path);
    }

    return ColorsToPixel(Colors , head);;
}

Bmp ColorsToPixel(char Color[] , Header head) {
    Bmp retbmp;
    retbmp.header = head;
    Pixel** Pixels = (Pixel**)malloc(sizeof(Pixel*) * retbmp.Width);
    for (int l = 0; l < retbmp.Width; ++l)
        Pixels[l] = (Pixel*)malloc(sizeof(Pixel) * retbmp.Height);

    for (int i = 0; i < retbmp.Size * 3; ++i) {
        
        Pixel temppixel;
        for (int j = 0; j < 3; ++j) {
            unsigned char r = (unsigned char) *((Color) + i + j);
            if (j == 0)
                temppixel.Bleu = r;
            if (j == 1)
                temppixel.Vert = r;
            if (j == 2)
                temppixel.Rouge = r;

        }
        retbmp.Pixels[i % retbmp.Width][i / retbmp.Width ] = temppixel;
    }
    retbmp.Pixels = Pixels;
    return retbmp;
}

/*
 double** Decolorize(Bmp bmp) {

    double** arrays[bmp.Height][bmp.Width]
    for (int i = 0; i < bmp.heigth; ++i) {
        for (int j = 0; j < bmp.Width; ++j) {
            Pixel temp = bmp.Pixels[i][j];
            arrays[i][j] = (0.11 * temp.Bleu + 0.59 * temp.Vert + 0.3 * temp.Rouge) / 255;
            //arrays[i][j] = 1 if ( (0.11*temp.Bleu + 0.59*temp.Vert + 0.3*temp.Rouge)/ 256) > 0,5 ? 0;
        }
    }

    return arrays;


}

double** convolution(double** arrays , int heigth , int width ) {
    int *kernel[3];
    kernel[1] = {-1, -1, -1};
    kernel[2] = {-1, 8, -1};
    kernel[3] = {-1, -1, -1};

    double **out[heigth][width];


    for (i = 1; i < m - 1; ++i) // iterate through image
    {
        for (j = 1; j < n - 1; ++j) {
            double sum = 0; // sum will be the sum of input data * coeff terms

            for (ii = -1; ii <= 1; ++ii) // iterate over kernel
            {
                for (jj = -1; jj <= 1; ++jj) {
                    double data = arrays[i + ii][j + jj];
                    double coeff = kernel[ii + K / 2][jj + K / 2];

                    sum += data * coeff;
                }
            }
            out[i][j] = sum / scale; // scale sum of convolution products and store in output
        }
    }
}


TupleHi Histogrammification(double** arrays ,int width , int height ){

    TupleHi couplehisto;

    int* histogramme1 = calloc(width, sizeof(unsigned int));
    int *histogramme2 = calloc(height, sizeof(unsigned int));
    for (int i = 0;i<width;++i) {
        for(int j = 0;j< height ; ++j){
                if (arrays[i][j] >= 0.5) {
                        histogramme1[i] += 1;
                        histogramme2[i] += 1;
                    }

            }
    }
    couplehisto.item1 = histogramme1;
    couplehisto.item2 = histogramme2;
    return couplehisto;


}



Tuple* choosefrom_histo(int* histogramme , int size) {
    int average = 0;
    for (int k = 0; k <size; ++k) {
        average += histogramme[k];
    }
    average /= size;
    Tuple *couple;
    couple->item1 = -1;
    couple->item2 = -1;
    for (int i = 0; i < size; i++) {
        if (histogramme[i] < average && couple->item2 == -1) {
            couple->item1 = i;
        } else if (histogramme[i] >= average) {
            couple->item2 = i;
        }
    }
    return couple;
}


double** resize (double** arrays , int width , int heigth)
{
    TupleHi* hitsos = histogrammification(arrays , width, heigth);
    Tuple* wid = choosefrom_histo(hitsos->item1 , width);
    int newwidth = (wid->item2- wid->item1);
    Tuple *hei = choosefrom_histo(hitsos->item2 , heigth);
    int newheigth = (hei->item2 - hei->item1);
    double ** newarrays = (double**)malloc(sizeof(double*) * newwidth );
    for (int i = 0; i <  newwidth; ++i)
    {
        newarrays[i] = (double*)malloc(sizeof(double) * newheigth );
    }
    
    for (int k = wid->item1; k < wid->item2; ++k) {
        for (int l = hei->item1; l < hei->item2; ++l) {
            newarrays[k - wid->item1 ][l - hei->item1] = arrays [k][l];
        }
    }
    free(arrays);
    return  newarrays;
}


double** deeppaissage(double ** letter, int width, int heigth)
{
    for (int k = 0; k < heigth; ++k) {
        for (int l = 0; l < width; ++l) {
            if (l + 1 < width || k + 1 < heigth)
            {
                letter[width][heigth] = 1;
            }
            else
            {
                if (letter[width + 1][heigth] + letter[width][heigth + 1] == 0)
                    letter[width][heigth] = letter[width + 1][heigth + 1] + 1 ; // si 1 = 0 si 0 = 1


            }
        }
    }

}*/