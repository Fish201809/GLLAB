
#include "error.h"


constexpr const char *runtime_error_message = "polymorphic openage Error object; catch by reference!";

Error::Error(const std::string &msg) :std::runtime_error{ runtime_error_message }, msg(msg){

}

const char * Error::what() const noexcept {
	return msg.c_str();
}

std::ostream &operator <<(std::ostream &os, const Error &e) {
	
	
	if (! e.msg.empty()) {
		os << ": " << e.msg;
	}

	return os;
}

