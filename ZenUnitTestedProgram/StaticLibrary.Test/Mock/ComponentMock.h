#pragma once
#include "StaticLibrary/Component.h"

class ComponentMock : public Zen::Mock<Component>
{
public:
   ZENMOCK_VOID0(VirtualFunction)
};