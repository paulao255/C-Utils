/*************************/
/* Library importations: */
/*************************/

#ifndef C_UTILS_COMPILE
#include "../../include/C-Utils/aud-utls.h"
#else
#include "C-Utils/aud-utls.h"
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

	if(!pMem)
	{
		return;
	}

	else
	{
		c_utils_size_t frames_to_copy = frameCount;
		c_utils_size_t required_capacity = pMem->current_frames + frames_to_copy;

		if(required_capacity > pMem->capacity_frames)
		{
			c_utils_size_t new_capacity = pMem->capacity_frames == 0 ? 44100 : pMem->capacity_frames * 2;
			c_utils_void_t *new_data;

			while(new_capacity < required_capacity)
			{
				new_capacity *= 2;
			}

			new_data = realloc(pMem->pcm_data, new_capacity * pMem->channels * pMem->format_size);

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
	}

	(c_utils_void_t)pOutput;
	(c_utils_void_t)pInput;
}

C_UTILS_API c_utils_result_t c_utils_audio_engine_initialize(const c_utils_audio_engine_config_t *config, c_utils_audio_engine_t *engine)
{
	if(!config)
	{
		fprintf(stderr, "Error in function c_utils_audio_engine_initialize, the config is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!engine)
	{
		fprintf(stderr, "Error in function c_utils_audio_engine_initialize, the engine is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const ma_result miniaudio_result = ma_engine_init(config, engine);

		if(miniaudio_result != MA_SUCCESS)
		{
			fprintf(stderr, "Error: failed to initialize miniaudio: %s (Code: %d, File: %s, Line: %d)\n", ma_result_description(miniaudio_result), miniaudio_result, __FILE__, __LINE__);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_engine_terminate(c_utils_audio_engine_t *engine)
{
	if(!engine)
	{
		fprintf(stderr, "Error in function c_utils_audio_engine_terminate, the engine is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	ma_engine_uninit(engine);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_engine_config_initialize(c_utils_audio_engine_config_t *const output)
{
	if(!output)
	{
		fprintf(stderr, "Error in function c_utils_audio_engine_config_initialize, the output is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	*output = ma_engine_config_init();

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_load_sound(c_utils_audio_engine_t *engine, const char *const path, c_utils_audio_sound_t *sound)
{
	if(!engine)
	{
		fprintf(stderr, "Error in function c_utils_audio_load_sound, the engine is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!path)
	{
		fprintf(stderr, "Error in function c_utils_audio_load_sound, the path is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!sound)
	{
		fprintf(stderr, "Error in function c_utils_audio_load_sound, the sound is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const ma_result miniaudio_result = ma_sound_init_from_file(engine, path, 0, C_UTILS_NULL_POINTER, C_UTILS_NULL_POINTER, sound);

		if(miniaudio_result != MA_SUCCESS)
		{
			fprintf(stderr, "Error: failed to load sound: %s (Code: %d, File: %s, Line: %d)\n", ma_result_description(miniaudio_result), miniaudio_result, __FILE__, __LINE__);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_unload_sound(c_utils_audio_sound_t *sound)
{
	if(!sound)
	{
		fprintf(stderr, "Error in function c_utils_audio_unload_sound, the sound is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	ma_sound_uninit(sound);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_start_sound(c_utils_audio_sound_t *sound)
{
	if(!sound)
	{
		fprintf(stderr, "Error in function c_utils_audio_start_sound, the sound is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const ma_result miniaudio_result = ma_sound_start(sound);

		if(miniaudio_result != MA_SUCCESS)
		{
			fprintf(stderr, "Error: failed to start sound: %s (Code: %d, File: %s, Line: %d)\n", ma_result_description(miniaudio_result), miniaudio_result, __FILE__, __LINE__);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_stop_sound(c_utils_audio_sound_t *sound)
{
	if(!sound)
	{
		fprintf(stderr, "Error in function c_utils_audio_stop_sound, the sound is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const ma_result miniaudio_result = ma_sound_stop(sound);

		if(miniaudio_result != MA_SUCCESS)
		{
			fprintf(stderr, "Error: failed to stop sound: %s (Code: %d, File: %s, Line: %d)\n", ma_result_description(miniaudio_result), miniaudio_result, __FILE__, __LINE__);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_set_volume(c_utils_audio_sound_t *sound, c_utils_float32_t volume)
{
	if(!sound)
	{
		fprintf(stderr, "Error in function c_utils_audio_set_volume, the sound is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	ma_sound_set_volume(sound, volume);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_get_volume(c_utils_audio_sound_t *sound, c_utils_float32_t *const output)
{
	if(!sound)
	{
		fprintf(stderr, "Error in function c_utils_audio_get_volume, the sound is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!output)
	{
		fprintf(stderr, "Error in function c_utils_audio_get_volume, the output is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	*output = ma_sound_get_volume(sound);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_seek_to_pcm_frame(c_utils_audio_sound_t *sound, c_utils_uint64_t position)
{
	if(!sound)
	{
		fprintf(stderr, "Error in function c_utils_audio_sound_seek_to_pcm_frame, the sound is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const ma_result miniaudio_result = ma_sound_seek_to_pcm_frame(sound, (ma_uint64)position);

		if(miniaudio_result != MA_SUCCESS)
		{
			fprintf(stderr, "Error: failed to seek to pcm frame: %s (Code: %d, File: %s, Line: %d)\n", ma_result_description(miniaudio_result), miniaudio_result, __FILE__, __LINE__);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_get_cursor_in_pcm_frames(c_utils_audio_sound_t *sound, c_utils_uint64_t *output)
{
	if(!sound)
	{
		fprintf(stderr, "Error in function c_utils_audio_get_cursor_in_pcm_frames, the sound is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!output)
	{
		fprintf(stderr, "Error in function c_utils_audio_get_cursor_in_pcm_frames, the output is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const ma_result miniaudio_result = ma_sound_get_cursor_in_pcm_frames(sound, (ma_uint64 *)output);

		if(miniaudio_result != MA_SUCCESS)
		{
			fprintf(stderr, "Error: failed to get cursor in pcm frames: %s (Code: %d, File: %s, Line: %d)\n", ma_result_description(miniaudio_result), miniaudio_result, __FILE__, __LINE__);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_set_looping(c_utils_audio_sound_t *sound, c_utils_bool_t looping)
{
	if(!sound)
	{
		fprintf(stderr, "Error in function c_utils_audio_sound_set_looping, the sound is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	ma_sound_set_looping(sound, (ma_bool32)looping);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_engine_listener_set_position(c_utils_audio_engine_t *engine, c_utils_uint32_t listener_index, c_utils_float32_t x, c_utils_float32_t y, c_utils_float32_t z)
{
	if(!engine)
	{
		fprintf(stderr, "Error in function c_utils_audio_engine_listener_set_position, the engine is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	ma_engine_listener_set_position(engine, (ma_uint32)listener_index, x, y, z);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_engine_listener_set_direction(c_utils_audio_engine_t *engine, c_utils_uint32_t listener_index, c_utils_float32_t x, c_utils_float32_t y, c_utils_float32_t z)
{
	if(!engine)
	{
		fprintf(stderr, "Error in function c_utils_audio_engine_listener_set_direction, the engine is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	ma_engine_listener_set_direction(engine, (ma_uint32)listener_index, x, y, z);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_engine_listener_set_velocity(c_utils_audio_engine_t *engine, c_utils_uint32_t listener_index, c_utils_float32_t x, c_utils_float32_t y, c_utils_float32_t z)
{
	if(!engine)
	{
		fprintf(stderr, "Error in function c_utils_audio_engine_listener_set_velocity, the engine is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	ma_engine_listener_set_velocity(engine, (ma_uint32)listener_index, x, y, z);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_set_spatialization_enabled(c_utils_audio_sound_t *sound, c_utils_bool_t enabled)
{
	if(!sound)
	{
		fprintf(stderr, "Error in function c_utils_audio_sound_set_spatialization_enabled, the sound is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	ma_sound_set_spatialization_enabled(sound, (ma_bool32)enabled);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_set_position(c_utils_audio_sound_t *sound, c_utils_float32_t x, c_utils_float32_t y, c_utils_float32_t z)
{
	if(!sound)
	{
		fprintf(stderr, "Error in function c_utils_audio_sound_set_position, the sound is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	ma_sound_set_position(sound, x, y, z);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_set_direction(c_utils_audio_sound_t *sound, c_utils_float32_t x, c_utils_float32_t y, c_utils_float32_t z)
{
	if(!sound)
	{
		fprintf(stderr, "Error in function c_utils_audio_sound_set_direction, the sound is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	ma_sound_set_direction(sound, x, y, z);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_set_velocity(c_utils_audio_sound_t *sound, c_utils_float32_t x, c_utils_float32_t y, c_utils_float32_t z)
{
	if(!sound)
	{
		fprintf(stderr, "Error in function c_utils_audio_sound_set_velocity, the sound is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	ma_sound_set_velocity(sound, x, y, z);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_set_pitch(c_utils_audio_sound_t *sound, c_utils_float32_t pitch)
{
	if(!sound)
	{
		fprintf(stderr, "Error in function c_utils_audio_sound_set_pitch, the sound is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	ma_sound_set_pitch(sound, pitch);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_set_pan(c_utils_audio_sound_t *sound, c_utils_float32_t pan)
{
	if(!sound)
	{
		fprintf(stderr, "Error in function c_utils_audio_sound_set_pan, the sound is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	ma_sound_set_pan(sound, pan);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_is_playing(c_utils_audio_sound_t *sound, c_utils_bool_t *const output)
{
	if(!sound)
	{
		fprintf(stderr, "Error in function c_utils_audio_sound_is_playing, the sound is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!output)
	{
		fprintf(stderr, "Error in function c_utils_audio_sound_is_playing, the output is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	*output = (c_utils_bool_t)ma_sound_is_playing(sound);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_is_at_end(c_utils_audio_sound_t *sound, c_utils_bool_t *const output)
{
	if(!sound)
	{
		fprintf(stderr, "Error in function c_utils_audio_sound_is_at_end, the sound is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!output)
	{
		fprintf(stderr, "Error in function c_utils_audio_sound_is_at_end, the output is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	*output = (c_utils_bool_t)ma_sound_at_end(sound);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_get_length_in_pcm_frames(c_utils_audio_sound_t *sound, c_utils_uint64_t *const output)
{
	if(!sound)
	{
		fprintf(stderr, "Error in function c_utils_audio_sound_get_length_in_pcm_frames, the sound is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!output)
	{
		fprintf(stderr, "Error in function c_utils_audio_sound_get_length_in_pcm_frames, the output is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const ma_result miniaudio_result = ma_sound_get_length_in_pcm_frames(sound, (ma_uint64 *)output);

		if(miniaudio_result != MA_SUCCESS)
		{
			fprintf(stderr, "Error: failed to get length in pcm frames: %s (Code: %d, File: %s, Line: %d)\n", ma_result_description(miniaudio_result), miniaudio_result, __FILE__, __LINE__);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_group_initialize(c_utils_audio_engine_t *engine, c_utils_audio_sound_group_t *group)
{
	if(!engine)
	{
		fprintf(stderr, "Error in function c_utils_audio_sound_group_initialize, the engine is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!group)
	{
		fprintf(stderr, "Error in function c_utils_audio_sound_group_initialize, the group is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const ma_result miniaudio_result = ma_sound_group_init(engine, 0, C_UTILS_NULL_POINTER, group);

		if(miniaudio_result != MA_SUCCESS)
		{
			fprintf(stderr, "Error: failed to initialize sound group: %s (Code: %d, File: %s, Line: %d)\n", ma_result_description(miniaudio_result), miniaudio_result, __FILE__, __LINE__);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_group_terminate(c_utils_audio_sound_group_t *group)
{
	if(!group)
	{
		fprintf(stderr, "Error in function c_utils_audio_sound_group_terminate, the group is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	ma_sound_group_uninit(group);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_group_set_volume(c_utils_audio_sound_group_t *group, c_utils_float32_t volume)
{
	if(!group)
	{
		fprintf(stderr, "Error in function c_utils_audio_sound_group_set_volume, the group is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	ma_sound_group_set_volume(group, volume);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_load_sound_into_group(c_utils_audio_engine_t *engine, const char *const path, c_utils_audio_sound_group_t *group, c_utils_audio_sound_t *sound)
{
	if(!engine)
	{
		fprintf(stderr, "Error in function c_utils_audio_load_sound_into_group, the engine is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!path)
	{
		fprintf(stderr, "Error in function c_utils_audio_load_sound_into_group, the path is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!group)
	{
		fprintf(stderr, "Error in function c_utils_audio_load_sound_into_group, the group is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!sound)
	{
		fprintf(stderr, "Error in function c_utils_audio_load_sound_into_group, the sound is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const ma_result miniaudio_result = ma_sound_init_from_file(engine, path, 0, group, C_UTILS_NULL_POINTER, sound);

		if(miniaudio_result != MA_SUCCESS)
		{
			fprintf(stderr, "Error: failed to load sound: %s (Code: %d, File: %s, Line: %d)\n", ma_result_description(miniaudio_result), miniaudio_result, __FILE__, __LINE__);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_decoder_initialize_from_memory(const c_utils_void_t *data, c_utils_size_t data_size, c_utils_audio_decoder_t *decoder)
{
	if(!data)
	{
		fprintf(stderr, "Error in function c_utils_audio_decoder_initialize_from_memory, the data is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!data_size)
	{
		fprintf(stderr, "Error in function c_utils_audio_decoder_initialize_from_memory, the data_size is 0 (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!decoder)
	{
		fprintf(stderr, "Error in function c_utils_audio_decoder_initialize_from_memory, the decoder is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const ma_result miniaudio_result = ma_decoder_init_memory(data, (size_t)data_size, C_UTILS_NULL_POINTER, decoder);

		if(miniaudio_result != MA_SUCCESS)
		{
			fprintf(stderr, "Error: failed to initialize decoder: %s (Code: %d, File: %s, Line: %d)\n", ma_result_description(miniaudio_result), miniaudio_result, __FILE__, __LINE__);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_decoder_terminate(c_utils_audio_decoder_t *decoder)
{
	if(!decoder)
	{
		fprintf(stderr, "Error in function c_utils_audio_decoder_terminate, the decoder is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	ma_decoder_uninit(decoder);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_load_sound_from_decoder(c_utils_audio_engine_t *engine, c_utils_audio_decoder_t *decoder, c_utils_audio_sound_t *sound)
{
	if(!engine)
	{
		fprintf(stderr, "Error in function c_utils_audio_load_sound_from_decoder, the engine is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!decoder)
	{
		fprintf(stderr, "Error in function c_utils_audio_load_sound_from_decoder, the decoder is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!sound)
	{
		fprintf(stderr, "Error in function c_utils_audio_load_sound_from_decoder, the sound is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const ma_result miniaudio_result = ma_sound_init_from_data_source(engine, decoder, 0, C_UTILS_NULL_POINTER, sound);

		if(miniaudio_result != MA_SUCCESS)
		{
			fprintf(stderr, "Error: failed to load sound: %s (Code: %d, File: %s, Line: %d)\n", ma_result_description(miniaudio_result), miniaudio_result, __FILE__, __LINE__);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_device_start(c_utils_audio_device_t *device)
{
	if(!device)
	{
		fprintf(stderr, "Error in function c_utils_audio_device_start, the device is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const ma_result miniaudio_result = ma_device_start(device);

		if(miniaudio_result != MA_SUCCESS)
		{
			fprintf(stderr, "Error: failed to start device: %s (Code: %d, File: %s, Line: %d)\n", ma_result_description(miniaudio_result), miniaudio_result, __FILE__, __LINE__);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_device_stop(c_utils_audio_device_t *device)
{
	if(!device)
	{
		fprintf(stderr, "Error in function c_utils_audio_device_stop, the device is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const ma_result miniaudio_result = ma_device_stop(device);

		if(miniaudio_result != MA_SUCCESS)
		{
			fprintf(stderr, "Error: failed to stop device: %s (Code: %d, File: %s, Line: %d)\n", ma_result_description(miniaudio_result), miniaudio_result, __FILE__, __LINE__);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_device_terminate(c_utils_audio_device_t *device)
{
	if(!device)
	{
		fprintf(stderr, "Error in function c_utils_audio_device_terminate, the device is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	ma_device_uninit(device);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_encoder_initialize_file(const char *const path, c_utils_uint32_t sample_rate, c_utils_uint32_t channels,  c_utils_audio_encoder_t *encoder)
{
	if(!path)
	{
		fprintf(stderr, "Error in function c_utils_audio_encoder_initialize_file, the path is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!encoder)
	{
		fprintf(stderr, "Error in function c_utils_audio_encoder_initialize_file, the encoder is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		const ma_encoder_config encoder_config = ma_encoder_config_init(ma_encoding_format_wav, ma_format_s16, channels, sample_rate);
		const ma_result miniaudio_result = ma_encoder_init_file(path, &encoder_config, encoder);

		if(miniaudio_result != MA_SUCCESS)
		{
			fprintf(stderr, "Error: failed to initialize encoder: %s (Code: %d, File: %s, Line: %d)\n", ma_result_description(miniaudio_result), miniaudio_result, __FILE__, __LINE__);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_encoder_terminate(c_utils_audio_encoder_t *encoder)
{
	if(!encoder)
	{
		fprintf(stderr, "Error in function c_utils_audio_encoder_terminate, the encoder is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	ma_encoder_uninit(encoder);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_capture_device_initialize_for_encoder(c_utils_uint32_t sample_rate, c_utils_uint32_t channels, c_utils_audio_encoder_t *encoder, c_utils_audio_device_t *device)
{
	if(!encoder)
	{
		fprintf(stderr, "Error in function c_utils_audio_capture_device_initialize_for_encoder, the encoder is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!device)
	{
		fprintf(stderr, "Error in function c_utils_audio_capture_device_initialize_for_encoder, the device is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		ma_device_config deviceConfig = ma_device_config_init(ma_device_type_capture);
		ma_result miniaudio_result;
		deviceConfig.capture.format = ma_format_s16;
		deviceConfig.capture.channels = channels;
		deviceConfig.sampleRate = sample_rate;
		deviceConfig.dataCallback = c_utils_audio_capture_file_callback;
		deviceConfig.pUserData = encoder;

		miniaudio_result = ma_device_init(C_UTILS_NULL_POINTER, &deviceConfig, device);

		if(miniaudio_result != MA_SUCCESS)
		{
			fprintf(stderr, "Error: failed to initialize device: %s (Code: %d, File: %s, Line: %d)\n", ma_result_description(miniaudio_result), miniaudio_result, __FILE__, __LINE__);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_capture_memory_initialize(c_utils_uint32_t channels, c_utils_audio_capture_memory_t *memory_context)
{
	if(!memory_context)
	{
		fprintf(stderr, "Error in function c_utils_audio_capture_memory_initialize, the memory context is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

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
		fprintf(stderr, "Error in function c_utils_audio_capture_memory_terminate, the memory context is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(memory_context->pcm_data)
	{
		free(memory_context->pcm_data);
		memory_context->pcm_data = C_UTILS_NULL_POINTER;
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_capture_device_initialize_for_memory(c_utils_uint32_t sample_rate, c_utils_uint32_t channels, c_utils_audio_capture_memory_t *memory_context, c_utils_audio_device_t *device)
{
	if(!memory_context)
	{
		fprintf(stderr, "Error in function c_utils_audio_capture_device_initialize_for_memory, the memory context is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	if(!device)
	{
		fprintf(stderr, "Error in function c_utils_audio_capture_device_initialize_for_memory, the device is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	else
	{
		ma_device_config deviceConfig = ma_device_config_init(ma_device_type_capture);
		ma_result miniaudio_result;
		deviceConfig.capture.format = ma_format_s16;
		deviceConfig.capture.channels = channels;
		deviceConfig.sampleRate = sample_rate;
		deviceConfig.dataCallback = c_utils_audio_capture_memory_callback;
		deviceConfig.pUserData = memory_context;

		miniaudio_result = ma_device_init(C_UTILS_NULL_POINTER, &deviceConfig, device);

		if(miniaudio_result != MA_SUCCESS)
		{
			fprintf(stderr, "Error: failed to initialize device: %s (Code: %d, File: %s, Line: %d)\n", ma_result_description(miniaudio_result), miniaudio_result, __FILE__, __LINE__);

			return C_UTILS_RESULT_FAILURE;
		}
	}

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_set_fade_in_milliseconds(c_utils_audio_sound_t *sound, c_utils_float32_t volume_begin, c_utils_float32_t volume_end, c_utils_uint64_t milliseconds)
{
	if(!sound)
	{
		fprintf(stderr, "Error in function c_utils_audio_sound_set_fade_in_milliseconds, the sound is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	ma_sound_set_fade_in_milliseconds(sound, volume_begin, volume_end, milliseconds);

	return C_UTILS_RESULT_SUCCESS;
}

C_UTILS_API c_utils_result_t c_utils_audio_sound_set_cone(c_utils_audio_sound_t *sound, c_utils_float32_t inner_angle_radians, c_utils_float32_t outer_angle_radians, c_utils_float32_t outer_gain)
{
	if(!sound)
	{
		fprintf(stderr, "Error in function c_utils_audio_sound_set_cone, the sound is a null pointer (File: %s, Line: %d)...\n", __FILE__, __LINE__);

		return C_UTILS_RESULT_FAILURE;
	}

	ma_sound_set_cone(sound, inner_angle_radians, outer_angle_radians, outer_gain);

	return C_UTILS_RESULT_SUCCESS;
}

/*****************************/
/* End C to C++ importation: */
/*****************************/

#ifdef __cplusplus
}
#endif
