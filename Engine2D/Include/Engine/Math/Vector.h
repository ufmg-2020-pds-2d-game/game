#ifndef VECTOR_H
#define VECTOR_H

class Vector {
public:
	Vector();
	Vector(float a, float b);
	Vector(const Vector& other);
	Vector& operator=(const Vector& other);
	virtual ~Vector();
	
	Vector operator+(const Vector& a);
	Vector operator-(const Vector& a);
	Vector operator*(const float& a);
	Vector operator/(const float& a);

	bool operator==(const Vector& a);

	// Assignment operators
	void operator+=(const Vector& a);
	void operator-=(const Vector& a);
	void operator*=(const float& a);
	void operator/=(const float& a);

	// Retorna o comprimento do vetor (sqrt(x*x+y*y)) 
	float Length();
	// Normaliza o Vetor (divide x e y pelo comprimento)
	void Normalize();
	// Retorna uma cópia normalizada do Vetor
	Vector Normalized();

	union {
		float x, u, s;
	};
	union {
		float y, v, t;
	};
};

#endif //!VECTOR_H