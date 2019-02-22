#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <mraa/types.h>

#include "common.h"
#include "arm/cosmic.h"
#include "arm/am335x.h"

#define PLATFORM_NAME_PHYBOARD_COSMIC "Phytec AM335x phyBOARD-cosmic"

mraa_board_t*
mraa_cosmic()
{
    mraa_board_t* b = (mraa_board_t*) calloc(1, sizeof(mraa_board_t));
    if (b == NULL) {
        return NULL;
    }
    b->platform_name = PLATFORM_NAME_PHYBOARD_COSMIC;
    b->phy_pin_count = MRAA_PHYBOARD_COSMIC_PINCOUNT;

    if (b->platform_name == NULL) {
        goto error;
    }

    b->pins = (mraa_pininfo_t*) calloc(b->phy_pin_count,sizeof(mraa_pininfo_t));
    if (b->pins == NULL) {
        goto error;
    }

    b->adv_func = (mraa_adv_func_t*) calloc(1, sizeof(mraa_adv_func_t));
    if (b->adv_func == NULL) {
        free(b->pins);
        goto error;
    }

    strncpy(b->pins[0].name, "INVALID", MRAA_PIN_NAME_SIZE);
    b->pins[0].capabilities = (mraa_pincapabilities_t){ 0, 0, 0, 0, 0, 0, 0, 0 };

    strncpy(b->pins[1].name, "VCC_5V0", MRAA_PIN_NAME_SIZE);
    b->pins[1].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 0, 0, 0, 0 };

    /* UART1  */
    strncpy(b->pins[35].name, "X_UART1_RXD", MRAA_PIN_NAME_SIZE);
    b->pins[35].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 0, 0, 0, 1 };
    b->pins[35].uart.mux_total = 0;

    strncpy(b->pins[37].name, "X_UART1_TXD", MRAA_PIN_NAME_SIZE);
    b->pins[37].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 0, 0, 0, 1 };
    b->pins[37].uart.mux_total = 0;
    /* UART2  */
    strncpy(b->pins[47].name, "X_UART2_RX", MRAA_PIN_NAME_SIZE);
    b->pins[47].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 0, 0, 0, 1 };
    b->pins[47].uart.mux_total = 0;

    strncpy(b->pins[49].name, "X_UART2_TXD", MRAA_PIN_NAME_SIZE);
    b->pins[49].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 0, 0, 0, 1 };
    b->pins[49].uart.mux_total = 0;
    /* UART3  */
    strncpy(b->pins[43].name, "X_UART3_RXD", MRAA_PIN_NAME_SIZE);
    b->pins[43].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 0, 0, 0, 1 };
    b->pins[43].uart.mux_total = 0;

    strncpy(b->pins[45].name, "X_UART3_TXD", MRAA_PIN_NAME_SIZE);
    b->pins[45].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 0, 0, 0, 1 };
    b->pins[45].uart.mux_total = 0;



    strncpy(b->pins[60].name, "GND", MRAA_PIN_NAME_SIZE);
    b->pins[60].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 0, 0, 0, 0 };


    /*on Board LEDS    D5 D4 D10 D11*/
    strncpy(b->pins[60+60+1].name, "X_GPIO3_7", MRAA_PIN_NAME_SIZE);
    b->pins[60+60+1].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 0, 0, 0 };
    b->pins[60+60+1].gpio.pinmap = (3*32 + 7);
    b->pins[60+60+1].gpio.parent_id = 0;
    b->pins[60+60+1].gpio.mux_total = 0;
    //   LED D10
    strncpy(b->pins[60+60+2].name, "X_GPIO1_27", MRAA_PIN_NAME_SIZE);
    b->pins[60+60+2].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 0, 0, 0 };
    b->pins[60+60+2].gpio.pinmap = (1*32 + 27);
    b->pins[60+60+2].gpio.parent_id = 0;
    b->pins[60+60+2].gpio.mux_total = 0;
    // LED D4
    strncpy(b->pins[60+60+3].name, "X_GPIO1_26", MRAA_PIN_NAME_SIZE);
    b->pins[60+60+3].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 0, 0, 0 };
    b->pins[60+60+3].gpio.pinmap = (1*32 + 26);
    b->pins[60+60+3].gpio.parent_id = 0;
    b->pins[60+60+3].gpio.mux_total = 0;


    b->uart_dev_count = 4;
    b->def_uart_dev = 1;
    /*  UART0 is default console */
    b->uart_dev[0].rx = 0;
    b->uart_dev[0].tx = 0;
    b->uart_dev[0].device_path = "/dev/ttyO0";
    /*  TODO UART1,2,3  */
    b->uart_dev[1].rx = 35;
    b->uart_dev[1].tx = 37;
    b->uart_dev[1].device_path = "/dev/ttyO1";
    b->uart_dev[2].rx = 47;
    b->uart_dev[2].tx = 49;
    b->uart_dev[2].device_path = "/dev/ttyO2";
    b->uart_dev[3].rx = 43;
    b->uart_dev[3].tx = 45;
    b->uart_dev[3].device_path = "/dev/ttyO3";

    b->gpio_count = 0;
    int i;
    for (i = 0; i < b->phy_pin_count; i++) {
        if (b->pins[i].capabilities.gpio) {
            b->gpio_count++;
        }
    }
    return b;
error:
    syslog(LOG_CRIT, "phyboard: failed to initialize");
    free(b);

    return NULL;
};
