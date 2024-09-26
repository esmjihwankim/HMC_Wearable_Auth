#include "main.h"

//======================================== Print functions ========================================
//
// Utility functions used to print results generated in this examples.
//
static void print_array(uint8_t const * p_string, size_t size)
{
    #if NRF_LOG_ENABLED
    size_t i;
    NRF_LOG_RAW_INFO("    ");
    for(i = 0; i < size; i++)
    {
        NRF_LOG_RAW_INFO("%02x", p_string[i]);
    }
    #endif // NRF_LOG_ENABLED
}


static void print_hex(char const * p_msg, uint8_t const * p_data, size_t size)
{
    NRF_LOG_INFO(p_msg);
    print_array(p_data, size);
    NRF_LOG_RAW_INFO("\r\n");
}


#define DEMO_ERROR_CHECK(error)     \
do                                  \
{                                   \
    if (error != NRF_SUCCESS)       \
    {                               \
        NRF_LOG_ERROR("Error 0x%04X: %s", error, nrf_crypto_error_string_get(error));\
        APP_ERROR_CHECK(error);     \
    }                               \
} while(0)




//========================================= Example entry =========================================
//


/** @brief Function for initializing the nrf log module.
 */
static void log_init(void)
{
    ret_code_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);

    NRF_LOG_DEFAULT_BACKENDS_INIT();
}


void generate_ecc_key_pair() {
    ret_code_t err_code; 

    nrf_crypto_ecc_key_pair_generate_context_t keygen_context; 

    nrf_crypto_ecc_private_key_t private_key;
    nrf_crypto_ecc_public_key_t public_key; 

    const nrf_crypto_ecc_curve_info_t * p_curve_info = &g_nrf_crypto_ecc_secp256r1_curve_info;

    err_code = nrf_crypto_ecc_key_pair_generate(
        &keygen_context,
        p_curve_info,
        &private_key,
        &public_key
    );

    if (err_code == NRF_SUCCESS) { 
        NRF_LOG_INFO("Successfully created ECC key pair %s", private_key.key_secp256r1.key);
    } else {
        NRF_LOG_INFO("Failed to create ECC key pair: 0x%x", err_code);
    }
}


/** @brief Function for application main entry.
 */
int main(void)
{
    ret_code_t err_code = NRF_SUCCESS;

    log_init();

    NRF_LOG_INFO("Key example started.\r\n");

    err_code = nrf_mem_init();
    DEMO_ERROR_CHECK(err_code);

    err_code = nrf_crypto_init();
    DEMO_ERROR_CHECK(err_code);

    
    generate_ecc_key_pair();


    //alice_sign();  // Alice signs the message
    //bob_verify();  // Bob verifies the signature

    NRF_LOG_INFO("Key example executed successfully.");

    for (;;)
    {
    }
}


/** @}
 */
