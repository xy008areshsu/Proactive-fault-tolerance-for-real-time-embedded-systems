/*
 * File: xil_instrumentation.c
 *
 * Code generated for instrumentation.
 *
 */

#include "xil_instrumentation.h"

/* Code instrumentation offset(s) for model InputProcessing */
#define taskTimeStart_InputProcessing_offset 0
#define taskTimeEnd_InputProcessing_offset 0
#define SIZEOF_TIMER_TYPE              sizeof(uint32_T)

static uint32_T xsd_xil_timer_corrected = 0;
static uint32_T xsd_xil_timer_freeze = 0;
static uint32_T xsd_xil_timer_unfreeze = 0;
void xilUploadProfilingData(uint32_T sectionId)
{
  xilProfilingUpdateCorrectedTimer();
  xilUploadCodeInstrData((void *)(&xsd_xil_timer_corrected), (uint32_T)
    (SIZEOF_TIMER_TYPE), sectionId);
}

void xilProfilingUpdateCorrectedTimer( void )
{
  /* Update the value of the corrected timer to exclude time spent in the
   * previous call to the instrumentation code.
   *
   * Using a timer that increments on each tick.
   */
  xsd_xil_timer_corrected = xsd_xil_timer_corrected
    + (xsd_xil_timer_freeze - xsd_xil_timer_unfreeze);
}

void xilProfilingTimerFreeze(void)
{
  xsd_xil_timer_freeze = (uint32_T) (profileTimerRead());
}

void xilProfilingTimerUnFreeze(void)
{
  xsd_xil_timer_unfreeze = ( uint32_T ) (profileTimerRead());
}

void taskTimeStart(uint32_T sectionId)
{
  /* Send execution profiling data to host */
  xilUploadProfilingData(sectionId);
  xilProfilingTimerUnFreeze();
}

void taskTimeEnd(uint32_T sectionId)
{
  uint32_T sectionIdNeg = ~sectionId;
  xilProfilingTimerFreeze();

  /* Send execution profiling data to host */
  xilUploadProfilingData(sectionIdNeg);
}

/* Code instrumentation method(s) for model InputProcessing */
void taskTimeStart_InputProcessing(uint32_T sectionId)
{
  taskTimeStart(taskTimeStart_InputProcessing_offset + sectionId);
}

void taskTimeEnd_InputProcessing(uint32_T sectionId)
{
  taskTimeEnd(taskTimeEnd_InputProcessing_offset + sectionId);
}
