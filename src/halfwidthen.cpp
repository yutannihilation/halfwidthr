// [[Rcpp::plugins(cpp11)]]

//' @useDynLib halfwidthr

#include <Rcpp.h>

using namespace Rcpp;

unsigned int utf8char_bytes(int16_t first_byte);
bool is_between(const char* c, const char* start, const char* end);


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

// Return the byte length of a given UTF-8 char.
// Byte length of UTF-8 chars are determined by the first byte.
// According to http://en.wikipedia.org/wiki/UTF-8:
//
// 1) between 0b00000000(0x00) and 0b10111111(0xBF) -> 1 byte length
// 2) between 0b11000000(0xC0) and 0b11011111(0xDF) -> 2 bytes length
// 3) between 0b11100000(0xE0) and 0b11101111(0xEF) -> 3 bytes length
// 4) larger than 0b11110000(0xF0)                  -> 4 butes length
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

// check if a UTF-8 char is between two characters
bool is_between(const char* c, const char* start, const char* end){
  if( strncmp(c, start, 3) >= 0 && strncmp(c, end, 3) <= 0 ) {
    return true;
  } else {
    return false;
  }
}