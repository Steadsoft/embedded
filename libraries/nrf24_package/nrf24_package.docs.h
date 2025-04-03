
// SEE: https://datasheetspdf.com/pdf-file/906332/Nordic/nRF24L01+/1
// SEE: https://www.edwinfairchild.com/2020/06/nrf24l01-driver-intro_18.html
// SEE: https://infocenter.nordicsemi.com/pdf/nan_24-08.pdf?cp=13_10
// SEE: https://github.com/mokhwasomssi/stm32_hal_nrf24l01p

// SEE: https://github.com/MaJerle/stm32f429/blob/4d32c1971b3049a92158dfef316b682357d1ab21/00-STM32F429_LIBRARIES/tm_stm32f4_nrf24l01.c

// Register can be read, written and updated. The update support enables 
// us to adjus the value of selected fields within a register while 
// leaving others unchanged. 
// This is done by use of an update "mask" any bit set in a mask indicates that
// that bit is to be changed but any bit unset in a mask means to leave that
// bit unchanged.

// Caution must be exercised if updating fields that are composed of multiple
// bits, make sure you set the mask to either all zeros or all ones in
// this case.