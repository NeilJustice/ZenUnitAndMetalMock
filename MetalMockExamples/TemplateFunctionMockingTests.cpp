#include "pch.h"

class KernelBypassNetwork
{
public:
   // Non-virtual function for slightly increased performance in a high-frequency trading environment
   void Initialize()
   {
   }

   // Non-virtual function for slightly increased performance in a high-frequency trading environment
   size_t Send(size_t numberOfBytes)
   {
      return numberOfBytes;
   }
};

class KernelBypassNetworkMock : Metal::Mock<KernelBypassNetwork>
{
public:
   METALMOCK_VOID0_NONVIRTUAL(Initialize)
   METALMOCK_NONVOID1_NONVIRTUAL(size_t, Send, size_t)
};

// Default NetworkType to KernelBypassNetwork for production trading,
// with OrderSender unit tests to set NetworkType to KernelBypassNetworkMock
template<typename NetworkType = KernelBypassNetwork>
class OrderSender
{
   friend class OrderSenderTests;
private:
   NetworkType _network;
public:
   void InitializeNetwork()
   {
      _network.Initialize();
   }

   void SendOrder()
   {
      constexpr size_t numberOfBytesForOneOrder = 123;
      const size_t numberOfBytesSent = _network.Send(numberOfBytesForOneOrder);
      if (numberOfBytesSent != numberOfBytesForOneOrder)
      {
         throw std::runtime_error("Failed to send complete order to the exchange");
      }
   }
};

TESTS(OrderSenderTests)
AFACT(InitializeNetwork_CallsNetworkInitialize)
AFACT(SendOrder_CallsNetworkSendWhichReturns123_Returns)
FACTS(SendOrder_CallsNetworkSendWhichDoesNotReturn123_ThrowsRuntimeError)
EVIDENCE

// Template parameter dependency injection of MetalMock class KernelBypassNetworkMock
OrderSender<KernelBypassNetworkMock> _orderSender;

TEST(InitializeNetwork_CallsNetworkInitialize)
{
   _orderSender._network.InitializeMock.Expect();
   //
   _orderSender.InitializeNetwork();
   //
   METALMOCK(_orderSender._network.InitializeMock.CalledOnce());
}

TEST(SendOrder_CallsNetworkSendWhichReturns123_Returns)
{
   _orderSender._network.SendMock.Return(123);
   //
   _orderSender.SendOrder();
   //
   METALMOCK(_orderSender._network.SendMock.CalledOnceWith(123));
}

TEST1X1(SendOrder_CallsNetworkSendWhichDoesNotReturn123_ThrowsRuntimeError,
   size_t sendReturnValue,
   0,
   122,
   124,
   1000)
{
   _orderSender._network.SendMock.Return(sendReturnValue);
   //
   THROWS_EXCEPTION(_orderSender.SendOrder(),
      std::runtime_error, "Failed to send complete order to the exchange");
   //
   METALMOCK(_orderSender._network.SendMock.CalledOnceWith(123));
}

RUN_TESTS(OrderSenderTests)
