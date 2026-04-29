/*	TWAI Network receive Example

	This example code is in the Public Domain (or CC0 licensed, at your option.)

	Unless required by applicable law or agreed to in writing, this
	software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
	CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_err.h"
#include "esp_log.h"
#include "driver/twai.h" // Update from V4.2

#include "spp.h"

static const char *TAG = "TWAI_V5";

extern QueueHandle_t xQueueSpp;

static const twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

#if CONFIG_CAN_BITRATE_25
static const twai_timing_config_t t_config = TWAI_TIMING_CONFIG_25KBITS();
#define BITRATE "Bitrate is 25 Kbit/s"
#elif CONFIG_CAN_BITRATE_50
static const twai_timing_config_t t_config = TWAI_TIMING_CONFIG_50KBITS();
#define BITRATE "Bitrate is 50 Kbit/s"
#elif CONFIG_CAN_BITRATE_100
static const twai_timing_config_t t_config = TWAI_TIMING_CONFIG_100KBITS();
#define BITRATE "Bitrate is 100 Kbit/s"
#elif CONFIG_CAN_BITRATE_125
static const twai_timing_config_t t_config = TWAI_TIMING_CONFIG_125KBITS();
#define BITRATE "Bitrate is 125 Kbit/s"
#elif CONFIG_CAN_BITRATE_250
static const twai_timing_config_t t_config = TWAI_TIMING_CONFIG_250KBITS();
#define BITRATE "Bitrate is 250 Kbit/s"
#elif CONFIG_CAN_BITRATE_500
static const twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();
#define BITRATE "Bitrate is 500 Kbit/s"
#elif CONFIG_CAN_BITRATE_800
static const twai_timing_config_t t_config = TWAI_TIMING_CONFIG_800KBITS();
#define BITRATE "Bitrate is 800 Kbit/s"
#elif CONFIG_CAN_BITRATE_1000
static const twai_timing_config_t t_config = TWAI_TIMING_CONFIG_1MBITS();
#define BITRATE "Bitrate is 1 Mbit/s"
#endif

static const twai_general_config_t g_config =
	TWAI_GENERAL_CONFIG_DEFAULT(CONFIG_CTX_GPIO, CONFIG_CRX_GPIO, TWAI_MODE_NORMAL);

void twai_receive_task(void *arg)
{
	ESP_LOGI(TAG, "Start");
	ESP_ERROR_CHECK(twai_driver_install(&g_config, &t_config, &f_config));
	ESP_LOGI(TAG, "Driver installed");
	ESP_ERROR_CHECK(twai_start());
	ESP_LOGI(TAG, "Driver started");

	CMD_t cmdBuf;
	cmdBuf.taskHandle = xTaskGetCurrentTaskHandle();
	cmdBuf.spp_event_id = SPP_OUTPUT_EVT;
	char CRLF[3];
	CRLF[0] = 0x0d;
	CRLF[1] = 0x0a;
	CRLF[2] = 0x00;
	char work[128];

	while (1) {
		twai_message_t rx_msg;
		twai_receive(&rx_msg, portMAX_DELAY);
		ESP_LOGD(TAG, "twai_receive identifier=0x%"PRIx32" flags=0x%"PRIx32" extd=0x%x rtr=0x%x data_length_code=%d",
			rx_msg.identifier, rx_msg.flags, rx_msg.extd, rx_msg.rtr, rx_msg.data_length_code);

		int ext = rx_msg.extd;
		int rtr = rx_msg.rtr;

		if (ext == 0) {
			sprintf(work, "Standard ID: 0x%03"PRIx32"%*s", rx_msg.identifier, 5, "");
		} else {
			sprintf(work, "Extended ID: 0x%08"PRIx32, rx_msg.identifier);
		}
		strcpy((char *)cmdBuf.payload, work);
		sprintf(work, "  DLC: %d  Data: ", rx_msg.data_length_code);
		strcat((char *)cmdBuf.payload, work);

		if (rtr == 0) {
			for (int i = 0; i < rx_msg.data_length_code; i++) {
				sprintf(work, "0x%02x ", rx_msg.data[i]);
				strcat((char *)cmdBuf.payload, work);
			}
		} else {
			sprintf(work, "REMOTE REQUEST FRAME");
			strcat((char *)cmdBuf.payload, work);
		}
		strcat((char *)cmdBuf.payload, CRLF);
		printf("%s", cmdBuf.payload);
		cmdBuf.length = strlen((char *)cmdBuf.payload);
		ESP_LOGD(TAG, "[%.*s]", cmdBuf.length, cmdBuf.payload);

		if (xQueueSend(xQueueSpp, &cmdBuf, portMAX_DELAY) != pdPASS) {
			ESP_LOGE(TAG, "xQueueSend Fail");
			break;
		}
	} // end while

	ESP_ERROR_CHECK(twai_stop());
	ESP_ERROR_CHECK(twai_driver_uninstall());
	vTaskDelete(NULL);
}
