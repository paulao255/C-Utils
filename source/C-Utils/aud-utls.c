/*************************/
/* Library importations: */
/*************************/

#ifndef C_UTILS_COMPILE
#include "../../include/C-Utils/aud-utls.h"
#include "../../include/C-Utils/err-utls.h"
#else
#include "C-Utils/aud-utls.h"
#include "C-Utils/err-utls.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/********************/
/* Import C to C++: */
/********************/

#ifdef __cplusplus
extern "C"
{
#endif

/**************************/
/* Functions definitions: */
/**************************/

static c_utils_void_t c_utils_audio_capture_file_callback(ma_device *pDevice, c_utils_void_t *pOutput, const c_utils_void_t *pInput, ma_uint32 frameCount)
{
	c_utils_audio_encoder_t *pEncoder = (c_utils_audio_encoder_t *)pDevice->pUserData;

	if(pEncoder)
	{
		ma_encoder_write_pcm_frames(pEncoder, pInput, frameCount, C_UTILS_NULL_POINTER);
	}

	(c_utils_void_t)pOutput;
}

static c_utils_void_t c_utils_audio_capture_memory_callback(ma_device *pDevice, c_utils_void_t *pOutput, const c_utils_void_t *pInput, ma_uint32 frameCount)
{
	c_utils_audio_capture_memory_t *pMem = (c_utils_audio_capture_memory_t *)pDevice->pUserData;

	if(!pMem || !pInput)
	{
		return;
	}

	else
	{
		const c_utils_size_t frame_size = pMem->channels * pMem->format_size;
		const c_utils_size_t required_capacity = pMem->current_frames + frameCount;

		if(required_capacity > pMem->capacity_frames)
		{
			c_utils_size_t new_capacity = pMem->capacity_frames == 0 ? 44100 : pMem->capacity_frames * 2;
			c_utils_void_t *new_data;

			while(new_capacity < required_capacity)
			{
				new_capacity *= 2;
			}

			new_data = realloc(pMem->pcm_data, new_capacity * frame_size);

			if(new_data)
			{
				pMem->pcm_data = new_data;
				pMem->capacity_frames = new_capacity;
			}

			else
			{
				return;
			}
		}

		memcpy((c_utils_void_t *)((unsigned char *)pMem->pcm_data + pMem->current_frames * frame_size), pInput, (c_utils_size_t)frameCount * frame_size);
		pMem->current_frames += (c_utils_size_t)frameCount;
	}

	(c_utils_void_t)pOutput;
}

C_UTILS_API c_utils_result_t c_utils_audio_engine_initialize(const c_utils_audio_engine_config_t *config, c_utils_audio_engine_t *engine)
{
	if(!config)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_engine_initialize, the config is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!engine)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_engine_initialize, the engine is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const ma_result miniaudio_result = ma_engine_init(config, engine);

		if(miniaudio_result != MA_SUCCESS)
		{
			const c_utils_char_t *const description = ma_result_description(miniaudio_result);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_audio_engine_initialize, function ma_engine_init failed: ") + strlen(description) + strlen(", error code: ");
			c_utils_size_t error_size = 1u;
			signed int value = (signed int)miniaudio_result;

			if(value < 0)
			{
				value = -value;
				error_size++;
			}

			while(value >= 10)
			{
				value /= 10;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_audio_engine_initialize, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_audio_engine_initialize, function ma_engine_init failed: %s, error code: %d", description, (signed int)miniaudio_result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_engine_terminate(c_utils_audio_engine_t *engine)
{
	if(!engine)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_engine_terminate, the engine is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	ma_engine_uninit(engine);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_engine_config_initialize(c_utils_audio_engine_config_t *const output)
{
	if(!output)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_engine_config_initialize, the output is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	*output = ma_engine_config_init();

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_load_sound(c_utils_audio_engine_t *engine, const c_utils_char_t *const path, c_utils_audio_sound_t *sound)
{
	if(!engine)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_load_sound, the engine is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!path)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_load_sound, the path is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!sound)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_load_sound, the sound is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const ma_result miniaudio_result = ma_sound_init_from_file(engine, path, 0, C_UTILS_NULL_POINTER, C_UTILS_NULL_POINTER, sound);

		if(miniaudio_result != MA_SUCCESS)
		{
			const c_utils_char_t *const description = ma_result_description(miniaudio_result);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_audio_load_sound, function ma_sound_init_from_file failed: ") + strlen(description) + strlen(", error code: ");
			c_utils_size_t error_size = 1u;
			signed int value = (signed int)miniaudio_result;

			if(value < 0)
			{
				value = -value;
				error_size++;
			}

			while(value >= 10)
			{
				value /= 10;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_audio_load_sound, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_audio_load_sound, function ma_sound_init_from_file failed: %s, error code: %d", description, (signed int)miniaudio_result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_unload_sound(c_utils_audio_sound_t *sound)
{
	if(!sound)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_unload_sound, the sound is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	ma_sound_uninit(sound);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_start_sound(c_utils_audio_sound_t *sound)
{
	if(!sound)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_start_sound, the sound is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const ma_result miniaudio_result = ma_sound_start(sound);

		if(miniaudio_result != MA_SUCCESS)
		{
			const c_utils_char_t *const description = ma_result_description(miniaudio_result);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_audio_start_sound, function ma_sound_start failed: ") + strlen(description) + strlen(", error code: ");
			c_utils_size_t error_size = 1u;
			signed int value = (signed int)miniaudio_result;

			if(value < 0)
			{
				value = -value;
				error_size++;
			}

			while(value >= 10)
			{
				value /= 10;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_audio_start_sound, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_audio_start_sound, function ma_sound_start failed: %s, error code: %d", description, (signed int)miniaudio_result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_stop_sound(c_utils_audio_sound_t *sound)
{
	if(!sound)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_stop_sound, the sound is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const ma_result miniaudio_result = ma_sound_stop(sound);

		if(miniaudio_result != MA_SUCCESS)
		{
			const c_utils_char_t *const description = ma_result_description(miniaudio_result);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_audio_stop_sound, function ma_sound_stop failed: ") + strlen(description) + strlen(", error code: ");
			c_utils_size_t error_size = 1u;
			signed int value = (signed int)miniaudio_result;

			if(value < 0)
			{
				value = -value;
				error_size++;
			}

			while(value >= 10)
			{
				value /= 10;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_audio_stop_sound, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_audio_stop_sound, function ma_sound_stop failed: %s, error code: %d", description, (signed int)miniaudio_result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_set_volume(c_utils_audio_sound_t *sound, c_utils_float32_t volume)
{
	if(!sound)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_set_volume, the sound is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	ma_sound_set_volume(sound, volume);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_get_volume(c_utils_audio_sound_t *sound, c_utils_float32_t *const output)
{
	if(!sound)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_get_volume, the sound is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!output)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_get_volume, the output is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	*output = ma_sound_get_volume(sound);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_seek_to_pcm_frame(c_utils_audio_sound_t *sound, c_utils_uint64_t position)
{
	if(!sound)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_sound_seek_to_pcm_frame, the sound is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const ma_result miniaudio_result = ma_sound_seek_to_pcm_frame(sound, (ma_uint64)position);

		if(miniaudio_result != MA_SUCCESS)
		{
			const c_utils_char_t *const description = ma_result_description(miniaudio_result);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_audio_sound_seek_to_pcm_frame, function ma_sound_seek_to_pcm_frame failed: ") + strlen(description) + strlen(", error code: ");
			c_utils_size_t error_size = 1u;
			signed int value = (signed int)miniaudio_result;

			if(value < 0)
			{
				value = -value;
				error_size++;
			}

			while(value >= 10)
			{
				value /= 10;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_audio_sound_seek_to_pcm_frame, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_audio_sound_seek_to_pcm_frame, function ma_sound_seek_to_pcm_frame failed: %s, error code: %d", description, (signed int)miniaudio_result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_get_cursor_in_pcm_frames(c_utils_audio_sound_t *sound, c_utils_uint64_t *output)
{
	if(!sound)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_get_cursor_in_pcm_frames, the sound is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!output)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_get_cursor_in_pcm_frames, the output is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const ma_result miniaudio_result = ma_sound_get_cursor_in_pcm_frames(sound, (ma_uint64 *)output);

		if(miniaudio_result != MA_SUCCESS)
		{
			const c_utils_char_t *const description = ma_result_description(miniaudio_result);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_audio_get_cursor_in_pcm_frames, function ma_sound_get_cursor_in_pcm_frames failed: ") + strlen(description) + strlen(", error code: ");
			c_utils_size_t error_size = 1u;
			signed int value = (signed int)miniaudio_result;

			if(value < 0)
			{
				value = -value;
				error_size++;
			}

			while(value >= 10)
			{
				value /= 10;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_audio_get_cursor_in_pcm_frames, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_audio_get_cursor_in_pcm_frames, function ma_sound_get_cursor_in_pcm_frames failed: %s, error code: %d", description, (signed int)miniaudio_result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_set_looping(c_utils_audio_sound_t *sound, c_utils_bool_t looping)
{
	if(!sound)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_sound_set_looping, the sound is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	ma_sound_set_looping(sound, (ma_bool32)looping);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_engine_listener_set_position(c_utils_audio_engine_t *engine, c_utils_uint32_t listener_index, c_utils_float32_t x, c_utils_float32_t y, c_utils_float32_t z)
{
	if(!engine)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_engine_listener_set_position, the engine is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	ma_engine_listener_set_position(engine, (ma_uint32)listener_index, x, y, z);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_engine_listener_set_direction(c_utils_audio_engine_t *engine, c_utils_uint32_t listener_index, c_utils_float32_t x, c_utils_float32_t y, c_utils_float32_t z)
{
	if(!engine)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_engine_listener_set_direction, the engine is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	ma_engine_listener_set_direction(engine, (ma_uint32)listener_index, x, y, z);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_engine_listener_set_velocity(c_utils_audio_engine_t *engine, c_utils_uint32_t listener_index, c_utils_float32_t x, c_utils_float32_t y, c_utils_float32_t z)
{
	if(!engine)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_engine_listener_set_velocity, the engine is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	ma_engine_listener_set_velocity(engine, (ma_uint32)listener_index, x, y, z);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_set_spatialization_enabled(c_utils_audio_sound_t *sound, c_utils_bool_t enabled)
{
	if(!sound)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_sound_set_spatialization_enabled, the sound is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	ma_sound_set_spatialization_enabled(sound, (ma_bool32)enabled);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_set_position(c_utils_audio_sound_t *sound, c_utils_float32_t x, c_utils_float32_t y, c_utils_float32_t z)
{
	if(!sound)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_sound_set_position, the sound is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	ma_sound_set_position(sound, x, y, z);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_set_direction(c_utils_audio_sound_t *sound, c_utils_float32_t x, c_utils_float32_t y, c_utils_float32_t z)
{
	if(!sound)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_sound_set_direction, the sound is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	ma_sound_set_direction(sound, x, y, z);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_set_velocity(c_utils_audio_sound_t *sound, c_utils_float32_t x, c_utils_float32_t y, c_utils_float32_t z)
{
	if(!sound)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_sound_set_velocity, the sound is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	ma_sound_set_velocity(sound, x, y, z);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_set_pitch(c_utils_audio_sound_t *sound, c_utils_float32_t pitch)
{
	if(!sound)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_sound_set_pitch, the sound is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	ma_sound_set_pitch(sound, pitch);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_set_pan(c_utils_audio_sound_t *sound, c_utils_float32_t pan)
{
	if(!sound)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_sound_set_pan, the sound is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	ma_sound_set_pan(sound, pan);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_is_playing(c_utils_audio_sound_t *sound, c_utils_bool_t *const output)
{
	if(!sound)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_sound_is_playing, the sound is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!output)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_sound_is_playing, the output is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	*output = (c_utils_bool_t)ma_sound_is_playing(sound);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_is_at_end(c_utils_audio_sound_t *sound, c_utils_bool_t *const output)
{
	if(!sound)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_sound_is_at_end, the sound is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!output)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_sound_is_at_end, the output is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	*output = (c_utils_bool_t)ma_sound_at_end(sound);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_get_length_in_pcm_frames(c_utils_audio_sound_t *sound, c_utils_uint64_t *const output)
{
	if(!sound)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_sound_get_length_in_pcm_frames, the sound is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!output)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_sound_get_length_in_pcm_frames, the output is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const ma_result miniaudio_result = ma_sound_get_length_in_pcm_frames(sound, (ma_uint64 *)output);

		if(miniaudio_result != MA_SUCCESS)
		{
			const c_utils_char_t *const description = ma_result_description(miniaudio_result);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_audio_sound_get_length_in_pcm_frames, function ma_sound_get_length_in_pcm_frames failed: ") + strlen(description) + strlen(", error code: ");
			c_utils_size_t error_size = 1u;
			signed int value = (signed int)miniaudio_result;

			if(value < 0)
			{
				value = -value;
				error_size++;
			}

			while(value >= 10)
			{
				value /= 10;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_audio_sound_get_length_in_pcm_frames, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_audio_sound_get_length_in_pcm_frames, function ma_sound_get_length_in_pcm_frames failed: %s, error code: %d", description, (signed int)miniaudio_result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_group_initialize(c_utils_audio_engine_t *engine, c_utils_audio_sound_group_t *group)
{
	if(!engine)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_sound_group_initialize, the engine is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!group)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_sound_group_initialize, the group is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const ma_result miniaudio_result = ma_sound_group_init(engine, 0, C_UTILS_NULL_POINTER, group);

		if(miniaudio_result != MA_SUCCESS)
		{
			const c_utils_char_t *const description = ma_result_description(miniaudio_result);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_audio_sound_group_initialize, function ma_sound_group_init failed: ") + strlen(description) + strlen(", error code: ");
			c_utils_size_t error_size = 1u;
			signed int value = (signed int)miniaudio_result;

			if(value < 0)
			{
				value = -value;
				error_size++;
			}

			while(value >= 10)
			{
				value /= 10;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_audio_sound_group_initialize, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_audio_sound_group_initialize, function ma_sound_group_init failed: %s, error code: %d", description, (signed int)miniaudio_result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_group_terminate(c_utils_audio_sound_group_t *group)
{
	if(!group)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_sound_group_terminate, the group is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	ma_sound_group_uninit(group);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_group_set_volume(c_utils_audio_sound_group_t *group, c_utils_float32_t volume)
{
	if(!group)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_sound_group_set_volume, the group is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	ma_sound_group_set_volume(group, volume);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_load_sound_into_group(c_utils_audio_engine_t *engine, const c_utils_char_t *const path, c_utils_audio_sound_group_t *group, c_utils_audio_sound_t *sound)
{
	if(!engine)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_load_sound_into_group, the engine is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!path)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_load_sound_into_group, the path is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!group)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_load_sound_into_group, the group is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!sound)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_load_sound_into_group, the sound is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const ma_result miniaudio_result = ma_sound_init_from_file(engine, path, 0, group, C_UTILS_NULL_POINTER, sound);

		if(miniaudio_result != MA_SUCCESS)
		{
			const c_utils_char_t *const description = ma_result_description(miniaudio_result);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_audio_load_sound_into_group, function ma_sound_init_from_file failed: ") + strlen(description) + strlen(", error code: ");
			c_utils_size_t error_size = 1u;
			signed int value = (signed int)miniaudio_result;

			if(value < 0)
			{
				value = -value;
				error_size++;
			}

			while(value >= 10)
			{
				value /= 10;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_audio_load_sound_into_group, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_audio_load_sound_into_group, function ma_sound_init_from_file failed: %s, error code: %d", description, (signed int)miniaudio_result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_decoder_initialize_from_memory(const c_utils_void_t *data, c_utils_size_t data_size, c_utils_audio_decoder_t *decoder)
{
	if(!data)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_decoder_initialize_from_memory, the data is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!data_size)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_decoder_initialize_from_memory, the data_size == 0u");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!decoder)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_decoder_initialize_from_memory, the decoder is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const ma_result miniaudio_result = ma_decoder_init_memory(data, (size_t)data_size, C_UTILS_NULL_POINTER, decoder);

		if(miniaudio_result != MA_SUCCESS)
		{
			const c_utils_char_t *const description = ma_result_description(miniaudio_result);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_audio_decoder_initialize_from_memory, function ma_decoder_init_memory failed: ") + strlen(description) + strlen(", error code: ");
			c_utils_size_t error_size = 1u;
			signed int value = (signed int)miniaudio_result;

			if(value < 0)
			{
				value = -value;
				error_size++;
			}

			while(value >= 10)
			{
				value /= 10;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_audio_decoder_initialize_from_memory, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_audio_decoder_initialize_from_memory, function ma_decoder_init_memory failed: %s, error code: %d", description, (signed int)miniaudio_result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_decoder_terminate(c_utils_audio_decoder_t *decoder)
{
	if(!decoder)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_decoder_terminate, the decoder is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	ma_decoder_uninit(decoder);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_load_sound_from_decoder(c_utils_audio_engine_t *engine, c_utils_audio_decoder_t *decoder, c_utils_audio_sound_t *sound)
{
	if(!engine)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_load_sound_from_decoder, the engine is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!decoder)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_load_sound_from_decoder, the decoder is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!sound)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_load_sound_from_decoder, the sound is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const ma_result miniaudio_result = ma_sound_init_from_data_source(engine, decoder, 0, C_UTILS_NULL_POINTER, sound);

		if(miniaudio_result != MA_SUCCESS)
		{
			const c_utils_char_t *const description = ma_result_description(miniaudio_result);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_audio_load_sound_from_decoder, function ma_sound_init_from_data_source failed: ") + strlen(description) + strlen(", error code: ");
			c_utils_size_t error_size = 1u;
			signed int value = (signed int)miniaudio_result;

			if(value < 0)
			{
				value = -value;
				error_size++;
			}

			while(value >= 10)
			{
				value /= 10;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_audio_load_sound_from_decoder, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_audio_load_sound_from_decoder, function ma_sound_init_from_data_source failed: %s, error code: %d", description, (signed int)miniaudio_result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_device_start(c_utils_audio_device_t *device)
{
	if(!device)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_device_start, the device is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const ma_result miniaudio_result = ma_device_start(device);

		if(miniaudio_result != MA_SUCCESS)
		{
			const c_utils_char_t *const description = ma_result_description(miniaudio_result);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_audio_device_start, function ma_device_start failed: ") + strlen(description) + strlen(", error code: ");
			c_utils_size_t error_size = 1u;
			signed int value = (signed int)miniaudio_result;

			if(value < 0)
			{
				value = -value;
				error_size++;
			}

			while(value >= 10)
			{
				value /= 10;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_audio_device_start, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_audio_device_start, function ma_device_start failed: %s, error code: %d", description, (signed int)miniaudio_result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_device_stop(c_utils_audio_device_t *device)
{
	if(!device)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_device_stop, the device is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const ma_result miniaudio_result = ma_device_stop(device);

		if(miniaudio_result != MA_SUCCESS)
		{
			const c_utils_char_t *const description = ma_result_description(miniaudio_result);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_audio_device_stop, function ma_device_stop failed: ") + strlen(description) + strlen(", error code: ");
			c_utils_size_t error_size = 1u;
			signed int value = (signed int)miniaudio_result;

			if(value < 0)
			{
				value = -value;
				error_size++;
			}

			while(value >= 10)
			{
				value /= 10;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_audio_device_stop, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_audio_device_stop, function ma_device_stop failed: %s, error code: %d", description, (signed int)miniaudio_result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_device_terminate(c_utils_audio_device_t *device)
{
	if(!device)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_device_terminate, the device is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	ma_device_uninit(device);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_encoder_initialize_file(const c_utils_char_t *const path, c_utils_uint32_t sample_rate, c_utils_uint32_t channels,  c_utils_audio_encoder_t *encoder)
{
	if(!path)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_encoder_initialize_file, the path is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!encoder)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_encoder_initialize_file, the encoder is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const ma_encoder_config encoder_config = ma_encoder_config_init(ma_encoding_format_wav, ma_format_s16, channels, sample_rate);
		const ma_result miniaudio_result = ma_encoder_init_file(path, &encoder_config, encoder);

		if(miniaudio_result != MA_SUCCESS)
		{
			const c_utils_char_t *const description = ma_result_description(miniaudio_result);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_audio_encoder_initialize_file, function ma_encoder_init_file failed: ") + strlen(description) + strlen(", error code: ");
			c_utils_size_t error_size = 1u;
			signed int value = (signed int)miniaudio_result;

			if(value < 0)
			{
				value = -value;
				error_size++;
			}

			while(value >= 10)
			{
				value /= 10;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_audio_encoder_initialize_file, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_audio_encoder_initialize_file, function ma_encoder_init_file failed: %s, error code: %d", description, (signed int)miniaudio_result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_encoder_terminate(c_utils_audio_encoder_t *encoder)
{
	if(!encoder)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_encoder_terminate, the encoder is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	ma_encoder_uninit(encoder);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_capture_device_initialize_for_encoder(const c_utils_audio_device_id_t *device_id, c_utils_uint32_t sample_rate, c_utils_uint32_t channels, c_utils_audio_encoder_t *encoder, c_utils_audio_device_t *device)
{
	if(!encoder)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_capture_device_initialize_for_encoder, the encoder is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!device)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_capture_device_initialize_for_encoder, the device is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		ma_device_config deviceConfig = ma_device_config_init(ma_device_type_capture);
		ma_result miniaudio_result;
		deviceConfig.capture.pDeviceID = device_id;
		deviceConfig.capture.format = ma_format_s16;
		deviceConfig.capture.channels = channels;
		deviceConfig.sampleRate = sample_rate;
		deviceConfig.dataCallback = c_utils_audio_capture_file_callback;
		deviceConfig.pUserData = encoder;

		miniaudio_result = ma_device_init(C_UTILS_NULL_POINTER, &deviceConfig, device);

		if(miniaudio_result != MA_SUCCESS)
		{
			const c_utils_char_t *const description = ma_result_description(miniaudio_result);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_audio_capture_device_initialize_for_encoder, function ma_device_init failed: ") + strlen(description) + strlen(", error code: ");
			c_utils_size_t error_size = 1u;
			signed int value = (signed int)miniaudio_result;

			if(value < 0)
			{
				value = -value;
				error_size++;
			}

			while(value >= 10)
			{
				value /= 10;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_audio_capture_device_initialize_for_encoder, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_audio_capture_device_initialize_for_encoder, function ma_device_init failed: %s, error code: %d", description, (signed int)miniaudio_result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_capture_memory_initialize(c_utils_uint32_t channels, c_utils_audio_capture_memory_t *memory_context)
{
	if(!memory_context)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_capture_memory_initialize, the memory_context is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	memory_context->pcm_data = C_UTILS_NULL_POINTER;
	memory_context->capacity_frames = 0;
	memory_context->current_frames = 0;
	memory_context->channels = channels;
	memory_context->format_size = sizeof(c_utils_uint16_t);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_capture_memory_terminate(c_utils_audio_capture_memory_t *memory_context)
{
	if(!memory_context)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_capture_memory_terminate, the memory_context is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(memory_context->pcm_data)
	{
		free(memory_context->pcm_data);
		memory_context->pcm_data = C_UTILS_NULL_POINTER;
	}

	memory_context->capacity_frames = 0u;
	memory_context->current_frames = 0u;

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_capture_device_initialize_for_memory(const c_utils_audio_device_id_t *device_id, c_utils_uint32_t sample_rate, c_utils_uint32_t channels, c_utils_audio_capture_memory_t *memory_context, c_utils_audio_device_t *device)
{
	if(!memory_context)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_capture_device_initialize_for_memory, the memory_context is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!device)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_capture_device_initialize_for_memory, the device is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		ma_device_config deviceConfig = ma_device_config_init(ma_device_type_capture);
		ma_result miniaudio_result;
		deviceConfig.capture.pDeviceID = device_id;
		deviceConfig.capture.format = ma_format_s16;
		deviceConfig.capture.channels = channels;
		deviceConfig.sampleRate = sample_rate;
		deviceConfig.dataCallback = c_utils_audio_capture_memory_callback;
		deviceConfig.pUserData = memory_context;

		miniaudio_result = ma_device_init(C_UTILS_NULL_POINTER, &deviceConfig, device);

		if(miniaudio_result != MA_SUCCESS)
		{
			const c_utils_char_t *const description = ma_result_description(miniaudio_result);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_audio_capture_device_initialize_for_memory, function ma_device_init failed: ") + strlen(description) + strlen(", error code: ");
			c_utils_size_t error_size = 1u;
			signed int value = (signed int)miniaudio_result;

			if(value < 0)
			{
				value = -value;
				error_size++;
			}

			while(value >= 10)
			{
				value /= 10;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_audio_capture_device_initialize_for_memory, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_audio_capture_device_initialize_for_memory, function ma_device_init failed: %s, error code: %d", description, (signed int)miniaudio_result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}

		memory_context->channels = device->capture.channels;
		memory_context->format_size = ma_get_bytes_per_sample(device->capture.format);
		memory_context->current_frames = 0u;
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_set_fade_in_milliseconds(c_utils_audio_sound_t *sound, c_utils_float32_t volume_begin, c_utils_float32_t volume_end, c_utils_uint64_t milliseconds)
{
	if(!sound)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_sound_set_fade_in_milliseconds, the sound is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	ma_sound_set_fade_in_milliseconds(sound, volume_begin, volume_end, milliseconds);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_set_cone(c_utils_audio_sound_t *sound, c_utils_float32_t inner_angle_radians, c_utils_float32_t outer_angle_radians, c_utils_float32_t outer_gain)
{
	if(!sound)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_sound_set_cone, the sound is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	ma_sound_set_cone(sound, inner_angle_radians, outer_angle_radians, outer_gain);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_context_initialize(c_utils_audio_context_t *context)
{
	if(!context)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_context_initialize, the context is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const ma_result miniaudio_result = ma_context_init(C_UTILS_NULL_POINTER, 0, C_UTILS_NULL_POINTER, context);

		if(miniaudio_result != MA_SUCCESS)
		{
			const c_utils_char_t *const description = ma_result_description(miniaudio_result);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_audio_context_initialize, function ma_context_init failed: ") + strlen(description) + strlen(", error code: ");
			c_utils_size_t error_size = 1u;
			signed int value = (signed int)miniaudio_result;

			if(value < 0)
			{
				value = -value;
				error_size++;
			}

			while(value >= 10)
			{
				value /= 10;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_audio_context_initialize, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_audio_context_initialize, function ma_context_init failed: %s, error code: %d", description, (signed int)miniaudio_result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_context_terminate(c_utils_audio_context_t *context)
{
	if(!context)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_context_terminate, the context is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	ma_context_uninit(context);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_get_capture_devices(c_utils_audio_context_t *context, c_utils_void_t *devices, c_utils_uint32_t *devices_count)
{
	if(!context)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_get_capture_devices, the context is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!devices)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_get_capture_devices, the devices is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!devices_count)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_get_capture_devices, the devices_count is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		c_utils_audio_device_info_t **type_devices = (c_utils_audio_device_info_t **)devices;
		const ma_result miniaudio_result = ma_context_get_devices
		(
			context,
			C_UTILS_NULL_POINTER,
			C_UTILS_NULL_POINTER,
			type_devices,
			devices_count
		);

		if(miniaudio_result != MA_SUCCESS)
		{
			const c_utils_char_t *const description = ma_result_description(miniaudio_result);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_audio_get_capture_devices, function ma_context_get_devices failed: ") + strlen(description) + strlen(", error code: ");
			c_utils_size_t error_size = 1u;
			signed int value = (signed int)miniaudio_result;

			if(value < 0)
			{
				value = -value;
				error_size++;
			}

			while(value >= 10)
			{
				value /= 10;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_audio_get_capture_devices, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_audio_get_capture_devices, function ma_context_get_devices failed: %s, error code: %d", description, (signed int)miniaudio_result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_engine_config_set_playback_device(c_utils_audio_engine_config_t *config, c_utils_audio_device_id_t *device_id)
{
	if(!config)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_engine_config_set_playback_device, the config is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!device_id)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_engine_config_set_playback_device, the device_id is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	config->pPlaybackDeviceID = device_id;

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_get_playback_devices(c_utils_audio_context_t *context, c_utils_void_t *devices, c_utils_uint32_t *devices_count)
{
	if(!context)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_get_playback_devices, the context is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!devices)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_get_playback_devices, the devices is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	if(!devices_count)
	{
		C_UTILS_REPORT_ERROR("Error in function c_utils_audio_get_playback_devices, the devices_count is a null pointer");

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		c_utils_audio_device_info_t **type_devices = (c_utils_audio_device_info_t **)devices;
		const ma_result miniaudio_result = ma_context_get_devices
		(
			context,
			type_devices,
			devices_count,
			C_UTILS_NULL_POINTER,
			C_UTILS_NULL_POINTER
		);

		if(miniaudio_result != MA_SUCCESS)
		{
			const c_utils_char_t *const description = ma_result_description(miniaudio_result);
			c_utils_char_t *error_buffer = C_UTILS_NULL_POINTER;
			c_utils_size_t prefix_size = strlen("Error in function c_utils_audio_get_playback_devices, function ma_context_get_devices failed: ") + strlen(description) + strlen(", error code: ");
			c_utils_size_t error_size = 1u;
			signed int value = (signed int)miniaudio_result;

			if(value < 0)
			{
				value = -value;
				error_size++;
			}

			while(value >= 10)
			{
				value /= 10;
				error_size++;
			}

			error_buffer = (c_utils_char_t *)malloc((prefix_size + error_size + 1u) * sizeof(*error_buffer));

			if(!error_buffer)
			{
				C_UTILS_REPORT_ERROR("Error in function c_utils_audio_get_playback_devices, function malloc failed");

				return C_UTILS_RESULT_FAILURE;
			}

			sprintf(error_buffer, "Error in function c_utils_audio_get_playback_devices, function ma_context_get_devices failed: %s, error code: %d", description, (signed int)miniaudio_result);

			C_UTILS_REPORT_ERROR(error_buffer);

			free((c_utils_void_t *)error_buffer);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

/*****************************/
/* End C to C++ importation: */
/*****************************/

#ifdef __cplusplus
}
#endif
