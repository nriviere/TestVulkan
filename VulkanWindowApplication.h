/*
 * VulkanWindow.h
 *
 *  Created on: 25 mars 2018
 *      Author: Vi4nde
 */

#ifndef VULKANWINDOWAPPLICATION_H_
#define VULKANWINDOWAPPLICATION_H_

#include "GLFWWindowApplication.h"
#include "VulkanRenderer.h"

class VulkanWindowApplication
  : public GLFWWindowApplication
  , public VulkanRenderer
{
 public:
   VulkanWindowApplication();
   virtual ~VulkanWindowApplication();

 protected:
   virtual void init();

   virtual void cleanup();
};

#endif /* VULKANWINDOWAPPLICATION_H_ */
