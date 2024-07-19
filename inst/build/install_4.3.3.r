install_packages <- function(pkgs, ...) {
  install.packages(pkgs, dependencies = TRUE, ...)
  
  # break if any of the packages was not installed
  not_installed <- setdiff(pkgs, installed.packages()[, 'Package'])
  if (length(not_installed) > 0) {
    stop("The following package(s) could not be installed: ", toString(sQuote(not_installed)))
  }
  invisible(NULL)
}

# This will fail if no internet access, but will print the binaries URL

# select CRAN from switzerland
chooseCRANmirror(ind = 60)
install.packages(
  c('assertthat',
    "av", # used for gganimate
    'devtools',
    "dplyr",
    "gganimate",
    "gifski", # used for gganimate
    "knitr",
    'microbenchmark',
    "qs",
    'Rcpp',
    'RcppParallel',
    'RcppArmadillo',
    'roxygen2',
    "remotes",
    "sf", # used for gganimate
    "stringr",
    'tictoc',
    'testthat',
    "transformr", # used for gganimate
    "XML",
    "xml2",
    "yaml",
    'usethis',
    "zip"),
  dependencies = TRUE)

install.packages(c("devtools"), dependencies = TRUE)
