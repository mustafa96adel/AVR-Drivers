/*
 * ESP01_PROG.c
 *
 *  Created on: Mar 5, 2023
 *      Author: joseph
 */

#include "STD_TYPES.h"

#include "UART_INT.h"

#include "ESP01_PRIV.h"
#include "ESP01_TYPES.h"
#include "ESP01_CFG.h"
#include "ESP01_INT.h"
#include "LCD_cfg.h"
#include "LCD_int.h"
#include <avr\delay.h>

volatile u8 ESP01Buffer[100];
volatile u8 BufferCounter = 0;
extern volatile u8 global_ReceivedData;

volatile u8 CommandReceivedFlag = 0;

void ISR_ESP01()
{
	ESP01Buffer[BufferCounter] = global_ReceivedData;
	BufferCounter++;
	if(global_ReceivedData == 'K')
	{
		CommandReceivedFlag = 1;
	}
}

void ISR_ESP01_ReceiveData()
{
	ESP01Buffer[BufferCounter] = global_ReceivedData;
	BufferCounter++;
	/*if(global_ReceivedData == 'Q')
	{
		CommandReceivedFlag = 1;
	}*/
}

void H_ESP01_void_Init()
{
	M_UART_Inite(UART_BAUD_115200, UART_8BIT_MODE, UART_PARITY_DISABLED, UART_STOP_1BIT);
	M_UART_ReceiveByteAsynchCallBack(ISR_ESP01);
}

void H_ESP01_void_SendCommand(u8* Command)
{
	M_UART_SendString(Command);
}

void H_ESP01_DisplayBuffer()
{
	CommandReceivedFlag = 0;
	ESP01Buffer[BufferCounter] ='\0';
	H_LCD_void_sendCommand(LCD_CMD_CLEAR);
	H_LCD_void_sendString(ESP01Buffer);
	BufferCounter = 0;
	memset(ESP01Buffer, '\0', 100);
	_delay_ms(1000);
}

void H_ESP_void_SetModeStation()
{
	H_ESP01_void_SendCommand(AT_CURRENT_WIFI_STATION_MODE);
}

void H_ESP_EchoCancel()
{
	H_ESP01_void_SendCommand("ATE0\r\n");
	//Wait for response
	u16 TimeOut =0;
	while(CommandReceivedFlag == 0 && BufferCounter<6)
	{
//		if(TimeOut == 1000)
//			break;
//
//		TimeOut++;
	}
	H_ESP01_DisplayBuffer();
}

ESP01_Response_Status H_ESP_SetMode(ESP_Mode EspMode)
{
	u8 Command[50];
	sprintf(Command, "AT+CWMODE=%d\r\n", EspMode);
	for(u8 i=0; i<3; i++)
	{
		H_ESP01_void_SendCommand(Command);
		u16 TimeOut=0;
		while(CommandReceivedFlag == 0 && BufferCounter<6)
		{
//			if(TimeOut == 1000)
//				break;
//
//			TimeOut++;
		}
		if(strstr(ESP01Buffer, "OK") != NULL)
		{
			H_ESP01_DisplayBuffer();
			return RESPONSE_OK;
		}
		H_ESP01_DisplayBuffer();
	}
	return RESPONSE_ERROR;
}

ESP01_Response_Status H_ESP_ConnectToWifi(u8* WifiName, u8* WifiPassword)
{
	u8 Command[50];
	sprintf(Command, "AT+CWJAP=\"%s\",\"%s\"\r\n",WifiName, WifiPassword );
	for(u8 i=0; i<3; i++)
	{
		H_ESP01_void_SendCommand(Command);
		//H_ESP01_void_SendCommand("AT+CWJAP=\"WE_A04DA4\",\"Ae22523114\"\r\n");
		u16 TimeOut=0;
		while(CommandReceivedFlag == 0 && BufferCounter<6)
		{
//			if(TimeOut == 1000)
//				break;
//
//			TimeOut++;
		}
		if(strstr(ESP01Buffer, "OK") != NULL)
		{
			H_ESP01_DisplayBuffer();
			return RESPONSE_OK;
		}
		H_ESP01_DisplayBuffer();
	}
	return RESPONSE_ERROR;
}

