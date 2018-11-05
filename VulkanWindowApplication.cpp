/*
 * VulkanWindow.cpp
 *
 *  Created on: 25 mars 2018
 *      Author: Vi4nde
 */

#include "VulkanWindowApplication.h"

#include <GLFW/glfw3.h>

VulkanWindowApplication::VulkanWindowApplication()
{
  // TODO Auto-generated constructor stub
}

VulkanWindowApplication::~VulkanWindowApplication()
{
  // TODO Auto-generated destructor stub
}

void VulkanWindowApplication::init()
{
  GLFWWindowApplication::init();

  TVulkanInstanceParameter vulkanInstanceParameter;
  vulkanInstanceParameter.extensionParameter.ppRequiredExtensions = glfwGetRequiredInstanceExtensions(&vulkanInstanceParameter.extensionParameter.requiredExtensionsCount);

  VulkanRenderer::init(vulkanInstanceParameter);
}

void VulkanWindowApplication::cleanup()
{
  VulkanRenderer::cleanup();
  GLFWWindowApplication::cleanup();
}
