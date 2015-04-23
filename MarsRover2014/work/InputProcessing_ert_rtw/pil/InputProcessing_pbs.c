/*
 * InputProcessing_pbs.c
 *
 * Automatically generated s-function with I/O interface for:
 * Component: InputProcessing
 * Component Simulink Path: InputProcessing
 * Simulation Mode: PIL
 *
 */

#define S_FUNCTION_NAME                InputProcessing_pbs
#define S_FUNCTION_LEVEL               2
#if !defined(RTW_GENERATED_S_FUNCTION)
#define RTW_GENERATED_S_FUNCTION
#endif

#include <stdio.h>
#include <string.h>
#include "simstruc.h"
#include "simtarget/slMdlrefSimTargetHeaders.h"
#include "fixedpoint.h"
#include "coder/connectivity_core/xilutils/xilutils.h"
#include "coder/connectivity/xilutils_sl/xilutils_sl.h"
#include "rtiostream_utils.h"
#include "coder/connectivity/xilcomms_rtiostream/xilcomms_rtiostream.h"
#include "coder/connectivity/xilservice/host/CInterface.h"
#include "coderprofile/codeinstr_service/host/CInterface.h"

/* Response case labels */
enum ResponseIDs {
  RESPONSE_ERROR = 0,
  RESPONSE_OUTPUT_DATA = 1,
  RESPONSE_PRINTF = 2,
  RESPONSE_FOPEN = 3,
  RESPONSE_FPRINTF = 4
};

typedef struct {
  FILE ** Fd;
  mwSize size;
  int32_T fidOffset;
} targetIOFd_T;

/* implements calls into MATLAB */
static int callMATLAB(SimStruct * S,
                      int nlhs,
                      mxArray * plhs[],
                      int nrhs,
                      mxArray * prhs[],
                      const char * functionName,
                      int withTrap)
{
  int errorOccurred = 0;
  if (withTrap) {
    mxArray * mException;
    mException = mexCallMATLABWithTrap(nlhs, plhs, nrhs, prhs, functionName);

    {
      int i;
      for (i=0; i<nrhs; i++) {
        mxDestroyArray(prhs[i]);
      }                                /* for */
    }

    if (mException != NULL) {
      mxArray * rhsDisplayMException[1];
      errorOccurred = 1;
      rhsDisplayMException[0] = mException;
      mException = mexCallMATLABWithTrap(0, NULL, 1, rhsDisplayMException,
        "rtw.pil.SILPILInterface.displayMException");
      mxDestroyArray(rhsDisplayMException[0]);
      if (mException != NULL) {
        mxDestroyArray(mException);
        ssSetErrorStatus( S,
                         "Error calling rtw.pil.SILPILInterface.displayMException on mException object.");
      } else {
        ssSetErrorStatus( S,
                         "See the preceding MException report for more details.");
      }                                /* if */
    }                                  /* if */
  } else {
    errorOccurred = mexCallMATLAB(nlhs, plhs, nrhs, prhs, functionName);

    {
      int i;
      for (i=0; i<nrhs; i++) {
        mxDestroyArray(prhs[i]);
      }                                /* for */
    }

    if (errorOccurred) {
      ssSetErrorStatus( S,"mexCallMATLAB failed!");
    }                                  /* if */
  }                                    /* if */

  return errorOccurred;
}

/* grow the buffer for target I/O Fd array
 * targetIOFd->Fd is NULL on failure */
static void growTargetIOFd(SimStruct *S, targetIOFd_T * IOFd, mwSize
  requiredSize)
{
  if (IOFd->size < requiredSize) {
    IOFd->Fd = mxRealloc(IOFd->Fd, requiredSize * sizeof(FILE*));
    if (IOFd->Fd == NULL) {
      ssSetErrorStatus( S,"growTargetIOFd: mxRealloc failed.");
    } else {
      mexMakeMemoryPersistent(IOFd->Fd);
      IOFd->size = requiredSize;
    }                                  /* if */
  }                                    /* if */
}

static void closeAndFreeTargetIOFd(SimStruct *S)
{
  int i;
  if (ssGetPWork(S) != NULL) {
    targetIOFd_T * targetIOFdPtr = (targetIOFd_T *) ssGetPWorkValue(S, 3);
    if (targetIOFdPtr != NULL) {
      if (targetIOFdPtr->Fd != NULL) {
        for (i=0; i<targetIOFdPtr->size; i++) {
          if (targetIOFdPtr->Fd[i] != NULL) {
            fclose(targetIOFdPtr->Fd[i]);
          }                            /* if */
        }                              /* for */

        mxFree(targetIOFdPtr->Fd);
      }                                /* if */

      mxFree(targetIOFdPtr);
    }                                  /* if */

    ssSetPWorkValue(S, 3, NULL);
  }                                    /* if */
}

/* receive one packet of data and dispatch to owning application */
static boolean_T recvData(SimStruct *S, void* pComms)
{
  int * pCommErrorOccurred = (int *) ssGetPWorkValue(S, 4);
  void * pXILUtils = (void *) ssGetPWorkValue(S, 5);
  if (pCommErrorOccurred == NULL) {
    ssSetErrorStatus( S,"pCommErrorOccurred is NULL.");
    return XILSERVICE_ERROR;
  }                                    /* if */

  if (pXILUtils == NULL) {
    ssSetErrorStatus( S,"pXILUtils is NULL.");
    return XILSERVICE_ERROR;
  }                                    /* if */

  *pCommErrorOccurred = (xilCommsRun(pComms, pXILUtils) !=
    XILCOMMS_RTIOSTREAM_SUCCESS);
  return (*pCommErrorOccurred?XILSERVICE_ERROR:XILSERVICE_SUCCESS);
}

/* send data via xil comms */
static boolean_T sendData(SimStruct *S, void* pXILService, XIL_IOBuffer_T
  * IOBuffer, mwSize sendSize)
{
  int * pCommErrorOccurred = (int *) ssGetPWorkValue(S, 4);
  if (pCommErrorOccurred == NULL) {
    ssSetErrorStatus( S,"pCommErrorOccurred is NULL.");
    return XILSERVICE_ERROR;
  }                                    /* if */

  *pCommErrorOccurred = (xilServiceSend(pXILService, IOBuffer->data, sendSize)
    != XILSERVICE_SUCCESS);
  return (*pCommErrorOccurred?XILSERVICE_ERROR:XILSERVICE_SUCCESS);
}

/* implements command dispatch */
static boolean_T commandDispatch(SimStruct *S, XIL_IOBuffer_T* IOBuffer, mwSize
  dataOutSize)
{
  void * pXILService = (void *) ssGetPWorkValue(S, 7);
  if (pXILService == NULL) {
    ssSetErrorStatus( S,"pXILService is NULL!");
    return XILSERVICE_ERROR;
  }                                    /* if */

  /* send the data */
  if (sendData(S, pXILService, IOBuffer, dataOutSize) != XILSERVICE_SUCCESS) {
    return XILSERVICE_ERROR;
  }                                    /* if */

  return XILSERVICE_SUCCESS;
}

/* implements command response */
static boolean_T commandResponse(SimStruct *S, mwSize * dataInSize,
  XILCommandResponseType* commandType)
{
  void * pComms = (void *) ssGetPWorkValue(S, 6);
  void * pXILService = (void *) ssGetPWorkValue(S, 7);
  if (pComms == NULL) {
    ssSetErrorStatus( S,"pComms is NULL!");
    return XILSERVICE_ERROR;
  }                                    /* if */

  if (pXILService == NULL) {
    ssSetErrorStatus( S,"pXILService is NULL!");
    return XILSERVICE_ERROR;
  }                                    /* if */

  {
    /* receive the response data */
    uint8_T COMMAND_COMPLETE = 0;
    while (!COMMAND_COMPLETE) {
      xilServiceSetIsResponseComplete(pXILService, 0);
      if (recvData(S, pComms) != XILSERVICE_SUCCESS) {
        return XILSERVICE_ERROR;
      }                                /* if */

      COMMAND_COMPLETE = xilServiceGetIsResponseComplete(pXILService);
    }                                  /* while */

    /* determine command response type */
    *commandType = (XILCommandResponseType) COMMAND_COMPLETE;
    *dataInSize = xilServiceGetPayloadSizeForOneStep(pXILService);
    return XILSERVICE_SUCCESS;
  }
}

static void copyIOData(void * const dstPtr, void * const srcPtr, uint8_T **
  const tgtPtrPtr, size_t numElements, size_t cTypeSize)
{
  size_t maxBytesConsumed = numElements * cTypeSize;
  memcpy(dstPtr, srcPtr, maxBytesConsumed);
  (*tgtPtrPtr)+=(maxBytesConsumed/sizeof(**tgtPtrPtr));
}

static boolean_T processResponseError(SimStruct * S, uint8_T ** mxMemUnitPtrPtr,
  const int withTrap)
{
  uint8_T errorId = **mxMemUnitPtrPtr;
  (*mxMemUnitPtrPtr)++;
  if (errorId) {
    {
      mxArray * prhs[ 2 ];
      prhs[0] = mxCreateString("PIL:pilverification:PILError");
      prhs[1] = mxCreateDoubleScalar(errorId);
      callMATLAB(S, 0, NULL, 2, prhs, "DAStudio.error", withTrap);
      return XILSERVICE_ERROR;
    }
  }                                    /* if */

  return XILSERVICE_SUCCESS;
}

static boolean_T processResponsePrintf(SimStruct * S, uint8_T ** mxMemUnitPtrPtr,
  const int withTrap)
{
  const int TARGET_IO_SUCCESS = 0;
  uint8_T PRINTF_ERROR;
  uint16_T PRINTF_SIZE;

  {
    uint8_T * simDataMemUnitPtr;
    simDataMemUnitPtr = (uint8_T *) &PRINTF_ERROR;

    {
      copyIOData( simDataMemUnitPtr, *mxMemUnitPtrPtr, &(*mxMemUnitPtrPtr), 1,
                 sizeof(uint8_T));
    }
  }

  {
    uint8_T * simDataMemUnitPtr;
    simDataMemUnitPtr = (uint8_T *) &PRINTF_SIZE;

    {
      copyIOData( simDataMemUnitPtr, *mxMemUnitPtrPtr, &(*mxMemUnitPtrPtr), 1,
                 sizeof(uint16_T));
    }
  }

  if (PRINTF_ERROR != TARGET_IO_SUCCESS) {
    {
      mxArray * prhs[ 2 ];
      prhs[0] = mxCreateString("PIL:pil:TargetIOError");
      prhs[1] = mxCreateDoubleScalar(PRINTF_ERROR);
      callMATLAB(S, 0, NULL, 2, prhs, "DAStudio.error", withTrap);
      return XILSERVICE_ERROR;
    }
  } else {
    uint8_T *pPrintBuff;
    pPrintBuff = *mxMemUnitPtrPtr;
    if (pPrintBuff[PRINTF_SIZE-1] == '\0') {
      mexPrintf("%s", pPrintBuff);
    }                                  /* if */
  }                                    /* if */

  (*mxMemUnitPtrPtr) = (*mxMemUnitPtrPtr) + PRINTF_SIZE;
  return XILSERVICE_SUCCESS;
}

