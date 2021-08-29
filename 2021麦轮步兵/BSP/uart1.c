#include "uart1.h"
#include "Device.h"
#include "Function.h"


/* Private macro -------------------------------------------------------------*/
/* TX */
#define    GPIO_TX                   GPIOA
#define    GPIO_PIN_TX               GPIO_Pin_9
#define    GPIO_PINSOURCE_TX         GPIO_PinSource9
#define    RCC_AHB1PERIPH_GPIO_TX    RCC_AHB1Periph_GPIOA

/* RX */
#define    GPIO_RX                   GPIOA
#define    GPIO_PIN_RX               GPIO_Pin_10
#define    GPIO_PINSOURCE_RX         GPIO_PinSource10
#define    RCC_AHB1PERIPH_GPIO_RX    RCC_AHB1Periph_GPIOA

/* DMA */
#define    DMA2_STREAM_RX            DMA2_Stream2
#define	   DMA2_STREAM_TX			       DMA2_Stream7

/* Buffer Len */
#define    USART1_BUFFER_RX_LEN     200
#define	   USART1_BUFFER_TX_LEN		  256
/* Private variables ---------------------------------------------------------*/
uint8_t Usart1_Buffer_Rx[ USART1_BUFFER_RX_LEN ] = {0};	//�������������ݴ�������
void USART1_RX_DMA_Init( void )
{
	DMA_InitTypeDef xCom1DMAInit;
	
	DMA_DeInit( DMA2_STREAM_RX );
	xCom1DMAInit.DMA_Channel = DMA_Channel_4;
	xCom1DMAInit.DMA_DIR = DMA_DIR_PeripheralToMemory;//�������赽�洢��
	xCom1DMAInit.DMA_PeripheralBaseAddr  = (uint32_t)&(USART1->DR);
	xCom1DMAInit.DMA_Memory0BaseAddr     = (uint32_t)Usart1_Buffer_Rx;
	xCom1DMAInit.DMA_BufferSize = USART1_BUFFER_RX_LEN;
	xCom1DMAInit.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	xCom1DMAInit.DMA_MemoryInc = DMA_MemoryInc_Enable;
	xCom1DMAInit.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	xCom1DMAInit.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	xCom1DMAInit.DMA_Mode = DMA_Mode_Circular;
	xCom1DMAInit.DMA_Priority = DMA_Priority_VeryHigh;
	xCom1DMAInit.DMA_FIFOMode = DMA_FIFOMode_Enable;
	xCom1DMAInit.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	xCom1DMAInit.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	xCom1DMAInit.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

	DMA_Init( DMA2_STREAM_RX, &xCom1DMAInit );	
	DMA_Cmd( DMA2_STREAM_RX, ENABLE);  // stream2	
}

/**
 *	@brief ����1 DMA��ʼ��
 */
void USART1_DMA_Init( void )
{		
	USART1_RX_DMA_Init();//ֻ�з���
}/* API functions -------------------------------------------------------------*/
/**
 *	@brief	Zigbeeͨ�Ŵ��ڳ�ʼ��(USART1)
 */
void USART1_Init( void )
{
	USART_InitTypeDef  xUsartInit;
	GPIO_InitTypeDef   xGpioInit;
	NVIC_InitTypeDef   xNvicInit;

	RCC_AHB1PeriphClockCmd( RCC_AHB1PERIPH_GPIO_TX | RCC_AHB1PERIPH_GPIO_RX, ENABLE );
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1, ENABLE );
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

	GPIO_PinAFConfig( GPIO_TX, GPIO_PINSOURCE_TX, GPIO_AF_USART1 );
	GPIO_PinAFConfig( GPIO_RX, GPIO_PINSOURCE_RX, GPIO_AF_USART1 ); 

	/*----Configure GPIO----*/
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

	/*----Configure USART----*/
  if(Master == MASTER_DOWN)
    xUsartInit.USART_BaudRate            = 9600;  
  else 
    xUsartInit.USART_BaudRate            = 115200; 
  
	xUsartInit.USART_WordLength          = USART_WordLength_8b;
	xUsartInit.USART_StopBits            = USART_StopBits_1;
	xUsartInit.USART_Parity              = USART_Parity_No;
	xUsartInit.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;
	xUsartInit.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	
	USART_Init( USART1, &xUsartInit );
	USART_Cmd( USART1, ENABLE );
	
	USART_ITConfig( USART1, USART_IT_IDLE, ENABLE  ); // ע��Ҫ���óɴ��ڿ����ж� 
//	USART_ITConfig( USART1, USART_IT_RXNE, ENABLE );

	/*----Configure DMA----*/
	USART1_DMA_Init( );	// ��ʼ��uart1��DMA
	USART_DMACmd( USART1, USART_DMAReq_Rx, ENABLE );
//	USART_DMACmd( USART1, USART_DMAReq_Tx, ENABLE );
//	

	
	/*----Configure NVIC----*/
	xNvicInit.NVIC_IRQChannel                    = USART1_IRQn;
	xNvicInit.NVIC_IRQChannelPreemptionPriority  = 2;
	xNvicInit.NVIC_IRQChannelSubPriority         = 0;
	xNvicInit.NVIC_IRQChannelCmd                 = ENABLE;
	NVIC_Init( &xNvicInit );
		
}

/**
 *	@brief	����1�жϺ���
 */
void USART1_IRQHandler( void )
{
	uint8_t res;
	/* �����ж� */
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
	{		
		res = res;	// ��������Ŀղ���
		//����ST�ٷ��ֲ�,��һ��SR��DR�Ĵ���,IDLE�����ٴ�ʹ��,�����һֱ�����ж�,�ͻ�����ڽ����ж�û����
		res = USART1->SR ;
		res = USART1->DR ;
		
		DMA_Cmd(DMA2_STREAM_RX, DISABLE);
		
		res = USART1_BUFFER_RX_LEN - DMA_GetCurrDataCounter(DMA2_STREAM_RX);
			
		
		memset(Usart1_Buffer_Rx, 0, USART1_BUFFER_RX_LEN);	// ����֮����������
		DMA_Cmd(DMA2_STREAM_RX, ENABLE);
	}
}
/**
  * @brief  ����һ�η���һ���ֽ�����
  * @param  �Լ�����õ�Ҫ�������е�����
  * @retval void
  * @attention  ������λ����
  */
void USART1_SendChar(uint8_t cData)
{
	while (USART_GetFlagStatus( USART1, USART_FLAG_TC ) == RESET);
	
	USART_SendData( USART1, cData );   
}
