#ifndef TEST_MOCKS_H
#define TEST_MOCKS_H

#include "pch.h"

#include "Engine.h"

class TestComponentVirtualMethods : public Component {
public:
    TestComponentVirtualMethods() {

    }
    virtual ~TestComponentVirtualMethods() {

    }

    virtual void Start() override {

    }
    virtual void Update() override {

    }
    virtual void End() override {

    }
};

#endif // !TEST_MOCKS_H