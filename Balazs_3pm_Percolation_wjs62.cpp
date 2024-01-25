//William Joel Sandoval Casas, Percolating Checker Board, 09.01.2024

//Import Libraries
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Declaring global libraries
//!!! USER SPECIFIES SIZE OF MATRIX AND ITERATIONS
#define size (20)
#define iterations (1000000)
 
//Function Properties   FIX FUNCTION PROTOTYPES
void gridClusterLabeller(int[][size], int [][size]);
//void leftChecker(int [][size], int, int, int []);
//void topChecker(int [][size], int , int , int []);
//void unir(int, int, int[]);
//int find(int, int[]);

//Start of Main method
int main(void){

    //Declaration of variables
    FILE * imprimir;
    srand(time(NULL)); //Sets the random number generator to ACTUALLY generate random numbers after each compilation (importing time)
    float checkerBoard[size][size] = {0};
    float rannum = 0;
    float CPercent = 0;

    //int demonstrationBoard[size][size] = {0};

    //Declaration of file pointer
    imprimir = fopen("PercolationData20x20.txt", "w");

    //int clusterCounter[size][size] = {0}; //To ensure no data corruption occurs, data is first stored in a separate, cluster matrix and later transferred to the demoBoard. CONTRARY = make matrix in main and pass to f(x)
    int N = 100;
    int numI = 0;
    float oSuccess[101] = {0};

    //while loop repeats entire program again
    while(numI < iterations){

        //Declaration of variables
        float percent = 0;

        //Initializes random values into checker board
        for (int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){

                //Generates random numbers in each instance of the checker board using rand()
                rannum = rand() % (N + 1);
                rannum = rannum / 100.0;
                checkerBoard[i][j] = rannum; 

            }
        }

        //Declares run as 1
        //int run = 1;

        //While loop allows user to test different percentage with same table of random values
        while(percent <= 100){

            //Declares success as 0
            int success = 0;

            //Prompts user for percentage(in terms of 10) & error checks
            //do{
                //printf("Please enter a value representative of the percentage for the checker board. \nMust be in multiples of ten from 10 to 100: ");
                //scanf("%f", &percent);
            //} while(percent != 10 && percent != 20 && percent != 30 && percent != 40 && percent != 50 && percent != 60 && percent != 70 && percent != 80 && percent != 90 && percent != 100);
            
            //Converts user inputed value into a percentage from 0 to 1
            CPercent = percent / 100.0;

            //Reiniatilizes values to 0 for future trials
            int clusterCounter[size][size] = {0};
            int demonstrationBoard[size][size] = {0};


            //Classifies numbers as 0 (over percent) and 1, under it
            for (int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){

                    //If a specific value of the checkerboard is under the percentage specified, a 1 is displayed, else a 0 (a different matrix is used for these operations to ensure no corruption of the data)
                    if(checkerBoard[i][j] <= CPercent){

                        //Signifies that spot is occupied
                        demonstrationBoard[i][j] = -1;

                    } else { 

                        //Space is empty (already a zero declared)

                    }

                }
            }

            //Calls cluster counter
            gridClusterLabeller(demonstrationBoard, clusterCounter);


            //path counter
            int clusterLabelTop[size];
            int clusterLabelBottom[size];
            int clusterLabelLeft[size];
            int clusterLabelRight[size];

            for (int j = 0; j < size; j++) {
	            clusterLabelTop[j] = clusterCounter[0][j];
	            clusterLabelBottom[j] = clusterCounter[size - 1][j];
            }

            for (int j = 0; j < size; j++) {
	            clusterLabelLeft[j] = clusterCounter[j][0];
	            clusterLabelRight[j] = clusterCounter[j][size - 1];
            }


            //check for paths
            double path = 0;

            for (int i = 0; i < size; i++) {
	            for (int j = 0; j < size; j++) {
		        
                    if (clusterLabelTop[i] != 0 && clusterLabelBottom[j] != 0) {
			            
                        int element = clusterLabelTop[i];
			
                        if (clusterLabelBottom[j] == element) {
				            path = path + 1;
			            }
		            }
	            }
            }

            for (int i = 0; i < size; i++) {
	            for (int j = 0; j < size; j++) {
		            
                    if (clusterLabelLeft[i] != 0 && clusterLabelRight[j] != 0) {
			
                        int element = clusterLabelLeft[i];
			
                        if (clusterLabelRight[j] == element) {
				            path = path + 1;
			            }
		            }
	            }
            }

            //Determines if percolation was successful.
            //TOP:

            for (int i = 0; i < size; i++) {
                for(int j = 0; j < size; j++){

                    if(clusterCounter[i][0] == clusterCounter[j][(size-1)] && clusterCounter[i][0] > 0){

                        success = 1;
                        break;

                    }
                }
            }

            //Sides:
            if(success == 0){
                for (int i = 0; i < size; i++) {
                    for(int j = 0; j < size; j++){

                        if(clusterCounter[0][i] == clusterCounter[(size-1)][j] && clusterCounter[0][i] > 0){

                            success = 1;
                            break;

                        }
                    }
                }
            }

            /*
            //Prints checker board under designated percentage of checker board
            for (int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){

                    //A precision of 1 is used to ensure the data does not display any random values.
                    printf("%d ", demonstrationBoard[i][j]);

                }
                //Escape sequence prints a new line to ensure asthethic
                printf("\n");
            }

            printf("\n");

            //Prints CLUSTER board under designated percentage of checker board  ******************************************
            for (int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){

                    //A precision of 1 is used to ensure the data does not display any random values.
                    printf("%d\t", clusterCounter[i][j]);

                }
                printf("\n");
            }
            */
            
            //gives trial success
            //printf("\n\nThe trial success: %d", success); //prints 1 if yes, 0 if no

            oSuccess[(int(percent))] += success;

            //Asks user whether to run again
            //do{
            //    printf("\n\nWould you like to test a different percentage?\nEnter 1 for yes and 0 for no: ");
            //    scanf("%d", &run);
            //} while(run != 1 && run != 0);
            //printf("%f\n", percent);
            percent = percent + 1;
        }

        //Do-while loop prompts user to run program again (using a new dataset of randomly generated values)
        //do{
            //printf("\n\nWould you like to generate new digits?\nEnter 1 for yes and 0 for no: ");
            //scanf("%d", &newnum);
        //} while(newnum != 1 && newnum != 0);
        numI ++;
    }



    //Calculates the average & prints trial success to file
    for(int i = 0; i < 101; i++){

        oSuccess[i] = oSuccess[i] / float(iterations); 
        fprintf(imprimir, "%f\n", oSuccess[i]);

    }
    

    //Closes file pointer
    fclose(imprimir);

}

