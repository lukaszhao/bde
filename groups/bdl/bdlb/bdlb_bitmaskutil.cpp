// bdlb_bitmaskutil.cpp                                               -*-C++-*-
#include <bdlb_bitmaskutil.h>

#include <bsls_ident.h>
BSLS_IDENT_RCSID(bdlb_bitutil_cpp,"$Id$ $CSID$")

#include <bslmf_assert.h>

namespace BloombergLP {
namespace bdlb {

BSLMF_ASSERT(4 == sizeof(BitMaskUtil::uint32_t));
BSLMF_ASSERT(8 == sizeof(BitMaskUtil::uint64_t));

}  // close package namespace
}  // close enterprise namespace

// ----------------------------------------------------------------------------
// Copyright 2015 Bloomberg Finance L.P.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ----------------------------- END-OF-FILE ----------------------------------
