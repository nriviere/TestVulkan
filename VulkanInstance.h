/*
 * VulkanInstance.h
 *
 *  Created on: 5 nov. 2018
 *      Author: Vi4nde
 */

#ifndef VULKANINSTANCE_H_
#define VULKANINSTANCE_H_

#include "Utilities.h"
#include <vector>
#include <vulkan/vulkan.h>

#define VK_API_VERSION VK_API_VERSION_1_0
const std::vector<const char*> validationLayers = { "VK_LAYER_LUNARG_standard_validation" };

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

class VulkanInstance
{
 public:
   VulkanInstance();
   virtual ~VulkanInstance();

   VkInstance getInstance() const { return instance; }

   static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT      messageSeverity,
                                                       VkDebugUtilsMessageTypeFlagsEXT             messageType,
                                                       const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                                       void*                                       pUserData);

   void init(TVulkanInstanceParameter& rVulkanInstanceParameter);
   void cleanup();

 private:
   void     checkExtensions(TExtensionParameter& rExtensionParameter);
   void     checkValidationLayerSupport();
   void     createInstance(TVulkanInstanceParameter& rVulkanInstanceParameter);
   void     initCreateInfoDebug(VkInstanceCreateInfo& createInfo, TVulkanInstanceParameter& rVulkanInstanceParameters);
   void     initCreateInfo(TVulkanInstanceParameter& rVulkanInstanceParameters, VkInstanceCreateInfo& createInfo);
   void     initAppInfo(VkApplicationInfo& appInfo, TVulkanInstanceParameter& rVulkanInstanceParameters);
   VkResult createDebugUtilsMessengerEXT(VkInstance                                instance,
                                         const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                         const VkAllocationCallbacks*              pAllocator,
                                         VkDebugUtilsMessengerEXT*                 pCallback);
   void     destroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT callback, const VkAllocationCallbacks* pAllocator);
   void     setupDebugCallback();

 private:
   VkInstance               instance;
   VkDebugUtilsMessengerEXT callback;
};

#endif /* VULKANINSTANCE_H_ */