static boolean_T processResponseFopen(SimStruct * S, uint8_T ** mxMemUnitPtrPtr,
  const int withTrap)
{
  uint16_T FOPEN_FID;
  uint16_T FOPEN_NAME_SIZE;
  targetIOFd_T *targetIOFdPtr;

  {
    uint8_T * simDataMemUnitPtr;
    simDataMemUnitPtr = (uint8_T *) &FOPEN_FID;

    {
      copyIOData( simDataMemUnitPtr, *mxMemUnitPtrPtr, &(*mxMemUnitPtrPtr), 1,
                 sizeof(uint16_T));
    }
  }

  {
    uint8_T * simDataMemUnitPtr;
    simDataMemUnitPtr = (uint8_T *) &FOPEN_NAME_SIZE;

    {
      copyIOData( simDataMemUnitPtr, *mxMemUnitPtrPtr, &(*mxMemUnitPtrPtr), 1,
                 sizeof(uint16_T));
    }
  }

  targetIOFdPtr = (targetIOFd_T *) ssGetPWorkValue(S, 3);
  if (targetIOFdPtr != NULL) {
    /* check fid increments by 1 */
    if (targetIOFdPtr->fidOffset + 1 == FOPEN_FID) {
      targetIOFdPtr->fidOffset = FOPEN_FID;
      growTargetIOFd(S, targetIOFdPtr, targetIOFdPtr->fidOffset + 1);
      if (targetIOFdPtr->Fd != NULL) {
        uint8_T *pFopenBuff;
        targetIOFdPtr->Fd[targetIOFdPtr->fidOffset] = NULL;
        pFopenBuff = (*mxMemUnitPtrPtr);
        if (pFopenBuff[FOPEN_NAME_SIZE-1] == '\0') {
          FILE * tmpFd = NULL;
          tmpFd = fopen((char *) pFopenBuff,"w");
          if (tmpFd != NULL) {
            /* save the file descriptor */
            targetIOFdPtr->Fd[targetIOFdPtr->fidOffset] = tmpFd;
          } else {
            {
              mxArray * prhs[ 2 ];
              prhs[0] = mxCreateString("PIL:pil:TargetIOFopenError");
              prhs[1] = mxCreateString((char *) pFopenBuff);
              callMATLAB(S, 0, NULL, 2, prhs, "DAStudio.error", withTrap);
              return XILSERVICE_ERROR;
            }
          }                            /* if */
        }                              /* if */
      }                                /* if */
    } else {
      {
        mxArray * prhs[ 2 ];
        prhs[0] = mxCreateString("PIL:pil:TargetIOFopenFidError");
        prhs[1] = mxCreateDoubleScalar(FOPEN_FID);
        callMATLAB(S, 0, NULL, 2, prhs, "DAStudio.error", withTrap);
        return XILSERVICE_ERROR;
      }
    }                                  /* if */
  }                                    /* if */

  (*mxMemUnitPtrPtr) = (*mxMemUnitPtrPtr) + FOPEN_NAME_SIZE;
  return XILSERVICE_SUCCESS;
}

static boolean_T processResponseFprintf(SimStruct * S, uint8_T
  ** mxMemUnitPtrPtr, const int withTrap)
{
  const int TARGET_IO_SUCCESS = 0;
  uint8_T FPRINTF_ERROR;
  uint16_T FPRINTF_FID;
  uint16_T FPRINTF_SIZE;

  {
    uint8_T * simDataMemUnitPtr;
    simDataMemUnitPtr = (uint8_T *) &FPRINTF_ERROR;

    {
      copyIOData( simDataMemUnitPtr, *mxMemUnitPtrPtr, &(*mxMemUnitPtrPtr), 1,
                 sizeof(uint8_T));
    }
  }

  {
    uint8_T * simDataMemUnitPtr;
    simDataMemUnitPtr = (uint8_T *) &FPRINTF_FID;

    {
      copyIOData( simDataMemUnitPtr, *mxMemUnitPtrPtr, &(*mxMemUnitPtrPtr), 1,
                 sizeof(uint16_T));
    }
  }

  {
    uint8_T * simDataMemUnitPtr;
    simDataMemUnitPtr = (uint8_T *) &FPRINTF_SIZE;

    {
      copyIOData( simDataMemUnitPtr, *mxMemUnitPtrPtr, &(*mxMemUnitPtrPtr), 1,
                 sizeof(uint16_T));
    }
  }

  if (FPRINTF_ERROR != TARGET_IO_SUCCESS) {
    {
      mxArray * prhs[ 2 ];
      prhs[0] = mxCreateString("PIL:pil:TargetIOError");
      prhs[1] = mxCreateDoubleScalar(FPRINTF_ERROR);
      callMATLAB(S, 0, NULL, 2, prhs, "DAStudio.error", withTrap);
      return XILSERVICE_ERROR;
    }
  } else {
    targetIOFd_T * targetIOFdPtr = (targetIOFd_T *) ssGetPWorkValue(S, 3);
    if (targetIOFdPtr != NULL) {
      if (targetIOFdPtr->size > FPRINTF_FID) {
        if (targetIOFdPtr->Fd[FPRINTF_FID] != NULL) {
          uint8_T *pFprintfBuff;
          pFprintfBuff = (*mxMemUnitPtrPtr);
          if (pFprintfBuff[FPRINTF_SIZE-1] == '\0') {
            fprintf(targetIOFdPtr->Fd[FPRINTF_FID], "%s", pFprintfBuff);
          }                            /* if */
        }                              /* if */
      }                                /* if */
    }                                  /* if */
  }                                    /* if */

  (*mxMemUnitPtrPtr) = (*mxMemUnitPtrPtr) + FPRINTF_SIZE ;
  return XILSERVICE_SUCCESS;
}

static boolean_T processErrorAndTargetIOResponseCases(SimStruct * S, const int
  responseId, uint8_T ** mxMemUnitPtrPtr, const int withTrap)
{
  switch (responseId) {
   case RESPONSE_ERROR:
    {
      return processResponseError(S, mxMemUnitPtrPtr, withTrap);
    }

   case RESPONSE_PRINTF:
    {
      return processResponsePrintf(S, mxMemUnitPtrPtr, withTrap);
    }

   case RESPONSE_FOPEN:
    {
      return processResponseFopen(S, mxMemUnitPtrPtr, withTrap);
    }

   case RESPONSE_FPRINTF:
    {
      return processResponseFprintf(S, mxMemUnitPtrPtr, withTrap);
    }

   default:
    {
      {
        mxArray * prhs[ 2 ];
        prhs[0] = mxCreateString("PIL:pilverification:UnknownResponseId");
        prhs[1] = mxCreateDoubleScalar(responseId);
        callMATLAB(S, 0, NULL, 2, prhs, "DAStudio.error", withTrap);
        return XILSERVICE_ERROR;
      }
    }
  }                                    /* switch */
}

/* Process params function shared between mdlStart and mdlProcessParams */
static void processParams(SimStruct * S, boolean_T isMdlStartCall)
{
  int isOkToProcessParams;

  {
    {
      mxArray *rhs[3];
      mxArray *lhs[1];
      const char * simulinkBlockPath = ssGetPath(S);
      rhs[ 0 ] = mxCreateString(
        "@coder.connectivity.SimulinkInterface.getSILPILInterface");
      rhs[ 1 ] = mxCreateDoubleScalar( 2 );
      rhs[ 2 ] = mxCreateString(simulinkBlockPath);
      callMATLAB(S, 1, lhs, 3, rhs,
                 "rtw.pil.SILPILInterface.sfunctionIsOkToProcessParamsHook", 0);
      isOkToProcessParams = (int) (*mxGetPr(lhs[0]));
      mxDestroyArray(lhs[0]);
    }
  }

  if (isOkToProcessParams) {
    if (!isMdlStartCall) {
      /* update run time params */
      ssUpdateAllTunableParamsAsRunTimeParams(S);
    }                                  /* if */

    {
      uint8_T * mxMemUnitPtr;
      mwSize dataInSize = 0;
      XIL_IOBuffer_T * IOBufferPtr = (XIL_IOBuffer_T *) ssGetPWorkValue(S, 1);
      if (IOBufferPtr != NULL) {
        void * pXILService = (void *) ssGetPWorkValue(S, 7);
        if (pXILService != NULL) {
          if (xilServiceGrowIOBuffer(pXILService, IOBufferPtr, 50, 0)!=
              XILSERVICE_SUCCESS) {
            return;
          }                            /* if */

          if (IOBufferPtr->data != NULL) {
            mxMemUnitPtr = (uint8_T *) IOBufferPtr->data;

            /* write command id */
            *mxMemUnitPtr = 8;
            mxMemUnitPtr++;

            {
              uint8_T * simDataMemUnitPtr;
              uint32_T commandDataFcnid = 0;
              simDataMemUnitPtr = (uint8_T *) &commandDataFcnid;

              {
                copyIOData( mxMemUnitPtr, simDataMemUnitPtr, &(mxMemUnitPtr), 1,
                           sizeof(uint32_T));
              }
            }

            {
              uint8_T * simDataMemUnitPtr;
              simDataMemUnitPtr = (uint8_T *) ssGetRunTimeParamInfo(S, 0)->data;

              {
                copyIOData( mxMemUnitPtr, simDataMemUnitPtr, &(mxMemUnitPtr), 2,
                           sizeof(real64_T));
              }
            }

            {
              uint8_T * simDataMemUnitPtr;
              simDataMemUnitPtr = (uint8_T *) ssGetRunTimeParamInfo(S, 1)->data;

              {
                copyIOData( mxMemUnitPtr, simDataMemUnitPtr, &(mxMemUnitPtr), 2,
                           sizeof(real64_T));
              }
            }

            {
              uint8_T * simDataMemUnitPtr;
              simDataMemUnitPtr = (uint8_T *) ssGetRunTimeParamInfo(S, 2)->data;

              {
                copyIOData( mxMemUnitPtr, simDataMemUnitPtr, &(mxMemUnitPtr), 1,
                           sizeof(real32_T));
              }
            }

            {
              uint8_T * simDataMemUnitPtr;
              simDataMemUnitPtr = (uint8_T *) ssGetRunTimeParamInfo(S, 3)->data;

              {
                copyIOData( mxMemUnitPtr, simDataMemUnitPtr, &(mxMemUnitPtr), 1,
                           sizeof(real32_T));
              }
            }

            {
              uint8_T * simDataMemUnitPtr;
              simDataMemUnitPtr = (uint8_T *) ssGetRunTimeParamInfo(S, 4)->data;

              {
                copyIOData( mxMemUnitPtr, simDataMemUnitPtr, &(mxMemUnitPtr), 1,
                           sizeof(real32_T));
              }
            }

            {
              uint8_T * simDataMemUnitPtr;
              simDataMemUnitPtr = (uint8_T *) ssGetRunTimeParamInfo(S, 5)->data;

              {
                copyIOData( mxMemUnitPtr, simDataMemUnitPtr, &(mxMemUnitPtr), 1,
                           sizeof(uint8_T));
              }
            }

            /* provide the time information to the code instrumentation service */
            {
              void * pCodeInstrService = (void *) ssGetPWorkValue(S, 8);
              time_T simTime = ssGetT(S);
              codeInstrServiceSetTime(pCodeInstrService, simTime);
            }

            /* dispatch command to the target */
            if (commandDispatch(S, IOBufferPtr, 50)!=XILSERVICE_SUCCESS) {
              return;
            }                          /* if */

            {
              XILCommandResponseType commandResponseType =
                XIL_COMMAND_NOT_COMPLETE;
              while (commandResponseType != XIL_STEP_COMPLETE) {
                /* receive command from the target */
                mwSize dataInSize = 0;
                if (commandResponse(S, &dataInSize, &commandResponseType) !=
                    XILSERVICE_SUCCESS) {
                  return;
                }                      /* if */

                if (dataInSize > 0) {
                  size_t dataInMemUnitSize = dataInSize;
                  uint8_T responseId = 0;
                  uint8_T * mxMemUnitPtrEnd;
                  mxMemUnitPtr = (uint8_T *) IOBufferPtr->data;
                  mxMemUnitPtrEnd = mxMemUnitPtr + dataInMemUnitSize - 1;
                  while (mxMemUnitPtr <= mxMemUnitPtrEnd) {
                    /* read response id */
                    responseId = *mxMemUnitPtr;
                    mxMemUnitPtr++;
                    switch (responseId) {
                     case RESPONSE_ERROR:
                     case RESPONSE_PRINTF:
                     case RESPONSE_FOPEN:
                     case RESPONSE_FPRINTF:
                      {
                        if (processErrorAndTargetIOResponseCases(S, responseId,
                             &mxMemUnitPtr, 0)== XILSERVICE_ERROR) {
                          return;
                        }              /* if */
                        break;
                      }

                     default:
                      {
                        {
                          mxArray * prhs[ 2 ];
                          prhs[0] = mxCreateString(
                            "PIL:pilverification:UnknownResponseId");
                          prhs[1] = mxCreateDoubleScalar(responseId);
                          callMATLAB(S, 0, NULL, 2, prhs, "DAStudio.error", 0);
                          return;
                        }
                        break;
                      }
                    }                  /* switch */
                  }                    /* while */
                }                      /* if */
              }                        /* while */
            }
          }                            /* if */
        }                              /* if */
      }                                /* if */
    }
  }                                    /* if */
}

