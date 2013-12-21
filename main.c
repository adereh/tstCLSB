#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"


char ctmp[64];

void Delay_us(uint32_t us)
{
 uint32_t temp;
 SysTick->LOAD = us * 11;
 SysTick->VAL = 0x00;
 SysTick->CTRL = 0x01 ;
 do
 {
  temp=SysTick->CTRL;

 }while(temp&0x01&&!(temp&(1<<16)));
 SysTick->CTRL = 0x00;
 SysTick->VAL = 0X00;
}

void pin_blink(GPIO_TypeDef *aport, uint16_t apin, uint32_t adelay){
	uint32_t i;
	aport->ODR ^= apin;
	/* delay */
	for( i=0;i<adelay;i++);
	aport->ODR ^= apin;

}



int main(void)
{
uint32_t uid0,uid1,uid2;

uint32_t cdelay=0xA0000, fdelay=1000000;

	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	/* Configure the GPIO_LED pin */
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|
			GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|
			GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_12|
			GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Port A */
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|
			GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|
			GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* MCO output pin */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	RCC_MCOConfig(RCC_MCO_PLLCLK_Div2);
	//RCC_MCOConfig(RCC_MCO_HSE);

	uid0=(uint32_t*)0x1FFFF7E8;
	uid1=(uint32_t*)0x1FFFF7E8+4;
	uid2=(uint32_t*)0x1FFFF7E8+8;

	//puts("Test started.\n");
	//printf("UID: %u-%u-%u",uid0,uid1,uid2);
	//SH_SendString(ctmp);



	    while (1)
	    {
	    	/* Toggle LEDs by functions ports */

	    	/*  Analog inputs */
	    	GPIO_WriteBit(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|
	    			GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7,Bit_SET);
	    	GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_SET);
	    	Delay_us(fdelay);
	    	GPIO_WriteBit(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|
	    			GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7,Bit_RESET);
	    	GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_RESET);

	    	/* Discreet outputs */
	    	GPIO_WriteBit(GPIOC,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|
	    		    			GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7,Bit_SET);
	    	Delay_us(fdelay);
	    	GPIO_WriteBit(GPIOC,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|
	    	    		    			GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7,Bit_RESET);

	    	/* Misc ouputs */
	    	GPIO_WriteBit(GPIOC,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11,Bit_SET);
	    	Delay_us(fdelay);
	    	GPIO_WriteBit(GPIOC,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11,Bit_RESET);

	    	/* RS driver */
	    	GPIO_WriteBit(GPIOA,GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12,Bit_SET);
	    	Delay_us(fdelay);
	    	GPIO_WriteBit(GPIOA,GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12,Bit_RESET);

	    	/* SPI interface */
	    	GPIO_WriteBit(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15,Bit_SET);
	    	Delay_us(fdelay);
	    	GPIO_WriteBit(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15,Bit_RESET);


	    	/* Blink LEDs by board side*/
	    	/* Toggle LEDs which connected to +5V side*/
	    	/* Toggle LEDs which connected to pin2*/
	    	pin_blink(GPIOA,GPIO_Pin_1,cdelay);
	    	/* Toggle LEDs which connected to pin3*/
	    	pin_blink(GPIOA,GPIO_Pin_2,cdelay);
	    	/* Toggle LEDs which connected to pin4*/
	    	pin_blink(GPIOA,GPIO_Pin_3,cdelay);
	    	/* Toggle LEDs which connected to pin5*/
	    	pin_blink(GPIOA,GPIO_Pin_4,cdelay);
	    	/* Toggle LEDs which connected to pin6*/
	    	pin_blink(GPIOA,GPIO_Pin_5,cdelay);
	    	/* Toggle LEDs which connected to pin7*/
	    	pin_blink(GPIOA,GPIO_Pin_6,cdelay);
	    	/* Toggle LEDs which connected to pin8*/
	    	pin_blink(GPIOA,GPIO_Pin_7,cdelay);
	    	/* Toggle LEDs which connected to pin9*/
	    	pin_blink(GPIOB,GPIO_Pin_0,cdelay);
	    	/* Toggle LEDs which connected to pin10*/
	    	pin_blink(GPIOB,GPIO_Pin_6,cdelay);
	    	/* Toggle LEDs which connected to pin11*/
	    	pin_blink(GPIOB,GPIO_Pin_7,cdelay);
	    	/* Toggle LEDs which connected to pin12*/
	    	pin_blink(GPIOB,GPIO_Pin_13,cdelay);
	    	/* Toggle LEDs which connected to pin13*/
	    	pin_blink(GPIOB,GPIO_Pin_15,cdelay);
	    	/* Toggle LEDs which connected to pin14*/
	    	pin_blink(GPIOB,GPIO_Pin_13,cdelay);
	    	/* Toggle LEDs which connected to pin15*/
	    	pin_blink(GPIOB,GPIO_Pin_12,cdelay);
	    	/* Toggle LEDs which connected to pin16*/
	    	pin_blink(GPIOC,GPIO_Pin_8,cdelay);
	    	/* Toggle LEDs which connected to pin17*/
	    	pin_blink(GPIOC,GPIO_Pin_9,cdelay);
	    	/* Toggle LEDs which connected to pin18*/
	    	pin_blink(GPIOC,GPIO_Pin_10,cdelay);
	    	/* Toggle LEDs which connected to pin19*/
	    	pin_blink(GPIOC,GPIO_Pin_11,cdelay);

	    	/* Toggle LEDs which connected to +3v3 side*/
	    	/* Toggle LEDs which connected to pin2*/
	    	pin_blink(GPIOA,GPIO_Pin_11,cdelay);
	    	/* Toggle LEDs which connected to pin3*/
	    	pin_blink(GPIOA,GPIO_Pin_12,cdelay);
	    	/* Toggle LEDs which connected to pin4*/
	    	pin_blink(GPIOA,GPIO_Pin_0,cdelay);
	    	/* Toggle LEDs which connected to pin5*/
	    	pin_blink(GPIOC,GPIO_Pin_0,cdelay);
	    	/* Toggle LEDs which connected to pin6*/
	    	pin_blink(GPIOC,GPIO_Pin_1,cdelay);
	    	/* Toggle LEDs which connected to pin7*/
	    	pin_blink(GPIOC,GPIO_Pin_2,cdelay);
	    	/* Toggle LEDs which connected to pin8*/
	    	pin_blink(GPIOC,GPIO_Pin_3,cdelay);
	    	/* Toggle LEDs which connected to pin9*/
	    	pin_blink(GPIOC,GPIO_Pin_4,cdelay);
	    	/* Toggle LEDs which connected to pin10*/
	    	pin_blink(GPIOC,GPIO_Pin_5,cdelay);
	    	/* Toggle LEDs which connected to pin11*/
	    	pin_blink(GPIOC,GPIO_Pin_6,cdelay);
	    	/* Toggle LEDs which connected to pin12*/
	    	pin_blink(GPIOC,GPIO_Pin_7,cdelay);
	    	/* Toggle LEDs which connected to pin13*/
	    	pin_blink(GPIOB,GPIO_Pin_5,cdelay);
	    	/* Toggle LEDs which connected to pin14*/
	    	pin_blink(GPIOA,GPIO_Pin_10,cdelay);
	    	/* Toggle LEDs which connected to pin15*/
	    	pin_blink(GPIOA,GPIO_Pin_9,cdelay);

	    }

}

