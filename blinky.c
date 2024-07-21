#include <stdint.h>

static uint32_t *RCC_AHB2ENR  = (uint32_t *)0x4002104c; // AHB2 peripheral clock enable reg
static uint32_t *GPIOB_MODER  = (uint32_t *)0x48000400; // GPIOB mode reg
static uint32_t *GPIOB_OTYPER = (uint32_t *)0x48000404; // GPIOB output type reg
static uint32_t *GPIOB_ODR    = (uint32_t *)0x48000414; // GPIOB output data reg
static uint32_t *GPIOB_BSRR   = (uint32_t *)0x48000418; // GPIOB bit set reset reg

void SystemInit(void)
{
    // System clock initialized automatically
    // Enable GPIOB clock
    *RCC_AHB2ENR |= 1U << 1;

    // Set output mode for PB6
    *GPIOB_MODER &= ~(1U << 13);
    *GPIOB_MODER |= (1U << 12);

    // Set push-pull output
    *GPIOB_OTYPER &= ~(1 << 6);
}

void _start(void)
{
    uint32_t is_set;
    int set_or_reset[2] = { 6, 22 };
    while (1)
    {
        is_set = (*GPIOB_ODR & (1 << 6)) >> 6;
        // Toggle PB6
        *GPIOB_BSRR = 1 << set_or_reset[is_set];
        for (int j = 0; j < 250000; j++)
        {
            ;
        }
    }

    // Link back to looping default handler
    return;
}
