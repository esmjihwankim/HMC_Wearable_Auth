
#ifndef DETECTION_H
#define DETECTION_H

#include <stdbool.h>
#include <stdio.h>
#include "gpio_control.h"
#include "bluetooth.h"

typedef enum Pulsing_Status 
{
    OFF_STATE = 0, 
    ON_STATE = 1
}Pulsing_Status_t;



int get_automatic_pulsing_state(void);
void set_automatic_pulsing_state(Pulsing_Status_t input);

int sensor_detection(int u_val, int v_val, int w_val, int x_val, int y_val, int z_val); 

#endif