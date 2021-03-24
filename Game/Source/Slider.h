#ifndef SLIDER_COMPONENT_H
#define SLIDER_COMPONENT_H

#include "Engine/Component.h"

#define NUM_COLUMNS 30
#define SLIDER_START_Y 700.f

class Slider : public Component {
public:
	Slider(bool offsetY=false, float velocity = 500.f);
	virtual ~Slider();

	virtual void Update() override;

	float speed;
protected:
	bool m_offsetY;
};

#endif // !SLIDER_COMPONENT_H