#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Image {
    int x; // x-coordinate
    int y; //y-coordinate
    char locationName[100]; //name of the location
    int imageNumber; //number of entry (image xxx)
} Image;

// void isCharacter(char loc[], int index);
void checkQuery(char query[], char subject[], Image DataList[], int index);
void searchX(Image DataList[], char subject[], int index);
void searchY(Image DataList[], char subject[], int index);
void searchN(Image DataList[], char subject[], int index);
// void isCharacterQuery(char loc[]);
void printData(Image DataList[], int i);

int main(int argc, char* argv[]){
  //index of how many structs in DataList array
    int index = 0;
    //If there are less than 4 arguments, there are not enough arguments to compute anything.
    if(argc < 4){
        printf("Invalid arguments. try ./<program name> <x coordinate> <y coordinate> <location>.\n");
        exit(0);
    }
    //initializes array of Images
    Image DataList[argc];
    //starting at 1 (0 is ./prog), increment i 3 times because each image is i, i+1 and i+2
    for(int i = 1; i < argc;i += 3){
      //temps for error checking and assigning into structs
        int xValue;
        int yValue;
        char locationValue[1000];
        //if x coordinate is not an integer, ERROR
        if(sscanf(argv[i], "%d", &xValue) != 1){
            printf("The x coordinate in entry number %d is not a valid integer.\n", index);
            exit(0);
        }
        //if y coordinate is not an integer, ERROR
        else if(sscanf(argv[i+1], "%d", &yValue) != 1){
            printf("The y coordinate in entry number %d is not a valid integer.\n", index);
            exit(0);
        }
        //if location is NULL, ERROR
        if(argv[i+2] == NULL){
          printf("The location in entry number %d is not a valid location name.\n", index);
          exit(0);
        }
        //test if location is a string using sscanf to put it into variable and my function isCharacter to check
        sscanf(argv[i+2],"%s", locationValue);
        // isCharacter(locationValue, index);
        //assign each element in the struct to the temp values.
        strcpy(DataList[index].locationName, locationValue);
        DataList[index].x = xValue;
        DataList[index].y = yValue;
        DataList[index].imageNumber = index;
        index++;
    }

    // used to be my function for printing out all the data while it is all in the DataList struct
    // for(int i = 0; i<index;i++){
    //     printData(DataList, i);
    // }
    //function given to us by Herve with my own touch
    int keepGoing = 1;
    while (keepGoing)
    {
        char line[200];
	//	the [^\n] means "any character other than end of line.""  If I wanted, say, other
	//	than tab or end of line, it would be [^\t\n]
	      scanf("%[^\n]", line);
	//	The \n character is still on the standard input, so I need to "consume" it, otherwise
	//	I would keep reading empty lines.
	      getc(stdin);
	//printf("line: -->|%s|<--\n", line);
        //printf("length: %ld", strlen(line));
	      if (strcmp(line, "EXIT") == 0)
	          keepGoing = 0;
	      else
	      {
           // subject is search query, query is the lab -x, -y, -n, etc.
	          char subject[200];
            char query[3];
            //checks the query and the subject
            sscanf(line,"%s %s", query, subject);
            //makes sure that there is not more than a query and a subject, if there is, its an error
            if(line[(strlen(query))+(strlen(subject))+1] != '\0'){
                printf("The query is not valid.\n");
                exit(0);
            }
            //check if query is right.
            checkQuery(query, subject, DataList, index);
	}
    }
    return 0;
}


//function to test if the string loc[] is a valid char array of letters and/or _
//TOLD BY HERVE TO NOT INCLUDE BECAUSE THE NAME CAN CONTAIN ANYTHING BUT A SPACE
// void isCharacter(char loc[], int index){
//   //goes char by char for length of loc and compares it to a through z, A through Z, and _
//     for (int i = 0; i < strlen(loc); i++){
//         if(('a' <= loc[i] && loc[i] <= 'z') || ('A' <= loc[i] && loc[i] <= 'Z') || (loc[i] == '_')){
//         } else{
//           //if not valid, it will output this error
//             printf("The location name in entry number %d is not a valid location name\n", index);
//             exit(0);
//         }
//     }
// }

//function to test if it is a character specifically for the queries (different error message)
//TOLD BY HERVE TO NOT INCLUDE BECAUSE THE NAME CAN CONTAIN ANYTHING BUT A SPACE
// void isCharacterQuery(char loc[]){
//     for (int i = 0; i < strlen(loc); i++){
//         if(('a' <= loc[i] && loc[i] <= 'z') || ('A' <= loc[i] && loc[i] <= 'Z') || (loc[i] == '_')){
//         } else{
//             printf("The query is not valid, please enter a location name after -n.\n");
//             exit(0);
//         }
//     }
// }

