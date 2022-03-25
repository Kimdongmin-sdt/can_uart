
//!*****************************************************************************
//!  \file      Demonstrator_V1_0.cpp
//!*****************************************************************************
//!
//!  \brief		Software Demonstration for the bachelor thesis.
//!
//!  \author    Pascal Frei (freip2)
//!
//!  \date      2019-06-27
//!
//!*****************************************************************************
//!
//!	 Copyright 2019 Bern University of Applied Sciences and Balluff AG
//!
//!	 Licensed under the Apache License, Version 2.0 (the "License");
//!  you may not use this file except in compliance with the License.
//!  You may obtain a copy of the License at
//!
//!	     http://www.apache.org/licenses/LICENSE-2.0
//!
//!	 Unless required by applicable law or agreed to in writing, software
//!	 distributed under the License is distributed on an "AS IS" BASIS,
//!	 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//!	 See the License for the specific language governing permissions and
//!	 limitations under the License.
//!
//!*****************************************************************************

//!**** Header-Files ***********************************************************
#include "../include/Demonstrator_V1_0.h"

#include "../include/Max14819.h"
#include "../include/BalluffBus0023.h"
#include "../include/IOLMasterPort.h"
#include "../include/IOLMasterPortMax14819.h"
#include "../include/IOLGenericDevice.h"
#include "../include/IOLink.h"

using namespace max14819;

#include <stdio.h>

typedef enum ISDU_FLOW_CTRL
{
    FLOW_CTRL_COUNT_x00 = 0x00,
    FLOW_CTRL_COUNT_x0F = 0x0F,
    FLOW_CTRL_START = 0x10,
    FLOW_CTRL_IDLE1 = 0x11,
    FLOW_CTRL_IDLE2 = 0x12,
    FLOW_CTRL_RESERVE_x13 = 0x00,
    FLOW_CTRL_RESERVE_x1E = 0x00,
    FLOW_CTRL_ABORT = 0x1F,
} ISDU_FLOW_CTRL_t;

#if 1
typedef enum iolink_arg_block_id
{
   IOLINK_ARG_BLOCK_ID_MASTERIDENT         = 0x0001,
   IOLINK_ARG_BLOCK_ID_FS_MASTER_ACCESS    = 0x0100,
   IOLINK_ARG_BLOCK_ID_W_MASTER_CFG        = 0x0200,
   IOLINK_ARG_BLOCK_ID_PD_IN               = 0x1001,
   IOLINK_ARG_BLOCK_ID_PD_OUT              = 0x1002,
   IOLINK_ARG_BLOCK_ID_PD_IN_OUT           = 0x1003,
   IOLINK_ARG_BLOCK_ID_SPDU_IN             = 0x1101,
   IOLINK_ARG_BLOCK_ID_SPDU_OUT            = 0x1102,
   IOLINK_ARG_BLOCK_ID_PD_IN_IQ            = 0x1FFE,
   IOLINK_ARG_BLOCK_ID_PD_OUT_IQ           = 0x1FFF,
   IOLINK_ARG_BLOCK_ID_OD_WR               = 0x3000,
   IOLINK_ARG_BLOCK_ID_OD_RD               = 0x3001,
   IOLINK_ARG_BLOCK_ID_DS_DATA             = 0x7000,
   IOLINK_ARG_BLOCK_ID_DEV_PAR_BAT         = 0x7001,
   IOLINK_ARG_BLOCK_ID_PORT_INXDEX_LIST    = 0x7002,
   IOLINK_ARG_BLOCK_ID_PORT_POWER          = 0x7003,
   IOLINK_ARG_BLOCK_ID_PORT_CFG_LIST       = 0x8000,
   IOLINK_ARG_BLOCK_ID_FS_PORT_CFG_LIST    = 0x8100,
   IOLINK_ARG_BLOCK_ID_W_TRACK_CFG_LIST    = 0x8200,
   IOLINK_ARG_BLOCK_ID_PORT_STATUS_LIST    = 0x9000,
   IOLINK_ARG_BLOCK_ID_FS_PORT_STATUS_LIST = 0x9100,
   IOLINK_ARG_BLOCK_ID_W_TRACK_STATUS_LIST = 0x9200,
   IOLINK_ARG_BLOCK_ID_W_TRACK_SCAN_RES    = 0x9201,
   IOLINK_ARG_BLOCK_ID_DEV_EVENT           = 0xA000,
   IOLINK_ARG_BLOCK_ID_PORT_EVENT          = 0xA001,
   IOLINK_ARG_BLOCK_ID_VOID_BLOCK          = 0xFFF0,
   IOLINK_ARG_BLOCK_ID_JOB_ERROR           = 0xFFFF,
} iolink_arg_block_id_t;


