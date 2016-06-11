#include "aes_xts.h"

void error_handler(void)
{
	ERR_print_errors_fp(stderr);
	abort();
}

static int _sbs_encrypt(EVP_CIPHER_CTX *ctx,unsigned char *ciphertext, unsigned char *plaintext, int plaintext_len)
{
          int len = 0;
          int ciphertext_len = 0;
          if(EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len) != 1)
                error_handler();

          ciphertext_len = len;

          if(EVP_EncryptFinal_ex(ctx, ciphertext + len, &len) != 1)
                error_handler();

          return ciphertext_len += len;


}

int sbs_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
  unsigned char *iv, unsigned char *ciphertext, EVP_CIPHER_CTX *ctx)
{
	  int offset = 0;
	  int len = 0;

          while (offset < plaintext_len) {
                len = _sbs_encrypt(ctx, ciphertext + offset , plaintext + offset, 512);
                offset += len;
          }
	  return offset;
}

static int _sbs_decrypt(EVP_CIPHER_CTX *ctx, unsigned char *ciphertext, int ciphertext_len, unsigned char *plaintext)
{
        int len = 0;
        int plaintext_len = 0;

        if(EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len) != 1)
                error_handler();

          plaintext_len = len;

          if(EVP_DecryptFinal_ex(ctx, plaintext + len, &len) != 1)
                 error_handler();

          return plaintext_len += len;


}

int sbs_decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
  unsigned char *iv, unsigned char *plaintext, EVP_CIPHER_CTX *ctx)
{
	  int offset = 0;
	  int len = 0;

	while (offset < ciphertext_len) {
                len = _sbs_decrypt(ctx, ciphertext + offset, 512, plaintext + offset );
                offset += len;
        }

          return offset;
}

int sbs_init_decrypt_engine(EVP_CIPHER_CTX **ctx, unsigned char *key, unsigned char* iv)
{
	EVP_CIPHER_CTX *tmp = EVP_CIPHER_CTX_new();
	if(!tmp)
		return -1;

	if(EVP_DecryptInit_ex(tmp, EVP_aes_256_xts(), NULL, key, iv) != 1)
		return -1;

	*ctx = tmp;
	return 0;
}

int sbs_init_encrypt_engine(EVP_CIPHER_CTX **ctx, unsigned char *key, unsigned char* iv)
{
	EVP_CIPHER_CTX *tmp = EVP_CIPHER_CTX_new();
	if(!tmp)
		return -1;

	if(EVP_EncryptInit_ex(tmp, EVP_aes_256_xts(), NULL, key, iv) != 1)
		return -1;

	*ctx = tmp;
	return 0;
}

int sbs_del_crypto_engine(EVP_CIPHER_CTX *ctx)
{
	EVP_CIPHER_CTX_free(ctx);
	return 0;
}
