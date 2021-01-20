#ifndef IMAGE_2D_COMPONENT_H
#define IMAGE_2D_COMPONENT_H

#include <string>

#include "Engine/Component.h"


class Image2D : public Component {
public:
	Image2D();
	virtual ~Image2D();

	std::string imageName;
protected:
};

#endif // !IMAGE_2D_COMPONENT_H