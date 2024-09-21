#include "auth.h"


nrf_crypto_ecc_private_key_t private_key;
nrf_crypto_ecc_public_key_t public_key; 

const uint8_t root_ca_cert_der[] = {
  
};


void generate_key_pair() 
{
    // ECC key pair 
    nrf_crypto_ecc_key_pair_generate(
        NULL,
        &g_nrf_crypto_ecc_secp256r1_curve_info,
        &private_key,
        &public_key
    );

} 

void generate_csr(char* csr_string, const char* common_name, nrf_crypto_ecc_public_key_t* public_key) 
{
    // form CSR in PEM format 
    uint16_t bytes_to_send; 

    bytes_to_send = sprintf(csr_string,
                            "-----BEGIN CERTIFICATE REQUEST-----\nSubject: CN=%s\nPublic Key: %s\n-----END CERTIFICATE REQUEST-----\n",
                            common_name,
                            public_key);
}


ret_code_t verify_signed_certificate(const uint8_t* signed_cert, size_t signed_cert_len, const uint8_t* signature, size_t sig_len)
{
    ret_code_t err_code; 
    nrf_crypto_ecc_public_key_t root_ca_pub_key; 

    err_code = nrf_crypto_ecc_public_key_from_raw(
        &g_nrf_crypto_ecc_secp256r1_curve_info,
        &root_ca_pub_key,
        root_ca_cert_der,
        sizeof(root_ca_cert_der) 
    );

    if(err_code != NRF_SUCCESS) 
    {
        NRF_LOG_ERROR("Failed to load rootCA: 0x%x", err_code);
        return err_code; 
    }

    // perform verification 
    err_code = nrf_crypto_ecdsa_verify( 
        NULL,
        &root_ca_pub_key,    // rootCA public key 
        signed_cert,         // signed cert data (parsed from PEM) 
        signed_cert_len,     // 
        signature,
        sig_len
    );

    if(err_code == NRF_SUCCESS)
    {
        NRF_LOG_INFO("Cert verification successful"); 
    } 
    else 
    {
        NRF_LOG_ERROR("Cert verification failed 0x%x", err_code); 
    }
  
    return err_code;
}

