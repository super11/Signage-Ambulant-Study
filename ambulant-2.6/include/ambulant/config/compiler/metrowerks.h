

//  (C) Copyright Boost.org 2001. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version.

/* 
 * @$Id$ 
 */

//  Metrowerks C++ compiler setup:

// locale support is disabled when linking with the dynamic runtime
#   ifdef _MSL_NO_LOCALE
#     define AMBULANT_NO_STD_LOCALE
#   endif 

#   if __MWERKS__ <= 0x2301  // 5.3
#     define AMBULANT_NO_FUNCTION_TEMPLATE_ORDERING
#     define AMBULANT_NO_POINTER_TO_MEMBER_CONST
#     define AMBULANT_NO_DEPENDENT_TYPES_IN_TEMPLATE_VALUE_PARAMETERS
#     define AMBULANT_NO_MEMBER_TEMPLATE_KEYWORD
#   endif

#   if __MWERKS__ <= 0x2401  // 6.2
//#     define AMBULANT_NO_FUNCTION_TEMPLATE_ORDERING
#   endif

#   if(__MWERKS__ <= 0x2407)  // 7.x
#     define AMBULANT_NO_MEMBER_FUNCTION_SPECIALIZATIONS
#     define AMBULANT_NO_UNREACHABLE_RETURN_DETECTION
#   endif

#   if(__MWERKS__ <= 0x3003)  // 8.x
#     define AMBULANT_NO_MEMBER_TEMPLATE_FRIENDS
#    endif

#if !__option(wchar_type)
#   define AMBULANT_NO_INTRINSIC_WCHAR_T
#endif

#if !__option(exceptions)
#   define AMBULANT_NO_EXCEPTIONS
#endif

#   if __MWERKS__ == 0x3000
#     define AMBULANT_COMPILER_VERSION 8.0
#   elif __MWERKS__ == 0x3001
#     define AMBULANT_COMPILER_VERSION 8.1
#   elif __MWERKS__ == 0x3002
#     define AMBULANT_COMPILER_VERSION 8.2
#   elif __MWERKS__ == 0x3003
#     define AMBULANT_COMPILER_VERSION 8.3
#   else
#     define AMBULANT_COMPILER_VERSION __MWERKS__
#   endif 

#define AMBULANT_COMPILER "Metrowerks CodeWarrior C++ version " AMBULANT_STRINGIZE(AMBULANT_COMPILER_VERSION)

//
// versions check:
// we don't support Metrowerks prior to version 5.3:
#if __MWERKS__ < 0x2301
#  error "Compiler not supported or configured - please reconfigure"
#endif
//
// last known and checked version:
#if (__MWERKS__ > 0x3003)
#  if defined(AMBULANT_ASSERT_CONFIG)
#     error "Unknown compiler version - please run the configure tests and report the results"
#  endif
#endif






