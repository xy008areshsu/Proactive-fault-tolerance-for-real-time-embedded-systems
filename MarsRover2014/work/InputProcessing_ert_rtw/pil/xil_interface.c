/*
 * File: xil_interface.c
 *
 * PIL generated interface for code: "InputProcessing"
 *
 */

#include "xil_interface.h"
#include "InputProcessing.h"
#include "xil_instrumentation.h"

/* Functions with a C call interface */
#ifdef __cplusplus

extern "C" {

#endif

#include "xil_data_stream.h"
#ifdef __cplusplus

}
#endif

static XILIOData xil_fcnid0_task1_u[7];
static XILIOData xil_fcnid0_task1_y[6];
static XILIOData xil_fcnid0_init_y[6];
static XILIOData xil_fcnid0_term_y[6];
static XILIOData xil_fcnid0_ws_params[7];

/* In-the-Loop Interface functions - see xil_interface.h */
XIL_INTERFACE_ERROR_CODE xilProcessParams(uint32_T xilFcnId)
{
  /* Single In-the-Loop Component */
  if (xilFcnId != 0) {
    return XIL_INTERFACE_UNKNOWN_FCNID;
  }

  return XIL_INTERFACE_SUCCESS;
}

void xilUploadCodeInstrData(void * pData, uint32_T numMemUnits, uint32_T
  sectionId)
{
  /* Send code instrumentation data to host */
  if (codeInstrWriteData((MemUnit_T *) &numMemUnits, sizeof(numMemUnits)) !=
      XIL_DATA_STREAM_SUCCESS) {
    for (;;) ;
  }

  if (codeInstrWriteData((MemUnit_T *) &sectionId, sizeof(uint32_T)) !=
      XIL_DATA_STREAM_SUCCESS) {
    for (;;) ;
  }

  if (codeInstrWriteData((MemUnit_T *) pData, numMemUnits) !=
      XIL_DATA_STREAM_SUCCESS) {
    for (;;) ;
  }
}

XIL_INTERFACE_ERROR_CODE xilGetDataTypeInfo(void)
{
  {
    /* send response id code */
    MemUnit_T memUnitData = XIL_RESPONSE_TYPE_SIZE;
    if (xilWriteData(&memUnitData, sizeof(memUnitData)) !=
        XIL_DATA_STREAM_SUCCESS) {
      return XIL_INTERFACE_COMMS_FAILURE;
    }

    /* send type id */
    memUnitData = 1;
    if (xilWriteData(&memUnitData, sizeof(memUnitData)) !=
        XIL_DATA_STREAM_SUCCESS) {
      return XIL_INTERFACE_COMMS_FAILURE;
    }

    /* PIL_FLOAT_SIZE should only be already defined for MathWorks testing */
#ifndef PIL_FLOAT_SIZE
#define PIL_FLOAT_SIZE                 sizeof(float)
#endif

    /* send size in bytes */
    memUnitData = (MemUnit_T) PIL_FLOAT_SIZE;

#ifndef HOST_WORD_ADDRESSABLE_TESTING

    /* convert MemUnits to bytes */
    memUnitData *= MEM_UNIT_BYTES;

#endif

    if (xilWriteData(&memUnitData, sizeof(memUnitData)) !=
        XIL_DATA_STREAM_SUCCESS) {
      return XIL_INTERFACE_COMMS_FAILURE;
    }
  }

  {
    /* send response id code */
    MemUnit_T memUnitData = XIL_RESPONSE_TYPE_SIZE;
    if (xilWriteData(&memUnitData, sizeof(memUnitData)) !=
        XIL_DATA_STREAM_SUCCESS) {
      return XIL_INTERFACE_COMMS_FAILURE;
    }

    /* send type id */
    memUnitData = 0;
    if (xilWriteData(&memUnitData, sizeof(memUnitData)) !=
        XIL_DATA_STREAM_SUCCESS) {
      return XIL_INTERFACE_COMMS_FAILURE;
    }

    /* PIL_DOUBLE_SIZE should only be already defined for MathWorks testing */
#ifndef PIL_DOUBLE_SIZE
#define PIL_DOUBLE_SIZE                sizeof(double)
#endif

    /* send size in bytes */
    memUnitData = (MemUnit_T) PIL_DOUBLE_SIZE;

#ifndef HOST_WORD_ADDRESSABLE_TESTING

    /* convert MemUnits to bytes */
    memUnitData *= MEM_UNIT_BYTES;

#endif

    if (xilWriteData(&memUnitData, sizeof(memUnitData)) !=
        XIL_DATA_STREAM_SUCCESS) {
      return XIL_INTERFACE_COMMS_FAILURE;
    }
  }

  return XIL_INTERFACE_SUCCESS;
}

