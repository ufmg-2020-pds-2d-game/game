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
	virtual ~BoxCollider2D();

	gs_aabb_t GetBoundingBox();
};

#endif // !BOX_COLLIDER_2D_COMPONENT_H