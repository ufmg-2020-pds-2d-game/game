#ifndef VECTOR_H
#define VECTOR_H

class Vector {
public:
	Vector();
	Vector(float a, float b);
	Vector(const Vector& other);
	Vector& operator=(const Vector& other);
	virtual ~Vector();

	union {
		float x, u, s;
	};
	union {
		float y, v, t;
	};
};

#endif //!VECTOR_H