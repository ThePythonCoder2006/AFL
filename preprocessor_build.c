# 1 "src/main.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "src/main.c"
# 1 "c:\\mingw\\include\\stdlib.h" 1 3
# 34 "c:\\mingw\\include\\stdlib.h" 3

# 35 "c:\\mingw\\include\\stdlib.h" 3
# 49 "c:\\mingw\\include\\stdlib.h" 3
# 1 "c:\\mingw\\include\\_mingw.h" 1 3
# 55 "c:\\mingw\\include\\_mingw.h" 3

# 56 "c:\\mingw\\include\\_mingw.h" 3
# 66 "c:\\mingw\\include\\_mingw.h" 3
# 1 "c:\\mingw\\include\\msvcrtver.h" 1 3
# 35 "c:\\mingw\\include\\msvcrtver.h" 3

# 36 "c:\\mingw\\include\\msvcrtver.h" 3
# 67 "c:\\mingw\\include\\_mingw.h" 2 3

# 1 "c:\\mingw\\include\\w32api.h" 1 3
# 35 "c:\\mingw\\include\\w32api.h" 3

# 36 "c:\\mingw\\include\\w32api.h" 3
# 59 "c:\\mingw\\include\\w32api.h" 3
# 1 "c:\\mingw\\include\\sdkddkver.h" 1 3
# 35 "c:\\mingw\\include\\sdkddkver.h" 3

# 36 "c:\\mingw\\include\\sdkddkver.h" 3
# 60 "c:\\mingw\\include\\w32api.h" 2 3
# 74 "c:\\mingw\\include\\_mingw.h" 2 3
# 50 "c:\\mingw\\include\\stdlib.h" 2 3

# 1 "c:\\mingw\\lib\\gcc\\mingw32\\6.3.0\\include\\stddef.h" 1 3 4
# 216 "c:\\mingw\\lib\\gcc\\mingw32\\6.3.0\\include\\stddef.h" 3 4

# 216 "c:\\mingw\\lib\\gcc\\mingw32\\6.3.0\\include\\stddef.h" 3 4
typedef unsigned int size_t;
# 328 "c:\\mingw\\lib\\gcc\\mingw32\\6.3.0\\include\\stddef.h" 3 4
typedef short unsigned int wchar_t;
# 56 "c:\\mingw\\include\\stdlib.h" 2 3
# 90 "c:\\mingw\\include\\stdlib.h" 3

# 99 "c:\\mingw\\include\\stdlib.h" 3
extern int _argc;
extern char **_argv;

extern __attribute__((__cdecl__)) __attribute__((__nothrow__)) int *__p___argc(void);
extern __attribute__((__cdecl__)) __attribute__((__nothrow__)) char ***__p___argv(void);
extern __attribute__((__cdecl__)) __attribute__((__nothrow__)) wchar_t ***__p___wargv(void);
# 142 "c:\\mingw\\include\\stdlib.h" 3
extern __attribute__((__dllimport__)) int __mb_cur_max;
# 166 "c:\\mingw\\include\\stdlib.h" 3
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int *_errno(void);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) int *__doserrno(void);

extern __attribute__((__cdecl__)) __attribute__((__nothrow__)) char ***__p__environ(void);

extern __attribute__((__cdecl__)) __attribute__((__nothrow__)) wchar_t ***__p__wenviron(void);
# 202 "c:\\mingw\\include\\stdlib.h" 3
extern __attribute__((__dllimport__)) int _sys_nerr;
# 227 "c:\\mingw\\include\\stdlib.h" 3
extern __attribute__((__dllimport__)) char *_sys_errlist[];
# 238 "c:\\mingw\\include\\stdlib.h" 3
extern __attribute__((__cdecl__)) __attribute__((__nothrow__)) unsigned int *__p__osver(void);
extern __attribute__((__cdecl__)) __attribute__((__nothrow__)) unsigned int *__p__winver(void);
extern __attribute__((__cdecl__)) __attribute__((__nothrow__)) unsigned int *__p__winmajor(void);
extern __attribute__((__cdecl__)) __attribute__((__nothrow__)) unsigned int *__p__winminor(void);
# 250 "c:\\mingw\\include\\stdlib.h" 3
extern __attribute__((__dllimport__)) unsigned int _osver;
extern __attribute__((__dllimport__)) unsigned int _winver;
extern __attribute__((__dllimport__)) unsigned int _winmajor;
extern __attribute__((__dllimport__)) unsigned int _winminor;
# 289 "c:\\mingw\\include\\stdlib.h" 3
__attribute__((__cdecl__)) __attribute__((__nothrow__)) char **__p__pgmptr(void);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) wchar_t **__p__wpgmptr(void);
# 325 "c:\\mingw\\include\\stdlib.h" 3
extern __attribute__((__dllimport__)) int _fmode;
# 335 "c:\\mingw\\include\\stdlib.h" 3
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int atoi(const char *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) long atol(const char *);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) double strtod(const char *, char **);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) double atof(const char *);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) double _wtof(const wchar_t *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int _wtoi(const wchar_t *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) long _wtol(const wchar_t *);
# 378 "c:\\mingw\\include\\stdlib.h" 3
__attribute__((__cdecl__)) __attribute__((__nothrow__)) float strtof(const char *__restrict__, char **__restrict__);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) long double strtold(const char *__restrict__, char **__restrict__);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) long strtol(const char *, char **, int);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) unsigned long strtoul(const char *, char **, int);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) long wcstol(const wchar_t *, wchar_t **, int);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) unsigned long wcstoul(const wchar_t *, wchar_t **, int);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) double wcstod(const wchar_t *, wchar_t **);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) float wcstof(const wchar_t *__restrict__, wchar_t **__restrict__);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) long double wcstold(const wchar_t *__restrict__, wchar_t **__restrict__);
# 451 "c:\\mingw\\include\\stdlib.h" 3
__attribute__((__cdecl__)) __attribute__((__nothrow__)) wchar_t *_wgetenv(const wchar_t *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int _wputenv(const wchar_t *);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) void _wsearchenv(const wchar_t *, const wchar_t *, wchar_t *);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) int _wsystem(const wchar_t *);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) void _wmakepath(wchar_t *, const wchar_t *, const wchar_t *, const wchar_t *,
                                                                        const wchar_t *);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) void _wsplitpath(const wchar_t *, wchar_t *, wchar_t *, wchar_t *, wchar_t *);

__attribute__((__cdecl__)) __attribute__((__nothrow__))
wchar_t *
_wfullpath(wchar_t *, const wchar_t *, size_t);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) size_t wcstombs(char *, const wchar_t *, size_t);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int wctomb(char *, wchar_t);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) int mblen(const char *, size_t);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) size_t mbstowcs(wchar_t *, const char *, size_t);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int mbtowc(wchar_t *, const char *, size_t);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) int rand(void);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) void srand(unsigned int);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) void *calloc(size_t, size_t) __attribute__((__malloc__));
__attribute__((__cdecl__)) __attribute__((__nothrow__)) void *malloc(size_t) __attribute__((__malloc__));
__attribute__((__cdecl__)) __attribute__((__nothrow__)) void *realloc(void *, size_t);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) void free(void *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) void abort(void) __attribute__((__noreturn__));
__attribute__((__cdecl__)) __attribute__((__nothrow__)) void exit(int) __attribute__((__noreturn__));

int __attribute__((__cdecl__)) __attribute__((__nothrow__)) atexit(void (*)(void));

