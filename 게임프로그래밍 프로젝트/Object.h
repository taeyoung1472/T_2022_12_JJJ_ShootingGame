#pragma once

enum class OBJECT_TYPE : UINT8
{
	NONE,

	COMPONENT,
	GAMEOBJECT,

	// Resource
	IMAGE,

	END,
};

enum
{
	OBJECT_TYPE_COUNT = static_cast<UINT8>(OBJECT_TYPE::END)
};


class Object
{
public:
	Object(OBJECT_TYPE type);
	virtual ~Object();

private:
	OBJECT_TYPE m_objectType = OBJECT_TYPE::NONE;
	string m_name;
};