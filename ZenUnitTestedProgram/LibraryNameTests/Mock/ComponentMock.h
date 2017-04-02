#pragma once
#include "LibraryName/Component.h"

class ComponentMock : public Zen::Mock<Component>
{
public:
   ZENMOCK_VOID0(VirtualFunction)
};
