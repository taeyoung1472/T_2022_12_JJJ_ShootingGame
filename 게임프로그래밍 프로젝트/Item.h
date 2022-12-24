#pragma once
#include "MonoBehaviour.h"

enum class ITEM_TYPE
{
	HP,
	OTHER1,
	OTHER2,
	END
};

class Item : public MonoBehaviour
{
public:
	Item();
	virtual ~Item();

	virtual void CollisionEnter(weak_ptr<Collider> collision) override;

	void SetType(ITEM_TYPE type) { m_type = type; }

private:
	ITEM_TYPE m_type;
};

