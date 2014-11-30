context("halfwidthen")

test_that("Convert Japanese numbers", {
  expect_equal(halfwidthen_one("０"), "0")
  
  expect_equal(halfwidthen_one("１２３４５６７８９"), "123456789")
  
  expect_equal(halfwidthen(c("１","１２","１２３")), c("1", "12", "123"))
})

test_that("Convert Japanese alphabets", {
  expect_equal(halfwidthen_one("ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲＳＴＵＶＷＸＹＺ"),
                               "ABCDEFGHIJKLMNOPQRSTUVWXYZ")
  
  expect_equal(halfwidthen_one("ａｂｃｄｅｆｇｈｉｊｋｌｍｎｏｐｑｒｓｔｕｖｗｘｙｚ"), 
                               "abcdefghijklmnopqrstuvwxyz")
  
  expect_equal(halfwidthen(c("ＮＯＲＭＡＬ","ＧＯＯＤ","ＢＡＤ")), 
                           c("NORMAL",      "GOOD",    "BAD"))
})

test_that("Do nothing with ASCII alphanumerics", {
  expect_equal(halfwidthen(c("123", "abc")), c("123", "abc"))
})

test_that("Do nothing with other Japanese Characters", {
  expect_equal(halfwidthen(c("〒", "画竜点睛", "「」")), 
                           c("〒", "画竜点睛", "「」"))
})

test_that("Convert mixed strings", {
  expect_equal(halfwidthen(c("1２3４5６7８9", "ＡBＣｘyｚ")), 
                           c("123456789",     "ABCxyz"))
})