__attribute__((__cdecl__)) __attribute__((__nothrow__)) int system(const char *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) char *getenv(const char *);

__attribute__((__cdecl__)) void *bsearch(const void *, const void *, size_t, size_t, int (*)(const void *, const void *));

__attribute__((__cdecl__)) void qsort(void *, size_t, size_t, int (*)(const void *, const void *));

__attribute__((__cdecl__)) __attribute__((__nothrow__)) int abs(int) __attribute__((__const__));
__attribute__((__cdecl__)) __attribute__((__nothrow__)) long labs(long) __attribute__((__const__));
# 519 "c:\\mingw\\include\\stdlib.h" 3
typedef struct
{
  int quot, rem;
} div_t;
typedef struct
{
  long quot, rem;
} ldiv_t;

__attribute__((__cdecl__)) __attribute__((__nothrow__)) div_t div(int, int) __attribute__((__const__));
__attribute__((__cdecl__)) __attribute__((__nothrow__)) ldiv_t ldiv(long, long) __attribute__((__const__));

__attribute__((__cdecl__)) __attribute__((__nothrow__)) void _exit(int) __attribute__((__noreturn__));

__attribute__((__cdecl__)) __attribute__((__nothrow__)) long long _atoi64(const char *);
# 545 "c:\\mingw\\include\\stdlib.h" 3
__attribute__((__cdecl__)) __attribute__((__nothrow__)) void _beep(unsigned int, unsigned int) __attribute__((__deprecated__));

__attribute__((__cdecl__)) __attribute__((__nothrow__)) void _seterrormode(int) __attribute__((__deprecated__));
__attribute__((__cdecl__)) __attribute__((__nothrow__)) void _sleep(unsigned long) __attribute__((__deprecated__));

typedef int (*_onexit_t)(void);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) _onexit_t _onexit(_onexit_t);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) int _putenv(const char *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) void _searchenv(const char *, const char *, char *);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) char *_ecvt(double, int, int *, int *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) char *_fcvt(double, int, int *, int *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) char *_gcvt(double, int, char *);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) void _makepath(char *, const char *, const char *, const char *, const char *);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) void _splitpath(const char *, char *, char *, char *, char *);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) char *_fullpath(char *, const char *, size_t);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) char *_itoa(int, char *, int);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) char *_ltoa(long, char *, int);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) char *_ultoa(unsigned long, char *, int);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) wchar_t *_itow(int, wchar_t *, int);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) wchar_t *_ltow(long, wchar_t *, int);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) wchar_t *_ultow(unsigned long, wchar_t *, int);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) char *_i64toa(long long, char *, int);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) char *_ui64toa(unsigned long long, char *, int);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) long long _wtoi64(const wchar_t *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) wchar_t *_i64tow(long long, wchar_t *, int);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) wchar_t *_ui64tow(unsigned long long, wchar_t *, int);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) unsigned int(_rotl)(unsigned int, int) __attribute__((__const__));
__attribute__((__cdecl__)) __attribute__((__nothrow__)) unsigned int(_rotr)(unsigned int, int) __attribute__((__const__));
__attribute__((__cdecl__)) __attribute__((__nothrow__)) unsigned long(_lrotl)(unsigned long, int) __attribute__((__const__));
__attribute__((__cdecl__)) __attribute__((__nothrow__)) unsigned long(_lrotr)(unsigned long, int) __attribute__((__const__));

__attribute__((__cdecl__)) __attribute__((__nothrow__)) int _set_error_mode(int);
# 628 "c:\\mingw\\include\\stdlib.h" 3
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int putenv(const char *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) void searchenv(const char *, const char *, char *);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) char *itoa(int, char *, int);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) char *ltoa(long, char *, int);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) char *ecvt(double, int, int *, int *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) char *fcvt(double, int, int *, int *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) char *gcvt(double, int, char *);
# 649 "c:\\mingw\\include\\stdlib.h" 3
__attribute__((__cdecl__)) __attribute__((__nothrow__)) void _Exit(int) __attribute__((__noreturn__));

extern inline __attribute__((__gnu_inline__))
__attribute__((__cdecl__)) __attribute__((__nothrow__)) void
_Exit(int __status) { _exit(__status); }

typedef struct
{
  long long quot, rem;
} lldiv_t;
__attribute__((__cdecl__)) __attribute__((__nothrow__)) lldiv_t lldiv(long long, long long) __attribute__((__const__));

__attribute__((__cdecl__)) __attribute__((__nothrow__)) long long llabs(long long);

extern inline __attribute__((__gnu_inline__))

__attribute__((__cdecl__)) __attribute__((__nothrow__)) long long
llabs(long long __j)
{
  return __j >= 0 ? __j : -__j;
}

__attribute__((__cdecl__)) __attribute__((__nothrow__)) long long strtoll(const char *__restrict__, char **__restrict, int);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) unsigned long long strtoull(const char *__restrict__, char **__restrict__, int);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) long long atoll(const char *);

extern inline __attribute__((__gnu_inline__))
__attribute__((__cdecl__)) __attribute__((__nothrow__)) long long
atoll(const char *_c) { return _atoi64(_c); }
# 726 "c:\\mingw\\include\\stdlib.h" 3
__attribute__((__cdecl__)) __attribute__((__nothrow__)) __attribute__((__deprecated__)) long long wtoll(const wchar_t *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) __attribute__((__deprecated__)) char *lltoa(long long, char *, int);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) __attribute__((__deprecated__)) char *ulltoa(unsigned long long, char *, int);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) __attribute__((__deprecated__)) wchar_t *lltow(long long, wchar_t *, int);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) __attribute__((__deprecated__)) wchar_t *ulltow(unsigned long long, wchar_t *, int);

extern inline __attribute__((__gnu_inline__))
__attribute__((__cdecl__)) __attribute__((__nothrow__)) char *
lltoa(long long __n, char *__c, int __i)
{
  return _i64toa(__n, __c, __i);
}

extern inline __attribute__((__gnu_inline__))
__attribute__((__cdecl__)) __attribute__((__nothrow__)) char *
ulltoa(unsigned long long __n, char *__c, int __i)
{
  return _ui64toa(__n, __c, __i);
}

extern inline __attribute__((__gnu_inline__))
__attribute__((__cdecl__)) __attribute__((__nothrow__)) long long
wtoll(const wchar_t *__w) { return _wtoi64(__w); }

extern inline __attribute__((__gnu_inline__))
__attribute__((__cdecl__)) __attribute__((__nothrow__)) wchar_t *
lltow(long long __n, wchar_t *__w, int __i)
{
  return _i64tow(__n, __w, __i);
}

extern inline __attribute__((__gnu_inline__))
__attribute__((__cdecl__)) __attribute__((__nothrow__)) wchar_t *
ulltow(unsigned long long __n, wchar_t *__w, int __i)
{
  return _ui64tow(__n, __w, __i);
}
# 766 "c:\\mingw\\include\\stdlib.h" 3
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int mkstemp(char *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int __mingw_mkstemp(int, char *);
# 808 "c:\\mingw\\include\\stdlib.h" 3
extern inline __attribute__((__gnu_inline__)) __attribute__((__always_inline__))
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int
mkstemp(char *__filename_template)
{
  return __mingw_mkstemp(0, __filename_template);
}
# 819 "c:\\mingw\\include\\stdlib.h" 3
__attribute__((__cdecl__)) __attribute__((__nothrow__)) char *mkdtemp(char *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) char *__mingw_mkdtemp(char *);

extern inline __attribute__((__gnu_inline__)) __attribute__((__always_inline__))
__attribute__((__cdecl__)) __attribute__((__nothrow__)) char *
mkdtemp(char *__dirname_template)
{
  return __mingw_mkdtemp(__dirname_template);
}

__attribute__((__cdecl__)) __attribute__((__nothrow__)) int setenv(const char *, const char *, int);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int unsetenv(const char *);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) int __mingw_setenv(const char *, const char *, int);

