// [[Rcpp::plugins(cpp11)]]

#include <Rcpp.h>

using namespace Rcpp;

int utf8char_bytes(int16_t first_byte){
  if (first_byte < 0x80) {
    return 1;
  } else if (first_byte < 0xE0) {
    return 2;
  } else if (first_byte < 0xF0) {
    return 3;
  } else {
    return 4;
  }  
}

// [[Rcpp::export]]
std::string halfwidthen_one(String r_str) {
  std::string std_str(r_str);
  int pos = 0;
  
  while ( pos < std_str.size() ) {
    int16_t first_byte = ((int16_t) std_str[pos] & 0xFF);
    int next = utf8char_bytes(first_byte);
    
    if ( next != 3 || first_byte != 0xEF ) {
      pos += next;
      continue;
    }
        
    if( strncmp(&std_str[pos], "！", 3) >= 0 && strncmp(&std_str[pos], "～", 3) <= 0 ) {
      std_str.erase(pos, 2);
      std_str[pos] = std_str[pos] - 0x60;
    }
  }
  
  return std_str;
}

// [[Rcpp::export]]
CharacterVector halfwidthen(CharacterVector str) {
  int length = str.size();
  
  for(auto x : str) {
    if(CharacterVector::is_na(x)) break;
    x = halfwidthen_one(x);
  }
  
  return str;
}