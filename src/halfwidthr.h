#ifndef HALFWIDTHR
#define HALFWIDTHR

#include <Rcpp.h>
#include <iostream>
#include <iomanip>

using namespace Rcpp;

unsigned int utf8char_bytes(int16_t first_byte);
bool is_between(const char* c, const char* start, const char* end);

#endif // HALFWIDTHR