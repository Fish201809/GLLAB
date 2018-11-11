
#include "gllab.h"

int main(int argc, char *argv[]) {
	try {
		GLLab basic_loop;
		basic_loop.Run();
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
	
	return 0;
}