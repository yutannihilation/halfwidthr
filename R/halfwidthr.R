#' halfwidthr
#' 
#' This package converts Japanese alphanumerics (a.k.a. "zenkaku") to ASCII alphanumerics (a.k.a. "hankaku").
#' For example, "１"(0xEFBC91) is converted to "1"(0x31).
#' 
#' @useDynLib halfwidthr, .registration = TRUE
#' @importFrom Rcpp sourceCpp
#' 
#' @name halfwidthr
#' @docType package
NULL