typedef struct
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
} nrf24L01_registers;

static nrf24L01_registers NrfRegister =
{ 
	.CONFIG = 0x00,
	.EN_AA = 0x01,
	.EN_RXADDR = 0x02,
	.SETUP_AW = 0x03,
	.SETUP_RETR = 0x04,
	.RF_CH = 0x05,
	.RF_SETUP = 0x06,
	.STATUS = 0x07,
	.OBSERVE_TX = 0x08,
	.CD = 0x09,
	.RX_ADDR_P0 = 0x0A,
	.RX_ADDR_P1 = 0x0B,
	.RX_ADDR_P2 = 0x0C,
	.RX_ADDR_P3 = 0x0D,
	.RX_ADDR_P4 = 0x0E,
	.RX_ADDR_P5 = 0x0F,
	.TX_ADDR = 0x10,
	.RX_PW_P0 = 0x11,
	.RX_PW_P1 = 0x12,
	.RX_PW_P2 = 0x13,
	.RX_PW_P3 = 0x14,
	.RX_PW_P4 = 0x15,
	.RX_PW_P5 = 0x16,
	.FIFO_STATUS = 0x17,
	.DYNPD = 0x1C,
	.FEATURE = 0x1D,
};

typedef struct 
{
	SPI_HandleTypeDef * spi_ptr;
	GPIO_TypeDef * gpio_ptr;
	HAL_StatusTypeDef status;
	uint8_t cs_pin;
	uint8_t ce_pin;
	
} NrfSpi;

typedef struct 
{
	unsigned int TX_FULL : 1;
	unsigned int RX_P_NO : 3;
	unsigned int MAX_RT : 1;
	unsigned int TX_DS : 1;
	unsigned int RX_DR : 1;
	unsigned int RESERVED : 1;

} STATUS;

typedef struct 
{
	unsigned int PRIM_RX : 1;
	unsigned int PWR_UP : 1;
	unsigned int CRCO : 1;
	unsigned int EN_CRC : 1;
	unsigned int MASK_MAX_RT : 1;
	unsigned int MASK_TX_DS : 1;
	unsigned int MASK_RX_DR : 1;
	unsigned int RESERVED : 1;

} CONFIG;

typedef struct 
{
	unsigned int ENAA_P0 : 1;
	unsigned int ENAA_P1 : 1;
	unsigned int ENAA_P2 : 1;
	unsigned int ENAA_P3 : 1;
	unsigned int ENAA_P4 : 1;
	unsigned int ENAA_P5 : 1;
	unsigned int RESERVED : 2;

} EN_AA;

typedef struct 
{
	unsigned int ERX_P0 : 1;
	unsigned int ERX_P1 : 1;
	unsigned int ERX_P2 : 1;
	unsigned int ERX_P3 : 1;
	unsigned int ERX_P4 : 1;
	unsigned int ERX_P5 : 1;
	unsigned int RESERVED : 2;

} EN_RXADDR;