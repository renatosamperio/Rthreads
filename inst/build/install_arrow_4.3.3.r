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
