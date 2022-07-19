#ifndef __DAFL__
#define __DAFL__

#include <stdint.h>
#include <inttypes.h>

#include "../../../C/useful_macros.h"

#define MYRIAGIT_BITS_SIZE 10
#define MYRIAGIT_DECIMAL_SIZE 3
#define UINT10_MAX 1023
#define MYRIAGIT_MAX 999
#define MYRIAGIT_DEC UINT10_MAX - MYRIAGIT_MAX

#define TRC_PRT(N, n) (N > MYRIAGIT_MAX) * (N - (MYRIAGIT_MAX - (n * MYRIAGIT_DEC)))
#define TRC(N, n) N - TRC_PRT(N, n)

typedef uint16_t myriagit_t;
typedef uint8_t dafl_head_t;

typedef struct
{
  dafl_head_t head;
  uint64_t exp;
  uint64_t prec;         // the number of myriagit asked
  uint8_t real_prec_dec; // the number of myriagit actually used

} dafl_t;

#endif //__DAFL__