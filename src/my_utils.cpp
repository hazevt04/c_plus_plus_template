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

std::vector<std::string> split_string(std::string str, std::string delimiter=" ") {
   size_t pos_start = 0;
   size_t pos_end = 0; 
   size_t delim_len = delimiter.length();
   std::string token;
   std::vector<std::string> split_strings;

   while ( (pos_end = str.find(delimiter, pos_start) ) != std::string::npos ) {
      token = str.substr(pos_start, pos_end - pos_start);
      pos_start = pos_end + delim_len;
      split_strings.push_back(token);
   }

   split_strings.push_back(str.substr(pos_start));
   return split_strings;
}

// end of C++ file for utils