ESP01_Response_Status H_ESP_void_InitializeTCP(u8* AddressIP, u16 PortNumber)
{
	u8 Command[50];
	sprintf(Command, "AT+CIPSTART=\"TCP\",\"%s\",%d\r\n",AddressIP ,PortNumber);
	for(u8 i=0; i<3; i++)
	{
		H_ESP01_void_SendCommand(Command);
		//H_ESP01_void_SendCommand("AT+CIPSTART=\"TCP\",\"10.204.24.181\",8080\r\n");
		//H_ESP01_void_SendCommand("AT+CIPSTART=\"TCP\",\"192.168.1.20\",8080\r\n");
		//while(/*ESP01Buffer[BufferCounter-1] != 'O' && */ESP01Buffer[BufferCounter-1] != 'K')
		u16 TimeOut =0;
		while(CommandReceivedFlag == 0 && BufferCounter<10)
		{
//			if(TimeOut == 1000)
//				break;
//
//			TimeOut++;
		}
		if(strstr(ESP01Buffer, "OK") != NULL)
		{
			H_ESP01_DisplayBuffer();
			return RESPONSE_OK;
		}
		H_ESP01_DisplayBuffer();
	}
	return RESPONSE_ERROR;

}

ESP01_Response_Status H_ESP_void_SendString(u8* String)
{
	u8 Command[50];
	u8 CommandLength = strlen(String);
	sprintf(Command, "AT+CIPSEND=%d\r\n",CommandLength);
	u8 Data[50];
	sprintf(Data, "%s\r\n", String);
	u8 FlagSuccess = 0;
	for(u8 i=0; i<3; i++)
	{
		H_ESP01_void_SendCommand(Command);
		_delay_ms(200);
		H_ESP01_void_SendCommand(Data);
		u16 TimeOut =0;
		while(CommandReceivedFlag == 0 && BufferCounter<8)
		{
//			if(TimeOut == 1000)
//				break;
//
//			TimeOut++;
		}
		if(strstr(ESP01Buffer, "OK") != NULL)
		{
			H_ESP01_DisplayBuffer();
			_delay_ms(100);
			return RESPONSE_OK;
		}
		H_ESP01_DisplayBuffer();
	}
	_delay_ms(100);
	return RESPONSE_ERROR;
}

void H_ESP_CIPMODE()
{

	u8 Command[] = "AT+CIPMODE=1\r\n";
	for(u8 i=0; i<3; i++)
	{
		H_ESP01_void_SendCommand(Command);
		while(CommandReceivedFlag == 0 && BufferCounter<10)
		{

		}
		if(strstr(ESP01Buffer, "OK") != NULL)
		{
			H_ESP01_DisplayBuffer();
			break;
		}
		H_ESP01_DisplayBuffer();
	}
}

void H_ESP_StartReceiveData()
{
	M_UART_ReceiveByteAsynchCallBack(ISR_ESP01_ReceiveData);
}

void H_ESP_void_SetModeStationSoftAP()
{
	H_ESP01_void_SendCommand(AT_CURRENT_WIFI_STATION_SOFTAP_MODE);
}

void H_ESP_void_SendByte(u8 Data)
{
	M_UART_SendByte(Data);
}

void H_ESP_void_ReceiveByteSynchNonBlocking(u8* Data, u16 TimeMicroSec)
{
	M_UART_ReceiveByteSynchNonBlocking(Data,TimeMicroSec);
}

void H_ESP_void_ReceiveByteAsynchCallBack(void(* CallBackFuncPtr)())
{
	M_UART_ReceiveByteAsynchCallBack(CallBackFuncPtr);
}

void H_ESP_void_ReceiveStringSynchNonBlocking(u8* OutputString, u8 StringLength, u8 EndChar, u16 TimeOutMMiliSec)
{
	M_UART_ReceiveStringSynchNonBlocking(OutputString, 20, EndChar, 1000000);
}

EPS01_Receive_Status H_ESP_CheckIfReceivedData()
{
	 if(strstr(ESP01Buffer, "+IPD") != NULL)
	 {
		 return RECEIVED_DONE;
	 }
	 else
	 {
		 return RECEIVED_NOT_DONE;
	 }
}

void H_ESP_ReceiveString(u8* OutputString)
{
	strcpy(OutputString, ESP01Buffer);

	H_ESP01_DisplayBuffer();

}
