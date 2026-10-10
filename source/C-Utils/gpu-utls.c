/*************************/
/* Library importations: */
/*************************/

#ifndef C_UTILS_COMPILE
#include "../../include/C-Utils/gpu-utls.h"
#include "../../include/C-Utils/err-utls.h"
#include "../../include/Zeux/volk.h"
#else
#include "C-Utils/gpu-utls.h"
#include "C-Utils/err-utls.h"
#include "Zeux/volk.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/********************/
/* Import C to C++: */
/********************/

/* C-Utils GPU variables: */
static c_utils_bool_t c_utils_gpu_is_initialized = C_UTILS_FALSE;
static c_utils_uint8_t c_utils_gpu_current_mode = C_UTILS_GPU_MODE_COMPUTE_ONLY;

/* Vulkan compute variables: */
static VkInstance vk_instance = C_UTILS_NULL_POINTER;
static VkPhysicalDevice vk_physical_device = C_UTILS_NULL_POINTER;
static VkDevice vk_device = C_UTILS_NULL_POINTER;
static c_utils_uint32_t vk_queue_family_index = 0;
static VkQueue vk_queue = C_UTILS_NULL_POINTER;
static VkCommandPool vk_command_pool = C_UTILS_NULL_POINTER;

#ifdef __cplusplus
extern "C"
{
#endif

/**************************/
/* Functions definitions: */
/**************************/

static c_utils_result_t c_utils_gpu_init_vulkan_instance(c_utils_void_t)
{
	if(volkInitialize() != VK_SUCCESS)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_init_vulkan_instance, function volkInitialize failed");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		VkApplicationInfo app_info;
		VkInstanceCreateInfo instance_info;

		memset(&app_info, 0, sizeof(app_info));
		app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		app_info.pApplicationName = "C-Utils";
		app_info.apiVersion = VK_API_VERSION_1_0;

		memset(&instance_info, 0, sizeof(instance_info));
		instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instance_info.pApplicationInfo = &app_info;

		if(vkCreateInstance(&instance_info, C_UTILS_NULL_POINTER, &vk_instance) != VK_SUCCESS)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_init_vulkan_instance, function vkCreateInstance failed");

			return C_UTILS_RESULT_FAILURE;
		}

		volkLoadInstance(vk_instance);
	}

	return C_UTILS_RESULT_SUCCESS;
}

static c_utils_result_t c_utils_gpu_select_physical_device_and_queue(c_utils_void_t)
{
	c_utils_uint32_t device_count = 0;

	vkEnumeratePhysicalDevices(vk_instance, &device_count, C_UTILS_NULL_POINTER);

	if(!device_count)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_select_physical_device_and_queue, the device_count == 0");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		VkPhysicalDevice *const devices = (VkPhysicalDevice *)malloc(device_count * sizeof(*devices));

		if(!devices)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_select_physical_device_and_queue, function malloc failed");

			return C_UTILS_RESULT_FAILURE;
		}

		else
		{
			c_utils_uint32_t i;
			c_utils_bool_t device_found = C_UTILS_FALSE;

			vkEnumeratePhysicalDevices(vk_instance, &device_count, devices);
			vk_physical_device = C_UTILS_NULL_POINTER;

			for(i = 0u; (i < device_count) && (!device_found); i++)
			{
				c_utils_uint32_t queue_family_count = 0u;

				vkGetPhysicalDeviceQueueFamilyProperties(
					devices[i],
					&queue_family_count,
					C_UTILS_NULL_POINTER
				);

				if(queue_family_count > 0u)
				{
					VkQueueFamilyProperties *const queue_families = (VkQueueFamilyProperties *)malloc(queue_family_count * sizeof(*queue_families));

					if(!queue_families)
					{
						C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_select_physical_device_and_queue, function malloc failed");

						free((c_utils_void_t *)devices);

						return C_UTILS_RESULT_FAILURE;
					}

					else
					{
						c_utils_uint32_t j;

						vkGetPhysicalDeviceQueueFamilyProperties(
							devices[i],
							&queue_family_count,
							queue_families
						);

						for(j = 0u; (j < queue_family_count) && (!device_found); j++)
						{
							if(queue_families[j].queueFlags & VK_QUEUE_GRAPHICS_BIT)
							{
								vk_physical_device = devices[i];
								vk_queue_family_index = j;
								device_found = C_UTILS_TRUE;
							}
						}

						free((c_utils_void_t *)queue_families);
					}
				}
			}

			free((c_utils_void_t *)devices);

			if(!device_found)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_select_physical_device_and_queue, the device_found == 0");

				return C_UTILS_RESULT_FAILURE;
			}
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