extern inline __attribute__((__gnu_inline__)) __attribute__((__always_inline__))
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int
setenv(const char *__n, const char *__v, int __f)
{
  return __mingw_setenv(__n, __v, __f);
}

extern inline __attribute__((__gnu_inline__)) __attribute__((__always_inline__))
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int
unsetenv(const char *__name)
{
  return __mingw_setenv(__name, ((void *)0), 1);
}

# 2 "src/main.c" 2
# 1 "c:\\mingw\\include\\stdio.h" 1 3
# 38 "c:\\mingw\\include\\stdio.h" 3

# 39 "c:\\mingw\\include\\stdio.h" 3
# 69 "c:\\mingw\\include\\stdio.h" 3
# 1 "c:\\mingw\\lib\\gcc\\mingw32\\6.3.0\\include\\stddef.h" 1 3 4
# 357 "c:\\mingw\\lib\\gcc\\mingw32\\6.3.0\\include\\stddef.h" 3 4
typedef short unsigned int wint_t;
# 70 "c:\\mingw\\include\\stdio.h" 2 3
# 94 "c:\\mingw\\include\\stdio.h" 3
# 1 "c:\\mingw\\include\\sys/types.h" 1 3
# 34 "c:\\mingw\\include\\sys/types.h" 3

# 35 "c:\\mingw\\include\\sys/types.h" 3
# 62 "c:\\mingw\\include\\sys/types.h" 3
typedef long __off32_t;

typedef __off32_t _off_t;

typedef _off_t off_t;
# 91 "c:\\mingw\\include\\sys/types.h" 3
typedef long long __off64_t;

typedef __off64_t off64_t;
# 115 "c:\\mingw\\include\\sys/types.h" 3
typedef int _ssize_t;

typedef _ssize_t ssize_t;
# 95 "c:\\mingw\\include\\stdio.h" 2 3

# 1 "c:\\mingw\\lib\\gcc\\mingw32\\6.3.0\\include\\stdarg.h" 1 3 4
# 40 "c:\\mingw\\lib\\gcc\\mingw32\\6.3.0\\include\\stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 103 "c:\\mingw\\include\\stdio.h" 2 3
# 210 "c:\\mingw\\include\\stdio.h" 3
typedef struct _iobuf
{
  char *_ptr;
  int _cnt;
  char *_base;
  int _flag;
  int _file;
  int _charbuf;
  int _bufsiz;
  char *_tmpfname;
} FILE;
# 239 "c:\\mingw\\include\\stdio.h" 3
extern __attribute__((__dllimport__)) FILE _iob[];
# 252 "c:\\mingw\\include\\stdio.h" 3

__attribute__((__cdecl__)) __attribute__((__nothrow__)) FILE *fopen(const char *, const char *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) FILE *freopen(const char *, const char *, FILE *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int fflush(FILE *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int fclose(FILE *);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) int remove(const char *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int rename(const char *, const char *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) FILE *tmpfile(void);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) char *tmpnam(char *);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) char *_tempnam(const char *, const char *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int _rmtmp(void);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int _unlink(const char *);
# 289 "c:\\mingw\\include\\stdio.h" 3
__attribute__((__cdecl__)) __attribute__((__nothrow__)) char *tempnam(const char *, const char *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int rmtmp(void);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int unlink(const char *);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) int setvbuf(FILE *, char *, int, size_t);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) void setbuf(FILE *, char *);
# 342 "c:\\mingw\\include\\stdio.h" 3
extern int __attribute__((__cdecl__)) __attribute__((__nothrow__)) __attribute__((__format__(__mingw_printf__, 2, 3))) __mingw_fprintf(FILE *, const char *, ...);
extern int __attribute__((__cdecl__)) __attribute__((__nothrow__)) __attribute__((__format__(__mingw_printf__, 1, 2))) __mingw_printf(const char *, ...);
extern int __attribute__((__cdecl__)) __attribute__((__nothrow__)) __attribute__((__format__(__mingw_printf__, 2, 3))) __mingw_sprintf(char *, const char *, ...);
extern int __attribute__((__cdecl__)) __attribute__((__nothrow__)) __attribute__((__format__(__mingw_printf__, 3, 4))) __mingw_snprintf(char *, size_t, const char *, ...);
extern int __attribute__((__cdecl__)) __attribute__((__nothrow__)) __attribute__((__format__(__mingw_printf__, 2, 0))) __mingw_vfprintf(FILE *, const char *, __builtin_va_list);
extern int __attribute__((__cdecl__)) __attribute__((__nothrow__)) __attribute__((__format__(__mingw_printf__, 1, 0))) __mingw_vprintf(const char *, __builtin_va_list);
extern int __attribute__((__cdecl__)) __attribute__((__nothrow__)) __attribute__((__format__(__mingw_printf__, 2, 0))) __mingw_vsprintf(char *, const char *, __builtin_va_list);
extern int __attribute__((__cdecl__)) __attribute__((__nothrow__)) __attribute__((__format__(__mingw_printf__, 3, 0))) __mingw_vsnprintf(char *, size_t, const char *, __builtin_va_list);
# 376 "c:\\mingw\\include\\stdio.h" 3
extern unsigned int _mingw_output_format_control(unsigned int, unsigned int);
# 453 "c:\\mingw\\include\\stdio.h" 3
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int fprintf(FILE *, const char *, ...);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int printf(const char *, ...);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int sprintf(char *, const char *, ...);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int vfprintf(FILE *, const char *, __builtin_va_list);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int vprintf(const char *, __builtin_va_list);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int vsprintf(char *, const char *, __builtin_va_list);
# 478 "c:\\mingw\\include\\stdio.h" 3
int __attribute__((__cdecl__)) __attribute__((__nothrow__)) __attribute__((__format__(__ms_printf__, 2, 3))) __msvcrt_fprintf(FILE *, const char *, ...);
int __attribute__((__cdecl__)) __attribute__((__nothrow__)) __attribute__((__format__(__ms_printf__, 1, 2))) __msvcrt_printf(const char *, ...);
int __attribute__((__cdecl__)) __attribute__((__nothrow__)) __attribute__((__format__(__ms_printf__, 2, 3))) __msvcrt_sprintf(char *, const char *, ...);
int __attribute__((__cdecl__)) __attribute__((__nothrow__)) __attribute__((__format__(__ms_printf__, 2, 0))) __msvcrt_vfprintf(FILE *, const char *, __builtin_va_list);
int __attribute__((__cdecl__)) __attribute__((__nothrow__)) __attribute__((__format__(__ms_printf__, 1, 0))) __msvcrt_vprintf(const char *, __builtin_va_list);
int __attribute__((__cdecl__)) __attribute__((__nothrow__)) __attribute__((__format__(__ms_printf__, 2, 0))) __msvcrt_vsprintf(char *, const char *, __builtin_va_list);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) int _snprintf(char *, size_t, const char *, ...);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int _vsnprintf(char *, size_t, const char *, __builtin_va_list);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int _vscprintf(const char *, __builtin_va_list);
# 501 "c:\\mingw\\include\\stdio.h" 3
__attribute__((__cdecl__)) __attribute__((__nothrow__)) __attribute__((__format__(__mingw_printf__, 3, 4))) int snprintf(char *, size_t, const char *, ...);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) __attribute__((__format__(__mingw_printf__, 3, 0))) int vsnprintf(char *, size_t, const char *, __builtin_va_list);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) int vscanf(const char *__restrict__, __builtin_va_list);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) int vfscanf(FILE *__restrict__, const char *__restrict__, __builtin_va_list);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) int vsscanf(const char *__restrict__, const char *__restrict__, __builtin_va_list);
# 646 "c:\\mingw\\include\\stdio.h" 3
__attribute__((__cdecl__)) __attribute__((__nothrow__)) ssize_t
getdelim(char **__restrict__, size_t *__restrict__, int, FILE *__restrict__);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) ssize_t
getline(char **__restrict__, size_t *__restrict__, FILE *__restrict__);

