# SLRE: Super Light Regular Expressions

SLRE is an ANSI C library that implements a subset of Perl&rsquo;
regular expression syntax. The main features of SLRE are:

* Written in strict ANSI C (C89)
* Small size (compiled x86 code is about 5kB)
* Uses little stack space and does no dynamic memory allocation
* Provides a simple and intuitive API
* Implements most useful subset of Perl regex syntax (see below)
* Easily extensible; e.g. if one wants to introduce a new metacharacter
  `\i`, meaning "IPv4 address", it is easy to do so with SLRE.

SLRE is perfect for tasks like parsing network requests, configuration
files, user input, etc, when libraries like [PCRE](http://pcre.org) are
too heavyweight for the given task. Developers of embedded systems would
benefit most.

## Supported syntax

 `expr`  | Description
---------+--------------------------------------------------------------
`^`      | Match beginning of a buffer
`$`      | Match end of a buffer
`()`     | Grouping and substring capturing
`\s`     | Match whitespace
`\S`     | Match non-whitespace
`\d`     | Match decimal digit
`\n`     | Match new line character
`\r`     | Match line feed character
`\f`     | Match form feed character
`\v`     | Match vertical tab character
`\t`     | Match horizontal tab character
`\b`     | Match backspace character
`+`      | Match one or more times (greedy)
`+?`     | Match one or more times (non-greedy)
`*`      | Match zero or more times (greedy)
`*?`     | Match zero or more times (non-greedy)
`?`      | Match zero or once (non-greedy)
`x|y`    | Match x or y (alternation operator)
`\meta`  | Match one of the meta character: ^$().[]*+?|\
`\xHH`   | Match byte with hex value 0xHH, e.g. \x4a
`[...]`  | Match any character from set. Ranges like `[a-z]` work
`[^...]` | Match any character but ones from set

Unicode support is still under development.

## API

```c
int slre_match(
	const char * regexp,
	const char * buf,
	int buf_len,
	struct slre_cap * caps,
	int num_caps,
	int flags );
```

`slre_match()` matches string buffer `buf` of length `buf_len` against
regular expression `regexp`, which should conform the syntax outlined
above. If regular expression `regexp` contains brackets, `slre_match()`
can capture the respective substrings into the array of
`struct slre_cap` structures:

```c
/* Stores matched fragment for the expression inside brackets */
struct slre_cap
{
	const char * ptr;  /* Points to the matched fragment */
	int len;          /* Length of the matched fragment */
};
```

N-th member of the `caps` array will contain fragment that corresponds
to the N-th opening bracket in the `regex`, N is zero-based.
`slre_match()` returns number of bytes scanned from the beginning of the
string. If return value is greater or equal to 0, there is a match. If
return value is less then 0, there is no match. Negative return codes
are as follows:

```c
#define SLRE_NO_MATCH               ( -1 )
#define SLRE_UNEXPECTED_QUANTIFIER  ( -2 )
#define SLRE_UNBALANCED_BRACKETS    ( -3 )
#define SLRE_INTERNAL_ERROR         ( -4 )
#define SLRE_INVALID_CHARACTER_SET  ( -5 )
#define SLRE_INVALID_METACHARACTER  ( -6 )
#define SLRE_CAPS_ARRAY_TOO_SMALL   ( -7 )
#define SLRE_TOO_MANY_BRANCHES      ( -8 )
#define SLRE_TOO_MANY_BRACKETS      ( -9 )
```

Valid flags are:

- `SLRE_IGNORE_CASE`: do case-insensitive match

### Example 1: parsing HTTP request line

```c
const char * const request = " GET /index.html HTTP/1.0\r\n\r\n";
struct slre_cap caps[4];
const int r = slre_match( "^\\s*(\\S+)\\s+(\\S+)\\s+HTTP/(\\d)\\.(\\d)",
                         request, strlen(request), caps, 4, 0 );

if( r > 0 )
{
	printf("Method: [%.*s], URI: [%.*s]\n",
	       caps[0].len, caps[0].ptr,
	       caps[1].len, caps[1].ptr);
}
else
{
	printf("Error parsing [%s]\n", request);
}
```

### Example 2: find all URLs in a string

```c
#define STR "<img src=\"HTTPS://FOO.COM/x?b#c=tab1\"/>"
"<a href=\"http://example.com\">some link</a>"
const char * const str = STR;
const int str_len = sizeof( STR );

const char * const regex = "((https?://)[^\\s/'\"<>]+/?[^\\s'\"<>]*)";
struct slre_cap caps[2];
int i, j;

for(i = 0, j = 0; j < str_len; j += i)
{
	i = slre_match( regex, str + j, str_len - j, caps, 2,
	                SLRE_IGNORE_CASE );

	if( i > 0 )
	{
		printf( "Found URL: [%.*s]\n", caps[0].len, caps[0].ptr );
	}
}
```

Output:

```
Found URL: [HTTPS://FOO.COM/x?b#c=tab1]
Found URL: [http://example.com]
```

## Contributing and copyright

The SLRE is licenced under the GNU General Public License, version 2.
By submitting your changes for inclusion in this project, you agree to
licence your work under these terms. The terms can be found in the
`COPYING` file of this repository, or alternatively on the Web at
<https://www.gnu.org/licenses/gpl-2.0.html>.
