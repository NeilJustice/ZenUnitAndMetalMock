#include "pch.h"

class NetworkClient
{
public:
   virtual ~NetworkClient() = default;
   virtual void Connect() const {} // LCOV_EXCL_LINE
   virtual void UploadData() const {} // LCOV_EXCL_LINE
};

class NetworkClientMock : public Metal::Mock<NetworkClient>
{
public:
   METALMOCK_VOID0_CONST(Connect)
   METALMOCK_VOID0_CONST(UploadData)
};

class BusinessLogic
{
   friend class OrderedFunctionCallAssertionsTests;
private:
   std::unique_ptr<const NetworkClient> _networkClient;
public:
   BusinessLogic()
      : _networkClient(std::make_unique<NetworkClient>())
   {
   }

   void Run()
   {
      _networkClient->Connect();
      _networkClient->UploadData();
   }
};

TESTS(OrderedFunctionCallAssertionsTests)
AFACT(Run_ConnectsThenUploadsData)
EVIDENCE

BusinessLogic _businessLogic;
NetworkClientMock* _networkClientMock = nullptr;

STARTUP
{
   _businessLogic._networkClient.reset(_networkClientMock = new NetworkClientMock);
}

TEST(Run_ConnectsThenUploadsData)
{
   _networkClientMock->ConnectMock.Expect();
   _networkClientMock->UploadDataMock.Expect();
   //
   _businessLogic.Run();
   //
   METALMOCKTHEN(_networkClientMock->ConnectMock.CalledOnce()).Then(
   METALMOCKTHEN(_networkClientMock->UploadDataMock.CalledOnce()));
}

RUN_TESTS(OrderedFunctionCallAssertionsTests)
