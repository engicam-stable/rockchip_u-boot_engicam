/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <dm.h>
#include <misc.h>
#include <usb.h>
#include <dwc3-uboot.h>
#include <spl.h>
#include <u-boot/sha256.h>
#include <power/regulator.h>
#include <dm/pinctrl.h>
#include <dm/uclass-internal.h>
#include <asm/io.h>
#include <asm/gpio.h>
#include <asm/setup.h>
#include <asm/arch/periph.h>
#include <asm/arch/grf_px30.h>
 
DECLARE_GLOBAL_DATA_PTR;
#define PMUGRF_GPIO0B_IOMUX_ADDR		0xFF010004
#define GRF_IO_VSEL_ADDR                0xFF140180 
#define EMMC_nEN_GPIO (8 + 6) /* GPIO0 RK_PB6 */

int rk_board_init(void)
{
    unsigned long *pmugrf;
    unsigned long *grf_vsel;
    unsigned int sys_reg;
    
    pmugrf = (void *)PMUGRF_GPIO0B_IOMUX_ADDR;
    sys_reg = 0x10000000;
    writel(sys_reg, pmugrf); 

    grf_vsel = (void *)GRF_IO_VSEL_ADDR;
    sys_reg = 0x00030003;
    writel(sys_reg, grf_vsel); 


    gpio_request(EMMC_nEN_GPIO, "emmc enabled");
    gpio_direction_output(EMMC_nEN_GPIO, 0);


    return 0;
}
 

