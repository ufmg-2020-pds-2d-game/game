#ifndef TEXT_COMPONENT_H
#define TEXT_COMPONENT_H

#include <string>

#include "Engine/Component.h"
#include "Engine/Math/Vector.h"


class Text : public Component {
public:
	Text();
	virtual ~Text();

	Vector position;
	float scale;
	std::string text;
protected:
};

#endif // !TEXT_COMPONENT_H