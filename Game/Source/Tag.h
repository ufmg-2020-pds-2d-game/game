#ifndef TAG_COMPONENT_H
#define TAG_COMPONENT_H

#include <string>

#include "Engine/Component.h"


class Tag : public Component {
public:
	Tag(const std::string& tag="");
	virtual ~Tag();

	std::string name;
protected:
	bool m_offsetY;
};

#endif // !TAG_COMPONENT_H