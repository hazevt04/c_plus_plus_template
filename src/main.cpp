// C++ File for main

#include <stdlib.h>

#include "sieve.h"

void usage( const char* prog_name ) {
   printf( "Usage: %s <max value>\n", prog_name );
   printf( "\n" );
}

int main( int argc, char** argv ) {
   int val = 50;
   if ( argc > 1 ) {
      val = atoi(argv[1]);
   } else {
      printf( "ERROR: Missing argument for max value\n" );
      usage( argv[0] );
      exit( EXIT_FAILURE );
   }
   int num_primes = 0;
   int* primes = ( int* )calloc( val, sizeof(int) );
   
   printf( "Val is %d\n", val );
   sieve( primes, &num_primes, val );

   for ( int index = 0; index < num_primes; index++ ) {
      printf( "%d) %d\n", index, primes[index] );
   }
   printf( "\n" );

   exit( EXIT_SUCCESS );
} 
