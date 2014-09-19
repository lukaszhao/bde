// bslx_versionfunctions.h                                            -*-C++-*-
#ifndef INCLUDED_BSLX_VERSIONFUNCTIONS
#define INCLUDED_BSLX_VERSIONFUNCTIONS

#ifndef INCLUDED_BSLS_IDENT
#include <bsls_ident.h>
#endif
BSLS_IDENT("$Id: $")

//@PURPOSE: Provide functions to return BDEX version information for types.
//
//@CLASSES:
//  bslx::VersionFunctions: namespace for functions returning version numbers
//
//@DESCRIPTION: This component provides a namespace, 'bslx::VersionFunctions',
// that contains functions for determining the BDEX version number for types.
//
// This namespace defines the 'maxSupportedBdexVersion' function, which is
// overloaded to return a predetermined value, 'k_NO_VERSION', also defined in
// this namespace, for each of the fundamental types, 'enum' types, and
// 'bsl::string'.  For 'bsl::vector', the 'maxSupportedBdexVersion' function
// returns 1 if the vector is parameterized on one of the three types mentioned
// above.  Otherwise, the version number returned is the same as that returned
// for 'bsl::vector::value_type'.  For BDEX-compliant types, the function
// returns the BDEX version number returned by the 'maxSupportedBdexVersion'
// method provided by that type.
//
// In general, this component is used by higher-level 'bslx' components to
// query the version number for types.
//
///Usage
///-----
// This section illustrates intended use of this component.
//
///Example 1: Querying BDEX Version
///- - - - - - - - - - - - - - - -
// This component may be used by clients to query the version number for types
// in a convenient manner.  First, define an 'enum', 'my_Enum':
//..
//  enum my_Enum {
//      ENUM_VALUE1,
//      ENUM_VALUE2,
//      ENUM_VALUE3,
//      ENUM_VALUE4
//  };
//..
// Then, define a BDEX-compliant class, 'my_Class':
//..
//  class my_Class {
//    public:
//      enum {
//          VERSION = 1
//      };
//
//      // CLASS METHODS
//      static int maxSupportedBdexVersion(int) {
//          return VERSION;
//      }
//
//      //...
//
//  };
//..
// Finally, verify the value returned by 'maxSupportedBdexVersion' for some
// fundamental types, 'my_Enum', and 'my_Class' with an arbitrary
// 'serializationVersion':
//..
//  using bslx::VersionFunctions::maxSupportedBdexVersion;
//  using bslx::VersionFunctions::k_NO_VERSION;
//
//  assert(k_NO_VERSION ==
//      maxSupportedBdexVersion(reinterpret_cast<char        *>(0), 20131127));
//  assert(k_NO_VERSION ==
//      maxSupportedBdexVersion(reinterpret_cast<int         *>(0), 20131127));
//  assert(k_NO_VERSION ==
//      maxSupportedBdexVersion(reinterpret_cast<double      *>(0), 20131127));
//  assert(k_NO_VERSION ==
//      maxSupportedBdexVersion(reinterpret_cast<bsl::string *>(0), 20131127));
//
//  assert(k_NO_VERSION ==
//      maxSupportedBdexVersion(reinterpret_cast<my_Enum     *>(0), 20131127));
//
//  assert(my_Class::VERSION ==
//      maxSupportedBdexVersion(reinterpret_cast<my_Class    *>(0), 20131127));
//..

#ifndef INCLUDED_BSLSCM_VERSION
#include <bslscm_version.h>
#endif

#ifndef INCLUDED_BSLMF_IF
#include <bslmf_if.h>
#endif

#ifndef INCLUDED_BSLMF_ISENUM
#include <bslmf_isenum.h>
#endif

#ifndef INCLUDED_BSLMF_ISFUNDAMENTAL
#include <bslmf_isfundamental.h>
#endif

#ifndef INCLUDED_BSLMF_ISSAME
#include <bslmf_issame.h>
#endif

#ifndef INCLUDED_BSLMF_REMOVECV
#include <bslmf_removecv.h>
#endif

#ifndef INCLUDED_BSL_STRING
#include <bsl_string.h>
#endif

#ifndef INCLUDED_BSL_VECTOR
#include <bsl_vector.h>
#endif

namespace BloombergLP {
namespace bslx {

                 // =============================================
                 // class VersionFunctions_DoesNotHaveBdexVersion
                 // =============================================

class VersionFunctions_DoesNotHaveBdexVersion {
    // This class is used to perform function overload resolution for types
    // that do *not* have BDEX versions.  This class contains no interface or
    // implementation by design.
};

                 // =====================================
                 // class VersionFunctions_HasBdexVersion
                 // =====================================

class VersionFunctions_HasBdexVersion {
    // This class is used to perform function overload resolution for types
    // that *have* BDEX versions.  This class contains no interface or
    // implementation by design.
};

                 // ==========================================
                 // struct VersionFunctions_NonFundamentalImpl
                 // ==========================================

template <class TYPE>
struct VersionFunctions_NonFundamentalImpl {
    // This 'struct' provides a namespace for functions used to obtain the
    // BDEX-compliant version information for vectors and types requiring a
    // 'TYPE::maxSupportedBdexVersion' method as per the BDEX protocol (see the
    // 'bslx' package-level documentation).

    static int maxSupportedBdexVersion(int serializationVersion);
        // Return the BDEX-compliant version information for the (template
        // parameter) type 'TYPE' given the specified 'serializationVersion'
        // (see the 'bslx' package-level documentation).
};

template <class TYPE, class ALLOC>
struct VersionFunctions_NonFundamentalImpl<bsl::vector<TYPE, ALLOC> > {
    static int maxSupportedBdexVersion(int serializationVersion);
        // Return the BDEX-compliant version information for the (template
        // parameter) type 'bsl::vector<TYPE, ALLOC>' given the specified
        // 'serializationVersion' (see the 'bslx' package-level documentation).
};

