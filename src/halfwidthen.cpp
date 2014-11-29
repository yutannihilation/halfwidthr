// [[Rcpp::plugins(cpp11)]]

//' @useDynLib halfwidthr

#include <Rcpp.h>

using namespace Rcpp;

unsigned int utf8char_bytes(int16_t first_byte);

//' Convert Japanese alphanumerics to ASCII alphanumerics
//' 
//' @title halfwidthen
//' @name halfwidthen
//' 
//' @description
//' {{halfwidthen_one}} takes a single string.
//' {{halfwidthen}} can take character vector whose length is more than one.
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
    int16_t first_byte = ((int16_t) std_str[pos] & 0xFF);
    unsigned int next = utf8char_bytes(first_byte);
    
    if ( next != 3 || first_byte != 0xEF ) {
      pos += next;
      continue;
    }
        
    if( strncmp(&std_str[pos], "！", 3) >= 0 && strncmp(&std_str[pos], "～", 3) <= 0 ) {
      std_str.erase(pos, 2);
      std_str[pos] = std_str[pos] - 0x60;
      length = std_str.size();
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

// A byte length of UTF-8 char varies.
// According to http://en.wikipedia.org/wiki/UTF-8, if first byte is...
//
// 1) 0b00000000(0x00) - 0b10111111(0xBF) -> 1 byte length
// 2) 0b11000000(0xC0) - 0b11011111(0xDF) -> 2 bytes length
// 3) 0b11100000(0xE0) - 0b11101111(0xEF) -> 3 bytes length
// 4) larger than 0b11110000(0xF0)        -> 4 butes length

unsigned int utf8char_bytes(int16_t first_byte){
  if (first_byte < 0xC0) {
    return 1;
  } else if (first_byte < 0xE0) {
    return 2;
  } else if (first_byte < 0xF0) {
    return 3;
  } else {
    return 4;
  }
}