/* C code produced by gperf version 2.8 (ACE version) */
/* Command-line: ..\..\..\bin\ace_gperf -a -p -D -k1,$ -s 2 -o adadefs.gperf  */
#include "ace/OS_NS_string.h"

#define TOTAL_KEYWORDS 54
#define MIN_WORD_LENGTH 3
#define MAX_WORD_LENGTH 17
#define MIN_HASH_VALUE 5
#define MAX_HASH_VALUE 126
#define HASH_VALUE_RANGE 122
#define DUPLICATES 2
#define WORDLIST_SIZE 59

static unsigned int
hash (const char *str, unsigned int len)
{
  static unsigned char asso_values[] =
    {
#if defined (ACE_MVS)
     127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
     127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
     127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
     127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
     127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
     127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
     127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
     127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
     127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
     127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
     127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
     127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
     127, 127, 127, 127, 127, 127, 127, 127, 127,  65,
      35,  35,   0,   0,  50,   5,   0,  45, 127, 127,
     127, 127, 127, 127, 127, 127, 127,  20,  45,  35,
     127,  15, 127,  60, 127, 127, 127, 127, 127, 127,
     127, 127,  10,   5, 127,  25,   0,  40, 127, 127,
     127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
     127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
     127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
     127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
     127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
     127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
     127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
     127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
     127, 127, 127, 127, 127, 127,
#else
     127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
     127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
     127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
     127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
     127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
     127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
     127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
     127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
     127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
     127, 127, 127, 127, 127, 127, 127,  65,  35,  35,
       0,   0,  50,   5,   0,  45, 127, 127,  20,  45,
      35, 127,  15, 127,  60,  10,   5, 127,  25,   0,
      40, 127, 127, 127, 127, 127, 127, 127,
#endif /* ACE_MVS */
    };
  return len + asso_values[(int) str[len - 1]] + asso_values[(int) str[0]];
}

const char *
in_word_set (const char *str, unsigned int len)
{
  static const char *wordlist[] =
    {
      "","","","","",
      "width", 
      "true", 
      "size", 
      "terminated", 
      "digits", 
      "pred", 
      "safe_large", 
      "string", 
      "storage_size", 
      "positive", 
      "large", 
      "length", 
      "pos", 
      "last", 
      "value", 
      "lastbit", 
      "small", 
      "base", 
      "safe_small", 
      "epsilon", 
      "callable", 
      "emax", 
      "count", 
      "constrained", 
      "val", 
      "succ", 
      "image", 
      "fore", 
      "false", 
      "position", 
      "safe_emax", 
      "float", 
      "first", 
      "natural", 
      "firstbit", 
      "range", 
      "machine_rounds", 
      "delta", 
      "machine_overflows", 
      "aft", 
      "boolean", 
      "tasking_error", 
      "address", 
      "storage_error", 
      "program_error", 
      "machine_emin", 
      "machine_emax", 
      "machine_radix", 
      "character", 
      "numeric_error", 
      "constraint_error", 
      "integer", 
      "mantissa", 
      "machine_mantissa", 
    };

  static signed short lookup[] =
    {
        -1,   -1,   -1,   -1,   -1,    5,   -1,   -1,   -1,    6,   -1,   -1,   -1,   -1, 
         7,    8,    9,   -1,   -1,   10,   11,   12,   13,   14,   -1,   15,   16,   -1, 
        17,   18,   19,   -1,   20,   -1,   -1,   21,   -1,   -1,   -1,   22,   23,   -1, 
        24,   25,   26,   27,   28,   -1,   29,   30,   31,   -1,   -1,   -1,   32,   33, 
       -36,   -2,   34,   35, -130,   -1,   38,   39,   -1,   40,   -1,   -1,   -1,   41, 
        42,   -1,   43,   44,   -1,   -1,   -1,   45,   46,   -1,   -1,   -1,   47,   48, 
        -1,   -1,   -1,   -1,   49,   -1,   -1,   -1,   50,   -1,   -1,   -1,   -1,   51, 
        52,   -1,   -1,   -1,   -1,   -1,   53,   -1,   -1,   -1,   54,   -1,   -1,   55, 
        56,   -1,   -1,   -1,   -1,   -1,   57,   -1,   -1,   -1,   -1,   -1,   -1,   -1, 
        58, 
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      unsigned int key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= MIN_HASH_VALUE)
        {
          int slot = lookup[key];

          if (slot >= 0 && slot < WORDLIST_SIZE)
            {
              const char *s = wordlist[slot];

              if (*str == *s && !ACE_OS::strcmp (str + 1, s + 1))
                return s;
            }
          else if (slot < 0 && slot >= -MAX_HASH_VALUE)
            return 0;
          else
            {
              unsigned int offset = key + slot + (slot > 0 ? -MAX_HASH_VALUE : MAX_HASH_VALUE);
              const char **base = &wordlist[-lookup[offset]];
              const char **ptr = base + -lookup[offset + 1];

              while (--ptr >= base)
                if (*str == **ptr && !ACE_OS::strcmp (str + 1, *ptr + 1))
                  return *ptr;
            }
        }
    }
  return 0;
}
