
#ifndef nstd_EXPORT_H
#define nstd_EXPORT_H

#ifdef nstd_BUILT_AS_STATIC
#  define nstd_EXPORT
#  define NSTD_NO_EXPORT
#else
#  ifndef nstd_EXPORT
#    ifdef nstd_EXPORTS
        /* We are building this library */
#      define nstd_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define nstd_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef NSTD_NO_EXPORT
#    define NSTD_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef NSTD_DEPRECATED
#  define NSTD_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef NSTD_DEPRECATED_EXPORT
#  define NSTD_DEPRECATED_EXPORT nstd_EXPORT NSTD_DEPRECATED
#endif

#ifndef NSTD_DEPRECATED_NO_EXPORT
#  define NSTD_DEPRECATED_NO_EXPORT NSTD_NO_EXPORT NSTD_DEPRECATED
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define NSTD_NO_DEPRECATED
#endif

#endif
