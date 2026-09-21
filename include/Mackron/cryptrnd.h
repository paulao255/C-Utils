#ifndef cryptorand_h
#define cryptorand_h

#ifdef __cplusplus
extern "C"
{
#endif

#if defined(_WIN32)
#define CRYPTORAND_WIN32
#elif defined(__linux__) || defined(__APPLE__) || defined(__DragonFly__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__ANDROID__)
#define CRYPTORAND_URANDOM
#elif defined(__OpenBSD__)
#define CRYPTORAND_ARC4RANDOM
#endif

#include <stddef.h>

typedef enum cryptorand_result
{
	CRYPTORAND_SUCCESS = 0,
	CRYPTORAND_ERROR = -1,
	CRYPTORAND_INVALID_ARGS = -2,
	CRYPTORAND_INVALID_OPERATION = -3,
	CRYPTORAND_TOO_BIG = -11,
	CRYPTORAND_NOT_IMPLEMENTED = -29
} cryptorand_result;

typedef void (*cryptorand_proc)(void);

typedef struct cryptorand
{
    struct
    {
#if defined(CRYPTORAND_WIN32)
        void* hBcryptDLL;   /* If set, using BCryptGenRandom() */
        cryptorand_proc BCryptOpenAlgorithmProvider;
        cryptorand_proc BCryptCloseAlgorithmProvider;
        cryptorand_proc BCryptGenRandom;
        void* hAlgorithm;   /* Used with BCryptGenRandom() */

        void* hAdvapiDLL;   /* If set, using CryptGenRandom() */
        cryptorand_proc CryptAcquireContextW;
        cryptorand_proc CryptReleaseContext;
        cryptorand_proc CryptGenRandom;
        void* hProvider;    /* Used with CryptGenRandom() */
    } win32;
#elif defined(CRYPTORAND_URANDOM)
        /*FILE**/ void* pFile;  /* The file handle returned by open(). */
    } urandom;
#elif defined(CRYPTORAND_ARC4RANDOM)
        int __unused;
    } arc4;
#endif
} cryptorand;

extern cryptorand_result cryptorand_init(cryptorand* pRNG);
extern void cryptorand_uninit(cryptorand* pRNG);
extern cryptorand_result cryptorand_generate(cryptorand* pRNG, void* pBufferOut, size_t byteCount);

#ifdef __cplusplus
}
#endif
#endif  /* cryptorand_h */

#if defined(CRYPTORAND_IMPLEMENTATION)
#ifndef cryptorand_c
#define cryptorand_c

#include <string.h>

#if defined(CRYPTORAND_WIN32)
#include <windows.h>    /* For LoadLibrary(). */

typedef LONG (WINAPI * CRYPTORAND_PFN_BCryptOpenAlgorithmProvider)(void** phAlgorithm, LPCWSTR pszAlgId, LPCWSTR pszImplementation, ULONG dwFlags);
typedef LONG (WINAPI * CRYPTORAND_PFN_BCryptCloseAlgorithmProvider)(void* hAlgorithm, ULONG dwFlags);
typedef LONG (WINAPI * CRYPTORAND_PFN_BCryptGenRandom)(void* hAlgorithm, unsigned char* pbBuffer, ULONG cbBuffer, ULONG dwFlags);

#define CRYPTORAND_BCRYPT_RNG_ALGORITHM L"RNG"


typedef BOOL (WINAPI * CRYPTORAND_PFN_CryptAcquireContextW)(void** phProv, LPCWSTR szContainer, LPCWSTR szProvider, DWORD dwProvType, DWORD dwFlags);
typedef BOOL (WINAPI * CRYPTORAND_PFN_CryptReleaseContext)(void* hProv, DWORD dwFlags);
typedef BOOL (WINAPI * CRYPTORAND_PFN_CryptGenRandom)(void* hProv, DWORD dwLen, BYTE* pbBuffer);

#define CRYPTORAND_PROV_RSA_FULL        1
#define CRYPTORAND_CRYPT_VERIFYCONTEXT  0xF0000000
#define CRYPTORAND_CRYPT_SILENT         0x00000040

