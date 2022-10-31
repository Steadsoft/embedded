
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

// This is the structure of the nRF24L01's STATUS register.
struct nrf_reg_status
{
	unsigned int TX_FULL : 1;
	unsigned int RX_P_NO : 3;
	unsigned int MAX_RT : 1;
	unsigned int TX_DS : 1;
	unsigned int RX_DR : 1;
	unsigned int RESERVED : 1;

} ;

// This is the structure of the nRF24L01's CONFIG register.
struct nrf_reg_config
{
	unsigned int PRIM_RX : 1;
	unsigned int PWR_UP : 1;
	unsigned int CRCO : 1;
	unsigned int EN_CRC : 1;
	unsigned int MASK_MAX_RT : 1;
	unsigned int MASK_TX_DS : 1;
	unsigned int MASK_RX_DR : 1;
	unsigned int RESERVED : 1;

};

// This is the structure of the nRF24L01's EN_AA register.
struct nrf_reg_EN_AA
{
	unsigned int ENAA_P0 : 1;
	unsigned int ENAA_P1 : 1;
	unsigned int ENAA_P2 : 1;
	unsigned int ENAA_P3 : 1;
	unsigned int ENAA_P4 : 1;
	unsigned int ENAA_P5 : 1;
	unsigned int RESERVED : 2;

};

// This is the structure of the nRF24L01's EN_RXADDR register.
struct nrf_reg_EN_RXADDR
{
	unsigned int ERX_P0 : 1;
	unsigned int ERX_P1 : 1;
	unsigned int ERX_P2 : 1;
	unsigned int ERX_P3 : 1;
	unsigned int ERX_P4 : 1;
	unsigned int ERX_P5 : 1;
	unsigned int RESERVED : 2;

};
struct nrf_read_calls
{
	void(* SingleByteRegister)(NrfSpiDevice_ptr device_ptr, uint8_t Register, uint8_t * Value, NrfReg_STATUS_ptr NrfStatus);
	void(* MultiBytesRegister)(NrfSpiDevice_ptr device_ptr, uint8_t Register, uint8_t Value[], uint8_t * BytesRead, NrfReg_STATUS_ptr NrfStatus);
};

struct nrf_write_calls
{
	void(* SingleByteRegister)(NrfSpiDevice_ptr device_ptr, uint8_t Register, uint8_t Value, NrfReg_STATUS_ptr NrfStatus);
	void(* MultiBytesRegister)(NrfSpiDevice_ptr device_ptr, uint8_t Register, uint8_t Value[], uint8_t * BytesWritten, NrfReg_STATUS_ptr NrfStatus);
};
struct nrf_library_calls
{
	NrfIoCallbacks_ptr ptr;
	struct nrf_read_calls Read;
	struct nrf_write_calls Write;
};

struct nrf_io_callbacks
{

};