/* C code produced by gperf version 2.8 (ACE version) */
/* Command-line: ..\..\..\bin\ace_gperf -a -o -S2 -p pascal.gperf  */
#include "ace/OS_NS_string.h"

#define TOTAL_KEYWORDS 36
#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 9
#define MIN_HASH_VALUE 2
#define MAX_HASH_VALUE 68
#define HASH_VALUE_RANGE 67
#define DUPLICATES 0
#define WORDLIST_SIZE 38

static unsigned int
hash (const char *str, unsigned int len)
{
  static unsigned char asso_values[] =
    {
#if defined (ACE_MVS)
     69, 69, 69, 69, 69, 69, 69, 69, 69, 69,
     69, 69, 69, 69, 69, 69, 69, 69, 69, 69,
     69, 69, 69, 69, 69, 69, 69, 69, 69, 69,
     69, 69, 69, 69, 69, 69, 69, 69, 69, 69,
     69, 69, 69, 69, 69, 69, 69, 69, 69, 69,
     69, 69, 69, 69, 69, 69, 69, 69, 69, 69,
     69, 69, 69, 69, 69, 69, 69, 69, 69, 69,
     69, 69, 69, 69, 69, 69, 69, 69, 69, 69,
     69, 69, 69, 69, 69, 69, 69, 69, 69, 69,
     69, 69, 69, 69, 69, 69, 69, 69, 69, 69,
     69, 69, 69, 69, 69, 69, 69, 69, 69, 69,
     69, 69, 69, 69, 69, 69, 69, 69, 69, 69,
     69, 69, 69, 69, 69, 69, 69, 69, 69,  5,
      5,  5,  0,  0, 45, 15, 15, 10, 69, 69,
     69, 69, 69, 69, 69, 69, 69,  0, 30, 15,
      0, 25, 69,  5, 69, 69, 69, 69, 69, 69,
     69, 69,  0, 10, 10, 40,  5, 69, 20, 69,
     69, 69, 69, 69, 69, 69, 69, 69, 69, 69,
     69, 69, 69, 69, 69, 69, 69, 69, 69, 69,
     69, 69, 69, 69, 69, 69, 69, 69, 69, 69,
     69, 69, 69, 69, 69, 69, 69, 69, 69, 69,
     69, 69, 69, 69, 69, 69, 69, 69, 69, 69,
     69, 69, 69, 69, 69, 69, 69, 69, 69, 69,
     69, 69, 69, 69, 69, 69, 69, 69, 69, 69,
     69, 69, 69, 69, 69, 69, 69, 69, 69, 69,
     69, 69, 69, 69, 69, 69,
#else
     69, 69, 69, 69, 69, 69, 69, 69, 69, 69,
     69, 69, 69, 69, 69, 69, 69, 69, 69, 69,
     69, 69, 69, 69, 69, 69, 69, 69, 69, 69,
     69, 69, 69, 69, 69, 69, 69, 69, 69, 69,
     69, 69, 69, 69, 69, 69, 69, 69, 69, 69,
     69, 69, 69, 69, 69, 69, 69, 69, 69, 69,
     69, 69, 69, 69, 69, 69, 69, 69, 69, 69,
     69, 69, 69, 69, 69, 69, 69, 69, 69, 69,
     69, 69, 69, 69, 69, 69, 69, 69, 69, 69,
     69, 69, 69, 69, 69, 69, 69,  5,  5,  5,
      0,  0, 45, 15, 15, 10, 69, 69,  0, 30,
     15,  0, 25, 69,  5,  0, 10, 10, 40,  5,
     69, 20, 69, 69, 69, 69, 69, 69,
#endif /* ACE_MVS */
    };
  return len + asso_values[(int) str[len - 1]] + asso_values[(int) str[0]];
}

const char *
in_word_set (const char *str, unsigned int len)
{
  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      unsigned int key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= MIN_HASH_VALUE)
        {
          if (key <= 21)
            {
              const char *resword; 

              switch (key - 2)
                {
                case   0:
                  resword = "do"; break;
                case   1:
                  resword = "end"; break;
                case   2:
                  resword = "else"; break;
                case   3:
                  resword = "label"; break;
                case   4:
                  resword = "downto"; break;
                case   5:
                  resword = "or"; break;
                case   6:
                  resword = "and"; break;
                case   7:
                  resword = "case"; break;
                case   8:
                  resword = "while"; break;
                case   9:
                  resword = "record"; break;
                case  10:
                  resword = "to"; break;
                case  11:
                  resword = "set"; break;
                case  12:
                  resword = "type"; break;
                case  13:
                  resword = "until"; break;
                case  16:
                  resword = "nil"; break;
                case  17:
                  resword = "goto"; break;
                case  18:
                  resword = "const"; break;
                case  19:
                  resword = "repeat"; break;
                default: return 0;
                }
              if (*str == *resword && !ACE_OS::strcmp (str + 1, resword + 1))
                return resword;
              return 0;
            }
          if (key <= 68)
            {
              const char *resword; 

              switch (key - 24)
                {
                case   0:
                  resword = "with"; break;
                case   1:
                  resword = "begin"; break;
                case   3:
                  resword = "in"; break;
                case   4:
                  resword = "not"; break;
                case   5:
                  resword = "then"; break;
                case   6:
                  resword = "array"; break;
                case   7:
                  resword = "packed"; break;
                case   9:
                  resword = "mod"; break;
                case  10:
                  resword = "procedure"; break;
                case  19:
                  resword = "div"; break;
                case  23:
                  resword = "of"; break;
                case  24:
                  resword = "var"; break;
                case  25:
                  resword = "file"; break;
                case  28:
                  resword = "forward"; break;
                case  29:
                  resword = "for"; break;
                case  33:
                  resword = "if"; break;
                case  38:
                  resword = "program"; break;
                case  44:
                  resword = "function"; break;
                default: return 0;
                }
              if (*str == *resword && !ACE_OS::strcmp (str + 1, resword + 1))
                return resword;
              return 0;
            }
        }
    }
  return 0;
}
