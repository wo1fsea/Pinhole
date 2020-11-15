#include "pinhole.h"
#include <iostream>
#define GLM_FORCE_RADIANS 1

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glad/glad.h"

namespace pinhole {

static const int SCREEN_FULLSCREEN = 0;
static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;
static const char *WINDOW_CAPTION = "pinhole";

static SDL_Window *window = NULL;
static SDL_GLContext maincontext;

void print_sdl_error() {
  auto error_message = SDL_GetError();
  std::cout << error_message << std::endl;
}

void setup_sdl_gl() {
  // Request an OpenGL 4.5 context (should be core)
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

  // Also request a depth buffer
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  // Default OpenGL is fine.
  SDL_GL_LoadLibrary(NULL);
}

void print_sdl_info() {
  std::cout << "OpenGL loaded" << std::endl;
  std::cout << "Vendor:" << glGetString(GL_VENDOR) << std::endl;
  std::cout << "Renderer:" << glGetString(GL_RENDERER) << std::endl;
  std::cout << "Version:" << glGetString(GL_VERSION) << std::endl;
}

bool init() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    print_sdl_error();
    return false;
  }
  atexit(SDL_Quit);

  setup_sdl_gl();

  // Create the window
  if (SCREEN_FULLSCREEN) {
    window = SDL_CreateWindow(
        WINDOW_CAPTION, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0,
        SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL);
  } else {
    window = SDL_CreateWindow(WINDOW_CAPTION, SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
  }

  if (window == NULL) {
    print_sdl_error();
    return false;
  }

  maincontext = SDL_GL_CreateContext(window);
  if (maincontext == NULL) {
    print_sdl_error();
    return false;
  }

  gladLoadGLLoader(SDL_GL_GetProcAddress);

  // Check OpenGL properties
  print_sdl_info(); 

  // Use v-sync
  SDL_GL_SetSwapInterval(1);

  int w, h;
  SDL_GetWindowSize(window, &w, &h);
  glViewport(0, 0, w, h);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  return true;
}

void shutdown() {}

bool update() {
  SDL_Event event;
  SDL_PollEvent(&event);

  return event.type != SDL_QUIT;
}

void render_frame() { SDL_GL_SwapWindow(window); }

} // namespace pinhole
