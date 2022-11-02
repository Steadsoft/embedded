typedef struct nrf_library_calls NrfLibraryCalls, * NrfLibraryCalls_ptr;
typedef struct nrf_register_calls NrfRegisterCalls, * NrfRegisterCalls_ptr;
typedef struct nrf_io_interface NrfIoInterface, * NrfIoInterface_ptr;
typedef struct nrf_io_callbacks NrfIoCallbacks, * NrfIoCallbacks_ptr;
typedef struct nrf_registers NrfRegisters, * NrfIoRegisters_ptr;
typedef struct nrf_spi_device NrfSpiDevice, * NrfSpiDevice_ptr;

/*---------------------------------------------------------------------*/
/* Registers are all defined as unions to faciliate access to their    */
/* individual fields yet also enable low level code to pass the fields */
/* as a simple byte.                                                   */
/*---------------------------------------------------------------------*/

typedef struct NrfReg_CONFIG_struct NrfReg_CONFIG, * NrfReg_CONFIG_ptr;
typedef struct NrfReg_EN_AA_struct NrfReg_EN_AA, * NrfReg_EN_AA_ptr;
typedef struct NrfReg_EN_RXADDR_struct NrfReg_EN_RXADDR, * NrfReg_EN_RXADDR_ptr;
typedef struct NrfReg_SETUP_AW_struct NrfReg_SETUP_AW, * NrfReg_SETUP_AW_ptr;
typedef struct NrfReg_SETUP_RETR_struct NrfReg_SETUP_RETR, * NrfReg_SETUP_RETR_ptr;
typedef struct NrfReg_RF_CH_struct NrfReg_RF_CH, * NrfReg_RF_CH_ptr;
typedef struct NrfReg_RF_SETUP_struct NrfReg_RF_SETUP, * NrfReg_RF_SETUP_ptr;
typedef struct NrfReg_STATUS_struct NrfReg_STATUS, * NrfReg_STATUS_ptr;
typedef struct NrfReg_OBSERVE_TX_struct NrfReg_OBSERVE_TX, * NrfReg_OBSERVE_TX_ptr;
typedef struct NrfReg_CD_struct NrfReg_CD, * NrfReg_CD_ptr;
typedef struct NrfReg_RX_ADDR_struct NrfReg_RX_ADDR, * NrfReg_RX_ADDR_ptr;
typedef struct NrfReg_RX_PW_struct NrfReg_RX_PW, * NrfReg_RX_PW_ptr;
typedef struct NrfReg_DYNPD_struct NrfReg_DYNPD, * NrfReg_DYNPD_ptr;
typedef struct NrfReg_FEATURE_struct NrfReg_FEATURE, * NrfReg_FEATURE_ptr;
