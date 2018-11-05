/*
 * VulkanApplication.cpp
 *
 *  Created on: 25 mars 2018
 *      Author: Vi4nde
 */

#include "VulkanRenderer.h"
#include <GLFW/glfw3.h>

VulkanRenderer::VulkanRenderer()
{
   // TODO Auto-generated constructor stub
}

VulkanRenderer::~VulkanRenderer()
{
   // TODO Auto-generated destructor stub
}

void
VulkanRenderer::init(TVulkanInstanceParameter& rVulkanInstanceParameter)
{
   instance.init(rVulkanInstanceParameter);
   physicalDevice.init(instance);
   logicalDevice.init(physicalDevice);
}

void
VulkanRenderer::cleanup()
{
   logicalDevice.cleanup();
   instance.cleanup();
}
