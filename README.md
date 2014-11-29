halfwidthr
==========

Convert Japanese alphanumerics（a.k.a. 全角英数） to ASCII alphanumerics（a.k.a. 半角英数）

# Usage

```R
> x = c("１", "２２Ａ", "３３3")

> halfwidthen(x)
[1] "1"   "22A" "333"
```

# Requirements

* C++11

# Installation

```R
library(devtools)
install_github("yutannihilation/halfwidthr")
```

If you got an error, try these (I'm not sure if this will work...):

```R
Sys.setenv("PKG_CXXFLAGS"="-std=c++11")
```

or

```R
Sys.setenv("PKG_CXXFLAGS"="-std=c++0x")
```