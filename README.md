halfwidthr
==========

Convert Japanese alphanumerics（a.k.a. 全角英数） to ASCII alphanumerics（a.k.a. 半角英数）

# Requirements

* C++11

# Installation

```R
library(devtools)
install_github("yutannihilation/halfwidthr")
```

If you got an error, setting this before installation may work(I'm not sure...):

```R
Sys.setenv("PKG_CXXFLAGS"="-std=c++11")

or

Sys.setenv("PKG_CXXFLAGS"="-std=c++0x")
```
