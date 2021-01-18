#ifndef ENTITY_H
#define ENTITY_H

#include "Engine\Math\Vector.h"

class App;

class Entity {
public:
	Entity();
	virtual ~Entity();

	virtual void Start();
	virtual void Update();
	virtual void Draw(App* app);

	inline Vector* GetPosition() { return &position; }
	inline Vector* GetScale() { return &scale; }

protected:
	Vector position;
	Vector scale;
private:
};

#endif // ! ENTITY_H