/*
 * Utilities.h
 *
 *  Created on: 25 mars 2018
 *      Author: Vi4nde
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <iostream>
#include <optional>

typedef struct SVersionNumber
{
   unsigned int major = 0;
   unsigned int minor = 0;
   unsigned int patch = 0;
} TVersionNumber;

typedef struct SExtensionParameter
{
   const char** ppRequiredExtensions    = nullptr;
   unsigned int requiredExtensionsCount = 0;

} TExtensionParameter;

typedef struct SVulkanInstanceParameter
{
   const char*         applicationName          = "Untitled";
   const char*         engineName               = "Untitled";
   TVersionNumber      applicationVersionNumber = { 1, 0, 0 };
   TVersionNumber      engineVersion            = { 1, 0, 0 };
   TExtensionParameter extensionParameter;

} TVulkanInstanceParameter;

typedef struct SQueueFamilyIndices
{
   std::optional<uint32_t> graphicsFamily;

   bool isComplete() { return graphicsFamily.has_value(); }

} TQueueFamilyIndices;

class Utilities
{
};

#endif /* UTILITIES_H_ */
