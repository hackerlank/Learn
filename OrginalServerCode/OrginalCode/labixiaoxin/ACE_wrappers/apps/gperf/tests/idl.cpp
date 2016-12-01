/* C code produced by gperf version 2.8 (ACE version) */
/* Command-line: ..\..\..\bin\ace_gperf -m -M -c -C -D -S1 -E -T -a -o -p idl.gperf  */
#include "ace/OS_NS_string.h"
static unsigned int
hash (const char *str, unsigned int len)
{
  static const unsigned char asso_values[] =
    {
#if defined (ACE_MVS)
     14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
     14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
     14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
     14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
     14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
     14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
     14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
     14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
     14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
     14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
     14, 14, 14, 14, 14, 14, 14, 14, 14,  0,
     14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
     14, 14, 14, 14, 14, 14, 14, 14, 14,  0,
     14, 14,  0, 14, 14,  5,  0, 14, 14, 14,
     14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
     14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
     14, 14,  0,  0, 14, 14, 14, 14,  0, 14,
     14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
     14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
     14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
     14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
     14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
     14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
     14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
     14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
     14, 14, 14, 14, 14, 14,
#else
     14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
     14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
     14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
     14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
     14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
     14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
     14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
     14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
     14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
     14, 14, 14, 14, 14,  0, 14,  0, 14, 14,
      0, 14, 14,  5,  0, 14, 14, 14, 14, 14,
     14, 14, 14, 14, 14,  0,  0, 14, 14, 14,
     14,  0, 14, 14, 14, 14, 14, 14,
#endif /* ACE_MVS */
    };
  return len + asso_values[(int) str[len - 1]] + asso_values[(int) str[0]];
}

const char *
in_word_set (const char *str, unsigned int len)
{
  enum
    {
      TOTAL_KEYWORDS = 9,
      MIN_WORD_LENGTH = 3,
      MAX_WORD_LENGTH = 13,
      MIN_HASH_VALUE = 3,
      MAX_HASH_VALUE = 13,
      HASH_VALUE_RANGE = 11,
      DUPLICATES = 3,
      WORDLIST_SIZE = 12
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      unsigned int key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= MIN_HASH_VALUE)
        {
            {
              const char *resword; 

              switch (key)
                {
                case   3:
                  resword = "set"; break;
                case   5:
                  resword = "_is_a"; break;
                case   7:
                  resword = "destroy"; break;
                case   8:
                  resword = "get"; break;
                case  10:
                  resword = "_get_width";
                  if (*str == *resword && !ACE_OS::strncmp (str + 1, resword + 1, len - 1)) return resword;
                  resword = "_set_width";
                  if (*str == *resword && !ACE_OS::strncmp (str + 1, resword + 1, len - 1)) return resword;
                  return 0;
                case  11:
                  resword = "_get_height";
                  if (*str == *resword && !ACE_OS::strncmp (str + 1, resword + 1, len - 1)) return resword;
                  resword = "_set_height";
                  if (*str == *resword && !ACE_OS::strncmp (str + 1, resword + 1, len - 1)) return resword;
                  return 0;
                case  13:
                  resword = "_non_existent"; break;
                default: return 0;
                }
              if (*str == *resword && !ACE_OS::strncmp (str + 1, resword + 1, len - 1))
                return resword;
              return 0;
            }
        }
    }
  return 0;
}
