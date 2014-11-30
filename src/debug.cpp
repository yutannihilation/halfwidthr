// [[Rcpp::plugins(cpp11)]]

//' Functions to dig into UTF-8 byte codes.
//' 
//' @title halfwidthr-debug
//' @name halfwidthr-debug
//' 
//' @description
//' \code{hexdump} prints a given UTF-8 string in hex format.
//' 
//' \code{hexinterpret} prints a UTF-8 chars which a given code point corresponds to.
//' 
//' \code{fullwidth_chars} returns correspondence table between code points and UTF-8 chars.
//' 
//' @examples
//' hexdump("あ")
//' hexdump("月が綺麗ですね")
//' 
//' hexinterpret(0xE38384)
//' 
//' crsp_table <- fullwidth_chars()
//' crsp_table[1:10,]

#include <Rcpp.h>
#include <iostream>
#include <iomanip>

using namespace Rcpp;

unsigned int utf8char_bytes(int16_t first_byte);

//' @rdname halfwidthr-debug
//' @param s string to hexdump
//' @export
// [[Rcpp::export]]
void hexdump(std::string s) {
  std::cout << "\"" << s << "\" is ";
  
  std::cout << std::hex << std::uppercase;
  for (char c : s) {
    std::cout << std::setw(2) << std::setfill('0') << ((int16_t) c & 0xFF) << " ";
  }
  
  std::cout << std::endl;
}

std::string utf8code_to_char(int charcode) {
  std::string str;

  for (int i = sizeof(int) - 1; i >= 0; i--) {
    unsigned char c = ((charcode >> 8*i) & 0xFF);
    if(c > 0) str += (char) c;
  }
  
  return std::string(str.begin(), str.end());
}

//' @rdname halfwidthr-debug
//' @param charcode a charcode between 0x00000000 to 0xFFFFFFFF
//' @export
//[[Rcpp::export]]
void hexinterpret(int charcode){
  std::string str = utf8code_to_char(charcode);
  
  std::cout << "0x" << std::hex << std::setfill('0') << charcode;
  std::cout << " is " << str << std::endl;
}

//' @rdname halfwidthr-debug
//' @param start charcode of lower limit of the correspondence table(default: 0xEFBC81, ！)
//' @param end charcode of upper limit of the correspondence table(default: 0xEFBC81, ～)
//' 
//' @export
//[[Rcpp::export]]
DataFrame fullwidth_chars(int start = 0xEFBC81, int end   = 0xEFBD9E){
  std::vector<std::string> utf8code;
  std::vector<std::string> utf8char;
  
  if (start > end) stop("start must be larger than end!");
  
  for (int i = start; i <= end; i++) {
    std::stringstream hexstr;
    hexstr << "0x" << std::hex << std::setfill('0') << i << " ";
    utf8code.push_back(hexstr.str());
    
    utf8char.push_back(utf8code_to_char(i));
  }
  return DataFrame::create(Named("hex")=utf8code, Named("char")=utf8char);
}