typedef const struct nrf24_hal_support_interface nrf24_hal_support_struct, * nrf_hal_support_ptr;
typedef struct nrf_register_calls NrfRegisterCalls, * NrfRegisterCalls_ptr;
typedef struct nrf_io_interface NrfIoInterface, * NrfIoInterface_ptr;
typedef struct nrf_io_callbacks NrfIoCallbacks, * NrfIoCallbacks_ptr;
typedef struct nrf_spi_device NrfSpiDevice, * NrfSpiDevice_ptr;
typedef enum nrf_error_code NrfErrorCode;
typedef void(*nrf_fault_handler)(NrfSpiDevice_ptr device_ptr, NrfErrorCode code);

#if defined(nrf24_hal_support_implementer)
// Private typedefs can go here, these will never been seen by consumer code when compiled.
#endif