/* returns data needed by code instrumentation service */
static CodeInstrServiceData_T* codeInstrServiceData(SimStruct *S, uint8_T
  memUnitSizeBytes)
{
  CodeInstrServiceData_T* pCodeInstrServiceData = (CodeInstrServiceData_T*)
    mxCalloc(1, sizeof(CodeInstrServiceData_T));
  const char * simulinkBlockPath = ssGetPath(S);
  if (pCodeInstrServiceData == NULL) {
    ssSetErrorStatus( S,
                     "Error in allocating memory for code instrumentation data through mxCalloc.");
    return NULL;
  }                                    /* if */

  pCodeInstrServiceData->infoPath = "./InputProcessing_ert_rtw/pil";
  pCodeInstrServiceData->blockPath = simulinkBlockPath;
  pCodeInstrServiceData->rootModel = ssGetPath(ssGetRootSS(S));
  pCodeInstrServiceData->memUnitSize = memUnitSizeBytes;
  pCodeInstrServiceData->isProfilingEnabled = true;
  pCodeInstrServiceData->inTheLoopType = 2;
  pCodeInstrServiceData->silPilInterfaceFcn =
    "@coder.connectivity.SimulinkInterface.getSILPILInterface";
  return pCodeInstrServiceData;
}

static void callStopHookAndFreeSFcnMemory(SimStruct *S)
{
  closeAndFreeTargetIOFd(S);

  {
    {
      void * pXILUtils = (void *) ssGetPWorkValue(S, 5);
      if (pXILUtils) {
        mxArray *rhs[3];
        const char * simulinkBlockPath = ssGetPath(S);
        rhs[ 0 ] = mxCreateString(
          "@coder.connectivity.SimulinkInterface.getSILPILInterface");
        rhs[ 1 ] = mxCreateDoubleScalar( 2 );
        rhs[ 2 ] = mxCreateString(simulinkBlockPath);
        if (xilUtilsCallMATLAB(pXILUtils, 0, NULL, 3, rhs,
                               "rtw.pil.SILPILInterface.sfunctionPILStopHook")!=
            XIL_UTILS_SUCCESS) {
        }                              /* if */
      }                                /* if */
    }
  }

  if (ssGetPWork(S) != NULL) {
    int * pCommErrorOccurred = (int *) ssGetPWorkValue(S, 4);
    if (pCommErrorOccurred != NULL) {
      mxFree(pCommErrorOccurred);
      ssSetPWorkValue(S, 4, NULL);
    }                                  /* if */
  }                                    /* if */

  if (ssGetPWork(S) != NULL) {
    XIL_IOBuffer_T* IOBufferPtr;
    XIL_RtIOStreamData_T * rtIOStreamDataPtr = (XIL_RtIOStreamData_T *)
      ssGetPWorkValue(S, 0);
    SIL_DEBUGGING_DATA_T * silDebuggingDataPtr = (SIL_DEBUGGING_DATA_T *)
      ssGetPWorkValue(S, 2);
    if (rtIOStreamDataPtr != NULL) {
      {
        int errorStatus = rtIOStreamUnloadLib(&rtIOStreamDataPtr->libH);
        if (errorStatus) {
          ssSetErrorStatus( S,"rtIOStreamUnloadLib failed.");
        }                              /* if */
      }

      mxFree(rtIOStreamDataPtr->lib);
      mxDestroyArray(rtIOStreamDataPtr->MATLABObject);
      mxFree(rtIOStreamDataPtr);
      ssSetPWorkValue(S, 0, NULL);
    }                                  /* if */

    if (silDebuggingDataPtr != NULL) {
      mxFree(silDebuggingDataPtr->componentBlockPath);
      mxFree(silDebuggingDataPtr->SILPILInterfaceFcnStr);
      mxFree(silDebuggingDataPtr);
      ssSetPWorkValue(S, 2, NULL);
    }                                  /* if */

    IOBufferPtr = (XIL_IOBuffer_T *) ssGetPWorkValue(S, 1);
    if (IOBufferPtr != NULL) {
      mxFree(IOBufferPtr->data);
      mxFree(IOBufferPtr);
      ssSetPWorkValue(S, 1, NULL);
    }                                  /* if */

    closeAndFreeTargetIOFd(S);
    if (ssGetPWork(S) != NULL) {
      void * pXILUtils = (void *) ssGetPWorkValue(S, 5);
      void * pComms = (void *) ssGetPWorkValue(S, 6);
      void * pXILService = (void *) ssGetPWorkValue(S, 7);
      void * pCodeInstrService = (void *) ssGetPWorkValue(S, 8);
      if (pCodeInstrService != NULL) {
        uint8_T memUnitSizeBytes = 1;
        CodeInstrServiceData_T* pCodeInstrServiceData = codeInstrServiceData(S,
          memUnitSizeBytes);
        codeInstrServiceDestroy(pCodeInstrService, pCodeInstrServiceData);
        mxFree(pCodeInstrServiceData);
      }                                /* if */

      ssSetPWorkValue(S, 8, NULL);
      if (pXILUtils != NULL) {
        xilUtilsDestroy(pXILUtils);
      }                                /* if */

      ssSetPWorkValue(S, 5, NULL);
      if (pComms != NULL) {
        xilCommsDestroy(pComms);
      }                                /* if */

      ssSetPWorkValue(S, 6, NULL);
      if (pXILService != NULL) {
        xilServiceDestroy(pXILService);
      }                                /* if */

      ssSetPWorkValue(S, 7, NULL);
    }                                  /* if */
  }                                    /* if */
}

/* This function checks the attributes of tunable parameters. */
#define MDL_CHECK_PARAMETERS
#if defined(MDL_CHECK_PARAMETERS) && defined(MATLAB_MEX_FILE)

static void mdlCheckParameters(SimStruct *S)
{
  {
    /* pcam */
    int_T dims[2];
    dims[0] = 1;
    dims[1] = 2;
    ssCheckSFcnParamValueAttribs(S, 0, "pcam", DYNAMICALLY_TYPED, 2, dims, 0);
  }

  {
    /* startPos */
    int_T dims[2];
    dims[0] = 1;
    dims[1] = 2;
    ssCheckSFcnParamValueAttribs(S, 1, "startPos", DYNAMICALLY_TYPED, 2, dims, 0);
  }

  {
    /* AxleLength */
    int_T dims[2];
    dims[0] = 1;
    dims[1] = 1;
    ssCheckSFcnParamValueAttribs(S, 2, "AxleLength", DYNAMICALLY_TYPED, 2, dims,
      0);
  }

  {
    /* EncRes */
    int_T dims[2];
    dims[0] = 1;
    dims[1] = 1;
    ssCheckSFcnParamValueAttribs(S, 3, "EncRes", DYNAMICALLY_TYPED, 2, dims, 0);
  }

  {
    /* WheelRadius */
    int_T dims[2];
    dims[0] = 1;
    dims[1] = 1;
    ssCheckSFcnParamValueAttribs(S, 4, "WheelRadius", DYNAMICALLY_TYPED, 2, dims,
      0);
  }

  {
    /* do_one_run */
    int_T dims[2];
    dims[0] = 1;
    dims[1] = 1;
    ssCheckSFcnParamValueAttribs(S, 5, "do_one_run", DYNAMICALLY_TYPED, 2, dims,
      0);
  }
}

#endif                                 /* MDL_CHECK_PARAMETERS */

