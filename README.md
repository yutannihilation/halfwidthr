halfwidthr
==========

[![Travis-CI Build Status](https://travis-ci.org/yutannihilation/halfwidthr.svg?branch=master)](https://travis-ci.org/yutannihilation/halfwidthr)

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
