typedef const struct nrf24_hal_support_interface nrf24_hal_support_struct, * nrf_hal_support_ptr;
typedef struct nrf_register_calls NrfRegisterCalls, * NrfRegisterCalls_ptr;
typedef struct nrf_io_interface NrfIoInterface, * NrfIoInterface_ptr;
typedef struct nrf_io_callbacks NrfIoCallbacks, * NrfIoCallbacks_ptr;
typedef struct nrf_device NrfDevice, * NrfDevice_ptr;
typedef struct nrf_spi_setup NrfSpiSetup, * NrfSpiSetup_ptr;
typedef enum nrf_error_code NrfErrorCode;
typedef void(*nrf_fault_handler)(NrfDevice_ptr device_ptr, NrfErrorCode code);
typedef struct nrf_interrupt NrfInterrupt, * NrfInterrupt_ptr;

#if defined(nrf24_hal_support_implementer)
// Private typedefs can go here, these will never been seen by consumer code when compiled.
#endif