static void mdlInitializeSizes(SimStruct *S)
{
  ssSetNumSFcnParams(S, 6);            /* Number of expected parameters */
  if (ssGetNumSFcnParams(S) == ssGetSFcnParamsCount(S)) {

#if defined(MDL_CHECK_PARAMETERS)

    mdlCheckParameters(S);

#endif

    if (ssGetErrorStatus(S) != (NULL))
      return;
  } else {
    /* Parameter mismatch will be reported by Simulink */
    return;
  }

  ssSetNumContStates(S, 0);
  ssSetNumDiscStates(S, 0);

  /* no support for SimState */
  ssSetSimStateCompliance(S, DISALLOW_SIM_STATE);

  /* Allow signal dimensions greater than 2 */
  ssAllowSignalsWithMoreThan2D(S);

  /* Allow fixed-point data types with 33 or more bits */
  ssFxpSetU32BitRegionCompliant(S,1);

  {
    mxArray * lhs[1];
    mxArray * error = NULL;
    char * installVersion;
    error = mexCallMATLABWithTrap(1, lhs, 0, NULL, "rtw.pil.getPILVersion");
    if (error != NULL) {
      mxDestroyArray(error);
      ssSetErrorStatus( S,
                       "Failed to determine the installed In-the-Loop version for comparison against the In-the-Loop s-function version (release 6.8 (R2015a)_12). To avoid this error, remove the In-the-Loop s-function from your MATLAB path (e.g. delete it or move to a clean working directory).");
      return;
    }                                  /* if */

    if (mxIsEmpty(lhs[0])) {
      ssSetErrorStatus( S,"rtw.pil.getPILVersion returned empty!");
      return;
    }                                  /* if */

    installVersion = mxArrayToString(lhs[0]);
    mxDestroyArray(lhs[0]);
    if (installVersion == NULL) {
      ssSetErrorStatus( S,"Failed to determine installed In-the-Loop version.");
      return;
    }                                  /* if */

    if (strcmp(installVersion, "6.8 (R2015a)_12") != 0) {
      ssSetErrorStatus( S,
                       "The In-the-Loop s-function is incompatible with the installed In-the-Loop version (see ver('ecoder')); it was generated for release 6.8 (R2015a)_12. To avoid this error, remove the In-the-Loop s-function from your MATLAB path (e.g. delete it or move to a clean working directory)");
      return;
    }                                  /* if */

    mxFree(installVersion);
  }

  ssSetRTWGeneratedSFcn(S, 4);
  if (!ssSetNumInputPorts(S, 6))
    return;

  /* Input Port 0 */
  /* contiguous inport */
  ssSetInputPortRequiredContiguous(S, 0, 1);

  /* directfeedthrough */
  ssSetInputPortDirectFeedThrough(S, 0, 1);
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 1;
    ssSetInputPortDataType(S, 0, dataTypeId);
  }

  /* dimensions */
  {
    DECL_AND_INIT_DIMSINFO(di);
    int_T dims[ 2 ] = { 8, 2 };

    di.numDims = 2;
    di.dims = dims;
    di.width = 16;
    ssSetInputPortDimensionInfo(S, 0, &di);
  }

  ssSetInputPortDimensionsMode(S, 0, FIXED_DIMS_MODE);

  /* complexity */
  ssSetInputPortComplexSignal(S, 0, COMPLEX_NO);

  /* using port based sample times */
  ssSetInputPortSampleTime(S, 0, 0.1);
  ssSetInputPortOffsetTime(S, 0, 0);

  /* sampling mode */
  ssSetInputPortFrameData(S, 0, FRAME_NO);

  /* Input Port 1 */
  /* contiguous inport */
  ssSetInputPortRequiredContiguous(S, 1, 1);

  /* directfeedthrough */
  ssSetInputPortDirectFeedThrough(S, 1, 1);
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 6;
    ssSetInputPortDataType(S, 1, dataTypeId);
  }

  /* dimensions */
  {
    DECL_AND_INIT_DIMSINFO(di);
    int_T dims[ 1 ] = { 1 };

    di.numDims = 1;
    di.dims = dims;
    di.width = 1;
    ssSetInputPortDimensionInfo(S, 1, &di);
  }

  ssSetInputPortDimensionsMode(S, 1, FIXED_DIMS_MODE);

  /* complexity */
  ssSetInputPortComplexSignal(S, 1, COMPLEX_NO);

  /* using port based sample times */
  ssSetInputPortSampleTime(S, 1, 0.1);
  ssSetInputPortOffsetTime(S, 1, 0);

  /* sampling mode */
  ssSetInputPortFrameData(S, 1, FRAME_NO);

  /* Input Port 2 */
  /* contiguous inport */
  ssSetInputPortRequiredContiguous(S, 2, 1);

  /* directfeedthrough */
  ssSetInputPortDirectFeedThrough(S, 2, 1);
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 6;
    ssSetInputPortDataType(S, 2, dataTypeId);
  }

  /* dimensions */
  {
    DECL_AND_INIT_DIMSINFO(di);
    int_T dims[ 1 ] = { 1 };

    di.numDims = 1;
    di.dims = dims;
    di.width = 1;
    ssSetInputPortDimensionInfo(S, 2, &di);
  }

  ssSetInputPortDimensionsMode(S, 2, FIXED_DIMS_MODE);

  /* complexity */
  ssSetInputPortComplexSignal(S, 2, COMPLEX_NO);

  /* using port based sample times */
  ssSetInputPortSampleTime(S, 2, 0.1);
  ssSetInputPortOffsetTime(S, 2, 0);

  /* sampling mode */
  ssSetInputPortFrameData(S, 2, FRAME_NO);

  /* Input Port 3 */
  /* contiguous inport */
  ssSetInputPortRequiredContiguous(S, 3, 1);

  /* directfeedthrough */
  ssSetInputPortDirectFeedThrough(S, 3, 1);
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 4;
    ssSetInputPortDataType(S, 3, dataTypeId);
  }

  /* dimensions */
  {
    DECL_AND_INIT_DIMSINFO(di);
    int_T dims[ 1 ] = { 6 };

    di.numDims = 1;
    di.dims = dims;
    di.width = 6;
    ssSetInputPortDimensionInfo(S, 3, &di);
  }

  ssSetInputPortDimensionsMode(S, 3, FIXED_DIMS_MODE);

  /* complexity */
  ssSetInputPortComplexSignal(S, 3, COMPLEX_NO);

  /* using port based sample times */
  ssSetInputPortSampleTime(S, 3, 0.1);
  ssSetInputPortOffsetTime(S, 3, 0);

  /* sampling mode */
  ssSetInputPortFrameData(S, 3, FRAME_NO);

  /* Input Port 4 */
  /* contiguous inport */
  ssSetInputPortRequiredContiguous(S, 4, 1);

  /* directfeedthrough */
  ssSetInputPortDirectFeedThrough(S, 4, 1);
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 2;
    ssSetInputPortDataType(S, 4, dataTypeId);
  }

  /* dimensions */
  {
    DECL_AND_INIT_DIMSINFO(di);
    int_T dims[ 1 ] = { 6 };

    di.numDims = 1;
    di.dims = dims;
    di.width = 6;
    ssSetInputPortDimensionInfo(S, 4, &di);
  }

  ssSetInputPortDimensionsMode(S, 4, FIXED_DIMS_MODE);

  /* complexity */
  ssSetInputPortComplexSignal(S, 4, COMPLEX_NO);

  /* using port based sample times */
  ssSetInputPortSampleTime(S, 4, 0.1);
  ssSetInputPortOffsetTime(S, 4, 0);

  /* sampling mode */
  ssSetInputPortFrameData(S, 4, FRAME_NO);

  /* Input Port 5 */
  /* contiguous inport */
  ssSetInputPortRequiredContiguous(S, 5, 1);

  /* directfeedthrough */
  ssSetInputPortDirectFeedThrough(S, 5, 1);
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 8;
    ssSetInputPortDataType(S, 5, dataTypeId);
  }

  /* dimensions */
  {
    DECL_AND_INIT_DIMSINFO(di);
    int_T dims[ 1 ] = { 1 };

    di.numDims = 1;
    di.dims = dims;
    di.width = 1;
    ssSetInputPortDimensionInfo(S, 5, &di);
  }

  ssSetInputPortDimensionsMode(S, 5, FIXED_DIMS_MODE);

  /* complexity */
  ssSetInputPortComplexSignal(S, 5, COMPLEX_NO);

  /* using port based sample times */
  ssSetInputPortSampleTime(S, 5, 0.1);
  ssSetInputPortOffsetTime(S, 5, 0);

  /* sampling mode */
  ssSetInputPortFrameData(S, 5, FRAME_NO);
  if (!ssSetNumOutputPorts(S, 5))
    return;

  /* Output Port 0 */
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 1;
    ssSetOutputPortDataType(S, 0, dataTypeId);
  }

  /* dimensions */
  {
    DECL_AND_INIT_DIMSINFO(di);
    int_T dims[ 1 ] = { 1 };

    di.numDims = 1;
    di.dims = dims;
    di.width = 1;
    ssSetOutputPortDimensionInfo(S, 0, &di);
  }

  ssSetOutputPortDimensionsMode(S, 0, FIXED_DIMS_MODE);

  /* complexity */
  ssSetOutputPortComplexSignal(S, 0, COMPLEX_NO);

  /* using port based sample times */
  ssSetOutputPortSampleTime(S, 0, 0.1);
  ssSetOutputPortOffsetTime(S, 0, 0);

  /* sampling mode */
  ssSetOutputPortFrameData(S, 0, FRAME_NO);

  /* Output Port 1 */
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 1;
    ssSetOutputPortDataType(S, 1, dataTypeId);
  }

  /* dimensions */
  {
    DECL_AND_INIT_DIMSINFO(di);
    int_T dims[ 1 ] = { 1 };

    di.numDims = 1;
    di.dims = dims;
    di.width = 1;
    ssSetOutputPortDimensionInfo(S, 1, &di);
  }

  ssSetOutputPortDimensionsMode(S, 1, FIXED_DIMS_MODE);

  /* complexity */
  ssSetOutputPortComplexSignal(S, 1, COMPLEX_NO);

  /* using port based sample times */
  ssSetOutputPortSampleTime(S, 1, 0.1);
  ssSetOutputPortOffsetTime(S, 1, 0);

  /* sampling mode */
  ssSetOutputPortFrameData(S, 1, FRAME_NO);

  /* Output Port 2 */
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 8;
    ssSetOutputPortDataType(S, 2, dataTypeId);
  }

  /* dimensions */
  {
    DECL_AND_INIT_DIMSINFO(di);
    int_T dims[ 1 ] = { 1 };

    di.numDims = 1;
    di.dims = dims;
    di.width = 1;
    ssSetOutputPortDimensionInfo(S, 2, &di);
  }

  ssSetOutputPortDimensionsMode(S, 2, FIXED_DIMS_MODE);

  /* complexity */
  ssSetOutputPortComplexSignal(S, 2, COMPLEX_NO);

  /* using port based sample times */
  ssSetOutputPortSampleTime(S, 2, 0.1);
  ssSetOutputPortOffsetTime(S, 2, 0);

  /* sampling mode */
  ssSetOutputPortFrameData(S, 2, FRAME_NO);

  /* Output Port 3 */
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 8;
    ssSetOutputPortDataType(S, 3, dataTypeId);
  }

  /* dimensions */
  {
    DECL_AND_INIT_DIMSINFO(di);
    int_T dims[ 1 ] = { 1 };

    di.numDims = 1;
    di.dims = dims;
    di.width = 1;
    ssSetOutputPortDimensionInfo(S, 3, &di);
  }

  ssSetOutputPortDimensionsMode(S, 3, FIXED_DIMS_MODE);

  /* complexity */
  ssSetOutputPortComplexSignal(S, 3, COMPLEX_NO);

  /* using port based sample times */
  ssSetOutputPortSampleTime(S, 3, 0.1);
  ssSetOutputPortOffsetTime(S, 3, 0);

  /* sampling mode */
  ssSetOutputPortFrameData(S, 3, FRAME_NO);

  /* Output Port 4 */
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 8;
    ssSetOutputPortDataType(S, 4, dataTypeId);
  }

  /* dimensions */
  {
    DECL_AND_INIT_DIMSINFO(di);
    int_T dims[ 1 ] = { 1 };

    di.numDims = 1;
    di.dims = dims;
    di.width = 1;
    ssSetOutputPortDimensionInfo(S, 4, &di);
  }

  ssSetOutputPortDimensionsMode(S, 4, FIXED_DIMS_MODE);

  /* complexity */
  ssSetOutputPortComplexSignal(S, 4, COMPLEX_NO);

  /* using port based sample times */
  ssSetOutputPortSampleTime(S, 4, 0.1);
  ssSetOutputPortOffsetTime(S, 4, 0);

  /* sampling mode */
  ssSetOutputPortFrameData(S, 4, FRAME_NO);

  /* using port based sample times */
  ssSetNumSampleTimes(S, PORT_BASED_SAMPLE_TIMES);

  /* this s-function is sample time dependent: do not allow sub-models containing it to inherit sample times */
  ssSetModelReferenceSampleTimeInheritanceRule(S,
    DISALLOW_SAMPLE_TIME_INHERITANCE);
  ssSetNumPWork(S, 9);
  ssSetNumRWork(S, 0);
  ssSetNumIWork(S, 0);
  ssSetNumModes(S, 0);
  ssSetNumNonsampledZCs(S, 0);

  {
    uint_T options = 0;

    /* do not allow (including inheritance of) constant block-based sample times*/
    options |= SS_OPTION_DISALLOW_CONSTANT_SAMPLE_TIME;
    options |= SS_OPTION_SUPPORTS_ALIAS_DATA_TYPES;
    options |= SS_OPTION_CALL_TERMINATE_ON_EXIT;
    ssSetOptions(S, options);
  }

  ssSetModelReferenceNormalModeSupport(S, MDL_START_AND_MDL_PROCESS_PARAMS_OK);
}

