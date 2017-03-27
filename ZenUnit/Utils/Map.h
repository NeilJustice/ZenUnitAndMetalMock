#pragma once
#include "ZenUnit/ToStringer/ToStringer.h"
#include "ZenUnit/Macros/ARE_EQUAL.h"

namespace ZenUnit
{
   class Map
   {
   public:
      template<typename MapType, typename KeyType, typename ValueType>
      static const ValueType* InsertNoOverwrite(
         MapType& m, const KeyType& key, const ValueType& value)
      {
         const std::pair<typename MapType::const_iterator, bool> insertIterAndDidInsert
            = m.insert(std::make_pair(key, value));
         if (!insertIterAndDidInsert.second)
         {
            InsertNoOverwrite_Throw(key);
         }
         const ValueType* const constPointerToValueInMap = &(*insertIterAndDidInsert.first).second;
         return constPointerToValueInMap;
      }

      // This At() exists because regular map.at() does not include the key not found in the exception what() text
      template<
         template<typename...>
         class MapType, typename KeyType, typename ValueType, typename... SubsequentTypes>
      static const ValueType& At(
         const MapType<KeyType, ValueType, SubsequentTypes...>& m, const KeyType& key)
      {
         try
         {
            const ValueType& constReferenceToValueInMap = m.at(key);
            return constReferenceToValueInMap;
         }
         catch (const std::out_of_range&)
         {
            At_Throw(key);
         }
      }

      template<typename MapType, typename KeyType, typename ValueType>
      static std::pair<bool, bool> ContainsKeyWithValue(
         const MapType& m, const KeyType& key, const ValueType& value)
      {
         const typename MapType::const_iterator findIter = m.find(key);
         if (findIter == m.end())
         {
            return { false, false };
         }
         else
         {
            try
            {
               ARE_EQUAL(value, findIter->second);
            }
            catch (const Anomaly&)
            {
               return { true, false };
            }
            return { true, true };
         }
      }

   private:
      template<typename KeyType>
      [[noreturn]] static NOINLINE void At_Throw(const KeyType& key)
      {
         const std::string toStringedKey = ToStringer::ToString(key);
         const std::string what = String::Concat("ZenUnit::Map::At: Key not found in map: ", toStringedKey);
         throw std::out_of_range(what);
      }

      template<typename KeyType>
      static NOINLINE void InsertNoOverwrite_Throw(const KeyType& key)
      {
         const std::string toStringedKey = ToStringer::ToString(key);
         const std::string what = String::Concat(
            "ZenUnit::Map::InsertNoOverwrite: Key already present in map: ", toStringedKey);
         throw std::invalid_argument(what);
      }
   };
}
