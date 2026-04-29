/*	Classic Bluetooth SPP Server Example

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
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_log.h"

#include "spp.h"

static const char *TAG = "MAIN";

QueueHandle_t xQueueSpp;
QueueHandle_t xQueueUart;

static void uart_task(void* pvParameters)
{
	ESP_LOGI(pcTaskGetName(NULL), "Start");
	CMD_t cmdBuf;

	while(1) {
		xQueueReceive(xQueueUart, &cmdBuf, portMAX_DELAY);
		ESP_LOGD(pcTaskGetName(NULL), "cmdBuf.length=%d", cmdBuf.length);
		ESP_LOG_BUFFER_HEXDUMP(pcTaskGetName(NULL), cmdBuf.payload, cmdBuf.length, ESP_LOG_DEBUG);
	} // end while
	vTaskDelete(NULL);
}

void spp_task(void* pvParameters);
void twai_receive_task(void * pvParameters);

void app_main(void)
{
	// Initialize NVS.
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK( ret );

	// Create Queue
	xQueueSpp = xQueueCreate( 10, sizeof(CMD_t) );
	configASSERT( xQueueSpp );
	xQueueUart = xQueueCreate( 10, sizeof(CMD_t) );
	configASSERT( xQueueUart );

	// Start tasks
	xTaskCreate(uart_task, "UART", 1024*4, NULL, 2, NULL);
	xTaskCreate(twai_receive_task, "TWAI", 1024*4, NULL, 2, NULL);
	xTaskCreate(spp_task, "SPP", 1024*4, NULL, 2, NULL);
}
