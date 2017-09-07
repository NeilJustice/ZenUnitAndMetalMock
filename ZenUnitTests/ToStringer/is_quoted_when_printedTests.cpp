#include "pch.h"
#include "ZenUnit/ToStringer/is_quoted_when_printed.h"

static_assert(is_quoted_when_printed<char*>::value);
static_assert(is_quoted_when_printed<char* const>::value);
static_assert(is_quoted_when_printed<const char*>::value);
static_assert(is_quoted_when_printed<const char* const>::value);
static_assert(is_quoted_when_printed<string>::value);
static_assert(is_quoted_when_printed<string&>::value);
static_assert(is_quoted_when_printed<const string>::value);
static_assert(is_quoted_when_printed<const string&>::value);

static_assert(is_quoted_when_printed<char[1]>::value);
static_assert(is_quoted_when_printed<const char[1]>::value);

static_assert(!is_quoted_when_printed<int>::value);
static_assert(!is_quoted_when_printed<char>::value);
static_assert(!is_quoted_when_printed<exception>::value);
static_assert(!is_quoted_when_printed<UserType>::value);
static_assert(!is_quoted_when_printed<UserTypeNonPrintable>::value);
