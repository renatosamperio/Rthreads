install_packages <- function(pkgs, ...) {
  install.packages(pkgs, dependencies = TRUE, ...)
  
  # break if any of the packages was not installed
  not_installed <- setdiff(pkgs, installed.packages()[, 'Package'])
  if (length(not_installed) > 0) {
    stop("The following package(s) could not be installed: ", toString(sQuote(not_installed)))
  }
  invisible(NULL)
}

# Install all compression types with "arrow" package.
Sys.setenv(
  "ARROW_WITH_BROTLI" = TRUE,
  "ARROW_WITH_BZ2" = TRUE,
  "ARROW_WITH_LZ4" = TRUE,
  "ARROW_WITH_SNAPPY" = TRUE,
  "ARROW_WITH_ZLIB" = TRUE,
  "ARROW_WITH_ZSTD" = TRUE,
  "ARROW_PARQUET" = TRUE,
  "LIBARROW_BUILD" = FALSE,
  "ARROW_R_DEV" = TRUE,
  "ARROW_BUILD_INTEGRATION" = FALSE,
  "ARROW_BUILD_STATIC" = FALSE,
  "ARROW_BUILD_TESTS" = FALSE,
  "ARROW_EXTRA_ERROR_CONTEXT" = TRUE,
  "ARROW_WITH_RE2" = FALSE,
  "ARROW_WITH_UTF8PROC" = FALSE,
  "ARROW_WITH_UTF8PROC" = FALSE
)

# select CRAN from switzerland
chooseCRANmirror(ind = 60)
install.packages(
  c('arrow'),
  dependencies = TRUE)