static c_utils_result_t c_utils_gpu_create_logical_device_and_queue(c_utils_void_t)
{
	c_utils_float32_t queue_priority = 1.0f;
	VkDeviceQueueCreateInfo queue_create_info;
	VkDeviceCreateInfo device_create_info;

	memset(&queue_create_info, 0, sizeof(queue_create_info));
	queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queue_create_info.queueFamilyIndex = vk_queue_family_index;
	queue_create_info.queueCount = 1u;
	queue_create_info.pQueuePriorities = &queue_priority;

	memset(&device_create_info, 0, sizeof(device_create_info));
	device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	device_create_info.queueCreateInfoCount = 1u;
	device_create_info.pQueueCreateInfos = &queue_create_info;

	if(vkCreateDevice(vk_physical_device, &device_create_info, C_UTILS_NULL_POINTER, &vk_device) != VK_SUCCESS)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_create_logical_device_and_queue, function vkCreateDevice failed");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		volkLoadDevice(vk_device);
		vkGetDeviceQueue(vk_device, vk_queue_family_index, 0u, &vk_queue);
	}

	return C_UTILS_RESULT_SUCCESS;
}

static c_utils_result_t c_utils_gpu_create_command_pool(c_utils_void_t)
{
	VkCommandPoolCreateInfo pool_info;

	memset(&pool_info, 0, sizeof(pool_info));
	pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	pool_info.queueFamilyIndex = vk_queue_family_index;
	pool_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

	if(vkCreateCommandPool(vk_device, &pool_info, C_UTILS_NULL_POINTER, &vk_command_pool) != VK_SUCCESS)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_create_command_pool, function vkCreateCommandPool failed");

		return C_UTILS_RESULT_FAILURE;
	}

	return C_UTILS_RESULT_SUCCESS;
}

static c_utils_uint32_t c_utils_gpu_find_memory_type(c_utils_uint32_t type_filter, VkMemoryPropertyFlags properties)
{
	if(vk_physical_device == C_UTILS_NULL_POINTER)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_find_memory_type, the vk_physical_device == C_UTILS_NULL_POINTER");

		return ~0u;
	}

	else
	{
		c_utils_uint32_t i;
		VkPhysicalDeviceMemoryProperties memory_properties;

		vkGetPhysicalDeviceMemoryProperties(vk_physical_device, &memory_properties);

		for(i = 0u; i < memory_properties.memoryTypeCount; i++)
		{
			if((type_filter & (1u << i)) && (memory_properties.memoryTypes[i].propertyFlags & properties) == properties)
			{
				return i;
			}
		}

		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_find_memory_type, the memory type was not found");
	}

	return ~0u;
}

