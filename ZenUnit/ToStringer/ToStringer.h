#pragma once
#include "ZenUnit/ToStringer/SFINAE/has_ZenUnitPrinter.h"
#include "ZenUnit/ToStringer/SFINAE/has_ostream_left_shift.h"
#include "ZenUnit/ToStringer/SFINAE/has_to_string.h"
#include "ZenUnit/ToStringer/is_quoted_when_printed.h"
#include "ZenUnit/Utils/StringUtil.h"
#include "ZenUnit/Utils/Type.h"
#include <functional>

namespace ZenUnit
{
   class ToStringer
   {
   public:
      static std::string ToString(const std::nullptr_t&);
      static std::string ToString(const char* str);
      static std::string ToString(char* str);
      static std::string ToString(const bool& value);
      static std::string ToString(const char& value);
      static std::string CharPointerToString(const char* str);

      template<typename T>
      static typename std::enable_if<
         has_to_string<T>::value, std::string>::type
         ToString(const T& value)
      {
         const std::string valueString(std::to_string(value));
         return valueString;
      }

      template<typename T>
      static typename std::enable_if<
         !has_to_string<T>::value && !std::is_enum<T>::value, std::string>::type
         ToString(const T& value)
      {
         return DoToString(value);
      }

      template<typename T>
      static typename std::enable_if<
         !has_to_string<T>::value && std::is_enum<T>::value, std::string>::type
         ToString(const T& value)
      {
         const std::string valueString = std::to_string(
            static_cast<typename std::underlying_type<T>::type>(value));
         return valueString;
      }

      template<typename T>
      static std::string ToString(T* pointerAddress)
      {
         return PointerToAddressString(pointerAddress);
      }

      template<typename T, typename Deleter>
      static std::string ToString(const std::unique_ptr<T, Deleter>& uniquePtr)
      {
         return PointerToAddressString(uniquePtr.get());
      }

      template<typename T>
      static std::string ToString(const std::shared_ptr<T>& sharedPtr)
      {
         return PointerToAddressString(sharedPtr.get());
      }

      template<typename ReturnType, typename... ArgumentTypes>
      static std::string ToString(const std::function<ReturnType(ArgumentTypes...)> stdFunction)
      {
         if (stdFunction)
         {
            static const std::string NonEmptyStdFunction("<non-empty std::function>");
            return NonEmptyStdFunction;
         }
         static const std::string EmptyStdFunction("<empty std::function>");
         return EmptyStdFunction;
      }

      template<typename FirstType, typename SecondType>
      static std::string ToString(const std::pair<FirstType, SecondType>& p)
      {
         const std::string toStringedFirst = ToStringer::ToString(p.first);
         const std::string toStringedSecond = ToStringer::ToString(p.second);
         const std::string toStringedPair = String::Concat("(", toStringedFirst, ", ", toStringedSecond, ")");
         return toStringedPair;
      }

      template<typename... Types>
      static std::string ToStringConcat(Types&&... values)
      {
         std::ostringstream oss;
         DoToStringConcat(oss, std::forward<Types>(values)...);
         const std::string toStringedValues = oss.str();
         return toStringedValues;
      }

      static std::string ToStringConcat()
      {
         return std::string();
      }

      template<typename T, typename... Types>
      static void DoToStringConcat(std::ostringstream& oss, const T& value, Types&&... values)
      {
         oss << ToString(value);
         size_t numberOfRemainingValues = sizeof...(values);
         if (numberOfRemainingValues > 0)
         {
            oss << ", ";
         }
         DoToStringConcat(oss, std::forward<Types>(values)...);
      }

      static void DoToStringConcat(std::ostringstream&)
      {
      }

   private:
      template<typename T>
      static std::string DoToString(const T& value)
      {
         std::ostringstream oss;
         ZenUnitPrinterOrOStreamInsertionOperatorOrPrintTypeName(oss, value);
         const std::string valueString(oss.str());
         return valueString;
      }

      template<typename T>
      static typename std::enable_if<
         has_ZenUnitPrinter<T>::value && has_ostream_left_shift<T>::value>::type
         ZenUnitPrinterOrOStreamInsertionOperatorOrPrintTypeName(std::ostream& os, const T& value)
      {
         ::ZenUnitPrinter<T>::Print(os, value);
      }

      template<typename T>
      static typename std::enable_if<
         has_ZenUnitPrinter<T>::value && !has_ostream_left_shift<T>::value>::type
         ZenUnitPrinterOrOStreamInsertionOperatorOrPrintTypeName(std::ostream& os, const T& value)
      {
         ::ZenUnitPrinter<T>::Print(os, value);
      }

      template<typename T>
      static typename std::enable_if<
         !has_ZenUnitPrinter<T>::value && has_ostream_left_shift<T>::value>::type
         ZenUnitPrinterOrOStreamInsertionOperatorOrPrintTypeName(std::ostream& os, const T& value)
      {
         if (is_quoted_when_printed<T>::value)
         {
            os << '\"';
         }
         os << value;
         if (is_quoted_when_printed<T>::value)
         {
            os << '\"';
         }
      }

      template<typename T>
      static typename std::enable_if<
         !has_ZenUnitPrinter<T>::value && !has_ostream_left_shift<T>::value>::type
         ZenUnitPrinterOrOStreamInsertionOperatorOrPrintTypeName(std::ostream& os, const T&)
      {
         const std::string* const typeName = Type::GetName<T>();
         os << "<" << *typeName << ">";
      }

      template<typename T>
      static std::string PointerToAddressString(T* pointer)
      {
         if (pointer == nullptr)
         {
            return "nullptr";
         }
         std::ostringstream oss;
         // Clang and GCC ostringstream operator<< on a pointer results in "0x<PointerAddress>"
         // MSVC ostringstream operator<< on a pointer results in "<PointerAddress>"
#ifdef _WIN32
         oss << "0x";
#endif
         oss << pointer;
         const std::string pointerAddressString(oss.str());
         return pointerAddressString;
      }
   };
}
