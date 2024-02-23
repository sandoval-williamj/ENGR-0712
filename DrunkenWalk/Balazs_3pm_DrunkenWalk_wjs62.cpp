//William Joel Sandoval Casas, Percolating Checker Board, 16.01.2024

//Importing libraries
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

//Function properties
void stepMaker(double[]);
double distanceP(double[]);

//Define global variables
#define runData (1000000)
#define steps (15000)

//Main methods - non-self avoiding
int main(){

    //Variables
    int counterOuter = 0;
    //double totalDistance = 0;
    //double avg = 0;
    double weit[steps] = {0};
    FILE * printy;

    //Rand declaration
    srand(time(NULL)); //Sets the random number generator to ACTUALLY generate random numbers after each compilation (importing time)

    //Print 
    printy = fopen("DrunkenWalk_NO_NON_15k_1M.txt", "w");

    ////Prompts user for how many times to run data.
    //printf("How many times would you like to run each data point: ");
    //scanf("%d", &runData);

    //Prompts user for a desired value of steps
    //printf("Please enter the max number of steps: ");
    //scanf("%d", &steps);

    //While loop runs the date multiple time to generate best results
    while(counterOuter < runData){  

        //Variables
        int counter = 0;
        double xy[2] = {0};

        //FILE * data;

        //Loop runs functions to figure out configuration of steps
        while(counter < steps){
            stepMaker(xy);
            weit[(counter)] = weit[(counter)] + distanceP(xy);
            counter ++;
        }

        //Calculates the average per step
        //avg = totalDistance / double(counterOuter);

        ////Prints to file
        //fprintf(printy, "%d ,%lf\n", counterOuter, avg);

        //Adds the counterouter by one
        counterOuter ++;
    }

    //Calculates the average and prints to file
    for(int i = 1; i <= steps; i++){

        //Calculates average
        weit[(i-1)] = weit[(i-1)] / double(runData);

        //Prints to file
        fprintf(printy, "%d,%lf\n", i, weit[(i-1)]);

    }

    //printf("The distance after %d steps is: %LF\n", steps, totalDistance);

    fclose(printy);

}

//FUNCTIONS_______________________


void stepMaker(double xy[]){

    //Declaration of variables
    double rannum = 0.0;

    //Generates random number
    rannum = rand() % (101);
    rannum = rannum / 100.0;

    //If rannum is greater than .75, then steps are right
    if (rannum >= .75){

        //Adds one step to right
        xy[0] = xy[0] + 1;

    //If rannum is greater than .5, then steps are left
    } else if (rannum >= .5){

        //Adds one step to left
        xy[0] = xy[0] - 1;

    //If rannum is greater than .25, then steps are going up
    } else if (rannum >= .25){

        //Adds one step to upwards direction
        xy[1] = xy[1] + 1;

    //If rannum is greater than 0, then steps are going down
    } else if (rannum >= 0){

        //Adds one step to downwards direction
        xy[1] = xy[1] - 1;

    }

}

//Function calculates distance between two points
double distanceP(double xy[]){

    //Variable declaration
    double d = 0;

    //Distance formula
    d = sqrt(((xy[0])*(xy[0]))+((xy[1])*(xy[1])));

    return d;
}