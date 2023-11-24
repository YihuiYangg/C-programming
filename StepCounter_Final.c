#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"


// Struct moved to header file

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array


// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

                    }
                


// Complete the main function
int main() {
    FITNESS_DATA RECORDS[100];
    char line[100];
    char filename[100];

    fgets(line,100,stdin);
    sscanf(line,"%s",filename);

    int counter=0;
    float mean=0;
    char choice;

    while(1){
        

        printf("Menu Options\n");
        printf("A: Specify the filename to be imported\n");
        printf("B: Display the total number of records in the file\n");
        printf("C: Find the date and time of the timeslot with the fewest steps\n");
        printf("D: Find the data and time of the timeslot with the largest number of steps\n");
        printf("E: Find the mean step count of all the records in the file\n");
        printf("F: Find the longest continuous period where the step count is above 500 steps\n");
        printf("Q: Exit");

        choice = getchar();
        while(getchar()!= '\n');
        FILE *input = fopen(filename,"r");

        switch(choice){
            case 'A':
            case 'a':
                
                if(!input){
                    printf("Error: Could not find or open the file.\n");
                    return 1;}
                else{
                printf("File successfully loaded.\n");
                }
                break;

            

            case 'B':
            case 'b':
                while(fgets(line,100,input))
            {
                tokeniseRecord(line,",",RECORDS[counter].date,RECORDS[counter].time,RECORDS[counter].steps);
                counter++;
            }
                printf("Total records:&d\n",counter);
                break;

            case 'C':
            case 'c':
                return 0;
                break;

            case 'D':
            case 'd':
                return 0;
                break;

            case 'E':
            case 'e':
                for(i=0,i < counter,i++;){
                    mean=mean+RECORDS[i].steps;
            }
                mean /= counter;
                printf("Mean step count: %f\n,mean");
                break;

            case 'F':
            case 'f':
                return 0;
                break;


            case 'Q':
            case 'q':
                return 0;
                break;

            default:
                printf("Invalid choice. Try again.\n");
                break;

        }
    }

    

    



   
}