typedef enum iolink_eventcode
{
   IOLINK_EVENTCODE_NONE              = 0x0000,
   IOLINK_EVENTCODE_NO_DEV            = 0x1800,
   IOLINK_EVENTCODE_START_PARAM_ERR   = 0x1801,
   IOLINK_EVENTCODE_BAD_VID           = 0x1802,
   IOLINK_EVENTCODE_BAD_DID           = 0x1803,
   IOLINK_EVENTCODE_SHORT_CIR_CQ      = 0x1804,
   IOLINK_EVENTCODE_PHY_OVERTEMP      = 0x1805,
   IOLINK_EVENTCODE_SHORT_CIR_L       = 0x1806,
   IOLINK_EVENTCODE_OVERCUR_L         = 0x1807,
   IOLINK_EVENTCODE_DEV_EVENT_OVERF   = 0x1808,
   IOLINK_EVENTCODE_BACKUP_INCON_SIZE = 0x1809,
   IOLINK_EVENTCODE_BACKUP_INCON_ID   = 0x180A,
   IOLINK_EVENTCODE_BACKUP_INCON      = 0x180B,
   IOLINK_EVENTCODE_BACKUP_INCON_UL   = 0x180C,
   IOLINK_EVENTCODE_BACKUP_INCON_DL   = 0x180D,
   IOLINK_EVENTCODE_P24               = 0x180E,
   IOLINK_EVENTCODE_P24_SHORT_CIR     = 0x180F,
   IOLINK_EVENTCODE_SHORT_CIR_IQ      = 0x1810,
   IOLINK_EVENTCODE_SHORT_CIR_DO_CQ   = 0x1811,
   IOLINK_EVENTCODE_OVERCUR_IQ        = 0x1812,
   IOLINK_EVENTCODE_OVERCUR_CQ        = 0x1813,

   IOLINK_EVENTCODE_INVAL_CYCTIME = 0x6000,
   IOLINK_EVENTCODE_REV_FAULT     = 0x6001,
   IOLINK_EVENTCODE_ISDU_FAIL     = 0x6002,

   IOLINK_EVENTCODE_PORT_STATUS_CHANGE = 0xFF26,
   IOLINK_EVENTCODE_DS_UPLOAD_DONE     = 0xFF27,

   IOLINK_EVENTCODE_DEV_DS_UPLOAD_REQ = 0xFF91, /* From D.1 EventCodes for
                                                   Devices */
} iolink_eventcode_t;

typedef enum iolink_portmode
{
   IOLINK_PORTMODE_DEACTIVE = 0,
   IOLINK_PORTMODE_IOL_MAN  = 1,
   IOLINK_PORTMODE_IOL_AUTO = 2,
   IOLINK_PORTMODE_DI_CQ    = 3,
   IOLINK_PORTMODE_DO_CQ    = 4,
} iolink_portmode_t;

typedef enum iolink_validation_check
{
   IOLINK_VALIDATION_CHECK_NO              = 0,
   IOLINK_VALIDATION_CHECK_V10             = 1,
   IOLINK_VALIDATION_CHECK_V11             = 2,
   IOLINK_VALIDATION_CHECK_V11_BAK_RESTORE = 3,
   IOLINK_VALIDATION_CHECK_V11_RESTORE     = 4,
} iolink_validation_check_t;

