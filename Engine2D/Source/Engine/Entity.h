#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

#include "Engine\Math\Vector.h"

class Component;
class App;

class Entity {
public:
	Entity();
	virtual ~Entity();

	virtual void Start();
	virtual void Update();
	virtual void Draw(App* app);

	void AddComponent(Component* c);

	inline Vector* GetPosition() { return &position; }
	inline Vector* GetScale() { return &scale; }

protected:
	std::vector<Component*> m_components;

	Vector position;
	Vector scale;
private:
	bool m_started;
};

#endif // ! ENTITY_H