#pragma once
#include <type_traits>

class Tuple
{
public:
   template<typename ClassType, typename MemberFunction, size_t I = 0ULL, typename... ArgTypes>
   static typename std::enable_if<I < sizeof...(ArgTypes)>::type
   Call1ArgMemberFunction(ClassType* classPtr, MemberFunction&& memberFunction, size_t argsIndex, const std::tuple<ArgTypes...>& args)
   {
      if (argsIndex == 0ULL)
      {
         (classPtr->*std::forward<MemberFunction>(memberFunction))(
            std::get<I>(args));
      }
      Call1ArgMemberFunction<ClassType, MemberFunction, I + 1ULL, ArgTypes...>(
         classPtr, std::forward<MemberFunction>(memberFunction), argsIndex - 1ULL, args);
   }

   template<typename ClassType, typename MemberFunction, size_t I = 0ULL, typename... ArgTypes>
   static typename std::enable_if<I < sizeof...(ArgTypes)>::type
   Call2ArgMemberFunction(ClassType* classPtr, MemberFunction&& memberFunction, size_t argsIndex, const std::tuple<ArgTypes...>& args)
   {
      if (argsIndex == 0ULL)
      {
         (classPtr->*std::forward<MemberFunction>(memberFunction))(
            std::get<I>(args),
            std::get<I + 1ULL>(args));
      }
      Call2ArgMemberFunction<ClassType, MemberFunction, I + 2ULL, ArgTypes...>(
         classPtr, std::forward<MemberFunction>(memberFunction), argsIndex - 2, args);
   }

   template<typename ClassType, typename MemberFunction, size_t I = 0ULL, typename... ArgTypes>
   static typename std::enable_if<I < sizeof...(ArgTypes)>::type
   Call3ArgMemberFunction(ClassType* classPtr, MemberFunction&& memberFunction, size_t argsIndex, const std::tuple<ArgTypes...>& args)
   {
      if (argsIndex == 0ULL)
      {
         (classPtr->*std::forward<MemberFunction>(memberFunction))(
            std::get<I>(args),
            std::get<I + 1ULL>(args),
            std::get<I + 2ULL>(args));
      }
      Call3ArgMemberFunction<ClassType, MemberFunction, I + 3ULL, ArgTypes...>(
         classPtr, std::forward<MemberFunction>(memberFunction), argsIndex - 3ULL, args);
   }

   template<typename ClassType, typename MemberFunction, size_t I = 0ULL, typename... ArgTypes>
   static typename std::enable_if<I < sizeof...(ArgTypes)>::type
   Call4ArgMemberFunction(ClassType* classPtr, MemberFunction&& memberFunction, size_t argsIndex, const std::tuple<ArgTypes...>& args)
   {
      if (argsIndex == 0ULL)
      {
         (classPtr->*std::forward<MemberFunction>(memberFunction))(
            std::get<I>(args),
            std::get<I + 1ULL>(args),
            std::get<I + 2ULL>(args),
            std::get<I + 3ULL>(args));
      }
      Call4ArgMemberFunction<ClassType, MemberFunction, I + 4ULL, ArgTypes...>(
         classPtr, std::forward<MemberFunction>(memberFunction), argsIndex - 4ULL, args);
   }

   template<typename ClassType, typename MemberFunction, size_t I = 0ULL, typename... ArgTypes>
   static typename std::enable_if<I < sizeof...(ArgTypes)>::type
   Call5ArgMemberFunction(ClassType* classPtr, MemberFunction&& memberFunction, size_t argsIndex, const std::tuple<ArgTypes...>& args)
   {
      if (argsIndex == 0ULL)
      {
         (classPtr->*std::forward<MemberFunction>(memberFunction))(
            std::get<I>(args),
            std::get<I + 1ULL>(args),
            std::get<I + 2ULL>(args),
            std::get<I + 3ULL>(args),
            std::get<I + 4ULL>(args));
      }
      Call5ArgMemberFunction<ClassType, MemberFunction, I + 5ULL, ArgTypes...>(
         classPtr, std::forward<MemberFunction>(memberFunction), argsIndex - 5ULL, args);
   }

