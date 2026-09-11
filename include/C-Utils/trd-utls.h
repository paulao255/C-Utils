/******************/
/* Include guard: */
/******************/

#ifndef C_UTILS_TRD_UTLS_H
#define C_UTILS_TRD_UTLS_H

/*************************/
/* Library importations: */
/*************************/

#include "defs.h"
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
#include <pthread.h>
#include <semaphore.h>
#else
#error "FATAL ERROR: !defined(_WIN32) && !defined(_WIN64) && !defined(__linux__) && !defined(__ANDROID__) && !defined(__APPLE__)."
#endif

/*****************/
/* Thread types: */
/*****************/

#if defined(_WIN32) || defined(_WIN64)
#define C_UTILS_THREAD_FUNCTION_T unsigned int __stdcall
#define C_UTILS_THREAD_FUNCTION_RETURN 0U
typedef HANDLE C_UTILS_THREAD_T;
typedef DWORD C_UTILS_THREAD_ID_T;
typedef CRITICAL_SECTION C_UTILS_MUTEX_T;
typedef CONDITION_VARIABLE C_UTILS_CONDITION_VARIABLE_T;
typedef SRWLOCK C_UTILS_RWLOCK_T;
typedef DWORD C_UTILS_TLS_KEY_T;
#elif defined(__linux__) || defined(__ANDROID__) || defined(__APPLE__)
#define C_UTILS_THREAD_FUNCTION_T c_utils_void_t *
#define C_UTILS_THREAD_FUNCTION_RETURN C_UTILS_NULL_POINTER
typedef pthread_t C_UTILS_THREAD_T;
typedef pthread_t C_UTILS_THREAD_ID_T;
typedef pthread_mutex_t C_UTILS_MUTEX_T;
typedef pthread_cond_t C_UTILS_CONDITION_VARIABLE_T;
typedef pthread_rwlock_t C_UTILS_RWLOCK_T;
typedef pthread_key_t C_UTILS_TLS_KEY_T;
#endif

/* C-Utils thread function type: */
#define c_utils_thread_function_t C_UTILS_THREAD_FUNCTION_T

/* C-Utils thread function return value: */
#define c_utils_thread_function_return C_UTILS_THREAD_FUNCTION_RETURN

/* C-Utils thread type: */
typedef C_UTILS_THREAD_T c_utils_thread_t;

/* C-Utils thread id type: */
typedef C_UTILS_THREAD_ID_T c_utils_thread_id_t;

/* C-Utils mutex type: */
typedef C_UTILS_MUTEX_T c_utils_mutex_t;

/* C-Utils condition variable type: */
typedef C_UTILS_CONDITION_VARIABLE_T c_utils_condition_variable_t;

/* C-Utils read/write lock type: */
typedef C_UTILS_RWLOCK_T c_utils_rwlock_t;

/* C-Utils thread local storage type: */
typedef C_UTILS_TLS_KEY_T c_utils_tls_key_t;

/* C-Utils thread function pointer type: */
typedef c_utils_void_t (*c_utils_task_function_pointer)(c_utils_void_t *arguments);

/* C-Utils semaphore type: */
struct c_utils_semaphore_t
{
	c_utils_mutex_t mutex;
	c_utils_condition_variable_t condition_variable;
	c_utils_uint32_t value;
};

/* C-Utils typedef semaphore type: */
typedef struct c_utils_semaphore_t c_utils_semaphore_t;

/* C-Utils thread arguments type: */
struct c_utils_thread_arguments_t
{
	c_utils_void_t *arguments;
	c_utils_int32_t exit_code;
};

/* C-Utils typedef thread arguments type: */
typedef struct c_utils_thread_arguments_t c_utils_thread_arguments_t;

/* C-Utils barrier type: */
struct c_utils_barrier_t
{
	c_utils_mutex_t mutex;
	c_utils_condition_variable_t condition_variable;
	c_utils_uint32_t total;
	c_utils_uint32_t count;
	c_utils_uint32_t cycle;
};

/* C-Utils typedef barrier type: */
typedef struct c_utils_barrier_t c_utils_barrier_t;

