

//  (C) Copyright Boost.org 2001. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version.

//  Comeau C++ compiler setup:

/* 
 * @$Id$ 
 */

#include "ambulant/config/compiler/common_edg.h"

#if (__COMO_VERSION__ <= 4245) || !defined(AMBULANT_STRICT_CONFIG)
#  if defined(_MSC_VER) && _MSC_VER <= 1300
#     define AMBULANT_NO_STDC_NAMESPACE
#     define AMBULANT_NO_SWPRINTF
#     if _MSC_VER > 100
         // only set this in non-strict mode:
#        define AMBULANT_NO_ARGUMENT_DEPENDENT_LOOKUP
#     endif
#  endif

// Void returns don't work when emulating VC 6 (Peter Dimov)

#  if defined(_MSC_VER) && (_MSC_VER == 1200)
#     define AMBULANT_NO_VOID_RETURNS
#  endif


#endif  // version 4245

//
// enable __int64 support in VC emulation mode
// we should also set AMBULANT_HAS_LONG_LONG when that is
// supported, but there is no way we can detect it:
//
#  if defined(_MSC_VER) && (_MSC_VER >= 1200)
#     define AMBULANT_HAS_MS_INT64
#  endif

//
// disable win32 support unless we are in VC emulation mode,
// (what does this do to Como on top of Borland?):
//
#if defined(_WIN32) && (_MSC_VER+0 < 1000)
#  define AMBULANT_DISABLE_WIN32
#endif

#define AMBULANT_COMPILER "Comeau compiler version " AMBULANT_STRINGIZE(__COMO_VERSION__)

//
// versions check:
// we don't know Comeau prior to version 4245:
#if __COMO_VERSION__ < 4245
#  error "Compiler not configured - please reconfigure"
#endif
//
// last known and checked version is 4245:
#if (__COMO_VERSION__ > 4245)
#  if defined(AMBULANT_ASSERT_CONFIG)
#     error "Unknown compiler version - please run the configure tests and report the results"
#  endif
#endif