extern inline __attribute__((__gnu_inline__)) __attribute__((__always_inline__))
__attribute__((__cdecl__)) __attribute__((__nothrow__)) ssize_t
getline(char **__restrict__ __l, size_t *__restrict__ __n, FILE *__restrict__ __s)
{
  return getdelim(__l, __n, '\n', __s);
}

__attribute__((__cdecl__)) __attribute__((__nothrow__)) int fscanf(FILE *, const char *, ...);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int scanf(const char *, ...);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int sscanf(const char *, const char *, ...);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) int fgetc(FILE *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) char *fgets(char *, int, FILE *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int fputc(int, FILE *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int fputs(const char *, FILE *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) char *gets(char *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int puts(const char *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int ungetc(int, FILE *);
# 687 "c:\\mingw\\include\\stdio.h" 3
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int _filbuf(FILE *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int _flsbuf(int, FILE *);

extern inline __attribute__((__gnu_inline__)) __attribute__((__cdecl__)) __attribute__((__nothrow__)) int getc(FILE *);
extern inline __attribute__((__gnu_inline__)) __attribute__((__cdecl__)) __attribute__((__nothrow__)) int getc(FILE *__F)
{
  return (--__F->_cnt >= 0)
             ? (int)(unsigned char)*__F->_ptr++
             : _filbuf(__F);
}

extern inline __attribute__((__gnu_inline__)) __attribute__((__cdecl__)) __attribute__((__nothrow__)) int putc(int, FILE *);
extern inline __attribute__((__gnu_inline__)) __attribute__((__cdecl__)) __attribute__((__nothrow__)) int putc(int __c, FILE *__F)
{
  return (--__F->_cnt >= 0)
             ? (int)(unsigned char)(*__F->_ptr++ = (char)__c)
             : _flsbuf(__c, __F);
}

extern inline __attribute__((__gnu_inline__)) __attribute__((__cdecl__)) __attribute__((__nothrow__)) int getchar(void);
extern inline __attribute__((__gnu_inline__)) __attribute__((__cdecl__)) __attribute__((__nothrow__)) int getchar(void)
{
  return (--(&_iob[0])->_cnt >= 0)
             ? (int)(unsigned char)*(&_iob[0])->_ptr++
             : _filbuf((&_iob[0]));
}

extern inline __attribute__((__gnu_inline__)) __attribute__((__cdecl__)) __attribute__((__nothrow__)) int putchar(int);
extern inline __attribute__((__gnu_inline__)) __attribute__((__cdecl__)) __attribute__((__nothrow__)) int putchar(int __c)
{
  return (--(&_iob[1])->_cnt >= 0)
             ? (int)(unsigned char)(*(&_iob[1])->_ptr++ = (char)__c)
             : _flsbuf(__c, (&_iob[1]));
}
# 734 "c:\\mingw\\include\\stdio.h" 3
__attribute__((__cdecl__)) __attribute__((__nothrow__)) size_t fread(void *, size_t, size_t, FILE *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) size_t fwrite(const void *, size_t, size_t, FILE *);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) int fseek(FILE *, long, int);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) long ftell(FILE *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) void rewind(FILE *);
# 787 "c:\\mingw\\include\\stdio.h" 3
typedef long long fpos_t;

__attribute__((__cdecl__)) __attribute__((__nothrow__)) int fgetpos(FILE *, fpos_t *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int fsetpos(FILE *, const fpos_t *);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) int feof(FILE *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int ferror(FILE *);
# 808 "c:\\mingw\\include\\stdio.h" 3
__attribute__((__cdecl__)) __attribute__((__nothrow__)) void clearerr(FILE *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) void perror(const char *);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) FILE *_popen(const char *, const char *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int _pclose(FILE *);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) FILE *popen(const char *, const char *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int pclose(FILE *);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) int _flushall(void);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int _fgetchar(void);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int _fputchar(int);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) FILE *_fdopen(int, const char *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int _fileno(FILE *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int _fcloseall(void);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) FILE *_fsopen(const char *, const char *, int);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) int _getmaxstdio(void);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int _setmaxstdio(int);
# 859 "c:\\mingw\\include\\stdio.h" 3
unsigned int __attribute__((__cdecl__)) __mingw_get_output_format(void);
unsigned int __attribute__((__cdecl__)) __mingw_set_output_format(unsigned int);

int __attribute__((__cdecl__)) __mingw_get_printf_count_output(void);
int __attribute__((__cdecl__)) __mingw_set_printf_count_output(int);
# 885 "c:\\mingw\\include\\stdio.h" 3
extern inline __attribute__((__gnu_inline__)) __attribute__((__always_inline__)) unsigned int __attribute__((__cdecl__)) _get_output_format(void)
{
  return __mingw_get_output_format();
}

extern inline __attribute__((__gnu_inline__)) __attribute__((__always_inline__)) unsigned int __attribute__((__cdecl__)) _set_output_format(unsigned int __style)
{
  return __mingw_set_output_format(__style);
}
# 910 "c:\\mingw\\include\\stdio.h" 3
extern inline __attribute__((__gnu_inline__)) __attribute__((__always_inline__)) int __attribute__((__cdecl__)) _get_printf_count_output(void)
{
  return 0 ? 1 : __mingw_get_printf_count_output();
}

extern inline __attribute__((__gnu_inline__)) __attribute__((__always_inline__)) int __attribute__((__cdecl__)) _set_printf_count_output(int __mode)
{
  return 0 ? 1 : __mingw_set_printf_count_output(__mode);
}

__attribute__((__cdecl__)) __attribute__((__nothrow__)) int fgetchar(void);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int fputchar(int);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) FILE *fdopen(int, const char *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int fileno(FILE *);
# 930 "c:\\mingw\\include\\stdio.h" 3
extern inline __attribute__((__gnu_inline__)) __attribute__((__always_inline__)) FILE *__attribute__((__cdecl__)) __attribute__((__nothrow__)) fopen64(const char *, const char *);
extern inline __attribute__((__gnu_inline__)) __attribute__((__always_inline__))
FILE *__attribute__((__cdecl__)) __attribute__((__nothrow__)) fopen64(const char *filename, const char *mode)
{
  return fopen(filename, mode);
}

int __attribute__((__cdecl__)) __attribute__((__nothrow__)) fseeko64(FILE *, __off64_t, int);

extern inline __attribute__((__gnu_inline__)) __attribute__((__always_inline__)) __off64_t __attribute__((__cdecl__)) __attribute__((__nothrow__)) ftello64(FILE *);
extern inline __attribute__((__gnu_inline__)) __attribute__((__always_inline__))
__off64_t __attribute__((__cdecl__)) __attribute__((__nothrow__)) ftello64(FILE *stream)
{
  fpos_t __pos;
  return (fgetpos(stream, &__pos)) ? -1LL : (__off64_t)(__pos);
}
# 958 "c:\\mingw\\include\\stdio.h" 3
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int fwprintf(FILE *, const wchar_t *, ...);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int wprintf(const wchar_t *, ...);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int vfwprintf(FILE *, const wchar_t *, __builtin_va_list);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int vwprintf(const wchar_t *, __builtin_va_list);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int _snwprintf(wchar_t *, size_t, const wchar_t *, ...);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int _vscwprintf(const wchar_t *, __builtin_va_list);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int _vsnwprintf(wchar_t *, size_t, const wchar_t *, __builtin_va_list);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int fwscanf(FILE *, const wchar_t *, ...);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int wscanf(const wchar_t *, ...);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int swscanf(const wchar_t *, const wchar_t *, ...);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) wint_t fgetwc(FILE *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) wint_t fputwc(wchar_t, FILE *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) wint_t ungetwc(wchar_t, FILE *);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) int swprintf(wchar_t *, const wchar_t *, ...);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int vswprintf(wchar_t *, const wchar_t *, __builtin_va_list);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) wchar_t *fgetws(wchar_t *, int, FILE *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int fputws(const wchar_t *, FILE *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) wint_t getwc(FILE *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) wint_t getwchar(void);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) wint_t putwc(wint_t, FILE *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) wint_t putwchar(wint_t);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) wchar_t *_getws(wchar_t *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int _putws(const wchar_t *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) FILE *_wfdopen(int, const wchar_t *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) FILE *_wfopen(const wchar_t *, const wchar_t *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) FILE *_wfreopen(const wchar_t *, const wchar_t *, FILE *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) FILE *_wfsopen(const wchar_t *, const wchar_t *, int);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) wchar_t *_wtmpnam(wchar_t *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) wchar_t *_wtempnam(const wchar_t *, const wchar_t *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int _wrename(const wchar_t *, const wchar_t *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int _wremove(const wchar_t *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) void _wperror(const wchar_t *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) FILE *_wpopen(const wchar_t *, const wchar_t *);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) int snwprintf(wchar_t *, size_t, const wchar_t *, ...);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int vsnwprintf(wchar_t *, size_t, const wchar_t *, __builtin_va_list);

extern inline __attribute__((__gnu_inline__)) __attribute__((__cdecl__)) __attribute__((__nothrow__))

int
vsnwprintf(wchar_t *__s, size_t __n, const wchar_t *__fmt, __builtin_va_list __arg)
{
  return _vsnwprintf(__s, __n, __fmt, __arg);
}

__attribute__((__cdecl__)) __attribute__((__nothrow__)) int vwscanf(const wchar_t *__restrict__, __builtin_va_list);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int vfwscanf(FILE *__restrict__, const wchar_t *__restrict__, __builtin_va_list);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int vswscanf(const wchar_t *__restrict__, const wchar_t *__restrict__, __builtin_va_list);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) FILE *wpopen(const wchar_t *, const wchar_t *);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) wint_t _fgetwchar(void);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) wint_t _fputwchar(wint_t);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int _getw(FILE *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int _putw(int, FILE *);

__attribute__((__cdecl__)) __attribute__((__nothrow__)) wint_t fgetwchar(void);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) wint_t fputwchar(wint_t);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int getw(FILE *);
__attribute__((__cdecl__)) __attribute__((__nothrow__)) int putw(int, FILE *);

