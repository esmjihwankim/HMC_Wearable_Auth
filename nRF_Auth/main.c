#include "main.h"


/**@brief Application main function.
 */
int main(void)
{
    ret_code_t err_code;

    bool erase_bonds;

    log_init();
    //err_code = ble_dfu_buttonless_async_svci_init();
    APP_ERROR_CHECK(err_code);

    gpio_init();
    uart_init();
    lfclk_config();
    timers_init();
    //buttons_leds_init(&erase_bonds);
    ble_stack_init();
    gap_params_init();
    gatt_init();
    services_init();
    advertising_init();

    nrf_crypto_init();

    // Advertising Strength selected 
    err_code = sd_ble_gap_tx_power_set(BLE_GAP_TX_POWER_ROLE_ADV, m_advertising.adv_handle, 0);
    APP_ERROR_CHECK(err_code);

    conn_params_init();

    saadc_sampling_event_init();
    saadc_init();
    saadc_sampling_event_enable();

    // Start execution.
    printf("\r\nUART started.\r\n");
    advertising_start();


    uint8_t rng_output[32]; 
    err_code = nrf_crypto_rng_vector_generate(rng_output, sizeof(rng_output));
    if (err_code == NRF_SUCCESS) {
        printf("RNG Test Passed. Random number generated.");
    } else {
        printf("RNG Test Failed. Error code: 0x%x", err_code);
    }
    
    generate_key_pair();
    



    // Enter main loop.
    for (;;)
    {
    }
}


/**
 * @}
 */