//---------------------------------------------------END of MAIN METHOD-----------------------------------------------------------

/* 
    NOTES
*/
//A single path across!! the point where it is guaranteed
//To get a complete path, higher or lower? -Depends on the grid size
//Randomly,
//For one path, does a percentage exist.
//Allowed to fine tune percent.

//---------------------------START of Functions------------------------------------------------------------------------

//Takes in matrix containing 0 and -1 and counts its clusters
void gridClusterLabeller(int demoBoard[][size], int clusterCounter[][size]){ //Need to get matrix // i = y j = x
    
    //Variable Declarations
    int iteration = 0;
    int above = 0;
    int left = 0;

    //int subtractionFactor[2];
    //int area[(size*size)+1] = {0};
    //bool top, access;

    //Fills area with int from 0 to size 
    /*
    for(int f = 0; f <= (size*size)+1; f++){

        area[f] = f;

    } */

    //Runs through length of matrix
    for (int i = 0; i < size; i++) {
	    for (int j = 0; j < size; j++) {

            //if demoBoard is not equal to 0
		    if (demoBoard[i][j] != 0) {

                //Helps protect against segmentation errors
			    if (i == 0) {

                    //Sets above to 0
				    above = 0;

			    } else {

				    above = clusterCounter[i - 1][j];
			    }

                //Helps protect against segmentation errors
			    if (j == 0) {

				    left = 0;

			    } else {

			        left = clusterCounter[i][j - 1];

                }



                //if no label above or left
			    if (left == 0 && above == 0) {

                    //Increases iteration (label) by one & counts the cell
				    iteration += 1; 
				    clusterCounter[i][j] = iteration;
			    
                //left item
                } else if (left != 0 && above == 0) {

                    //Declares cell to left value
				    clusterCounter[i][j] = left;

                //Above item
			    } else if (left == 0 && above != 0) {

                    //Declare cell to top value
				    clusterCounter[i][j] = above;

                //left and above item
		        } else {

				    clusterCounter[i][j] = left;

                //Runs through loop to unite code
				    for (int x = 0; x < size; x++) {
					    for (int y = 0; y < size; y++) {

						    if (clusterCounter[x][y] == above) {
							
                                clusterCounter[x][y] = left;

						    }
					    }
				    }

			    }

		    }
	    }
    }
 /*       
        //Cluster counter
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){

                //Declaring left and above
                int left = 0, above = 0;

                //If cell occupied, then
                if(demoBoard[i][j] == -1){

                    //declares left and above
                    if(i > 0){

                        above = clusterCounter[(i-1)][j];
                    } 

                    if (j > 0){

                        left = clusterCounter[i][(j-1)];
                    }

                    //If no pieces detected, no declaration above or left
                    if(left == 0 && above == 0){

                        //Makes new, unused cluster label
                        iteration += 1; 
                        
                        //Declares an iteration on the clustercounter
                        clusterCounter[i][j] = iteration;

                    //Conditional looks at above and left cell, enters if left detects
                    } else if (left != 0 && above == 0) {

                        //Calls function find and returns a value
                        //clusterCounter[i][j] = find(left);
                        clusterCounter[i][j] = clusterCounter[(i-1)][j]; 

                    //Conditional looks at above and left cell, enters if above detects
                    } else if (left == 0 && above != 0) {

                        //Calls function find and returns a value
                        //clusterCounter[i][j] = find(above);
                        clusterCounter[i][j] = clusterCounter[i][(j-1)];


                    //Enters if a piece exists both above and left
                    } else {

                        //links left and above clusters
                        //unir(left, above, area);
                        

                        //finds left
                        //clusterCounter[i][j] = find(left);
                    }

                }




                /*
                //Checks if the stop is empty (represented with 0) or full
                if(demoBoard[i][j] == -1){
                    
                    //Reinitializes substraction factor
                    subtractionFactor[0] = 1;
                    subtractionFactor[1] = 1;
                    top = false;
                    access = false;

                    //Checks the rows (top)
                    if(clusterCounter[(i-subtractionFactor[0])][j] > 0){

                        //Sets top equal to current spot
                        clusterCounter[i][j] = clusterCounter[(i-subtractionFactor[0])][j];
                        top = true;
                        access = true;

                    }

                    //Reinitialize substraction factor
                    //subtractionFactor[0] = 1; (NOT NEEDED, done above)

                    //Checks the columns (left)
                    if(clusterCounter[i][(j-subtractionFactor[0])] > 0 && clusterCounter[i][(j-subtractionFactor[0])] <= (iteration * 2)){   ///MIGHT BE BROKEN IF OUT OF BOUNDS, CHECK

                        //Sets left equal to current spot
                        if(top == false){

                            //If nothing at the top exists, then current cell equal to left
                            clusterCounter[i][j] = clusterCounter[i][(j-subtractionFactor[0])];

                        } else if (clusterCounter[i][(j-subtractionFactor[0])] != clusterCounter[(i-subtractionFactor[0])][j] || top == true){

                            
                            //Calls left checker which checks if something exists to the left
                            leftChecker(clusterCounter, j, i, subtractionFactor); //FUNCTION_______________________________

                        }

                        //Declares access (representative of accessing the if-statements) as true
                        access = true;
                        
                    }

                    if (access == false){

                        //Sets spot equal to iteration   FIX SO THAT ONLY OCCURS IF NO CELL DETECTED ABOVE OR TO THE LEFT
                        clusterCounter[i][j] = iteration; //at end, adds one to the cluster counter   BE CAUTIOUS~~~~~~~~~~~~~~~~~
                        iteration ++;
                    }

                //If no value is present in that particular spot, a zero is saved on the cluster counter.
                } else if (demoBoard[i][j] == 0){

                    //Initializes the location that is unused on the demoBoard as a 0.
                    clusterCounter[i][j] = 0;

                }
                

            }
        }
        */
        
}

