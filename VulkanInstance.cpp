/*
 * VulkanInstance.cpp
 *
 *  Created on: 5 nov. 2018
 *      Author: Vi4nde
 */

#include "VulkanInstance.h"
#include <string.h>

VulkanInstance::VulkanInstance()
{
   // TODO Auto-generated constructor stub
}

VulkanInstance::~VulkanInstance()
{
   // TODO Auto-generated destructor stub
}

void
VulkanInstance::checkExtensions(TExtensionParameter& rExtensionParameter)
{
   uint32_t extensionCount = 0;
   vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
   std::vector<VkExtensionProperties> extensions(extensionCount);

   vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

   for (unsigned int requiredExtensionIndex = 0; requiredExtensionIndex < rExtensionParameter.requiredExtensionsCount; ++requiredExtensionIndex)
   {
      const char* requiredExtensionName = rExtensionParameter.ppRequiredExtensions[requiredExtensionIndex];
      bool        found                 = false;
      for (const auto& extension : extensions)
      {
         if (0 == strcmp(extension.extensionName, requiredExtensionName))
         {
            found = true;
            break;
         }
      }

      if (!found)
      {
         std::string errorMsg("Missing extension : ");
         errorMsg += requiredExtensionName;
         throw std::runtime_error(errorMsg);
      }
   }
}

void
VulkanInstance::checkValidationLayerSupport()
{
   uint32_t layerCount;
   vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

   std::vector<VkLayerProperties> availableLayers(layerCount);
   vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

   for (const char* layerName : validationLayers)
   {
      bool layerFound = false;
      for (const auto& layerProperties : availableLayers)
      {
         if (strcmp(layerName, layerProperties.layerName) == 0)
         {
            layerFound = true;
            break;
         }
      }

      if (!layerFound)
      {
         std::string errorMsg("Missing validation layer : ");
         errorMsg += layerName;
         throw std::runtime_error(errorMsg);
      }
   }
}

void
VulkanInstance::initCreateInfoDebug(VkInstanceCreateInfo& createInfo, TVulkanInstanceParameter& rVulkanInstanceParameters)
{
   std::vector<const char*> extensions(rVulkanInstanceParameters.extensionParameter.ppRequiredExtensions,
                                       rVulkanInstanceParameters.extensionParameter.ppRequiredExtensions + rVulkanInstanceParameters.extensionParameter.requiredExtensionsCount);

   this->checkValidationLayerSupport();

   createInfo.enabledLayerCount   = static_cast<uint32_t>(validationLayers.size());
   createInfo.ppEnabledLayerNames = validationLayers.data();
   extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
   extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
   TExtensionParameter extensionParameter = { extensions.data(), extensions.size() };

   this->checkExtensions(extensionParameter);

   createInfo.enabledExtensionCount   = extensionParameter.requiredExtensionsCount;
   createInfo.ppEnabledExtensionNames = extensionParameter.ppRequiredExtensions;
}

void
VulkanInstance::initCreateInfo(TVulkanInstanceParameter& rVulkanInstanceParameters, VkInstanceCreateInfo& createInfo)
{
   this->checkExtensions(rVulkanInstanceParameters.extensionParameter);

   createInfo.enabledExtensionCount   = rVulkanInstanceParameters.extensionParameter.requiredExtensionsCount;
   createInfo.ppEnabledExtensionNames = rVulkanInstanceParameters.extensionParameter.ppRequiredExtensions;
}

void
VulkanInstance::initAppInfo(VkApplicationInfo& appInfo, TVulkanInstanceParameter& rVulkanInstanceParameters)
{
   appInfo.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
   appInfo.pApplicationName   = rVulkanInstanceParameters.applicationName;
   appInfo.applicationVersion = VK_MAKE_VERSION(
     rVulkanInstanceParameters.applicationVersionNumber.major, rVulkanInstanceParameters.applicationVersionNumber.minor, rVulkanInstanceParameters.applicationVersionNumber.patch);
   appInfo.pEngineName = rVulkanInstanceParameters.engineName;
   appInfo.engineVersion =
     VK_MAKE_VERSION(rVulkanInstanceParameters.engineVersion.major, rVulkanInstanceParameters.engineVersion.minor, rVulkanInstanceParameters.engineVersion.patch);
   appInfo.apiVersion = VK_API_VERSION;
}

void
VulkanInstance::createInstance(TVulkanInstanceParameter& rVulkanInstanceParameters)
{
   VkApplicationInfo appInfo = {};
   this->initAppInfo(appInfo, rVulkanInstanceParameters);

   VkInstanceCreateInfo createInfo = {};
   createInfo.sType                = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
   createInfo.pApplicationInfo     = &appInfo;

   if (enableValidationLayers)
   {
      this->initCreateInfoDebug(createInfo, rVulkanInstanceParameters);
   }
   else
   {
      this->initCreateInfo(rVulkanInstanceParameters, createInfo);
   }

   if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
   {
      throw std::runtime_error("failed to create instance!");
   }
}

VkBool32
VulkanInstance::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT      messageSeverity,
                              VkDebugUtilsMessageTypeFlagsEXT             messageType,
                              const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                              void*                                       pUserData)
{
   std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

   return VK_FALSE;
}

VkResult
VulkanInstance::createDebugUtilsMessengerEXT(VkInstance                                instance,
                                             const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                             const VkAllocationCallbacks*              pAllocator,
                                             VkDebugUtilsMessengerEXT*                 pCallback)
{
   auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
   if (func != nullptr)
   {
      return func(instance, pCreateInfo, pAllocator, pCallback);
   }
   else
   {
      return VK_ERROR_EXTENSION_NOT_PRESENT;
   }
}

void
VulkanInstance::destroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT callback, const VkAllocationCallbacks* pAllocator)
{
   auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
   if (func != nullptr)
   {
      func(instance, callback, pAllocator);
   }
}

void
VulkanInstance::init(TVulkanInstanceParameter& rVulkanInstanceParameter)
{
   this->createInstance(rVulkanInstanceParameter);
   this->setupDebugCallback();
}

void
VulkanInstance::cleanup()
{
   if (enableValidationLayers)
   {
      destroyDebugUtilsMessengerEXT(instance, callback, nullptr);
   }
   vkDestroyInstance(instance, nullptr);
}

void
VulkanInstance::setupDebugCallback()
{
   if (!enableValidationLayers)
      return;

   VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
   createInfo.sType                              = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
   createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
   createInfo.messageType     = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
   createInfo.pfnUserCallback = debugCallback;
   createInfo.pUserData       = nullptr; // Optional

   if (this->createDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &callback) != VK_SUCCESS)
   {
      throw std::runtime_error("failed to set up debug callback!");
   }
}
