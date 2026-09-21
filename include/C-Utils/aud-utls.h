/******************/
/* Include guard: */
/******************/

#ifndef C_UTILS_AUD_UTLS_H
#define C_UTILS_AUD_UTLS_H

/*************************/
/* Library importations: */
/*************************/

#ifdef C_UTILS_ENABLE_INT64
#undef C_UTILS_ENABLE_INT64
#endif
#define C_UTILS_ENABLE_INT64
#include "defs.h"
#ifndef C_UTILS_COMPILE
#include "../../include/Mackron/miniaudi.h"
#else
#include "Mackron/miniaudi.h"
#endif

/*********************/
/* Type definitions: */
/*********************/

/* C-Utils audio engine config type: */
typedef ma_engine_config c_utils_audio_engine_config_t;

/* C-Utils audio engine type: */
typedef ma_engine c_utils_audio_engine_t;

/* C-Utils audio sound type: */
typedef ma_sound c_utils_audio_sound_t;

/* C-Utils audio decoder type: */
typedef ma_decoder c_utils_audio_decoder_t;

/* C-Utils audio sound group type: */
typedef ma_sound_group c_utils_audio_sound_group_t;

/* C-Utils audio device type: */
typedef ma_device c_utils_audio_device_t;

/* C-Utils audio encoder type: */
typedef ma_encoder c_utils_audio_encoder_t;

/* C-Utils audio context type: */
typedef ma_context c_utils_audio_context_t;

/* C-Utils audio device id type: */
typedef ma_device_id c_utils_audio_device_id_t;

/* C-Utils audio device info type: */
typedef ma_device_info c_utils_audio_device_info_t;

/* C-Utils audio capture memory struct: */
struct c_utils_audio_capture_memory_t
{
	c_utils_void_t *pcm_data;
	c_utils_size_t current_frames;
	c_utils_size_t capacity_frames;
	c_utils_uint32_t channels;
	c_utils_uint32_t format_size;
};

/* C-Utils typedef audio capture memory type: */
typedef struct c_utils_audio_capture_memory_t c_utils_audio_capture_memory_t;

/********************/
/* Import C to C++: */
/********************/

