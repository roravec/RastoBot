#include "ADC_PIC32MK.h"

void ADC_Init(void)
{
    /* Calibrate the ADCs by using these values contained in the DEVADC registers */
    ADC0CFG = DEVADC0; // Load the calibration numbers into the ADCs
    ADC1CFG = DEVADC1;
    ADC2CFG = DEVADC2;
    ADC3CFG = DEVADC3;
    ADC4CFG = DEVADC4;
    ADC7CFG = DEVADC7;
    
        /* No selection for dedicated ADC modules, no presync trigger, not sync sampling */
    ADCTRGMODE = 0;
    /* Configure ADCGIRQENx */
    ADCGIRQEN1 = 0; // No interrupts are used
    ADCGIRQEN2 = 0;
    /* Configure ADCCSSx */
    ADCCSS1 = 0; // No scanning is used
    ADCCSS2 = 0;
    /* Configure ADCCMPCONx */
    ADCCMPCON1 = 0; // No digital comparators are used. Setting the ADCCMPCONx
    ADCCMPCON2 = 0; // register to '0' ensures that the comparator is disabled.
    ADCCMPCON3 = 0; // Other registers are ?don't care?.
    ADCCMPCON4 = 0;
    /* Configure ADCFLTRx */
    ADCFLTR1 = 0; // No oversampling filters are used.
    ADCFLTR2 = 0;
    ADCFLTR3 = 0;
    ADCFLTR4 = 0;
    /* Early interrupt */
    ADCEIEN1 = 0; // No early interrupt
    ADCEIEN2 = 0;
    ADCANCON = 0;
    ADCCON3 = 0;
    ADCCON1bits.ON = 0;             // turn off ADC before initialization
    ADCIMCON2bits.DIFF19 = 0;       // AN19 is not differential
    ADCIMCON2bits.SIGN19 = 1;       // AN19 uses unsigned data format
    ADCTRGSNSbits.LVL19 = 0;        // edge trigger
    ADCTRG5bits.TRGSRC19 = 1;       // SW trigger, try 3
    ADCCON1bits.STRGSRC = 1;
    
    //ADCTRGMODEbits.
    
    /* Configure ADCCON1 */
    ADCCON1bits.FRACT = 1;          // use Fractional output format
    ADCCON1bits.SELRES = 3;         // ADC7 resolution is 12 bits
    //ADCCON1bits.STRGSRC = 0;      // No scan trigger.
    /* Configure ADCCON2 */
    ADCCON2bits.SAMC = 5;           // ADC7 sampling time = 5 * TAD7
    ADCCON2bits.ADCDIV = 1;         // ADC7 clock freq is half of control clock = TAD7
    /* Initialize warm up time register */
    ADCANCONbits.WKUPCLKCNT = 5;    // Wakeup exponent = 32 * TADx
    ADCANCONbits.ANEN7 = 0;         // 
    /* Clock setting */
    ADCCON3bits.ADCSEL = 1;         // Select input clock source SYSCLK
    ADCCON3bits.CONCLKDIV = 1;      // Control clock frequency is half of input clock
    ADCCON3bits.VREFSEL = 0;        // voltage reference
    ADCCON3bits.ADINSEL = 19;       // select AN19 as input
    
    ADCSYSCFG0bits.AN19 = 1;
    ADCCON1bits.ON = 1;             // turn on ADC
    
    /* Wait for voltage reference to be stable */
    while(!ADCCON2bits.BGVRRDY); // Wait until the reference voltage is ready
    while(ADCCON2bits.REFFLT); // Wait if there is a fault with the reference voltage
    /* Enable clock to analog circuit */
    ADCANCONbits.ANEN7 = 1; // Enable the clock to analog bias
    /* Wait for ADC to be ready */
    while(!ADCANCONbits.WKRDY7); // Wait until ADC7 is ready
    /* Enable the ADC module */
    ADCCON3bits.DIGEN7 = 1; // Enable ADC7
}

uint32_t ADC_ReadData_AN19(void)
{
    /* Trigger a conversion */
    ADCCON3bits.GSWTRG = 1;
    /* Wait the conversions to complete */
    while (ADCDSTAT1bits.ARDY19 == 0);
    /* fetch the result */
    uint32_t data = (ADCDATA19);
    return data;
}