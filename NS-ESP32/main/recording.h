#ifndef recording_h
#define recording_h

#include "main.h"
#include "esp_spi_flash.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_partition.h"
#include "driver/i2s.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "soc/syscon_reg.h"
#include "soc/syscon_struct.h"

void configure_i2s(void);
void recording(void);



#endif