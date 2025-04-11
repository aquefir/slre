/*
 * Copyright (C) 2004-2013 Sergey Lyubka <valenok@gmail.com>
 * Copyright (C) 2013 Cesanta Software Limited
 * Copyright (C) 2025 Aquefir Consulting LLC <//aquefir.co/>
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301 USA.
 */

/*
 * This is a regular expression library that implements a subset of Perl
 * RE. Please refer to README.md for a detailed reference.
 */

#ifndef INC_API__SLRE_H
#define INC_API__SLRE_H

#if !defined( __cplusplus )
#define SLRE_API extern
#else
#define SLRE_API extern "C"
#endif /* !defined( __cplusplus ) */

/* slre_match() failure codes */
#define SLRE_NO_MATCH ( -1 )
#define SLRE_UNEXPECTED_QUANTIFIER ( -2 )
#define SLRE_UNBALANCED_BRACKETS ( -3 )
#define SLRE_INTERNAL_ERROR ( -4 )
#define SLRE_INVALID_CHARACTER_SET ( -5 )
#define SLRE_INVALID_METACHARACTER ( -6 )
#define SLRE_CAPS_ARRAY_TOO_SMALL ( -7 )
#define SLRE_TOO_MANY_BRANCHES ( -8 )
#define SLRE_TOO_MANY_BRACKETS ( -9 )

struct slre_cap
{
	const char * ptr;
	int len;
};

SLRE_API int slre_match( const char * regexp,
	const char * buf,
	int buf_len,
	struct slre_cap * caps,
	int num_caps,
	int flags );

/* Possible flags for slre_match() */
enum
{
	SLRE_IGNORE_CASE = 1
};

#endif /* INC_API__SLRE_H */
