//William Joel Sandoval Casas, Percolating Checker Board, 16.01.2024

//Importing libraries
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

//Defining global variables
#define gridSize (1001)         //Remains constant
#define drunkenLadStart (501)   //Marks origin
#define spacesBetween (6)       //ex. 5 would mean 009000009 (0x0, 1x1, 3x3, 5x5)
#define runData (1000000)       //Number of iterations
#define steps (15000)           //Max step   

//Function properties
void stepMaker(double[][gridSize], int[]);
double distanceP(double[][gridSize], int[]);

//Main methods - non-self avoiding
int main(void){
    
    //Rand declaration
    srand(time(NULL)); //Sets the random number generator to ACTUALLY generate random numbers after each compilation (importing time)

    //Variables
    int counterOuter = 0;
    //double totalDistance = 0;

    //Declaration of file pointers
    FILE * print;

    //Open file pointer
    print = fopen("Balazs_3pm_DWM-SelfAvoiding-Obstacle-S5_Group3.txt", "w");

    //Prompts user for how many times to run data.
    //printf("How many times would you like to run each data point: ");
    //scanf("%d", &runData);

    //Prompts user for a desired value of steps
    //printf("Please enter the max number of steps: ");
    //scanf("%d", &steps);

    //Declare distance
    double laDistancia[steps] = {0};

    //While loop re-runs program by specified user amount
    while(counterOuter < runData){

        //Variables
        int counter = 0;
        int drunkenLadLocation[2] = {drunkenLadStart, drunkenLadStart}; //First square row, second column
        double xy[gridSize][gridSize] = {0}, weit = 0;
        double dSoFar = 0;

        //Places obstacles in grid (labelled by number 9) _____________________________________________________________EDIT FOR Trials
        for(int i = 0; i < gridSize; i += spacesBetween){
            for(int j = 0; j < gridSize; j += spacesBetween){
        
                //Places an obtacle of in a designated radius away
                xy[i][j] = 9;
        
                //If statements add obstables (3x3) to the grid
                //Top
                if(xy[(i+1)][j] == 0){

                    xy[(i+1)][j] = 9;

                }

                //Bottom
                if(xy[(i-1)][j] == 0){

                    xy[(i-1)][j] = 9;

                }

                //Left
                if(xy[i][(j-1)] == 0){

                    xy[i][(j-1)] = 9;

                }
        
                //Right
                if(xy[i][(j+1)] == 0){

                    xy[i][(j+1)] = 9;

                }

                //TopRight
                if(xy[(i+1)][(j+1)] == 0){

                    xy[(i+1)][(j+1)] = 9;

                }

                //TopLeft
                if(xy[(i+1)][(j-1)] == 0){

                    xy[(i+1)][(j-1)] = 9;

                }

                //BottomLeft
                if(xy[(i-1)][(j-1)] == 0){

                    xy[(i-1)][(j-1)] = 9;

                }

                //BottomRight
                if(xy[(i-1)][(j+1)] == 0){

                    xy[(i-1)][(j+1)] = 9;

                }

                //TODO: Segmentation fault when radius == 5
                //If statements add obstacles (5x5) to grid
                //Top
                if(xy[(i+2)][j] == 0){

                    xy[(i+2)][j] = 9;

                }

                //Bottom
                if(xy[(i-2)][j] == 0){

                    xy[(i-2)][j] = 9;

                }

                //TopRightMiddle
                if(xy[(i+2)][(j+1)] == 0){

                    xy[(i+2)][(j+1)] = 9;

                }

                //BottomRightMiddle
                if(xy[(i-2)][(j+1)] == 0){

                    xy[(i-2)][(j+1)] = 9;

                }

                //TopRight
                if(xy[(i+2)][(j+2)] == 0){

                    xy[(i+2)][(j+2)] = 9;

                }

                //BottomRight
                if(xy[(i-2)][(j+2)] == 0){

                    xy[(i-2)][(j+2)] = 9;

                }

                //TopLeftMiddle
                if(xy[(i+2)][(j-1)] == 0){

                    xy[(i+2)][(j-1)] = 9;

                }

                //BottomLeftMiddle
                if(xy[(i-2)][(j-1)] == 0){

                    xy[(i-2)][(j-1)] = 9;

                }

                //TopLeft
                if(xy[(i+2)][(j-2)] == 0){

                    xy[(i+2)][(j-2)] = 9;

                }

                //BottomLeft
                if(xy[(i-2)][(j-2)] == 0){

                    xy[(i-2)][(j-2)] = 9;

                }

                //Right
                if(xy[i][(j+2)] == 0){

                    xy[i][(j+2)] = 9;

                }

                //Left
                if(xy[i][(j-2)] == 0){

                    xy[i][(j-2)] = 9;

                }

                //RightUpMid
                if(xy[(i+1)][(j+2)] == 0){

                    xy[(i+1)][(j+2)] = 9;

                }

                //LeftUpMid
                if(xy[(i+1)][(j-2)] == 0){

                    xy[(i+1)][(j-2)] = 9;

                }

                //RightDownMid
                if(xy[(i-1)][(j+2)] == 0){

                    xy[(i-1)][(j+2)] = 9;

                }

                //LeftUpMid
                if(xy[(i-1)][(j-2)] == 0){

                    xy[(i-1)][(j-2)] = 9;

                }

            }
        }

        //Places the drunken lad in the middle on the grid ex. in [501][501] grid, loc would be [250][250]
        xy[drunkenLadLocation[0]][drunkenLadLocation[1]] = 1;

        //Loop runs functions to figure out configuration of steps
        while(counter < steps){

            //Calls function stepmaker which decides where drunk lad walks
            stepMaker(xy, drunkenLadLocation);
            
            //Measures end distance of drunk lad
            weit = distanceP(xy, drunkenLadLocation);
            //dSoFar = dSoFar + weit;
            //Adds up all the distance
            laDistancia[counter] = weit + laDistancia[counter];

            //Adds up by one
            counter ++;
        }


        // //Sample matrix print
        // for(int i = 490; i < 511; i++){
        //     for(int j = 490; j < 511; j++){

        //         //Prints a sample 21*21 matrix
        //         printf("%1.0lf ", xy[i][j]);

        //     }
        //     printf("\n");
        // }

        //Adds the counterouter by one
        counterOuter ++;
    }
    
    //Average out the distance for each run
    for(int x = 0; x < steps; x++){
        
        //averages out each cell in matrix
        laDistancia[x] = laDistancia[x] / runData;
        fprintf(print, "%.10lf\n", laDistancia[x]);

    }

    //totalDistance = totalDistance / runData;

    //Prints info statement
    //printf("The distance after %d steps is: %lf\n", steps, totalDistance);

    fclose(print);


}

