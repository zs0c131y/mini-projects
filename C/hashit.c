#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define MAX_INPUT_LENGTH 1024

void compute_md5(const unsigned char *input, size_t length, unsigned char *md5_hash, unsigned int *md_len)
{
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, EVP_md5(), NULL);
    EVP_DigestUpdate(ctx, input, length);
    EVP_DigestFinal_ex(ctx, md5_hash, md_len);
    EVP_MD_CTX_free(ctx);
}

void compute_sha1(const unsigned char *input, size_t length, unsigned char *sha1_hash, unsigned int *md_len)
{
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, EVP_sha1(), NULL);
    EVP_DigestUpdate(ctx, input, length);
    EVP_DigestFinal_ex(ctx, sha1_hash, md_len);
    EVP_MD_CTX_free(ctx);
}

void compute_sha256(const unsigned char *input, size_t length, unsigned char *sha256_hash, unsigned int *md_len)
{
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, EVP_sha256(), NULL);
    EVP_DigestUpdate(ctx, input, length);
    EVP_DigestFinal_ex(ctx, sha256_hash, md_len);
    EVP_MD_CTX_free(ctx);
}

void hash_string(const char *input)
{
    unsigned char md5_hash[EVP_MAX_MD_SIZE];
    unsigned char sha1_hash[EVP_MAX_MD_SIZE];
    unsigned char sha256_hash[EVP_MAX_MD_SIZE];
    unsigned int md_len;

    compute_md5((const unsigned char *)input, strlen(input), md5_hash, &md_len);
    printf("Input String: %s\n", input);
    printf("MD5 Hash: ");
    for (unsigned int i = 0; i < md_len; i++)
        printf("%02x", md5_hash[i]);
    printf("\n");

    compute_sha1((const unsigned char *)input, strlen(input), sha1_hash, &md_len);
    printf("SHA-1 Hash: ");
    for (unsigned int i = 0; i < md_len; i++)
        printf("%02x", sha1_hash[i]);
    printf("\n");

    compute_sha256((const unsigned char *)input, strlen(input), sha256_hash, &md_len);
    printf("SHA-256 Hash: ");
    for (unsigned int i = 0; i < md_len; i++)
        printf("%02x", sha256_hash[i]);
    printf("\n");
}

void hash_file(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    unsigned char md5_hash[EVP_MAX_MD_SIZE];
    unsigned char sha1_hash[EVP_MAX_MD_SIZE];
    unsigned char sha256_hash[EVP_MAX_MD_SIZE];
    unsigned int md_len;

    EVP_MD_CTX *md5_ctx = EVP_MD_CTX_new();
    EVP_MD_CTX *sha1_ctx = EVP_MD_CTX_new();
    EVP_MD_CTX *sha256_ctx = EVP_MD_CTX_new();

    EVP_DigestInit_ex(md5_ctx, EVP_md5(), NULL);
    EVP_DigestInit_ex(sha1_ctx, EVP_sha1(), NULL);
    EVP_DigestInit_ex(sha256_ctx, EVP_sha256(), NULL);

    unsigned char buffer[1024];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) != 0)
    {
        EVP_DigestUpdate(md5_ctx, buffer, bytes_read);
        EVP_DigestUpdate(sha1_ctx, buffer, bytes_read);
        EVP_DigestUpdate(sha256_ctx, buffer, bytes_read);
    }

    EVP_DigestFinal_ex(md5_ctx, md5_hash, &md_len);
    printf("Input File: %s\n", filename);
    printf("MD5 Hash: ");
    for (unsigned int i = 0; i < md_len; i++)
        printf("%02x", md5_hash[i]);
    printf("\n");

    EVP_DigestFinal_ex(sha1_ctx, sha1_hash, &md_len);
    printf("SHA-1 Hash: ");
    for (unsigned int i = 0; i < md_len; i++)
        printf("%02x", sha1_hash[i]);
    printf("\n");

    EVP_DigestFinal_ex(sha256_ctx, sha256_hash, &md_len);
    printf("SHA-256 Hash: ");
    for (unsigned int i = 0; i < md_len; i++)
        printf("%02x", sha256_hash[i]);
    printf("\n");

    EVP_MD_CTX_free(md5_ctx);
    EVP_MD_CTX_free(sha1_ctx);
    EVP_MD_CTX_free(sha256_ctx);
    fclose(file);
}

int main()
{
    char input[MAX_INPUT_LENGTH];
    char filename[MAX_INPUT_LENGTH];
    int choice;

    printf("1. Hash a string\n");
    printf("2. Hash a file\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        printf("Enter the string to hash: ");
        scanf("%s", input);
        hash_string(input);
        break;
    case 2:
        printf("Enter the filename to hash: ");
        scanf("%s", filename);
        hash_file(filename);
        break;
    default:
        printf("Invalid choice\n");
    }

    return 0;
}
