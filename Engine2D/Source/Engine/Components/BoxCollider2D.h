#ifndef BOX_COLLIDER_2D_COMPONENT_H
#define BOX_COLLIDER_2D_COMPONENT_H

#include "Engine/Component.h"

// Se uma Entidade tiver um BoxCollider2D, significa que a engine
// irá usar a área definida pelo Transform2D da entidade para calcular
// Colisões.
class BoxCollider2D : public Component {
public:
	BoxCollider2D();
	virtual ~BoxCollider2D();
};

#endif // !BOX_COLLIDER_2D_COMPONENT_H