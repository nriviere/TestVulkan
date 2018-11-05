/*
 * VulkanDevice.cpp
 *
 *  Created on: 5 nov. 2018
 *      Author: Vi4nde
 */

#include "VulkanPhysicalDevice.h"

#include <iostream>
#include <vector>

VulkanPhysicalDevice::VulkanPhysicalDevice()
{
   // TODO Auto-generated constructor stub
}

VulkanPhysicalDevice::~VulkanPhysicalDevice()
{
   // TODO Auto-generated destructor stub
}

void
VulkanPhysicalDevice::pickPhysicalDevice(VulkanInstance& vulkanInstance)
{
   uint32_t deviceCount = 0;
   vkEnumeratePhysicalDevices(vulkanInstance.getInstance(), &deviceCount, nullptr);

   if (deviceCount == 0)
   {
      throw std::runtime_error("failed to find GPUs with Vulkan support!");
   }

   std::vector<VkPhysicalDevice> devices(deviceCount);
   vkEnumeratePhysicalDevices(vulkanInstance.getInstance(), &deviceCount, devices.data());

   for (const auto& device : devices)
   {
      TQueueFamilyIndices indices = findQueueFamilies(device);

      if (indices.isComplete())
      {
         physicalDevice       = device;
         queueFamiliesIndices = indices;
         break;
      }
   }

   if (physicalDevice == VK_NULL_HANDLE)
   {
      throw std::runtime_error("failed to find a suitable GPU!");
   }
}

TQueueFamilyIndices
VulkanPhysicalDevice::findQueueFamilies(VkPhysicalDevice device)
{
   TQueueFamilyIndices indices;

   uint32_t queueFamilyCount = 0;
   vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

   std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
   vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

   for (const auto& queueFamily : queueFamilies)
   {
      int i = 0;
      if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
      {
         indices.graphicsFamily = i;
      }

      if (indices.isComplete())
      {
         break;
      }

      i++;
   }
   return indices;
}

void
VulkanPhysicalDevice::init(VulkanInstance& vulkanInstance)
{
   this->pickPhysicalDevice(vulkanInstance);
}
