#include "halfwidthr.h"

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