typedef enum iolink_iq_behavior
{
   IOLINK_IQ_BEHAVIOR_NO_SUPPORT = 0,
   IOLINK_IQ_BEHAVIOR_DI         = 1,
   IOLINK_IQ_BEHAVIOR_DO         = 2,
   IOLINK_IQ_BEHAVIOR_RES1       = 3,
   IOLINK_IQ_BEHAVIOR_RES2       = 4,
   IOLINK_IQ_BEHAVIOR_POWER2     = 5,
} iolink_iq_behavior_t;

typedef enum
{
   IOLINK_PORT_TYPES_A            = 0,
   IOLINK_PORT_TYPES_A_POWER      = 1,
   IOLINK_PORT_TYPES_B            = 2,
   IOLINK_PORT_TYPES_FS_A_NO_OSSD = 3,
   IOLINK_PORT_TYPES_FS_A_OSSD    = 4,
   IOLINK_PORT_TYPES_FS_B         = 5,
   IOLINK_PORT_TYPES_W_MASTER     = 6,
} iolink_port_types_t;

typedef enum iolink_port_status_info
{
   IOLINK_PORT_STATUS_INFO_NO_DEV      = 0,
   IOLINK_PORT_STATUS_INFO_DEACTIVATED = 1,
   IOLINK_PORT_STATUS_INFO_PORT_DIAG   = 2,
   IOLINK_PORT_STATUS_INFO_PREOP       = 3,
   IOLINK_PORT_STATUS_INFO_OP          = 4,
   IOLINK_PORT_STATUS_INFO_DI          = 5,
   IOLINK_PORT_STATUS_INFO_DO          = 6,
   IOLINK_PORT_STATUS_INFO_POWER_OFF   = 254,
   IOLINK_PORT_STATUS_INFO_NOT_AVAIL   = 255,
} iolink_port_status_info_t;


typedef enum iolink_transmission_rate
{
   IOLINK_TRANSMISSION_RATE_NOT_DETECTED = 0,
   IOLINK_TRANSMISSION_RATE_COM1         = 1,
   IOLINK_TRANSMISSION_RATE_COM2         = 2,
   IOLINK_TRANSMISSION_RATE_COM3         = 3,
} iolink_transmission_rate_t;


typedef enum iolink_smi_errortypes
{
   IOLINK_SMI_ERRORTYPE_NONE = 0x0000,
   /* Table C.1 ErrorTypes */
   IOLINK_SMI_ERRORTYPE_APP_DEV               = 0x8000,
   IOLINK_SMI_ERRORTYPE_IDX_NOTAVAIL          = 0x8011,
   IOLINK_SMI_ERRORTYPE_SUBIDX_NOTAVAIL       = 0x8012,
   IOLINK_SMI_ERRORTYPE_SERV_NOTAVAIL         = 0x8020,
   IOLINK_SMI_ERRORTYPE_SERV_NOTAVAIL_LOCCTRL = 0x8021,
   IOLINK_SMI_ERRORTYPE_SERV_NOTAVAIL_DEVCTRL = 0x8022,
   IOLINK_SMI_ERRORTYPE_IDX_NOT_ACCESSIBLE    = 0x8023,
   IOLINK_SMI_ERRORTYPE_PAR_VALOUTOFRNG       = 0x8030,
   IOLINK_SMI_ERRORTYPE_PAR_VALGTLIM          = 0x8031,
   IOLINK_SMI_ERRORTYPE_PAR_VALLTLIM          = 0x8032,
   IOLINK_SMI_ERRORTYPE_VAL_LENOVRRUN         = 0x8033, /* Also in C.2 */
   IOLINK_SMI_ERRORTYPE_VAL_LENUNDRUN         = 0x8034,
   IOLINK_SMI_ERRORTYPE_FUNC_NOTAVAIL         = 0x8035,
   IOLINK_SMI_ERRORTYPE_FUNC_UNAVAILTEMP      = 0x8036,
   IOLINK_SMI_ERRORTYPE_PAR_SETINVALID        = 0x8040,
   IOLINK_SMI_ERRORTYPE_PAR_SETINCONSIST      = 0x8041,
   IOLINK_SMI_ERRORTYPE_APP_DEVNOTRDY         = 0x8082,
   IOLINK_SMI_ERRORTYPE_UNSPECIFIC            = 0x8100,
   /* Table C.2 Derivced ErrorTypes */
   IOLINK_SMI_ERRORTYPE_COM_ERR           = 0x1000,
   IOLINK_SMI_ERRORTYPE_I_SERVICE_TIMEOUT = 0x1100,
   IOLINK_SMI_ERRORTYPE_M_ISDU_CHECKSUM   = 0x5600,
   IOLINK_SMI_ERRORTYPE_M_ISDU_ILLEGAL    = 0x5700,

   /* Table C.3 SMI related ErrorTypes */
   IOLINK_SMI_ERRORTYPE_ARGBLOCK_NOT_SUPPORTED   = 0x4001,
   IOLINK_SMI_ERRORTYPE_ARGBLOCK_INCONSISTENT    = 0x4002,
   IOLINK_SMI_ERRORTYPE_DEV_NOT_ACCESSIBLE       = 0x4003,
   IOLINK_SMI_ERRORTYPE_SERVICE_NOT_SUPPORTED    = 0x4004,
   IOLINK_SMI_ERRORTYPE_DEV_NOT_IN_OPERATE       = 0x4005,
   IOLINK_SMI_ERRORTYPE_MEMORY_OVERRUN           = 0x4006,
   IOLINK_SMI_ERRORTYPE_PORT_NUM_INVALID         = 0x4011,
   IOLINK_SMI_ERRORTYPE_ARGBLOCK_LENGTH_INVALID  = 0x4034,
   IOLINK_SMI_ERRORTYPE_SERVICE_TEMP_UNAVAILABLE = 0x4036,
} iolink_smi_errortypes_t;


