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
      std::vector<DecayedReturnType> _returnValues;
      size_t _returnValueIndex;
   public:
      ValueReturner(const std::string& zenMockedFunctionSignature)
         : ZenMockedFunctionSignature(zenMockedFunctionSignature)
         , _returnValueIndex(0)
      {
      }

      void PrivatePushBackReturnValue(const ReturnType& returnValue)
      {
         _returnValues.push_back(returnValue);
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
         _returnValues.insert(end(_returnValues), values.cbegin(), values.cend());
      }

      template<typename FunctionReturnType = ReturnType>
      typename std::enable_if<std::is_default_constructible<
         FunctionReturnType>::value, FunctionReturnType>::type PrivateNextReturnValue()
      {
         if (_returnValues.empty())
         {
            const FunctionReturnType defaultReturnValue{};
            return defaultReturnValue;
         }
         return NextReturnValue();
      }

      template<typename FunctionReturnType = ReturnType>
      typename std::enable_if<!std::is_default_constructible<
         FunctionReturnType>::value, FunctionReturnType>::type PrivateNextReturnValue()
      {
         if (_returnValues.empty())
         {
            throw ZenMock::ReturnValueMustBeSpecifiedException(ZenMockedFunctionSignature);
         }
         return NextReturnValue();
      }

      ReturnType NextReturnValue()
      {
         const DecayedReturnType& nextReturnValue =
            _returnValueIndex < _returnValues.size() ? _returnValues[_returnValueIndex++] : _returnValues.back();
         return nextReturnValue;
      }
   };
}
