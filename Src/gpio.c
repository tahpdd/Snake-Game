#include "gpio.h"
#include "stm32f4xx.h"

static GPIO_TypeDef *gpio_get_port(GPIO_Port port)
{
    switch (port) {
        case GPIO_PORT_A: return GPIOA;
        case GPIO_PORT_B: return GPIOB;
        case GPIO_PORT_C: return GPIOC;
        case GPIO_PORT_D: return GPIOD;
        case GPIO_PORT_E: return GPIOE;
        case GPIO_PORT_F: return GPIOF;
        case GPIO_PORT_G: return GPIOG;
        case GPIO_PORT_H: return GPIOH;
        case GPIO_PORT_I: return GPIOI;
        default: return 0;
    }
}

static void gpio_enable_clock(GPIO_TypeDef *GPIOx)
{
    if (GPIOx == GPIOA) {
        SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);
    } else if (GPIOx == GPIOB) {
        SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN);
    } else if (GPIOx == GPIOC) {
        SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN);
    } else if (GPIOx == GPIOD) {
        SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);
    } else if (GPIOx == GPIOE) {
        SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);
    } else if (GPIOx == GPIOF) {
        SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOFEN);
    } else if (GPIOx == GPIOG) {
        SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOGEN);
    } else if (GPIOx == GPIOH) {
        SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOHEN);
    } else if (GPIOx == GPIOI) {
        SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOIEN);
    }

    (void)RCC->AHB1ENR;
}

void gpio_init_output(GPIO_Port port, uint8_t pin)
{
    GPIO_TypeDef *GPIOx = gpio_get_port(port);
    uint32_t pin_mask = 1UL << pin;
    uint32_t mode_mask = 3UL << (pin * 2U);

    if (GPIOx == 0) {
        return;
    }

    gpio_enable_clock(GPIOx);
    GPIOx->BSRR = pin_mask << 16U;
    MODIFY_REG(GPIOx->MODER, mode_mask, 1UL << (pin * 2U));
    CLEAR_BIT(GPIOx->OTYPER, pin_mask);
    MODIFY_REG(GPIOx->OSPEEDR, mode_mask, 3UL << (pin * 2U));
    CLEAR_BIT(GPIOx->PUPDR, mode_mask);
}

void gpio_init_af(GPIO_Port port, uint8_t pin, uint8_t alternate_function)
{
    GPIO_TypeDef *GPIOx = gpio_get_port(port);
    uint32_t mode_mask = 3UL << (pin * 2U);
    uint32_t af_shift = (pin % 8U) * 4U;
    uint32_t af_mask = 15UL << af_shift;

    if (GPIOx == 0) {
        return;
    }

    gpio_enable_clock(GPIOx);
    MODIFY_REG(GPIOx->MODER, mode_mask, 2UL << (pin * 2U));
    CLEAR_BIT(GPIOx->OTYPER, 1UL << pin);
    MODIFY_REG(GPIOx->OSPEEDR, mode_mask, 3UL << (pin * 2U));
    CLEAR_BIT(GPIOx->PUPDR, mode_mask);
    MODIFY_REG(GPIOx->AFR[pin / 8U], af_mask, (uint32_t)alternate_function << af_shift);
}

void gpio_set_pin(GPIO_Port port, uint8_t pin)
{
    GPIO_TypeDef *GPIOx = gpio_get_port(port);

    if (GPIOx == 0) {
        return;
    }

    GPIOx->BSRR = 1UL << pin;
}

void gpio_clear_pin(GPIO_Port port, uint8_t pin)
{
    GPIO_TypeDef *GPIOx = gpio_get_port(port);

    if (GPIOx == 0) {
        return;
    }

    GPIOx->BSRR = 1UL << (pin + 16U);
}

void gpio_toggle_pin(GPIO_Port port, uint8_t pin)
{
    GPIO_TypeDef *GPIOx = gpio_get_port(port);

    if (GPIOx == 0) {
        return;
    }

    GPIOx->ODR ^= 1UL << pin;
}
