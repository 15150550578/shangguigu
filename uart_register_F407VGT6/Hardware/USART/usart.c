#include "usart.h"

//初始化
void USART_Init(void)
{
    //1.配置时钟,打开GPIOA和USART1的时钟
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; //使能GPIOA时钟
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; //使能USART1时钟

    //2.配置GPIOA的PA9和PA10为复用功能,PA9->TX,PA10->RX
    GPIOA->MODER &= ~(GPIO_MODER_MODER9 | GPIO_MODER_MODER10); //清除PA9和PA10的模式位
    GPIOA->MODER |= (GPIO_MODER_MODER9_1)|(GPIO_MODER_MODER10_1);          //PA9，PA10开启复用功能
    
    // PA9、PA10 选择 AF7：USART1
    GPIOA->AFR[1] &= ~((0x0F << 4) | (0x0F << 8));
    GPIOA->AFR[1] |=  (0x07 << 4) | (0x07 << 8);

    //4.串口配重
    //4.1 配置波特率
    USART1->BRR = 0x8B; //设置波特率为115200,假设APB2时钟为16MHz,则BRR=16MHz/115200=138.8889=0x8B

    //4.2收发器使能
    USART1->CR1 |= USART_CR1_TE | USART_CR1_RE|USART_CR1_UE; //使能发送和接收，USART1使能

    //4.3其他配置，设置数据帧格式,8为数据位，无校验位，1个停止位
    USART1->CR1 &= ~(USART_CR1_M | USART_CR1_PCE);
    USART1->CR2 &= ~(USART_CR2_STOP); //设置停止位为1个
    USART1->CR3 &= ~(USART_CR3_CTSE | USART_CR3_RTSE); //不使用硬件流控制

}

//发送字符
void USART_SendChar( uint8_t ch)
{
    //等待发送缓冲区为空
    while(!(USART1->SR & USART_SR_TXE));
    //发送数据
    USART1->DR = ch;
}

//接收一个字符
uint8_t USART_ReceiveChar(void)
{
    //等待接收缓冲区不为空
    while(!(USART1->SR & USART_SR_RXNE));
    //读取数据
    return USART1->DR;
}

//发送字符串
void USART_SendString(uint8_t *str)
{
    while(*str)
    {
        USART_SendChar(*str++);
    }
}

//接收字符串
void USART_ReceiveString(uint8_t buffer[], uint8_t *length)
{
    uint8_t i = 0;

    //外层循环，接收字符串直到检测到空闲
    while(1)
    {
        //内层循环，判断当前是否数据接收完毕
        while(!(USART1->SR & USART_SR_RXNE)) //等待接收缓冲区不为空
        {
            if(USART1->SR & USART_SR_IDLE) //检测到空闲中断
            {
                buffer[i] = '\0';
                *length = i; //保存接收到的字符串长度
                (void)USART1->DR; //读取数据
                return; //退出接收函数
            }
        }
        if(i < 99)
        {
            buffer[i++] = USART1->DR; //读取数据
        }
        else
        {
            (void)USART1->DR;
        }
    }
}