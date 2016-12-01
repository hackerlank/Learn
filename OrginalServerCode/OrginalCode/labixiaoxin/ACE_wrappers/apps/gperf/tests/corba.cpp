/* C code produced by gperf version 2.8 (ACE version) */
/* Command-line: ..\..\..\bin\ace_gperf -a -o corba.gperf  */
#include "ace/OS_NS_string.h"

#define TOTAL_KEYWORDS 36
#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 9
#define MIN_HASH_VALUE 4
#define MAX_HASH_VALUE 46
#define HASH_VALUE_RANGE 43
#define DUPLICATES 0
#define WORDLIST_SIZE 40

static unsigned int
hash (const char *str, unsigned int len)
{
  static unsigned char asso_values[] =
    {
#if defined (ACE_MVS)
     47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
     47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
     47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
     47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
     47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
     47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
     47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
     47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
     47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
     47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
     47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
     47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
     47, 47, 47, 47, 47, 47, 47, 47, 47, 30,
     15,  5, 10,  0, 30, 25, 30, 15, 47, 47,
     47, 47, 47, 47, 47, 47, 47, 15, 15,  5,
     40, 47, 47, 20, 47, 47, 47, 47, 47, 47,
     47, 47,  0,  0, 20, 20,  0, 47,  0, 47,
     47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
     47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
     47, 47, 47, 47, 47, 47, 47,  0, 10, 47,
     47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
     47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
     47, 47, 47, 47, 47, 47, 47,  0, 47, 47,
     47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
     47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
     47, 47, 47, 47, 47, 47,
#else
     47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
     47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
     47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
     47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
     47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
     47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
     47, 47, 47, 47, 47, 47, 47, 47, 47,  0,
     10, 47, 47, 47, 47, 47, 47, 47, 47, 47,
     47, 47, 47, 47,  0, 47, 47, 47, 47, 47,
     47, 47, 47, 47, 47, 47, 47, 30, 15,  5,
     10,  0, 30, 25, 30, 15, 47, 47, 15, 15,
      5, 40, 47, 47, 20,  0,  0, 20, 20,  0,
     47,  0, 47, 47, 47, 47, 47, 47,
#endif /* ACE_MVS */
    };
  return len + asso_values[(int) str[len - 1]] + asso_values[(int) str[0]];
}

const char *
in_word_set (const char *str, unsigned int len)
{
  static const char *wordlist[] =
    {
      "","","","",
      "TRUE", 
      "short", 
      "struct", 
      "",
      "sequence", 
      "case", 
      "const", 
      "native", 
      "context", 
      "",
      "exception", 
      "FALSE", 
      "double", 
      "default", 
      "",
      "enum", 
      "inout", 
      "module", 
      "in", 
      "",
      "interface", 
      "wchar", 
      "raises", 
      "boolean", 
      "readonly", 
      "char", 
      "union", 
      "string", 
      "wstring", 
      "any", 
      "void", 
      "float", 
      "switch", 
      "typedef", 
      "unsigned", 
      "attribute", 
      "","","",
      "out", 
      "long", 
      "octet", 
      "oneway", 
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
