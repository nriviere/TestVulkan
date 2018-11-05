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
#include "VulkanLogicalDevice.h"
#include "VulkanPhysicalDevice.h"
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

 private:
   VulkanInstance       instance;
   VulkanPhysicalDevice physicalDevice;
   VulkanLogicalDevice  logicalDevice;
};

#endif /* VULKANRENDERER_H_ */
