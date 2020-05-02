// C++ File for main

#include "my_file_io_funcs.h"

void usage( const char* prog_name ) {
   printf( "Usage: %s <max value>\n", prog_name );
   printf( "\n" );
}


int main( int argc, char** argv ) {
   std::string filename = "foo.bin";
   bool debug = true;
   int num_vals = 10;
   long long file_size = 0;
   std::ostringstream err_msg_stream( std::ostringstream::ate );

   try {
      float* write_vals = new float[ num_vals * sizeof( float ) ];
      float* read_vals = new float[ num_vals * sizeof( float ) ];

      gen_vals<float>( write_vals, 100, 0, num_vals );
      printf( "Write Values:\n" );
      printf_floats( write_vals, num_vals );

      debug_printf( debug, "The input text file is %s\n", filename.c_str() ); 

      write_binary_floats_file( write_vals, filename.c_str(), num_vals, debug );

      filename = "wrong_file.bin";
      check_file_size( file_size, filename.c_str(), debug ); 

      read_binary_floats_file( read_vals, filename.c_str(), num_vals, debug ); 
      
      printf( "Read Values:\n" );
      printf_floats( read_vals, num_vals );

      int num_mismatches = 0;
      if ( !compare_floats( read_vals, write_vals, num_vals ) ) {
         err_msg_stream <<  "Values read from " << filename << " don't match values written";      
         throw std::runtime_error(err_msg_stream.str().c_str());
      } else {
         printf( "All %d values read from %s matched the values written", num_vals, filename.c_str() );
      }
      return EXIT_SUCCESS;
   } catch( std::exception& ex ) {
      printf( "ERROR: %s\n", ex.what() ); 
      return EXIT_FAILURE;
   }
   
} 

