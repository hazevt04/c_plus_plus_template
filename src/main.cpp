// C++ File for main

#define MY_TEST_STRING 123
#include "my_file_io_funcs.hpp"

void usage( const char* prog_name ) {
   std::cout << "Usage: " << std::string{prog_name} << "<num values> <-e/--error>\n";
}

void test_my_popcount( const int& val ) {
   std::cout << "(My) popcount(" << val << ") is " << my_popcount( val ) << "\n\n"; 
}

void test_my_count_leading_zeros( const int& val ) {
   std::cout << "(My) count_leading_zeros(" << val << ") is " << my_count_leading_zeros( val ) << "\n\n"; 
}

void test_ilog2( const int& val ) {
   std::cout << "Integer Log2(" << val << ") is " << ilog2( val ) << "\n\n"; 
}

void test_my_ilog2( const int& val ) {
   std::cout << "(My) Integer Log2(" << val << ") is " << my_ilog2( val ) << "\n\n"; 
}

void test_is_divisible_by( const int& val, const int& div ) {
   if ( is_divisible_by( val, div ) ) {
      std::cout << val << " is divisible by " << div << "\n\n"; 
   } else {
      std::cout << val << " is NOT divisible by " << div << "\n\n"; 
   }
}

int main( int argc, char** argv ) {
   try {
      std::string filename = "foo.bin";
      bool debug = true;
      int num_vals = 10;
      bool inject_error = false;
      
      if ( argc > 2 ) {
         dout << "argv[2] = " << std::string{argv[ 2 ]} << "\n";
         if ( ( !strcmp( argv[ 2 ], "-e" ) ) || ( !strcmp( argv[ 2 ], "--error" ) ) ) {
            inject_error = true;
         } else {
            throw std::invalid_argument{std::string{"Invalid input: "} + std::string{argv[ 2 ]}};
         }
      } else if ( argc > 1 ) {
         dout << "argv[1] = " << std::string{argv[ 1 ]} << "\n";
         char* end_ptr = nullptr;
         num_vals = (int)strtoul( argv[ 1 ], &end_ptr, 10 );
         if ( *end_ptr != '\0' ) {
            throw std::invalid_argument{std::string{"Invalid input: "} + std::string{argv[ 1 ]}};
         }
      }

      std::string foo_str = "foo";
      double foo_double = 3.141592653589793238462f;
      dout << "Testing debug_cout: num_vals is "
         << num_vals
         << ", foo_str is "
         << foo_str
         << ", foo_double is "
         << foo_double;

      test_my_file_io_funcs( filename, num_vals, inject_error, debug );

      int check_status = 1;
      std::string check_status_str = decode_status( check_status );
      std::cout << "Check Status is " << check_status_str;

      std::string test_string = "Split me up.";
      auto split_strings = split_string( test_string, " " );
      dout << "Test string is " << test_string << "\n";
      for ( auto split_string: split_strings ) {
         dout << "'" << split_string << "'\n";
      }
      dout << "\n\n";

      test_string = "/home/user/path/to/split/up";
      split_strings = split_string( test_string, "/" );
      dout << "Test string is " << test_string << "\n";
      for ( auto split_string: split_strings ) {
         dout << "'" << split_string << "'\n";
      }
      dout << "\n\n";
      
      int val = 8;
      int val2 = ((1u<<21)-1);
      int div = 4;

      test_my_popcount( val );
      test_my_count_leading_zeros( val );
      test_my_ilog2( val );
      test_ilog2( val );
      test_is_divisible_by( val, div );

      test_my_popcount( val2 );
      test_my_count_leading_zeros( val2 );
      test_my_ilog2( val2 );
      test_ilog2( val2 );
      test_is_divisible_by( val2, div );
      std::cout << "Done\n"; 
         
      return EXIT_SUCCESS;

   } catch ( std::exception& ex ) {
      std::cout << "ERROR: " << ex.what() << "\n";
      return EXIT_FAILURE;
   }
}

