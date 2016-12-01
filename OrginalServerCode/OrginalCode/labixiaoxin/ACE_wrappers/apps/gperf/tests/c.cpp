/* C code produced by gperf version 2.8 (ACE version) */
/* Command-line: ..\..\..\bin\ace_gperf -a -p -c -l -S1 -o c.gperf  */
#include "ace/OS_NS_string.h"

#define TOTAL_KEYWORDS 32
#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 8
#define MIN_HASH_VALUE 3
#define MAX_HASH_VALUE 48
#define HASH_VALUE_RANGE 46
#define DUPLICATES 0
#define WORDLIST_SIZE 35

static unsigned int
hash (const char *str, unsigned int len)
{
  static unsigned char asso_values[] =
    {
#if defined (ACE_MVS)
     49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
     49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
     49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
     49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
     49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
     49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
     49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
     49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
     49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
     49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
     49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
     49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
     49, 49, 49, 49, 49, 49, 49, 49, 49, 28,
      5, 15,  5,  0, 20, 13, 10,  0, 49, 49,
     49, 49, 49, 49, 49, 49,  0, 20,  5, 23,
      0, 49, 49,  5, 49, 49, 49, 49, 49, 49,
     49, 49, 10,  0, 20,  5,  0, 49, 49, 49,
     49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
     49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
     49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
     49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
     49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
     49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
     49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
     49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
     49, 49, 49, 49, 49, 49,
#else
     49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
     49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
     49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
     49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
     49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
     49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
     49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
     49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
     49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
     49, 49, 49, 49, 49, 49, 49, 28,  5, 15,
      5,  0, 20, 13, 10,  0, 49,  0, 20,  5,
     23,  0, 49, 49,  5, 10,  0, 20,  5,  0,
     49, 49, 49, 49, 49, 49, 49, 49,
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
            {
              const char *resword; unsigned int key_len;

              switch (key)
                {
                case   3:
                  resword = "int"; key_len = 3; break;
                case   4:
                  resword = "else"; key_len = 4; break;
                case   5:
                  resword = "while"; key_len = 5; break;
                case   7:
                  resword = "do"; key_len = 2; break;
                case   9:
                  resword = "enum"; key_len = 4; break;
                case  10:
                  resword = "break"; key_len = 5; break;
                case  11:
                  resword = "double"; key_len = 6; break;
                case  12:
                  resword = "default"; key_len = 7; break;
                case  13:
                  resword = "volatile"; key_len = 8; break;
                case  14:
                  resword = "void"; key_len = 4; break;
                case  15:
                  resword = "short"; key_len = 5; break;
                case  16:
                  resword = "struct"; key_len = 6; break;
                case  17:
                  resword = "goto"; key_len = 4; break;
                case  18:
                  resword = "register"; key_len = 8; break;
                case  19:
                  resword = "case"; key_len = 4; break;
                case  20:
                  resword = "const"; key_len = 5; break;
                case  21:
                  resword = "signed"; key_len = 6; break;
                case  22:
                  resword = "if"; key_len = 2; break;
                case  23:
                  resword = "continue"; key_len = 8; break;
                case  24:
                  resword = "char"; key_len = 4; break;
                case  25:
                  resword = "float"; key_len = 5; break;
                case  26:
                  resword = "switch"; key_len = 6; break;
                case  27:
                  resword = "typedef"; key_len = 7; break;
                case  28:
                  resword = "for"; key_len = 3; break;
                case  29:
                  resword = "extern"; key_len = 6; break;
                case  31:
                  resword = "static"; key_len = 6; break;
                case  32:
                  resword = "auto"; key_len = 4; break;
                case  33:
                  resword = "unsigned"; key_len = 8; break;
                case  34:
                  resword = "return"; key_len = 6; break;
                case  36:
                  resword = "sizeof"; key_len = 6; break;
                case  37:
                  resword = "long"; key_len = 4; break;
                case  48:
                  resword = "union"; key_len = 5; break;
                default: return 0;
                }
              if (len == key_len && *str == *resword && !ACE_OS::strncmp (str + 1, resword + 1, len - 1))
                return resword;
              return 0;
            }
        }
    }
  return 0;
}
