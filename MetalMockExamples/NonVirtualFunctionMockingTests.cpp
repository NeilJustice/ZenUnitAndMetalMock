#include "pch.h"

class KernelBypassNetwork
{
public:
   // Non-virtual function for increased performance in a high-frequency trading environment
   void SendBytes(size_t /*numberOfBytes*/)
   {
   }
};

class KernelBypassNetworkMock : Metal::Mock<KernelBypassNetwork>
{
public:
   METALMOCK_VOID1_NONVIRTUAL(SendBytes, size_t)
};

// Mockable template parameter NetworkType
template<typename NetworkType = KernelBypassNetwork>
class OrderSender
{
   friend class OrderSenderTests;
private:
   NetworkType _network;
public:
   void SendOrder()
   {
      _network.SendBytes(123);
   }
};

TESTS(OrderSenderTests)
AFACT(SendOrder_CallsNetworkSendWhichReturns123_Returns)
EVIDENCE

// Template parameter dependency injection of MetalMock class KernelBypassNetworkMock
OrderSender<KernelBypassNetworkMock> _orderSender;

TEST(SendOrder_CallsNetworkSendWhichReturns123_Returns)
{
   _orderSender._network.SendBytesMock.Expect();
   //
   _orderSender.SendOrder();
   //
   METALMOCK(_orderSender._network.SendBytesMock.CalledOnceWith(123));
}

RUN_TESTS(OrderSenderTests)
