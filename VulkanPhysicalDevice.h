/*
 * VulkanDevice.h
 *
 *  Created on: 5 nov. 2018
 *      Author: Vi4nde
 */

#ifndef VULKANPHYSICALDEVICE_H_
#define VULKANPHYSICALDEVICE_H_

#include "VulkanInstance.h"

#include <vulkan/vulkan.h>

class VulkanPhysicalDevice
{
 public:
   VulkanPhysicalDevice();
   virtual ~VulkanPhysicalDevice();

   VkPhysicalDevice           getPhysicalDevice() const { return physicalDevice; }
   const TQueueFamilyIndices& getQueueFamiliesIndices() const { return queueFamiliesIndices; }

   void init(VulkanInstance& vulkanInstance);

 private:
   void                pickPhysicalDevice(VulkanInstance& vulkanInstance);
   TQueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

 private:
   VkPhysicalDevice    physicalDevice = VK_NULL_HANDLE;
   TQueueFamilyIndices queueFamiliesIndices;
};

#endif /* VULKANPHYSICALDEVICE_H_ */
