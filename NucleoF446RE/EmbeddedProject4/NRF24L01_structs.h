/* Note, all bitfield structs are lexically ordered with */
/* the MSB at the bottom and the LSB at the top.         */
struct nrf_registers
{
	uint8_t CONFIG;
	uint8_t EN_AA ;
	uint8_t EN_RXADDR;
	uint8_t SETUP_AW ;
	uint8_t SETUP_RETR ;
	uint8_t RF_CH;
	uint8_t RF_SETUP;
	uint8_t STATUS;
	uint8_t OBSERVE_TX;
	uint8_t CD;
	uint8_t RX_ADDR_P0;
	uint8_t RX_ADDR_P1;
	uint8_t RX_ADDR_P2;
	uint8_t RX_ADDR_P3 ;
	uint8_t RX_ADDR_P4;
	uint8_t RX_ADDR_P5;
	uint8_t TX_ADDR;
	uint8_t RX_PW_P0;
	uint8_t RX_PW_P1;
	uint8_t RX_PW_P2;
	uint8_t RX_PW_P3;
	uint8_t RX_PW_P4;
	uint8_t RX_PW_P5;
	uint8_t FIFO_STATUS;
	uint8_t DYNPD;
	uint8_t FEATURE;
};

// Create (in effect) a "namespace" for containing all of the register names.

// This type represents all of the hardware specific items needed by the library.

struct nrf_spi_device
{
	void(* ReadBytes)(void * io_ptr, uint8_t BytesIn[], uint8_t BytesToRead);
	void(* WriteBytes)(void * io_ptr, uint8_t BytesOut[], uint8_t BytesToWrite);
	void(* ExchangeBytes)(void * io_ptr, uint8_t BytesOut[], uint8_t BytesIn[], uint8_t Count);
	void(* SelectDevice)(void * io_ptr);
	void(* DeselectDevice)(void * io_ptr);
	void * io_ptr;
};

// Register structures

union nrf_reg_CONFIG_union
{
	uint8_t value;
	struct 
	{
		uint8_t PRIM_RX : 1;
		uint8_t PWR_UP : 1;
		uint8_t CRCO : 1;
		uint8_t EN_CRC : 1;
		uint8_t MASK_MAX_RT : 1;
		uint8_t MASK_TX_DS : 1;
		uint8_t MASK_RX_DR : 1;
		uint8_t RESERVED : 1;

	} fields;
};
union nrf_reg_EN_AA_union
{
	uint8_t value;

