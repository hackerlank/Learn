#include"read_rsa_key.h"

RSA *pubKey;

bool get_pubilc_key()
{
	pubKey = RSA_new();
	//char FileName[] = "config/pub_key/test_pub.pem";
	char FileName[] = "config/pub_key/test_pub.pem";
#if 1
	FILE *fp = fopen(FileName, "r");
	
	if (fp == NULL)
	{
		printf("FFFFFFFFFFFFFFFFFFF\n"); 
		return NULL;
	}
	//fclose(fp);
#endif 
	//rsaK=PEM_read_bio_RSAPublicKey(BP, NULL, NULL, NULL);
	pubKey=PEM_read_RSA_PUBKEY(fp, NULL, NULL, NULL);
	if(pubKey == NULL)
	{
		printf("读取公钥失败\n");
		fclose(fp);
		RSA_free(pubKey);
		return false;
	}
	else {
		printf("读取公钥成功\n");
	}
	fclose(fp);
	
}


BYTE Decode_GetByte(char c)
{
    if(c == '+')
        return 62;
    else if(c == '/')
        return 63;
    else if(c <= '9')
        return (BYTE)(c - '0' + 52);
    else if(c == '=')
        return 64;
    else if(c <= 'Z')
        return (BYTE)(c - 'A');
    else if(c <= 'z')
        return (BYTE)(c - 'a' + 26);
    return 64;
}

size_t Base64_Decode(char *pDest, const char *pSrc, size_t srclen)
{
    BYTE input[4];
    size_t i, index = 0;
    for(i = 0; i < srclen; i += 4)
    {
        //byte[0]
        input[0] = Decode_GetByte(pSrc[i]);
        input[1] = Decode_GetByte(pSrc[i + 1]);
        pDest[index++] = (input[0] << 2) + (input[1] >> 4);
        
        //byte[1]
        if(pSrc[i + 2] != '=')
        {
            input[2] = Decode_GetByte(pSrc[i + 2]);
            pDest[index++] = ((input[1] & 0x0f) << 4) + (input[2] >> 2);
        }

        //byte[2]
        if(pSrc[i + 3] != '=')
        {
            input[3] = Decode_GetByte(pSrc[i + 3]);
            pDest[index++] = ((input[2] & 0x03) << 6) + (input[3]);
        }            
    }

    //null-terminator
    pDest[index] = 0;
    return index;
}

void str2uc(char *src, int srcLen, unsigned char * dst, int dstLen)
{
	for (int i = 0; i < (srcLen / 2); i++)
	{
		int first = (src[2 * i] >= 'a' ) ? 10+src[2 * i]-'a' : src[2*i] - '0';
		int second = (src[2 * i+1] >= 'a') ? 10+src[2 * i+1]-'a' : src[2*i+1] - '0';
		dst[i] = (unsigned char)(first * 16 + second);
	}
	
}
