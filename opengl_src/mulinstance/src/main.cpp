#include "tool.h"

class ElementSphere : public ExampleTemplate
{
public:
	ElementSphere() {
		plane = std::make_shared<Plane>();
		cube_ = std::make_shared<Cube>();
	}
	virtual void display() override {
		plane->display();
		cube_->display();
	}

	virtual void init() override {
		plane->init();
		cube_->init();
	}

	std::shared_ptr<Plane> plane;
	std::shared_ptr<Cube> cube_;

	virtual void set_state() override {
		glEnable(GL_DEPTH_TEST);
	}
};

int main(int agrc, char *argv[]) {
	ElementSphere e;
	e.run();

	return 0;
}