// C++ File for main

#include "my_file_io_funcs.hpp"

void usage( const char* prog_name ) {
   std::cout << "Usage: " << std::string{prog_name} << "<num values> <-e/--error>\n";
}


int main( int argc, char** argv ) {
   try {
      std::string filename = "foo.bin";
      bool debug = true;
      int num_vals = 10;
      bool inject_error = false;

      if ( argc > 2 ) {
         debug_cout( debug, "argv[2] = ", std::string{argv[ 2 ]}, "\n" );
         if ( ( !strcmp( argv[ 2 ], "-e" ) ) || ( !strcmp( argv[ 2 ], "--error" ) ) ) {
            inject_error = true;
         } else {
            throw std::invalid_argument{std::string{"Invalid input: "} + std::string{argv[ 2 ]}};
         }
      } else if ( argc > 1 ) {
         debug_cout( debug, "argv[1] = ", std::string{argv[ 1 ]}, "\n" );
         char* end_ptr = nullptr;
         num_vals = (int)strtoul( argv[ 1 ], &end_ptr, 10 );
         if ( end_ptr == nullptr ) {
            throw std::invalid_argument{std::string{"Invalid input: "} + std::string{argv[ 1 ]}};
         }
      }

      std::string foo_str = "foo";
      double foo_double = 3.141592653589793238462f;
      debug_cout( debug,
         "Testing debug_cout: num_vals is ",
         num_vals,
         ", foo_str is ",
         foo_str,
         ", foo_double is ",
         foo_double );

      test_my_file_io_funcs( filename, num_vals, inject_error, debug );

      int check_status = 1;
      std::string check_status_str = decode_status( check_status );
      debug_cout( true, "Check Status is ", check_status_str );

      return EXIT_SUCCESS;

   } catch ( std::exception& ex ) {
      std::cout << "ERROR: " << ex.what() << "\n";
      return EXIT_FAILURE;
   }
}

