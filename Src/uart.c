#include "stm32f4xx.h"
#include "gpio.h"
#include "uart.h"

void uart2_init(void)
{
    SET_BIT(RCC->APB1ENR, RCC_APB1ENR_USART2EN);
    gpio_init_af(GPIO_PORT_A, 3U, 7U);

    USART2->CR1 = 0U;
    USART2->CR2 = 0U;
    USART2->CR3 = 0U;
    USART2->BRR = 42000000U / 9600U;
    SET_BIT(USART2->CR1, USART_CR1_RE | USART_CR1_UE);
}

uint8_t uart2_available(void)
{
    return READ_BIT(USART2->SR, USART_SR_RXNE) != 0U;
}

uint8_t uart2_receive_byte(void)
{
    while (READ_BIT(USART2->SR, USART_SR_RXNE) == 0U) {

    }

    return (uint8_t)USART2->DR;
}
