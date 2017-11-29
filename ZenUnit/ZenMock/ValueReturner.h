#pragma once
#include "ZenUnit/ZenMock/Exceptions/ReturnValueMustBeSpecifiedException.h"
#include <vector>

namespace ZenMock
{
   template<typename FunctionReturnType>
   class ValueReturner
   {
      friend class ValueReturnerTests;
   public:
      using DecayedFunctionReturnType = typename std::decay<FunctionReturnType>::type;
   private:
      const std::string _zenMockedFunctionSignature;
      std::vector<DecayedFunctionReturnType> _returnValues;
      size_t _returnValueIndex;
   public:
      explicit ValueReturner(std::string zenMockedFunctionSignature)
         : _zenMockedFunctionSignature(std::move(zenMockedFunctionSignature))
         , _returnValueIndex(0)
      {
      }

      template<typename ReturnType>
      void ZenMockAddReturnValue(ReturnType&& returnValue)
      {
         _returnValues.emplace_back(std::forward<ReturnType>(returnValue));
      }

      template<typename ReturnType, typename... ReturnTypes>
      void ZenMockAddReturnValues(ReturnType&& firstReturnValue, ReturnTypes&&... subsequentReturnValues)
      {
         ZenMockAddReturnValue(std::forward<ReturnType>(firstReturnValue));
         ZenMockAddReturnValues(std::forward<ReturnTypes>(subsequentReturnValues)...);
      }

      void ZenMockAddReturnValues()
      {
      }

      template<typename ContainerType>
      void ZenMockAddContainerReturnValues(ContainerType&& returnValues)
      {
         if (returnValues.empty())
         {
            throw std::invalid_argument(
               "ZenMock::ValueReturner::ZenMockAddContainerReturnValues(): Return values container cannot be empty.");
         }
         _returnValues.insert(_returnValues.end(), returnValues.cbegin(), returnValues.cend());
      }

      const DecayedFunctionReturnType& ZenMockNextReturnValue()
      {
         if (_returnValues.empty())
         {
            throw ZenMock::ReturnValueMustBeSpecifiedException(_zenMockedFunctionSignature);
         }
         const DecayedFunctionReturnType& nextReturnValue =
            _returnValueIndex < _returnValues.size() ? _returnValues[_returnValueIndex++] : _returnValues.back();
         return nextReturnValue;
      }
   };
}