/* C-Utils task node type: */
struct c_utils_task_node_t
{
	c_utils_task_function_pointer function;
	c_utils_void_t *arguments;
	struct c_utils_task_node_t *next;
};

/* C-Utils typedef task node type: */
typedef struct c_utils_task_node_t c_utils_task_node_t;

/* C-Utils thread pool type: */
struct c_utils_thread_pool_t
{
	c_utils_mutex_t mutex;
	c_utils_condition_variable_t condition_has_tasks;
	c_utils_condition_variable_t condition_idle;
	c_utils_thread_t *threads;
	c_utils_size_t thread_count;
	c_utils_task_node_t *head;
	c_utils_task_node_t *tail;
	c_utils_size_t pending_tasks;
	c_utils_size_t active_tasks;
	c_utils_bool_t stop;
};

/* C-Utils typedef thread pool type: */
typedef struct c_utils_thread_pool_t c_utils_thread_pool_t;

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

/* Function to get the recommended thread count and return it to the output. */
C_UTILS_API c_utils_result_t c_utils_get_processor_count(c_utils_int32_t *const output);

/* Function to create a thread. */
C_UTILS_API c_utils_result_t c_utils_thread_create(c_utils_thread_t *const thread, c_utils_thread_function_t (*f)(c_utils_void_t *arguments), c_utils_void_t *arguments);

/* Function to join a thread. */
C_UTILS_API c_utils_result_t c_utils_thread_join(c_utils_thread_t thread);

/* Function to detach a thread. */
C_UTILS_API c_utils_result_t c_utils_thread_detach(c_utils_thread_t thread);

/* Function to get the current thread id. */
C_UTILS_API c_utils_result_t c_utils_thread_get_id(c_utils_thread_id_t *const thread);

/* Function to yield the current thread. */
C_UTILS_API c_utils_result_t c_utils_thread_yield(c_utils_void_t);

/* Function to exit the current thread. */
C_UTILS_API c_utils_void_t c_utils_thread_exit(const c_utils_int32_t exit_code, c_utils_thread_arguments_t *const arguments);

/* Function to create a mutex. */
C_UTILS_API c_utils_result_t c_utils_mutex_create(c_utils_mutex_t *const mutex);

/* Function to lock a mutex. */
C_UTILS_API c_utils_result_t c_utils_mutex_lock(c_utils_mutex_t *const mutex);

/* Function to try to lock a mutex. */
C_UTILS_API c_utils_result_t c_utils_mutex_trylock(c_utils_mutex_t *const mutex, c_utils_bool_t *const is_locked);

/* Function to unlock a mutex. */
C_UTILS_API c_utils_result_t c_utils_mutex_unlock(c_utils_mutex_t *const mutex);

/* Function to destroy a mutex. */
C_UTILS_API c_utils_result_t c_utils_mutex_destroy(c_utils_mutex_t *const mutex);

/* Function to create a condition variable. */
C_UTILS_API c_utils_result_t c_utils_condition_variable_create(c_utils_condition_variable_t *const condition_variable);

/* Function to wait on a condition variable. */
C_UTILS_API c_utils_result_t c_utils_condition_variable_wait(c_utils_condition_variable_t *const condition_variable, c_utils_mutex_t *const mutex);

/* Function to send a signal to a condition variable. */
C_UTILS_API c_utils_result_t c_utils_condition_variable_signal(c_utils_condition_variable_t *const condition_variable);

/* Function to broadcast a signal to a condition variable. */
C_UTILS_API c_utils_result_t c_utils_condition_variable_broadcast(c_utils_condition_variable_t *const condition_variable);

/* Function to destroy a condition variable. */
C_UTILS_API c_utils_result_t c_utils_condition_variable_destroy(c_utils_condition_variable_t *const condition_variable);

/* Function to create a semaphore. */
C_UTILS_API c_utils_result_t c_utils_semaphore_create(c_utils_semaphore_t *const semaphore, c_utils_uint32_t initial_value);

/* Function to wait on a semaphore. */
C_UTILS_API c_utils_result_t c_utils_semaphore_wait(c_utils_semaphore_t *const semaphore);

