NrfHalFunctions AppFunctions =
{
	.init_spi = init_spi,
	.init_control_pins = init_control_pins,
	.spi_ce_lo = spi_ce_lo,
	.spi_ce_hi = spi_ce_hi,
	.spi_cs_lo = spi_cs_lo,
	.spi_cs_hi = spi_cs_hi,
	.exchange_bytes = exchange_bytes,
	.read_bytes = read_bytes,
	.write_bytes = write_bytes
};
