#include <unistd.h> 
#include <stdio.h>
#include <fcntl.h> 
#include <sys/wait.h>
#include <sys/stat.h>
#include <ctype.h>

#define BUFFER_SIZE 4096;
#define OFFSET_SIZE 4096; // File offset


using namespace std;

int main (int argc, char *argv[]){
  int toUpperCount; // Number of characters to capitalize
  int inputFD;      // Input file descriptor

  pid_t returnedValue = fork(); 
  if(returnedValue < 0){ 
    perror("error forking"); 
    return -1; 
  } else if (returnedValue == 0){ 
    if(close(STDOUT_FILENO) < 0){
      perror("error closing standard output");
      return -1;
    } 
    inputFD = open(argv[1], O_RDWR);

    if(inputFD < 0){
      perror("error opening passwd"); 
      return -1;
    }

    toUpperCount = lseek(inputFD, OFFSET_SIZE, SEEK_SET); // seek all characters in passwd
    toUpperCount = toupper(OFFSET_SIZE); // set all lowercase characters to uppercase equivalents

    perror("error executing toUpper"); 
    return -1; 
    } else { 
      if(waitpid(returnedValue, 0, 0) < 0){
        perror("error waiting for child");
        return -1; 
      }
      printf("Note the parent still has the old standard output.");
    }
}