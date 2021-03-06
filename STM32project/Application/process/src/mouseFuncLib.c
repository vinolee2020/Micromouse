/**
  ******************************************************************************
  * @file    mouseApp.c
  * @author  张东
  * @version V1.0.0
  * @date    2019-10-7
  * @brief   移动平台逻辑应用主程序
  ******************************************************************************
  */
/*include file ---------------------------------------------------------------*/
#include "mousefunclib.h"
#include "OccupyingGrid.h"
#include "InfraredCalc.h"
#include "odometer.h"
#include "MoveCtrl.h"
#include "attitude.h"
#include "usart.h"
#include "drive.h"
#include "stdio.h"

const uint8_t codeSMC[1542] = {
0x76,0x6F,0x69,0x64,0x20,0x67,0x73,0x74,0x6F,0x70,0x28,0x76,0x6F,0x69,0x64,0x29,0x0D,0x0A,0x7B,0x0D,0x0A,
0x20,0x20,0x5F,0x5F,0x47,0x75,0x63,0x4D,0x6F,0x75,0x73,0x65,0x53,0x74,0x61,0x74,0x65,0x20,0x20,0x20,0x3D,
0x20,0x5F,0x5F,0x53,0x54,0x4F,0x50,0x3B,0x0D,0x0A,0x20,0x20,0x6D,0x6F,0x75,0x73,0x65,0x53,0x74,0x6F,0x70,
0x28,0x29,0x3B,0x0D,0x0A,0x7D,0x0D,0x0A,0x0D,0x0A,0x76,0x6F,0x69,0x64,0x20,0x67,0x6F,0x61,0x28,0x66,0x6C,
0x6F,0x61,0x74,0x20,0x64,0x69,0x73,0x29,0x0D,0x0A,0x7B,0x0D,0x0A,0x20,0x20,0x69,0x6E,0x74,0x33,0x32,0x5F,
0x74,0x20,0x64,0x69,0x73,0x74,0x61,0x6E,0x63,0x65,0x20,0x3D,0x20,0x28,0x4F,0x4E,0x45,0x42,0x4C,0x4F,0x43,
0x4B,0x20,0x2A,0x20,0x33,0x35,0x20,0x2F,0x20,0x33,0x36,0x20,0x2F,0x20,0x31,0x38,0x29,0x20,0x2A,0x20,0x64,
0x69,0x73,0x3B,0x0D,0x0A,0x20,0x20,0x0D,0x0A,0x20,0x20,0x5F,0x5F,0x47,0x6D,0x4C,0x65,0x66,0x74,0x2E,0x75,
0x69,0x50,0x75,0x6C,0x73,0x65,0x43,0x74,0x72,0x20,0x3D,0x30,0x3B,0x0D,0x0A,0x20,0x20,0x5F,0x5F,0x47,0x6D,
0x52,0x69,0x67,0x68,0x74,0x2E,0x75,0x69,0x50,0x75,0x6C,0x73,0x65,0x43,0x74,0x72,0x20,0x3D,0x30,0x3B,0x0D,
0x0A,0x0D,0x0A,0x20,0x20,0x5F,0x5F,0x47,0x75,0x63,0x4D,0x6F,0x75,0x73,0x65,0x53,0x74,0x61,0x74,0x65,0x20,
0x20,0x20,0x3D,0x20,0x5F,0x5F,0x54,0x55,0x52,0x4E,0x4C,0x45,0x46,0x54,0x3B,0x20,0x0D,0x0A,0x20,0x20,0x5F,
0x5F,0x47,0x6D,0x52,0x69,0x67,0x68,0x74,0x2E,0x63,0x53,0x74,0x61,0x74,0x65,0x20,0x20,0x3D,0x20,0x5F,0x5F,
0x4D,0x4F,0x54,0x4F,0x52,0x52,0x55,0x4E,0x3B,0x20,0x20,0x20,0x20,0x20,0x20,0x0D,0x0A,0x20,0x20,0x5F,0x5F,
0x47,0x6D,0x4C,0x65,0x66,0x74,0x2E,0x63,0x53,0x74,0x61,0x74,0x65,0x20,0x20,0x20,0x3D,0x20,0x5F,0x5F,0x4D,
0x4F,0x54,0x4F,0x52,0x52,0x55,0x4E,0x3B,0x0D,0x0A,0x20,0x20,0x0D,0x0A,0x20,0x20,0x5F,0x5F,0x47,0x6D,0x52,
0x69,0x67,0x68,0x74,0x2E,0x75,0x69,0x50,0x75,0x6C,0x73,0x65,0x20,0x3D,0x20,0x64,0x69,0x73,0x74,0x61,0x6E,
0x63,0x65,0x3B,0x0D,0x0A,0x20,0x20,0x5F,0x5F,0x47,0x6D,0x4C,0x65,0x66,0x74,0x2E,0x75,0x69,0x50,0x75,0x6C,
0x73,0x65,0x20,0x20,0x3D,0x20,0x64,0x69,0x73,0x74,0x61,0x6E,0x63,0x65,0x3B,0x0D,0x0A,0x20,0x20,0x0D,0x0A,
0x20,0x20,0x69,0x6E,0x74,0x20,0x73,0x70,0x65,0x65,0x64,0x20,0x3D,0x20,0x28,0x64,0x69,0x73,0x20,0x3E,0x20,
0x30,0x29,0x20,0x3F,0x20,0x38,0x35,0x20,0x3A,0x20,0x2D,0x38,0x35,0x3B,0x0D,0x0A,0x20,0x20,0x5F,0x5F,0x47,
0x6D,0x53,0x50,0x49,0x44,0x2E,0x73,0x52,0x65,0x66,0x20,0x20,0x20,0x20,0x20,0x3D,0x20,0x73,0x70,0x65,0x65,
0x64,0x3B,0x0D,0x0A,0x0D,0x0A,0x20,0x20,0x77,0x68,0x69,0x6C,0x65,0x20,0x28,0x28,0x5F,0x5F,0x47,0x6D,0x52,
0x69,0x67,0x68,0x74,0x2E,0x75,0x69,0x50,0x75,0x6C,0x73,0x65,0x43,0x74,0x72,0x29,0x20,0x3C,0x3D,0x20,0x5F,
0x5F,0x47,0x6D,0x52,0x69,0x67,0x68,0x74,0x2E,0x75,0x69,0x50,0x75,0x6C,0x73,0x65,0x29,0x3B,0x0D,0x0A,0x20,
0x20,0x77,0x68,0x69,0x6C,0x65,0x20,0x28,0x28,0x5F,0x5F,0x47,0x6D,0x4C,0x65,0x66,0x74,0x2E,0x75,0x69,0x50,
0x75,0x6C,0x73,0x65,0x43,0x74,0x72,0x29,0x20,0x3C,0x3D,0x20,0x5F,0x5F,0x47,0x6D,0x4C,0x65,0x66,0x74,0x2E,
0x75,0x69,0x50,0x75,0x6C,0x73,0x65,0x29,0x3B,0x0D,0x0A,0x20,0x20,0x0D,0x0A,0x20,0x20,0x67,0x73,0x74,0x6F,
0x70,0x28,0x29,0x3B,0x0D,0x0A,0x7D,0x0D,0x0A,0x0D,0x0A,0x76,0x6F,0x69,0x64,0x20,0x67,0x6F,0x66,0x28,0x66,
0x6C,0x6F,0x61,0x74,0x20,0x64,0x69,0x73,0x29,0x0D,0x0A,0x7B,0x0D,0x0A,0x20,0x20,0x75,0x69,0x6E,0x74,0x33,
0x32,0x5F,0x74,0x20,0x64,0x69,0x73,0x74,0x61,0x6E,0x63,0x65,0x20,0x3D,0x20,0x28,0x4F,0x4E,0x45,0x42,0x4C,
0x4F,0x43,0x4B,0x20,0x2A,0x20,0x33,0x35,0x20,0x2F,0x20,0x33,0x36,0x20,0x2F,0x20,0x31,0x38,0x29,0x20,0x2A,
0x20,0x64,0x69,0x73,0x3B,0x0D,0x0A,0x20,0x20,0x0D,0x0A,0x20,0x20,0x5F,0x5F,0x47,0x6D,0x4C,0x65,0x66,0x74,
0x2E,0x75,0x69,0x50,0x75,0x6C,0x73,0x65,0x43,0x74,0x72,0x20,0x3D,0x30,0x3B,0x0D,0x0A,0x20,0x20,0x5F,0x5F,
0x47,0x6D,0x52,0x69,0x67,0x68,0x74,0x2E,0x75,0x69,0x50,0x75,0x6C,0x73,0x65,0x43,0x74,0x72,0x20,0x3D,0x30,
0x3B,0x0D,0x0A,0x0D,0x0A,0x20,0x20,0x5F,0x5F,0x47,0x75,0x63,0x4D,0x6F,0x75,0x73,0x65,0x53,0x74,0x61,0x74,
0x65,0x20,0x20,0x20,0x3D,0x20,0x5F,0x5F,0x47,0x4F,0x41,0x48,0x45,0x41,0x44,0x3B,0x0D,0x0A,0x20,0x20,0x5F,
0x5F,0x47,0x69,0x4D,0x61,0x78,0x53,0x70,0x65,0x65,0x64,0x20,0x20,0x20,0x20,0x20,0x20,0x3D,0x20,0x38,0x35,
0x3B,0x0D,0x0A,0x20,0x20,0x0D,0x0A,0x20,0x20,0x5F,0x5F,0x47,0x6D,0x52,0x69,0x67,0x68,0x74,0x2E,0x75,0x69,
0x50,0x75,0x6C,0x73,0x65,0x20,0x3D,0x20,0x64,0x69,0x73,0x74,0x61,0x6E,0x63,0x65,0x3B,0x0D,0x0A,0x20,0x20,
0x5F,0x5F,0x47,0x6D,0x4C,0x65,0x66,0x74,0x2E,0x75,0x69,0x50,0x75,0x6C,0x73,0x65,0x20,0x20,0x3D,0x20,0x64,
0x69,0x73,0x74,0x61,0x6E,0x63,0x65,0x3B,0x0D,0x0A,0x20,0x20,0x0D,0x0A,0x20,0x20,0x5F,0x5F,0x47,0x6D,0x52,
0x69,0x67,0x68,0x74,0x2E,0x63,0x53,0x74,0x61,0x74,0x65,0x20,0x20,0x3D,0x20,0x5F,0x5F,0x4D,0x4F,0x54,0x4F,
0x52,0x52,0x55,0x4E,0x3B,0x0D,0x0A,0x20,0x20,0x5F,0x5F,0x47,0x6D,0x4C,0x65,0x66,0x74,0x2E,0x63,0x53,0x74,
0x61,0x74,0x65,0x20,0x20,0x20,0x3D,0x20,0x5F,0x5F,0x4D,0x4F,0x54,0x4F,0x52,0x52,0x55,0x4E,0x3B,0x0D,0x0A,
0x20,0x20,0x0D,0x0A,0x20,0x20,0x47,0x75,0x69,0x53,0x70,0x65,0x65,0x64,0x43,0x74,0x72,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x3D,0x20,0x5F,0x5F,0x53,0x50,0x45,0x45,0x44,0x55,0x50,0x3B,0x0D,0x0A,0x0D,0x0A,0x20,0x20,
0x77,0x68,0x69,0x6C,0x65,0x20,0x28,0x28,0x5F,0x5F,0x47,0x6D,0x52,0x69,0x67,0x68,0x74,0x2E,0x75,0x69,0x50,
0x75,0x6C,0x73,0x65,0x43,0x74,0x72,0x29,0x20,0x3C,0x3D,0x20,0x5F,0x5F,0x47,0x6D,0x52,0x69,0x67,0x68,0x74,
0x2E,0x75,0x69,0x50,0x75,0x6C,0x73,0x65,0x29,0x3B,0x0D,0x0A,0x20,0x20,0x77,0x68,0x69,0x6C,0x65,0x20,0x28,
0x28,0x5F,0x5F,0x47,0x6D,0x4C,0x65,0x66,0x74,0x2E,0x75,0x69,0x50,0x75,0x6C,0x73,0x65,0x43,0x74,0x72,0x29,
0x20,0x3C,0x3D,0x20,0x5F,0x5F,0x47,0x6D,0x4C,0x65,0x66,0x74,0x2E,0x75,0x69,0x50,0x75,0x6C,0x73,0x65,0x29,
0x3B,0x0D,0x0A,0x20,0x20,0x0D,0x0A,0x20,0x20,0x67,0x73,0x74,0x6F,0x70,0x28,0x29,0x3B,0x0D,0x0A,0x7D,0x0D,
0x0A,0x0D,0x0A,0x76,0x6F,0x69,0x64,0x20,0x61,0x72,0x63,0x28,0x66,0x6C,0x6F,0x61,0x74,0x20,0x61,0x6E,0x67,
0x65,0x6C,0x2C,0x69,0x6E,0x74,0x33,0x32,0x5F,0x74,0x20,0x73,0x70,0x64,0x29,0x0D,0x0A,0x7B,0x0D,0x0A,0x20,
0x20,0x5F,0x5F,0x47,0x75,0x63,0x4D,0x6F,0x75,0x73,0x65,0x53,0x74,0x61,0x74,0x65,0x20,0x20,0x20,0x3D,0x20,
0x5F,0x5F,0x54,0x55,0x52,0x4E,0x4C,0x45,0x46,0x54,0x3B,0x20,0x0D,0x0A,0x20,0x20,0x5F,0x5F,0x47,0x6D,0x52,
0x69,0x67,0x68,0x74,0x2E,0x63,0x53,0x74,0x61,0x74,0x65,0x20,0x20,0x3D,0x20,0x5F,0x5F,0x4D,0x4F,0x54,0x4F,
0x52,0x52,0x55,0x4E,0x3B,0x20,0x20,0x20,0x20,0x20,0x20,0x0D,0x0A,0x20,0x20,0x5F,0x5F,0x47,0x6D,0x4C,0x65,
0x66,0x74,0x2E,0x63,0x53,0x74,0x61,0x74,0x65,0x20,0x20,0x20,0x3D,0x20,0x5F,0x5F,0x4D,0x4F,0x54,0x4F,0x52,
0x52,0x55,0x4E,0x3B,0x0D,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0D,0x0A,0x20,0x20,0x5F,0x5F,
0x47,0x6D,0x53,0x50,0x49,0x44,0x2E,0x73,0x52,0x65,0x66,0x20,0x20,0x20,0x20,0x20,0x3D,0x20,0x73,0x70,0x64,
0x3B,0x20,0x20,0x20,0x0D,0x0A,0x20,0x20,0x5F,0x5F,0x47,0x6D,0x57,0x50,0x49,0x44,0x2E,0x73,0x52,0x65,0x66,
0x20,0x20,0x20,0x20,0x20,0x3D,0x20,0x61,0x6E,0x67,0x65,0x6C,0x3B,0x0D,0x0A,0x20,0x20,0x0D,0x0A,0x20,0x20,
0x61,0x6E,0x67,0x65,0x6C,0x20,0x3D,0x20,0x28,0x61,0x6E,0x67,0x65,0x6C,0x20,0x3E,0x20,0x30,0x29,0x20,0x3F,
0x20,0x61,0x6E,0x67,0x65,0x6C,0x20,0x3A,0x20,0x2D,0x61,0x6E,0x67,0x65,0x6C,0x3B,0x0D,0x0A,0x0D,0x0A,0x20,
0x20,0x69,0x6E,0x74,0x33,0x32,0x5F,0x74,0x20,0x77,0x69,0x20,0x3D,0x20,0x61,0x6E,0x67,0x65,0x6C,0x20,0x2A,
0x20,0x39,0x35,0x32,0x2E,0x37,0x37,0x37,0x37,0x37,0x38,0x3B,0x0D,0x0A,0x20,0x20,0x0D,0x0A,0x20,0x20,0x47,
0x57,0x3D,0x30,0x3B,0x0D,0x0A,0x20,0x20,0x77,0x68,0x69,0x6C,0x65,0x28,0x31,0x29,0x0D,0x0A,0x20,0x20,0x7B,
0x0D,0x0A,0x20,0x20,0x20,0x20,0x57,0x3D,0x28,0x66,0x6C,0x6F,0x61,0x74,0x29,0x47,0x57,0x2A,0x35,0x31,0x32,
0x31,0x2F,0x34,0x30,0x39,0x36,0x2F,0x32,0x3B,0x0D,0x0A,0x20,0x20,0x20,0x20,0x69,0x66,0x28,0x57,0x3E,0x77,
0x69,0x29,0x0D,0x0A,0x20,0x20,0x20,0x20,0x7B,0x0D,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x62,0x72,0x65,0x61,
0x6B,0x3B,0x0D,0x0A,0x20,0x20,0x20,0x20,0x7D,0x20,0x0D,0x0A,0x20,0x20,0x7D,0x0D,0x0A,0x20,0x20,0x67,0x73,
0x74,0x6F,0x70,0x28,0x29,0x3B,0x0D,0x0A,0x7D,
};

