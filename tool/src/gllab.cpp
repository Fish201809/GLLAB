#include "gllab.h"

void GLLab::RenderGL() {
	glClear(GL_DEPTH_BUFFER_BIT);
}

void GLLab::SetState() {
	glEnable(GL_DEPTH_TEST);
}
