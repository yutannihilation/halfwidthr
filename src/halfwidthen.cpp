#include "halfwidthr.h"

String halfwidthen_one(const String & x);

//' 
//' Convert Japanese alphanumerics to ASCII alphanumerics
//' 
//' @title halfwidthen
//' @name halfwidthen
//' 
//' @param x A string to convert
//' 
//' @examples
//' x = c("\uff10", "\uff11")
//' halfwidthen(x)
//'
//' @export
// [[Rcpp::export]]
CharacterVector halfwidthen(CharacterVector x) {
  CharacterVector str(x.size());
  std::transform(x.begin(), x.end(), str.begin(), halfwidthen_one);
  return str;
}

String halfwidthen_one(const String & x) {
  String str(x);
  
  // If NA, no need to convert; just return NA
  if(str == NA_STRING) return str;
  
  // convert to UTF-8
  str.set_encoding(CE_UTF8);
  
  std::string std_str(str);
  
  unsigned int length = std_str.size();
  unsigned int pos = 0;
  
  while ( pos < length ) {
    int16_t first_byte = (int16_t) std_str[pos] & 0xFF;
    unsigned int next = utf8char_bytes(first_byte);
    
    if( next == 3 ) {
      if( is_between(&std_str[pos], "０", "９") || 
          is_between(&std_str[pos], "Ａ", "Ｚ") ) {
        std_str.erase(pos, 2);
        std_str[pos] = std_str[pos] - 0x60;
        length = std_str.size();
      } else if( is_between(&std_str[pos], "ａ", "ｚ") ) {
        std_str.erase(pos, 2);
        std_str[pos] = std_str[pos] - 0x20;
        length = std_str.size();
      }
      pos += 1;
    } else {
      pos += next;
    }
  }
  
  return String(std_str, CE_UTF8);
}