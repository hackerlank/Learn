#include "key.h"
unsigned long hashKey(unsigned int key1,unsigned int key2)
{
    unsigned long key = key1;
    key <<= 32;
    key += key2;
    return key;
}

unsigned int hashKey(unsigned short key1,unsigned short key2)
{
    unsigned int key = key1;
    key <<= 16;
    key += key2;
    return key;
}

unsigned short hashKey(unsigned char key1,unsigned char key2)
{
    unsigned short key = key1;
    key <<= 8;
    key += key2;
    return key;
}
