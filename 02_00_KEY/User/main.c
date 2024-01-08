#include 	"stm32f10x.h"
#include 	"bsp_led.h"
#include	"bsp_key.h"

int main(void) 
{
	LED_GPIO_Config( );
	KEY_GPIO_Config( );
	uint8_t led_status;
    led_status = 0;
    LED_B_TOGGLE;
	while (1) {
        if (Key_Scan(KEY1_GPIO_PORT, KEY1_GPIO_PIN) == KEY_PRESS) {	
            switch (led_status) {
                case LED_RED : {
                    LED_B_TOGGLE;
                    LED_R_TOGGLE;
                    break;
                }
                case LED_GREEN : {
                    LED_R_TOGGLE;
                    LED_G_TOGGLE;
                    break;
                }
                case LED_BLUE : {
                    LED_G_TOGGLE;
                    LED_B_TOGGLE;
                    break;
                }
                default :
                    break;
            }
            led_status++;
            led_status = led_status % 3;
        }  
	}	
}
