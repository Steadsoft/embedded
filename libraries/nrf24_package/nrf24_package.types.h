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
	uint8_t RPD;
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
struct nrf_commands
{
	uint8_t R_REGISTER;
	uint8_t W_REGISTER;
	uint8_t R_RX_PAYLOAD;
	uint8_t W_TX_PAYLOAD;
	uint8_t FLUSH_TX;
	uint8_t FLUSH_RX;
	uint8_t REUSE_TX_PL;
	uint8_t R_RX_PL_WID;
	uint8_t W_ACK_PAYLOAD;
	uint8_t W_TX_PAYLOAD_NOACK;
	uint8_t NOP;
};

// Create (in effect) a "namespace" for containing all of the register names.

// This type represents all of the hardware specific items needed by the library.


// Register structures

struct test_struct
{
	uint8_t PRIM_RX : 1; // 1 = receiver, 0 = transmitter

};


struct NrfReg_CONFIG_struct
{
	uint8_t PRIM_RX : 1;		// 1 = receiver, 0 = transmitter
	uint8_t PWR_UP : 1;			// 1 = powerup, 0 = powerdown
	uint8_t CRCO : 1;			// 1 = 2 byte scheme, 0 = 1 byte scheme.
	uint8_t EN_CRC : 1;			// 1 = enable CRC, 0 = disable CRC
	uint8_t MASK_MAX_RT : 1;	// Enables/Disables whether the MAX_RT interrupt drives the IRQ pin
	uint8_t MASK_TX_DS : 1;		// Enables/Disables whether the TX_DS interrupt drives the IRQ pin
	uint8_t MASK_RX_DR : 1;		// Enables/Disables whether the RX_DR interrupt drives the IRQ pin
	uint8_t RESERVED : 1;

};
struct NrfReg_EN_AA_struct
{
	// These bits are used to enable auto acknowledge on the given pipe number. 
	uint8_t ENAA_P0 : 1;
	uint8_t ENAA_P1 : 1;
	uint8_t ENAA_P2 : 1;
	uint8_t ENAA_P3 : 1;
	uint8_t ENAA_P4 : 1;
	uint8_t ENAA_P5 : 1;
	uint8_t RESERVED : 2;

};
struct NrfReg_EN_RXADDR_struct
{
	// This bits are used to enable a given pipe number.
	uint8_t ERX_P0 : 1;
	uint8_t ERX_P1 : 1;
	uint8_t ERX_P2 : 1;
	uint8_t ERX_P3 : 1;
	uint8_t ERX_P4 : 1;
	uint8_t ERX_P5 : 1;
	uint8_t RESERVED : 2;

};

/*																			
This register only uses 2bits to set the width of the pipe addresses.  
The values allowed are as follow:

00 - Illegal
01 - 3 bytes
10 - 4 bytes
11 - 5 bytes

Remember that the address is transmitted every time you send a packet so having less bytes
to transmit can be beneficial in some applications but the robustness of having more bytes 
may be useful in other applications.
*/
struct	NrfReg_SETUP_AW_struct
{
	uint8_t AW : 2;
	uint8_t RESERVED : 6;

};

/*
0-3 : ARC : These bits are used to set how many times the transmitter will re-transmit when 
it fails to receive an auto ACK from the receiver.  

Acceptable values are:

0000 - re-transmit disabled
0001 - 1 re-transmit
0010 - 2 re-transmit
........ etc .......
1111 - 15 re-transmit


4-7 : ARD :  These bits are used to assign a designated waiting period before each re-transmission.

Acceptable values are:

0000 - Wait 250 uS
0001 - Wait 500 uS
0010 - Wait 750 uS
........ etc .......
1111 - Wait 4000 uS
*/

struct NrfReg_SETUP_RETR_struct
{
	uint8_t ARC : 4;
	uint8_t ARD : 4;
};

