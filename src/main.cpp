// C++ File for main

#include "my_file_io_funcs.h"

void usage( const char* prog_name ) {
   printf( "Usage: %s <num values> <-e/--error>\n", prog_name );
   printf( "\n" );
}


int main( int argc, char** argv ) {
   std::string filename = "foo.bin";
   bool debug = true;
   int num_vals = 10;
   long long file_size = 0;
   std::ostringstream err_msg_stream( std::ostringstream::ate );
   bool inject_error = false;

   try {
      if ( argc > 2 ) {
         debug_printf( debug, "argv[2] = %s\n", argv[2] ); 
         if ( (!strcmp( argv[2], "-e" )) || (!strcmp( argv[2], "--error" ) ) ) {
            inject_error = true;
         } else {
            err_msg_stream << "Invalid input: " << argv[2];
            throw std::invalid_argument( err_msg_stream.str() );
         }
      } else if ( argc > 1 ) {
         debug_printf( debug, "argv[1] = %s\n", argv[1] ); 
         char* end_ptr = nullptr;
         num_vals = (int)strtoul( argv[1], &end_ptr, 10 );
         if  ( end_ptr == nullptr ) {
            err_msg_stream << "Invalid input: " << argv[1];
            throw std::invalid_argument( err_msg_stream.str() );
         }
      }

      float* write_vals = new float[ num_vals * sizeof( float ) ];
      float* read_vals = new float[ num_vals * sizeof( float ) ];

      gen_vals<float>( write_vals, 100, 0, num_vals );
      printf( "Write Values:\n" );
      printf_floats( write_vals, num_vals );

      debug_printf( debug, "The input text file is %s\n", filename.c_str() ); 

      write_binary_floats_file( write_vals, filename.c_str(), num_vals, debug );

      check_file_size( file_size, filename.c_str(), debug ); 

      if ( inject_error ) {
         filename = "wrong_file.bin";
      }

      read_binary_floats_file( read_vals, filename.c_str(), num_vals, debug ); 
      
      printf( "Read Values:\n" );
      printf_floats( read_vals, num_vals );

      int num_mismatches = 0;
      if ( !compare_floats( read_vals, write_vals, num_vals ) ) {
         err_msg_stream <<  "Values read from " << filename 
            << " don't match values written";      
         throw std::runtime_error( err_msg_stream.str() );
      } else {
         printf( "All %d values read from %s matched the values written\n", 
               num_vals, filename.c_str() );
      }
      return EXIT_SUCCESS;
   
   } catch( std::exception& ex ) {
      printf( "ERROR: %s\n", ex.what() ); 
      return EXIT_FAILURE;
   }
   
}