   template<typename ClassType, typename MemberFunction, size_t I = 0ULL, typename... ArgTypes>
   static typename std::enable_if<I < sizeof...(ArgTypes)>::type
   Call6ArgMemberFunction(ClassType* classPtr, MemberFunction&& memberFunction, size_t argsIndex, const std::tuple<ArgTypes...>& args)
   {
      if (argsIndex == 0ULL)
      {
         (classPtr->*std::forward<MemberFunction>(memberFunction))(
            std::get<I>(args),
            std::get<I + 1ULL>(args),
            std::get<I + 2ULL>(args),
            std::get<I + 3ULL>(args),
            std::get<I + 4ULL>(args),
            std::get<I + 5ULL>(args));
      }
      Call6ArgMemberFunction<ClassType, MemberFunction, I + 6ULL, ArgTypes...>(
         classPtr, std::forward<MemberFunction>(memberFunction), argsIndex - 6ULL, args);
   }

   template<typename ClassType, typename MemberFunction, size_t I = 0ULL, typename... ArgTypes>
   static typename std::enable_if<I < sizeof...(ArgTypes)>::type
   Call7ArgMemberFunction(ClassType* classPtr, MemberFunction&& memberFunction, size_t argsIndex, const std::tuple<ArgTypes...>& args)
   {
      if (argsIndex == 0ULL)
      {
         (classPtr->*std::forward<MemberFunction>(memberFunction))(
            std::get<I>(args),
            std::get<I + 1ULL>(args),
            std::get<I + 2ULL>(args),
            std::get<I + 3ULL>(args),
            std::get<I + 4ULL>(args),
            std::get<I + 5ULL>(args),
            std::get<I + 6ULL>(args));
      }
      Call7ArgMemberFunction<ClassType, MemberFunction, I + 7ULL, ArgTypes...>(
         classPtr, std::forward<MemberFunction>(memberFunction), argsIndex - 7ULL, args);
   }

   template<typename ClassType, typename MemberFunction, size_t I = 0ULL, typename... ArgTypes>
   static typename std::enable_if<I < sizeof...(ArgTypes)>::type
   Call8ArgMemberFunction(ClassType* classPtr, MemberFunction&& memberFunction, size_t argsIndex, const std::tuple<ArgTypes...>& args)
   {
      if (argsIndex == 0ULL)
      {
         (classPtr->*std::forward<MemberFunction>(memberFunction))(
            std::get<I>(args),
            std::get<I + 1ULL>(args),
            std::get<I + 2ULL>(args),
            std::get<I + 3ULL>(args),
            std::get<I + 4ULL>(args),
            std::get<I + 5ULL>(args),
            std::get<I + 6ULL>(args),
            std::get<I + 7ULL>(args));
      }
      Call8ArgMemberFunction<ClassType, MemberFunction, I + 8ULL, ArgTypes...>(
         classPtr, std::forward<MemberFunction>(memberFunction), argsIndex - 8ULL, args);
   }

   template<typename ClassType, typename MemberFunction, size_t I = 0ULL, typename... ArgTypes>
   static typename std::enable_if<I < sizeof...(ArgTypes)>::type
   Call9ArgMemberFunction(ClassType* classPtr, MemberFunction&& memberFunction, size_t argsIndex, const std::tuple<ArgTypes...>& args)
   {
      if (argsIndex == 0ULL)
      {
         (classPtr->*std::forward<MemberFunction>(memberFunction))(
            std::get<I>(args),
            std::get<I + 1ULL>(args),
            std::get<I + 2ULL>(args),
            std::get<I + 3ULL>(args),
            std::get<I + 4ULL>(args),
            std::get<I + 5ULL>(args),
            std::get<I + 6ULL>(args),
            std::get<I + 7ULL>(args),
            std::get<I + 8ULL>(args));
      }
      Call9ArgMemberFunction<ClassType, MemberFunction, I + 9ULL, ArgTypes...>(
         classPtr, std::forward<MemberFunction>(memberFunction), argsIndex - 9ULL, args);
   }