# 3 "src/main.c" 2

# 1 "include/DAFL.h" 1

# 1 "c:\\mingw\\lib\\gcc\\mingw32\\6.3.0\\include\\stdint.h" 1 3 4
# 9 "c:\\mingw\\lib\\gcc\\mingw32\\6.3.0\\include\\stdint.h" 3 4
# 1 "c:\\mingw\\include\\stdint.h" 1 3 4
# 34 "c:\\mingw\\include\\stdint.h" 3 4

# 35 "c:\\mingw\\include\\stdint.h" 3
# 54 "c:\\mingw\\include\\stdint.h" 3
# 1 "c:\\mingw\\lib\\gcc\\mingw32\\6.3.0\\include\\stddef.h" 1 3 4
# 55 "c:\\mingw\\include\\stdint.h" 2 3

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned uint32_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;

typedef signed char int_least8_t;
typedef unsigned char uint_least8_t;
typedef short int_least16_t;
typedef unsigned short uint_least16_t;
typedef int int_least32_t;
typedef unsigned uint_least32_t;
typedef long long int_least64_t;
typedef unsigned long long uint_least64_t;

typedef signed char int_fast8_t;
typedef unsigned char uint_fast8_t;
typedef short int_fast16_t;
typedef unsigned short uint_fast16_t;
typedef int int_fast32_t;
typedef unsigned int uint_fast32_t;
typedef long long int_fast64_t;
typedef unsigned long long uint_fast64_t;
# 106 "c:\\mingw\\include\\stdint.h" 3
typedef int __intptr_t;

typedef __intptr_t intptr_t;
# 118 "c:\\mingw\\include\\stdint.h" 3
typedef unsigned int __uintptr_t;

typedef __uintptr_t uintptr_t;

typedef long long intmax_t;
typedef unsigned long long uintmax_t;
# 10 "c:\\mingw\\lib\\gcc\\mingw32\\6.3.0\\include\\stdint.h" 2 3 4
# 5 "include/DAFL.h" 2
# 1 "c:\\mingw\\include\\inttypes.h" 1 3
# 9 "c:\\mingw\\include\\inttypes.h" 3
# 1 "c:\\mingw\\lib\\gcc\\mingw32\\6.3.0\\include\\stddef.h" 1 3 4
# 10 "c:\\mingw\\include\\inttypes.h" 2 3

typedef struct
{
  intmax_t quot;
  intmax_t rem;
} imaxdiv_t;
# 258 "c:\\mingw\\include\\inttypes.h" 3
intmax_t __attribute__((__cdecl__)) __attribute__((__nothrow__)) imaxabs(intmax_t j);

extern inline __attribute__((__gnu_inline__))
intmax_t __attribute__((__cdecl__)) __attribute__((__nothrow__)) imaxabs(intmax_t __j)
{
  return __j >= 0 ? __j : -__j;
}

extern inline __attribute__((__gnu_inline__)) long long llabs(long long);

imaxdiv_t __attribute__((__cdecl__)) __attribute__((__nothrow__)) imaxdiv(intmax_t numer, intmax_t denom);

intmax_t __attribute__((__cdecl__)) __attribute__((__nothrow__)) strtoimax(const char *__restrict__ nptr,
                                                                           char **__restrict__ endptr, int base);
uintmax_t __attribute__((__cdecl__)) __attribute__((__nothrow__)) strtoumax(const char *__restrict__ nptr,
                                                                            char **__restrict__ endptr, int base);

intmax_t __attribute__((__cdecl__)) __attribute__((__nothrow__)) wcstoimax(const wchar_t *__restrict__ nptr,
                                                                           wchar_t **__restrict__ endptr, int base);
uintmax_t __attribute__((__cdecl__)) __attribute__((__nothrow__)) wcstoumax(const wchar_t *__restrict__ nptr,
                                                                            wchar_t **__restrict__ endptr, int base);

