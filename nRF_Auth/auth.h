
#ifndef _AUTH_H
#define _AUTH_H

#include <stdio.h>
#include "nrf_log.h"
#include "nrf_crypto.h"
#include "nrf_crypto_error.h"
#include "nrf_crypto_ecc.h" 
#include "mbedtls/base64.h"
#include "micro_ecc_backend_ecc.h"

extern char* csr_string;


void generate_csr(char* csr_string); 
ret_code_t verify_signed_certificate(const uint8_t* signed_cert, size_t signed_cert_len, const uint8_t* signature, size_t sig_len);



#endif