#define MDL_SET_INPUT_PORT_SAMPLE_TIME                           /* Change to #undef to remove function */
#if defined(MDL_SET_INPUT_PORT_SAMPLE_TIME) && defined(MATLAB_MEX_FILE)

static void mdlSetInputPortSampleTime(SimStruct *S, int_T portIdx, real_T
  sampleTime, real_T offsetTime)
{
  /* sample times are fully specified */
}

#endif                                 /* MDL_SET_INPUT_PORT_SAMPLE_TIME */

#define MDL_SET_OUTPUT_PORT_SAMPLE_TIME                          /* Change to #undef to remove function */
#if defined(MDL_SET_OUTPUT_PORT_SAMPLE_TIME) && defined(MATLAB_MEX_FILE)

static void mdlSetOutputPortSampleTime(SimStruct *S, int_T portIdx, real_T
  sampleTime, real_T offsetTime)
{
  /* sample times are fully specified */
}

#endif                                 /* MDL_SET_OUTPUT_PORT_SAMPLE_TIME */

static void mdlInitializeSampleTimes(SimStruct *S)
{
  /* using port based sample times */
}

#define MDL_START                                                /* Change to #undef to remove function */
#if defined(MDL_START)

static void mdlStart(SimStruct *S)
{
  /* no solver check required for singlerate (singletasking) scheduling */
  /* check Sim Mode is Normal or (top-model) Accel */
  if ((ssGetSimMode(S) != SS_SIMMODE_NORMAL) && !ssRTWGenIsAccelerator(S)) {
    {
      mxArray * prhs[ 1 ];
      prhs[0] = mxCreateString("PIL:pil:XILBlockCodeGenError");
      callMATLAB(S, 0, NULL, 1, prhs, "DAStudio.error", 0);
      return;
    }
  }

  /* Check current start time is consistent with the generated code */
  if (ssGetTStart(S) != 0.0) {
    {
      mxArray * prhs[ 2 ];
      prhs[0] = mxCreateString("PIL:pil:XILBlockStartTimeError");
      prhs[1] = mxCreateString("0.0");
      callMATLAB(S, 0, NULL, 2, prhs, "DAStudio.error", 0);
      return;
    }
  }                                    /* if */

  {
    mxArray *rhs[4];
    mxArray *lhs[1];
    char * rootLoggingPath;
    const char * simulinkBlockPath = ssGetPath(S);
    rhs[ 0 ] = mxCreateString(
      "@coder.connectivity.SimulinkInterface.getSILPILInterface");
    rhs[ 1 ] = mxCreateDoubleScalar( 2 );
    rhs[ 2 ] = mxCreateString(simulinkBlockPath);
    rhs[3] = mxCreateString(ssGetPath(ssGetRootSS(S)));
    callMATLAB(S, 1, lhs, 4 , rhs,
               "rtw.pil.SILPILInterface.sfunctionInitializeHook", 0);
    rootLoggingPath = mxArrayToString(lhs[0]);
    mxDestroyArray(lhs[0]);

    {
      int * pCommErrorOccurred = (int *) mxCalloc(1, sizeof(int));
      if (pCommErrorOccurred == NULL) {
        ssSetErrorStatus( S,
                         "Error in allocating memory for pCommErrorOccurred through mxCalloc.");
        return;
      }                                /* if */

      *pCommErrorOccurred = 0;
      mexMakeMemoryPersistent(pCommErrorOccurred);
      ssSetPWorkValue(S, 4, pCommErrorOccurred);
    }

    mxFree(rootLoggingPath);
  }

  {
    {
      mxArray *rhs[4];
      const char * simulinkBlockPath = ssGetPath(S);
      rhs[ 0 ] = mxCreateString(
        "@coder.connectivity.SimulinkInterface.getSILPILInterface");
      rhs[ 1 ] = mxCreateDoubleScalar( 2 );
      rhs[ 2 ] = mxCreateString(simulinkBlockPath);
      rhs[3] = mxCreateString("uint8");
      callMATLAB(S, 0, NULL, 4, rhs,
                 "rtw.pil.SILPILInterface.sfunctionPILStartHook", 0);
    }
  }

  {
    mxArray *rhs[3];
    mxArray *lhs[5];
    const char * simulinkBlockPath = ssGetPath(S);
    rhs[ 0 ] = mxCreateString(
      "@coder.connectivity.SimulinkInterface.getSILPILInterface");
    rhs[ 1 ] = mxCreateDoubleScalar( 2 );
    rhs[ 2 ] = mxCreateString(simulinkBlockPath);
    callMATLAB(S, 5, lhs, 3, rhs,
               "rtw.pil.SILPILInterface.sfunctionGetRtIOStreamInfoHook", 0);

    {
      XIL_RtIOStreamData_T* rtIOStreamDataPtr = (XIL_RtIOStreamData_T*) mxCalloc
        (1, sizeof(XIL_RtIOStreamData_T));
      if (rtIOStreamDataPtr == NULL) {
        ssSetErrorStatus( S,"Error in allocating memory through mxCalloc.");
        return;
      }                                /* if */

      rtIOStreamDataPtr->lib = mxArrayToString(lhs[0]);
      rtIOStreamDataPtr->MATLABObject = mxDuplicateArray(lhs[1]);
      mexMakeMemoryPersistent(rtIOStreamDataPtr);
      mexMakeMemoryPersistent(rtIOStreamDataPtr->lib);
      mexMakeArrayPersistent(rtIOStreamDataPtr->MATLABObject);
      rtIOStreamDataPtr->streamID = *mxGetPr(lhs[2]);
      rtIOStreamDataPtr->recvTimeout = *mxGetPr(lhs[3]);
      rtIOStreamDataPtr->sendTimeout = *mxGetPr(lhs[4]);
      rtIOStreamDataPtr->isRtIOStreamCCall = 1;
      rtIOStreamDataPtr->ioMxClassID = mxUINT8_CLASS;
      rtIOStreamDataPtr->ioDataSize = sizeof(uint8_T);
      rtIOStreamDataPtr->targetRecvBufferSizeBytes = 128;
      rtIOStreamDataPtr->targetSendBufferSizeBytes = 128;

      {
        int errorStatus = rtIOStreamLoadLib(&rtIOStreamDataPtr->libH,
          rtIOStreamDataPtr->lib);
        if (errorStatus) {
          ssSetErrorStatus( S,"rtIOStreamLoadLib failed.");
          return;
        }                              /* if */
      }

      ssSetPWorkValue(S, 0, rtIOStreamDataPtr);
    }

    {
      int i;
      for (i=0; i<5; i++) {
        mxDestroyArray(lhs[i]);
      }                                /* for */
    }
  }

  {
    XIL_IOBuffer_T* IOBufferPtr = (XIL_IOBuffer_T *) mxCalloc(1, sizeof
      (XIL_IOBuffer_T));
    if (IOBufferPtr == NULL) {
      ssSetErrorStatus( S,"Error in allocating memory through mxCalloc.");
      return;
    }                                  /* if */

    mexMakeMemoryPersistent(IOBufferPtr);
    ssSetPWorkValue(S, 1, IOBufferPtr);
  }

  {
    SIL_DEBUGGING_DATA_T* silDebuggingDataPtr = (SIL_DEBUGGING_DATA_T*) mxCalloc
      (1, sizeof(SIL_DEBUGGING_DATA_T));
    const char * simulinkBlockPath = ssGetPath(S);
    if (silDebuggingDataPtr == NULL) {
      ssSetErrorStatus( S,
                       "Error in allocating memory through mxCalloc for SIL_DEBUGGING_DATA_T.");
      return;
    }                                  /* if */

    silDebuggingDataPtr->componentBlockPath = strcpy((char *) mxCalloc(strlen
      (simulinkBlockPath)+1, sizeof(char)), simulinkBlockPath);
    silDebuggingDataPtr->SILPILInterfaceFcnStr = strcpy((char*) mxCalloc(57,
      sizeof(char)), "@coder.connectivity.SimulinkInterface.getSILPILInterface");
    silDebuggingDataPtr->inTheLoopType = 2;
    mexMakeMemoryPersistent(silDebuggingDataPtr);
    mexMakeMemoryPersistent(silDebuggingDataPtr->componentBlockPath);
    mexMakeMemoryPersistent(silDebuggingDataPtr->SILPILInterfaceFcnStr);
    ssSetPWorkValue(S, 2, silDebuggingDataPtr);
  }

  {
    targetIOFd_T * targetIOFdPtr = (targetIOFd_T *) mxCalloc(1, sizeof
      (targetIOFd_T));
    if (targetIOFdPtr == NULL) {
      return;
    }                                  /* if */

    mexMakeMemoryPersistent(targetIOFdPtr);
    targetIOFdPtr->size = 0;
    targetIOFdPtr->Fd = NULL;
    targetIOFdPtr->fidOffset = -1;
    ssSetPWorkValue(S, 3, targetIOFdPtr);
  }

  {
    int retValXILUtils;
    void* pComms = NULL;
    void* pXILService = NULL;
    void* pXILUtils = NULL;
    void* pMemUnitTransformer = NULL;
    uint8_T memUnitSizeBytes = 1;
    uint8_T ioDataTypeSizeBytes = sizeof(uint8_T);
    XIL_RtIOStreamData_T * rtIOStreamDataPtr = (XIL_RtIOStreamData_T *)
      ssGetPWorkValue(S, 0);
    SIL_DEBUGGING_DATA_T * silDebuggingDataPtr = (SIL_DEBUGGING_DATA_T *)
      ssGetPWorkValue(S, 2);
    XIL_IOBuffer_T * IOBufferPtr = (XIL_IOBuffer_T *) ssGetPWorkValue(S, 1);
    void* pCodeInstrService = NULL;
    CodeInstrServiceData_T* pCodeInstrServiceData = codeInstrServiceData(S,
      memUnitSizeBytes);
    retValXILUtils = xilSimulinkUtilsCreate(&pXILUtils, S);
    if (retValXILUtils!=XIL_UTILS_SUCCESS) {
      ssSetErrorStatus( S,"Error instantiating XIL Utils!");
      return;
    }                                  /* if */

    if (xilCommsCreate(&pComms, rtIOStreamDataPtr, silDebuggingDataPtr,
                       memUnitSizeBytes, pMemUnitTransformer, pXILUtils) !=
        XILCOMMS_RTIOSTREAM_SUCCESS) {
      return;
    }                                  /* if */

    if (xilServiceCreate(&pXILService, pComms, pXILUtils, IOBufferPtr,
                         memUnitSizeBytes, ioDataTypeSizeBytes, 0) !=
        XILSERVICE_SUCCESS) {
      return;
    }                                  /* if */

    if (codeInstrServiceCreate(&pCodeInstrService, pCodeInstrServiceData, pComms,
         pMemUnitTransformer, 32, pXILUtils, memUnitSizeBytes, 0) !=
        CODEINSTR_SERVICE_SUCCESS) {
      mxFree(pCodeInstrServiceData);
      return;
    }                                  /* if */

    mxFree(pCodeInstrServiceData);
    xilCommsRegisterApplication(pComms, pXILService);
    xilCommsRegisterApplication(pComms, pCodeInstrService);
    ssSetPWorkValue(S, 7, pXILService);
    ssSetPWorkValue(S, 6, pComms);
    ssSetPWorkValue(S, 5, pXILUtils);
    ssSetPWorkValue(S, 8, pCodeInstrService);
  }

  {
    uint8_T * mxMemUnitPtr;
    mwSize dataInSize = 0;
    XIL_IOBuffer_T * IOBufferPtr = (XIL_IOBuffer_T *) ssGetPWorkValue(S, 1);
    if (IOBufferPtr != NULL) {
      void * pXILService = (void *) ssGetPWorkValue(S, 7);
      if (pXILService != NULL) {
        if (xilServiceGrowIOBuffer(pXILService, IOBufferPtr, 5, 0)!=
            XILSERVICE_SUCCESS) {
          return;
        }                              /* if */

        if (IOBufferPtr->data != NULL) {
          mxMemUnitPtr = (uint8_T *) IOBufferPtr->data;

          /* write command id */
          *mxMemUnitPtr = 0;
          mxMemUnitPtr++;

          {
            uint8_T * simDataMemUnitPtr;
            uint32_T commandDataFcnid = 0;
            simDataMemUnitPtr = (uint8_T *) &commandDataFcnid;

            {
              copyIOData( mxMemUnitPtr, simDataMemUnitPtr, &(mxMemUnitPtr), 1,
                         sizeof(uint32_T));
            }
          }

          /* provide the time information to the code instrumentation service */
          {
            void * pCodeInstrService = (void *) ssGetPWorkValue(S, 8);
            time_T simTime = ssGetT(S);
            codeInstrServiceSetTime(pCodeInstrService, simTime);
          }

          /* dispatch command to the target */
          if (commandDispatch(S, IOBufferPtr, 5)!=XILSERVICE_SUCCESS) {
            return;
          }                            /* if */

          {
            XILCommandResponseType commandResponseType =
              XIL_COMMAND_NOT_COMPLETE;
            while (commandResponseType != XIL_STEP_COMPLETE) {
              /* receive command from the target */
              mwSize dataInSize = 0;
              if (commandResponse(S, &dataInSize, &commandResponseType) !=
                  XILSERVICE_SUCCESS) {
                return;
              }                        /* if */

              if (dataInSize > 0) {
                size_t dataInMemUnitSize = dataInSize;
                uint8_T responseId = 0;
                uint8_T * mxMemUnitPtrEnd;

#define RESPONSE_TYPE_SIZE             5

                mxMemUnitPtr = (uint8_T *) IOBufferPtr->data;
                mxMemUnitPtrEnd = mxMemUnitPtr + dataInMemUnitSize - 1;
                while (mxMemUnitPtr <= mxMemUnitPtrEnd) {
                  /* read response id */
                  responseId = *mxMemUnitPtr;
                  mxMemUnitPtr++;
                  switch (responseId) {
                   case RESPONSE_ERROR:
                   case RESPONSE_PRINTF:
                   case RESPONSE_FOPEN:
                   case RESPONSE_FPRINTF:
                    {
                      if (processErrorAndTargetIOResponseCases(S, responseId,
                           &mxMemUnitPtr, 0)== XILSERVICE_ERROR) {
                        return;
                      }                /* if */
                      break;
                    }

                   case RESPONSE_TYPE_SIZE:
                    {
                      uint8_T typeId = *mxMemUnitPtr;
                      uint8_T typeBytes;
                      mxMemUnitPtr++;
                      typeBytes = *mxMemUnitPtr;
                      mxMemUnitPtr++;
                      switch (typeId) {
                       case SS_SINGLE:
                        {
                          if (typeBytes != 4) {
                            {
                              mxArray * prhs[ 3 ];
                              prhs[0] = mxCreateString(
                                "PIL:pilverification:SingleUnsupported");
                              prhs[1] = mxCreateDoubleScalar(4);
                              prhs[2] = mxCreateDoubleScalar(typeBytes);
                              callMATLAB(S, 0, NULL, 3, prhs, "DAStudio.error",
                                         0);
                              return;
                            }
                          }            /* if */
                          break;
                        }

                       case SS_DOUBLE:
                        {
                          if (typeBytes != 8) {
                            {
                              mxArray * prhs[ 3 ];
                              prhs[0] = mxCreateString(
                                "PIL:pilverification:DoubleUnsupported");
                              prhs[1] = mxCreateDoubleScalar(8);
                              prhs[2] = mxCreateDoubleScalar(typeBytes);
                              callMATLAB(S, 0, NULL, 3, prhs, "DAStudio.error",
                                         0);
                              return;
                            }
                          }            /* if */
                          break;
                        }

                       default:
                        {
                          {
                            mxArray * prhs[ 2 ];
                            prhs[0] = mxCreateString(
                              "PIL:pilverification:UnknownTypeId");
                            prhs[1] = mxCreateDoubleScalar(typeId);
                            callMATLAB(S, 0, NULL, 2, prhs, "DAStudio.error", 0);
                            return;
                          }
                          break;
                        }
                      }                /* switch */
                      break;
                    }

                   default:
                    {
                      {
                        mxArray * prhs[ 2 ];
                        prhs[0] = mxCreateString(
                          "PIL:pilverification:UnknownResponseId");
                        prhs[1] = mxCreateDoubleScalar(responseId);
                        callMATLAB(S, 0, NULL, 2, prhs, "DAStudio.error", 0);
                        return;
                      }
                      break;
                    }
                  }                    /* switch */
                }                      /* while */
              }                        /* if */
            }                          /* while */
          }
        }                              /* if */
      }                                /* if */
    }                                  /* if */
  }

  /* initialize parameters */
  processParams(S, true);

  {
    uint8_T * mxMemUnitPtr;
    mwSize dataInSize = 0;
    XIL_IOBuffer_T * IOBufferPtr = (XIL_IOBuffer_T *) ssGetPWorkValue(S, 1);
    if (IOBufferPtr != NULL) {
      void * pXILService = (void *) ssGetPWorkValue(S, 7);
      if (pXILService != NULL) {
        if (xilServiceGrowIOBuffer(pXILService, IOBufferPtr, 5, 0)!=
            XILSERVICE_SUCCESS) {
          return;
        }                              /* if */

        if (IOBufferPtr->data != NULL) {
          mxMemUnitPtr = (uint8_T *) IOBufferPtr->data;

          /* write command id */
          *mxMemUnitPtr = 1;
          mxMemUnitPtr++;

          {
            uint8_T * simDataMemUnitPtr;
            uint32_T commandDataFcnid = 0;
            simDataMemUnitPtr = (uint8_T *) &commandDataFcnid;

            {
              copyIOData( mxMemUnitPtr, simDataMemUnitPtr, &(mxMemUnitPtr), 1,
                         sizeof(uint32_T));
            }
          }

          /* provide the time information to the code instrumentation service */
          {
            void * pCodeInstrService = (void *) ssGetPWorkValue(S, 8);
            time_T simTime = ssGetT(S);
            codeInstrServiceSetTime(pCodeInstrService, simTime);
          }

          /* dispatch command to the target */
          if (commandDispatch(S, IOBufferPtr, 5)!=XILSERVICE_SUCCESS) {
            return;
          }                            /* if */

          {
            XILCommandResponseType commandResponseType =
              XIL_COMMAND_NOT_COMPLETE;
            while (commandResponseType != XIL_STEP_COMPLETE) {
              /* receive command from the target */
              mwSize dataInSize = 0;
              if (commandResponse(S, &dataInSize, &commandResponseType) !=
                  XILSERVICE_SUCCESS) {
                return;
              }                        /* if */

              if (dataInSize > 0) {
                size_t dataInMemUnitSize = dataInSize;
                uint8_T responseId = 0;
                uint8_T * mxMemUnitPtrEnd;
                mxMemUnitPtr = (uint8_T *) IOBufferPtr->data;
                mxMemUnitPtrEnd = mxMemUnitPtr + dataInMemUnitSize - 1;
                while (mxMemUnitPtr <= mxMemUnitPtrEnd) {
                  /* read response id */
                  responseId = *mxMemUnitPtr;
                  mxMemUnitPtr++;
                  switch (responseId) {
                   case RESPONSE_ERROR:
                   case RESPONSE_PRINTF:
                   case RESPONSE_FOPEN:
                   case RESPONSE_FPRINTF:
                    {
                      if (processErrorAndTargetIOResponseCases(S, responseId,
                           &mxMemUnitPtr, 0)== XILSERVICE_ERROR) {
                        return;
                      }                /* if */
                      break;
                    }

                   case RESPONSE_OUTPUT_DATA:
                    {
                      {
                        uint8_T * simDataMemUnitPtr;
                        simDataMemUnitPtr = ( uint8_T *) ssGetOutputPortSignal(S,
                          0);

                        {
                          copyIOData( simDataMemUnitPtr, mxMemUnitPtr,
                                     &(mxMemUnitPtr), 1, sizeof(real32_T));
                        }
                      }

                      {
                        uint8_T * simDataMemUnitPtr;
                        simDataMemUnitPtr = ( uint8_T *) ssGetOutputPortSignal(S,
                          1);

                        {
                          copyIOData( simDataMemUnitPtr, mxMemUnitPtr,
                                     &(mxMemUnitPtr), 1, sizeof(real32_T));
                        }
                      }

                      {
                        uint8_T * simDataMemUnitPtr;
                        simDataMemUnitPtr = ( uint8_T *) ssGetOutputPortSignal(S,
                          2);

                        {
                          copyIOData( simDataMemUnitPtr, mxMemUnitPtr,
                                     &(mxMemUnitPtr), 1, sizeof(uint8_T));
                        }
                      }

                      {
                        uint8_T * simDataMemUnitPtr;
                        simDataMemUnitPtr = ( uint8_T *) ssGetOutputPortSignal(S,
                          3);

                        {
                          copyIOData( simDataMemUnitPtr, mxMemUnitPtr,
                                     &(mxMemUnitPtr), 1, sizeof(uint8_T));
                        }
                      }

                      {
                        uint8_T * simDataMemUnitPtr;
                        simDataMemUnitPtr = ( uint8_T *) ssGetOutputPortSignal(S,
                          4);

                        {
                          copyIOData( simDataMemUnitPtr, mxMemUnitPtr,
                                     &(mxMemUnitPtr), 1, sizeof(uint8_T));
                        }
                      }
                      break;
                    }

                   default:
                    {
                      {
                        mxArray * prhs[ 2 ];
                        prhs[0] = mxCreateString(
                          "PIL:pilverification:UnknownResponseId");
                        prhs[1] = mxCreateDoubleScalar(responseId);
                        callMATLAB(S, 0, NULL, 2, prhs, "DAStudio.error", 0);
                        return;
                      }
                      break;
                    }
                  }                    /* switch */
                }                      /* while */
              }                        /* if */
            }                          /* while */
          }
        }                              /* if */
      }                                /* if */
    }                                  /* if */
  }
}

