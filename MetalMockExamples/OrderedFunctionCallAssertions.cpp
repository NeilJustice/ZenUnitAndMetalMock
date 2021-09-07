#include "pch.h"

class NetworkClient
{
public:
   virtual ~NetworkClient() = default;
   virtual void Connect() const {}
   virtual void UploadData() const {}
};

class NetworkClientMock : public Metal::Mock<NetworkClient>
{
public:
   METALMOCK_VOID0_CONST(Connect)
   METALMOCK_VOID0_CONST(UploadData)
};

class BusinessLogic
{
   friend class BusinessLogicTests;
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

TESTS(BusinessLogicTests)
AFACT(Run_Connects_UploadsData_Disconnects)
EVIDENCE

BusinessLogic _businessLogic;
NetworkClientMock* _networkClientMock = nullptr;

STARTUP
{
   _businessLogic._networkClient.reset(_networkClientMock = new NetworkClientMock);
}

TEST(Run_Connects_UploadsData_Disconnects)
{
   _networkClientMock->ConnectMock.Expect();
   _networkClientMock->UploadDataMock.Expect();
   //
   _businessLogic.Run();
   //
   METALMOCKTHEN(_networkClientMock->ConnectMock.CalledOnce()).Then(
   METALMOCKTHEN(_networkClientMock->UploadDataMock.CalledOnce()));
}

RUN_TESTS(BusinessLogicTests)