#ifdef __cplusplus
extern "C"
{
#endif

/*************************/
/* Functions prototypes: */
/*************************/

/* C-Utils audio engine initialize. */
C_UTILS_API c_utils_result_t c_utils_audio_engine_initialize(const c_utils_audio_engine_config_t *config, c_utils_audio_engine_t *engine);

/* C-Utils audio engine terminate. */
C_UTILS_API c_utils_result_t c_utils_audio_engine_terminate(c_utils_audio_engine_t *engine);

/* C-Utils audio engine config initialize. */
C_UTILS_API c_utils_result_t c_utils_audio_engine_config_initialize(c_utils_audio_engine_config_t *const output);

/* C-Utils audio load sound. */
C_UTILS_API c_utils_result_t c_utils_audio_load_sound(c_utils_audio_engine_t *engine, const char *const path, c_utils_audio_sound_t *sound);

/* C-Utils audio unload sound. */
C_UTILS_API c_utils_result_t c_utils_audio_unload_sound(c_utils_audio_sound_t *sound);

/* C-Utils audio start sound. */
C_UTILS_API c_utils_result_t c_utils_audio_start_sound(c_utils_audio_sound_t *sound);

/* C-Utils audio stop sound. */
C_UTILS_API c_utils_result_t c_utils_audio_stop_sound(c_utils_audio_sound_t *sound);

/* C-Utils audio set volume. */
C_UTILS_API c_utils_result_t c_utils_audio_set_volume(c_utils_audio_sound_t *sound, c_utils_float32_t volume);

/* C-Utils audio get volume. */
C_UTILS_API c_utils_result_t c_utils_audio_get_volume(c_utils_audio_sound_t *sound, c_utils_float32_t *const output);

/* C-Utils audio sound seek to pcm frame. */
C_UTILS_API c_utils_result_t c_utils_audio_sound_seek_to_pcm_frame(c_utils_audio_sound_t *sound, c_utils_uint64_t position);

/* C-Utils audio get cursor in pcm frames. */
C_UTILS_API c_utils_result_t c_utils_audio_get_cursor_in_pcm_frames(c_utils_audio_sound_t *sound, c_utils_uint64_t *output);

/* C-Utils audio sound set looping. */
C_UTILS_API c_utils_result_t c_utils_audio_sound_set_looping(c_utils_audio_sound_t *sound, c_utils_bool_t looping);

/* C-Utils audio engine listener set position. */
C_UTILS_API c_utils_result_t c_utils_audio_engine_listener_set_position(c_utils_audio_engine_t *engine, c_utils_uint32_t listener_index, c_utils_float32_t x, c_utils_float32_t y, c_utils_float32_t z);

/* C-Utils audio engine listener set direction. */
C_UTILS_API c_utils_result_t c_utils_audio_engine_listener_set_direction(c_utils_audio_engine_t *engine, c_utils_uint32_t listener_index, c_utils_float32_t x, c_utils_float32_t y, c_utils_float32_t z);

/* C-Utils audio engine listener set velocity. */
C_UTILS_API c_utils_result_t c_utils_audio_engine_listener_set_velocity(c_utils_audio_engine_t *engine, c_utils_uint32_t listener_index, c_utils_float32_t x, c_utils_float32_t y, c_utils_float32_t z);

/* C-Utils audio sound set spatialization enabled. */
C_UTILS_API c_utils_result_t c_utils_audio_sound_set_spatialization_enabled(c_utils_audio_sound_t *sound, c_utils_bool_t enabled);

/* C-Utils audio sound set position. */
C_UTILS_API c_utils_result_t c_utils_audio_sound_set_position(c_utils_audio_sound_t *sound, c_utils_float32_t x, c_utils_float32_t y, c_utils_float32_t z);

/* C-Utils audio sound set direction. */
C_UTILS_API c_utils_result_t c_utils_audio_sound_set_direction(c_utils_audio_sound_t *sound, c_utils_float32_t x, c_utils_float32_t y, c_utils_float32_t z);

/* C-Utils audio sound set velocity. */
C_UTILS_API c_utils_result_t c_utils_audio_sound_set_velocity(c_utils_audio_sound_t *sound, c_utils_float32_t x, c_utils_float32_t y, c_utils_float32_t z);

/* C-Utils audio sound set pitch. */
C_UTILS_API c_utils_result_t c_utils_audio_sound_set_pitch(c_utils_audio_sound_t *sound, c_utils_float32_t pitch);

/* C-Utils audio sound set pan. */
C_UTILS_API c_utils_result_t c_utils_audio_sound_set_pan(c_utils_audio_sound_t *sound, c_utils_float32_t pan);

/* C-Utils audio sound is playing. */
C_UTILS_API c_utils_result_t c_utils_audio_sound_is_playing(c_utils_audio_sound_t *sound, c_utils_bool_t *const output);

/* C-Utils audio sound is at end. */
C_UTILS_API c_utils_result_t c_utils_audio_sound_is_at_end(c_utils_audio_sound_t *sound, c_utils_bool_t *const output);

/* C-Utils audio sound get length in pcm frames. */
C_UTILS_API c_utils_result_t c_utils_audio_sound_get_length_in_pcm_frames(c_utils_audio_sound_t *sound, c_utils_uint64_t *const output);

/* C-Utils audio sound group initialize. */
C_UTILS_API c_utils_result_t c_utils_audio_sound_group_initialize(c_utils_audio_engine_t *engine, c_utils_audio_sound_group_t *group);

/* C-Utils audio sound group terminate. */
C_UTILS_API c_utils_result_t c_utils_audio_sound_group_terminate(c_utils_audio_sound_group_t *group);

/* C-Utils audio sound group set volume. */
C_UTILS_API c_utils_result_t c_utils_audio_sound_group_set_volume(c_utils_audio_sound_group_t *group, c_utils_float32_t volume);

/* C-Utils audio load sound into group. */
C_UTILS_API c_utils_result_t c_utils_audio_load_sound_into_group(c_utils_audio_engine_t *engine, const char *const path, c_utils_audio_sound_group_t *group, c_utils_audio_sound_t *sound);

/* C-Utils audio decoder initialize from memory. */
C_UTILS_API c_utils_result_t c_utils_audio_decoder_initialize_from_memory(const c_utils_void_t *data, c_utils_size_t data_size, c_utils_audio_decoder_t *decoder);

/* C-Utils audio decoder terminate. */
C_UTILS_API c_utils_result_t c_utils_audio_decoder_terminate(c_utils_audio_decoder_t *decoder);

/* C-Utils audio load sound from decoder. */
C_UTILS_API c_utils_result_t c_utils_audio_load_sound_from_decoder(c_utils_audio_engine_t *engine, c_utils_audio_decoder_t *decoder, c_utils_audio_sound_t *sound);

/* C-Utils audio device start. */
C_UTILS_API c_utils_result_t c_utils_audio_device_start(c_utils_audio_device_t *device);

/* C-Utils audio device stop. */
C_UTILS_API c_utils_result_t c_utils_audio_device_stop(c_utils_audio_device_t *device);

/* C-Utils audio device terminate. */
C_UTILS_API c_utils_result_t c_utils_audio_device_terminate(c_utils_audio_device_t *device);

/* C-Utils audio encoder initialize file. */
C_UTILS_API c_utils_result_t c_utils_audio_encoder_initialize_file(const char *const path, c_utils_uint32_t sample_rate, c_utils_uint32_t channels,  c_utils_audio_encoder_t *encoder);

/* C-Utils audio encoder terminate. */
C_UTILS_API c_utils_result_t c_utils_audio_encoder_terminate(c_utils_audio_encoder_t *encoder);

/* C-Utils audio capture device initialize for encoder. */
C_UTILS_API c_utils_result_t c_utils_audio_capture_device_initialize_for_encoder(const c_utils_audio_device_id_t *device_id, c_utils_uint32_t sample_rate, c_utils_uint32_t channels, c_utils_audio_encoder_t *encoder, c_utils_audio_device_t *device);

/* C-Utils audio capture memory initialize. */
C_UTILS_API c_utils_result_t c_utils_audio_capture_memory_initialize(c_utils_uint32_t channels, c_utils_audio_capture_memory_t *memory_context);

/* C-Utils audio capture memory terminate. */
C_UTILS_API c_utils_result_t c_utils_audio_capture_memory_terminate(c_utils_audio_capture_memory_t *memory_context);

/* C-Utils audio capture device initialize for memory. */
C_UTILS_API c_utils_result_t c_utils_audio_capture_device_initialize_for_memory(const c_utils_audio_device_id_t *device_id, c_utils_uint32_t sample_rate, c_utils_uint32_t channels, c_utils_audio_capture_memory_t *memory_context, c_utils_audio_device_t *device);

/* C-Utils audio sound set fade in milliseconds. */
C_UTILS_API c_utils_result_t c_utils_audio_sound_set_fade_in_milliseconds(c_utils_audio_sound_t *sound, c_utils_float32_t volume_begin, c_utils_float32_t volume_end, c_utils_uint64_t milliseconds);

/* C-Utils audio sound set cone. */
C_UTILS_API c_utils_result_t c_utils_audio_sound_set_cone(c_utils_audio_sound_t *sound, c_utils_float32_t inner_angle_radians, c_utils_float32_t outer_angle_radians, c_utils_float32_t outer_gain);

/* C-Utils audio context initialize. */
C_UTILS_API c_utils_result_t c_utils_audio_context_initialize(c_utils_audio_context_t *context);

/* C-Utils audio context terminate. */
C_UTILS_API c_utils_result_t c_utils_audio_context_terminate(c_utils_audio_context_t *context);

/* C-Utils audio get capture devices. */
C_UTILS_API c_utils_result_t c_utils_audio_get_capture_devices(c_utils_audio_context_t *context, c_utils_void_t *devices, c_utils_uint32_t *devices_count);

/* C-Utils audio engine config set playback device. */
C_UTILS_API c_utils_result_t c_utils_audio_engine_config_set_playback_device(c_utils_audio_engine_config_t *config, c_utils_audio_device_id_t *device_id);

/* C-Utils audio get playback devices. */
C_UTILS_API c_utils_result_t c_utils_audio_get_playback_devices(c_utils_audio_context_t *context, c_utils_void_t *devices, c_utils_uint32_t *devices_count);

/*****************************/
/* End C to C++ importation: */
/*****************************/

#ifdef __cplusplus
}
#endif

/***************************/
/* End C_UTILS_AUD_UTLS_H: */
/***************************/

#endif
