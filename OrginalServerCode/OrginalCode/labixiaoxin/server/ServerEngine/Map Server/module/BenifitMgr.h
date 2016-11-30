#pragma once

#include "ace\ace.h"
#include "BaseModule.h"
#include "..\..\Base\Event\EventListener.h"
#include "..\..\GameBase\res\BenifitRes.h"

typedef struct tagBenefitValueInfo
{
	//float fValue;
	//float fScale;
	ACE_UINT32 unValue;
	ACE_UINT32 unScale;
}BenefitValueInfo;

class BenifitMgr : public BaseModule, public EventListener
{
public:
	BenifitMgr();
	~BenifitMgr();

	void init();
	virtual void update(ACE_UINT32 unCurrentTime);

	virtual void handle_event(BaseEvent *e);

	int get_benefit(ACE_UINT32 unID, float base_value);

private:
	void update_2_db();

	BenefitValueInfo m_benefitList[BENEFIT_TYPE_MAX];

	void add_benefit(BenifitRes *benefitRes);
	void init_static_benefit();
};