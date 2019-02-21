/*
 * Author: Sivanageswararao  <siva.v@phytec.in>
 * Based on include/arm/phyboard.h
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "mraa_internal.h"

#define MRAA_PHYBOARD_COSMIC_PINCOUNT 140

mraa_board_t * mraa_cosmic();

#ifdef __cplusplus
}
#endif
