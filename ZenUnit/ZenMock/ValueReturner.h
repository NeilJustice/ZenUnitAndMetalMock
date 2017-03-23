#pragma once
#include <vector>
#include "ZenUnit/ZenMock/Exceptions/ReturnValueMustBeSpecifiedException.h"

namespace ZenMock
{
   template<typename ReturnType>
   class ValueReturner
   {
      friend class ValueReturnerTests;
   private:
      const std::string ZenMockedFunctionSignature;
      using DecayedReturnType = typename std::decay<ReturnType>::type;
      std::vector<DecayedReturnType> returnValues;
      size_t returnValueIndex;
   public:
      ValueReturner(const std::string& zenMockedFunctionSignature)
         : ZenMockedFunctionSignature(zenMockedFunctionSignature)
         , returnValueIndex(0)
      {
      }

      void PrivatePushBackReturnValue(const ReturnType& returnValue)
      {
         returnValues.push_back(returnValue);
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void PrivatePushBackReturnValues(
         const FirstReturnValue& firstReturnValue,
         const SubsequentReturnValues&... subsequentReturnValues)
      {
         PrivatePushBackReturnValue(firstReturnValue);
         PrivatePushBackReturnValues(subsequentReturnValues...);
      }
      void PrivatePushBackReturnValues() {}

      void PrivatePushBackReturnValues(const std::vector<DecayedReturnType>& values)
      {
         if (values.empty())
         {
            throw std::invalid_argument(
               "ZenMock::ValueReturner::PrivatePushBackReturnValues(): Return values vector cannot be empty");
         }
         returnValues.insert(end(returnValues), values.cbegin(), values.cend());
      }

      template<typename FunctionReturnType = ReturnType>
      typename std::enable_if<std::is_default_constructible<
         FunctionReturnType>::value, FunctionReturnType>::type PrivateNextReturnValue()
      {
         if (returnValues.empty())
         {
            FunctionReturnType defaultReturnValue{};
            return defaultReturnValue;
         }
         return NextReturnValue();
      }

      template<typename FunctionReturnType = ReturnType>
      typename std::enable_if<!std::is_default_constructible<
         FunctionReturnType>::value, FunctionReturnType>::type PrivateNextReturnValue()
      {
         if (returnValues.empty())
         {
            throw ZenMock::ReturnValueMustBeSpecifiedException(ZenMockedFunctionSignature);
         }
         return NextReturnValue();
      }

      ReturnType NextReturnValue()
      {
         const DecayedReturnType& nextReturnValue =
            returnValueIndex < returnValues.size() ? returnValues[returnValueIndex++] : returnValues.back();
         return nextReturnValue;
      }
   };
}
