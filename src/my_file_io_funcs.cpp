// C++ File for my_file_io_funcs

#include "my_file_io_funcs.h"

void write_binary_floats_file( float* vals, const char* filename, const int num_vals, const bool debug = false ) {

   std::ofstream ofile;
   int val_num = 0;
   std::streampos file_size;
   ofile.open( filename, std::ios::out | std::ios::binary );
   if ( ofile.is_open() ) {
      std::streamsize val_size = num_vals * sizeof(float);
      debug_printf( debug, "%s(): Val size is %zu bytes\n\n", __func__, val_size );
      ofile.write( (char*)vals, val_size );
   } else {
      printf( "ERROR: Unable to open file, %s, for writing\n", filename );
      exit( EXIT_FAILURE );
   }
   ofile.close();
   if ( !ofile.good() ) {
      printf( "ERROR: While writing file, %s\n", filename );
      exit( EXIT_FAILURE );
   }
}


void check_file_size( long long& file_size, const char* filename, const bool debug = false) {
   
   std::ifstream ifile;
   std::string err_msg = "";
   try {
      ifile.open( filename, std::ios::in | std::ios::binary );
      if ( ifile.is_open() ) {
         // get length of file:
         ifile.seekg (0, ifile.end);
         file_size = (long long)ifile.tellg();
         ifile.seekg (0, ifile.beg);
         debug_printf( debug, "%s(): File size for %s is %llu bytes\n\n", __func__, filename, file_size ); 
      } else {
         err_msg += "Unable to open file, ";
         err_msg += filename;
         err_msg += ", for checking filesize\n";
         throw std::runtime_error(err_msg.c_str());
      }
      ifile.close();
   } catch( std::exception& ex ) {
      printf( "Error: %s\n", ex.what() ); 
      if ( ifile.is_open() ) {
         ifile.close();
      }
      exit(EXIT_FAILURE);
   } // end of catch
   
}


void read_binary_floats_file( float* vals, const char* filename, const int num_vals, const bool debug = false ) {
   
   std::ifstream ifile;
   int val_num = 0;
   std::streampos file_size;
   std::string err_msg = "";
   try {
      ifile.open( filename, std::ios::in | std::ios::binary );
      if ( ifile.is_open() ) {
         size_t val_size = num_vals * sizeof(float);
         debug_printf( debug, "%s(): Val size is %zu bytes\n", __func__, val_size ); 
         ifile.seekg (0, ifile.end);
         long long file_size = (long long)ifile.tellg();
         ifile.seekg (0, ifile.beg);
         debug_printf( debug, "%s(): File size is %llu bytes\n\n", __func__, (long long)file_size ); 
         if ( file_size < val_size ) {
            err_msg += " Expected file size, ";
            err_msg += std::to_string( file_size ); 
            err_msg += " bytes, less than expected: ";
            err_msg +=  std::to_string( val_size ); 
            err_msg += " bytes, for file, ";
            err_msg += filename;
            throw std::runtime_error(err_msg.c_str());
         }
         ifile.read( (char*)vals, file_size );
         ifile.close();
      } else {
         err_msg += "Unable to open file: ";
         err_msg += filename;
         throw std::runtime_error(err_msg.c_str());
      } // end of if ( ifile.is_open() ) {
   } catch( std::exception& ex ) {
      printf( "Error: %s\n", ex.what() ); 
      if ( ifile.is_open() ) {
         ifile.close();
      }
      exit(EXIT_FAILURE);
   }
}



// end of C++ file for my_file_io_funcs
