
#include "test.h"
#include <stdlib.h>
#include <stdio.h>


int** deeppaissage(int** letter, int width, int heigth)
{	
	int temp = 0;
    for (int k = 0; k < heigth; ++k) {
    	int notedone = 1 ;
    	printf("\n");

        for (int l = 0; l < width; ++l) 
        {
        	if (letter[l][k] == 0)
        		{
        			notedone = 1;
        	    }

        	else if (letter[l][k] == 1 && notedone == 1    )
        		{
        		  	

        			letter[l][k] == 0;
        			notedone == 0;
        			printf("%d", 0);
        		}


            /*if (l + 1 >= width || k + 1 >= heigth)
            {
                letter[l][k] = 0;
            }
            else
            {
            	if (l == 0 && k == 0)
            		temp = notedone + letter[l + 1][k]  + letter[l ][k + 1]+ letter[l + 1][k + 1] ;
            	else if ( l == 0 )
            		temp = notedone + letter[l + 1][k] +  + letter[l ][k + 1] + letter[l][k - 1] + letter[l + 1][k + 1] + letter[l + 1][k - 1] ;
            	else 
            		temp = notedone + letter[l + 1][k] + letter[l - 1][k] + letter[l ][k + 1] + letter[l][k - 1] + letter[l - 1][k - 1] + letter[l + 1][k + 1] + letter[l - 1][k + 1] + letter[l + 1][k - 1] ;
                if (temp < -10  && temp >= - 30)
                    {
                    	letter[l][k] = -20 ;
                    	notedone = 0;
                    }
                     // = ^ 1 ; // si 1 = 0 si 0 = 1
                
µ					*/


           
        }
    }
    for(int i = 0; i < 8; i++) {
    	for(int j = 0; j < 8; j++) {
        	printf("%d ", letter[i][j]);
    	}
    	printf("\n");
	}
	    	printf("\n");

    for (int i = 0; i < heigth; ++i)
    {
    	
    	for (int j = 0; j < width; ++j)
    	{
    		if (letter[j][i] ==  -20 )
    			letter[j][i] = 0;

    	}
    }
    return letter;

}




/*

int main(int argc, char const *argv[])
{
	
	int** letter = (int**)malloc(sizeof(int*) * 8);
	for (int l = 0; l < 8; l++)
  		letter[l] = (int*)malloc(sizeof(double) * 8);

	/*double  letter[8][8] =  {
	{0,0,0,0,0,0,0,0},0
 	{0,0,1,1,1,1,0,0},1
 	{0,0,1,0,0,1,0,0},2
 	{0,1,1,0,0,1,1,0},3
	{0,1,1,1,1,1,1,0},4
	{1,1,0,0,0,0,1,1},5
	{1,1,0,0,0,0,1,1}6
	};
	letter[0][2] = 1;
	letter[0][5] = 1;
	letter[0][3] = 1;
	letter[0][4] = 1; 
	letter[1][2] = 1;
	letter[1][5] = 1;
	letter[1][3] = 1;
	letter[1][4] = 1; 
	letter[2][2] = 1;
	letter[2][5] = 1;
	letter[3][1] = 1;
	letter[3][6] = 1;
	letter[3][2] = 1;
	letter[3][5] = 1;
	letter[4][1] = 1;
	letter[4][5] = 1;
	letter[4][2] = 1;
	letter[4][6] = 1;
	letter[4][3] = 1;
	letter[4][4] = 1;
	letter[5][0] = 1;
	letter[5][1] = 1;
	letter[5][7] = 1;
	letter[5][7] = 1;
	letter[5][6] = 1;
	letter[5][6] = 1;
	letter[6][0] = 1;
	letter[6][1] = 1;
	letter[6][7] = 1;
	letter[6][6] = 1;
	letter[7][0] = 1;
	letter[7][1] = 1;
	letter[7][7] = 1;
	letter[7][6] = 1;

	//printf("%lf ", letter[5][5]);
	for(int i = 0; i < 8; i++) {
    	for(int j = 0; j < 8; j++) {
        	printf("%d ", letter[i][j]);
    	}
    	printf("\n");
	}
	printf("\n");
	printf("\n");
	
	letter = deeppaissage(letter , 8 ,8 );

	for(int i = 0; i < 8; i++) {
    	for(int j = 0; j < 8; j++) {
        	printf("%d ", letter[i][j]);
    	}
    	printf("\n");
	}


	for (int l = 0; l < 8; l++)
  		free(letter[l]);
  	free(letter);
	return 0;
}

*/