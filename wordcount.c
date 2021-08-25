#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <unistd.h>
/*
 * File: wordcount.c
 * Tiffany Tran ... Implemented function comes after main....
 */



/*
 * YOUR COMMENTS: n/a
 */


int main(int argc, char *argv[])
{
  // YOU NEED TO IMPLEMENT THIS + some other functions! 
  int i,results = 0,  n = argc-1;
  pid_t cPID;  // the child process that the execution will soon run inside of. 
  int success = 0, failed = 0; 

  for(i=1; i < argc; i++) {  //create child processes depending on how many files given
    cPID = fork(); //fork
    if (cPID == 0) { 
      // child process 

      // call a function to count and return the number of words in file argv[i]
      char *file = argv[i];
      int num = countWords(file);
      int pid = getpid();
      
      //testing to see what num returns 
      //printf("%d num is %d", i, num);
      
      // print the number of words in file argv[i] or error message if file argv[i] does not exist
      if(num != -3){
        printf("\nChild process pid_%d for %s: number of words is %d\n", pid, argv[i], num);
        // Otherwise; return/exit with an exit code of 0 indicting that a file is counted sucessfully!
        exit(0);
      }else{
        printf("\nChild process pid_%d for %s: does not exist\n", pid, argv[i]);
        // return/exit with an exit code of 1 if the file argv[i] does not exist. 
        exit(1);
      }//end of if else

    }else if(cPID < 0){//fork doesn't return 0
      printf("\nFork failed\n");
    }else{

      waitpid(cPID, &results,0);  // Parent process waits here for child to terminate.
      
      if (results == 0){  // Verify child process terminated without error.  
        success++; //return normally
      }else{
        failed++; //returned error
      }//end of if else

    }//end if else 

  }//end for loop

  printf("\nParent process created %d child processes to count words in %d files\n", n, n);
  printf("%d file(s) have been counted successfully!\n", success);
  printf("%d file(s) did not exist\n\n", failed);

  return 0;
}


/* Function: countWords(char *file)
USAGE: num = countWords(file)
Takes a file name as a parameter and 
checks to see if the file exist or not
if it does not exist returns -3 
if the file exists it opens the file 
and begins counting how many words 
are in the file
 */
int countWords(char *file){

  int wordCount = 1; //initilaize wordcount
  FILE *openFile; //create file pointer
  char c, currWord[120]; //create char variables

  if( access( file, F_OK ) == 0 ) { //check to see if file exist

    openFile = fopen(file, "r"); //open file in read mode

    while((c= fgetc(openFile)) != EOF){ //iterate through file and when it gets to end of file stop loop
        while (fscanf(openFile, "%s", currWord) == 1) { //read one word at a time 
        wordCount++; //increment word count
        }//end while
    }//end of while

    if(wordCount == 0){ //if wordcount is 0 then dont do anything
    }else{//else get rid of excess one
    wordCount--;//get rid of excess one since we didn't intitialize as 0 based indexing
    }//end of if else

    fclose(openFile); //close file
  } else { //if file does not exist
    wordCount = -3;
  }

  return wordCount;
}
   