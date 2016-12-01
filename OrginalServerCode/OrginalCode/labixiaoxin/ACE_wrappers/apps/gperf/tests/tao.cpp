/* C code produced by gperf version 2.8 (ACE version) */
/* Command-line: ..\..\..\bin\ace_gperf -c -C -D -E -f 0 -a -o tao.gperf  */
#include "ace/OS_NS_string.h"
static unsigned int
hash (const char *str, unsigned int len)
{
  static const unsigned char asso_values[] =
    {
#if defined (ACE_MVS)
     24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
     24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
     24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
     24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
     24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
     24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
     24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
     24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
     24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
     24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
     24, 24, 24, 24, 24, 24, 24, 24, 24,  5,
     24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
     24, 24, 24, 24, 24, 24, 24, 24, 24,  0,
      0,  5, 24,  5, 24, 24, 24, 24, 24, 24,
     24, 24, 24, 24, 24, 24, 24, 24, 24,  0,
     24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
     24, 24,  0,  0, 24, 24, 24, 24, 24, 24,
     24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
     24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
     24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
     24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
     24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
     24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
     24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
     24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
     24, 24, 24, 24, 24, 24,
#else
     24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
     24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
     24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
     24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
     24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
     24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
     24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
     24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
     24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
     24, 24, 24, 24, 24,  5, 24,  0,  0,  5,
     24,  5, 24, 24, 24, 24, 24, 24, 24, 24,
      0, 24, 24, 24, 24,  0,  0, 24, 24, 24,
     24, 24, 24, 24, 24, 24, 24, 24,
#endif /* ACE_MVS */
    };
  return len + asso_values[(int) str[len - 1]] + asso_values[(int) str[0]];
}

const char *
in_word_set (const char *str, unsigned int len)
{
  enum
    {
      TOTAL_KEYWORDS = 21,
      MIN_WORD_LENGTH = 5,
      MAX_WORD_LENGTH = 18,
      MIN_HASH_VALUE = 8,
      MAX_HASH_VALUE = 23,
      HASH_VALUE_RANGE = 16,
      DUPLICATES = 13,
      WORDLIST_SIZE = 29
    };

  static const char *wordlist[] =
    {
      "","","","","","","","",
      "shutdown", 
      "_is_a", 
      "ackConfCsData", 
      "ackConfBasData", 
      "ackConfR15Data", 
      "ackConfR14Data", 
      "ackConfR13Data", 
      "ackConfR12Data", 
      "ackConfR11Data", 
      "ackConfR10Data", 
      "ackConfSscData", 
      "ackConfSosData", 
      "ackConfFftData", 
      "ackConfVonData", 
      "ackConfTwmData", 
      "ackConfMosData", 
      "ackConfArchData", 
      "transferTriggerDb", 
      "_non_existent", 
      "_interface", 
      "transferTriggerTdc", 
    };

  static const signed char lookup[] =
    {
       -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,   8,  -1,   9, -11, -13,  10, 
      -26,  24,  -1,  25,  26,  -1,  27,  -1,  -1,  28, 
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

              if (*str == *s && !ACE_OS::strncmp (str + 1, s + 1, len - 1))
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
                if (*str == **ptr && !ACE_OS::strncmp (str + 1, *ptr + 1, len - 1))
                  return *ptr;
            }
        }
    }
  return 0;
}
