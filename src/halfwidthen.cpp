#include "halfwidthr.h"

//' @useDynLib halfwidthr

//' 
//' Convert Japanese alphanumerics to ASCII alphanumerics
//' 
//' @title halfwidthen
//' @name halfwidthen
//' 
//' @description
//' \code{halfwidthen_one} takes a single string.
//' 
//' \code{halfwidthen} can take character vector whose length is more than one.
//' 
//' @examples
//' x = c("１", "２２Ａ", "３３3")
//' halfwidthen(x)
//' halfwidthen_one(x[1])
//' 
//' \dontrun{
//' # You will see error; halfwidthen_one can take one string as its argument.
//' halfwidthen_one(x)
//' }

//' @rdname halfwidthen
//' @param str a string to convert
//' @return a converted string
//' @export
// [[Rcpp::export]]
std::string halfwidthen_one(String str) {
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
  
  return std_str;
}

//' @rdname halfwidthen
//' @param strs string(s) to convert
//' 
//' @export
// [[Rcpp::export]]
CharacterVector halfwidthen(CharacterVector strs) {  
  for(auto x : strs) {
    if(CharacterVector::is_na(x)) break;
    x = halfwidthen_one(x);
  }
  
  return strs;
}