XIL_INTERFACE_ERROR_CODE xilInitialize(uint32_T xilFcnId)
{
  XIL_INTERFACE_ERROR_CODE errorCode = XIL_INTERFACE_SUCCESS;

  /* initialize output storage owned by In-the-Loop */
  /* Single In-the-Loop Component */
  if (xilFcnId == 0) {
    taskTimeStart_InputProcessing(1U);
    InputProcessing_initialize();
    taskTimeEnd_InputProcessing(1U);
  } else {
    errorCode = XIL_INTERFACE_UNKNOWN_FCNID;
  }

  return errorCode;
}

XIL_INTERFACE_ERROR_CODE xilInitializeConditions(uint32_T xilFcnId)
{
  XIL_INTERFACE_ERROR_CODE errorCode = XIL_INTERFACE_SUCCESS;

  /* Single In-the-Loop Component */
  if (xilFcnId == 0) {
    /* No Initialize Conditions Function to Call */
  } else {
    errorCode = XIL_INTERFACE_UNKNOWN_FCNID;
  }

  return errorCode;
}

XIL_INTERFACE_ERROR_CODE xilGetHostToTargetData(uint32_T xilFcnId,
  XIL_COMMAND_TYPE_ENUM xilCommandType, uint32_T xilCommandIdx, XILIOData
  ** xilIOData)
{
  XIL_INTERFACE_ERROR_CODE errorCode = XIL_INTERFACE_SUCCESS;
  *xilIOData = 0;

  /* Single In-the-Loop Component */
  if (xilFcnId != 0) {
    errorCode = XIL_INTERFACE_UNKNOWN_FCNID;
    return errorCode;
  }

  switch (xilCommandType) {
   case XIL_PROCESS_PARAMS_COMMAND:
    {
      static int initComplete = 0;
      if (!initComplete) {
        uint32_T tableIdx = 0;

        {
          void * dataAddress = (void *) &(InputProcessing_P.pcam[0]);
          xil_fcnid0_ws_params[tableIdx].memUnitLength = 2 * sizeof(real_T);
          xil_fcnid0_ws_params[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(InputProcessing_P.startPos[0]);
          xil_fcnid0_ws_params[tableIdx].memUnitLength = 2 * sizeof(real_T);
          xil_fcnid0_ws_params[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(InputProcessing_P.AxleLength);
          xil_fcnid0_ws_params[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_ws_params[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(InputProcessing_P.EncRes);
          xil_fcnid0_ws_params[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_ws_params[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(InputProcessing_P.WheelRadius);
          xil_fcnid0_ws_params[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_ws_params[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(InputProcessing_P.do_one_run);
          xil_fcnid0_ws_params[tableIdx].memUnitLength = 1 * sizeof(boolean_T);
          xil_fcnid0_ws_params[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        xil_fcnid0_ws_params[tableIdx].memUnitLength = 0;
        xil_fcnid0_ws_params[tableIdx++].address = (MemUnit_T *) 0;
        initComplete = 1;
      }

      *xilIOData = &xil_fcnid0_ws_params[0];
      break;
    }

   case XIL_STEP_COMMAND:
    {
      static int initComplete = 0;
      if (!initComplete) {
        uint32_T tableIdx = 0;

        {
          void * dataAddress = (void *) &(InputProcessing_U.Targets[0]);
          xil_fcnid0_task1_u[tableIdx].memUnitLength = 16 * sizeof(real32_T);
          xil_fcnid0_task1_u[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(InputProcessing_U.EncoderLeft);
          xil_fcnid0_task1_u[tableIdx].memUnitLength = 1 * sizeof(int32_T);
          xil_fcnid0_task1_u[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(InputProcessing_U.EncoderRight);
          xil_fcnid0_task1_u[tableIdx].memUnitLength = 1 * sizeof(int32_T);
          xil_fcnid0_task1_u[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(InputProcessing_U.distance[0]);
          xil_fcnid0_task1_u[tableIdx].memUnitLength = 6 * sizeof(int16_T);
          xil_fcnid0_task1_u[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(InputProcessing_U.bearing[0]);
          xil_fcnid0_task1_u[tableIdx].memUnitLength = 6 * sizeof(int8_T);
          xil_fcnid0_task1_u[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(InputProcessing_U.Go);
          xil_fcnid0_task1_u[tableIdx].memUnitLength = 1 * sizeof(boolean_T);
          xil_fcnid0_task1_u[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        xil_fcnid0_task1_u[tableIdx].memUnitLength = 0;
        xil_fcnid0_task1_u[tableIdx++].address = (MemUnit_T *) 0;
        initComplete = 1;
      }

      *xilIOData = &xil_fcnid0_task1_u[0];
      break;
    }

   default:
    errorCode = XIL_INTERFACE_UNKNOWN_TID;
    break;
  }

  UNUSED_PARAMETER(xilCommandIdx);
  return errorCode;
}

XIL_INTERFACE_ERROR_CODE xilOutput(uint32_T xilFcnId, uint32_T xilTID)
{
  /* Single In-the-Loop Component */
  if (xilFcnId != 0) {
    return XIL_INTERFACE_UNKNOWN_FCNID;
  }

  switch (xilTID) {
   case 1:
    taskTimeStart_InputProcessing(2U);
    InputProcessing_step();
    taskTimeEnd_InputProcessing(2U);
    break;

   default:
    return XIL_INTERFACE_UNKNOWN_TID;
  }

  return XIL_INTERFACE_SUCCESS;
}

XIL_INTERFACE_ERROR_CODE xilUpdate(uint32_T xilFcnId, uint32_T xilTID)
{
  /* Single In-the-Loop Component */
  if (xilFcnId != 0) {
    return XIL_INTERFACE_UNKNOWN_FCNID;
  }

  /* No Update Function */
  UNUSED_PARAMETER(xilTID);
  return XIL_INTERFACE_SUCCESS;
}

XIL_INTERFACE_ERROR_CODE xilGetTargetToHostData(uint32_T xilFcnId,
  XIL_COMMAND_TYPE_ENUM xilCommandType, uint32_T xilCommandIdx, XILIOData
  ** xilIOData)
{
  XIL_INTERFACE_ERROR_CODE errorCode = XIL_INTERFACE_SUCCESS;

  /* Single In-the-Loop Component */
  *xilIOData = 0;
  if (xilFcnId != 0) {
    errorCode = XIL_INTERFACE_UNKNOWN_FCNID;
    return errorCode;
  }

  switch (xilCommandType) {
   case XIL_INITIALIZE_COMMAND:
    {
      static int initComplete = 0;
      if (!initComplete) {
        uint32_T tableIdx = 0;

        {
          void * dataAddress = (void *) &(InputProcessing_Y.BearingtoTarget);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(InputProcessing_Y.DistancetoTarget);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(InputProcessing_Y.doBeep);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(boolean_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(InputProcessing_Y.doScan);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(boolean_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(InputProcessing_Y.allTargetsDone);
          xil_fcnid0_init_y[tableIdx].memUnitLength = 1 * sizeof(boolean_T);
          xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        xil_fcnid0_init_y[tableIdx].memUnitLength = 0;
        xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) 0;
        initComplete = 1;
      }

      *xilIOData = &xil_fcnid0_init_y[0];
      break;
    }

   case XIL_TERMINATE_COMMAND:
    {
      static int initComplete = 0;
      if (!initComplete) {
        uint32_T tableIdx = 0;

        {
          void * dataAddress = (void *) &(InputProcessing_Y.BearingtoTarget);
          xil_fcnid0_term_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_term_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(InputProcessing_Y.DistancetoTarget);
          xil_fcnid0_term_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_term_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(InputProcessing_Y.doBeep);
          xil_fcnid0_term_y[tableIdx].memUnitLength = 1 * sizeof(boolean_T);
          xil_fcnid0_term_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(InputProcessing_Y.doScan);
          xil_fcnid0_term_y[tableIdx].memUnitLength = 1 * sizeof(boolean_T);
          xil_fcnid0_term_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(InputProcessing_Y.allTargetsDone);
          xil_fcnid0_term_y[tableIdx].memUnitLength = 1 * sizeof(boolean_T);
          xil_fcnid0_term_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        xil_fcnid0_term_y[tableIdx].memUnitLength = 0;
        xil_fcnid0_term_y[tableIdx++].address = (MemUnit_T *) 0;
        initComplete = 1;
      }

      *xilIOData = &xil_fcnid0_term_y[0];
      break;
    }

   case XIL_STEP_COMMAND:
    {
      static int initComplete = 0;
      if (!initComplete) {
        uint32_T tableIdx = 0;

        {
          void * dataAddress = (void *) &(InputProcessing_Y.BearingtoTarget);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(InputProcessing_Y.DistancetoTarget);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(real32_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(InputProcessing_Y.doBeep);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(boolean_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(InputProcessing_Y.doScan);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(boolean_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        {
          void * dataAddress = (void *) &(InputProcessing_Y.allTargetsDone);
          xil_fcnid0_task1_y[tableIdx].memUnitLength = 1 * sizeof(boolean_T);
          xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
        }

        xil_fcnid0_task1_y[tableIdx].memUnitLength = 0;
        xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) 0;
        initComplete = 1;
      }

      *xilIOData = &xil_fcnid0_task1_y[0];
      break;
    }

   default:
    errorCode = XIL_INTERFACE_UNKNOWN_TID;
    break;
  }

  UNUSED_PARAMETER(xilCommandIdx);
  return errorCode;
}

XIL_INTERFACE_ERROR_CODE xilTerminate(uint32_T xilFcnId)
{
  /* Single In-the-Loop Component */
  if (xilFcnId != 0) {
    return XIL_INTERFACE_UNKNOWN_FCNID;
  }

  taskTimeStart_InputProcessing(3U);
  InputProcessing_terminate();
  taskTimeEnd_InputProcessing(3U);
  return XIL_INTERFACE_SUCCESS;
}

XIL_INTERFACE_ERROR_CODE xilEnable(uint32_T xilFcnId, uint32_T xilTID)
{
  /* Single In-the-Loop Component */
  if (xilFcnId != 0) {
    return XIL_INTERFACE_UNKNOWN_FCNID;
  }

  UNUSED_PARAMETER(xilTID);

  /* No Enable Function - this function should never be called */
  return XIL_INTERFACE_UNKNOWN_TID;
}

XIL_INTERFACE_ERROR_CODE xilDisable(uint32_T xilFcnId, uint32_T xilTID)
{
  /* Single In-the-Loop Component */
  if (xilFcnId != 0) {
    return XIL_INTERFACE_UNKNOWN_FCNID;
  }

  UNUSED_PARAMETER(xilTID);

  /* No Disable Function - this function should never be called */
  return XIL_INTERFACE_UNKNOWN_TID;
}
