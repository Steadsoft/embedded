typedef const struct nrf24_package_interface nrf24_package_struct, * nrf24_package_ptr;
typedef const struct nrf_registers nrf24_register_names;
typedef const struct nrf_commands nrf24_command_names;



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
typedef struct NrfReg_RPD_struct NrfReg_RPD, * NrfReg_RPD_ptr;
typedef struct NrfReg_RX_ADDR_LONG_struct NrfReg_RX_ADDR_LONG, * NrfReg_RX_ADDR_LONG_ptr;
typedef struct NrfReg_RX_ADDR_SHORT_struct NrfReg_RX_ADDR_SHORT, * NrfReg_RX_ADDR_SHORT_ptr;
typedef struct NrfReg_TX_ADDR_LONG_struct NrfReg_TX_ADDR_LONG, * NrfReg_TX_ADDR_LONG_ptr;
typedef struct NrfReg_RX_PW_struct NrfReg_RX_PW, * NrfReg_RX_PW_ptr;
typedef struct NrfReg_FIFO_STATUS_struct NrfReg_FIFO_STATUS, * NrfReg_FIFO_STATUS_ptr;
typedef struct NrfReg_DYNPD_struct NrfReg_DYNPD, * NrfReg_DYNPD_ptr;
typedef struct NrfReg_FEATURE_struct NrfReg_FEATURE, * NrfReg_FEATURE_ptr;

typedef struct NrfReg_ALL_REGISTERS_struct NrfReg_ALL_REGISTERS, * NrfReg_ALL_REGISTERS_ptr;

