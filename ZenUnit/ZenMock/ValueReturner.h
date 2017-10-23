#pragma once
#include "ZenUnit/ZenMock/Exceptions/ReturnValueMustBeSpecifiedException.h"
#include <vector>

namespace ZenMock
{
   template<typename FunctionReturnType>
   class ValueReturner
   {
      friend class ValueReturnerTests;
   private:
      const std::string ZenMockedFunctionSignature;
      using DecayedReturnType = typename std::decay<FunctionReturnType>::type;
      std::vector<DecayedReturnType> _returnValues;
      size_t _returnValueIndex;
   public:
      explicit ValueReturner(std::string zenMockedFunctionSignature)
         : ZenMockedFunctionSignature(std::move(zenMockedFunctionSignature))
         , _returnValueIndex(0)
      {
      }

      template<typename ReturnType>
      void ZenMockAddReturnValue(ReturnType&& returnValue)
      {
         _returnValues.emplace_back(std::forward<ReturnType>(returnValue));
      }

      template<typename ReturnType, typename... ReturnTypeURefs>
      void ZenMockAddReturnValues(
         ReturnType&& firstReturnValue, ReturnTypeURefs&&... subsequentReturnValues)
      {
         ZenMockAddReturnValue(std::forward<ReturnType>(firstReturnValue));
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

      template<typename ReturnType = FunctionReturnType>
      typename std::enable_if<std::is_default_constructible<
         ReturnType>::value, ReturnType>::type ZenMockNextReturnValue()
      {
         if (_returnValues.empty())
         {
            const ReturnType defaultReturnValue{};
            return defaultReturnValue;
         }
         return DoZenMockNextReturnValue();
      }

      template<typename ReturnType = FunctionReturnType>
      typename std::enable_if<!std::is_default_constructible<
         ReturnType>::value, ReturnType>::type ZenMockNextReturnValue()
      {
         if (_returnValues.empty())
         {
            throw ZenMock::ReturnValueMustBeSpecifiedException(ZenMockedFunctionSignature);
         }
         return DoZenMockNextReturnValue();
      }
   protected:
      FunctionReturnType DoZenMockNextReturnValue()
      {
         const DecayedReturnType& nextReturnValue =
            _returnValueIndex < _returnValues.size() ? _returnValues[_returnValueIndex++] : _returnValues.back();
         return nextReturnValue;
      }
   };
}
