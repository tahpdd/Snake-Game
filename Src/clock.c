#include "stm32f4xx.h"
#include "clock.h"

void clock_init_max(void)
{
    SET_BIT(RCC->CR, RCC_CR_HSION);

    while (READ_BIT(RCC->CR, RCC_CR_HSIRDY) == 0U) {

    }

    SET_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN);
    (void)RCC->APB1ENR;
    SET_BIT(PWR->CR, PWR_CR_VOS);

    while (READ_BIT(PWR->CSR, PWR_CSR_VOSRDY) == 0U) {

    }

    MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_5WS);
    SET_BIT(FLASH->ACR, FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN);

    RCC->PLLCFGR = 16U | (336U << RCC_PLLCFGR_PLLN_Pos) | (7U << RCC_PLLCFGR_PLLQ_Pos);

    MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2, RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV4 | RCC_CFGR_PPRE2_DIV2);
    SET_BIT(RCC->CR, RCC_CR_PLLON);

    while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) == 0U) {

    }

    MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL);

    while (READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) {

    }

}

void clock_init_timer(void)
{
    SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM2EN);
    TIM2->PSC = 83U;
    TIM2->ARR = 999U;
    TIM2->EGR = TIM_EGR_UG;
    TIM2->SR = 0U;
    TIM2->CNT = 0U;
    SET_BIT(TIM2->CR1, TIM_CR1_CEN);
}

void clock_delay_ms(uint32_t milliseconds)
{
    while (milliseconds-- > 0U) {
        TIM2->CNT = 0U;
        CLEAR_BIT(TIM2->SR, TIM_SR_UIF);

        while (READ_BIT(TIM2->SR, TIM_SR_UIF) == 0U) {

        }
    }
}
