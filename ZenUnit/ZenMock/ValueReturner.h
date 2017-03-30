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

      void ZenMockPushBackReturnValue(const ReturnType& returnValue)
      {
         _returnValues.push_back(returnValue);
      }

      template<typename FirstReturnValue, typename... SubsequentReturnValues>
      void ZenMockPushBackReturnValues(
         const FirstReturnValue& firstReturnValue,
         const SubsequentReturnValues&... subsequentReturnValues)
      {
         ZenMockPushBackReturnValue(firstReturnValue);
         ZenMockPushBackReturnValues(subsequentReturnValues...);
      }
      void ZenMockPushBackReturnValues() {}

      void ZenMockPushBackReturnValues(const std::vector<DecayedReturnType>& values)
      {
         if (values.empty())
         {
            throw std::invalid_argument(
               "ZenMock::ValueReturner::ZenMockPushBackReturnValues(): Return values vector cannot be empty");
         }
         _returnValues.insert(end(_returnValues), values.cbegin(), values.cend());
      }

      template<typename FunctionReturnType = ReturnType>
      typename std::enable_if<std::is_default_constructible<
         FunctionReturnType>::value, FunctionReturnType>::type ZenMockZenMockNextReturnValue()
      {
         if (_returnValues.empty())
         {
            const FunctionReturnType defaultReturnValue{};
            return defaultReturnValue;
         }
         return ZenMockNextReturnValue();
      }

      template<typename FunctionReturnType = ReturnType>
      typename std::enable_if<!std::is_default_constructible<
         FunctionReturnType>::value, FunctionReturnType>::type ZenMockZenMockNextReturnValue()
      {
         if (_returnValues.empty())
         {
            throw ZenMock::ReturnValueMustBeSpecifiedException(ZenMockedFunctionSignature);
         }
         return ZenMockNextReturnValue();
      }
   protected:
      ReturnType ZenMockNextReturnValue()
      {
         const DecayedReturnType& ZenMockNextReturnValue =
            _returnValueIndex < _returnValues.size() ? _returnValues[_returnValueIndex++] : _returnValues.back();
         return ZenMockNextReturnValue;
      }
   };
}
