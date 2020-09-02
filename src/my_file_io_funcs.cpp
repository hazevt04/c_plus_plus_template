// C++ File for my_file_io_funcs

#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <complex>

#include "utils.h"
#include "my_file_io_funcs.h"


void check_num_file_bytes( llong& num_file_bytes, const char* filename, const bool debug = false) {
   
   std::ifstream ifile;
   std::ostringstream  err_msg_stream( std::ostringstream::ate );
   try {
      ifile.open( filename, std::ios::in | std::ios::binary );
      if ( ifile.is_open() ) {
         // get length of file:
         ifile.seekg (0, ifile.end);
         num_file_bytes = (llong)ifile.tellg();
         ifile.seekg (0, ifile.beg);
         debug_cout( debug, __func__, "(): File size for ", filename, " is ", num_file_bytes, " bytes\n\n" ); 
      } else {
         err_msg_stream << "Unable to open file, " << filename << ", for checking filesize.";
         throw std::runtime_error(err_msg_stream.str());
      }
      ifile.close();
   } catch( std::exception& ex ) {
      std::cerr << __func__ << "(): ERROR: " << ex.what() << "\n"; 
      if ( ifile.is_open() ) {
         ifile.close();
      }
      exit(EXIT_FAILURE);
   } // end of catch
   
} // end of void check_num_file_bytes()


void write_binary_floats_file( float* vals, const char* filename, const int num_vals, 
      const bool debug = false ) {

   std::ofstream ofile;
   int val_num = 0;
   std::streampos num_file_bytes;
   std::ostringstream  err_msg_stream( std::ostringstream::ate );
   try {
      ofile.open( filename, std::ios::out | std::ios::binary );
      if ( ofile.is_open() ) {
         std::streamsize num_val_bytes = num_vals * sizeof(float);
         debug_cout( debug, __func__, "(): Val size is ", num_val_bytes, " bytes\n\n" );
         ofile.write( (char*)vals, num_val_bytes );
      } else {
         err_msg_stream << "Unable to open file, " << filename << ", for writing.";
         throw std::runtime_error(err_msg_stream.str());
      }
      ofile.close();

      if ( ( ofile.rdstate() & std::ofstream::failbit ) != 0 ) {
         err_msg_stream << "Logical error while writing file, " << filename << ".";
         throw std::runtime_error(err_msg_stream.str());
      }
      if ( ( ofile.rdstate() & std::ofstream::badbit ) != 0 ) {
         err_msg_stream << "Write error while writing file, " << filename << ".";
         throw std::runtime_error(err_msg_stream.str());
      }
   } catch( std::exception& ex ) {
      std::cerr << __func__ << "(): ERROR: " << ex.what() << "\n"; 
   }
} // end of write_binary_floats_file() 


void write_binary_complex_floats_file( std::vector<std::complex<float>>& vals, const std::string& filename, const int num_vals, 
      const bool debug = false ) {

   std::ofstream ofile;
   int val_num = 0;
   std::ostringstream  err_msg_stream( std::ostringstream::ate );
   try {
      ofile.open( filename, std::ios::out | std::ios::binary );
      if ( ofile.is_open() ) {
         auto num_val_bytes = num_vals * sizeof(std::complex<float>);
         debug_cout( debug, __func__, "(): Val size is ", num_val_bytes, " bytes\n\n" );
         ofile.write( reinterpret_cast<char*>(vals.data()), num_val_bytes );
      } else {
         err_msg_stream << "Unable to open file, " << filename << ", for writing.";
         throw std::runtime_error(err_msg_stream.str());
      }
      ofile.close();

      if ( ( ofile.rdstate() & std::ofstream::failbit ) != 0 ) {
         err_msg_stream << "Logical error while writing file, " << filename << ".";
         throw std::runtime_error(err_msg_stream.str());
      }
      if ( ( ofile.rdstate() & std::ofstream::badbit ) != 0 ) {
         err_msg_stream << "Write error while writing file, " << filename << ".";
         throw std::runtime_error(err_msg_stream.str());
      }
   } catch( std::exception& ex ) {
      std::cerr << __func__ << "(): ERROR: " << ex.what() << "\n"; 
   }
} // end of write_binary_complex_floats_file()



