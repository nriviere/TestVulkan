/*
 * VulkanLogicalDevice.cpp
 *
 *  Created on: 5 nov. 2018
 *      Author: Vi4nde
 */

#include "VulkanLogicalDevice.h"

VulkanLogicalDevice::VulkanLogicalDevice()
{
   // TODO Auto-generated constructor stub
}

VulkanLogicalDevice::~VulkanLogicalDevice()
{
   // TODO Auto-generated destructor stub
}

void
VulkanLogicalDevice::init(VulkanPhysicalDevice& physicalDevice)
{
   TQueueFamilyIndices indices = physicalDevice.getQueueFamiliesIndices();

   VkDeviceQueueCreateInfo queueCreateInfo = {};
   queueCreateInfo.sType                   = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
   queueCreateInfo.queueFamilyIndex        = indices.graphicsFamily.value();
   queueCreateInfo.queueCount              = 1;

   float queuePriority              = 1.0f;
   queueCreateInfo.pQueuePriorities = &queuePriority;

   VkPhysicalDeviceFeatures deviceFeatures = {};

   VkDeviceCreateInfo createInfo = {};
   createInfo.sType              = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

   createInfo.pQueueCreateInfos    = &queueCreateInfo;
   createInfo.queueCreateInfoCount = 1;

   createInfo.pEnabledFeatures = &deviceFeatures;

   createInfo.enabledExtensionCount = 0;

   if (enableValidationLayers)
   {
      createInfo.enabledLayerCount   = static_cast<uint32_t>(validationLayers.size());
      createInfo.ppEnabledLayerNames = validationLayers.data();
   }
   else
   {
      createInfo.enabledLayerCount = 0;
   }

   if (vkCreateDevice(physicalDevice.getPhysicalDevice(), &createInfo, nullptr, &device) != VK_SUCCESS)
   {
      throw std::runtime_error("failed to create logical device!");
   }

   vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
}

void
VulkanLogicalDevice::cleanup()
{
   vkDestroyDevice(device, nullptr);
}