//FUNCTIONS______________________________________________________________

//Decides where the human moves
void stepMaker(double xy[][gridSize], int drunkenLadLocation[]){  //row, column

    //Declaration of variables
    double rannum = rand() % (100 + 1);
    rannum = rannum / 100.0;

    //If rannum is greater than .75, then steps are right
    if (rannum > .75 && rannum <= 1.0 && xy[drunkenLadLocation[0]][(drunkenLadLocation[1] + 1)] == 0){

        //Adds one step to right
        //xy[0] = xy[0] + 1;
        drunkenLadLocation[1] += 1;
        xy[drunkenLadLocation[0]][(drunkenLadLocation[1]-1)] = 1;

    //If rannum is greater than .5, then steps are left
    } else if (rannum > .5 && rannum <= .75 && xy[drunkenLadLocation[0]][(drunkenLadLocation[1] - 1)] == 0){

        //Adds one step to left
        //xy[0] = xy[0] - 1;
        drunkenLadLocation[1] -= 1;
        xy[drunkenLadLocation[0]][(drunkenLadLocation[1]+1)] = 1;

    //If rannum is greater than .25, then steps are going up
    } else if (rannum > .25 && rannum <= .5 && xy[(drunkenLadLocation[0] + 1)][drunkenLadLocation[1]] == 0){

        //Adds one step to upwards direction
        //xy[1] = xy[1] + 1;
        drunkenLadLocation[0] += 1;
        xy[(drunkenLadLocation[0]-1)][drunkenLadLocation[1]] = 1;

    //If rannum is greater than 0, then steps are going down
    } else if (rannum >= 0.0 && rannum <= .25 && xy[(drunkenLadLocation[0] - 1)][drunkenLadLocation[1]] == 0){

        //Adds one step to downwards direction
        //xy[1] = xy[1] - 1;
        drunkenLadLocation[0] -= 1;
        xy[(drunkenLadLocation[0]+1)][drunkenLadLocation[1]] = 1;

    } else if (xy[(drunkenLadLocation[0] - 1)][drunkenLadLocation[1]] != 0 && xy[(drunkenLadLocation[0] + 1)][drunkenLadLocation[1]] != 0 && xy[drunkenLadLocation[0]][(drunkenLadLocation[1] - 1)] != 0 && xy[drunkenLadLocation[0]][(drunkenLadLocation[1] + 1)] != 0){

        //If all spots occupiedin the surrounding, end program.


    } else {

        //Calls the function again to attempt to find a number with an empty space
        stepMaker(xy, drunkenLadLocation);

    }
}

//Function calculates distance between two points
double distanceP(double xy[][gridSize], int drunkenLadLocation[]){

    //Variable declaration
    double d = 0.0;
    double x = (drunkenLadLocation[0] - drunkenLadStart), y = (drunkenLadLocation[1] - drunkenLadStart);

    //Distance formula
    //d = sqrt(((xy[0])*(xy[0]))+((xy[1])+(xy[1])));
    d = sqrt(((x)*(x)) + ((y)*(y)));

    //Returns distance to main
    return d;
}

//Matrix sizes
/*

    1001 * 1001
    (record distance data at )


*/