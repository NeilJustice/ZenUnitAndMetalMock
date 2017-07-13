#pragma once
#include <type_traits>

class Tuple
{
public:
   template<typename ClassType, typename MemberFunction, unsigned long long I = 0ull, typename... ArgTypes>
   static typename std::enable_if<I < sizeof...(ArgTypes)>::type
   Call1ArgMemberFunction(ClassType* classPtr, MemberFunction&& memberFunction, unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
   {
      if (argsIndex == 0ull)
      {
         (classPtr->*std::forward<MemberFunction>(memberFunction))(
            I + 1ull,
            std::get<I>(args));
      }
      Call1ArgMemberFunction<ClassType, MemberFunction, I + 1ull, ArgTypes...>(
         classPtr, std::forward<MemberFunction>(memberFunction), argsIndex - 1ull, args);
   }

   template<typename ClassType, typename MemberFunction, unsigned long long I = 0ull, typename... ArgTypes>
   static typename std::enable_if<I < sizeof...(ArgTypes)>::type
   Call2ArgMemberFunction(ClassType* classPtr, MemberFunction&& memberFunction, unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
   {
      if (argsIndex == 0ull)
      {
         (classPtr->*std::forward<MemberFunction>(memberFunction))(
            I / 2ull + 1ull,
            std::get<I>(args),
            std::get<I + 1ull>(args));
      }
      Call2ArgMemberFunction<ClassType, MemberFunction, I + 2ull, ArgTypes...>(
         classPtr, std::forward<MemberFunction>(memberFunction), argsIndex - 2, args);
   }

   template<typename ClassType, typename MemberFunction, unsigned long long I = 0ull, typename... ArgTypes>
   static typename std::enable_if<I < sizeof...(ArgTypes)>::type
   Call3ArgMemberFunction(ClassType* classPtr, MemberFunction&& memberFunction, unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
   {
      if (argsIndex == 0ull)
      {
         (classPtr->*std::forward<MemberFunction>(memberFunction))(
            I / 3ull + 1ull,
            std::get<I>(args),
            std::get<I + 1ull>(args),
            std::get<I + 2ull>(args));
      }
      Call3ArgMemberFunction<ClassType, MemberFunction, I + 3ull, ArgTypes...>(
         classPtr, std::forward<MemberFunction>(memberFunction), argsIndex - 3ull, args);
   }

   template<typename ClassType, typename MemberFunction, unsigned long long I = 0ull, typename... ArgTypes>
   static typename std::enable_if<I < sizeof...(ArgTypes)>::type
   Call4ArgMemberFunction(ClassType* classPtr, MemberFunction&& memberFunction, unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
   {
      if (argsIndex == 0ull)
      {
         (classPtr->*std::forward<MemberFunction>(memberFunction))(
            I / 4ull + 1ull,
            std::get<I>(args),
            std::get<I + 1ull>(args),
            std::get<I + 2ull>(args),
            std::get<I + 3ull>(args));
      }
      Call4ArgMemberFunction<ClassType, MemberFunction, I + 4ull, ArgTypes...>(
         classPtr, std::forward<MemberFunction>(memberFunction), argsIndex - 4ull, args);
   }

   template<typename ClassType, typename MemberFunction, unsigned long long I = 0ull, typename... ArgTypes>
   static typename std::enable_if<I < sizeof...(ArgTypes)>::type
   Call5ArgMemberFunction(ClassType* classPtr, MemberFunction&& memberFunction, unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
   {
      if (argsIndex == 0ull)
      {
         (classPtr->*std::forward<MemberFunction>(memberFunction))(
            I / 5ull + 1ull,
            std::get<I>(args),
            std::get<I + 1ull>(args),
            std::get<I + 2ull>(args),
            std::get<I + 3ull>(args),
            std::get<I + 4ull>(args));
      }
      Call5ArgMemberFunction<ClassType, MemberFunction, I + 5ull, ArgTypes...>(
         classPtr, std::forward<MemberFunction>(memberFunction), argsIndex - 5ull, args);
   }

   template<typename ClassType, typename MemberFunction, unsigned long long I = 0ull, typename... ArgTypes>
   static typename std::enable_if<I < sizeof...(ArgTypes)>::type
   Call6ArgMemberFunction(ClassType* classPtr, MemberFunction&& memberFunction, unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
   {
      if (argsIndex == 0ull)
      {
         (classPtr->*std::forward<MemberFunction>(memberFunction))(
            I / 6ull + 1ull,
            std::get<I>(args),
            std::get<I + 1ull>(args),
            std::get<I + 2ull>(args),
            std::get<I + 3ull>(args),
            std::get<I + 4ull>(args),
            std::get<I + 5ull>(args));
      }
      Call6ArgMemberFunction<ClassType, MemberFunction, I + 6ull, ArgTypes...>(
         classPtr, std::forward<MemberFunction>(memberFunction), argsIndex - 6ull, args);
   }

   template<typename ClassType, typename MemberFunction, unsigned long long I = 0ull, typename... ArgTypes>
   static typename std::enable_if<I < sizeof...(ArgTypes)>::type
   Call7ArgMemberFunction(ClassType* classPtr, MemberFunction&& memberFunction, unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
   {
      if (argsIndex == 0ull)
      {
         (classPtr->*std::forward<MemberFunction>(memberFunction))(
            I / 7ull + 1ull,
            std::get<I>(args),
            std::get<I + 1ull>(args),
            std::get<I + 2ull>(args),
            std::get<I + 3ull>(args),
            std::get<I + 4ull>(args),
            std::get<I + 5ull>(args),
            std::get<I + 6ull>(args));
      }
      Call7ArgMemberFunction<ClassType, MemberFunction, I + 7ull, ArgTypes...>(
         classPtr, std::forward<MemberFunction>(memberFunction), argsIndex - 7ull, args);
   }

   template<typename ClassType, typename MemberFunction, unsigned long long I = 0ull, typename... ArgTypes>
   static typename std::enable_if<I < sizeof...(ArgTypes)>::type
   Call8ArgMemberFunction(ClassType* classPtr, MemberFunction&& memberFunction, unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
   {
      if (argsIndex == 0ull)
      {
         (classPtr->*std::forward<MemberFunction>(memberFunction))(
            I / 8ull + 1ull,
            std::get<I>(args),
            std::get<I + 1ull>(args),
            std::get<I + 2ull>(args),
            std::get<I + 3ull>(args),
            std::get<I + 4ull>(args),
            std::get<I + 5ull>(args),
            std::get<I + 6ull>(args),
            std::get<I + 7ull>(args));
      }
      Call8ArgMemberFunction<ClassType, MemberFunction, I + 8ull, ArgTypes...>(
         classPtr, std::forward<MemberFunction>(memberFunction), argsIndex - 8ull, args);
   }

   template<typename ClassType, typename MemberFunction, unsigned long long I = 0ull, typename... ArgTypes>
   static typename std::enable_if<I < sizeof...(ArgTypes)>::type
   Call9ArgMemberFunction(ClassType* classPtr, MemberFunction&& memberFunction, unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
   {
      if (argsIndex == 0ull)
      {
         (classPtr->*std::forward<MemberFunction>(memberFunction))(
            I / 9ull + 1ull,
            std::get<I>(args),
            std::get<I + 1ull>(args),
            std::get<I + 2ull>(args),
            std::get<I + 3ull>(args),
            std::get<I + 4ull>(args),
            std::get<I + 5ull>(args),
            std::get<I + 6ull>(args),
            std::get<I + 7ull>(args),
            std::get<I + 8ull>(args));
      }
      Call9ArgMemberFunction<ClassType, MemberFunction, I + 9ull, ArgTypes...>(
         classPtr, std::forward<MemberFunction>(memberFunction), argsIndex - 9ull, args);
   }

   template<typename ClassType, typename MemberFunction, unsigned long long I = 0ull, typename... ArgTypes>
   static typename std::enable_if<I < sizeof...(ArgTypes)>::type
   Call10ArgMemberFunction(ClassType* classPtr, MemberFunction&& memberFunction, unsigned long long argsIndex, const std::tuple<ArgTypes...>& args)
   {
      if (argsIndex == 0ull)
      {
         (classPtr->*std::forward<MemberFunction>(memberFunction))(
            I / 10ull + 1ull,
            std::get<I>(args),
            std::get<I + 1ull>(args),
            std::get<I + 2ull>(args),
            std::get<I + 3ull>(args),
            std::get<I + 4ull>(args),
            std::get<I + 5ull>(args),
            std::get<I + 6ull>(args),
            std::get<I + 7ull>(args),
            std::get<I + 8ull>(args),
            std::get<I + 9ull>(args));
      }
      Call10ArgMemberFunction<ClassType, MemberFunction, I + 10ull, ArgTypes...>(
         classPtr, std::forward<MemberFunction>(memberFunction), argsIndex - 10ull, args);
   }

   template<typename ClassType, typename MemberFunction, unsigned long long I, typename... ArgTypes>
   static typename std::enable_if<I == sizeof...(ArgTypes), void>::type
   Call1ArgMemberFunction(ClassType*, MemberFunction&&, unsigned long long, const std::tuple<ArgTypes...>&) {}

   template<typename ClassType, typename MemberFunction, unsigned long long I, typename... ArgTypes>
   static typename std::enable_if<I == sizeof...(ArgTypes), void>::type
   Call2ArgMemberFunction(ClassType*, MemberFunction&&, unsigned long long, const std::tuple<ArgTypes...>&) {}

   template<typename ClassType, typename MemberFunction, unsigned long long I, typename... ArgTypes>
   static typename std::enable_if<I == sizeof...(ArgTypes), void>::type
   Call3ArgMemberFunction(ClassType*, MemberFunction&&, unsigned long long, const std::tuple<ArgTypes...>&) {}

   template<typename ClassType, typename MemberFunction, unsigned long long I, typename... ArgTypes>
   static typename std::enable_if<I == sizeof...(ArgTypes), void>::type
   Call4ArgMemberFunction(ClassType*, MemberFunction&&, unsigned long long, const std::tuple<ArgTypes...>&) {}

   template<typename ClassType, typename MemberFunction, unsigned long long I, typename... ArgTypes>
   static typename std::enable_if<I == sizeof...(ArgTypes), void>::type
   Call5ArgMemberFunction(ClassType*, MemberFunction&&, unsigned long long, const std::tuple<ArgTypes...>&) {}

   template<typename ClassType, typename MemberFunction, unsigned long long I, typename... ArgTypes>
   static typename std::enable_if<I == sizeof...(ArgTypes), void>::type
   Call6ArgMemberFunction(ClassType*, MemberFunction&&, unsigned long long, const std::tuple<ArgTypes...>&) {}

   template<typename ClassType, typename MemberFunction, unsigned long long I, typename... ArgTypes>
   static typename std::enable_if<I == sizeof...(ArgTypes), void>::type
   Call7ArgMemberFunction(ClassType*, MemberFunction&&, unsigned long long, const std::tuple<ArgTypes...>&) {}

   template<typename ClassType, typename MemberFunction, unsigned long long I, typename... ArgTypes>
   static typename std::enable_if<I == sizeof...(ArgTypes), void>::type
   Call8ArgMemberFunction(ClassType*, MemberFunction&&, unsigned long long, const std::tuple<ArgTypes...>&) {}

   template<typename ClassType, typename MemberFunction, unsigned long long I, typename... ArgTypes>
   static typename std::enable_if<I == sizeof...(ArgTypes), void>::type
   Call9ArgMemberFunction(ClassType*, MemberFunction&&, unsigned long long, const std::tuple<ArgTypes...>&) {}

   template<typename ClassType, typename MemberFunction, unsigned long long I, typename... ArgTypes>
   static typename std::enable_if<I == sizeof...(ArgTypes), void>::type
   Call10ArgMemberFunction(ClassType*, MemberFunction&&, unsigned long long, const std::tuple<ArgTypes...>&) {}
};