C_UTILS_API c_utils_result_t c_utils_gpu_load_spir_v(const c_utils_char_t *const path, c_utils_memory_handle_t *output_handle, c_utils_size_t *output_size)
{
	if(!path)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_load_spir_v, the path is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!output_handle)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_load_spir_v, the output_handle is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!output_size)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_load_spir_v, the output_size is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		FILE *const file = fopen(path, "rb");

		if(!file)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_load_spir_v, function fopen failed");

			return C_UTILS_RESULT_FAILURE;
		}

		if(fseek(file, 0L, SEEK_END))
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_load_spir_v, function fseek failed");

			if(fclose(file) == EOF)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_load_spir_v, function fclose failed");
			}

			return C_UTILS_RESULT_FAILURE;
		}

		else
		{
			signed long int size = ftell(file);

			if(size <= 0L)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_load_spir_v, the size <= 0L");

				if(fclose(file) == EOF)
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_load_spir_v, function fclose failed");
				}

				return C_UTILS_RESULT_FAILURE;
			}

			rewind(file);

			if(c_utils_mem_allocate(output_handle, (c_utils_size_t)size))
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_load_spir_v, function c_utils_mem_allocate failed");

				if(fclose(file) == EOF)
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_load_spir_v, function fclose failed");
				}

				return C_UTILS_RESULT_FAILURE;
			}

			if(fread(output_handle->pointer, 1u, (c_utils_size_t)size, file) != (c_utils_size_t)size)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_load_spir_v, function fread failed");

				if(c_utils_mem_free_and_unregist(output_handle))
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_load_spir_v, function c_utils_mem_free_and_unregist failed");
				}

				if(fclose(file) == EOF)
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_load_spir_v, function fclose failed");
				}

				return C_UTILS_RESULT_FAILURE;
			}

			if(fclose(file) == EOF)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_load_spir_v, function fclose failed");

				if(c_utils_mem_free_and_unregist(output_handle))
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_load_spir_v, function c_utils_mem_free_and_unregist failed");
				}

				return C_UTILS_RESULT_FAILURE;
			}

			*output_size = (c_utils_size_t)size;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_gpu_compute_initialize(c_utils_void_t)
{
	if(c_utils_gpu_is_initialized)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_initialize, C-Utils GPU is already initialized");

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_gpu_init_vulkan_instance() != C_UTILS_RESULT_SUCCESS)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_initialize, function c_utils_gpu_init_vulkan_instance failed");

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_gpu_select_physical_device_and_queue() != C_UTILS_RESULT_SUCCESS)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_initialize, function c_utils_gpu_select_physical_device_and_queue failed");

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_gpu_create_logical_device_and_queue() != C_UTILS_RESULT_SUCCESS)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_initialize, function c_utils_gpu_create_logical_device_and_queue failed");

		return C_UTILS_RESULT_FAILURE;
	}

	if(c_utils_gpu_create_command_pool() != C_UTILS_RESULT_SUCCESS)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_initialize, function c_utils_gpu_create_command_pool failed");

		return C_UTILS_RESULT_FAILURE;
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_gpu_compute_create(const c_utils_uint32_t *spir_v_code, c_utils_size_t spir_v_size, c_utils_gpu_compute_t *output_compute)
{
	if(!spir_v_code)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_create, spir_v_code is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!spir_v_size)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_create, spir_v_size == 0u");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!output_compute)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_create, output_compute is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(vk_device == C_UTILS_NULL_POINTER)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_create, vk_device == C_UTILS_NULL_POINTER");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		VkShaderModuleCreateInfo shader_info;

		memset(output_compute, 0, sizeof(*output_compute));
		memset(&shader_info, 0, sizeof(shader_info));
		shader_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		shader_info.codeSize = spir_v_size;
		shader_info.pCode = spir_v_code;

		if(vkCreateShaderModule(vk_device, &shader_info, C_UTILS_NULL_POINTER, &output_compute->shader_module) != VK_SUCCESS)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_create, function vkCreateShaderModule failed");

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_gpu_compute_buffer_create(c_utils_size_t size, c_utils_uint8_t type, c_utils_gpu_buffer_t *output_buffer)
{
	if(!size)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_buffer_create, the size == 0u");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!output_buffer)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_buffer_create, the output_buffer is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(vk_device == C_UTILS_NULL_POINTER)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_buffer_create, the vk_device == C_UTILS_NULL_POINTER");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		VkBufferCreateInfo buffer_info;

		memset(output_buffer, 0, sizeof(*output_buffer));

		memset(&buffer_info, 0, sizeof(buffer_info));

		buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		buffer_info.size = (VkDeviceSize)size;
		buffer_info.usage = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
		buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		if(vkCreateBuffer(
			vk_device,
			&buffer_info,
			C_UTILS_NULL_POINTER,
			&output_buffer->buffer
			) != VK_SUCCESS
		)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_buffer_create, function vkCreateBuffer failed");

			return C_UTILS_RESULT_FAILURE;
		}

		else
		{
			VkMemoryRequirements memory_requirements;
			c_utils_uint32_t memory_type_index;

			vkGetBufferMemoryRequirements(vk_device, output_buffer->buffer, &memory_requirements);

			memory_type_index = c_utils_gpu_find_memory_type(memory_requirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

			if(memory_type_index == ~0u)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_buffer_create, function c_utils_gpu_find_memory_type failed");

				vkDestroyBuffer(vk_device, output_buffer->buffer, C_UTILS_NULL_POINTER);
				output_buffer->buffer = C_UTILS_NULL_POINTER;

				return C_UTILS_RESULT_FAILURE;
			}

			else
			{
				VkMemoryAllocateInfo alloc_info;

				memset(&alloc_info, 0, sizeof(alloc_info));

				alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
				alloc_info.allocationSize = memory_requirements.size;
				alloc_info.memoryTypeIndex = memory_type_index;

				if(vkAllocateMemory(
					vk_device,
					&alloc_info,
					C_UTILS_NULL_POINTER,
					&output_buffer->memory
					) != VK_SUCCESS
				)
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_buffer_create, function vkAllocateMemory failed");

					vkDestroyBuffer(vk_device, output_buffer->buffer, C_UTILS_NULL_POINTER);
					output_buffer->buffer = C_UTILS_NULL_POINTER;

					return C_UTILS_RESULT_FAILURE;
				}

				if(vkBindBufferMemory(
					vk_device,
					output_buffer->buffer,
					output_buffer->memory,
					0u
					) != VK_SUCCESS
				)
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_buffer_create, function vkBindBufferMemory failed");

					vkFreeMemory(vk_device, output_buffer->memory, C_UTILS_NULL_POINTER);
					output_buffer->memory = C_UTILS_NULL_POINTER;

					vkDestroyBuffer(vk_device, output_buffer->buffer, C_UTILS_NULL_POINTER);
					output_buffer->buffer = C_UTILS_NULL_POINTER;

					return C_UTILS_RESULT_FAILURE;
				}

				output_buffer->size = size;
			}
		}
	}

	(c_utils_void_t)type;

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_gpu_compute_buffer_write(c_utils_gpu_buffer_t *buffer, const c_utils_void_t *data, const c_utils_size_t size)
{
	if(!buffer)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_buffer_write, the buffer is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!data)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_buffer_write, the data is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!size || size > buffer->size)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_buffer_write, the size == 0u || size > buffer->size");

		return C_UTILS_RESULT_FAILURE;
	}

	if(vk_device == C_UTILS_NULL_POINTER)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_buffer_write, the vk_device == C_UTILS_NULL_POINTER");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		c_utils_void_t *mapped_ptr = C_UTILS_NULL_POINTER;

		vkQueueWaitIdle(vk_queue);

		if(vkMapMemory(
			vk_device,
			buffer->memory,
			0u,
			(VkDeviceSize)size,
			0u,
			&mapped_ptr
			) != VK_SUCCESS
		)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_buffer_write, function vkMapMemory failed");

			return C_UTILS_RESULT_FAILURE;
		}

		memcpy(mapped_ptr, data, size);
		vkUnmapMemory(vk_device, buffer->memory);
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_gpu_compute_buffer_read(c_utils_gpu_buffer_t *buffer, c_utils_void_t *data)
{
	if(!buffer)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_buffer_read, the buffer is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!data)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_buffer_read, the data is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(vk_device == C_UTILS_NULL_POINTER)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_buffer_read, the vk_device == C_UTILS_NULL_POINTER");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		c_utils_void_t *mapped_ptr = C_UTILS_NULL_POINTER;

		vkQueueWaitIdle(vk_queue);

		if(vkMapMemory(
			vk_device,
			buffer->memory,
			0u,
			(VkDeviceSize)buffer->size,
			0u,
			&mapped_ptr
			) != VK_SUCCESS
		)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_buffer_read, function vkMapMemory failed");

			return C_UTILS_RESULT_FAILURE;
		}

		memcpy(data, mapped_ptr, buffer->size);
		vkUnmapMemory(vk_device, buffer->memory);
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_gpu_compute_buffer_destroy(c_utils_gpu_buffer_t *buffer)
{
	if(!buffer)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_buffer_destroy, the buffer is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(vk_device == C_UTILS_NULL_POINTER)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_buffer_destroy, the vk_device == C_UTILS_NULL_POINTER");

		return C_UTILS_RESULT_FAILURE;
	}

	if(buffer->buffer != C_UTILS_NULL_POINTER)
	{
		vkDestroyBuffer(
			vk_device,
			buffer->buffer,
			C_UTILS_NULL_POINTER
		);

		buffer->buffer = C_UTILS_NULL_POINTER;
	}

	if(buffer->memory != C_UTILS_NULL_POINTER)
	{
		vkFreeMemory(
			vk_device,
			buffer->memory,
			C_UTILS_NULL_POINTER
		);

		buffer->memory = C_UTILS_NULL_POINTER;
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_gpu_compute_bind_buffer(c_utils_gpu_compute_t *compute, c_utils_uint32_t binding, c_utils_gpu_buffer_t *buffer)
{
	if(!compute)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_bind_buffer, the compute is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!buffer)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_bind_buffer, the buffer is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(binding >= compute->bound_capacity)
	{
		c_utils_uint32_t new_capacity = binding + 1u;
		c_utils_gpu_buffer_t **new_buffers = (c_utils_gpu_buffer_t **)realloc(compute->bound_buffers, sizeof(*new_buffers) * new_capacity);

		if(!new_buffers)
		{
			C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_bind_buffer, function realloc failed");

			return C_UTILS_RESULT_FAILURE;
		}

		else
		{
			c_utils_uint32_t i;

			for(i = compute->bound_capacity; i < new_capacity; i++)
			{
				new_buffers[i] = C_UTILS_NULL_POINTER;
			}

			compute->bound_buffers = new_buffers;
			compute->bound_capacity = new_capacity;
		}
	}

	compute->bound_buffers[binding] = buffer;

	if(binding >= compute->bound_count)
	{
		compute->bound_count = binding + 1u;
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_gpu_compute_dispatch(c_utils_gpu_compute_t *compute, c_utils_uint32_t group_x, c_utils_uint32_t group_y, c_utils_uint32_t group_z)
{
	if(!compute)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_dispatch, the compute is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!vk_device)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_dispatch, vk_device == C_UTILS_NULL_POINTER");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		VkCommandBufferAllocateInfo cmd_alloc_info;
		VkCommandBuffer cmd_buffer;
		VkCommandBufferBeginInfo begin_info;
		VkSubmitInfo submit_info;

		if(!compute->is_compiled)
		{
			VkDescriptorSetLayoutBinding *bindings;

			if(compute->bound_count > 0u)
			{
				bindings = (VkDescriptorSetLayoutBinding *)malloc(sizeof(*bindings) * compute->bound_count);

				if(!bindings)
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_dispatch, function malloc failed");

					return C_UTILS_RESULT_FAILURE;
				}

				else
				{
					c_utils_uint32_t i;

					memset(bindings, 0, sizeof(*bindings) * compute->bound_count);

					for(i = 0u; i < compute->bound_count; i++)
					{
						bindings[i].binding = i;
						bindings[i].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
						bindings[i].descriptorCount = 1u;
						bindings[i].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
					}
				}
			}

			else
			{
				VkDescriptorSetLayoutCreateInfo layout_info;

				memset(&layout_info, 0, sizeof(layout_info));

				layout_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
				layout_info.bindingCount = compute->bound_count;
				layout_info.pBindings = bindings;

				vkCreateDescriptorSetLayout(
					vk_device,
					&layout_info,
					C_UTILS_NULL_POINTER,
					&compute->descriptor_layout
				);

				if(bindings)
				{
					free((c_utils_void_t *)bindings);
					bindings = C_UTILS_NULL_POINTER;
				}

				else
				{
					VkDescriptorPoolSize pool_size;
					VkDescriptorPoolCreateInfo pool_info;
					VkDescriptorSetAllocateInfo alloc_info;
					VkPipelineLayoutCreateInfo pipeline_layout_info;
					VkComputePipelineCreateInfo pipeline_info;

					memset(&pool_info, 0, sizeof(pool_info));

					pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
					pool_info.maxSets = 1u;
					pool_info.poolSizeCount = 1u;
					pool_info.pPoolSizes = &pool_size;

					vkCreateDescriptorPool(
						vk_device,
						&pool_info,
						C_UTILS_NULL_POINTER,
						&compute->descriptor_pool
					);

					memset(&alloc_info, 0, sizeof(alloc_info));

					alloc_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
					alloc_info.descriptorPool = compute->descriptor_pool;
					alloc_info.descriptorSetCount = 1u;
					alloc_info.pSetLayouts = &compute->descriptor_layout;

					vkAllocateDescriptorSets(
						vk_device,
						&alloc_info,
						&compute->descriptor_set
					);

					memset(&pipeline_layout_info, 0, sizeof(pipeline_layout_info));

					pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
					pipeline_layout_info.setLayoutCount = 1u;
					pipeline_layout_info.pSetLayouts = &compute->descriptor_layout;

					vkCreatePipelineLayout(
						vk_device,
						&pipeline_layout_info,
						C_UTILS_NULL_POINTER,
						&compute->pipeline_layout
					);

					memset(&pipeline_info, 0, sizeof(pipeline_info));

					pipeline_info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
					pipeline_info.stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
					pipeline_info.stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
					pipeline_info.stage.module = compute->shader_module;
					pipeline_info.stage.pName = "main";
					pipeline_info.layout = compute->pipeline_layout;

					vkCreateComputePipelines(
						vk_device,
						C_UTILS_NULL_POINTER,
						1u,
						&pipeline_info,
						C_UTILS_NULL_POINTER,
						&compute->pipeline
					);

					compute->is_compiled = 1u;
				}
			}
		}

		if(compute->bound_count > 0u)
		{
			VkWriteDescriptorSet *const writes = (VkWriteDescriptorSet *)malloc(sizeof(*writes) * compute->bound_count);

			if(!writes)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_dispatch, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			else
			{
				VkDescriptorBufferInfo *buffer_infos = (VkDescriptorBufferInfo *)malloc(sizeof(*buffer_infos) * compute->bound_count);

				if(!buffer_infos)
				{
					C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_dispatch, function malloc failed");

					free((c_utils_void_t *)writes);

					return C_UTILS_RESULT_FAILURE;
				}

				else
				{
					c_utils_uint32_t i;

					memset(writes, 0, sizeof(VkWriteDescriptorSet) * compute->bound_count);
					memset(buffer_infos, 0, sizeof(VkDescriptorBufferInfo) * compute->bound_count);

					for(i = 0u; i < compute->bound_count; i++)
					{
						if(compute->bound_buffers[i])
						{
							buffer_infos[i].buffer = compute->bound_buffers[i]->buffer;
							buffer_infos[i].offset = 0u;
							buffer_infos[i].range = (VkDeviceSize)compute->bound_buffers[i]->size;

							writes[i].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
							writes[i].dstSet = compute->descriptor_set;
							writes[i].dstBinding = i;
							writes[i].descriptorCount = 1u;
							writes[i].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
							writes[i].pBufferInfo = &buffer_infos[i];
						}
					}

					vkUpdateDescriptorSets(
						vk_device,
						compute->bound_count,
						writes,
						0u,
						C_UTILS_NULL_POINTER
					);

					free(writes);
					free(buffer_infos);
				}
			}
		}

		memset(&cmd_alloc_info, 0, sizeof(cmd_alloc_info));

		cmd_alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		cmd_alloc_info.commandPool = vk_command_pool;
		cmd_alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		cmd_alloc_info.commandBufferCount = 1u;
		vkAllocateCommandBuffers(vk_device, &cmd_alloc_info, &cmd_buffer);

		memset(&begin_info, 0, sizeof(begin_info));
		begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		vkBeginCommandBuffer(cmd_buffer, &begin_info);
		vkCmdBindPipeline(cmd_buffer, VK_PIPELINE_BIND_POINT_COMPUTE, compute->pipeline);

		if(compute->bound_count > 0u)
		{
			vkCmdBindDescriptorSets(cmd_buffer, VK_PIPELINE_BIND_POINT_COMPUTE, compute->pipeline_layout, 0u, 1u, &compute->descriptor_set, 0u, C_UTILS_NULL_POINTER);
		}

		vkCmdDispatch(cmd_buffer, group_x > 0u ? group_x : 1u, group_y > 0u ? group_y : 1u, group_z > 0u ? group_z : 1u);
		vkEndCommandBuffer(cmd_buffer);

		memset(&submit_info, 0, sizeof(submit_info));
		submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submit_info.commandBufferCount = 1u;
		submit_info.pCommandBuffers = &cmd_buffer;

		vkQueueSubmit(vk_queue, 1u, &submit_info, C_UTILS_NULL_POINTER);
		vkQueueWaitIdle(vk_queue);

		vkFreeCommandBuffers(vk_device, vk_command_pool, 1u, &cmd_buffer);
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_gpu_compute_destroy(c_utils_gpu_compute_t *compute)
{
	if(!compute || vk_device == C_UTILS_NULL_POINTER)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_destroy, compute == NULL or vk_device == C_UTILS_NULL_POINTER");

		return C_UTILS_RESULT_FAILURE;
	}

	if(compute->pipeline != C_UTILS_NULL_POINTER)
	{
		vkDestroyPipeline(vk_device, compute->pipeline, C_UTILS_NULL_POINTER);
		compute->pipeline = C_UTILS_NULL_POINTER;
	}

	if(compute->pipeline_layout != C_UTILS_NULL_POINTER)
	{
		vkDestroyPipelineLayout(vk_device, compute->pipeline_layout, C_UTILS_NULL_POINTER);
		compute->pipeline_layout = C_UTILS_NULL_POINTER;
	}

	if(compute->descriptor_pool != C_UTILS_NULL_POINTER)
	{
		vkDestroyDescriptorPool(vk_device, compute->descriptor_pool, C_UTILS_NULL_POINTER);
		compute->descriptor_pool = C_UTILS_NULL_POINTER;
	}

	if(compute->descriptor_layout != C_UTILS_NULL_POINTER)
	{
		vkDestroyDescriptorSetLayout(vk_device, compute->descriptor_layout, C_UTILS_NULL_POINTER);
		compute->descriptor_layout = C_UTILS_NULL_POINTER;
	}

	if(compute->shader_module != C_UTILS_NULL_POINTER)
	{
		vkDestroyShaderModule(vk_device, compute->shader_module, C_UTILS_NULL_POINTER);
		compute->shader_module = C_UTILS_NULL_POINTER;
	}

	if(compute->bound_buffers)
	{
		free((c_utils_void_t *)compute->bound_buffers);
		compute->bound_buffers = C_UTILS_NULL_POINTER;
	}

	compute->bound_capacity = 0u;
	compute->bound_count = 0u;
	compute->is_compiled = C_UTILS_FALSE;

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_gpu_compute_terminate(c_utils_void_t)
{
	if(!c_utils_gpu_is_initialized)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_gpu_compute_terminate, C-Utils GPU is not initialized");

		return C_UTILS_RESULT_FAILURE;
	}

	if(vk_device != C_UTILS_NULL_POINTER)
	{
		vkDeviceWaitIdle(vk_device);
	}

	if(vk_command_pool != C_UTILS_NULL_POINTER && vk_device != C_UTILS_NULL_POINTER)
	{
		vkDestroyCommandPool(vk_device, vk_command_pool, C_UTILS_NULL_POINTER);
		vk_command_pool = C_UTILS_NULL_POINTER;
	}

	if(vk_device != C_UTILS_NULL_POINTER)
	{
		vkDestroyDevice(vk_device, C_UTILS_NULL_POINTER);
		vk_device = C_UTILS_NULL_POINTER;
	}

	if(vk_instance != C_UTILS_NULL_POINTER)
	{
		vkDestroyInstance(vk_instance, C_UTILS_NULL_POINTER);
		vk_instance = C_UTILS_NULL_POINTER;
	}

	c_utils_gpu_is_initialized = C_UTILS_FALSE;

	return C_UTILS_RESULT_SUCCESS;
}

/*****************************/
/* End C to C++ importation: */
/*****************************/

#ifdef __cplusplus
}
#endif
