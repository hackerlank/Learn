/* C code produced by gperf version 2.8 (ACE version) */
/* Command-line: ..\..\..\bin\ace_gperf -a -D cpp.gperf  */
#include "ace/OS_NS_string.h"

#define TOTAL_KEYWORDS 73
#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 16
#define MIN_HASH_VALUE 3
#define MAX_HASH_VALUE 236
#define HASH_VALUE_RANGE 234
#define DUPLICATES 4
#define WORDLIST_SIZE 76

static unsigned int
hash (const char *str, unsigned int len)
{
  static unsigned char asso_values[] =
    {
#if defined (ACE_MVS)
     237, 237, 237, 237, 237, 237, 237, 237, 237, 237,
     237, 237, 237, 237, 237, 237, 237, 237, 237, 237,
     237, 237, 237, 237, 237, 237, 237, 237, 237, 237,
     237, 237, 237, 237, 237, 237, 237, 237, 237, 237,
     237, 237, 237, 237, 237, 237, 237, 237, 237, 237,
     237, 237, 237, 237, 237, 237, 237, 237, 237, 237,
     237, 237, 237, 237, 237, 237, 237, 237, 237, 237,
     237, 237, 237, 237, 237, 237, 237, 237, 237, 237,
     237, 237, 237, 237, 237, 237, 237, 237, 237, 237,
     237, 237, 237, 237, 237, 237, 237, 237, 237, 237,
     237, 237, 237, 237, 237, 237, 237, 237, 237, 237,
     237, 237, 237, 237, 237, 237, 237, 237, 237, 237,
     237, 237, 237, 237, 237, 237, 237, 237, 237,  25,
      10, 120,  80,  45,  55,  30,  35,  40, 237, 237,
     237, 237, 237, 237, 237, 237,   5,  10,   5,  55,
       0,  55,  10,  15, 237, 237, 237, 237, 237, 237,
     237, 237, 110,   0,   5,  15,   5,   0,   0, 237,
     237, 237, 237, 237, 237, 237, 237, 237, 237, 237,
     237, 237, 237, 237, 237, 237, 237, 237, 237, 237,
     237, 237, 237, 237, 237, 237, 237, 237, 237, 237,
     237, 237, 237, 237, 237, 237, 237, 237, 237, 237,
     237, 237, 237, 237, 237, 237, 237, 237, 237, 237,
     237, 237, 237, 237, 237, 237, 237, 237, 237, 237,
     237, 237, 237, 237, 237, 237, 237, 237, 237, 237,
     237, 237, 237, 237, 237, 237, 237, 237, 237, 237,
     237, 237, 237, 237, 237, 237,
#else
     237, 237, 237, 237, 237, 237, 237, 237, 237, 237,
     237, 237, 237, 237, 237, 237, 237, 237, 237, 237,
     237, 237, 237, 237, 237, 237, 237, 237, 237, 237,
     237, 237, 237, 237, 237, 237, 237, 237, 237, 237,
     237, 237, 237, 237, 237, 237, 237, 237, 237, 237,
     237, 237, 237, 237, 237, 237, 237, 237, 237, 237,
     237, 237, 237, 237, 237, 237, 237, 237, 237, 237,
     237, 237, 237, 237, 237, 237, 237, 237, 237, 237,
     237, 237, 237, 237, 237, 237, 237, 237, 237, 237,
     237, 237, 237, 237, 237, 237, 237,  25,  10, 120,
      80,  45,  55,  30,  35,  40, 237,   5,  10,   5,
      55,   0,  55,  10,  15, 110,   0,   5,  15,   5,
       0,   0, 237, 237, 237, 237, 237, 237,
#endif /* ACE_MVS */
    };
  return len + asso_values[(int) str[len - 1]] + asso_values[(int) str[0]];
}

const char *
in_word_set (const char *str, unsigned int len)
{
  static const char *wordlist[] =
    {
      "","","",
      "try", 
      "throw", 
      "wchar_t", 
      "or_eq", 
      "xor_eq", 
      "or", 
      "xor", 
      "break", 
      "operator", 
      "bool", 
      "auto", 
      "bitor", 
      "reinterpret_cast", 
      "virtual", 
      "asm", 
      "goto", 
      "register", 
      "using", 
      "and_eq", 
      "int", 
      "long", 
      "true", 
      "explicit", 
      "typename", 
      "template", 
      "enum", 
      "while", 
      "mutable", 
      "not", 
      "float", 
      "typedef", 
      "new", 
      "union", 
      "volatile", 
      "not_eq", 
      "for", 
      "return", 
      "do", 
      "typeid", 
      "default", 
      "inline", 
      "dynamic_cast", 
      "unsigned", 
      "else", 
      "bitand", 
      "if", 
      "void", 
      "false", 
      "extern", 
      "private", 
      "and", 
      "namespace", 
      "this", 
      "short", 
      "struct", 
      "static_cast", 
      "const", 
      "const_cast", 
      "delete", 
      "double", 
      "compl", 
      "char", 
      "friend", 
      "protected", 
      "switch", 
      "catch", 
      "case", 
      "sizeof", 
      "continue", 
      "public", 
      "signed", 
      "class", 
      "static", 
    };

  static signed short lookup[] =
    {
        -1,   -1,   -1,    3,   -1,   -1,   -1,   -1,   -1,   -1,    4,   -1,    5,   -1, 
        -1,    6,    7,    8,    9,   -1,   10,   -1,   -1,   11,   12,   -1,   -1,   -1, 
        -1,   13,   14,   15,   16,   17,   18,   -1,   -1,   -1,   19,   -1,   20,   21, 
        -1,   22,   23,   -1,   -1,   -1,   -1,   24,   -1,  -25,   -3, -238,   28,   29, 
        -1,   30,   31,   -1,   32,   -1,   33,   34,   -1,   35,   -1,   -1,   36,   -1, 
        -1,   37,   -1,   38,   -1,   -1,   39,   -1,   -1,   -1,   -1,   -1,   40,   -1, 
        -1,   -1,   41,   42,   -1,   -1,   -1,   43,   44,   45,   46,   -1,   47,   48, 
        -1,   49,   -1,   -1,   -1,   -1,   -1,   50,   51,   52,   53,   54,   -1,   -1, 
        -1,   -1,   55,   56,   57,   -1,   -1,   -1,   -1,   58,   -1,   -1,   -1,   59, 
        -1,   -1,  -61,   -2,   60, -239,   -1,   -1,   -1,   63,   -1,   -1,   -1,   64, 
        -1,   65,   -1,   -1,   66,   -1,   -1,   -1,   -1,   -1,   -1,   67,   -1,   -1, 
        -1,   -1,   -1,   -1,   -1,   -1,   68,   -1,   -1,   -1,   -1,   -1,   -1,   -1, 
        -1,   69,   -1,   70,   -1,   71,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   72, 
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1, 
        73,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1, 
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1, 
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   74,   75, 
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
