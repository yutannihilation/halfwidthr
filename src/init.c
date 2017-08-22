#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* FIXME: 
Check these declarations against the C/Fortran source code.
*/

/* .Call calls */
extern SEXP _halfwidthr_fullwidth_chars(SEXP, SEXP);
extern SEXP _halfwidthr_halfwidthen(SEXP);
extern SEXP _halfwidthr_hexdump(SEXP);
extern SEXP _halfwidthr_hexinterpret(SEXP);

static const R_CallMethodDef CallEntries[] = {
  {"_halfwidthr_fullwidth_chars", (DL_FUNC) &_halfwidthr_fullwidth_chars, 2},
  {"_halfwidthr_halfwidthen",     (DL_FUNC) &_halfwidthr_halfwidthen,     1},
  {"_halfwidthr_hexdump",         (DL_FUNC) &_halfwidthr_hexdump,         1},
  {"_halfwidthr_hexinterpret",    (DL_FUNC) &_halfwidthr_hexinterpret,    1},
  {NULL, NULL, 0}
};

void R_init_halfwidthr(DllInfo *dll)
{
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}