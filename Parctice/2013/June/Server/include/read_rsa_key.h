#ifndef _READ_RSA_KEY_H_
#define	_READ_RSA_KEY_H_

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <string.h>

typedef unsigned char BYTE;

extern RSA *pubKey;
bool get_pubilc_key();

size_t Base64_Decode(char *pDest, const char *pSrc, size_t srclen);

void str2uc(char *src, int srcLen, unsigned char * dst, int dstLen);
#endif