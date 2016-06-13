#ifndef _AES_XTS_H
#define _AES_XTS_H
#include <openssl/conf.h>
#include <openssl/opensslconf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include "qemu/error-report.h"

int sbs_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
  		unsigned char *iv, unsigned char *ciphertext, EVP_CIPHER_CTX *ctx,
		int sector_size);

int sbs_decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
  		unsigned char *iv, unsigned char *plaintext, EVP_CIPHER_CTX *ctx,
		int sector_size);

int sbs_init_decrypt_engine(EVP_CIPHER_CTX **ctx, unsigned char *key, unsigned char* iv);

int sbs_init_encrypt_engine(EVP_CIPHER_CTX **ctx, unsigned char *key, unsigned char* iv);

int sbs_del_crypto_engine(EVP_CIPHER_CTX *ctx);
#endif
