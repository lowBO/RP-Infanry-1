#include "uart4.h"
#include "Device.h"
#include "Function.h"

/* TX */
#define    GPIO_TX                   GPIOA
#define    GPIO_PIN_TX               GPIO_Pin_0
#define    GPIO_PINSOURCE_TX         GPIO_PinSource0
#define    RCC_AHB1PERIPH_GPIO_TX    RCC_AHB1Periph_GPIOA

/* RX */
#define    GPIO_RX                   GPIOA
#define    GPIO_PIN_RX               GPIO_Pin_1
#define    GPIO_PINSOURCE_RX         GPIO_PinSource1
#define    RCC_AHB1PERIPH_GPIO_RX    RCC_AHB1Periph_GPIOA

/* DMA */
#define    DMA1_Stream_RX            DMA1_Stream2
#define    DMA1_Stream_TX            DMA1_Stream4

/* Buffer Len */
#define    VISION_BUFFER_LEN         100

/* Private variables ---------------------------------------------------------*/
/* ## Global variables ## ----------------------------------------------------*/
uint8_t  Vision_Buffer[ VISION_BUFFER_LEN ] = {0};	//�Ӿ��������������ݴ�������
uint8_t  Vision_txBuffer[ VISION_BUFFER_LEN ] = {0}; //���ͻ���
//float Yaw_error,Pitch_error;//��UART4�иı�

//js������
float js_pitch_erro_V = 0,js_yaw_erro_V = 0;

void UART4_DMA_Init(void)
{		
	DMA_InitTypeDef xCom4DMAInit;
	
	DMA_DeInit( DMA1_Stream_RX );
	xCom4DMAInit.DMA_Channel = DMA_Channel_4;
	xCom4DMAInit.DMA_PeripheralBaseAddr  = (uint32_t)&(UART4->DR);
	xCom4DMAInit.DMA_Memory0BaseAddr     = (uint32_t)Vision_Buffer;
	xCom4DMAInit.DMA_DIR = DMA_DIR_PeripheralToMemory;//�������赽�洢��
	xCom4DMAInit.DMA_BufferSize = VISION_BUFFER_LEN;
	xCom4DMAInit.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	xCom4DMAInit.DMA_MemoryInc = DMA_MemoryInc_Enable;
	xCom4DMAInit.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	xCom4DMAInit.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	xCom4DMAInit.DMA_Mode = DMA_Mode_Circular;                             //DMA_Mode_Normal��ֻ����һ�Σ�
	xCom4DMAInit.DMA_Priority = DMA_Priority_VeryHigh;                     //�жϵȼ�
	xCom4DMAInit.DMA_FIFOMode = DMA_FIFOMode_Enable;                       //ֱ��ģʽ
	xCom4DMAInit.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;               
	xCom4DMAInit.DMA_MemoryBurst = DMA_MemoryBurst_Single;                 //�洢�����δ���
	xCom4DMAInit.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;         //���赥�δ���

	DMA_Init( DMA1_Stream_RX, &xCom4DMAInit );	
	DMA_Cmd( DMA1_Stream_RX, ENABLE);  // stream2
  
	DMA_DeInit( DMA1_Stream_TX );
	xCom4DMAInit.DMA_Channel = DMA_Channel_4;
	xCom4DMAInit.DMA_PeripheralBaseAddr  = (uint32_t)&(UART4->DR);
	xCom4DMAInit.DMA_Memory0BaseAddr     = (uint32_t)Vision_txBuffer;
	xCom4DMAInit.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	xCom4DMAInit.DMA_BufferSize = VISION_BUFFER_LEN;
	xCom4DMAInit.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	xCom4DMAInit.DMA_MemoryInc = DMA_MemoryInc_Enable;
	xCom4DMAInit.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	xCom4DMAInit.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	xCom4DMAInit.DMA_Mode = DMA_Mode_Circular;                             //DMA_Mode_Normal��ֻ����һ�Σ�
	xCom4DMAInit.DMA_Priority = DMA_Priority_VeryHigh;                     //�жϵȼ�
	xCom4DMAInit.DMA_FIFOMode = DMA_FIFOMode_Enable;                       //ֱ��ģʽ
	xCom4DMAInit.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;               
	xCom4DMAInit.DMA_MemoryBurst = DMA_MemoryBurst_Single;                 //�洢�����δ���
	xCom4DMAInit.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;         //���赥�δ���

	DMA_Init( DMA1_Stream_TX, &xCom4DMAInit );	
//	DMA_Cmd( DMA1_Stream_TX, ENABLE);  // stream2   ����dma������ʹ��
  DMA_ITConfig(DMA1_Stream_TX , DMA_IT_TC , ENABLE);//��������ж�
}