#endif                                 /* MDL_START */

#define MDL_PROCESS_PARAMETERS
#if defined(MDL_PROCESS_PARAMETERS)

static void mdlProcessParameters(SimStruct *S)
{
  processParams(S, false);
}

#endif                                 /* MDL_PROCESS_PARAMETERS */

#define MDL_INITIALIZE_CONDITIONS                                /* Change to #undef to remove function */
#if defined(MDL_INITIALIZE_CONDITIONS)

static void mdlInitializeConditions(SimStruct *S)
{
  if (!ssIsFirstInitCond(S)) {
    ssSetErrorStatus(S,
                     "This In-the-Loop block cannot be called from within a subsystem that can reset its states because the target code does not contain an 'InitializeConditions' function for In-the-Loop to invoke.\n");
    return;
  }
}

#endif                                 /* MDL_INITIALIZE_CONDITIONS */

#define MDL_SET_WORK_WIDTHS                                      /* Change to #undef to remove function */
#if defined(MDL_SET_WORK_WIDTHS)

static void mdlSetWorkWidths(SimStruct *S)
{
  /* Set number of run-time parameters */
  if (!ssSetNumRunTimeParams(S, 6))
    return;

  {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 0;
    ssRegDlgParamAsRunTimeParam(S, 0, 0, "P0_pcam", dataTypeId);
    if (ssGetErrorStatus(S) != (NULL))
      return;
  }

  {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 0;
    ssRegDlgParamAsRunTimeParam(S, 1, 1, "P1_startPos", dataTypeId);
    if (ssGetErrorStatus(S) != (NULL))
      return;
  }

  {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 1;
    ssRegDlgParamAsRunTimeParam(S, 2, 2, "P2_AxleLength", dataTypeId);
    if (ssGetErrorStatus(S) != (NULL))
      return;
  }

  {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 1;
    ssRegDlgParamAsRunTimeParam(S, 3, 3, "P3_EncRes", dataTypeId);
    if (ssGetErrorStatus(S) != (NULL))
      return;
  }

  {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 1;
    ssRegDlgParamAsRunTimeParam(S, 4, 4, "P4_WheelRadius", dataTypeId);
    if (ssGetErrorStatus(S) != (NULL))
      return;
  }

  {
    DTypeId dataTypeId = INVALID_DTYPE_ID;

    /* set datatype */
    dataTypeId = 8;
    ssRegDlgParamAsRunTimeParam(S, 5, 5, "P5_do_one_run", dataTypeId);
    if (ssGetErrorStatus(S) != (NULL))
      return;
  }
}