//a function to check the query given by the user. detects if query is valid and if it is forwards the subject with
//necessary info to another helper function that computes the query
void checkQuery(char query[], char subject[], Image DataList[], int index){
    //queries -x -y -n all start with -
    if(query[0] == '-'){
    } else{
        printf("The query is not valid, try -x <number>, -y <number>, or -n <name>.\n");
        exit(0);
    }
    //all queries -x -y -n end with \0 on second index
    if(query[2] == '\0'){
    } else{
        printf("The query is not valid, try -x <number>, -y <number>, or -n <name>.\n");
        exit(0);
    }
    //detects if query[1] is x y or z and sends to helped functions
    if(query[1] == 'x'){
        searchX(DataList, subject, index);
    }else if(query[1] == 'n'){
        searchN(DataList, subject, index);
    }else if(query[1] == 'y'){
        searchY(DataList, subject, index);
    } else {
        printf("The query is not valid, try -x <number>, -y <number>, or -n <name>.\n");
        exit(0);
    }
}

//prints the data and computes the accurate image number under 1000 <- limitation that can be changed based on format
//showed in pdf of image number.
void printData(Image DataList[], int i){
    if(DataList[i].imageNumber < 10){
        printf("image 00%d. location: %d, %d. Name: %s.\n", DataList[i].imageNumber %10,DataList[i].x, DataList[i].y, DataList[i].locationName);
    } else if(DataList[i].imageNumber < 100) {
        printf("image 0%d. location: %d, %d. Name: %s.\n", DataList[i].imageNumber %100, DataList[i].x, DataList[i].y, DataList[i].locationName);
    } else if(DataList[i].imageNumber < 1000) {
        printf("image %d. location: %d, %d. Name: %s.\n", DataList[i].imageNumber %1000, DataList[i].x, DataList[i].y, DataList[i].locationName);
    } else if(DataList[i].imageNumber >= 1000) {
        printf("image %d. location: %d, %d. Name: %s.\n", DataList[i].imageNumber, DataList[i].x, DataList[i].y, DataList[i].locationName);
    }
}

//searches for a location based on the name of the city
void searchN(Image DataList[], char subject[], int index){
    // checks if subject is a character
    // isCharacterQuery(subject);
    //documents noneMatch so if there is no matching location it outputs that there is no matching image data
    int noneMatch = 0;
    for(int i = 0; i < index; i++){
      // same to make sure that all the chars are equal
        int same = 1;
        if ((strlen(subject)) == (strlen(DataList[i].locationName))){
            for(int j = 0; (j < strlen(subject)) && (same == 1); j++){
                if(DataList[i].locationName[j] == subject[j]){
                    same = 1;
                }else {
                    same = 0;
                }
            }//if same == 1 locationName is the same a subjecy and print data for the locatonName by going to printData
            if(same==1){
                noneMatch=1;
                printData(DataList, i);
            }
        }
    }
    if(noneMatch == 0){
        printf("No image found at that location.\n");
    }
}

//function that searches DataList by x coordinates
void searchX(Image DataList[], char subject[], int index){
     //temp var for the subject and makes sure it is an int
    int coordinate;
    if(sscanf(subject, "%d", &coordinate) !=  1){
        printf("The x coordinate to search for is not a valid integer.\n");
        exit(0);
    }
    //used the same as noneMatch in searchN
    int noneMatch = 0;
    ///if coordinate==x in datalist output data
    for(int i = 0; i < index; i++){
        if(coordinate == DataList[i].x){
            printData(DataList, i);
            noneMatch = 1;
        }
    }
    if(noneMatch == 0){
        printf("No image found at that location.\n");
    }
}

//function that searches data list by y coordinates
void searchY(Image DataList[], char subject[], int index){
//used the same as in searchX
    int coordinate;
    if(sscanf(subject, "%d", &coordinate) !=  1){
        printf("The y coordinate to search for is not a valid integer.\n");
        exit(0);
    }
    //used the as in searchX
    int noneMatch = 0;
    //if coordinate == data list y coordinate, output data
    for(int i = 0; i < index; i++){
        if(coordinate == DataList[i].y){
            printData(DataList, i);
            noneMatch = 1;
        }
    }
    if(noneMatch == 0){
        printf("No image found at that location.\n");
    }
}