void UART4_Init(void)
{
	USART_InitTypeDef  xUsartInit;
	GPIO_InitTypeDef   xGpioInit;
	NVIC_InitTypeDef   xNvicInit;
  
  RCC_AHB1PeriphClockCmd( RCC_AHB1PERIPH_GPIO_TX | RCC_AHB1PERIPH_GPIO_RX, ENABLE );//GPIOʱ��
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_UART4, ENABLE );//����4ʱ��

	GPIO_PinAFConfig( GPIO_TX, GPIO_PINSOURCE_TX, GPIO_AF_UART4 );
	GPIO_PinAFConfig( GPIO_RX, GPIO_PINSOURCE_RX, GPIO_AF_UART4 ); 

	xGpioInit.GPIO_Pin   = GPIO_PIN_TX;
	xGpioInit.GPIO_Mode  = GPIO_Mode_AF;
	xGpioInit.GPIO_OType = GPIO_OType_PP;
  
  if(Master == MASTER_DOWN)
    xGpioInit.GPIO_Speed = GPIO_Speed_50MHz;
  else 
    xGpioInit.GPIO_Speed = GPIO_Speed_100MHz;
  
	xGpioInit.GPIO_PuPd  = GPIO_PuPd_UP;

	GPIO_Init( GPIO_TX, &xGpioInit );

	xGpioInit.GPIO_Pin = GPIO_PIN_RX;
	GPIO_Init( GPIO_RX, &xGpioInit );
 
  if(Master == MASTER_DOWN)
    xUsartInit.USART_BaudRate            = 9600;  
  else 
    xUsartInit.USART_BaudRate            = 115200;   
  
	xUsartInit.USART_WordLength          = USART_WordLength_8b;
	xUsartInit.USART_StopBits            = USART_StopBits_1;
	xUsartInit.USART_Parity              = USART_Parity_No;
	xUsartInit.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;
	xUsartInit.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	
	USART_Init( UART4, &xUsartInit );
	USART_Cmd( UART4, ENABLE );
	
	USART_ITConfig( UART4, USART_IT_IDLE, ENABLE  ); // ע��Ҫ���óɴ��ڿ����ж� 
  
	UART4_DMA_Init( );	// ��ʼ��uart4��DMA
	USART_DMACmd( UART4, USART_DMAReq_Rx, ENABLE );
	USART_DMACmd( UART4, USART_DMAReq_Tx, ENABLE );
  
	xNvicInit.NVIC_IRQChannel                    = UART4_IRQn;
	xNvicInit.NVIC_IRQChannelPreemptionPriority  = 1;//��ռ
	xNvicInit.NVIC_IRQChannelSubPriority         = 0;//��
	xNvicInit.NVIC_IRQChannelCmd                 = ENABLE;
	NVIC_Init( &xNvicInit );
  
	xNvicInit.NVIC_IRQChannel                    = DMA1_Stream4_IRQn;
	xNvicInit.NVIC_IRQChannelPreemptionPriority  = 1;//��ռ
	xNvicInit.NVIC_IRQChannelSubPriority         = 1;//��
	xNvicInit.NVIC_IRQChannelCmd                 = ENABLE;
	NVIC_Init( &xNvicInit );
	 
}

