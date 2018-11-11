#include "basic_loop.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

#include "ProjectionCamera.h"

static const char* glsl_version = "#version 130";

BasicLoop::BasicLoop() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
		printf("Error: %s\n", SDL_GetError());
	}
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	// Create window with graphics context
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_DisplayMode current;
	SDL_GetCurrentDisplayMode(0, &current);
	window_ = SDL_CreateWindow("Dear ImGui SDL2+OpenGL3 example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1400, 900, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    gl_context_ = SDL_GL_CreateContext(window_);
	SDL_GL_SetSwapInterval(1); // Enable vsync

	 // Initialize OpenGL loader
	gl3wInit();

	// Setup Dear ImGui binding
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

	ImGui_ImplSDL2_InitForOpenGL(window_, gl_context_);
	ImGui_ImplOpenGL3_Init(glsl_version);

	ImGui::StyleColorsDark();
	key_state_ = SDL_GetKeyboardState(nullptr);
	camera = std::make_shared<ProjectionCamera>();

}

BasicLoop::~BasicLoop() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(gl_context_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

void BasicLoop::SetState() {

}


void BasicLoop::Init() {

}

void BasicLoop::Run() {
	SetState();
	Init();
	while (!done_) {
		// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q)))
				done_ = true;
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window_))
				done_ = true;
			ProsessEvent(event);
		}
		KeyEvent();
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(window_);
		ImGui::NewFrame();
		RenderGui();
		ImGui::Render();

		SDL_GL_MakeCurrent(window_, gl_context_);
		glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
		glClearColor(clear_color_.x, clear_color_.y, clear_color_.z, clear_color_.w);
		glClear(GL_COLOR_BUFFER_BIT);
		
		RenderGL();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		SDL_GL_SwapWindow(window_);
	}
}

void BasicLoop::RenderGL() {

}

void BasicLoop::RenderGui() {
	//// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	/*if (show_demo_window_)
		ImGui::ShowDemoWindow(&show_demo_window_);
*/
	//// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	//{
	//	static float f = 0.0f;
	//	static int counter = 0;

	//	ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

	//	ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
	//	ImGui::Checkbox("Demo Window", &show_demo_window_);      // Edit bools storing our window open/close state
	//	ImGui::Checkbox("Another Window", &show_another_window_);

	//	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
	//	ImGui::ColorEdit3("clear color", (float*)&clear_color_); // Edit 3 floats representing a color

	//	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
	//		counter++;
	//	ImGui::SameLine();
	//	ImGui::Text("counter = %d", counter);

	//	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	//	ImGui::End();
	//}

	//// 3. Show another simple window.
	//if (show_another_window_) {
	//	ImGui::Begin("Another Window", &show_another_window_);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
	//	ImGui::Text("Hello from another window!");
	//	if (ImGui::Button("Close Me"))
	//		show_another_window_ = false;
	//	ImGui::End();
	//}
}

void BasicLoop::LoadResource() {

}

void BasicLoop::ProsessEvent(SDL_Event event) {
	if (event.type == SDL_MOUSEWHEEL) {

		float fov = camera->Fov();
		fov = fov + event.wheel.y;
		if (fov <= 1.0f)
			fov = 1.0f;
		if (fov >= 89.0f)
			fov = 89.0f;
		camera->Fov(fov);
	}

	if (event.type == SDL_MOUSEMOTION && event.motion.state == SDL_BUTTON_LEFT) {
		static float xoffset = 0.0f;
		static float yoffset = 0.0f;
		static float speed = 3.0f;
		xoffset -= event.motion.xrel * speed;
		yoffset += event.motion.yrel * speed;
		float pitch = glm::radians(yoffset);
		float yaw = glm::radians(xoffset);
		if (pitch > 89.0f) {
			pitch = 89.0f;
		}
		else if (pitch < -89.0f) {
			pitch = -89.0f;
		}
		camera->Pitch(pitch);
		camera->Yaw(yaw);
		camera->update_vector();
	}
}

void BasicLoop::KeyEvent() {
	glm::vec3 position = camera->World_position();
	glm::vec3 front = camera->Front();
	glm::vec3 right = camera->Right();
	if (key_state_[SDL_SCANCODE_W] == SDL_TRUE) {
		position -= 3.5f * front;
		camera->World_position(position);
	}
	if (key_state_[SDL_SCANCODE_S] == SDL_TRUE) {
		position += 3.5f * front;
		camera->World_position(position);
	}
	if (key_state_[SDL_SCANCODE_D] == SDL_TRUE) {
		position -= 3.5f * right;
		camera->World_position(position);
	}
	if (key_state_[SDL_SCANCODE_A] == SDL_TRUE) {
		position += 3.5f * right;
		camera->World_position(position);
	}
}