/*
 This register uses bits 0 through 6 to set the channel frequency where your NRF will transmit 
 and receive its data. Needless to say that both transmitter and receiver need to be on the 
 same frequency. Also needless to say you get 126 RF channels to chose from. 
 000000 is not acceptable, hence why you dont have 127. 
*/
struct	NrfReg_RF_CH_struct
{
	uint8_t RF_CH : 7;
	uint8_t RESERVED : 1;
};

struct NrfReg_RF_SETUP_struct
{
	uint8_t  OBSOLETE : 1;
	uint8_t  RF_PWR : 2;
	uint8_t  RF_DR_HIGH : 1;
	uint8_t  PLL_LOCK : 1;
	uint8_t  RF_DR_LOW : 1;
	uint8_t  RESERVED : 1;
	uint8_t  CONT_WAVE : 1;
};

/*
 0 : TX_FULL : When this bit is set it means the TX FIFO is full and you must either read 
 some data or  risk it being lost as it pushes out the oldest data to fill it with new 
 incoming data

1-3: RX_P_NO : Tells you on what Pipe there is the current data available to read.

4 : MAX_RT : This is an interrupt that signals when the maximum number of re-transmits has been
             reached. Write a 1 to clear this bit
5 : TX_DS  : Interrupt that signals when the data packet has been transmitted. If auto ACK is                  
             enabled his interrupt will only trigger when the ACK is received. Write 1 to clear

6 : RX_DR  : This interrupt signals that new data has arrived to be read from the FIFO. 
             Write 1 to clear it.

Like stated in the CONFIG register description, these interrupts can drive the IRQ pin low 
when the flags are set. And like most status registers the interrupts are cleared by writing 
a 1 to the bit. 
 */
struct NrfReg_STATUS_struct
{
	uint8_t  TX_FULL : 1;
	uint8_t  RX_P_NO : 3;
	uint8_t  MAX_RT : 1; // Interrupt flag, write a 1 to clear
	uint8_t  TX_DS : 1;  // Interrupt flag, write a 1 to clear
	uint8_t  RX_DR : 1;  // Interrupt flag, write a 1 to clear
	uint8_t  RESERVED : 1;
};

/*
 0-3 : ARC_CNT : These bits tell current count of re-transmit

4-7 : PLOS_CNT : These bits keep track of how many packets have been lost after the max re-transmit

When ARC_CNT exceeds the max number of re-transmits set in the SETUP_RETR register it triggers 
the MAX_RT interrupt , which in turn may or may not trigger the IRQ pin to go low depending on 
your settings.
 */
struct NrfReg_OBSERVE_TX_struct
{
	uint8_t  ARC_CNT : 4;
	uint8_t  PLOS_CNT : 4;

};
/*
The RPD register has only one readable bit that signals power levels above -64dBm present in 
the RF channel you are using. Otherwise it reads 0.
*/
struct NrfReg_RPD_struct
{
	uint8_t  RPD : 1;
	uint8_t  RESERVED : 7;
};

struct NrfReg_RX_ADDR_LONG_struct // Represents the two long RX_ADDR registers from _P0 thru _P1
{
	uint8_t value[5];
};

struct NrfReg_RX_ADDR_SHORT_struct // Represents every RX_ADDR short register from _P2 thru _P5
{
	uint8_t value;
};
struct NrfReg_TX_ADDR_LONG_struct
{
	uint8_t value[5];
};

struct NrfReg_RX_PW_struct
{
	uint8_t  RX_PW_LEN : 6;
	uint8_t  RESERVED : 2;

};

