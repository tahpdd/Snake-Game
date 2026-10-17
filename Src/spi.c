#include "stm32f4xx.h"
#include "gpio.h"
#include "spi.h"

void spi2_init(void)
{
    gpio_init_af(GPIO_PORT_B, 10U, 5U);
    gpio_init_af(GPIO_PORT_C, 3U, 5U);

    SET_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI2EN);

    SPI2->CR1 = SPI_CR1_MSTR | SPI_CR1_BR_1 | SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE;
    SPI2->CR2 = 0U;
    SET_BIT(SPI2->CR1, SPI_CR1_SPE);
}

void spi2_send_byte(uint8_t data)
{
    while (READ_BIT(SPI2->SR, SPI_SR_TXE) == 0U) {

    }

    *(__IO uint8_t *)&SPI2->DR = data;

    while (READ_BIT(SPI2->SR, SPI_SR_TXE) == 0U) {

    }

    while (READ_BIT(SPI2->SR, SPI_SR_BSY) != 0U) {

    }
}
