# select CRAN from switzerland
chooseCRANmirror(ind = 60)
install.packages(
  c('assertthat',
    'devtools',
    "dplyr",
    "gganimate",
    "knitr",
    'microbenchmark',
    "qs",
    'Rcpp',
    'RcppParallel',
    'RcppArmadillo',
    'roxygen2',
    "remotes",
    "stringr",
    'tictoc',
    'testthat',
    "XML",
    "xml2",
    "yaml",
    'usethis',
    "zip"),
  dependencies = TRUE)

install.packages(c("devtools"), dependencies = TRUE)
