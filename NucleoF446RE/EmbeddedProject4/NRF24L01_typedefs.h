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

typedef union nrf_reg_STATUS_union NrfReg_STATUS, * NrfReg_STATUS_ptr;
typedef union nrf_reg_CONFIG_union NrfReg_CONFIG, * NrfReg_CONFIG_ptr;
typedef union nrf_reg_RF_CH_union NrfReg_RF_CH, * NrfReg_RF_CH_ptr;
typedef union nrf_reg_EN_AA_union NrfReg_EN_AA, * NrfReg_EN_AA_ptr;
typedef union nrf_reg_EN_RXADDR_union NrfReg_EN_RXADDR, * NrfReg_EN_RXADDR_ptr;
