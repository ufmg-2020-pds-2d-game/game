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

	void Start();
	void Update();
	void End();

	enum FactoryType {
		NO_COLLISION,
		STATIC,
		DYNAMIC
	};

	static Entity* Factory(const std::string& image, FactoryType t=STATIC);

	Component* Add(Component* c);

	template <typename T>
	T* New() {
		return (T*)Add((Component*)new T());
	}

	template <typename T>
	T* Get() {
		for (auto i : m_components) {
			T* c = dynamic_cast<T*>(i);
			if (c)	return c;
		}
		return nullptr;
	}

	template <typename T>
	void Remove() {
		size_t count = 0;
		for (auto i : m_components) {
			T* c = dynamic_cast<T*>(i);
			if (c) {
				i->End();
				break;
			}
			count++;
		}
		if (count < m_components.size()) {
			m_components.erase(m_components.begin());
		}
	}

protected:
	std::vector<Component*> m_components;

private:
	bool m_started;
};

#endif // ! ENTITY_H