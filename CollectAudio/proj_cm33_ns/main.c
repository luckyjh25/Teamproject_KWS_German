

/*******************************************************************************
* Header Files
*******************************************************************************/


#include "cy_pdl.h"
#include "cy_pdm_pcm_v2.h"
#include "cy_scb_uart.h"
#include "cy_syslib.h"
#include "cybsp.h"
#include "cycfg_peripherals.h"
#include "mtb_hal.h"
#include "mtb_hal_hw_types_uart_scb.h"
#include "mtb_hal_uart.h"
#include <stdint.h>
#include <stdio.h>
#include <sys/_intsup.h>





/*******************************************************************************
 * Macros
 ******************************************************************************/




/*******************************************************************************
 * Global Variables
 ******************************************************************************/

static mtb_hal_uart_t uart;
static cy_stc_scb_uart_context_t context;

/*******************************************************************************
 * Function Name: main
 *******************************************************************************
 * 
 *
 ******************************************************************************/
int main(void)
{
    cy_rslt_t result;

    /* Initialize the device and board peripherals */
    result = cybsp_init();

    /* Board initialization failed. Stop program execution */
    if (CY_RSLT_SUCCESS != result)
    {
        
    }
	
	 __enable_irq();

	/**UART Setup*/
	Cy_SCB_UART_Init(UART_LOG_HW,&UART_LOG_config, &context);
	Cy_SCB_UART_Enable(UART_LOG_HW);

	mtb_hal_uart_setup(&uart, & UART_LOG_hal_config, &context, &UART_LOG_hal_clock);
	mtb_hal_uart_write_string(&uart, "Read Audio\r\n");

	/*Microphone PDM Setup*/	
	
   	Cy_PDM_PCM_Init(PDM0, &CYBSP_PDM_config);
	Cy_PDM_PCM_Channel_Init(PDM0, &channel_3_config, 3);
	Cy_PDM_PCM_Channel_Enable(PDM0, 3);
	Cy_PDM_PCM_Activate_Channel(PDM0, 3);


	//Micro Test ob Samples ankommen
	int32_t testsample =0;
    char testbuffer[64];
	
	while(1)
	{
		if(Cy_PDM_PCM_Channel_GetNumInFifo(PDM0, 3)>0)
		{
			testsample=Cy_PDM_PCM_Channel_ReadFifo(PDM0, 3);
			sprintf(testbuffer, "%ld\r\n",(long)testsample);
			mtb_hal_uart_write_string(&uart, testbuffer);
	        Cy_SysLib_Delay(50);
		}

	}
   
    /* Enable global interrupts */
   
      
     while(1);

    

}

/* [] END OF FILE */
