#ifndef CAMERA_2D_COMPONENT_H
#define CAMERA_2D_COMPONENT_H

#include "Engine/Component.h"

#include "Engine/Math/Vector.h"

class Camera2D : public Component {
public:
	Camera2D(Vector camOffset=Vector());
	virtual ~Camera2D();

	Vector GetPosition();

	virtual void Update() override;

	float zoom;
	Vector offset;
private:
};

#endif // !CAMERA_2D_COMPONENT_H