# 6 "include/DAFL.h" 2
# 1 "c:\\mingw\\include\\math.h" 1 3
# 35 "c:\\mingw\\include\\math.h" 3

# 36 "c:\\mingw\\include\\math.h" 3
# 111 "c:\\mingw\\include\\math.h" 3

# 151 "c:\\mingw\\include\\math.h" 3
struct _exception
{
  int type;
  char *name;
  double arg1;
  double arg2;
  double retval;
};

double __attribute__((__cdecl__)) sin(double);
double __attribute__((__cdecl__)) cos(double);
double __attribute__((__cdecl__)) tan(double);
double __attribute__((__cdecl__)) sinh(double);
double __attribute__((__cdecl__)) cosh(double);
double __attribute__((__cdecl__)) tanh(double);
double __attribute__((__cdecl__)) asin(double);
double __attribute__((__cdecl__)) acos(double);
double __attribute__((__cdecl__)) atan(double);
double __attribute__((__cdecl__)) atan2(double, double);
double __attribute__((__cdecl__)) exp(double);
double __attribute__((__cdecl__)) log(double);
double __attribute__((__cdecl__)) log10(double);
double __attribute__((__cdecl__)) pow(double, double);
double __attribute__((__cdecl__)) sqrt(double);
double __attribute__((__cdecl__)) ceil(double);
double __attribute__((__cdecl__)) floor(double);
double __attribute__((__cdecl__)) fabs(double);
double __attribute__((__cdecl__)) ldexp(double, int);
double __attribute__((__cdecl__)) frexp(double, int *);
double __attribute__((__cdecl__)) modf(double, double *);
double __attribute__((__cdecl__)) fmod(double, double);
# 225 "c:\\mingw\\include\\math.h" 3
struct _complex
{

  double x;
  double y;
};

double __attribute__((__cdecl__)) _cabs(struct _complex);

double __attribute__((__cdecl__)) _hypot(double, double);
double __attribute__((__cdecl__)) _j0(double);
double __attribute__((__cdecl__)) _j1(double);
double __attribute__((__cdecl__)) _jn(int, double);
double __attribute__((__cdecl__)) _y0(double);
double __attribute__((__cdecl__)) _y1(double);
double __attribute__((__cdecl__)) _yn(int, double);
int __attribute__((__cdecl__)) _matherr(struct _exception *);
# 252 "c:\\mingw\\include\\math.h" 3
double __attribute__((__cdecl__)) _chgsign(double);
double __attribute__((__cdecl__)) _copysign(double, double);
double __attribute__((__cdecl__)) _logb(double);
double __attribute__((__cdecl__)) _nextafter(double, double);
double __attribute__((__cdecl__)) _scalb(double, long);

int __attribute__((__cdecl__)) _finite(double);
int __attribute__((__cdecl__)) _fpclass(double);
int __attribute__((__cdecl__)) _isnan(double);
# 269 "c:\\mingw\\include\\math.h" 3
double __attribute__((__cdecl__)) j0(double);
double __attribute__((__cdecl__)) j1(double);
double __attribute__((__cdecl__)) jn(int, double);
double __attribute__((__cdecl__)) y0(double);
double __attribute__((__cdecl__)) y1(double);
double __attribute__((__cdecl__)) yn(int, double);

double __attribute__((__cdecl__)) chgsign(double);
# 285 "c:\\mingw\\include\\math.h" 3
int __attribute__((__cdecl__)) finite(double);
int __attribute__((__cdecl__)) fpclass(double);
# 355 "c:\\mingw\\include\\math.h" 3
typedef long double float_t;
typedef long double double_t;
# 391 "c:\\mingw\\include\\math.h" 3
extern int __attribute__((__cdecl__)) __fpclassifyf(float);
extern int __attribute__((__cdecl__)) __fpclassify(double);
extern int __attribute__((__cdecl__)) __fpclassifyl(long double);

extern inline __attribute__((__gnu_inline__)) int __attribute__((__cdecl__)) __fpclassifyl(long double x)
{
  unsigned short sw;
  __asm__("fxam; fstsw %%ax;"
          : "=a"(sw)
          : "t"(x));
  return sw & (0x0100 | 0x0400 | 0x4000);
}
# 417 "c:\\mingw\\include\\math.h" 3
extern int __attribute__((__cdecl__)) __isnan(double);
extern int __attribute__((__cdecl__)) __isnanf(float);
extern int __attribute__((__cdecl__)) __isnanl(long double);

extern inline __attribute__((__gnu_inline__)) int __attribute__((__cdecl__)) __isnan(double _x)
{
  unsigned short sw;
  __asm__("fxam;"
          "fstsw %%ax"
          : "=a"(sw)
          : "t"(_x));
  return (sw & (0x0100 | 0x0400 | (0x0100 | 0x0400) | 0x4000 | (0x0400 | 0x4000))) == 0x0100;
}

extern inline __attribute__((__gnu_inline__)) int __attribute__((__cdecl__)) __isnanf(float _x)
{
  unsigned short sw;
  __asm__("fxam;"
          "fstsw %%ax"
          : "=a"(sw)
          : "t"(_x));
  return (sw & (0x0100 | 0x0400 | (0x0100 | 0x0400) | 0x4000 | (0x0400 | 0x4000))) == 0x0100;
}

extern inline __attribute__((__gnu_inline__)) int __attribute__((__cdecl__)) __isnanl(long double _x)
{
  unsigned short sw;
  __asm__("fxam;"
          "fstsw %%ax"
          : "=a"(sw)
          : "t"(_x));
  return (sw & (0x0100 | 0x0400 | (0x0100 | 0x0400) | 0x4000 | (0x0400 | 0x4000))) == 0x0100;
}
# 457 "c:\\mingw\\include\\math.h" 3
extern int __attribute__((__cdecl__)) __signbit(double);
extern int __attribute__((__cdecl__)) __signbitf(float);
extern int __attribute__((__cdecl__)) __signbitl(long double);

extern inline __attribute__((__gnu_inline__)) int __attribute__((__cdecl__)) __signbit(double x)
{
  unsigned short stw;
  __asm__("fxam; fstsw %%ax;"
          : "=a"(stw)
          : "t"(x));
  return (stw & 0x0200) != 0;
}

extern inline __attribute__((__gnu_inline__)) int __attribute__((__cdecl__)) __signbitf(float x)
{
  unsigned short stw;
  __asm__("fxam; fstsw %%ax;"
          : "=a"(stw)
          : "t"(x));
  return (stw & 0x0200) != 0;
}

extern inline __attribute__((__gnu_inline__)) int __attribute__((__cdecl__)) __signbitl(long double x)
{
  unsigned short stw;
  __asm__("fxam; fstsw %%ax;"
          : "=a"(stw)
          : "t"(x));
  return (stw & 0x0200) != 0;
}
# 486 "c:\\mingw\\include\\math.h" 3
extern float __attribute__((__cdecl__)) sinf(float);
extern long double __attribute__((__cdecl__)) sinl(long double);

extern float __attribute__((__cdecl__)) cosf(float);
extern long double __attribute__((__cdecl__)) cosl(long double);

extern float __attribute__((__cdecl__)) tanf(float);
extern long double __attribute__((__cdecl__)) tanl(long double);

extern float __attribute__((__cdecl__)) asinf(float);
extern long double __attribute__((__cdecl__)) asinl(long double);

