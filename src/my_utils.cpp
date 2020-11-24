// C++ File for utils

#include "my_utils.hpp"

bool string_is_palindrome(const std::string& s) {
    return std::equal(s.begin(), s.begin() + s.size()/2, s.rbegin());
}

// variadic free function!
int free_these(void *arg1, ...) {
    va_list args;
    void *vp;
    if ( arg1 != NULL ) free(arg1);
    va_start(args, arg1);
    while ((vp = va_arg(args, void *)) != 0)
        if ( vp != NULL ) free(vp);
    va_end(args);
    return SUCCESS;
}

// Boost? Hurrumph!
// String splitter from SO:
// https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
void my_string_splitter( std::vector<std::string>& str_strings, std::string& str, const std::string delimiter = " ", const bool debug=false ) {
   size_t pos = 0;
   dout << __func__ << "(): str at start is '" << str << "'\n";
   while ((pos = str.find(delimiter)) != std::string::npos) {
      dout << __func__ << "(): token is '" <<  str.substr(0, pos) << "'\n";
      str_strings.push_back( str.substr(0, pos) );
      str.erase(0, pos + delimiter.length());
      dout << __func__ << "(): str in while loop is '" << str << "'\n";
   }
   // Get the rest of the string if any
   if ( str != "" ) str_strings.push_back( str );
}
// end of C++ file for utils
