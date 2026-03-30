# Autor: martian_12
# Check for compress-decompress libraries availability
#
# Define HAVE_LIBZIP if libzip is present
# Define HAVE_LIBZSTD if libzstd is present

AC_CHECK_LIB([zip], [zip_stat],
             [LIBS="$LIBS -lzip" AC_DEFINE([HAVE_LIBZIP], [1], [Define to 1 if you have the 'zip' library])],
             [AC_MSG_ERROR([libzip library not found])]
)
AC_CHECK_LIB([zstd], [ZSTD_decompress],
             [LIBS="$LIBS -lzstd" AC_DEFINE([HAVE_LIBZSTD], [1], [Define to 1 if you have the 'zstd' library])],
             [AC_MSG_ERROR([libzstd library not found])]
)
