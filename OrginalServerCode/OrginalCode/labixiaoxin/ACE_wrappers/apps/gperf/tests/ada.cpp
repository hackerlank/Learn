/* C code produced by gperf version 2.8 (ACE version) */
/* Command-line: ..\..\..\bin\ace_gperf -a -k1,4,$ ada.gperf  */
#include "ace/OS_NS_string.h"

#define TOTAL_KEYWORDS 63
#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 9
#define MIN_HASH_VALUE 3
#define MAX_HASH_VALUE 181
#define HASH_VALUE_RANGE 179
#define DUPLICATES 0
#define WORDLIST_SIZE 66

static unsigned int
hash (const char *str, unsigned int len)
{
  static unsigned char asso_values[] =
    {
#if defined (ACE_MVS)
     182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
     182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
     182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
     182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
     182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
     182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
     182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
     182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
     182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
     182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
     182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
     182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
     182, 182, 182, 182, 182, 182, 182, 182, 182,  60,
      15,  45,  30,   0,   5,  60,  20,  47, 182, 182,
     182, 182, 182, 182, 182, 182,  35,   5,  41,  15,
      20,  55, 182,  40, 182, 182, 182, 182, 182, 182,
     182, 182,  20,   5,   0,  15,   0,   0,   0, 182,
     182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
     182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
     182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
     182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
     182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
     182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
     182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
     182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
     182, 182, 182, 182, 182, 182,
#else
     182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
     182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
     182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
     182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
     182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
     182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
     182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
     182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
     182, 182, 182, 182, 182, 182, 182, 182, 182, 182,
     182, 182, 182, 182, 182, 182, 182,  60,  15,  45,
      30,   0,   5,  60,  20,  47, 182,  35,   5,  41,
      15,  20,  55, 182,  40,  20,   5,   0,  15,   0,
       0,   0, 182, 182, 182, 182, 182, 182,
#endif /* ACE_MVS */
    };
  unsigned int hval = len;

  switch (hval)
    {
      default:
      case 4:
        hval += asso_values[(int) str[3]];
      case 3:
      case 2:
      case 1:
        hval += asso_values[(int) str[0]];
    }
  return hval + asso_values[(int) str[len - 1]];
}

const char *
in_word_set (const char *str, unsigned int len)
{
  static const char *wordlist[] =
    {
      "","","",
      "use", 
      "else", 
      "","","","",
      "type", 
      "while", 
      "","","",
      "exit", 
      "","","",
      "new", 
      "body", 
      "","","",
      "not", 
      "exception", 
      "","",
      "of", 
      "out", 
      "null", 
      "",
      "select", 
      "subtype", 
      "end", 
      "when", 
      "","","","",
      "then", 
      "","",
      "declare", 
      "xor", 
      "with", 
      "entry", 
      "others", 
      "reverse", 
      "for", 
      "case", 
      "","",
      "do", 
      "",
      "if", 
      "terminate", 
      "",
      "elsif", 
      "","","",
      "return", 
      "or", 
      "",
      "in", 
      "raise", 
      "",
      "at", 
      "all", 
      "is", 
      "",
      "accept", 
      "",
      "function", 
      "mod", 
      "","",
      "private", 
      "constant", 
      "task", 
      "","",
      "begin", 
      "abs", 
      "rem", 
      "",
      "access", 
      "",
      "separate", 
      "limited", 
      "","","",
      "and", 
      "",
      "delay", 
      "record", 
      "package", 
      "","",
      "delta", 
      "","",
      "digits", 
      "goto", 
      "range", 
      "","","",
      "procedure", 
      "abort", 
      "",
      "generic", 
      "","","","","","",
      "loop", 
      "","","","","",
      "array", 
      "",
      "renames", 
      "","","","","","","","","",
      "","","","","","","","","",
      "","","","","","","","","",
      "","","","","","","","","",
      "","","","","","","","","",
      "","","","","","","","",
      "pragma", 
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      unsigned int key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= MIN_HASH_VALUE)
        {
          const char *s = wordlist[key];

          if (*str == *s && !ACE_OS::strcmp (str + 1, s + 1))
            return s;
        }
    }
  return 0;
}
