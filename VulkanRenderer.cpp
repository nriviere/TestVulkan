/*
 * VulkanApplication.cpp
 *
 *  Created on: 25 mars 2018
 *      Author: Vi4nde
 */

#include "VulkanRenderer.h"
#include <GLFW/glfw3.h>
#include <string.h>

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
}

void
VulkanRenderer::cleanup()
{
   instance.cleanup();
}

void
VulkanRenderer::pickPhysicalDevice()
{
   uint32_t deviceCount = 0;
   vkEnumeratePhysicalDevices(instance.getInstance(), &deviceCount, nullptr);

   if (deviceCount == 0)
   {
      throw std::runtime_error("failed to find GPUs with Vulkan support!");
   }

   std::vector<VkPhysicalDevice> devices(deviceCount);
   vkEnumeratePhysicalDevices(instance.getInstance(), &deviceCount, devices.data());

   for (const auto& device : devices)
   {
      if (this->isDeviceSuitable(device))
      {
         physicalDevice = device;
         break;
      }
   }

   if (physicalDevice == VK_NULL_HANDLE)
   {
      throw std::runtime_error("failed to find a suitable GPU!");
   }
}

bool
VulkanRenderer::isDeviceSuitable(VkPhysicalDevice device)
{
   return true;
}
