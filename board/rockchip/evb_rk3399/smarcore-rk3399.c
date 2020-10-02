/*
 * (C) Copyright 2020 Engicam srl - http://www.engicam.com
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <syscon.h>
#include <asm/io.h>
#include <asm/arch/grf_rk3399.h>
#include <asm/arch/clock.h>
#include <asm/arch/hardware.h>


static void setup_iodomain(void)
{
	const u32 GRF_IO_VSEL_GPIO4CD_SHIFT = 3;
	struct rk3399_grf_regs *grf =
	    syscon_get_first_range(ROCKCHIP_SYSCON_GRF);

	/*
	 * Set bit 3 in GRF_IO_VSEL to have APIO4 working (debug UART2 is ).
	 */
	rk_setreg(&grf->io_vsel, 1 << GRF_IO_VSEL_GPIO4CD_SHIFT);
}

/*
	Smarcore RK3399: APIO4 18V powered
*/
int board_early_init_r(void)
{
	setup_iodomain();

	return 0;
}
