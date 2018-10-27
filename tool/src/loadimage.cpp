#include "loadimage.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "filesystem.h"

unsigned char* load_image(std::string name, int &width, int &height, int &channel) {
	std::string fname = FileSystem::getPath(name.c_str());
	return stbi_load(fname.c_str(), &width, &height, &channel, 0);
}