typedef enum iolink_master_type
{
   IOLINK_MASTER_TYPE_UNSPEC     = 0,
   IOLINK_MASTER_TYPE_RESERVED   = 1,
   IOLINK_MASTER_TYPE_MASTER_ACC = 2,
   IOLINK_MASTER_TYPE_FS         = 3,
   IOLINK_MASTER_TYPE_W          = 4,
} iolink_master_type_t;

typedef enum  IOLINK_MC_TYPE{
    IOLINK_MC_TYPE_PROCESS      =   0,
    IOLINK_MC_TYPE_PAGE         =   1,
    IOLINK_MC_TYPE_DIAGNOSIS    =   2,
    IOLINK_MC_TYPE_ISDU         =   3
} IOLINK_MC_TYPE_t;

typedef enum  IOLINK_MC_RW{
    IOLINK_MC_TYPE_WRITE      =   0,
    IOLINK_MC_TYPE_READ       =   1,
} IOLINK_MC_RW_t;

typedef union {
    struct
    {
        unsigned short b0 : 1;
        unsigned short b1 : 1;
        unsigned short b2 : 1;
        unsigned short b3 : 1;
        unsigned short b4 : 1;
        unsigned short b5 : 1;
        unsigned short b6 : 1;
        unsigned short b7 : 1;
        unsigned short b8 : 1;
        unsigned short b9 : 1;
        unsigned short b10 : 1;
        unsigned short b11 : 1;
        unsigned short b12 : 1;
        unsigned short b13 : 1;
        unsigned short b14 : 1;
        unsigned short b15 : 1;
    } bits;
    uint8_t bytes[2];
    uint16_t word;
} WORD_t;


typedef union SENSOR_MC{
    struct
    {
        unsigned char addr:5; // adress
        unsigned char mc_tye:2;
        unsigned char rw_flag:1;
    }bits;
    uint8_t data;
}SENSOR_MC_t;

typedef union {
        struct
    {
        unsigned char CHK         : 6;
        unsigned char FRAME_TYPE  : 2;
    }s;
    unsigned char data;
}CKT_t;

typedef enum STATE{
    IDLE=0,
    SETUP,
    READ
}Machine_t;

typedef enum SDI_STATE{
    SETUP_STEP_0  =   0,
    SETUP_STEP_1,
    SETUP_STEP_2,
    SETUP_STEP_3,
    SETUP_STEP_4
} SDI_STATE_T;
#endif
static Machine_t state = IDLE;