void LEDFlash(uint32_t num)
{
	static uint32_t lasttick = 0;
	
	if((Sys_GetTick() - lasttick) > num)
	{
		lasttick  = Sys_GetTick();
		//B12LED
		if((GPIOB->ODR & (0x01 << 12)) != 0)
		{
			GPIOB->BRR = (0x01 << 12);
		}
		else
		{
			GPIOB->BSRR = (0x01 << 12);
		}
	}
}	
//快速自转测试
void TestFuncMoveFastTern(void)
{
	//快速移动测试
	while(1)
	{
		//右拐循环测试
		
		//获得当前位置
		PosTypedef mp = getMousePos();
		
		//抵近障碍物
		if(getBarrierAct())
		{
			//右转
			mouseMove(ML180);
			mouseMove(MStop);
			while(1);
		}
		//前进
		mouseMove(MForward);
	}
}


//通过发送地图
void SendMaoToUsart(void)
{
	uint8_t str[50];
	//按照行列发送地图信息
	for(int y = 0;y < 16;y++)
	{
		for(int x = 0;x < 16;x++)
		{
			sprintf((char *)str,"0x%02X,",readMapGrid(x,y));
			UsartSendData(str);
		}
		UsartSendData("\r\n");
	}
}

extern RedValTypedef g_RedSenVal;