                         // ===============================
                         // namespace VersionFunctions_Impl
                         // ===============================

namespace VersionFunctions_Impl {
    // This namespace contains functions that allow the computation of version
    // information for a (template parameter) type 'TYPE' as per the BDEX
    // protocol (see the 'bslx' package-level documentation).  These functions
    // presume that all 'const' and 'volatile' qualifiers have been stripped
    // from the (template parameter) 'TYPE'.

    // CLASS METHODS
    template <class TYPE>
    int maxSupportedBdexVersion(
                               int,
                               const VersionFunctions_DoesNotHaveBdexVersion&);
        // Return 'k_NO_VERSION'.  Note that this function is called only for
        // enumerations, fundamental types, and 'bsl::string', which do not
        // require versioning as per the BDEX protocol.

    template <class TYPE>
    int maxSupportedBdexVersion(
                   int                                    serializationVersion,
                   const VersionFunctions_HasBdexVersion&);
        // Return the version to use while streaming an object of the (template
        // parameter) type 'TYPE' with the specified 'serializationVersion' as
        // per the BDEX protocol (see the 'bslx' package-level documentation).
        // Note that this function assumes the 'TYPE' is neither 'const' nor
        // 'volatile' and that this function is called only for types which are
        // not enumerations, not fundamental types, and not 'bsl::string'
        // (vectors and other BDEX-compliant types will use this function).

    template <class TYPE>
    int maxSupportedBdexVersion(int serializationVersion);
        // Return the version to use while streaming an object of the (template
        // parameter) type 'TYPE' with the specified 'serializationVersion' as
        // per the BDEX protocol (see the 'bslx' package-level documentation).
        // Note that this function assumes the 'TYPE' is neither 'const' nor
        // 'volatile'.
};

                         // ==========================
                         // namespace VersionFunctions
                         // ==========================

namespace VersionFunctions {
    // This namespace contains functions that allow the computation of version
    // information for a (template parameter) type 'TYPE' as per the BDEX
    // protocol (see the 'bslx' package-level documentation).

    enum {
        k_NO_VERSION = -1  // Value to be used when there is no BDEX version.
    };

    // CLASS METHODS
    template <class TYPE>
    int maxSupportedBdexVersion(const TYPE *, int serializationVersion);
        // Return the version to use while streaming an object of the (template
        // parameter) type 'TYPE' with the specified 'serializationVersion' as
        // per the BDEX protocol (see the 'bslx' package-level documentation).
        // Note that this function ignores any 'const' and 'volatile'
        // qualifiers on the 'TYPE'.
};

// ============================================================================
//                      INLINE FUNCTION DEFINITIONS
// ============================================================================

                 // ------------------------------------------
                 // struct VersionFunctions_NonFundamentalImpl
                 // ------------------------------------------

// CLASS METHODS
template <class TYPE>
inline
int VersionFunctions_NonFundamentalImpl<TYPE>::
                              maxSupportedBdexVersion(int serializationVersion)
{
    // A compilation error indicating the next line of code implies the class
    // of 'TYPE' does not support the 'maxSupportedBdexVersion' method.

    return TYPE::maxSupportedBdexVersion(serializationVersion);
}

template <class TYPE, class ALLOC>
inline
int VersionFunctions_NonFundamentalImpl<bsl::vector<TYPE, ALLOC> >::
                              maxSupportedBdexVersion(int serializationVersion)
{
    using VersionFunctions::maxSupportedBdexVersion;

    const int version = maxSupportedBdexVersion(reinterpret_cast<TYPE *>(0),
                                                serializationVersion);

    return version != VersionFunctions::k_NO_VERSION ? version : 1;
}

                        // -------------------------------
                        // namespace VersionFunctions_Impl
                        // -------------------------------

template <class TYPE>
inline
int VersionFunctions_Impl::maxSupportedBdexVersion(
                                int,
                                const VersionFunctions_DoesNotHaveBdexVersion&)
{
    return VersionFunctions::k_NO_VERSION;
}

template <class TYPE>
inline
int VersionFunctions_Impl::maxSupportedBdexVersion(
                   int                                    serializationVersion,
                   const VersionFunctions_HasBdexVersion&)
{
    return VersionFunctions_NonFundamentalImpl<TYPE>::
                                 maxSupportedBdexVersion(serializationVersion);
}

template <class TYPE>
inline
int VersionFunctions_Impl::maxSupportedBdexVersion(int serializationVersion)
{
    typedef typename bslmf::If<bslmf::IsFundamental<TYPE>::value
                               || bslmf::IsEnum<TYPE>::value
                               || bsl::is_same<TYPE, bsl::string>::value,
                               VersionFunctions_DoesNotHaveBdexVersion,
                               VersionFunctions_HasBdexVersion>::Type
                                                                     dummyType;

    return VersionFunctions_Impl::
              maxSupportedBdexVersion<TYPE>(serializationVersion, dummyType());
}

                        // --------------------------
                        // namespace VersionFunctions
                        // --------------------------

template <class TYPE>
inline
int VersionFunctions::maxSupportedBdexVersion(const TYPE *,
                                              int         serializationVersion)
{
    return VersionFunctions_Impl::
                  maxSupportedBdexVersion<typename bsl::remove_cv<TYPE>::type>(
                                                         serializationVersion);
}

}  // close package namespace
}  // close enterprise namespace

#endif

// ----------------------------------------------------------------------------
// Copyright (C) 2013 Bloomberg Finance L.P.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------- END-OF-FILE ----------------------------------