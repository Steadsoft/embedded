// Declare and initialize the global pointer to perhipher register sets

typedef const struct bus_control_struct Bus, *Bus_ptr;

struct bus_control_struct
{
	AHB1_Bus_ptr	ahb1_ptr;
	APB1_Bus_ptr	apb1_ptr;
	SYST_Regset_ptr	syst_ptr;
	SCB_Regset_ptr 	scb_ptr;
};

Bus bus =
{ 
	.ahb1_ptr = (AHB1_Bus_ptr)(0x40020000),	
	.apb1_ptr = (APB1_Bus_ptr)(0x40000000),
	.syst_ptr = (SYST_Regset_ptr)(0xE000E010),
    .scb_ptr  = (SCB_Regset_ptr)(0xE000ED00)
};

//AHB1_Bus_ptr	ahb1_ptr = (AHB1_Bus_ptr)(0x40020000);
//APB1_Bus_ptr	apb1_ptr = (APB1_Bus_ptr)(0x40000000);
//SYST_Regset_ptr	syst_ptr = (SYST_Regset_ptr)(0xE000E010);
//SCB_Regset_ptr 	scb_ptr  = (SCB_Regset_ptr)(0xE000ED00);
