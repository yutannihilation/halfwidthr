// [[Rcpp::plugins(cpp11)]]

#include <Rcpp.h>
#include <iostream>
#include <iomanip>

using namespace Rcpp;

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

//[[Rcpp::export]]
void display_fullwidth_chars(){
  int i1 = 0x80;
  int i2 = 0xEFBC81;
  std::cout << sizeof(i1) << " ";
  std::cout << sizeof(i2);
  
  const int c = 0xEFBC81;
  std::ostringstream s;
  s << c;
  std::cout << s.str();
}