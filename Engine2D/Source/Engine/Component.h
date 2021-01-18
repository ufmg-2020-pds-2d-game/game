#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

class Component {
public:
	Component();
	virtual ~Component();

	virtual void Start();
	virtual void Update();

	Entity* GetEntity();
	void SetEntity(Entity* e);
protected:
	Entity* m_entity;
};

#endif // !COMPONENT_H