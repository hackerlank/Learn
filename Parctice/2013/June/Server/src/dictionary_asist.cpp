/****************************************************************
 * Filename: dictionary_asist.cpp
 * 
 * Description: 字典库
 *
 * Original Author : bison, 2012-10-16
 *
 ****************************************************************/
#include"dictionary_asist.h"
#include <locale.h>
# include <langinfo.h>
# define locale_charset()  nl_langinfo(CODESET)
#define ALPHA_ENC   "UCS-4LE"

#define N_ELEMENTS(a)   (sizeof(a)/sizeof((a)[0]))

iconv_t to_alpha_mode;
iconv_t from_alpha_mode;
Dictionary *dirtyWordsDict;
Dictionary *IllSymbolDict;

extern set<string> dirtyWordsPack;					//脏词库
extern set<string> illegalCharPack;					//命名非法符号

static void init_conv()
{
	const char *prev_locale;
    const char *locale_codeset;

    prev_locale = setlocale (LC_CTYPE, "");
    locale_codeset = locale_charset();
    setlocale (LC_CTYPE, prev_locale);
	cout<<"BisonTEst : locale_codeset is "<<locale_codeset<<endl;
	to_alpha_mode = iconv_open (ALPHA_ENC, locale_codeset);
	from_alpha_mode = iconv_open (locale_codeset, ALPHA_ENC);
}

static void close_conv()
{
    iconv_close (to_alpha_mode);
    iconv_close (from_alpha_mode);
}

static size_t conv_to_alpha(const char *in, AlpChar *out, size_t out_size)
{
    char   *in_p = (char *) in;
    char   *out_p = (char *) out;
    size_t  in_left = strlen (in);
    size_t  out_left = out_size * sizeof (AlpChar);
    size_t  res;
    const unsigned char *byte_p;

    if (sizeof (AlpChar) != 4)
	{
		cout<<"BisonSHow AlpChar is not 4 size"<<endl;
	}

    /* convert to UCS-4LE */
    res = iconv(to_alpha_mode, (char **) &in_p, &in_left,
                 (char **) &out_p, &out_left);

    if (res < 0)
        return res;

    /* convert UCS-4LE to AlphaChar string */
    res = 0;
    for (byte_p = (const unsigned char *)out;
         res < out_size && byte_p + 3 < (unsigned char*)out_p;
         byte_p += 4)
    {
        out[res++] = byte_p[0]
                     | (byte_p[1] << 8)
                     | (byte_p[2] << 16)
                     | (byte_p[3] << 24);
    }
    if (res < out_size) {
        out[res] = 0;
    }

    return res;
}

int alpCharLen(const AlpChar *alp)
{
	const AlpChar *base = alp;
	for (base; *base; base++);
	return base - alp;
}

static size_t conv_from_alpha(const AlpChar *in, char *out, size_t out_size)
{
    size_t  in_left = alpCharLen (in) * sizeof (AlpChar);
    size_t  res;

    if (sizeof (AlpChar) != 4)
	{
		cout<<"BisonWarning: very hurt really very hurt"<<endl;
	}
	
    /* convert AlphaChar to UCS-4LE */
    for (res = 0; in[res]; res++) {
        unsigned char  b[4];

        b[0] = in[res] & 0xff;
        b[1] = (in[res] >> 8) & 0xff;
        b[2] = (in[res] >> 16) & 0xff;
        b[3] = (in[res] >> 24) & 0xff;

        memcpy ((char *) &in[res], b, 4);
    }

    /* convert UCS-4LE to locale codeset */
    res = iconv (from_alpha_mode, (char **) &in, &in_left,
                 &out, &out_size);
    *out = 0;

    return res;
}


void initDirtyWordsDict()
{
	init_conv();
	
	dirtyWordsDict = new Dictionary();
	
	set<string>::iterator it;
	cout<<"BisonTest init begin with dictionary"<<endl;
	for (it = dirtyWordsPack.begin(); it != dirtyWordsPack.end(); it++)
	{
		string oneDirty = (*it);
		AlpChar out[oneDirty.size() + 1];
		conv_to_alpha(oneDirty.c_str(), out, N_ELEMENTS(out));
		//cout<<"@@@@@@@@@@@@@Before add one str to dictionary@@@@@@@@@@"<<endl;
		dirtyWordsDict->addOneStr(out);
		//cout<<"@@@@@@@@@@@@@After add one str to dictionary@@@@@@@@@@"<<endl;
	}
	cout<<"BisonTest init AFTER with dictionary"<<endl;
	close_conv();
}

void initIllSymbolDict()
{
	init_conv();
	
	IllSymbolDict = new Dictionary();
	
	set<string>::iterator it;
	for (it = illegalCharPack.begin(); it != illegalCharPack.end(); it++)
	{
		string oneIllegalSymbol = (*it);
		AlpChar out[oneIllegalSymbol.size() + 1];
		conv_to_alpha(oneIllegalSymbol.c_str(), out, N_ELEMENTS(out));
		IllSymbolDict->addOneStr(out);
	}
	
	close_conv();
}

void initDictionary()
{
	initDirtyWordsDict();
	initIllSymbolDict();
}

bool isHaveIllSymbol(char* strToCheck)
{
	init_conv();
	//转成alphaChar
	AlpChar checkStr[strlen(strToCheck) + 1];
	conv_to_alpha (strToCheck, checkStr, N_ELEMENTS(checkStr));
	close_conv();
	
	return IllSymbolDict->search(checkStr);
}

bool isHaveDirtyWords(char* strToCheck)
{
	init_conv();
	//转成alphaChar
	AlpChar checkStr[strlen(strToCheck) + 1];
	conv_to_alpha (strToCheck, checkStr, N_ELEMENTS(checkStr));
	close_conv();
	
	return dirtyWordsDict->search(checkStr);
}

//alpha格式字符串长度
int alphaCharLen(char* strToCheck)
{
	init_conv();
	//转成alphaChar
	AlpChar checkStr[strlen(strToCheck) + 1];
	conv_to_alpha (strToCheck, checkStr, N_ELEMENTS(checkStr));
	close_conv();
	
	const AlpChar *base;
	base = checkStr;
	for (base; *base; base++);
    return base - checkStr;
}