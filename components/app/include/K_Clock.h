
#pragma once
/**
 ******************************************************************************
 * @file           user.h
 * @description:   
 * @author:        
 * @date:          2022-10-16
 * @version:       v0.1
 * @history: 
 *    [version]   [date]       [author]       [description]
 *    v0.1   	    2022-10-16              create
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __K_CLOCK_H__
#define __K_CLOCK_H__



#ifdef __cplusplus
extern "C" {
#endif


#include "stdint.h"
#include "stdio.h"
#include <cstring>
#include "driver/timer.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "esp_timer.h"
#include "math.h"

#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_tls.h"
#include "esp_http_client.h"

#include "nvs_flash.h"
#include "esp_sntp.h"
#include "button.h"

#include "esp_netif.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "DendoStepper.h"
#include "cJSON.h"
/* Includes ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/*


{
  "results": [
    {
      "location": {
        "id": "C23NB62W20TF",
        "name": "����ͼ",
        "country": "US",
        "path": "����ͼ,��ʢ����,����",
        "timezone": "America/Los_Angeles",
        "timezone_offset": "-07:00"
      },
      "now": {
        "text": "����", //������������
        "code": "4", //�����������
        "temperature": "14", //�¶ȣ���λΪc���϶Ȼ�f���϶�
        "feels_like": "14", //����¶ȣ���λΪc���϶Ȼ�f���϶�
        "pressure": "1018", //��ѹ����λΪmb������inӢ��
        "humidity": "76", //���ʪ�ȣ�0~100����λΪ�ٷֱ�
        "visibility": "16.09", //�ܼ��ȣ���λΪkm�����miӢ��
        "wind_direction": "����", //��������
        "wind_direction_degree": "340", //����Ƕȣ���Χ0~360��0Ϊ������90Ϊ������180Ϊ���ϣ�270Ϊ����
        "wind_speed": "8.05", //���٣���λΪkm/h����ÿСʱ��mphӢ��ÿСʱ
        "wind_scale": "2", //�����ȼ�����ο���http://baike.baidu.com/view/465076.htm
        "clouds": "90", //��������λ%����Χ0~100����ձ��Ƹ��ǵİٷֱ� #Ŀǰ��֧���й�����#
        "dew_point": "-12" //¶���¶ȣ���ο���http://baike.baidu.com/view/118348.htm #Ŀǰ��֧���й�����#
      },
      "last_update": "2015-09-25T22:45:00-07:00" //���ݸ���ʱ�䣨�ó��еı���ʱ�䣩
    }
  ]
}

*/

enum weatherCode_t
{
    SUNNY = 0,
    CLOUDY,
    OVERCAST,
    SHOWER,
    THUNDERSHOWER,
    LIGHT_RAIN,
    MODERATE_RAIN,
    HEAVY_RAIN,
    STORM,
    SLEET,
    LIGHT_SNOW,
    MODERATE_SNOW,
    HEAVY_SNOW,
    SNOWSTORM,
    FOGGY,
    HURRICANE,
    HAIL,
    FROST,
    DUSTSTORM,
    SEVERE_STORM,
    BLUSTERY,
    THOUNDER,
    TORNADO
};

typedef struct
{
  char name[20];
  char text[20];
  uint8_t code;
  int8_t temperature;
  uint8_t humidity;

} Weather_t;

/**
 * @brief Configuration structure
 */
typedef struct
{

   wifi_config_t wifiConfig;
   char* ntpUrl;
   char* userKey;
   char* location;
   
   gpio_num_t powerPin;
   uint8_t pages;
   uint16_t ntpInterval;
   uint16_t speed;
   uint16_t compensation;
   DendoStepper_config_t stepperConfig;
        
} Clock_config_t;


class K_clock
{
private:
  /* data */
  Clock_config_t conf;
  DendoStepper step1;

  void wifiConnect(void);
  void wifiConnect(uint8_t* ssid, uint8_t* password);


  static void sntpcallback(struct timeval *tv);
  static void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);
  static esp_err_t esp_event_handler(void *ctx, system_event_t *event);

public:

 
  K_clock();
  ~K_clock();

  void config(Clock_config_t *config);
  void init(void);
  esp_err_t sntpInit(void);
  void motorInit(void);

  uint8_t getTimeHour(void);
  uint8_t getTimeMin(void);
  uint8_t getTimeSec(void);

  uint8_t getWeatherCode(void);
  void weatherCodeParse(char* str, Weather_t* weather);
  uint8_t weatherCodeSwitch(uint8_t weatherCode);
  void setupdateFlag(uint8_t flag);
  uint8_t getupdateFlag(void);
  esp_err_t returnToZero(void);
  void runPages(int16_t value);
  void runPos(int16_t value);
  void runInf(int16_t value);
  void resetPos(void);
  void powerON(void);
  void powerOFF(void);
};


/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /*  */