struct NrfReg_FIFO_STATUS_struct
{
	uint8_t RX_EMPTY : 1;
	uint8_t RX_FULL : 1;
	uint8_t RESERVED0 : 2;
	uint8_t TX_EMPTY : 1;
	uint8_t TX_FULL : 1;
	uint8_t TX_REUSE : 1;
	uint8_t RESERVED1 : 1;

};
struct NrfReg_DYNPD_struct
{
	uint8_t  DPL_P0 : 1;
	uint8_t  DPL_P1 : 1;
	uint8_t  DPL_P2 : 1;
	uint8_t  DPL_P3 : 1;
	uint8_t  DPL_P4 : 1;
	uint8_t  DPL_P5 : 1;
	uint8_t  RESERVED : 2;
};
struct NrfReg_FEATURE_struct
{
	uint8_t  EN_DYN_ACK : 1;
	uint8_t  EN_ACK_PAY : 1;
	uint8_t  EN_DPL : 1;
	uint8_t  RESERVED : 5;
};

struct NrfReg_ALL_REGISTERS_struct
{
	NrfReg_CONFIG CONFIG;
	NrfReg_EN_AA  EN_AA;
	NrfReg_EN_RXADDR EN_RXADDR;
	NrfReg_SETUP_AW SETUP_AW;
	NrfReg_SETUP_RETR SETUP_RETR;
	NrfReg_RF_CH RF_CH;
	NrfReg_RF_SETUP RF_SETUP;
	NrfReg_STATUS STATUS;
	NrfReg_OBSERVE_TX OBSERVE_TX;
	NrfReg_RPD RPD;
	NrfReg_RX_ADDR_LONG RX_ADDR_P0;
	NrfReg_RX_ADDR_LONG RX_ADDR_P1;
	NrfReg_RX_ADDR_SHORT RX_ADDR_P2;
	NrfReg_RX_ADDR_SHORT RX_ADDR_P3;
	NrfReg_RX_ADDR_SHORT RX_ADDR_P4;
	NrfReg_RX_ADDR_SHORT RX_ADDR_P5;
	NrfReg_TX_ADDR_LONG  TX_ADDR;
	NrfReg_RX_PW RX_PW_P0;
	NrfReg_RX_PW RX_PW_P1;
	NrfReg_RX_PW RX_PW_P2;
	NrfReg_RX_PW RX_PW_P3;
	NrfReg_RX_PW RX_PW_P4;
	NrfReg_RX_PW RX_PW_P5;
	NrfReg_FIFO_STATUS FIFO_STATUS;
	NrfReg_DYNPD DYNPD;
	NrfReg_FEATURE FEATURE;
	
};
struct nrf_write_interface
{
	void(* CONFIG)(NrfDevice_ptr device_ptr, NrfReg_CONFIG Value, NrfReg_STATUS_ptr NrfStatus);
	void(* EN_AA)(NrfDevice_ptr device_ptr, NrfReg_EN_AA Value, NrfReg_STATUS_ptr NrfStatus);
	void(* EN_RXADDR)(NrfDevice_ptr device_ptr, NrfReg_EN_RXADDR Value, NrfReg_STATUS_ptr NrfStatus);
	void(* SETUP_AW)(NrfDevice_ptr device_ptr, NrfReg_SETUP_AW Value, NrfReg_STATUS_ptr NrfStatus);
	void(* SETUP_RETR)(NrfDevice_ptr device_ptr, NrfReg_SETUP_RETR Value, NrfReg_STATUS_ptr NrfStatus);
	void(* RF_CH)(NrfDevice_ptr device_ptr,  NrfReg_RF_CH Value, NrfReg_STATUS_ptr NrfStatus);
	void(* RF_SETUP)(NrfDevice_ptr device_ptr, NrfReg_RF_SETUP Value, NrfReg_STATUS_ptr NrfStatus);
	void(* STATUS)(NrfDevice_ptr device_ptr, NrfReg_STATUS Value, NrfReg_STATUS_ptr NrfStatus);
	void(* OBSERVE_TX)(NrfDevice_ptr device_ptr, NrfReg_OBSERVE_TX Value, NrfReg_STATUS_ptr NrfStatus);
	void(* RPD)(NrfDevice_ptr device_ptr, NrfReg_RPD Value, NrfReg_STATUS_ptr NrfStatus);
	void(* RX_ADDR_LONG)(NrfDevice_ptr device_ptr, NrfReg_RX_ADDR_LONG Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
	void(* RX_ADDR_SHORT)(NrfDevice_ptr device_ptr, NrfReg_RX_ADDR_SHORT Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
	void(* TX_ADDR_LONG)(NrfDevice_ptr device_ptr, NrfReg_TX_ADDR_LONG Value, NrfReg_STATUS_ptr NrfStatus);
	void(* RX_PW)(NrfDevice_ptr device_ptr, NrfReg_RX_PW Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
	void(* FIFO_STATUS)(NrfDevice_ptr device_ptr, NrfReg_FIFO_STATUS Value, NrfReg_STATUS_ptr NrfStatus);
	void(* DYNPD)(NrfDevice_ptr device_ptr, NrfReg_DYNPD Value, NrfReg_STATUS_ptr NrfStatus);
	void(* FEATURE)(NrfDevice_ptr device_ptr, NrfReg_FEATURE Value, NrfReg_STATUS_ptr NrfStatus);
//	void(* SingleByteRegister)(NrfSpiDevice_ptr device_ptr, uint8_t Register, uint8_t * Value, NrfReg_STATUS_ptr NrfStatus);
//	void(* MultiBytesRegister)(NrfSpiDevice_ptr device_ptr, uint8_t Register, uint8_t Value[], uint8_t * BytesRead, NrfReg_STATUS_ptr NrfStatus);

};
struct nrf_read_interface
{
	void(* CONFIG)(NrfDevice_ptr device_ptr, NrfReg_CONFIG_ptr Value, NrfReg_STATUS_ptr NrfStatus);
	void(* EN_AA)(NrfDevice_ptr device_ptr, NrfReg_EN_AA_ptr Value, NrfReg_STATUS_ptr NrfStatus);
	void(* EN_RXADDR)(NrfDevice_ptr device_ptr, NrfReg_EN_RXADDR_ptr Value, NrfReg_STATUS_ptr NrfStatus);
	void(* SETUP_AW)(NrfDevice_ptr device_ptr, NrfReg_SETUP_AW_ptr Value, NrfReg_STATUS_ptr NrfStatus);
	void(* SETUP_RETR)(NrfDevice_ptr device_ptr, NrfReg_SETUP_RETR_ptr Value, NrfReg_STATUS_ptr NrfStatus);
	void(* RF_CH)(NrfDevice_ptr device_ptr, NrfReg_RF_CH_ptr Value, NrfReg_STATUS_ptr NrfStatus);
	void(* RF_SETUP)(NrfDevice_ptr device_ptr, NrfReg_RF_SETUP_ptr Value, NrfReg_STATUS_ptr NrfStatus);
	void(* STATUS)(NrfDevice_ptr device_ptr, NrfReg_STATUS_ptr Value);
	void(* OBSERVE_TX)(NrfDevice_ptr device_ptr, NrfReg_OBSERVE_TX_ptr Value, NrfReg_STATUS_ptr NrfStatus);
	void(* RPD)(NrfDevice_ptr device_ptr, NrfReg_RPD_ptr Value, NrfReg_STATUS_ptr NrfStatus);
	void(* RX_ADDR_LONG)(NrfDevice_ptr device_ptr, NrfReg_RX_ADDR_LONG_ptr Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
	void(* RX_ADDR_SHORT)(NrfDevice_ptr device_ptr, NrfReg_RX_ADDR_SHORT_ptr Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
	void(* TX_ADDR_LONG)(NrfDevice_ptr device_ptr, NrfReg_TX_ADDR_LONG_ptr Value, NrfReg_STATUS_ptr NrfStatus);
	void(* RX_PW)(NrfDevice_ptr device_ptr, NrfReg_RX_PW_ptr Value, uint8_t Pipe, NrfReg_STATUS_ptr NrfStatus);
	void(* FIFO_STATUS)(NrfDevice_ptr device_ptr, NrfReg_FIFO_STATUS_ptr Value, NrfReg_STATUS_ptr NrfStatus);
	void(* DYNPD)(NrfDevice_ptr device_ptr, NrfReg_DYNPD_ptr Value, NrfReg_STATUS_ptr NrfStatus);
	void(* FEATURE)(NrfDevice_ptr device_ptr, NrfReg_FEATURE_ptr Value, NrfReg_STATUS_ptr NrfStatus);
	void(* ALL_REGISTERS)(NrfDevice_ptr device_ptr, NrfReg_ALL_REGISTERS_ptr Value, NrfReg_STATUS_ptr NrfStatus);
};

struct nrf_update_interface
{
	void (* CONFIG)(NrfDevice_ptr device_ptr, NrfReg_CONFIG Value, NrfReg_CONFIG Mask, NrfReg_STATUS_ptr NrfStatus);
	void (* EN_AA)(NrfDevice_ptr device_ptr, NrfReg_EN_AA Value, NrfReg_EN_AA Mask, NrfReg_STATUS_ptr NrfStatus);
	void (* EN_RXADDR)(NrfDevice_ptr device_ptr, NrfReg_EN_RXADDR Value, NrfReg_EN_RXADDR Mask, NrfReg_STATUS_ptr NrfStatus);
	void (* SETUP_AW)(NrfDevice_ptr device_ptr, NrfReg_SETUP_AW Value, NrfReg_SETUP_AW Mask, NrfReg_STATUS_ptr NrfStatus);
	void (* SETUP_RETR)(NrfDevice_ptr device_ptr, NrfReg_SETUP_RETR Value, NrfReg_SETUP_RETR Mask, NrfReg_STATUS_ptr NrfStatus);
	void (* RF_CH)(NrfDevice_ptr device_ptr, NrfReg_RF_CH Value, NrfReg_RF_CH Mask, NrfReg_STATUS_ptr NrfStatus);
	void (* RF_SETUP)(NrfDevice_ptr device_ptr, NrfReg_RF_SETUP Value, NrfReg_RF_SETUP Mask, NrfReg_STATUS_ptr NrfStatus);
	void (* STATUS)(NrfDevice_ptr device_ptr, NrfReg_STATUS Value, NrfReg_STATUS Mask);
	void (* OBSERVE_TX)(NrfDevice_ptr device_ptr, NrfReg_OBSERVE_TX Value, NrfReg_OBSERVE_TX Mask, NrfReg_STATUS_ptr NrfStatus);
	void (* RPD)(NrfDevice_ptr device_ptr, NrfReg_RPD Value, NrfReg_RPD Mask, NrfReg_STATUS_ptr NrfStatus);
	void (* FIFO_STATUS)(NrfDevice_ptr device_ptr, NrfReg_FIFO_STATUS Value, NrfReg_FIFO_STATUS Mask, NrfReg_STATUS_ptr NrfStatus);
	void (* DYNPD)(NrfDevice_ptr device_ptr, NrfReg_DYNPD Value, NrfReg_DYNPD Mask, NrfReg_STATUS_ptr NrfStatus);
	void (* FEATURE)(NrfDevice_ptr device_ptr, NrfReg_FEATURE Value, NrfReg_FEATURE Mask, NrfReg_STATUS_ptr NrfStatus);
};

// these are abstract composite operations
struct nrf_action_interface
{
	void(* ResetDevice)(NrfDevice_ptr); // Sets all device registers to the same values they have after powering off/on.
	/*
	 * @brief Initializes the NRF registers prior to setting up TX or RX operation.
	 * @param device_ptr Pointer to the configured NRF device structure that contains the SPI and GPIO control structures.
	 * 
	 */
	void(* ConfigureTransmitter)(NrfDevice_ptr device_ptr, bool auto_ack);
	void(* ConfigureReceiver)(NrfDevice_ptr device_ptr, uint8_t address[5], uint8_t pipe, bool auto_ack,  uint8_t payload_sizee);
	void(* ConfigureRadio)(NrfDevice_ptr device_ptr, uint8_t channel, uint8_t power, uint8_t rate, bool auto_ack);
	void(* PowerDown)(NrfDevice_ptr);
	void(* PowerUpDevice)(NrfDevice_ptr);
	void(* PulseCE)(NrfDevice_ptr device_ptr);
	void(* SendPayload)(NrfDevice_ptr device_ptr,  uint8_t * buffer, uint8_t size);
	void(* WaitForInterrupt)(NrfInterrupt_ptr rx_interrupt, int32_t max_spins);
	void(* ConfirmTxInterrupt)(NrfDevice_ptr device_ptr);
	void(* ConfirmRxInterrupt)(NrfInterrupt_ptr device_ptr);
	void(* GetDefaultAddress)(uint8_t address[5]);
	void(* DumpRegisters)(NrfDevice_ptr device_ptr);
	void(* SetTransmitAddress)(NrfDevice_ptr device_ptr, uint8_t address[5]);
	void(* SetReceiveAddressLong)(NrfDevice_ptr device_ptr, uint8_t address[5], uint8_t pipe); // pipes 0 and 1
	void(* SetReceiveAddressShort)(NrfDevice_ptr device_ptr, uint8_t address, uint8_t pipe); // pipes 2,3,4 and 5
	void(* SetAutoAck)(NrfDevice_ptr device_ptr, uint8_t pipe, bool state);
	void(* SetPipeState)(NrfDevice_ptr device_ptr, uint8_t pipe, bool state);
	void(* ClearInterruptFlags)(NrfDevice_ptr device_ptr, bool RX_DR, bool TX_DS, bool MAX_RT);
	void(* SetReceiveMode)(NrfDevice_ptr device_ptr);
	void(* SetTransmitMode)(NrfDevice_ptr device_ptr);
	void(* MaskInterrupts)(NrfDevice_ptr device_ptr, bool RX_DR, bool TX_DS, bool MAX_RT);
	void(* SetReceivePayloadSize)(NrfDevice_ptr device_ptr, uint8_t payload_size, uint8_t pipe);
	void(* SetCRC)(NrfDevice_ptr device_ptr, bool enable, bool size);
	void(* SetAutoAckRetries)(NrfDevice_ptr device_ptr, uint8_t delay, uint8_t max);
	void(* SetAddressWidth)(NrfDevice_ptr device_ptr, uint8_t width);
	void(* SetDynamicPayloads)(NrfDevice_ptr device_ptr, bool state);
	void(* SetDynamicPipe)(NrfDevice_ptr device_ptr, uint8_t pipe, bool state);

};

// These represent the documented commands
struct nrf_command_interface
{
	void(* FLUSH_TX)(NrfDevice_ptr, NrfReg_STATUS_ptr NrfStatus);
	void(* FLUSH_RX)(NrfDevice_ptr, NrfReg_STATUS_ptr NrfStatus);
	void(* W_TX_PAYLOAD)(NrfDevice_ptr, uint8_t * data_ptr, uint8_t data_len, NrfReg_STATUS_ptr NrfStatus);
	void(* R_RX_PAYLOAD)(NrfDevice_ptr, uint8_t * data_ptr, uint8_t data_len, NrfReg_STATUS_ptr NrfStatus);
	void(* R_RX_PL_WID)(NrfDevice_ptr, uint8_t * data_len, NrfReg_STATUS_ptr NrfStatus);

	//void(* ReadRxPayload)(NrfDevice_ptr, NrfReg_STATUS_ptr NrfStatus);
};

struct nrf_empty
{
	
	const NrfReg_STATUS STATUS;
};
struct nrf24_package_interface
{
	NrfIoCallbacks_ptr ptr;
	struct nrf_write_interface Write;
	struct nrf_read_interface Read;
	struct nrf_update_interface Update;
	struct nrf_action_interface Action;
	struct nrf_command_interface Command;
	struct nrf_empty EmptyRegister;
};
struct nrf_io_callbacks
{

};