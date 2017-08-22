#include "halfwidthr.h"

//' Dig Into UTF-8 Byte Codes
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
//' hexdump("\\u6708\\u304c\\u7dba\\u9e97\\u3067\\u3059\\u306d")
//' 
//' hexinterpret(0xE38384)
//' 
//' crsp_table <- fullwidth_chars()
//' crsp_table[1:10,]

//' @rdname halfwidthr-debug
//' @param s string to hexdump
//' @export
// [[Rcpp::export]]
void hexdump(std::string s) {
  Rcpp::Rcout << "\"" << s << "\" is ";
  
  Rcpp::Rcout << std::hex << std::uppercase;
  for (auto c : s) {
    Rcpp::Rcout << std::setw(2) << std::setfill('0') << ((int16_t) c & 0xFF) << " ";
  }
  
  Rcpp::Rcout << std::endl;
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
//' @param charcode a charcode between \code{0x00000000} to \code{0xFFFFFFFF}
//' @export
//[[Rcpp::export]]
void hexinterpret(int charcode){
  String str(utf8code_to_char(charcode), CE_UTF8);

  Rcpp::Rcout << "0x" << std::hex << std::setfill('0') << charcode;
  Rcpp::Rcout << " is " << Rf_translateChar(str.get_sexp()) << std::endl;
}

//' @rdname halfwidthr-debug
//' @param start charcode of lower limit of the correspondence table(default: 0xEFBC81)
//' @param end charcode of upper limit of the correspondence table(default: 0xEFBC81)
//' 
//' @export
//[[Rcpp::export]]
DataFrame fullwidth_chars(int start = 0xEFBC81, int end = 0xEFBD9E){
  CharacterVector utf8code, utf8char;

  if (start > end) stop("start must be larger than end!");
  
  for (int i = start; i <= end; i++) {
    std::stringstream hexstr;
    hexstr << "0x" << std::hex << std::setfill('0') << i << " ";
    utf8code.push_back(String(hexstr.str(), CE_UTF8));
    utf8char.push_back(String(utf8code_to_char(i), CE_UTF8));
  }
  return DataFrame::create(Named("hex")=utf8code, Named("char")=utf8char);
}