#endif                                 /* MDL_SET_WORK_WIDTHS */

static void mdlOutputs(SimStruct *S, int_T tid)
{
  /* Singlerate scheduling */
  /* check for sample time hit associated with task 1 */
  if (ssIsSampleHit(S, ssGetInputPortSampleTimeIndex(S, 0), tid)) {
    time_T taskTime = ssGetTaskTime(S, ssGetInputPortSampleTimeIndex(S, 0));

    {
      uint8_T * mxMemUnitPtr;
      mwSize dataInSize = 0;
      XIL_IOBuffer_T * IOBufferPtr = (XIL_IOBuffer_T *) ssGetPWorkValue(S, 1);
      if (IOBufferPtr != NULL) {
        void * pXILService = (void *) ssGetPWorkValue(S, 7);
        if (pXILService != NULL) {
          if (xilServiceGrowIOBuffer(pXILService, IOBufferPtr, 100, 0)!=
              XILSERVICE_SUCCESS) {
            return;
          }                            /* if */

          if (IOBufferPtr->data != NULL) {
            mxMemUnitPtr = (uint8_T *) IOBufferPtr->data;

            /* write command id */
            *mxMemUnitPtr = 3;
            mxMemUnitPtr++;

            {
              uint8_T * simDataMemUnitPtr;
              uint32_T commandDataFcnidTID[2] = { 0, 1 };

              simDataMemUnitPtr = (uint8_T *) &commandDataFcnidTID[0];

              {
                copyIOData( mxMemUnitPtr, simDataMemUnitPtr, &(mxMemUnitPtr), 2,
                           sizeof(uint32_T));
              }
            }

            {
              uint8_T * simDataMemUnitPtr;
              simDataMemUnitPtr = ( uint8_T *) ssGetInputPortSignal(S, 0);

              {
                copyIOData( mxMemUnitPtr, simDataMemUnitPtr, &(mxMemUnitPtr), 16,
                           sizeof(real32_T));
              }
            }

            {
              uint8_T * simDataMemUnitPtr;
              simDataMemUnitPtr = ( uint8_T *) ssGetInputPortSignal(S, 1);

              {
                copyIOData( mxMemUnitPtr, simDataMemUnitPtr, &(mxMemUnitPtr), 1,
                           sizeof(int32_T));
              }
            }

            {
              uint8_T * simDataMemUnitPtr;
              simDataMemUnitPtr = ( uint8_T *) ssGetInputPortSignal(S, 2);

              {
                copyIOData( mxMemUnitPtr, simDataMemUnitPtr, &(mxMemUnitPtr), 1,
                           sizeof(int32_T));
              }
            }

            {
              uint8_T * simDataMemUnitPtr;
              simDataMemUnitPtr = ( uint8_T *) ssGetInputPortSignal(S, 3);

              {
                copyIOData( mxMemUnitPtr, simDataMemUnitPtr, &(mxMemUnitPtr), 6,
                           sizeof(int16_T));
              }
            }

            {
              uint8_T * simDataMemUnitPtr;
              simDataMemUnitPtr = ( uint8_T *) ssGetInputPortSignal(S, 4);

              {
                copyIOData( mxMemUnitPtr, simDataMemUnitPtr, &(mxMemUnitPtr), 6,
                           sizeof(int8_T));
              }
            }

            {
              uint8_T * simDataMemUnitPtr;
              simDataMemUnitPtr = ( uint8_T *) ssGetInputPortSignal(S, 5);

              {
                copyIOData( mxMemUnitPtr, simDataMemUnitPtr, &(mxMemUnitPtr), 1,
                           sizeof(uint8_T));
              }
            }

            /* provide the time information to the code instrumentation service */
            {
              void * pCodeInstrService = (void *) ssGetPWorkValue(S, 8);
              codeInstrServiceSetTime(pCodeInstrService, taskTime);
            }

            /* dispatch command to the target */
            if (commandDispatch(S, IOBufferPtr, 100)!=XILSERVICE_SUCCESS) {
              return;
            }                          /* if */

            {
              XILCommandResponseType commandResponseType =
                XIL_COMMAND_NOT_COMPLETE;
              while (commandResponseType != XIL_STEP_COMPLETE) {
                /* receive command from the target */
                mwSize dataInSize = 0;
                if (commandResponse(S, &dataInSize, &commandResponseType) !=
                    XILSERVICE_SUCCESS) {
                  return;
                }                      /* if */

                if (dataInSize > 0) {
                  size_t dataInMemUnitSize = dataInSize;
                  uint8_T responseId = 0;
                  uint8_T * mxMemUnitPtrEnd;
                  mxMemUnitPtr = (uint8_T *) IOBufferPtr->data;
                  mxMemUnitPtrEnd = mxMemUnitPtr + dataInMemUnitSize - 1;
                  while (mxMemUnitPtr <= mxMemUnitPtrEnd) {
                    /* read response id */
                    responseId = *mxMemUnitPtr;
                    mxMemUnitPtr++;
                    switch (responseId) {
                     case RESPONSE_ERROR:
                     case RESPONSE_PRINTF:
                     case RESPONSE_FOPEN:
                     case RESPONSE_FPRINTF:
                      {
                        if (processErrorAndTargetIOResponseCases(S, responseId,
                             &mxMemUnitPtr, 0)== XILSERVICE_ERROR) {
                          return;
                        }              /* if */
                        break;
                      }

                     case RESPONSE_OUTPUT_DATA:
                      {
                        {
                          uint8_T * simDataMemUnitPtr;
                          simDataMemUnitPtr = ( uint8_T *) ssGetOutputPortSignal
                            (S, 0);

                          {
                            copyIOData( simDataMemUnitPtr, mxMemUnitPtr,
                                       &(mxMemUnitPtr), 1, sizeof(real32_T));
                          }
                        }

                        {
                          uint8_T * simDataMemUnitPtr;
                          simDataMemUnitPtr = ( uint8_T *) ssGetOutputPortSignal
                            (S, 1);

                          {
                            copyIOData( simDataMemUnitPtr, mxMemUnitPtr,
                                       &(mxMemUnitPtr), 1, sizeof(real32_T));
                          }
                        }

                        {
                          uint8_T * simDataMemUnitPtr;
                          simDataMemUnitPtr = ( uint8_T *) ssGetOutputPortSignal
                            (S, 2);

                          {
                            copyIOData( simDataMemUnitPtr, mxMemUnitPtr,
                                       &(mxMemUnitPtr), 1, sizeof(uint8_T));
                          }
                        }

                        {
                          uint8_T * simDataMemUnitPtr;
                          simDataMemUnitPtr = ( uint8_T *) ssGetOutputPortSignal
                            (S, 3);

                          {
                            copyIOData( simDataMemUnitPtr, mxMemUnitPtr,
                                       &(mxMemUnitPtr), 1, sizeof(uint8_T));
                          }
                        }

                        {
                          uint8_T * simDataMemUnitPtr;
                          simDataMemUnitPtr = ( uint8_T *) ssGetOutputPortSignal
                            (S, 4);

                          {
                            copyIOData( simDataMemUnitPtr, mxMemUnitPtr,
                                       &(mxMemUnitPtr), 1, sizeof(uint8_T));
                          }
                        }
                        break;
                      }

                     default:
                      {
                        {
                          mxArray * prhs[ 2 ];
                          prhs[0] = mxCreateString(
                            "PIL:pilverification:UnknownResponseId");
                          prhs[1] = mxCreateDoubleScalar(responseId);
                          callMATLAB(S, 0, NULL, 2, prhs, "DAStudio.error", 0);
                          return;
                        }
                        break;
                      }
                    }                  /* switch */
                  }                    /* while */
                }                      /* if */
              }                        /* while */
            }
          }                            /* if */
        }                              /* if */
      }                                /* if */
    }
  }                                    /* if */
}

