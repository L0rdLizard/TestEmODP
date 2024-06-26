/*
 *   Copyright (c) 2015, Nokia Solutions and Networks
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the copyright holder nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 *
 * Event Machine HW specific functions and other additions.
 */

#ifndef EVENT_MACHINE_HW_SPECIFIC_H
#define EVENT_MACHINE_HW_SPECIFIC_H

#pragma GCC visibility push(default)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get the major event type.
 *
 * The event type includes a major and a minor part. This function returns the
 * major part. It can be compared against the enumeration em_event_type_major_e.
 *
 * @param type   Event type
 *
 * @return Major event type
 */
static inline em_event_type_t
em_event_type_major(em_event_type_t type)
{
	return type & 0xFF000000;
}

/* Backwards compatible naming */
#define em_get_type_major em_event_type_major

/**
 * Get the minor event type.
 *
 * The event type includes a major and a minor part. This function returns the
 * minor part. It can be compared against a type-specific minor enumeration.
 *
 * EM_EVENT_TYPE_SW_DEFAULT is reserved for (SW) events that are
 * generic and directly accessible buffers of memory.
 *
 * @param type          Event type
 *
 * @return Minor event type
 */
static inline em_event_type_t
em_event_type_minor(em_event_type_t type)
{
	return type & 0x00FFFFFF;
}

/* Backwards compatible naming */
#define em_get_type_minor em_event_type_minor

/*
 * Core mask manipulation functions
 */

/**
 * Zero the whole mask.
 *
 * @param[out] mask  Core mask to zero (clear)
 */
void em_core_mask_zero(em_core_mask_t *mask);

/**
 * Set a bit in the mask.
 *
 * @param      core  Core id
 * @param[out] mask  Core mask
 */
void em_core_mask_set(int core, em_core_mask_t *mask);

/**
 * Clear a bit in the mask.
 *
 * @param      core  Core id
 * @param[out] mask  Core mask
 */
void em_core_mask_clr(int core, em_core_mask_t *mask);

/**
 * Test if a bit is set in the mask.
 *
 * @param core  Core id
 * @param mask  Core mask
 *
 * @return Non-zero if core id is set in the mask
 */
int em_core_mask_isset(int core, const em_core_mask_t *mask);

/**
 * Test if the mask is all zero.
 *
 * @param mask  Core mask
 *
 * @return Non-zero if the mask is all zero
 */
int em_core_mask_iszero(const em_core_mask_t *mask);

/**
 * Test if two masks are equal
 *
 * @param mask1  First core mask
 * @param mask2  Second core mask
 *
 * @return Non-zero if the two masks are equal
 */
int em_core_mask_equal(const em_core_mask_t *mask1,
		       const em_core_mask_t *mask2);

/**
 * Set a range (0...count-1) of bits in the mask.
 *
 * @param      count  Number of bits to set
 * @param[out] mask   Core mask
 */
void em_core_mask_set_count(int count, em_core_mask_t *mask);

/**
 * Copy core mask
 *
 * @param[out] dst  Destination core mask
 * @param      src  Source core mask
 */
void em_core_mask_copy(em_core_mask_t *dst, const em_core_mask_t *src);

/**
 * Count the number of bits set in the mask.
 *
 * @param mask  Core mask
 *
 * @return Number of bits set
 */
int em_core_mask_count(const em_core_mask_t *mask);

/**
 * Set specified bits from 'bits[]' in core mask.
 *
 * core 0:  bits[0] = 0x1 (len = 1)
 * core 1:  bits[0] = 0x2 (len = 1)
 * ...
 * core 64: bits[0] = 0x0, bits[1] = 0x1 (len = 2)
 * core 65: bits[0] = 0x0, bits[1] = 0x2 (len = 2)
 * ...
 * cores 0-127: bits[0]=0xffffffffffffffff, bits[1]=0xffffffffffffffff (len=2)
 * ...
 * @param      bits  Array of uint64_t:s with the bits to set in the core mask
 * @param      len   Number of array elements in bits[].
 * @param[out] mask  Core mask to set.
 *
 * @note bits ar 'or'ed into mask, so any previously set bits will remain set.
 */
void em_core_mask_set_bits(const uint64_t bits[], int len,
			   em_core_mask_t *mask);

/**
 * Get core mask, stored in a uint64_t array for the user
 *
 * core 0:  bits[0] = 0x1 (len = 1)
 * core 1:  bits[0] = 0x2 (len = 1)
 * ...
 * core 64: bits[0] = 0x0, bits[1] = 0x1 (len = 2)
 * core 65: bits[0] = 0x0, bits[1] = 0x2 (len = 2)
 * ...
 * cores 0-127: bits[0]=0xffffffffffffffff, bits[1]=0xffffffffffffffff (len=2)
 * ...
 * @param[out] bits  Array of uint64_t:s that the core mask will be stored in.
 * @param      len   Number of array elements in bits[].
 * @param      mask  Core mask to get bits from.
 *
 * @return The number of uint64_t:s written into bits[].
 */
int em_core_mask_get_bits(uint64_t bits[/*out*/], int len,
			  const em_core_mask_t *mask);

/**
 * Set bits in a mask according to a given string.
 *
 * @param      mask_str  String containing '0xcoremask' to set
 * @param[out] mask      Core mask to set
 *
 * @return Zero (0) on success, non-zero on error.
 *
 * @note bits ar 'or'ed into mask, so any previously set bits will remain set.
 */
int em_core_mask_set_str(const char *mask_str, em_core_mask_t *mask);

/**
 * Get core mask in string format
 *
 * @param[out] mask_str  String into which the core mask will be printed
 * @param      len       Length of 'mask_str'
 * @param      mask      Core mask to convert to string format
 */
void em_core_mask_tostr(char *mask_str /*out*/, int len,
			const em_core_mask_t *mask);

/**
 * Return the index (position) of the Nth set bit in the core mask
 *
 * @param n     Nth set bit, note n=1 means first set bit, n=[1...MaxCores]
 * @param mask  Core mask
 *
 * @return  Index of the Nth set bit, <0 on error or if no such bit.
 */
int em_core_mask_idx(int n, const em_core_mask_t *mask);

/**
 * Bitwise AND operation on two masks, store the result in 'dst'
 *
 * dst = src1 & src2
 *
 * @param[out] dst   Destination core mask, result is stored here
 * @param      src1  Source mask #1
 * @param      src2  Source mask #2
 */
void em_core_mask_and(em_core_mask_t *dst, const em_core_mask_t *src1,
		      const em_core_mask_t *src2);

/**
 * Bitwise OR operation on two masks, store the result in 'dst'
 *
 * dst = src1 | src2
 *
 * @param[out] dst   Destination core mask, result is stored here
 * @param      src1  Source mask #1
 * @param      src2  Source mask #2
 */
void em_core_mask_or(em_core_mask_t *dst, const em_core_mask_t *src1,
		     const em_core_mask_t *src2);

/**
 * Bitwise XOR operation on two masks, store the result in 'dst'
 *
 * dst = src1 ^ src2
 *
 * @param[out] dst   Destination core mask, result is stored here
 * @param      src1  Source mask #1
 * @param      src2  Source mask #2
 */
void em_core_mask_xor(em_core_mask_t *dst, const em_core_mask_t *src1,
		      const em_core_mask_t *src2);

#ifdef __cplusplus
}
#endif

#pragma GCC visibility pop
#endif /* EVENT_MACHINE_HW_SPECIFIC_H */
