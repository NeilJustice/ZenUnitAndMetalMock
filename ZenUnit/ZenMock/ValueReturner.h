#pragma once
#include "ZenUnit/ZenMock/Exceptions/ReturnValueMustBeSpecifiedException.h"
#include <vector>

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
      explicit ValueReturner(std::string zenMockedFunctionSignature)
         : ZenMockedFunctionSignature(std::move(zenMockedFunctionSignature))
         , _returnValueIndex(0)
      {
      }

      template<typename ReturnTypeURef>
      void ZenMockAddReturnValue(ReturnTypeURef&& returnValue)
      {
         _returnValues.emplace_back(std::forward<ReturnTypeURef>(returnValue));
      }

      template<typename ReturnTypeURef, typename... ReturnTypeURefs>
      void ZenMockAddReturnValues(
         ReturnTypeURef&& firstReturnValue, ReturnTypeURefs&&... subsequentReturnValues)
      {
         ZenMockAddReturnValue(std::forward<ReturnTypeURef>(firstReturnValue));
         ZenMockAddReturnValues(std::forward<ReturnTypeURefs>(subsequentReturnValues)...);
      }
      void ZenMockAddReturnValues() {}

      template<typename ContainerType>
      void ZenMockAddContainerReturnValues(ContainerType&& returnValues)
      {
         if (returnValues.empty())
         {
            throw std::invalid_argument(
               "ZenMock::ValueReturner::ZenMockAddContainerReturnValues(): Return values vector cannot be empty");
         }
         _returnValues.insert(_returnValues.end(), returnValues.cbegin(), returnValues.cend());
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
         const DecayedReturnType& nextReturnValue =
            _returnValueIndex < _returnValues.size() ? _returnValues[_returnValueIndex++] : _returnValues.back();
         return nextReturnValue;
      }
   };
}
