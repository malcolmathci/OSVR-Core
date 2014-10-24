/** @file
    @brief Header defining a dependency-free, cross-platform substitute for
   struct timeval

    Must be c-safe!

    @date 2014

    @author
    Ryan Pavlik
    <ryan@sensics.com>;
    <http://sensics.com>
*/

/*
// Copyright 2014 Sensics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// 	http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
*/

#ifndef INCLUDED_TimeValueC_h_GUID_A02C6917_124D_4CB3_E63E_07F2DA7144E9
#define INCLUDED_TimeValueC_h_GUID_A02C6917_124D_4CB3_E63E_07F2DA7144E9

/* Internal Includes */
#include <ogvr/Util/Export.h>
#include <ogvr/Util/PlatformConfig.h>

/* Library/third-party includes */
/* none */

/* Standard includes */
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
/** @defgroup C API for time interaction.

    This provides a level of interoperability with struct timeval on systems
   with that facility. It provides a neutral representation with sufficiently
   large types.

    For C++ code, use of boost::chrono instead is recommended.

    @{
*/

/** @brief The signed integer type storing the seconds in a struct
 * OGVR_TimeValue */
typedef int64_t OGVR_TimeValue_Seconds;
/** @brief The signed integer type storing the microseconds in a struct
 * OGVR_TimeValue */
typedef int32_t OGVR_TimeValue_Microseconds;

/** @brief Standardized, portable parallel to struct timeval for representing
   both absolute times and time intervals.

   Where interpreted as an absolute time, its meaning is to be considered the
   same as that of the POSIX struct timeval:
   time since 00:00 Coordinated Universal Time (UTC), January 1, 1970.

   For best results, please keep normalized. Output of all functions here
   is normalized.
   */
struct OGVR_TimeValue {
    /** @brief Seconds portion of the time value. */
    OGVR_TimeValue_Seconds seconds;
    /** @brief Microseconds portion of the time value. */
    OGVR_TimeValue_Microseconds microseconds;
};

#ifdef OGVR_HAVE_STRUCT_TIMEVAL
struct timeval; /* forward declaration */

/** @brief Converts from a TimeValue struct to your system's struct timeval.

    @param dest Pointer to an empty struct timeval for your platform.
    @param src A pointer to an OGVR_TimeValue you'd like to convert from.

    If either parameter is NULL, the function will return without doing
   anything.
*/
OGVR_UTIL_EXPORT void
ogvrTimeValueToStructTimeval(struct timeval *dest,
                             const struct OGVR_TimeValue *src);

/** @brief Converts from a TimeValue struct to your system's struct timeval.
    @param dest An OGVR_TimeValue destination pointer.
    @param src Pointer to a struct timeval you'd like to convert from.

    The result is normalized.

    If either parameter is NULL, the function will return without doing
   anything.
*/
OGVR_UTIL_EXPORT void ogvrStructTimevalToTimeValue(struct OGVR_TimeValue *dest,
                                                   const struct timeval *src);
#endif

/** @brief "Normalizes" a time value so that the absolute number of microseconds
    is less than 1,000,000, and that the sign of both components is the same.

    @param tv Address of a struct TimeValue to normalize in place.

    If the given pointer is NULL, this function returns without doing anything.
*/
OGVR_UTIL_EXPORT void ogvrTimeValueNormalize(struct OGVR_TimeValue *tv);

/** @brief Sums two time values, replacing the first with the result.

    @param tvA Destination and first source.
    @param tvB second source

    If a given pointer is NULL, this function returns without doing anything.

    Both parameters are expected to be in normalized form.
*/
OGVR_UTIL_EXPORT void ogvrTimeValueSum(struct OGVR_TimeValue *tvA,
                                       const struct OGVR_TimeValue *tvB);

/** @brief Computes the difference between two time values, replacing the first
   with the result.

    Effectively, `*tvA = *tvA - *tvB`

    @param tvA Destination and first source.
    @param tvB second source

    If a given pointer is NULL, this function returns without doing anything.

    Both parameters are expected to be in normalized form.
*/
OGVR_UTIL_EXPORT void ogvrTimeValueDifference(struct OGVR_TimeValue *tvA,
                                              const struct OGVR_TimeValue *tvB);

/** @} */

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif
