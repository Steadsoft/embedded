
// SEE: https://datasheetspdf.com/pdf-file/906332/Nordic/nRF24L01+/1
// SEE: https://www.edwinfairchild.com/2020/06/nrf24l01-driver-intro_18.html
// SEE: https://infocenter.nordicsemi.com/pdf/nan_24-08.pdf?cp=13_10
// SEE: https://github.com/mokhwasomssi/stm32_hal_nrf24l01p

/*
 * This is how we update a resgister at the bit level.
 * We pass two instances of the register struct, the first is the
 * bit values we want to the register's bits set to and the 
 * second is a mask that describes which bits in the register are to be 
 * modified.
 * 
 * REG = 1101
 * NEW = 0000
 * MSK = 0100
 * END = 1001 
 *
 *
 * REG = 1001
 * NEW = 0010
 * MSK = 0010
 * END = 1011 
 * 
 *	M R N E
	0 1 0 1
	0 1 1 1
	1 0 1 1
	1 1 1 1
	0 0 0 0
	0 0 1 0
	1 0 0 0
	1 1 0 0
 
 E = (!M & R & !N) | (!M & R & N) | (M & !R & N) | (M & R & N)
 
 
 **/