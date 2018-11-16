#include "basic_loop.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

#include "ProjectionCamera.h"

static const char* glsl_version = "#version 450 core";

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
	SDL_ShowCursor(SDL_DISABLE);
}


void BasicLoop::Init() {

}

void BasicLoop::Run() {
	SetState();
	Init();

	while (!done_) {
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

	ImGui::Begin("OpenGL Status");

	static int e = 1;
	if (ImGui::RadioButton("GL_LINE", &e, 0)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	ImGui::SameLine();
	if (ImGui::RadioButton("GL_FILL", &e, 1)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	ImGui::SameLine();

	ImGui::End();
}

void BasicLoop::LoadResource() {

}

void BasicLoop::ProsessEvent(SDL_Event event) {
	
}

void BasicLoop::KeyEvent() {
	
}
