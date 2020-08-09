#include "pch.h"

class KernelBypassNetwork
{
public:
   // Non-virtual for performance
   void Initialize()
   {
   }

   // Non-virtual for performance
   bool Send(unsigned)
   {
      return true;
   }
};

class KernelBypassNetworkMock : Zen::Mock<KernelBypassNetwork>
{
public:
   METALMOCK_VOID0_NONVIRTUAL(Initialize)
   METALMOCK_NONVOID1_NONVIRTUAL(bool, Send, unsigned)
};

// Increased code complexity (which may be worth it) by having to templatize the class under test
template<typename NetworkType = KernelBypassNetwork>
class OrderSender
{
   friend class OrderSenderTests;
private:
   NetworkType _network;
public:
   void Initialize()
   {
      _network.Initialize();
   }

   void SendOrder(unsigned size)
   {
      const bool didSendOrder = _network.Send(size);
      if (!didSendOrder)
      {
         throw std::runtime_error("Failed to send order to exchange");
      }
   }
};

TESTS(OrderSenderTests)
AFACT(Initialize_CallsNetworkInitialize)
AFACT(SendOrder_CallsNetworkSendWhichReturnsTrue_Returns)
AFACT(SendOrder_CallsNetworkSendWhichReturnsFalse_Throws)
EVIDENCE

// Template parameter dependency injection of MetalMock class KernelBypassNetworkMock
OrderSender<KernelBypassNetworkMock> _orderSender;

TEST(Initialize_CallsNetworkInitialize)
{
   _orderSender._network.InitializeMock.Expect();
   //
   _orderSender.Initialize();
   //
   METALMOCK(_orderSender._network.InitializeMock.CalledOnce());
}

TEST(SendOrder_CallsNetworkSendWhichReturnsTrue_Returns)
{
   _orderSender._network.SendMock.Return(true);
   const unsigned size = ZenUnit::Random<unsigned>();
   //
   _orderSender.SendOrder(size);
   //
   METALMOCK(_orderSender._network.SendMock.CalledOnceWith(size));
}

TEST(SendOrder_CallsNetworkSendWhichReturnsFalse_Throws)
{
   _orderSender._network.SendMock.Return(false);
   const unsigned size = ZenUnit::Random<unsigned>();
   //
   THROWS_EXCEPTION(_orderSender.SendOrder(size),
      std::runtime_error, "Failed to send order to exchange");
   //
   METALMOCK(_orderSender._network.SendMock.CalledOnceWith(size));
}

RUN_TESTS(OrderSenderTests)