void function (void){

    

}




































/*
//Function unites cells
void unir(int x, int y, int area[]){

    //calls find
    area[find(y, area)] = find(x, area);

}

//Function locates
int find(int x, int area[]){

    //declares y to x
    int y = x;

    //Loops runs while area != to y/x
    while(area[y] != y){

        //declares y to area
        y = area[y];

    }

    while(area[x] != x){

        //declares x
        int z = area[x];

        area[x] = y;

        x = z;


    }

    return y;

}

/***
//Calls function leftChecker
void leftChecker(int clusterCounter[][size], int j, int i, int subtractionFactor[]){ ///[row][column]

    /*
    //declaration of variables WOULDNT WORK
    bool topCheckerr = false;     

    //substraction factor reset (if top checker is true) 
    if(topCheckerr == true){
        subtractionFactor[1] = 1;
    }
    *

    //Reinitializes substraction factor as 1
    subtractionFactor[0] = 1;

    while(clusterCounter[i][(j - subtractionFactor[0])] > 0 && subtractionFactor[0] <= j){

        //Test if two spoots to left is not equal to 0 (there is a value present)
        if(clusterCounter[i][(j - subtractionFactor[0])] > 0){

            //Makes cell to the left equal to cell to right
            clusterCounter[i][(j - subtractionFactor[0])] = clusterCounter[i][(j - subtractionFactor[0] + 1)];
    
        
            //Calls top checker only if a value exists above
            if(clusterCounter[(i-subtractionFactor[0])][j] > 0 && i - subtractionFactor[1] >= 0){

                //Calls top checker which checks if something exists to the top
    
                topChecker(clusterCounter, j, i-subtractionFactor[0], subtractionFactor);
                //topCheckerr = true;

            }

            //Increases the subtraction factor by 1
            subtractionFactor[0] += 1; //adds one to the substraction factor at position 1

        }

            //Calls the leftChecker again to test more values to the left, ends once a cell on clusterCounter is equal to 0
            //if(j - subtractionFactor[0] >= 0) {
            //    leftChecker(clusterCounter, j, i, subtractionFactor);
            //}

    }
}

//Checks the top cell
void topChecker(int clusterCounter[][size], int j, int i, int subtractionFactor[]){ ///[row][column]

    //Variables
    //subtractionFactor[0] ++; //brings the subtractionFactor up by one everytime function is called
    //Not needed, already done in leftChecker

    //Reinitializes substractionFactor as 1
    subtractionFactor[1] = 1;

    //Tests if a value exists two spots above //The first statement in the if statement might be redundant

    while(clusterCounter[(i - subtractionFactor[1])][j] > 0 && subtractionFactor[1] <= i){

        if(clusterCounter[(i - subtractionFactor[1])][j] > 0 && (i-subtractionFactor[1] >= 0)){

            clusterCounter[(i - subtractionFactor[1])][j] = clusterCounter[(i - subtractionFactor[1] + 1)][j];

        }

        //Calls function again if anything to the left exists
        if(clusterCounter[i-subtractionFactor[1]][(j - 1)] > 0){
            leftChecker(clusterCounter, j, i-subtractionFactor[1], subtractionFactor);
        }

        //ups substractionfactor by 1
        subtractionFactor[1] += 1;

    }
}


*/
/*

OOOO
3O33
3OO3
3333

*/