typedef union {
    struct
    {
        SENSOR_MC_t _mc;        //8, FC
        CKT_t _ckt;             //8
        unsigned char _process_data;    //8
        unsigned char on_req_data;      //8
    }st;
    uint8_t bytes[4];       //32
    unsigned int raw;       //32 bit
} ISDU_SEND_u;

typedef union {
        struct
    {
        unsigned char CHK  : 6;
        unsigned char PD    : 1;
        unsigned char E  : 1;
    }s;
    unsigned char data;
}CKS_t;

typedef union {
    struct
    {
        CKS_t _cks;             //8
        unsigned char _process_data;    //8
        unsigned char on_req_data;      //8
    }st;
    uint8_t bytes[3];       //32
    unsigned int raw;       //32 bit
} ISDU_RECV_u;

typedef struct arg_block_od
{
   iolink_arg_block_id_t arg_block_id; // IOLINK_ARG_BLOCK_ID_OD_{WR,RD}
   uint16_t index;
   uint8_t subindex;
   uint8_t data[];
} arg_block_od_t;

//!**** Macros *****************************************************************

//!**** Data types *************************************************************
IOLMasterPortMax14819 port0;
IOLMasterPortMax14819 port1;
IOLMasterPortMax14819 port2;
IOLMasterPortMax14819 port3;
static Max14819 *pDriver01;
static Max14819 *pDriver23;

#if 0
BalluffBus0023 BUS0023;
#endif
HardwareBase * hardware;
//!**** Function prototypes ****************************************************
void printDataMatlab(uint16_t level, uint32_t measureNr);
//!**** Data *******************************************************************

//!**** Implementation *********************************************************

//The setup function is called once at startup of the sketch
void Demo_setup(HardwareBase *hardware_loc)
{
    //testDistSensorPortLayer();
	// Create hardware setup
    hardware = hardware_loc;
	hardware->begin();

    // Create drivers
    pDriver01 = new max14819::Max14819(max14819::DRIVER01, hardware);
    pDriver23 = new max14819::Max14819(max14819::DRIVER23, hardware);

    // Create ports
    port0 = IOLMasterPortMax14819(pDriver01, max14819::PORT0PORT);
	port1 = IOLMasterPortMax14819(pDriver01, max14819::PORT1PORT);
	port2 = IOLMasterPortMax14819(pDriver23, max14819::PORT2PORT);
	port3 = IOLMasterPortMax14819(pDriver23, max14819::PORT3PORT);
#if 0
    BUS0023 = BalluffBus0023(&port1);
#endif
    // Start IO-Link communication
	//BUS0023.begin();
    //port0.begin();
    port1.begin();
#if 0
    port2.begin();
    port3.begin();
#endif
    state=SETUP;
}

#define SSC1_SWITCH_ON_DELAY_SUBIDX             0
#define ON_REQ_DATA_DEFAULT                     181
#define SSC1_SWITCH_ON_DELAY                    370
#define SSC1_SWITCH_OFF_DELAY                   371
#define SSC2_SWITCH_ON_DELAY                    372
#define SSC2_SWITCH_OFF_DELAY                   373
#define SSC1_SWITCH_ON_DELAY_SET_VALUE          125
#define SSC1_SWITCH_OFF_DELAY_SET_VALUE         5700
#define SSC2_SWITCH_ON_DELAY_SET_VALUE          5600
#define SSC2_SWITCH_OFF_DELAY_SET_VALUE         5500


uint8_t CalculateCHKPDU( char* pData, size_t size)
{

    uint16_t temp=0;
    for ( int i=0;i<size;i++)
    {
        temp ^= pData[i];
    }
    return (temp & 0xFF);
}

