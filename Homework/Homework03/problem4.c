#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#define LOWER_X_CHAR 'x';
#define UPPER_X_CHAR 'X';

using namespace std;

int main( int argc, char *argv[] ) {

  char c;

  if( argc != 3 ) {
    printf("Usage: %s infile outfile", argv[0]);
    return -1;
  }
  // open the file READ-ONLY
  int fd_in = open( argv[1], O_RDONLY );
  if( fd_in < 0 ) {
    perror( argv[1] );                           // check if an error occurred
    return -1;
  }
  struct stat info;
  if( fstat( fd_in, &info ) < 0 ) {
    perror( "Error stating input file" );
    return -1;
  }
  // map the input file into memory
  void *addr_in = mmap( 0, info.st_size, PROT_READ, MAP_SHARED, fd_in, 0 );
  if( addr_in == MAP_FAILED ) {
    perror( "Error mapping input file" );
    return -1;
  }

  while ((c = fgetc(addr_in)) != EOF) {
    if (c == LOWER_X_CHAR || c == UPPER_X_CHAR) {
      printf("'x/X' character found. Exiting program");
      break;
    }
  }
  
  return 0;
}