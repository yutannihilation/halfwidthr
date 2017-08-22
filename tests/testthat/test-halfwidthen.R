context("halfwidthen")

test_that("Convert Japanese numbers", {
  expect_equal(halfwidthen("\uff10"), "0")
  
  expect_equal(halfwidthen("\uff11\uff12\uff13\uff14\uff15\uff16\uff17\uff18\uff19"), "123456789")
  
  expect_equal(halfwidthen(c("\uff11","\uff11\uff12","\uff11\uff12\uff13")), c("1", "12", "123"))
})

test_that("Convert Japanese alphabets", {
  expect_equal(halfwidthen("\uff21\uff22\uff23\uff24\uff25\uff26\uff27\uff28\uff29\uff2a\uff2b\uff2c\uff2d\uff2e\uff2f\uff30\uff31\uff32\uff33\uff34\uff35\uff36\uff37\uff38\uff39\uff3a"),
                               "ABCDEFGHIJKLMNOPQRSTUVWXYZ")
  
  expect_equal(halfwidthen("\uff41\uff42\uff43\uff44\uff45\uff46\uff47\uff48\uff49\uff4a\uff4b\uff4c\uff4d\uff4e\uff4f\uff50\uff51\uff52\uff53\uff54\uff55\uff56\uff57\uff58\uff59\uff5a"), 
                               "abcdefghijklmnopqrstuvwxyz")
  
  expect_equal(halfwidthen(c("\uff2e\uff2f\uff32\uff2d\uff21\uff2c",
                             "\uff27\uff2f\uff2f\uff24",
                             "\uff22\uff21\uff24")), 
                           c("NORMAL",
                             "GOOD",
                             "BAD"))
})

test_that("Do nothing with ASCII alphanumerics", {
  expect_equal(halfwidthen(c("123", "abc")), c("123", "abc"))
})

test_that("Do nothing with other Japanese Characters", {
  expect_equal(halfwidthen(c("\u3012", "\u753b\u7adc\u70b9\u775b", "\u300c\u300d")), 
                           c("\u3012", "\u753b\u7adc\u70b9\u775b", "\u300c\u300d"))
})

test_that("Do nothing with NAs", {
  expect_equal(halfwidthen(c("123", NA)), c("123", NA))
})

test_that("Convert mixed strings", {
  expect_equal(halfwidthen(c("1\uff123\uff145\uff167\uff189", "\uff21B\uff23\uff58y\uff5a")), 
                           c("123456789",     "ABCxyz"))
})

test_that("Convert native characters", {
  expect_equal(halfwidthen(enc2native("\uff10")), "0")
})