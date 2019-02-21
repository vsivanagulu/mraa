#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <mraa/types.h>

#include "common.h"
#include "arm/cosmic.h"
#include "arm/am335x.h"

#define PLATFORM_NAME_PHYBOARD_COSMIC "phyBOARD-cosmic"

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

