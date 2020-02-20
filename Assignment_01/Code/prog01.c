#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void noArgument(int argc, char programName[]);
void tooManyArguments(int argc, char programName[]);
void divisorsOneInt(int number);
void calculateGCD(int firstNumber, int secondNumber);

int main(int argc, char* argv[])
{
    int slash=0;
    //Extra Credit
    //Identifies where the slash is in the program name (if there is one) and puts it in slash
    for(int i=(strlen(argv[0])-1);(i>=0)||(slash==0);i--){
        if(argv[0][i]=='/'){
            slash=i;
        }
    }
    //Create new array the length of everything after the slash+1 so there is room for '\0'
    char progName[(strlen(argv[0]))-(slash-1)];
    int slashPtr=slash;
    //starting at the position after the slash, copy the name of the file into progName for    
    //use with errors
    for(int j=0; j<strlen(progName); j++){
        progName[j]=argv[0][slashPtr+1];
        slashPtr++;
    }
    //Manually put null character into it just in case it is not allocated.
    progName[strlen(progName)]='\0';
    //Checks for errors with amount of arguments
    noArgument(argc, progName);
    tooManyArguments(argc, progName);
    //If only one argument besides the executable is entered
    if(argc==2){
        long long int firstValue;
        //Checks to make sure that the argument given is an integer with the sscanf function and that it is
        //strictly postive, if it is not it prints an error and exits the program
        if(sscanf(argv[1], "%lld", &firstValue) !=1 || firstValue<1){
            printf("%s's argument is not a strictly positive integer.\n", progName);
            exit(0);
        }
        //Calls the function to get the divisors for the value
        divisorsOneInt(firstValue);
    //If two arguments besides the executable are entered
    }else if(argc==3){
        long long int firstValue;
        long long int secondValue;
        //Scans to make sure first argument is an interger and strictly positive
        if(sscanf(argv[1], "%lld", &firstValue) !=1 || firstValue <1){
            printf("%s's first argument is not a strictly positive integer.\n", progName);
            exit(0);
        }
        //Scans to make sure second argument is an integer and strictly positive
        if(sscanf(argv[2], "%lld", &secondValue) !=1 || secondValue<1){
            printf("%s's second argument is not a strictly positive integer.\n", progName);
            exit(0);
        }
        //Calls the function to get the GCD of the two numbers
        calculateGCD(firstValue, secondValue);
    }
    return 0;
}

//Takes in the amount of arguments given to the program from argc and the name of the program from argv[0]
//Will use the number of arguments to see if there are enough declared by the user
void noArgument(int argc, char programName[])
{
    //If there are less than two arguments, they either did not run the program or they did not enter a number
    //If this is triggered, it will give an error statement and exit out of the program, but if there are
    //enough arguments, the program will continue as it should
    if(argc < 2){
        printf("%s launched with no argument\n", programName);
        printf("Proper usage: %s m [n]\n", programName);
        exit(0);
    }
}

//Takes in the amount of arguments given to the program from argc and the name of the program from argv[0]
//Uses the number of arguments to see if there were too many declared by the user
void tooManyArguments(int argc, char programName[])
{
    //If there are more than three arguments,they have too many arguments because the program should take
    //the program name and one int to ask for the divisors or the program name and two ints to ask for the
    //the GCD. If this is triggered, it will give an error statement and exit out of the program
    if(argc > 3){
        printf("%s launched with too many arguments\n", programName);
        printf("Proper usage: %s m [n]\n", programName);
        exit(0);
    }
}

//Takes in the number given to the the program and calculate the divisors for the number and prints them out
void divisorsOneInt(int number){
    printf("The list of divisors of %d is: ", number);
    //The program goes through and does the the number %(mod) i which will go from 1 to the number. and if
    //number%1 is equal to 0 (meaning i can equally divide the number), it will print out i.
    for(int i=1;i<=number;i++){
        //will be triggered at the last value of i (which is equal to number) and print i without a space to
        //make the output have correct spacing before the period and line break
        if(number==i){
          printf("%d", i);
        }
        else if(number%i==0){
            printf("%d, ",i);
        }
    }
    //prints out the period and line break after the last divisor.
    printf(".\n");
}

//Takes in the two numbers given to the program and calculates the GCD between them
void calculateGCD(int firstNumber, int secondNumber){
    //All strictly positive integers have a common divisor of 1 so GCD is defaultly set to 1
    int gcd = 1;
    //This will do firstNumber%i and secondNumber%i at the same time and if they are both 0, it will make
    //i the new value of gcd. It will continue to do this until i is bigger than firstNumber or secondNumber
    for(int i=2; i<=firstNumber && i<=secondNumber;i++){
        if(firstNumber%i==0 && secondNumber%i==0){
            gcd=i;
        }
    }
    printf("The gcd of %d and %d is %d.\n", firstNumber, secondNumber, gcd);
}
