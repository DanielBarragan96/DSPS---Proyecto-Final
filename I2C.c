/**
	\file
	\brief
		This is the source file for the I2C device driver.
		i.e., this is the application programming interface (API) for the GPIO peripheral.
	\author J. Alejandro Ávila & Daniel Barragán
	\date	30/10/2017
 */


//ver en el osciloscopio que al empezar baje la trama, y después ya empiece a transmitir
#include "I2C.h"

//baud being 187500 start 16 stop 21
void I2C_init(I2C_ChannelType channel, uint32 systemClock, uint32 baudRate)
{
	switch(channel)
	{
		case I2C_0:
			SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
			GPIO_clockGating(GPIO_B);
			/**configures both ptc1 and ptb18 in alt modes 3,4 respectively*/
			GPIO_pinControlRegisterType pinControlRegisterMux2 = GPIO_MUX2;
			GPIO_pinControlRegister(GPIO_B,BIT2,&pinControlRegisterMux2); //SCL
			GPIO_pinControlRegister(GPIO_B,BIT3,&pinControlRegisterMux2); //SDA

			uint32 BusClock = (systemClock/2);
			uint32 SCL = 0;
			I2C0->F |= I2C_F_MULT(2);
			uint8 mult = 4;
			SCL = BusClock/(baudRate*mult);
			uint8 ICR = 0x1c;//((SCL - 20)/2)+1;
			I2C0->F |= I2C_F_ICR(ICR);
			I2C0->C1 |= I2C_C1_IICEN_MASK;
			break;
		case I2C_1:
			break;
		case I2C_2:
			break;
		default:
			break;
	}
}

uint8 I2C_busy()
{
	if(0 == (I2C0->S & I2C_S_BUSY_MASK))
	{
		return 0;
	}else
		return 1;
}

void I2C_MST_OrSLV_Mode(I2C_MasterType MasterOrSlave)
{
	if(I2C_SLAVE == MasterOrSlave)
	{
		I2C0->C1 &= ~(I2C_C1_MST_MASK);
	}else
		I2C0->C1 |= I2C_C1_MST_MASK;
}

void I2C_TX_RX_Mode(I2C_TxType TxOrRx)
{
//	SRW en el I2C_S
	if(I2C_RX == TxOrRx)
	{
		I2C0->C1  &= ~(I2C_C1_TX_MASK);
	}else
		I2C0->C1 |= I2C_C1_TX_MASK;
}

void I2C_NACK(void)
{
	I2C0->C1 |= I2C_C1_TXAK_MASK;
	delay(1000);
}

void I2C_repeted_Start(void)
{
	I2C0->C1 |= I2C_C1_RSTA_MASK;
}

void I2C_write_Byte(uint8 data)
{

	I2C0->D = data;
	delay(1000);
}

uint8 I2C_read_Byte(void)
{
	return I2C0->D;
}

void I2C_wait(void)
{
	while(!(I2C0->S & I2C_S_IICIF_MASK))
	{
		;
		delay(1000);
	}
}

uint16 I2C_get_ACK(void)
{
	if(0 == (I2C0->S & I2C_S_RXAK_MASK))// 0 there was an ack
	{
		return 0;
	}else
		return 1;
}

void I2C_start(void)
{
	I2C_MST_OrSLV_Mode(I2C_MASTER);
	I2C_TX_RX_Mode(I2C_TX);
}

void I2C_stop(void)
{
	I2C0->C1 &= ~(I2C_C1_MST_MASK);
	I2C0->C1 &= ~(I2C_C1_TX_MASK);
	delay(20000);
}