static cryptorand_result cryptorand_init__win32(cryptorand* pRNG)
{
    /*
    We first need to try using BCrypt which is the most modern version. If this fails it might mean
    we're running on Windows XP in which case we'll fall back to CryptGenRandom().
    */
    memset(&pRNG->win32, 0, sizeof(*&pRNG->win32));
    {
        HMODULE hBcryptDLL;

        hBcryptDLL = LoadLibraryW(L"bcrypt.dll");
        if (hBcryptDLL != NULL) {
            pRNG->win32.hBcryptDLL                   = (void*)hBcryptDLL;
            pRNG->win32.BCryptOpenAlgorithmProvider  = (cryptorand_proc)GetProcAddress(hBcryptDLL, "BCryptOpenAlgorithmProvider");
            pRNG->win32.BCryptCloseAlgorithmProvider = (cryptorand_proc)GetProcAddress(hBcryptDLL, "BCryptCloseAlgorithmProvider");
            pRNG->win32.BCryptGenRandom              = (cryptorand_proc)GetProcAddress(hBcryptDLL, "BCryptGenRandom");

            if (pRNG->win32.BCryptOpenAlgorithmProvider != NULL && pRNG->win32.BCryptCloseAlgorithmProvider != NULL && pRNG->win32.BCryptGenRandom != NULL) {
                if (((CRYPTORAND_PFN_BCryptOpenAlgorithmProvider)pRNG->win32.BCryptOpenAlgorithmProvider)(&pRNG->win32.hAlgorithm, CRYPTORAND_BCRYPT_RNG_ALGORITHM, NULL, 0) == 0) {
                    return CRYPTORAND_SUCCESS;
                } else {
                    /* Failed to open provider. */
                }
            } else {
                /* Failed to retrieve function addresses.*/
            }
        } else {
            /* Failed to load DLL. */
        }
    }


    /* Getting here means we're falling back to the old method. */
    memset(&pRNG->win32, 0, sizeof(*&pRNG->win32));
    {
        HMODULE hAdvapiDLL;

        hAdvapiDLL = LoadLibraryW(L"advapi32.dll");
        if (hAdvapiDLL != NULL) {
            pRNG->win32.hAdvapiDLL           = (void*)hAdvapiDLL;
            pRNG->win32.CryptAcquireContextW = (cryptorand_proc)GetProcAddress(hAdvapiDLL, "CryptAcquireContextW");
            pRNG->win32.CryptReleaseContext  = (cryptorand_proc)GetProcAddress(hAdvapiDLL, "CryptReleaseContext");
            pRNG->win32.CryptGenRandom       = (cryptorand_proc)GetProcAddress(hAdvapiDLL, "CryptGenRandom");

            if (pRNG->win32.CryptAcquireContextW != NULL && pRNG->win32.CryptReleaseContext != NULL && pRNG->win32.CryptGenRandom != NULL) {
                if (((CRYPTORAND_PFN_CryptAcquireContextW)pRNG->win32.CryptAcquireContextW)(&pRNG->win32.hProvider, NULL, NULL, CRYPTORAND_PROV_RSA_FULL, CRYPTORAND_CRYPT_VERIFYCONTEXT | CRYPTORAND_CRYPT_SILENT)) {
                    return CRYPTORAND_SUCCESS;
                } else {
                    /* Failed to acquire context. */
                }
            } else {
                /* Failed to retrieve function addresses.*/
            }
        } else {
            /* Failed to load DLL. */
        }
    }


    /* Getting here means both BCryptGenRandom() and CryptGenRandom() are unusable. */
    memset(&pRNG->win32, 0, sizeof(*&pRNG->win32));

    return CRYPTORAND_ERROR;
}

static void cryptorand_uninit__win32(cryptorand* pRNG)
{
    if (pRNG->win32.hAlgorithm != NULL) {
        ((CRYPTORAND_PFN_BCryptCloseAlgorithmProvider)pRNG->win32.BCryptCloseAlgorithmProvider)(pRNG->win32.hAlgorithm, 0);
    } else if (pRNG->win32.hProvider != NULL) {
        ((CRYPTORAND_PFN_CryptReleaseContext)pRNG->win32.CryptReleaseContext)(pRNG->win32.hProvider, 0);
    }

    if (pRNG->win32.hBcryptDLL != NULL) {
        FreeLibrary((HMODULE)pRNG->win32.hBcryptDLL);
    }
    if (pRNG->win32.hAdvapiDLL != NULL) {
        FreeLibrary((HMODULE)pRNG->win32.hAdvapiDLL);
    }
}

