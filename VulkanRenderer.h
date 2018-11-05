/*
 * VulkanApplication.h
 *
 *  Created on: 25 mars 2018
 *      Author: Vi4nde
 */

#ifndef VULKANRENDERER_H_
#define VULKANRENDERER_H_

#include "Utilities.h"
#include "VulkanInstance.h"
#include <iostream>
#include <vector>
#include <vulkan/vulkan.h>

class VulkanRenderer
{
 public:
   VulkanRenderer();

   virtual ~VulkanRenderer();

   void init(TVulkanInstanceParameter& rVulkanInstanceParameter);

   void cleanup();

   void pickPhysicalDevice();
   bool isDeviceSuitable(VkPhysicalDevice device);

 private:
   VulkanInstance   instance;
   VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
};

#endif /* VULKANRENDERER_H_ */
