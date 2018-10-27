#pragma once

// pxd: from libcpp cimport bool
#include <iostream>
#include <memory>
#include <stdexcept>
// pxd: from libcpp.string cimport string
#include <string>

class Error : public std::runtime_error
{
public:
	Error(const std::string &msg);

	/**
	 * The error message.
	 */
	std::string msg;

	/**
	 * Returns the message's content.
	 */
	const char *what() const noexcept override;
};

std::ostream &operator <<(std::ostream &os, const Error &e);
