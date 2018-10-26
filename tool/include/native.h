#pragma once

#include <fstream>
#include <iostream>
#include <memory>
#include <string>


#if defined(_MSC_VER)
#ifndef HAVE_SSIZE_T
// ssize_t is defined the same as Python's definition it in pyconfig.h.
// This is necessary to facilitate the build and link procedure using MSVC.
#ifdef _WIN64
typedef __int64 ssize_t;
#else
typedef int ssize_t;
#endif
#define HAVE_SSIZE_T 1
#endif // HAVE_SSIZE_T
#endif // _MSC_VER

#ifndef _ISO646
#define _ISO646
#ifndef RC_INVOKED

#if !defined(__cplusplus) || defined(_MSC_EXTENSIONS)
#define and	&&
#define and_eq	&=
#define bitand	&
#define bitor	|
#define compl	~
#define not	!
#define not_eq	!=
#define or		||
#define or_eq	|=
#define xor	^
#define xor_eq	^=
#endif /* !defined(__cplusplus) || defined(_MSC_EXTENSIONS) */
#endif /* RC_INVOKED */
#endif /* _ISO646 */


/**
 * File-like class that uses native stdlib functions to access data.
 */
class Native
{
	
	enum class seek_t : int
	{
		SET = 0,  //!< offset from file beginning
		CUR = 1,  //!< offset from current position
		END = 2   //!< offset from file end
	};

	/**
	 * File access mode.
	 *
	 * Sync the numbers with the fslike/cpp.pyx
	 * because Cython can't enum class yet.
	 * TODO: once cython can handle enum class, add pxd annotation.
	 */
	enum class mode_t : int
	{
		R = 0,
		W = 1,
		RW = 2,
		A = 3,
		AR = 4,
	};
public:
	Native(const std::string &path, mode_t mode = mode_t::R);
	virtual ~Native();

	std::string read(ssize_t max = -1);
	size_t read_to(void *buf, ssize_t max);

	bool readable();

	void write(const std::string &data);

	bool writable();

	void seek(ssize_t offset, seek_t how = seek_t::SET);
	bool seekable();
	size_t tell();
	void close();
	void flush();
	ssize_t get_size();

	std::ostream &repr(std::ostream &);

protected:
	std::string path;

	mode_t mode;

	std::fstream file;
};