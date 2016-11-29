#ifndef CITTA_MGR_H
#define CITTA_MGR_H

#include "Singleton.h"

#include "Citta.h"

#include "CittaCFG.h"
#include "CittaMergeCFG.h"
#include "CittaSignetCFG.h"
#include "CittaSignetSuitCFG.h"

#include "Fighter.h"

enum ECittaAttrType
{
    eCittaAttrNone      = 0,
    eCittaAttrAttack    = 1,
    eCittaAttrPhyDef    = 2,
    eCittaAttrMgcDef    = 3,
    eCittaAttrHP        = 4,
    eCittaAttrHit       = 5,
    eCittaAttrDodge     = 6,
    eCittaAttrCri       = 7,
    eCittaAttrAntiCri   = 8,
    eCittaAttrPiece     = 9,
    eCittaAttrCounter   = 10,
    eCittaAttrResist    = 11,
    eCittaAttrMax
};

class CCittaMgr : public Singleton<CCittaMgr>
{

    public:
        bool Init();
        bool Reload();

        bool LoadConfig(const string &);

        ECittaResult GetMaterial(UINT32 dwFormulaID, map<UINT16, UINT32>& mapMaterial);
        ECittaResult GetBreakMaterial(UINT16 wItemID, UINT16& wMaterialID, UINT16& wCount);
        UINT32       GetMergeSilver(UINT32 dwFormulaID) const;
        UINT32       GetBreakSilver(UINT16 wItemID) const;
        UINT32       GetBreakLootID(UINT16 wItemID) const;

        ECittaResult GetCittaID(UINT32 dwFormulaID, UINT32 wCount, TVecUINT32& vecCittaID, TVecUINT32& vecSignet);

        ECittaResult SetCittaAttr(CCitta& rCitta);
        ECittaResult SetCittaSignet(CCitta& rCitta, UINT32 dwSignetID = 0);
        ECittaResult SetCittaSkill(CCitta& rCitta);
        bool         SignetToAttr(const TSetUINT32& setSignetID, TVecFloat& rvecAddAttr);
        ECittaNameType GetNameType(UINT16 wItemID, const TMapCittaAttr& rmapCittaAttr);


    private:
        struct SProbData
        {
            UINT32 _dwID;
            UINT32 _dwProb;
            UINT32 _dwVal;
            SProbData()
                : _dwID(0), _dwProb(0), _dwVal(0)
            {
            }
        };
        typedef vector<SProbData> TVecProbData;

        struct SSuitData
        {
            UINT8   _byCount;       // 套装个数
            UINT32  _dwAttrID;      // 套装激活的属性
            SSuitData()
                : _byCount(0), _dwAttrID(0)
            {
            }
        };
        typedef vector<SSuitData> TVecSuitData;

        bool InitProbData();
        bool InitSuitData();

        ECittaResult    AddOneCittaRandAttr(CCitta& rCitta, TVecUINT8& vecAttrType, TVecUINT32& vecAttrValue,
                UINT32 dwRangeMax, UINT32 dwRangeMin);
        bool            AddOneSuitAttr(UINT32 dwAttrID, TVecFloat& rvecAddAttr);

        bool AnalysisString2ProbData(const string& strValue, TVecProbData& vecProbData, const string& strSep = "|", const string& strSep2 = ";");
        bool AnalysisString2VectorUINT32(const string& strValue, TVecUINT32& vecData, const string& strSep = ";");
        bool AnalysisString2SetUINT32(const string& strValue, TSetUINT32& setData, const string& strSep = ",");

    private:
        CCittaLoader        	    _cLoader;
        CCittaMergeLoader   	    _cMergeLoader;
        CCittaSignetLoader  	    _cSignetLoader;
        CCittaSignetSuitLoader      _cSignetSuitLoader;

        map<UINT32, TVecProbData>   _mapMergeCittaID;       // 合成心法生成心法的概率
        map<UINT32, TVecUINT32>     _mapMergeSignetID;      // 合成心法带出印记的概率
        map<UINT32, TVecProbData>   _mapCittaSkillID;       // 合成心法带出技能的概率
        map<UINT32, TVecProbData>   _mapSignetID;           // 获得心法带出印记的概率
        map<UINT32, TSetUINT32>     _mapSignetSuitID;       // 印记套装
        map<UINT32, UINT32>         _mapSignetIndex;        // 印记索引
        map<UINT32, TVecSuitData>   _mapSignetSuitAttr;     // 印记激活的属性ID
};

#endif // #ifndef CITTA_MGR_H