	struct 
	{
		uint8_t ENAA_P0 : 1;
		uint8_t ENAA_P1 : 1;
		uint8_t ENAA_P2 : 1;
		uint8_t ENAA_P3 : 1;
		uint8_t ENAA_P4 : 1;
		uint8_t ENAA_P5 : 1;
		uint8_t RESERVED : 2;

	} fields;
};
union nrf_reg_EN_RXADDR_union
{
	uint8_t value;
	struct 
	{
		uint8_t ERX_P0 : 1;
		uint8_t ERX_P1 : 1;
		uint8_t ERX_P2 : 1;
		uint8_t ERX_P3 : 1;
		uint8_t ERX_P4 : 1;
		uint8_t ERX_P5 : 1;
		uint8_t RESERVED : 2;

	} fields;
};
union nrf_reg_SETUP_AW_union
{
	uint8_t value;
	struct 
	{
		uint8_t AW : 2;
		uint8_t RESERVED : 6;

	} fields;
};
union nrf_reg_SETUP_RETR_union
{
	uint8_t value;
	struct 
	{
		uint8_t ARC : 4;
		uint8_t ARD : 4;
	} fields;

};
union nrf_reg_RF_CH_union
{
	uint8_t value;
	struct 
	{
		uint8_t RF_CH : 7;
		uint8_t RESERVED : 1;
	} fields;
};
union nrf_reg_RF_SETUP_union
{
	uint8_t value;
	struct
	{
		uint8_t  LNA_HCURR : 1;
		uint8_t  RF_PWR : 2;
		uint8_t  RF_DR : 1;
		uint8_t  PLL_LOCK : 1;
		uint8_t  RESERVED : 3;
	} fields;
};
union nrf_reg_STATUS_union
{
	uint8_t value;
	struct 
	{
		uint8_t  TX_FULL : 1;
		uint8_t  RX_P_NO : 3;
		uint8_t  MAX_RT : 1;
		uint8_t  TX_DS : 1;
		uint8_t  RX_DR : 1;
		uint8_t  RESERVED : 1;

	} fields;
};
union nrf_reg_OBSERVE_TX_union
{
	uint8_t value;
	struct 
	{
		uint8_t  ARC_CNT : 4;
		uint8_t  PLOS_CNT : 4;

	} fields;
};
union nrf_reg_CD_union
{
	uint8_t value;
	struct 
	{
		uint8_t  CD : 1;
		uint8_t  RESERVED : 7;

	} fields;
};
union nrf_reg_RX_ADDR_union // Represents every RX_ADDR short register from _P2 thru _P5
{
	uint8_t value;
	struct 
	{
		uint8_t  RX_PW_LEN : 1;
		uint8_t  RESERVED : 2;

	} fields;
};
union nrf_reg_RX_PW_union // Represents every RX_PW register from _P0 thru _P5
{
	uint8_t value;
	struct 
	{
		uint8_t  RX_PW_LEN : 1;
		uint8_t  RESERVED : 2;

	} fields;
};
union nrf_reg_DYNPD_union
{
	uint8_t value;
	struct
	{
		uint8_t  DPL_P0 : 1;
		uint8_t  DPL_P1 : 1;
		uint8_t  DPL_P2 : 1;
		uint8_t  DPL_P3 : 1;
		uint8_t  DPL_P4 : 1;
		uint8_t  DPL_P5 : 1;
		uint8_t  RESERVED : 2;
	} fields;
};
union nrf_reg_FEATURE_union
{
	uint8_t value;
	struct
	{
		uint8_t  EN_DYN_ACK : 1;
		uint8_t  EN_ACK_PAY : 1;
		uint8_t  EN_DPL : 1;
		uint8_t  RESERVED : 5;
	} fields;
};

