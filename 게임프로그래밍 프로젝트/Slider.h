#pragma once
#include "SpriteRendere.h"

class Slider : public SpriteRendere
{
public:
	Slider();
	virtual ~Slider();

public:
	void Init(int max);
	void SetValue(int value);

public:
	virtual void Render() override;

private:
	int maxValue;
	int curValue;
};
