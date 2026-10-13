/******************/
/* Include guard: */
/******************/

#ifndef C_UTILS_GPU_UTLS_H
#define C_UTILS_GPU_UTLS_H

/*************************/
/* Library importations: */
/*************************/

#include "defs.h"
#include "c-utils.h"
#include "../Zeux/volk.h"

/***********/
/* Macros: */
/***********/

#ifdef C_UTILS_BUFFER_TYPE_INPUT_DATA
#error "FATAL ERROR: C_UTILS_BUFFER_TYPE_INPUT_DATA already defined."
#else
#define C_UTILS_BUFFER_TYPE_INPUT_DATA 0u
#endif

#ifdef C_UTILS_BUFFER_TYPE_EMPTY_DATA
#error "FATAL ERROR: C_UTILS_BUFFER_TYPE_EMPTY_DATA already defined."
#else
#define C_UTILS_BUFFER_TYPE_EMPTY_DATA 1u
#endif

#ifdef C_UTILS_GPU_MODE_COMPUTE_ONLY
#error "FATAL ERROR: C_UTILS_GPU_MODE_COMPUTE_ONLY already defined."
#else
#define C_UTILS_GPU_MODE_COMPUTE_ONLY 0u
#endif

#ifdef C_UTILS_GPU_MODE_GRAPHICS
#error "FATAL ERROR: C_UTILS_GPU_MODE_GRAPHICS already defined."
#else
#define C_UTILS_GPU_MODE_GRAPHICS 1u
#endif

/********************/
/* Import C to C++: */
/********************/

#ifdef __cplusplus
extern "C"
{
#endif

/*********************/
/* Type definitions: */
/*********************/

/* C-Utils gpu buffer type: */
struct c_utils_gpu_buffer_t
{
	VkBuffer buffer;
	VkDeviceMemory memory;
	c_utils_size_t size;
	c_utils_uint8_t is_host_visible;
};

/* C-Utils typedef gpu buffer type: */
typedef struct c_utils_gpu_buffer_t c_utils_gpu_buffer_t;

/* C-Utils gpu compute type: */
struct c_utils_gpu_compute_t
{
	VkShaderModule shader_module;
	VkDescriptorSetLayout descriptor_layout;
	VkDescriptorPool descriptor_pool;
	VkDescriptorSet descriptor_set;
	VkPipelineLayout pipeline_layout;
	VkPipeline pipeline;
	c_utils_gpu_buffer_t **bound_buffers;
	c_utils_uint32_t bound_capacity;
	c_utils_uint32_t bound_count;
	c_utils_uint8_t is_compiled;
};

/* C-Utils typedef gpu compute type: */
typedef struct c_utils_gpu_compute_t c_utils_gpu_compute_t;

/*************************/
/* Functions prototypes: */
/*************************/

/* C-Utils gpu load spir v function: */
C_UTILS_API c_utils_result_t c_utils_gpu_load_spir_v(const c_utils_char_t *const path, c_utils_memory_handle_t *output_handle, c_utils_size_t *output_size);

/* C-Utils gpu initialize function: */
C_UTILS_API c_utils_result_t c_utils_gpu_initialize(const c_utils_uint8_t mode);

/* C-Utils gpu enable graphics function: */
C_UTILS_API c_utils_result_t c_utils_gpu_enable_graphics(c_utils_void_t);

/* C-Utils gpu compute create function: */
C_UTILS_API c_utils_result_t c_utils_gpu_compute_create(const c_utils_uint32_t *spir_v_code, c_utils_size_t spir_v_size, c_utils_gpu_compute_t *output_compute);

/* C-Utils gpu compute buffer create function: */
C_UTILS_API c_utils_result_t c_utils_gpu_compute_buffer_create(c_utils_size_t size, c_utils_uint8_t type, c_utils_gpu_buffer_t *output_buffer);

/* C-Utils gpu compute buffer write function: */
C_UTILS_API c_utils_result_t c_utils_gpu_compute_buffer_write(c_utils_gpu_buffer_t *buffer, const c_utils_void_t *data, const c_utils_size_t size);

/* C-Utils gpu compute buffer read function: */
C_UTILS_API c_utils_result_t c_utils_gpu_compute_buffer_read(c_utils_gpu_buffer_t *buffer, c_utils_void_t *data);

/* C-Utils gpu compute buffer destroy function: */
C_UTILS_API c_utils_result_t c_utils_gpu_compute_buffer_destroy(c_utils_gpu_buffer_t *buffer);

/* C-Utils gpu compute bind buffer function: */
C_UTILS_API c_utils_result_t c_utils_gpu_compute_bind_buffer(c_utils_gpu_compute_t *compute, c_utils_uint32_t binding, c_utils_gpu_buffer_t *buffer);

/* C-Utils gpu compute dispatch function: */
C_UTILS_API c_utils_result_t c_utils_gpu_compute_dispatch(c_utils_gpu_compute_t *compute, c_utils_uint32_t group_x, c_utils_uint32_t group_y, c_utils_uint32_t group_z);

/* C-Utils gpu compute destroy function: */
C_UTILS_API c_utils_result_t c_utils_gpu_compute_destroy(c_utils_gpu_compute_t *compute);

/* C-Utils gpu terminate function: */
C_UTILS_API c_utils_result_t c_utils_gpu_terminate(c_utils_void_t);

/*****************************/
/* End C to C++ importation: */
/*****************************/

#ifdef __cplusplus
}
#endif

/***************************/
/* End C_UTILS_GPU_UTLS_H: */
/***************************/

#endif
