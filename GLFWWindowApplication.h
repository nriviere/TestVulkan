/*
 * TestVulkanApp.h
 *
 *  Created on: 25 mars 2018
 *      Author: Vi4nde
 */

#ifndef GLFWWINDOWAPPLICATION_H_
#define GLFWWINDOWAPPLICATION_H_

class GLFWwindow;

#include <iostream>

typedef struct SGLFWWindowParameter
{
   unsigned int width  = 800;
   unsigned int height = 600;
   const char*  title  = "Untitled";
} TGLFWWindowParameter;

class GLFWWindowApplication
{
 public:
   GLFWWindowApplication();

   GLFWWindowApplication(TGLFWWindowParameter& parameter);

   virtual ~GLFWWindowApplication();

   void run();

 protected:
   virtual void init();

   void mainLoop();

   virtual void cleanup();

 private:
   class GLFWwindow* window = nullptr;

   TGLFWWindowParameter appParameters;
};

#endif /* GLFWWINDOWAPPLICATION_H_ */
