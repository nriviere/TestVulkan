/*
 * VulkanLogicalDevice.h
 *
 *  Created on: 5 nov. 2018
 *      Author: Vi4nde
 */

#ifndef VULKANLOGICALDEVICE_H_
#define VULKANLOGICALDEVICE_H_

#include "VulkanPhysicalDevice.h"
#include <vulkan/vulkan.h>

class VulkanLogicalDevice
{
 public:
   VulkanLogicalDevice();
   virtual ~VulkanLogicalDevice();

   void init(VulkanPhysicalDevice& physicalDevice);
   void cleanup();

   VkQueue getGraphicsQueue() const { return graphicsQueue; }

 private:
   VkDevice device        = VK_NULL_HANDLE;
   VkQueue  graphicsQueue = VK_NULL_HANDLE;
};

#endif /* VULKANLOGICALDEVICE_H_ */
