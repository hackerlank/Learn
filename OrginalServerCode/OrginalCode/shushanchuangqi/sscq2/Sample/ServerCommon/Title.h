#ifndef TRANS_TITLE_H_
#define TRANS_TITLE_H_
namespace TITLE_DATA
{
#define MAX_TILENUM  1000
#define MAX_TILELEN   250
    static char cHex[] ={ '0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};

    static char cBit[16][4] = { 
        {'0','0','0','0'},
        {'0','0','0','1'},
        {'0','0','1','0'},
        {'0','0','1','1'},
        {'0','1','0','0'},
        {'0','1','0','1'},
        {'0','1','1','0'},
        {'0','1','1','1'},
        {'1','0','0','0'},
        {'1','0','0','1'},
        {'1','0','1','0'},
        {'1','0','1','1'},
        {'1','1','0','0'},
        {'1','1','0','1'},
        {'1','1','1','0'},
        {'1','1','1','1'}
    };

    UINT8 GetNumByHex(char c)
    {
        UINT8 Num = 0;    
        if( c >= '0' && c <= '9')
        {
            Num = c - '0';
        }
        else if(c >= 'a' && c <= 'f')
        {
            Num = 10 + c - 'a';
        }
        return Num;

    }

    bool NumTitleIsValid(UINT16 wTitle)
    {
        if(wTitle > MAX_TILENUM || wTitle == 0)
        {
            return false;
        } 
        return true;
    }

    bool StrTitleIsValid(const string& strTitle)
    {
        return strTitle.size() >= MAX_TILELEN;
    }

    void VecNumToChar(const vector<UINT16> &vecData, string &strTitle)
    {
        char tempChar[MAX_TILENUM];
        if (!StrTitleIsValid(strTitle))
        {
            strTitle.clear();
            strTitle.resize(MAX_TILELEN,'0');
        }
        for( size_t it = 0;it != vecData.size();it++)
        {
            if(!NumTitleIsValid(vecData[it]))
            {
                continue;
            }
            tempChar[vecData[it]-1] = '1';
        }
        for( size_t it =0 ;it < MAX_TILENUM;it = it + 4)
        {
            UINT8 ucTemp = 0;

            for(size_t subit = it ;subit !=it + 4 ; subit++)
            {
                if(tempChar[subit] == '1')
                {
                    ucTemp += 1 << (3 + it - subit );
                }
            }       
            strTitle[it / 4] = cHex[ucTemp];
        }
    }

    void CharToVecNum(vector<UINT16> &vecData,const string & strTitle)
    {   
        if (!StrTitleIsValid(strTitle))
        {
            return ;
        }
        char tempChar[MAX_TILENUM];
        memset(tempChar,'0',MAX_TILENUM);
        for( size_t it = 0;it !=MAX_TILELEN;it++)
        { 
            memcpy(tempChar+it * 4,cBit[GetNumByHex(strTitle[it])],4);      
        }
        for( size_t it =0 ;it != MAX_TILENUM ;it ++)
        {
            if(tempChar[it] == '1')
            {
                vecData.push_back(it+1);
            }
        }
    }

    bool TestNum(UINT16 usTestId,const string & strTitle)
    {
        if (!StrTitleIsValid(strTitle))
        {
            return false;
        }
        if (!NumTitleIsValid(usTestId))
        {
            return false;
        }  
        return (GetNumByHex(strTitle[(usTestId-1) / 4]) & (1 << (3 - (usTestId-1) % 4))) >0 ;
    }

    void DelNum(UINT16 usDelId, string &strTitle)
    {
        if (!StrTitleIsValid(strTitle))
        {
            return ;
        }
        if (!NumTitleIsValid(usDelId))
        {
            return ;
        }  
        UINT8 Num = GetNumByHex(strTitle[(usDelId-1) / 4]);   
        Num = Num &(~(1 << (3 - (usDelId-1) % 4)));  
        strTitle[(usDelId-1) / 4] = cHex[Num];
    }

    void AddNum(UINT16 usAddId,string &strTitle)
    {
        if (!NumTitleIsValid(usAddId))
        {
            return ;
        }
        if (!StrTitleIsValid(strTitle))
        {
            strTitle.clear();
            strTitle.resize(MAX_TILELEN,'0');
        }
        UINT8 Num = GetNumByHex(strTitle[(usAddId-1) / 4]);
        Num = Num | (1 << (3 - (usAddId-1) % 4));
        strTitle[(usAddId-1) / 4] = cHex[Num];
    }
}
#endif