static cryptorand_result cryptorand_generate__win32(cryptorand* pRNG, void* pBufferOut, size_t byteCount)
{
    if (byteCount > 0xFFFFFFFF) {
        return CRYPTORAND_TOO_BIG;  /* TODO: Maybe handle this better by running in a loop. */
    }

    if (pRNG->win32.hAlgorithm != NULL) {
        LONG result = ((CRYPTORAND_PFN_BCryptGenRandom)pRNG->win32.BCryptGenRandom)(pRNG->win32.hAlgorithm, (unsigned char*)pBufferOut, (ULONG)byteCount, 0);
        if (result != 0) {
            return CRYPTORAND_ERROR;
        }
    } else if (pRNG->win32.hProvider != NULL) {
        if (!((CRYPTORAND_PFN_CryptGenRandom)pRNG->win32.CryptGenRandom)(pRNG->win32.hProvider, (DWORD)byteCount, (unsigned char*)pBufferOut)) {
            return CRYPTORAND_ERROR;
        }
    }

    return CRYPTORAND_SUCCESS;
}
#endif

#if defined(CRYPTORAND_URANDOM)
#include <stdio.h>

static cryptorand_result cryptorand_init__urandom(cryptorand* pRNG)
{
    pRNG->urandom.pFile = fopen("/dev/urandom", "rb");

    if(!pRNG->urandom.pFile)
    {
        return CRYPTORAND_ERROR;
    }

    return CRYPTORAND_SUCCESS;
}

static cryptorand_result cryptorand_generate__urandom(cryptorand* pRNG, void* pBufferOut, size_t byteCount)
{
    size_t bytesRead;

    if(!pRNG->urandom.pFile)
    {
        return CRYPTORAND_INVALID_OPERATION;
    }

    bytesRead = fread(pBufferOut, 1u, byteCount, (FILE*)pRNG->urandom.pFile);

    if(bytesRead < byteCount)
    {
        return CRYPTORAND_ERROR;    /* Wasn't able to read all the data. Should never happen. */
    }

    return CRYPTORAND_SUCCESS;
}
#endif

#if defined(CRYPTORAND_ARC4RANDOM)
#include <stdlib.h>
#endif

extern cryptorand_result cryptorand_init(cryptorand* pRNG)
{
    cryptorand_result result;

    if(!pRNG)
    {
        return CRYPTORAND_INVALID_ARGS;
    }

    memset(pRNG, 0, sizeof(*pRNG));

    result =
#if defined(CRYPTORAND_WIN32)
    cryptorand_init__win32(pRNG);
#elif defined(CRYPTORAND_URANDOM)
    cryptorand_init__urandom(pRNG);
#elif defined(CRYPTORAND_ARC4RANDOM)
    CRYPTORAND_SUCCESS;
#else
    CRYPTORAND_NOT_IMPLEMENTED;
#endif

    if(result != CRYPTORAND_SUCCESS)
    {
	memset(pRNG, 0, sizeof(*pRNG));
    }

    return result;
}

extern void cryptorand_uninit(cryptorand* pRNG)
{
    if(!pRNG)
    {
        return;
    }

#if defined(CRYPTORAND_WIN32)
    cryptorand_uninit__win32(pRNG);
#elif defined(CRYPTORAND_URANDOM)
    if(!pRNG->urandom.pFile);

    else
    {
	fclose((FILE*)pRNG->urandom.pFile);
    }
#elif defined(CRYPTORAND_ARC4RANDOM)
#endif

    memset(pRNG, 0, sizeof(*pRNG));
}

extern cryptorand_result cryptorand_generate(cryptorand* pRNG, void* pBufferOut, size_t byteCount)
{
    cryptorand_result result;

    if(!pRNG || !pBufferOut)
    {
        return CRYPTORAND_INVALID_ARGS;
    }

    result = 
#if defined(CRYPTORAND_WIN32)
    cryptorand_generate__win32(pRNG, pBufferOut, byteCount);
#elif defined(CRYPTORAND_URANDOM)
    cryptorand_generate__urandom(pRNG, pBufferOut, byteCount);
#elif defined(CRYPTORAND_ARC4RANDOM)
    CRYPTORAND_SUCCESS;
    acr4random_buf(pBufferOut, byteCount);
#else
    CRYPTORAND_NOT_IMPLEMENTED;
#endif

    if(result != CRYPTORAND_SUCCESS)
    {
	memset(pBufferOut, 0, byteCount);
    }

    return result;
}

#endif  /* cryptorand_c */
#endif  /* CRYPTORAND_IMPLEMENTATION */
