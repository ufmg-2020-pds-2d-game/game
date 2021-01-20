#ifndef TRANSFORM_2D_COMPONENT_H
#define TRANSFORM_2D_COMPONENT_H

#include "Engine/Component.h"

#include "Engine/Math/Vector.h"

class Transform2D : public Component {
public:
	Transform2D();
	virtual ~Transform2D();

	Vector position;
	float rotation;
	Vector scale;
protected:
};

#endif // !TRANSFORM_2D_COMPONENT_H