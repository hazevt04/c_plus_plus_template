// C++ File for sieve

#include <stdlib.h>
#include <math.h>

#include "sieve.h"

void sieve( int* __restrict__ primes, int* num_primes, int max ) {
   bool prime_flags[max];
   prime_flags[0] = false;
   prime_flags[1] = false;
   for ( int index = 2; index < max; index++ ) {
      prime_flags[index] = true;
   }
   
   int max_sqrt = (int)sqrt( max );
   for ( int outer_index = 2; outer_index < max_sqrt; outer_index++ ) {
      if ( prime_flags[outer_index] ) {
         int outer_squared = outer_index * outer_index;
         for ( int inner_index = outer_squared; inner_index < max; inner_index += outer_index ) {
            prime_flags[inner_index] = false;
         }
      }
   } // end of for loop

   int prime_index = 0;
   for ( int index = 0; index < max; index++ ) {
      if ( prime_flags[index] ) {
         primes[prime_index] = index;
         ++prime_index;
      } // end of if ( prime_flags[index[ )
   }

   *num_primes = prime_index;
} // end of sieve


// end of C++ file for sieve