/**
 *	@brief	����4�жϺ���  (��ȡ����)
 */

void UART4_IRQHandler( void )
{
	uint8_t res;
	/* �����ж� */
	if(USART_GetITStatus(UART4, USART_IT_IDLE) != RESET)
	{		
		res = res;	// ��������Ŀղ���
		//����ST�ٷ��ֲ�,��һ��SR��DR�Ĵ���,IDLE�����ٴ�ʹ��,�����һֱ�����ж�,�ͻ�����ڽ����ж�û����
		res = UART4->SR ;
		res = UART4->DR ;//USART_ClearITPendingBit(USART3, USART_IT_IDLE);  //������λ
		
		DMA_Cmd(DMA1_Stream_RX, DISABLE);
		
		res = VISION_BUFFER_LEN - DMA_GetCurrDataCounter(DMA1_Stream_RX);
		
  if(Master == MASTER_DOWN)
    Sonic_ReadData_FR(Vision_Buffer);
  else 
    VISION_ReadData(Vision_Buffer);		// ��ȡ�Ӿ�����
    
		memset(Vision_Buffer, 0, VISION_BUFFER_LEN);	// ����֮����������
		DMA_Cmd(DMA1_Stream_RX, ENABLE);
    
      Single_time_cal();
	}
}

bool IF_Uart4_DMA_Busy = NO;
void DMA1_Stream4_IRQHandler(void)
{
  if(DMA_GetITStatus(DMA1_Stream4 , DMA_IT_TCIF4) != RESET)
  {
    /* DMA������� */
    DMA_ClearFlag(DMA1_Stream4 , DMA_FLAG_TCIF4);
//    DMA_ClearFlag(DMA1_Stream4 , DMA_FLAG_HTIF4);
//    DMA_ClearFlag(DMA1_Stream4 , DMA_FLAG_TEIF4);
//    DMA_ClearFlag(DMA1_Stream4 , DMA_FLAG_FEIF4);
//    DMA_ClearFlag(DMA1_Stream4 , DMA_FLAG_DMEIF4);
    DMA_Cmd(DMA1_Stream4 , DISABLE);
    
    IF_Uart4_DMA_Busy = NO;//DMA����
    /* ��շ��ͻ��� */
    memset(Vision_txBuffer , 0 , VISION_BUFFER_LEN);
  }
  if(DMA_GetITStatus(DMA1_Stream4 , DMA_IT_HTIF4) != RESET)
  {
  }
  if(DMA_GetITStatus(DMA1_Stream4 , DMA_IT_TEIF4) != RESET)
  {
  }
  if(DMA_GetITStatus(DMA1_Stream4 , DMA_IT_DMEIF4) != RESET)
  {
  }
  if(DMA_GetITStatus(DMA1_Stream4 , DMA_IT_FEIF4) != RESET)
  {
  }
}

void UART4_DMA_SentData(uint8_t *cData , int size)
{
  if(IF_Uart4_DMA_Busy == NO)
  {
    /* DMAû�ڷ��� */
    for(int a = 0;a < size;a++)
    {
      Vision_txBuffer[a] = cData[a];
    }
    /* �޸�DMA���ͳ��� */
    DMA_SetCurrDataCounter(DMA1_Stream4,size);
    /* DMAæ�� */
    IF_Uart4_DMA_Busy = YES;
    /* DMA���� */
    DMA_Cmd(DMA1_Stream4 , ENABLE);
  }
} 


/**
  * @brief  ����һ�η���һ���ֽ�����
  * @param  �Լ�����õ�Ҫ�������е�����
  */
void UART4_SendChar(uint8_t cData)
{
	while (USART_GetFlagStatus( UART4, USART_FLAG_TC ) == RESET);
	
	USART_SendData( UART4, cData );   
}


