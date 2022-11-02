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

typedef union nrf_reg_CONFIG_union NrfReg_CONFIG, * NrfReg_CONFIG_ptr;
typedef union nrf_reg_EN_AA_union NrfReg_EN_AA, * NrfReg_EN_AA_ptr;
typedef union nrf_reg_EN_RXADDR_union NrfReg_EN_RXADDR, * NrfReg_EN_RXADDR_ptr;
typedef union nrf_reg_SETUP_AW_union NrfReg_SETUP_AW, * NrfReg_SETUP_AW_ptr;
typedef union nrf_reg_SETUP_RETR_union NrfReg_SETUP_RETR, * NrfReg_SETUP_RETR_ptr;
typedef union nrf_reg_RF_CH_union NrfReg_RF_CH, * NrfReg_RF_CH_ptr;
typedef union nrf_reg_RF_SETUP_union NrfReg_RF_SETUP, * NrfReg_RF_SETUP_ptr;
typedef union nrf_reg_STATUS_union NrfReg_STATUS, * NrfReg_STATUS_ptr;
typedef union nrf_reg_OBSERVE_TX_union NrfReg_OBSERVE_TX, * NrfReg_OBSERVE_TX_ptr;
typedef union nrf_reg_CD_union NrfReg_CD, * NrfReg_CD_ptr;
typedef union nrf_reg_RX_ADDR_union NrfReg_RX_ADDR, * NrfReg_RX_ADDR_ptr;
typedef union nrf_reg_RX_PW_union NrfReg_RX_PW, * NrfReg_RX_PW_ptr;
typedef union nrf_reg_DYNPD_union NrfReg_DYNPD, * NrfReg_DYNPD_ptr;
typedef union nrf_reg_FEATURE_union NrfReg_FEATURE, * NrfReg_FEATURE_ptr;

