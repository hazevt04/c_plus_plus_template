#ifndef _UTILS_H_
#define _UTILS_H_

#define SUCCESS 0
#define FAILURE -2

// printf is preferred over std::cout
#ifdef USE_COUT
#  include <iostream>
#else
#  include <cstdio>
#endif

#include <stdarg.h>
#include <cstdlib>
#include <cstddef>
#include <chrono>
#include <string>

#define SWAP(a,b) { \
   (a) ^= (b); \
   (b) ^= (a); \
   (a) ^= (b); \
}

#define MAX(a,b) ((a) > (b)) ? (a) : (b);

#define CEILING(a,b) ((a) + ((b)-1))/(b);

// Hacker's Delight Second Edition pg 44 ('doz')
// Only valid for signed integers, -2^30 < a,b <=(2^30)-1
// or unsigned integers, 0 < a,b <= (2^31)-1
inline int difference_or_zero(int a, int b) {
   return ((a-b) & ~((a-b) >> 31));
}


#define MILLISECONDS_PER_SECOND (1000.0f)
typedef std::chrono::steady_clock Steady_Clock;
typedef std::chrono::time_point<std::chrono::steady_clock> Time_Point;
typedef std::chrono::duration<float, std::milli> Duration_ms;
typedef std::chrono::duration<float, std::micro> Duration_us;
typedef std::chrono::duration<float, std::nano> Duration_ns;

//Example usage:
//Time_Point start = Steady_Clock::now();
//Timed code goes here
//Duration_ms duration_ms = Steady_Clock::now() - start;
//milliseconds = duration_ms.count();
//printf( "CPU: Func() took %f milliseconds to process %d values\n", milliseconds, num_vals );

template <class T>
void gen_vals( T* vals, const T upper, const T lower, const int num_vals ) {
  srand(time(NULL));
  T range = upper - lower + (T)1;
  for( int index = 0; index < num_vals; index++ ) {
    vals[index] = (T)(rand() % (int)range) + lower;
  }
}

int free_these(void *arg1, ...); 
void printf_floats( float* const vals, const int num_vals );
void printf_ints( int* const vals, const int num_vals );
void printf_uints( unsigned int* const vals, const int num_vals );
void printf_ulongs( unsigned long* const vals, const int num_vals );

#define debug_printf( debug, fmt, ... ) { \
   if ( debug ) { \
      printf(fmt, ##__VA_ARGS__); \
   } \
}

#define check_status( status, msg ) { \
   if ( status != SUCCESS ) { \
      printf( "%s(): ERROR: " #msg "\n", __func__ ); \
      exit(EXIT_FAILURE); \
   } \
}

#define try_new( type, ptr, num ) { \
   try { \
      ptr = new type[num]; \
   } catch( const std::bad_alloc& error ) { \
      printf( "%s(): ERROR: new of %d "\
         "items for " #ptr " failed\n", __func__, num ); \
      exit(EXIT_FAILURE); \
   } \
}


#define try_func(status, msg, func) { \
  status = func; \
  check_status( status, msg ); \
}


#define try_delete( ptr ) { \
  if (ptr) delete [] ptr; \
}

#endif