void process(void)
{
    SENSOR_MC_t _SensorMC;
    SDI_STATE_T _SensorSetupStep=SETUP_STEP_0;
    uint8_t sizeData = 0;
    PortSelect _port = PORTB;
    WORD_t value;
    WORD_t index;
    value.word=0;
    index.word = ON_REQ_DATA_DEFAULT;
    ISDU_SEND_u send_msg;
    unsigned char ProcessData[10];
    int nPos=0;
    for(;;)
    {
        switch (state)
        {
        case IDLE:
            break;

        case SETUP: {
            switch (_SensorSetupStep) {
            case SETUP_STEP_0:{
                memset( ProcessData,0,sizeof(ProcessData));


                ProcessData[nPos++]=(ON_REQ_DATA_DEFAULT & 0Xff );
                WORD_t temp;
                temp.word=0;
                temp.word = SSC1_SWITCH_ON_DELAY_SET_VALUE;
                ProcessData[nPos++]=temp.bytes[1];  //index hi
                ProcessData[nPos++]=temp.bytes[0]; // index low
                ProcessData[nPos++]=SSC1_SWITCH_ON_DELAY_SUBIDX; //sub index
                ProcessData[nPos++] = 0;
                uint8_t chk = CalculateCHKPDU( (char*)ProcessData,nPos );
                printf(" checksum=0x%x \n",chk);
                ProcessData[nPos] = chk;



                nPos=0;
                _SensorMC.data = 0;
                _SensorMC.bits.addr = 0x65;
                _SensorMC.bits.mc_tye = IOLINK_MC_TYPE_ISDU;
                _SensorMC.bits.rw_flag = IOLINK_MC_TYPE_WRITE;

                value.word = SSC1_SWITCH_ON_DELAY_SET_VALUE;
                // FC
                send_msg.raw=0;
                send_msg.st._mc.bits.mc_tye = IOLINK_MC_TYPE_ISDU;
                send_msg.st._mc.bits.addr = FLOW_CTRL_START;
                send_msg.st._mc.bits.rw_flag = IOLINK_MC_TYPE_WRITE;
                send_msg.st._process_data = ProcessData[nPos++];

                // FC

                //CKT
                send_msg.st._ckt.data = calculateCKT(send_msg.st._mc.data, &send_msg.st._process_data, sizeof(send_msg.st._process_data), IOL::M_TYPE_2_X);
                printf("frame=0x%x\n",send_msg.raw);
                printf("byteframe [0]=0x%x,[1]=0x%x,[2]=0x%x,[3]=0x%x\n",send_msg.bytes[0], send_msg.bytes[1], send_msg.bytes[2], send_msg.bytes[3]);
                printf("mc=0x%x, processdata=0x%x, ckt=0x%x\n",send_msg.st._mc.data, send_msg.st._process_data,send_msg.st._ckt );
                printf("mc_type :  0x%x, mc_addr : 0x%x, mc_rw_flag : 0x%x\n", send_msg.st._mc.bits.mc_tye, send_msg.st._mc.bits.addr,  send_msg.st._mc.bits.rw_flag);
#if 1
                pDriver01->writeRegister(TxRxDataB, send_msg.bytes[0]);
                pDriver01->writeRegister(TxRxDataB, send_msg.st._ckt.data);
                pDriver01->writeRegister(TxRxDataB, send_msg.st._process_data);
                pDriver01->writeRegister(TxRxDataB, send_msg.st.on_req_data);
#endif

                _SensorSetupStep = SETUP_STEP_1;
                ThisThread::sleep_for(50ms);
            } break;
            case SETUP_STEP_1:{
                ISDU_SEND_u send_msg;
                // FC
                send_msg.raw=0;
                send_msg.st._mc.bits.mc_tye = IOLINK_MC_TYPE_ISDU;
                send_msg.st._mc.bits.addr = FLOW_CTRL_COUNT_x00;
                send_msg.st._mc.bits.rw_flag = IOLINK_MC_TYPE_WRITE;
                send_msg.st._process_data = ProcessData[nPos++];

                // FC

                //CKT
                send_msg.st._ckt.data = calculateCKT(send_msg.st._mc.data, &send_msg.st._process_data, sizeof(send_msg.st._process_data), IOL::M_TYPE_2_X);
                printf("frame=0x%x\n",send_msg.raw);
                printf("byteframe [0]=0x%x,[1]=0x%x,[2]=0x%x,[3]=0x%x\n",send_msg.bytes[0], send_msg.bytes[1], send_msg.bytes[2], send_msg.bytes[3]);
                printf("mc=0x%x, processdata=0x%x, ckt=0x%x\n",send_msg.st._mc.data, send_msg.st._process_data,send_msg.st._ckt );
                printf("mc_type :  0x%x, mc_addr : 0x%x, mc_rw_flag : 0x%x\n", send_msg.st._mc.bits.mc_tye, send_msg.st._mc.bits.addr,  send_msg.st._mc.bits.rw_flag);

                pDriver01->writeRegister(TxRxDataB, send_msg.bytes[0]);
                pDriver01->writeRegister(TxRxDataB, send_msg.st._ckt.data);
                pDriver01->writeRegister(TxRxDataB, send_msg.st._process_data);
                pDriver01->writeRegister(TxRxDataB, send_msg.st.on_req_data);

                _SensorSetupStep = SETUP_STEP_2;
                ThisThread::sleep_for(50ms);
            }break;
            case SETUP_STEP_2:{
                ISDU_SEND_u send_msg;
                // FC
                send_msg.raw=0;
                send_msg.st._mc.bits.mc_tye  = IOLINK_MC_TYPE_ISDU;
                send_msg.st._mc.bits.addr    = FLOW_CTRL_COUNT_x00;
                send_msg.st._mc.bits.rw_flag = IOLINK_MC_TYPE_WRITE;
                send_msg.st._process_data    = ProcessData[nPos++];

                // FC

                //CKT
                send_msg.st._ckt.data = calculateCKT(send_msg.st._mc.data, &send_msg.st._process_data, sizeof(send_msg.st._process_data), IOL::M_TYPE_2_X);
                printf("frame=0x%x\n",send_msg.raw);
                printf("byteframe [0]=0x%x,[1]=0x%x,[2]=0x%x,[3]=0x%x\n",send_msg.bytes[0], send_msg.bytes[1], send_msg.bytes[2], send_msg.bytes[3]);
                printf("mc=0x%x, processdata=0x%x, ckt=0x%x\n",send_msg.st._mc.data, send_msg.st._process_data,send_msg.st._ckt );
                printf("mc_type :  0x%x, mc_addr : 0x%x, mc_rw_flag : 0x%x\n", send_msg.st._mc.bits.mc_tye, send_msg.st._mc.bits.addr,  send_msg.st._mc.bits.rw_flag);

                pDriver01->writeRegister(TxRxDataB, send_msg.bytes[0]);
                pDriver01->writeRegister(TxRxDataB, send_msg.st._ckt.data);
                pDriver01->writeRegister(TxRxDataB, send_msg.st._process_data);
                pDriver01->writeRegister(TxRxDataB, send_msg.st.on_req_data);

                _SensorSetupStep = SETUP_STEP_3;
                ThisThread::sleep_for(50ms);
             } break;
            case SETUP_STEP_3:{
                ISDU_SEND_u send_msg;
                // FC
                send_msg.raw=0;
                send_msg.st._mc.bits.mc_tye  = IOLINK_MC_TYPE_ISDU;
                send_msg.st._mc.bits.addr    = FLOW_CTRL_COUNT_x00;
                send_msg.st._mc.bits.rw_flag = IOLINK_MC_TYPE_WRITE;
                send_msg.st._process_data    = SSC1_SWITCH_ON_DELAY_SUBIDX;
                send_msg.st.on_req_data = SSC1_SWITCH_ON_DELAY_SUBIDX;
                // FC

                //CKT
                send_msg.st._ckt.data = calculateCKT(send_msg.st._mc.data, &send_msg.st._process_data, sizeof(send_msg.st._process_data), IOL::M_TYPE_2_X);
                printf("frame=0x%x\n",send_msg.raw);
                printf("byteframe [0]=0x%x,[1]=0x%x,[2]=0x%x,[3]=0x%x\n",send_msg.bytes[0], send_msg.bytes[1], send_msg.bytes[2], send_msg.bytes[3]);
                printf("mc=0x%x, processdata=0x%x, ckt=0x%x\n",send_msg.st._mc.data, send_msg.st._process_data,send_msg.st._ckt );
                printf("mc_type :  0x%x, mc_addr : 0x%x, mc_rw_flag : 0x%x\n", send_msg.st._mc.bits.mc_tye, send_msg.st._mc.bits.addr,  send_msg.st._mc.bits.rw_flag);

                pDriver01->writeRegister(TxRxDataB, send_msg.bytes[0]);
                pDriver01->writeRegister(TxRxDataB, send_msg.st._ckt.data);
                pDriver01->writeRegister(TxRxDataB, send_msg.st._process_data);
                pDriver01->writeRegister(TxRxDataB, send_msg.st.on_req_data);

                _SensorSetupStep = SETUP_STEP_4;
                ThisThread::sleep_for(50ms);
            }break;
            case SETUP_STEP_4:{
                ISDU_SEND_u send_msg;
                // FC
                send_msg.raw=0;
                send_msg.st._mc.bits.mc_tye  = IOLINK_MC_TYPE_ISDU;
                send_msg.st._mc.bits.addr    = FLOW_CTRL_COUNT_x00;
                send_msg.st._mc.bits.rw_flag = IOLINK_MC_TYPE_WRITE;
                send_msg.st._process_data    = SSC1_SWITCH_ON_DELAY_SET_VALUE;
                // FC

                //CKT
                send_msg.st._ckt.data = calculateCKT(send_msg.st._mc.data, &send_msg.st._process_data, sizeof(send_msg.st._process_data), IOL::M_TYPE_2_X);
                printf("frame=0x%x\n",send_msg.raw);
                send_msg.st.on_req_data = send_msg.raw;
                printf("byteframe [0]=0x%x,[1]=0x%x,[2]=0x%x,[3]=0x%x\n",send_msg.bytes[0], send_msg.bytes[1], send_msg.bytes[2], send_msg.bytes[3]);
                printf("mc=0x%x, processdata=0x%x, ckt=0x%x\n",send_msg.st._mc.data, send_msg.st._process_data,send_msg.st._ckt );
                printf("mc_type :  0x%x, mc_addr : 0x%x, mc_rw_flag : 0x%x\n", send_msg.st._mc.bits.mc_tye, send_msg.st._mc.bits.addr,  send_msg.st._mc.bits.rw_flag);




                pDriver01->writeRegister(TxRxDataB, send_msg.bytes[0]);
                pDriver01->writeRegister(TxRxDataB, send_msg.st._ckt.data);
                pDriver01->writeRegister(TxRxDataB, send_msg.st._process_data);
                pDriver01->writeRegister(TxRxDataB, send_msg.st.on_req_data);

                ThisThread::sleep_for(50ms);
                state = READ;
            }break;
            }
            break;

        }
        case READ: {
            uint8_t pData[4];
            uint8_t sizeData = 4;
            pDriver01->readData(pData, sizeData, _port);
            printf("receive data : ");
            for (int i = 0 ; i < sizeData; i++) {
                printf("pData[%d] : 0x%02x\t", i, pData[i]);
            }

            putchar('\n');
        } break;

        default:
            break;
        }

        ThisThread::sleep_for(50);
    }
}

// The loop function is called in an endless loop
void Demo_loop()
{
    hardware->Serial_Write("LOOP");
	// Variables used for distance and level conversation
	uint16_t distance = 0;
	uint16_t testVal = 0;
	uint16_t level = 0;
	uint8_t data[4];
	char buf[64];

	// Default levels for demonstrator
	uint16_t TANK_MAX_LVL = 210;
	uint16_t TANK_WARNING_LVL = 100;
	uint32_t measureNr = 0;
    constexpr uint16_t TANK_EMPTY_LVL = 50;
    while (1) {
        hardware->wait_for(100);
        // Read process data and convert them if there is no error
        constexpr int input_data_size = 20;
        uint8_t data[input_data_size];
        uint16_t distance = 0;
        if (port1.readPD(data, input_data_size) != ERROR) {
            //distance = (uint16_t)(((data[1] << 8) | data[2]) >> 1);
        }

		//distance = BUS0023.readDistance();
		hardware->Serial_Write("Messung");
		sprintf(buf, "%d", distance);
		hardware->Serial_Write(buf);
    }
}

void printDataMatlab(uint16_t level, uint32_t measureNr) {
}
