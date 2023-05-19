/**
 * @file common.h
 * @author Ali Nasrolahi (a.nasrolahi01@gmail.com)
 * @brief Generic functionalities to be used across projects.
 * @version 0.1
 * @date 2023-03-08
 *
 */

#include "esp_err.h"
#include "esp_log.h"
#include "sdkconfig.h"

#define DEFAULT_LOGGING_TAG CONFIG_EXAMPLE_LOGGING_TAG

/**
 * @brief Returns phy mode.
 */
#define PHY_MODE(_ap)                                                                              \
    (_ap)->phy_11n ? "802.11n"                                                                     \
                   : ((_ap)->phy_11g ? "802.11g" : ((_ap)->phy_11b ? "802.11b" : "UNKOWN"))

#define INFO(...) ESP_LOGI(DEFAULT_LOGGING_TAG, ##__VA_ARGS__)

#define DELAY(_t) vTaskDelay(_t)
#define DELAY_IN_SEC(_t) DELAY((_t)*100)