void read_binary_complex_floats_file( std::vector<std::complex<float>>& vals, const std::string& filename, const int num_vals, const bool debug = false ) {
   
   std::ifstream ifile;
   int val_num = 0;
   std::ostringstream  err_msg_stream( std::ostringstream::ate );
   try {
      ifile.open( filename, std::ios::in | std::ios::binary );
      if ( ifile.is_open() ) {
         size_t num_val_bytes = num_vals * sizeof(std::complex<float>);
         debug_cout( debug, __func__, "(): Val size is ", num_val_bytes, " bytes\n" ); 
         ifile.seekg (0, ifile.end);
         llong num_file_bytes = (llong)ifile.tellg();
         ifile.seekg (0, ifile.beg);
         debug_cout( debug, __func__, "(): File size is ", (llong)num_file_bytes, " bytes\n\n" ); 
         if ( num_file_bytes < num_val_bytes ) {
            err_msg_stream << "Expected file size, " << num_file_bytes << " bytes, less than expected: "
               << num_val_bytes << " bytes, for file " << filename << ".";
            throw std::runtime_error(err_msg_stream.str());
         }
         ifile.read( reinterpret_cast<char*>(vals.data()), num_val_bytes );
         ifile.close();

      } else {
         err_msg_stream << "Unable to open file: " << filename << ".";
         throw std::runtime_error(err_msg_stream.str());
      } // end of if ( ifile.is_open() ) {
   } catch( std::exception& ex ) {
      std::cerr << __func__ << "(): ERROR: " << ex.what() << "\n"; 
      if ( ifile.is_open() ) {
         ifile.close();
      }
      exit(EXIT_FAILURE);
   }
}

void read_binary_floats_file( float* vals, const char* filename, const int num_vals, const bool debug = false ) {
   
   std::ifstream ifile;
   int val_num = 0;
   std::streampos num_file_bytes;
   std::ostringstream  err_msg_stream( std::ostringstream::ate );
   try {
      ifile.open( filename, std::ios::in | std::ios::binary );
      if ( ifile.is_open() ) {
         size_t num_val_bytes = num_vals * sizeof(float);
         debug_cout( debug, __func__, "(): Val size is ", num_val_bytes, "\n" ); 
         ifile.seekg (0, ifile.end);
         llong num_file_bytes = (llong)ifile.tellg();
         ifile.seekg (0, ifile.beg);
         debug_cout( debug, __func__, "(): File size is ", (llong)num_file_bytes, " bytes\n\n" ); 
         if ( num_file_bytes < num_val_bytes ) {
            err_msg_stream << "Expected file size, " << num_file_bytes << " bytes, less than expected: "
               << num_val_bytes << " bytes, for file " << filename << ".";
            throw std::runtime_error(err_msg_stream.str());
         }
         ifile.read( (char*)vals, num_file_bytes );
         ifile.close();

      } else {
         err_msg_stream << "Unable to open file: " << filename << ".";
         throw std::runtime_error(err_msg_stream.str());
      } // end of if ( ifile.is_open() ) {
   } catch( std::exception& ex ) {
      std::cerr << __func__ << "(): ERROR: " << ex.what() << "\n"; 
      if ( ifile.is_open() ) {
         ifile.close();
      }
      exit(EXIT_FAILURE);
   }
}


void test_my_file_io_funcs( std::string filename, const int num_vals, const bool inject_error, const bool debug ) {
   float* write_vals = nullptr;
   float* read_vals = nullptr;
   try {
      llong num_file_bytes = 0;

      write_vals = new float[ num_vals * sizeof( float ) ];
      read_vals = new float[ num_vals * sizeof( float ) ];
      std::ostringstream err_msg_stream( std::ostringstream::ate );
      
      gen_vals<float>( write_vals, 100, 0, num_vals );
      std::cout << "Write Values:\n";
      printf_floats( write_vals, num_vals );

      debug_cout( debug, "The input text file is %s\n", filename.c_str() ); 

      write_binary_floats_file( write_vals, filename.c_str(), num_vals, debug );

      check_num_file_bytes( num_file_bytes, filename.c_str(), debug ); 

      if ( inject_error ) {
         filename = "wrong_file.bin";
      }

      read_binary_floats_file( read_vals, filename.c_str(), num_vals, debug ); 
      
      std::cout << "Read Values:\n";
      printf_floats( read_vals, num_vals );

      int num_mismatches = 0;
      if ( !compare_floats( read_vals, write_vals, num_vals ) ) {
         err_msg_stream <<  "Values read from " << filename 
            << " don't match values written";      
         throw std::runtime_error( err_msg_stream.str() );
      } else {
         std::cout << "All " << num_vals << " values read from " << filename << " matched the values written\n";
      }
      delete [] write_vals;
      delete [] read_vals;

   } catch ( std::exception& ex ) {
      std::cerr << __func__ << "(): ERROR: " << ex.what() << "\n"; 
      if ( write_vals ) delete [] write_vals;
      if ( read_vals ) delete [] read_vals;
   }

}


// end of C++ file for my_file_io_funcs