extern float __attribute__((__cdecl__)) acosf(float);
extern long double __attribute__((__cdecl__)) acosl(long double);

extern float __attribute__((__cdecl__)) atanf(float);
extern long double __attribute__((__cdecl__)) atanl(long double);

extern float __attribute__((__cdecl__)) atan2f(float, float);
extern long double __attribute__((__cdecl__)) atan2l(long double, long double);

extern float __attribute__((__cdecl__)) sinhf(float);

extern inline __attribute__((__gnu_inline__)) float __attribute__((__cdecl__)) sinhf(float x)
{
  return (float)sinh(x);
}

extern long double __attribute__((__cdecl__)) sinhl(long double);

extern float __attribute__((__cdecl__)) coshf(float);

extern inline __attribute__((__gnu_inline__)) float __attribute__((__cdecl__)) coshf(float x)
{
  return (float)cosh(x);
}

extern long double __attribute__((__cdecl__)) coshl(long double);

extern float __attribute__((__cdecl__)) tanhf(float);

extern inline __attribute__((__gnu_inline__)) float __attribute__((__cdecl__)) tanhf(float x)
{
  return (float)tanh(x);
}

extern long double __attribute__((__cdecl__)) tanhl(long double);

extern double __attribute__((__cdecl__)) acosh(double);
extern float __attribute__((__cdecl__)) acoshf(float);
extern long double __attribute__((__cdecl__)) acoshl(long double);

extern double __attribute__((__cdecl__)) asinh(double);
extern float __attribute__((__cdecl__)) asinhf(float);
extern long double __attribute__((__cdecl__)) asinhl(long double);

extern double __attribute__((__cdecl__)) atanh(double);
extern float __attribute__((__cdecl__)) atanhf(float);
extern long double __attribute__((__cdecl__)) atanhl(long double);

extern float __attribute__((__cdecl__)) expf(float);

extern inline __attribute__((__gnu_inline__)) float __attribute__((__cdecl__)) expf(float x)
{
  return (float)exp(x);
}

extern long double __attribute__((__cdecl__)) expl(long double);

extern double __attribute__((__cdecl__)) exp2(double);
extern float __attribute__((__cdecl__)) exp2f(float);
extern long double __attribute__((__cdecl__)) exp2l(long double);

extern double __attribute__((__cdecl__)) expm1(double);
extern float __attribute__((__cdecl__)) expm1f(float);
extern long double __attribute__((__cdecl__)) expm1l(long double);

extern float __attribute__((__cdecl__)) frexpf(float, int *);

extern inline __attribute__((__gnu_inline__)) float __attribute__((__cdecl__)) frexpf(float x, int *expn)
{
  return (float)frexp(x, expn);
}

extern long double __attribute__((__cdecl__)) frexpl(long double, int *);

extern int __attribute__((__cdecl__)) ilogb(double);
extern int __attribute__((__cdecl__)) ilogbf(float);
extern int __attribute__((__cdecl__)) ilogbl(long double);

extern float __attribute__((__cdecl__)) ldexpf(float, int);

extern inline __attribute__((__gnu_inline__)) float __attribute__((__cdecl__)) ldexpf(float x, int expn)
{
  return (float)ldexp(x, expn);
}

extern long double __attribute__((__cdecl__)) ldexpl(long double, int);

extern float __attribute__((__cdecl__)) logf(float);
extern long double __attribute__((__cdecl__)) logl(long double);

extern float __attribute__((__cdecl__)) log10f(float);
extern long double __attribute__((__cdecl__)) log10l(long double);

extern double __attribute__((__cdecl__)) log1p(double);
extern float __attribute__((__cdecl__)) log1pf(float);
extern long double __attribute__((__cdecl__)) log1pl(long double);

extern double __attribute__((__cdecl__)) log2(double);
extern float __attribute__((__cdecl__)) log2f(float);
extern long double __attribute__((__cdecl__)) log2l(long double);

extern double __attribute__((__cdecl__)) logb(double);
extern float __attribute__((__cdecl__)) logbf(float);
extern long double __attribute__((__cdecl__)) logbl(long double);

extern inline __attribute__((__gnu_inline__)) double __attribute__((__cdecl__)) logb(double x)
{
  double res;
  __asm__("fxtract\n\t"
          "fstp	%%st"
          : "=t"(res)
          : "0"(x));
  return res;
}

extern inline __attribute__((__gnu_inline__)) float __attribute__((__cdecl__)) logbf(float x)
{
  float res;
  __asm__("fxtract\n\t"
          "fstp	%%st"
          : "=t"(res)
          : "0"(x));
  return res;
}

extern inline __attribute__((__gnu_inline__)) long double __attribute__((__cdecl__)) logbl(long double x)
{
  long double res;
  __asm__("fxtract\n\t"
          "fstp	%%st"
          : "=t"(res)
          : "0"(x));
  return res;
}

extern float __attribute__((__cdecl__)) modff(float, float *);
extern long double __attribute__((__cdecl__)) modfl(long double, long double *);

extern double __attribute__((__cdecl__)) scalbn(double, int);
extern float __attribute__((__cdecl__)) scalbnf(float, int);
extern long double __attribute__((__cdecl__)) scalbnl(long double, int);

extern double __attribute__((__cdecl__)) scalbln(double, long);
extern float __attribute__((__cdecl__)) scalblnf(float, long);
extern long double __attribute__((__cdecl__)) scalblnl(long double, long);

extern double __attribute__((__cdecl__)) cbrt(double);
extern float __attribute__((__cdecl__)) cbrtf(float);
extern long double __attribute__((__cdecl__)) cbrtl(long double);

extern float __attribute__((__cdecl__)) fabsf(float x);
extern long double __attribute__((__cdecl__)) fabsl(long double x);

extern double __attribute__((__cdecl__)) hypot(double, double);
extern float __attribute__((__cdecl__)) hypotf(float, float);
extern long double __attribute__((__cdecl__)) hypotl(long double, long double);

extern float __attribute__((__cdecl__)) powf(float, float);
extern long double __attribute__((__cdecl__)) powl(long double, long double);

extern float __attribute__((__cdecl__)) sqrtf(float);
extern long double __attribute__((__cdecl__)) sqrtl(long double);

extern double __attribute__((__cdecl__)) erf(double);
extern float __attribute__((__cdecl__)) erff(float);
extern long double __attribute__((__cdecl__)) erfl(long double);

extern double __attribute__((__cdecl__)) erfc(double);
extern float __attribute__((__cdecl__)) erfcf(float);
extern long double __attribute__((__cdecl__)) erfcl(long double);

extern double __attribute__((__cdecl__)) lgamma(double);
extern float __attribute__((__cdecl__)) lgammaf(float);
extern long double __attribute__((__cdecl__)) lgammal(long double);

extern double __attribute__((__cdecl__)) tgamma(double);
extern float __attribute__((__cdecl__)) tgammaf(float);
extern long double __attribute__((__cdecl__)) tgammal(long double);

extern float __attribute__((__cdecl__)) ceilf(float);
extern long double __attribute__((__cdecl__)) ceill(long double);

extern float __attribute__((__cdecl__)) floorf(float);
extern long double __attribute__((__cdecl__)) floorl(long double);

extern double __attribute__((__cdecl__)) nearbyint(double);
extern float __attribute__((__cdecl__)) nearbyintf(float);
extern long double __attribute__((__cdecl__)) nearbyintl(long double);

