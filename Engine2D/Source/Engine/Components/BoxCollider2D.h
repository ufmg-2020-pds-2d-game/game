#ifndef BOX_COLLIDER_2D_COMPONENT_H
#define BOX_COLLIDER_2D_COMPONENT_H

#include <Gunslinger/gs.h>

#include "Engine/Component.h"

// Se uma Entidade tiver um BoxCollider2D, significa que a engine
// irá usar a área definida pelo Transform2D da entidade para calcular
// Colisões.
class BoxCollider2D : public Component {
public:
	BoxCollider2D();
	BoxCollider2D(float w, float h);
	virtual ~BoxCollider2D();

	gs_aabb_t GetBoundingBox();

	// Defaults: 1.0f
	// Use esses parâmetros caso você queira deixar o BoundingBox
	// menor ou maior que a forma original do objeto.
	float width, height;
};

#endif // !BOX_COLLIDER_2D_COMPONENT_H