   template<typename ClassType, typename MemberFunction, size_t I = 0ULL, typename... ArgTypes>
   static typename std::enable_if<I < sizeof...(ArgTypes)>::type
   Call10ArgMemberFunction(ClassType* classPtr, MemberFunction&& memberFunction, size_t argsIndex, const std::tuple<ArgTypes...>& args)
   {
      if (argsIndex == 0ULL)
      {
         (classPtr->*std::forward<MemberFunction>(memberFunction))(
            std::get<I>(args),
            std::get<I + 1ULL>(args),
            std::get<I + 2ULL>(args),
            std::get<I + 3ULL>(args),
            std::get<I + 4ULL>(args),
            std::get<I + 5ULL>(args),
            std::get<I + 6ULL>(args),
            std::get<I + 7ULL>(args),
            std::get<I + 8ULL>(args),
            std::get<I + 9ULL>(args));
      }
      Call10ArgMemberFunction<ClassType, MemberFunction, I + 10ULL, ArgTypes...>(
         classPtr, std::forward<MemberFunction>(memberFunction), argsIndex - 10ULL, args);
   }

   template<typename ClassType, typename MemberFunction, size_t I, typename... ArgTypes>
   static typename std::enable_if<I == sizeof...(ArgTypes), void>::type
   Call1ArgMemberFunction(ClassType*, MemberFunction&&, size_t, const std::tuple<ArgTypes...>&) {}

   template<typename ClassType, typename MemberFunction, size_t I, typename... ArgTypes>
   static typename std::enable_if<I == sizeof...(ArgTypes), void>::type
   Call2ArgMemberFunction(ClassType*, MemberFunction&&, size_t, const std::tuple<ArgTypes...>&) {}

   template<typename ClassType, typename MemberFunction, size_t I, typename... ArgTypes>
   static typename std::enable_if<I == sizeof...(ArgTypes), void>::type
   Call3ArgMemberFunction(ClassType*, MemberFunction&&, size_t, const std::tuple<ArgTypes...>&) {}

   template<typename ClassType, typename MemberFunction, size_t I, typename... ArgTypes>
   static typename std::enable_if<I == sizeof...(ArgTypes), void>::type
   Call4ArgMemberFunction(ClassType*, MemberFunction&&, size_t, const std::tuple<ArgTypes...>&) {}

   template<typename ClassType, typename MemberFunction, size_t I, typename... ArgTypes>
   static typename std::enable_if<I == sizeof...(ArgTypes), void>::type
   Call5ArgMemberFunction(ClassType*, MemberFunction&&, size_t, const std::tuple<ArgTypes...>&) {}

   template<typename ClassType, typename MemberFunction, size_t I, typename... ArgTypes>
   static typename std::enable_if<I == sizeof...(ArgTypes), void>::type
   Call6ArgMemberFunction(ClassType*, MemberFunction&&, size_t, const std::tuple<ArgTypes...>&) {}

   template<typename ClassType, typename MemberFunction, size_t I, typename... ArgTypes>
   static typename std::enable_if<I == sizeof...(ArgTypes), void>::type
   Call7ArgMemberFunction(ClassType*, MemberFunction&&, size_t, const std::tuple<ArgTypes...>&) {}

   template<typename ClassType, typename MemberFunction, size_t I, typename... ArgTypes>
   static typename std::enable_if<I == sizeof...(ArgTypes), void>::type
   Call8ArgMemberFunction(ClassType*, MemberFunction&&, size_t, const std::tuple<ArgTypes...>&) {}

   template<typename ClassType, typename MemberFunction, size_t I, typename... ArgTypes>
   static typename std::enable_if<I == sizeof...(ArgTypes), void>::type
   Call9ArgMemberFunction(ClassType*, MemberFunction&&, size_t, const std::tuple<ArgTypes...>&) {}

   template<typename ClassType, typename MemberFunction, size_t I, typename... ArgTypes>
   static typename std::enable_if<I == sizeof...(ArgTypes), void>::type
   Call10ArgMemberFunction(ClassType*, MemberFunction&&, size_t, const std::tuple<ArgTypes...>&) {}
};