extern double __attribute__((__cdecl__)) rint(double);
extern float __attribute__((__cdecl__)) rintf(float);
extern long double __attribute__((__cdecl__)) rintl(long double);

extern long __attribute__((__cdecl__)) lrint(double);
extern long __attribute__((__cdecl__)) lrintf(float);
extern long __attribute__((__cdecl__)) lrintl(long double);

extern long long __attribute__((__cdecl__)) llrint(double);
extern long long __attribute__((__cdecl__)) llrintf(float);
extern long long __attribute__((__cdecl__)) llrintl(long double);

extern inline __attribute__((__gnu_inline__)) double __attribute__((__cdecl__)) rint(double x)
{
  double retval;
  __asm__("frndint;"
          : "=t"(retval)
          : "0"(x));
  return retval;
}

extern inline __attribute__((__gnu_inline__)) float __attribute__((__cdecl__)) rintf(float x)
{
  float retval;
  __asm__("frndint;"
          : "=t"(retval)
          : "0"(x));
  return retval;
}

extern inline __attribute__((__gnu_inline__)) long double __attribute__((__cdecl__)) rintl(long double x)
{
  long double retval;
  __asm__("frndint;"
          : "=t"(retval)
          : "0"(x));
  return retval;
}

extern inline __attribute__((__gnu_inline__)) long __attribute__((__cdecl__)) lrint(double x)
{
  long retval;
  __asm__ __volatile__("fistpl %0"
                       : "=m"(retval)
                       : "t"(x)
                       : "st");
  return retval;
}

extern inline __attribute__((__gnu_inline__)) long __attribute__((__cdecl__)) lrintf(float x)
{
  long retval;
  __asm__ __volatile__("fistpl %0"
                       : "=m"(retval)
                       : "t"(x)
                       : "st");
  return retval;
}

extern inline __attribute__((__gnu_inline__)) long __attribute__((__cdecl__)) lrintl(long double x)
{
  long retval;
  __asm__ __volatile__("fistpl %0"
                       : "=m"(retval)
                       : "t"(x)
                       : "st");
  return retval;
}

extern inline __attribute__((__gnu_inline__)) long long __attribute__((__cdecl__)) llrint(double x)
{
  long long retval;
  __asm__ __volatile__("fistpll %0"
                       : "=m"(retval)
                       : "t"(x)
                       : "st");
  return retval;
}

extern inline __attribute__((__gnu_inline__)) long long __attribute__((__cdecl__)) llrintf(float x)
{
  long long retval;
  __asm__ __volatile__("fistpll %0"
                       : "=m"(retval)
                       : "t"(x)
                       : "st");
  return retval;
}

extern inline __attribute__((__gnu_inline__)) long long __attribute__((__cdecl__)) llrintl(long double x)
{
  long long retval;
  __asm__ __volatile__("fistpll %0"
                       : "=m"(retval)
                       : "t"(x)
                       : "st");
  return retval;
}

extern double __attribute__((__cdecl__)) round(double);
extern float __attribute__((__cdecl__)) roundf(float);
extern long double __attribute__((__cdecl__)) roundl(long double);

extern long __attribute__((__cdecl__)) lround(double);
extern long __attribute__((__cdecl__)) lroundf(float);
extern long __attribute__((__cdecl__)) lroundl(long double);

extern long long __attribute__((__cdecl__)) llround(double);
extern long long __attribute__((__cdecl__)) llroundf(float);
extern long long __attribute__((__cdecl__)) llroundl(long double);

extern double __attribute__((__cdecl__)) trunc(double);
extern float __attribute__((__cdecl__)) truncf(float);
extern long double __attribute__((__cdecl__)) truncl(long double);

extern float __attribute__((__cdecl__)) fmodf(float, float);
extern long double __attribute__((__cdecl__)) fmodl(long double, long double);

extern double __attribute__((__cdecl__)) remainder(double, double);
extern float __attribute__((__cdecl__)) remainderf(float, float);
extern long double __attribute__((__cdecl__)) remainderl(long double, long double);

extern double __attribute__((__cdecl__)) remquo(double, double, int *);
extern float __attribute__((__cdecl__)) remquof(float, float, int *);
extern long double __attribute__((__cdecl__)) remquol(long double, long double, int *);

extern double __attribute__((__cdecl__)) copysign(double, double);
extern float __attribute__((__cdecl__)) copysignf(float, float);
extern long double __attribute__((__cdecl__)) copysignl(long double, long double);

extern double __attribute__((__cdecl__)) nan(const char *tagp);
extern float __attribute__((__cdecl__)) nanf(const char *tagp);
extern long double __attribute__((__cdecl__)) nanl(const char *tagp);
# 855 "c:\\mingw\\include\\math.h" 3
extern double __attribute__((__cdecl__)) nextafter(double, double);
extern float __attribute__((__cdecl__)) nextafterf(float, float);
extern long double __attribute__((__cdecl__)) nextafterl(long double, long double);

extern double __attribute__((__cdecl__)) nexttoward(double, long double);
extern float __attribute__((__cdecl__)) nexttowardf(float, long double);
extern long double __attribute__((__cdecl__)) nexttowardl(long double, long double);

extern double __attribute__((__cdecl__)) fdim(double x, double y);
extern float __attribute__((__cdecl__)) fdimf(float x, float y);
extern long double __attribute__((__cdecl__)) fdiml(long double x, long double y);

extern double __attribute__((__cdecl__)) fmax(double, double);
extern float __attribute__((__cdecl__)) fmaxf(float, float);
extern long double __attribute__((__cdecl__)) fmaxl(long double, long double);

extern double __attribute__((__cdecl__)) fmin(double, double);
extern float __attribute__((__cdecl__)) fminf(float, float);
extern long double __attribute__((__cdecl__)) fminl(long double, long double);

extern double __attribute__((__cdecl__)) fma(double, double, double);
extern float __attribute__((__cdecl__)) fmaf(float, float, float);
extern long double __attribute__((__cdecl__)) fmal(long double, long double, long double);
# 931 "c:\\mingw\\include\\math.h" 3

# 7 "include/DAFL.h" 2

# 1 "include/../../../C/useful_macros.h" 1
# 9 "include/DAFL.h" 2
# 24 "include/DAFL.h"

# 24 "include/DAFL.h"
typedef uint64_t dafl_ref_t;
typedef uint16_t myriagit_t;
typedef uint8_t dafl_head_t;
typedef uint8_t dafl_limb_t[((2 * 42 * 10)) / (8) + (((2 * 42 * 10)) % (8) != 0)];

typedef struct
{
  dafl_head_t head;
  uint64_t exp;
  uint64_t prec;
  uint8_t real_prec_dec;

} dafl_t;

dafl_ref_t dafl_init();
# 5 "src/main.c" 2

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;

#define num 999ULL + 1

  printf("hello DAFL !!!, %i, %i, %i\n", num, (num) - (((num)) > 999ULL) * (((num)) - (999ULL - (((0)) * (1023ULL - 999ULL)))), ((num) > 999ULL) * ((num) - (999ULL - ((0) * (1023ULL - 999ULL)))));

  printf("%"
# 15 "src/main.c" 3
         "u"
# 15 "src/main.c"
         ", %"
# 15 "src/main.c" 3
         "u"
# 15 "src/main.c"
         ", %"
# 15 "src/main.c" 3
         "u"
# 15 "src/main.c"
         "\n",
         (1023ULL - 999ULL), ((1023ULL - 999ULL)), (999ULL - (0U * (1023ULL - 999ULL))));

  return 0;
}
