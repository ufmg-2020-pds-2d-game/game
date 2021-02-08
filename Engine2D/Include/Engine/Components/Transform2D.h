#ifndef TRANSFORM_2D_COMPONENT_H
#define TRANSFORM_2D_COMPONENT_H

#include "Engine/Component.h"

#include "Engine/Math/Vector.h"

class Transform2D : public Component {
public:
	Transform2D();
	Transform2D(Vector pos, Vector scl = Vector(400.f, 400.f));
	virtual ~Transform2D();

	Vector position;
	float rotation;
	Vector scale;
protected:
};

#endif // !TRANSFORM_2D_COMPONENT_H