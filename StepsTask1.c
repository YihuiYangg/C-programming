#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

// Define any additional variables here
# define max 100


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
    FILE *fptr;
    fptr=fopen("FitnessData_2023.csv","r");

    FITNESS_DATA records[max];
    int numRecords=0;

    while (fscanf(fptr,"%11[^,],%6[^,],%d\n",records[numRecords].date, records[numRecords].time, &records[numRecords].steps)==3){
        numRecords=numRecords+1;
    }

    
    printf("Number of records in file:%d\n",numRecords);

    int i;
    for (i=0;i<3;i++){
        if (strcmp(records[i].time, "07:30") == 0 || strcmp(records[i].time, "07:45") == 0 || strcmp(records[i].time, "08:00") == 0){
            printf("%s/%s/%d\n", records[i].date, records[i].time, records[i].steps);
        }
    }
    fclose(fptr);
    return 0;

}