/* Function to post to a semaphore. */
C_UTILS_API c_utils_result_t c_utils_semaphore_post(c_utils_semaphore_t *const semaphore);

/* Function to destroy a semaphore. */
C_UTILS_API c_utils_result_t c_utils_semaphore_destroy(c_utils_semaphore_t *const semaphore);

/* Function to create a read-write lock. */
C_UTILS_API c_utils_result_t c_utils_rwlock_create(c_utils_rwlock_t *const rwlock);

/* Function to lock a read-write lock for reading. */
C_UTILS_API c_utils_result_t c_utils_rwlock_read_lock(c_utils_rwlock_t *const rwlock);

/* Function to lock a read-write lock for writing. */
C_UTILS_API c_utils_result_t c_utils_rwlock_write_lock(c_utils_rwlock_t *const rwlock);

/* Function to unlock a read-write lock. */
C_UTILS_API c_utils_result_t c_utils_rwlock_unlock(c_utils_rwlock_t *const rwlock, const c_utils_bool_t is_write_lock);

/* Function to destroy a read-write lock. */
C_UTILS_API c_utils_result_t c_utils_rwlock_destroy(c_utils_rwlock_t *const rwlock);

/* Function to create a thread-local storage. */
C_UTILS_API c_utils_result_t c_utils_tls_create(c_utils_tls_key_t *const key);

/* Function to set a value in thread-local storage. */
C_UTILS_API c_utils_result_t c_utils_tls_set(c_utils_tls_key_t key, c_utils_void_t *const value);

/* Function to get a value from thread-local storage. */
C_UTILS_API c_utils_result_t c_utils_tls_get(c_utils_tls_key_t key, c_utils_void_t *const output);

/* Function to destroy a thread-local storage key. */
C_UTILS_API c_utils_result_t c_utils_tls_destroy(c_utils_tls_key_t key);

/* Function to create a barrier. */
C_UTILS_API c_utils_result_t c_utils_barrier_create(c_utils_barrier_t *const barrier, c_utils_uint32_t count);

/* Function to wait on a barrier. */
C_UTILS_API c_utils_result_t c_utils_barrier_wait(c_utils_barrier_t *const barrier);

/* Function to destroy a barrier. */
C_UTILS_API c_utils_result_t c_utils_barrier_destroy(c_utils_barrier_t *const barrier);

/* Function to create a thread pool. */
C_UTILS_API c_utils_result_t c_utils_thread_pool_create(c_utils_thread_pool_t *const pool, c_utils_size_t thread_count);

/* Function to add a task to a thread pool. */
C_UTILS_API c_utils_result_t c_utils_thread_pool_add_task(c_utils_thread_pool_t *const pool, c_utils_task_function_pointer function, c_utils_void_t *arguments);

/* Function to wait on a thread pool. */
C_UTILS_API c_utils_result_t c_utils_thread_pool_wait(c_utils_thread_pool_t *const pool);

/* Function to clear a thread pool. */
C_UTILS_API c_utils_result_t c_utils_thread_pool_clear(c_utils_thread_pool_t *const pool);

/* Function to get the number of pending tasks in a thread pool. */
C_UTILS_API c_utils_result_t c_utils_thread_pool_get_pending_tasks(c_utils_thread_pool_t *const pool, c_utils_size_t *const output);

/* Function to get the number of active tasks in a thread pool. */
C_UTILS_API c_utils_result_t c_utils_thread_pool_get_active_tasks(c_utils_thread_pool_t *const pool, c_utils_size_t *const output);

/* Function to get the number of threads in a thread pool. */
C_UTILS_API c_utils_result_t c_utils_thread_pool_get_thread_count(c_utils_thread_pool_t *const pool, c_utils_size_t *const output);

/* Function to destroy a thread pool. */
C_UTILS_API c_utils_result_t c_utils_thread_pool_destroy(c_utils_thread_pool_t *const pool);

/*****************************/
/* End C to C++ importation: */
/*****************************/

#ifdef __cplusplus
}
#endif

/**************************/
/* End C_UTILS_TRD_UTLS_H */
/**************************/

#endif
