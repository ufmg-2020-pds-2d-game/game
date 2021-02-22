#ifndef TEST_MOCKS_H
#define TEST_MOCKS_H

#include "pch.h"

#include "Engine.h"

class TestComponentVirtualMethods : public Component {
public:
	TestComponentVirtualMethods() {
		calledStart = nullptr;
		calledUpdate = nullptr;
		calledEnd = nullptr;
	}
	virtual ~TestComponentVirtualMethods() {

	}

	// Ponteiros para três booleanas. Eles são setados
	// como true (caso não nulos) assim que o App chama
	// cada um dessas funções.
	bool* calledStart;
	bool* calledUpdate;
	bool* calledEnd;

	// Aqui as três funções sobrescritas para fazer isso:
	virtual void Start() override {
		if (calledStart) {
			*calledStart = true;
		}
	}
	virtual void Update() override {
		if (calledUpdate) {
			*calledUpdate = true;
		}
	}
	virtual void End() override {
		if (calledEnd) {
			*calledEnd = true;
		}
	}
};

#endif // !TEST_MOCKS_H