#ifndef __PIECEROLERES_H_
#define __PIECEROLERES_H_
#include "BaseRes.h"

class PieceRoleRes : public BaseRes
{
public:
	PieceRoleRes(ACE_UINT32 unType);
	virtual ~PieceRoleRes();

	virtual int parse_xml_node(xmlNodePtr node);
	
	CostInfoList m_cost;//额外资源：填入额外需求的资源的ID和对应的数量，用“,”隔开。
	ACE_UINT32 m_piece_id;//碎片ID：填入伙伴碎片的ID-第6个商品
	ACE_UINT32 m_use_amount;//需求数量：填入转换角色需求的数量
	ACE_UINT32 m_character_id;//目标角色ID：填入转换后可以获得的伙伴的ID
};

#endif