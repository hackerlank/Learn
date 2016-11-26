/****************************************************************
 * Filename: dictionary_asist.h
 * 
 * Description: ×Öµä¿â
 *
 * Original Author : bison, 2012-10-16
 *
 ****************************************************************/
 
#ifndef _DICTIONARY_ASIST_H_
#define _DICTIONARY_ASIST_H_

#include"dictionary.h"
#include <iconv.h>
#include<string>
#include<iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <set>
#include <map>
using namespace std;

//³õÊ¼ÆÁ±Î×Öµä
void initDictionary();
//ÆÁ±ÎÔà´Ê
bool isHaveDirtyWords(char* strToCheck);
//ÆÁ±Î±êµã·ûºÅ
bool isHaveIllSymbol(char* strToCheck);
//alpha¸ñÊ½×Ö·û´®³¤¶È
int alphaCharLen(char* strToCheck);
#endif
