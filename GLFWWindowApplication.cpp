/*
 * TestVulkanApp.cpp
 *
 *  Created on: 25 mars 2018
 *      Author: Vi4nde
 */

#include "GLFWWindowApplication.h"

#include <GLFW/glfw3.h>
#include <cstdlib>
#include <functional>
#include <stdexcept>

GLFWWindowApplication::GLFWWindowApplication() {}

GLFWWindowApplication::GLFWWindowApplication(TGLFWWindowParameter& rParameter)
  : appParameters(rParameter)
{
}

GLFWWindowApplication::~GLFWWindowApplication()
{
   // TODO Auto-generated destructor stub
}

void
GLFWWindowApplication::mainLoop()
{
   while (!glfwWindowShouldClose(this->window))
   {
      glfwPollEvents();
   }
}

void
GLFWWindowApplication::run()
{
   init();
   mainLoop();
   cleanup();
}

void
GLFWWindowApplication::init()
{
   // GLFW initialization
   glfwInit();

   // Tell GLFW not to create an open GL context
   glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

   // Disable resizable window
   glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

   // Window creation
   this->window = glfwCreateWindow(appParameters.width, appParameters.height, appParameters.title, nullptr, nullptr);
}

void
GLFWWindowApplication::cleanup()
{
   // GLFW window destruction
   glfwDestroyWindow(this->window);

   // GLFW termination
   glfwTerminate();
}