struct nrf_read_calls
{
	void(* Config)(NrfSpiDevice_ptr device_ptr, NrfReg_CONFIG_ptr Value, NrfReg_STATUS_ptr NrfStatus);
	void(* EnAa)(NrfSpiDevice_ptr device_ptr, NrfReg_EN_AA_ptr Value, NrfReg_STATUS_ptr NrfStatus);
	void(* EnRxAddr)(NrfSpiDevice_ptr device_ptr, NrfReg_EN_RXADDR_ptr Value, NrfReg_STATUS_ptr NrfStatus);
	void(* SetupAw)(NrfSpiDevice_ptr device_ptr, NrfReg_SETUP_AW_ptr Value, NrfReg_STATUS_ptr NrfStatus);
	void(* SetupRetr)(NrfSpiDevice_ptr device_ptr, NrfReg_SETUP_RETR_ptr Value, NrfReg_STATUS_ptr NrfStatus);
	void(* RfChannel)(NrfSpiDevice_ptr device_ptr,  NrfReg_RF_CH_ptr Value, NrfReg_STATUS_ptr NrfStatus);
	void(* RfSetup)(NrfSpiDevice_ptr device_ptr, NrfReg_RF_SETUP_ptr Value, NrfReg_STATUS_ptr NrfStatus);
	void(* Status)(NrfSpiDevice_ptr device_ptr, NrfReg_STATUS_ptr Value, NrfReg_STATUS_ptr NrfStatus);
	void(* ObserveTx)(NrfSpiDevice_ptr device_ptr, NrfReg_OBSERVE_TX_ptr Value, NrfReg_STATUS_ptr NrfStatus);
	void(* Cd)(NrfSpiDevice_ptr device_ptr, NrfReg_CD_ptr Value, NrfReg_STATUS_ptr NrfStatus);
	void(* RxAddr)(NrfSpiDevice_ptr device_ptr, NrfReg_RX_ADDR_ptr Value, NrfReg_STATUS_ptr NrfStatus);
	void(* RxPw)(NrfSpiDevice_ptr device_ptr, NrfReg_RX_PW_ptr Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
	void(* Dynpd)(NrfSpiDevice_ptr device_ptr, NrfReg_DYNPD_ptr Value, NrfReg_STATUS_ptr NrfStatus);
	void(* Feature)(NrfSpiDevice_ptr device_ptr, NrfReg_FEATURE_ptr Value, NrfReg_STATUS_ptr NrfStatus);
	void(* SingleByteRegister)(NrfSpiDevice_ptr device_ptr, uint8_t Register, uint8_t * Value, NrfReg_STATUS_ptr NrfStatus);
	void(* MultiBytesRegister)(NrfSpiDevice_ptr device_ptr, uint8_t Register, uint8_t Value[], uint8_t * BytesRead, NrfReg_STATUS_ptr NrfStatus);

};

struct nrf_write_calls
{
	void(* Config)(NrfSpiDevice_ptr device_ptr, NrfReg_CONFIG Value, NrfReg_STATUS_ptr NrfStatus);
	void(* EnAa)(NrfSpiDevice_ptr device_ptr, NrfReg_EN_AA Value, NrfReg_STATUS_ptr NrfStatus);
	void(* EnRxAddr)(NrfSpiDevice_ptr device_ptr, NrfReg_EN_RXADDR Value, NrfReg_STATUS_ptr NrfStatus);
	void(* SetupAw)(NrfSpiDevice_ptr device_ptr, NrfReg_SETUP_AW Value, NrfReg_STATUS_ptr NrfStatus);
	void(* SetupRetr)(NrfSpiDevice_ptr device_ptr, NrfReg_SETUP_RETR Value, NrfReg_STATUS_ptr NrfStatus);
	void(* Status)(NrfSpiDevice_ptr device_ptr, NrfReg_STATUS Value, NrfReg_STATUS_ptr NrfStatus);
	void(* ObserveTx)(NrfSpiDevice_ptr device_ptr, NrfReg_OBSERVE_TX Value, NrfReg_STATUS_ptr NrfStatus);
	void(* Cd)(NrfSpiDevice_ptr device_ptr, NrfReg_CD Value, NrfReg_STATUS_ptr NrfStatus);
	void(* RxAddr)(NrfSpiDevice_ptr device_ptr, NrfReg_RX_ADDR Value, NrfReg_STATUS_ptr NrfStatus);
	void(* RxPw)(NrfSpiDevice_ptr device_ptr, NrfReg_RX_PW Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
	void(* Dynpd)(NrfSpiDevice_ptr device_ptr, NrfReg_DYNPD Value, NrfReg_STATUS_ptr NrfStatus);
	void(* RfChannel)(NrfSpiDevice_ptr device_ptr, NrfReg_RF_CH Value, NrfReg_STATUS_ptr NrfStatus);
	void(* RfSetup)(NrfSpiDevice_ptr device_ptr, NrfReg_RF_SETUP Value, NrfReg_STATUS_ptr NrfStatus);
	void(* Feature)(NrfSpiDevice_ptr device_ptr, NrfReg_FEATURE Value, NrfReg_STATUS_ptr NrfStatus);
	void(* SingleByteRegister)(NrfSpiDevice_ptr device_ptr, uint8_t Register, uint8_t Value, NrfReg_STATUS_ptr NrfStatus);
	void(* MultiBytesRegister)(NrfSpiDevice_ptr device_ptr, uint8_t Register, uint8_t Value[], uint8_t * BytesWritten, NrfReg_STATUS_ptr NrfStatus);
};
struct nrf_library_calls
{
	NrfIoCallbacks_ptr ptr;
	struct nrf_read_calls GetRegister;
	struct nrf_write_calls SetRegister;
};

struct nrf_io_callbacks
{

};