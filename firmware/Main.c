/*
 Zhonghao Shi  UCL   Scenario X
 Descrambler
 */
#include "driverlib.h"
#include "filter.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#define PI 3.14159265f

//const bool DEBUG = true;

static volatile float currentADC = 0;
//static volatile float currentInput;

static volatile float sine[50];
int R = 0;
#define PTS 20

int main(void)
{
    /* Halting the Watchdog */
    MAP_WDT_A_holdTimer();
    
    /* Configure P5.6 and P5.7 to their analog functions to output VREF */
    P5SEL0 |= BIT6 | BIT7;
    P5SEL1 |= BIT6 | BIT7;
    
    
    REFCTL0 |= REFON;                     // Turn on reference module
    REFCTL0 |= REFOUT;                    // Output reference voltage to a pin
    
    
    /* Configuring pins for HFXT crystal */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_PJ,
                                                   GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
    
    /* Set P6.0 as output */
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P6, GPIO_PIN0);
    
    /* Set all 8 pins of P2 as output */
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3 | GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);
    
    
    /* Configuring GPIOs (4.3 MCLK) */
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P4, GPIO_PIN3,
                                                    GPIO_PRIMARY_MODULE_FUNCTION);
    
    /* Setting the external clock frequency. This API is optional, but will
     * come in handy if the user ever wants to use the getMCLK/getACLK/etc
     * functions
     */
    CS_setExternalClockSourceFrequency(32000,48000000);
    
    /* Starting HFXT in non-bypass mode without a timeout. Before we start
     * we have to change VCORE to 1 to support the 48MHz frequency */
    MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);
    MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
    MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);
    CS_startHFXT(false);
    
    /* Initializing MCLK to HFXT (effectively 48MHz) */
    MAP_CS_initClockSignal(CS_MCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);
    
    /* Configuring SysTick to trigger at 50kHz (MCLK is 48MHz so this will
     * make it toggle every 0.5s) */
    MAP_SysTick_enableModule();
    MAP_SysTick_setPeriod(960);
    MAP_Interrupt_enableSleepOnIsrExit();
    MAP_SysTick_enableInterrupt();
    
    /* Initializing ADC (MCLK/1//1) */
    MAP_ADC14_enableModule();
    MAP_ADC14_initModule(ADC_CLOCKSOURCE_MCLK, ADC_PREDIVIDER_1, ADC_DIVIDER_1,
                         0);
    
    /* Configuring GPIOs (P5.0 (A5) as the ADC input pin) */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN0,
                                                   GPIO_TERTIARY_MODULE_FUNCTION);
    
    /* Configure ADC Resolution */
    ADC14_setResolution(ADC_10BIT);
    
    
    /* Configuring ADC Memory */
    MAP_ADC14_configureSingleSampleMode(ADC_MEM0, true);
    MAP_ADC14_configureConversionMemory(ADC_MEM0, ADC_VREFPOS_INTBUF_VREFNEG_VSS,
                                        ADC_INPUT_A5, false);
    
    
    /* Configuring Sample Timer */
    MAP_ADC14_enableSampleTimer(ADC_MANUAL_ITERATION);
    
    
    /* Enabling MASTE4R interrupts */
    MAP_Interrupt_enableMaster();
    int N = 0;
    for(N=0;N<50;N++){
        float j = N*7.0f;
        float k = j/50.0f;
        float l = k*2.0f*PI;
        float n = sin(l);
        sine[N] = n;
    }
    while (1)
    {
        //MAP_PCM_gotoLPM0();
    }
}

void systick_isr(void)
{
    P6OUT |= BIT0; // P6.0 high
    
    
    static long temp_ADC = 0;
    
    temp_ADC = ADC14->MEM[0];  //Get the conversion result.  Alternatively, you can use temp_ADC = ADC14_getResult(ADC_MEM0)
    
    // 0 magnitude value - (600/1200)*16384
    float input =temp_ADC ;
    
    float input2 = input - 512.0f;
    float input_bandstop = bandstop(input2);
    
    float input_bandstop_sine = (input_bandstop*sine[R]);
    float input_lowpass_sine = lowpass(input_bandstop_sine);
    float filtered = input_lowpass_sine + 512.0f;
    
    //float filtered = input_bandstop +512.0f;
    
    float output = filtered / 4;
    
    P2OUT = output;
    //P2OUT = temp_ADC/4 ;
    
    
    R = R+1;
    if(R > 49){  // 7 full sine waves, 50 samples
        R = 0;
    }
    MAP_ADC14_enableConversion();
    MAP_ADC14_toggleConversionTrigger();
    MAP_ADC14_toggleConversionTrigger();
    
    P6OUT &= ~BIT0; // P6.0 low
}


/* ADC Interrupt Handler. This handler is called whenever there is a conversion
 * that is finished for ADC_MEM0.
 */
void adc_isr(void)
{
    
    uint64_t status = MAP_ADC14_getEnabledInterruptStatus();
    MAP_ADC14_clearInterruptFlag(status);
    
    if (status & ADC_INT0){
        currentADC = MAP_ADC14_getResult(ADC_MEM0);
    }
    
}