//发送红外测试数据
void SendInfrared(void)
{
	uint8_t str[50];
	sprintf((char *)str,"LS = %5d , LF = %5d , RF = %5d ,RS = %5d \r\n",g_RedSenVal.LS,g_RedSenVal.LF,g_RedSenVal.RF,g_RedSenVal.RS);
	UsartSendData(str);
	
	delay_ms(200);
}


void ETR_Test(void)
{
	mouseMoveFastI(MForward);
	
	while(1)
	{
		if(getBarrierAct())
		{
			mouseMoveFastI(MStop);
			
			uint8_t str[50];
			sprintf((char *)str,"ETR = %d \r\n",readOdometerEtr());
			UsartSendData(str);
			while(1);
		}
	}
	
}

//高速测试
void TestFuncMoveFast()
{
	uint16_t x = 0;
	
	TIM4->CCR3 = 600;
	while(1)
	{
		setFastStMoveGridNum(15);
		AttitudeStateSet(AFStraight);
		if(getPosState())
		{
			//mouseMove(MStop);
			//while(1);
			x++;
			if(x == 15)
			{
				x = 0;
				mouseMoveFastI(MR90);
				//mouseMove(MStop);
				//while(1);
			}
		}
//		
//		TIM4->CCR3 = 0;
//		mouseMove(MStop);
//		while(1);
	}
}
//发送代码
void sendSMCCode(void)
{
	UsartSendData((u8 *)codeSMC);
}