static void mdlTerminate(SimStruct *S)
{
  int isOkToTerminate;
  int commErrorOccurred = 0;

  {
    if (ssGetPWork(S) != NULL) {
      int * pCommErrorOccurred = (int *) ssGetPWorkValue(S, 4);
      if (pCommErrorOccurred != NULL) {
        commErrorOccurred = *pCommErrorOccurred;
      }                                /* if */
    }                                  /* if */
  }

  {
    {
      mxArray *rhs[3];
      mxArray *lhs[1];
      const char * simulinkBlockPath = ssGetPath(S);
      rhs[ 0 ] = mxCreateString(
        "@coder.connectivity.SimulinkInterface.getSILPILInterface");
      rhs[ 1 ] = mxCreateDoubleScalar( 2 );
      rhs[ 2 ] = mxCreateString(simulinkBlockPath);
      callMATLAB(S, 1, lhs, 3, rhs,
                 "rtw.pil.SILPILInterface.sfunctionIsOkToTerminateHook", 0);
      isOkToTerminate = (int) (*mxGetPr(lhs[0]));
      mxDestroyArray(lhs[0]);
    }
  }

  if (isOkToTerminate) {
    if (!commErrorOccurred) {
      {
        uint8_T * mxMemUnitPtr;
        mwSize dataInSize = 0;
        XIL_IOBuffer_T * IOBufferPtr = (XIL_IOBuffer_T *) ssGetPWorkValue(S, 1);
        if (IOBufferPtr != NULL) {
          void * pXILService = (void *) ssGetPWorkValue(S, 7);
          if (pXILService != NULL) {
            if (xilServiceGrowIOBuffer(pXILService, IOBufferPtr, 5, 0)!=
                XILSERVICE_SUCCESS) {
              callStopHookAndFreeSFcnMemory(S);
              return;
            }                          /* if */

            if (IOBufferPtr->data != NULL) {
              mxMemUnitPtr = (uint8_T *) IOBufferPtr->data;

              /* write command id */
              *mxMemUnitPtr = 4;
              mxMemUnitPtr++;

              {
                uint8_T * simDataMemUnitPtr;
                uint32_T commandDataFcnid = 0;
                simDataMemUnitPtr = (uint8_T *) &commandDataFcnid;

                {
                  copyIOData( mxMemUnitPtr, simDataMemUnitPtr, &(mxMemUnitPtr),
                             1, sizeof(uint32_T));
                }
              }

              /* provide the time information to the code instrumentation service */
              {
                void * pCodeInstrService = (void *) ssGetPWorkValue(S, 8);
                time_T simTime = ssGetT(S);
                codeInstrServiceSetTime(pCodeInstrService, simTime);
              }

              /* dispatch command to the target */
              if (commandDispatch(S, IOBufferPtr, 5)!=XILSERVICE_SUCCESS) {
                callStopHookAndFreeSFcnMemory(S);
                return;
              }                        /* if */

              {
                XILCommandResponseType commandResponseType =
                  XIL_COMMAND_NOT_COMPLETE;
                while (commandResponseType != XIL_STEP_COMPLETE) {
                  /* receive command from the target */
                  mwSize dataInSize = 0;
                  if (commandResponse(S, &dataInSize, &commandResponseType) !=
                      XILSERVICE_SUCCESS) {
                    callStopHookAndFreeSFcnMemory(S);
                    return;
                  }                    /* if */

                  if (dataInSize > 0) {
                    size_t dataInMemUnitSize = dataInSize;
                    uint8_T responseId = 0;
                    uint8_T * mxMemUnitPtrEnd;
                    mxMemUnitPtr = (uint8_T *) IOBufferPtr->data;
                    mxMemUnitPtrEnd = mxMemUnitPtr + dataInMemUnitSize - 1;
                    while (mxMemUnitPtr <= mxMemUnitPtrEnd) {
                      /* read response id */
                      responseId = *mxMemUnitPtr;
                      mxMemUnitPtr++;
                      switch (responseId) {
                       case RESPONSE_ERROR:
                       case RESPONSE_PRINTF:
                       case RESPONSE_FOPEN:
                       case RESPONSE_FPRINTF:
                        {
                          if (processErrorAndTargetIOResponseCases(S, responseId,
                               &mxMemUnitPtr, 1)== XILSERVICE_ERROR) {
                            callStopHookAndFreeSFcnMemory(S);
                            return;
                          }            /* if */
                          break;
                        }

                       case RESPONSE_OUTPUT_DATA:
                        {
                          {
                            uint8_T * simDataMemUnitPtr;
                            simDataMemUnitPtr = ( uint8_T *)
                              ssGetOutputPortSignal(S, 0);

                            {
                              copyIOData( simDataMemUnitPtr, mxMemUnitPtr,
                                         &(mxMemUnitPtr), 1, sizeof(real32_T));
                            }
                          }

                          {
                            uint8_T * simDataMemUnitPtr;
                            simDataMemUnitPtr = ( uint8_T *)
                              ssGetOutputPortSignal(S, 1);

                            {
                              copyIOData( simDataMemUnitPtr, mxMemUnitPtr,
                                         &(mxMemUnitPtr), 1, sizeof(real32_T));
                            }
                          }

                          {
                            uint8_T * simDataMemUnitPtr;
                            simDataMemUnitPtr = ( uint8_T *)
                              ssGetOutputPortSignal(S, 2);

                            {
                              copyIOData( simDataMemUnitPtr, mxMemUnitPtr,
                                         &(mxMemUnitPtr), 1, sizeof(uint8_T));
                            }
                          }

                          {
                            uint8_T * simDataMemUnitPtr;
                            simDataMemUnitPtr = ( uint8_T *)
                              ssGetOutputPortSignal(S, 3);

                            {
                              copyIOData( simDataMemUnitPtr, mxMemUnitPtr,
                                         &(mxMemUnitPtr), 1, sizeof(uint8_T));
                            }
                          }

                          {
                            uint8_T * simDataMemUnitPtr;
                            simDataMemUnitPtr = ( uint8_T *)
                              ssGetOutputPortSignal(S, 4);

                            {
                              copyIOData( simDataMemUnitPtr, mxMemUnitPtr,
                                         &(mxMemUnitPtr), 1, sizeof(uint8_T));
                            }
                          }
                          break;
                        }

                       default:
                        {
                          {
                            mxArray * prhs[ 2 ];
                            prhs[0] = mxCreateString(
                              "PIL:pilverification:UnknownResponseId");
                            prhs[1] = mxCreateDoubleScalar(responseId);
                            callMATLAB(S, 0, NULL, 2, prhs, "DAStudio.error", 1);
                            callStopHookAndFreeSFcnMemory(S);
                            return;
                          }
                          break;
                        }
                      }                /* switch */
                    }                  /* while */
                  }                    /* if */
                }                      /* while */
              }
            }                          /* if */
          }                            /* if */
        }                              /* if */
      }

      {
        uint8_T * mxMemUnitPtr;
        mwSize dataInSize = 0;
        XIL_IOBuffer_T * IOBufferPtr = (XIL_IOBuffer_T *) ssGetPWorkValue(S, 1);
        if (IOBufferPtr != NULL) {
          void * pXILService = (void *) ssGetPWorkValue(S, 7);
          if (pXILService != NULL) {
            if (xilServiceGrowIOBuffer(pXILService, IOBufferPtr, 1, 0)!=
                XILSERVICE_SUCCESS) {
              callStopHookAndFreeSFcnMemory(S);
              return;
            }                          /* if */

            if (IOBufferPtr->data != NULL) {
              mxMemUnitPtr = (uint8_T *) IOBufferPtr->data;

              /* write command id */
              *mxMemUnitPtr = 10;
              mxMemUnitPtr++;

              /* provide the time information to the code instrumentation service */
              {
                void * pCodeInstrService = (void *) ssGetPWorkValue(S, 8);
                time_T simTime = ssGetT(S);
                codeInstrServiceSetTime(pCodeInstrService, simTime);
              }

              /* dispatch command to the target */
              if (commandDispatch(S, IOBufferPtr, 1)!=XILSERVICE_SUCCESS) {
                callStopHookAndFreeSFcnMemory(S);
                return;
              }                        /* if */
            }                          /* if */
          }                            /* if */
        }                              /* if */
      }
    }                                  /* if */

    callStopHookAndFreeSFcnMemory(S);
  }                                    /* if */
}

#define MDL_ENABLE
#if defined(MDL_ENABLE)

static void mdlEnable(SimStruct *S)
{
  if (ssGetT(S) != ssGetTStart(S)) {
    {
      mxArray * prhs[ 3 ];
      prhs[0] = mxCreateString("PIL:pil:EnableDisableCallbackError");
      prhs[1] = mxCreateString("enable");
      prhs[2] = mxCreateString("enable");
      callMATLAB(S, 0, NULL, 3, prhs, "DAStudio.error", 0);
      return;
    }
  }                                    /* if */
}

#endif                                 /* MDL_ENABLE */

#define MDL_DISABLE
#if defined(MDL_DISABLE)

static void mdlDisable(SimStruct *S)
{
  {
    mxArray * prhs[ 3 ];
    prhs[0] = mxCreateString("PIL:pil:EnableDisableCallbackError");
    prhs[1] = mxCreateString("disable");
    prhs[2] = mxCreateString("disable");
    callMATLAB(S, 0, NULL, 3, prhs, "DAStudio.error", 0);
    return;
  }
}

#endif                                 /* MDL_DISABLE */

/* Required S-function trailer */
#ifdef MATLAB_MEX_FILE                 /* Is this file being compiled as a MEX-file? */
#include "simulink.c"                  /* MEX-file interface mechanism */
#include "fixedpoint.c"
#else
#error Assertion failed: file must be compiled as a MEX-file
#endif
