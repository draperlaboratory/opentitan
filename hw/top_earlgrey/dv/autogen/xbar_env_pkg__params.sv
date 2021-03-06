// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
// xbar_env_pkg__params generated by `topgen.py` tool


// List of Xbar device memory map
tl_device_t xbar_devices[$] = '{
    '{"rom", '{
        '{32'h00008000, 32'h0000bfff}
    }},
    '{"debug_mem", '{
        '{32'h1a110000, 32'h1a110fff}
    }},
    '{"ram_main", '{
        '{32'h10000000, 32'h1001ffff}
    }},
    '{"eflash", '{
        '{32'h20000000, 32'h200fffff}
    }},
    '{"flash_ctrl", '{
        '{32'h41000000, 32'h41000fff}
    }},
    '{"hmac", '{
        '{32'h41110000, 32'h41110fff}
    }},
    '{"kmac", '{
        '{32'h41120000, 32'h41120fff}
    }},
    '{"aes", '{
        '{32'h41100000, 32'h41100fff}
    }},
    '{"entropy_src", '{
        '{32'h41160000, 32'h41160fff}
    }},
    '{"csrng", '{
        '{32'h41150000, 32'h41150fff}
    }},
    '{"edn0", '{
        '{32'h41170000, 32'h41170fff}
    }},
    '{"edn1", '{
        '{32'h41180000, 32'h41180fff}
    }},
    '{"rv_plic", '{
        '{32'h41010000, 32'h41010fff}
    }},
    '{"otbn", '{
        '{32'h411d0000, 32'h411dffff}
    }},
    '{"keymgr", '{
        '{32'h41130000, 32'h41130fff}
    }},
    '{"sram_ctrl_main", '{
        '{32'h411c0000, 32'h411c0fff}
    }},
    '{"uart0", '{
        '{32'h40000000, 32'h40000fff}
    }},
    '{"uart1", '{
        '{32'h40010000, 32'h40010fff}
    }},
    '{"uart2", '{
        '{32'h40020000, 32'h40020fff}
    }},
    '{"uart3", '{
        '{32'h40030000, 32'h40030fff}
    }},
    '{"i2c0", '{
        '{32'h40080000, 32'h40080fff}
    }},
    '{"i2c1", '{
        '{32'h40090000, 32'h40090fff}
    }},
    '{"i2c2", '{
        '{32'h400a0000, 32'h400a0fff}
    }},
    '{"pattgen", '{
        '{32'h400e0000, 32'h400e0fff}
    }},
    '{"gpio", '{
        '{32'h40040000, 32'h40040fff}
    }},
    '{"spi_device", '{
        '{32'h40050000, 32'h40051fff}
    }},
    '{"rv_timer", '{
        '{32'h40100000, 32'h40100fff}
    }},
    '{"usbdev", '{
        '{32'h40110000, 32'h40110fff}
    }},
    '{"pwrmgr_aon", '{
        '{32'h40400000, 32'h40400fff}
    }},
    '{"rstmgr_aon", '{
        '{32'h40410000, 32'h40410fff}
    }},
    '{"clkmgr_aon", '{
        '{32'h40420000, 32'h40420fff}
    }},
    '{"pinmux_aon", '{
        '{32'h40460000, 32'h40460fff}
    }},
    '{"padctrl_aon", '{
        '{32'h40470000, 32'h40470fff}
    }},
    '{"ram_ret_aon", '{
        '{32'h40520000, 32'h40520fff}
    }},
    '{"otp_ctrl", '{
        '{32'h40130000, 32'h40133fff}
    }},
    '{"lc_ctrl", '{
        '{32'h40140000, 32'h40140fff}
    }},
    '{"sensor_ctrl_aon", '{
        '{32'h40500000, 32'h40500fff}
    }},
    '{"alert_handler", '{
        '{32'h40150000, 32'h40150fff}
    }},
    '{"sram_ctrl_ret_aon", '{
        '{32'h40510000, 32'h40510fff}
    }},
    '{"nmi_gen", '{
        '{32'h40160000, 32'h40160fff}
    }},
    '{"ast_wrapper", '{
        '{32'h40490000, 32'h40490fff}
    }}};

  // List of Xbar hosts
tl_host_t xbar_hosts[$] = '{
    '{"corei", 0, '{
        "rom",
        "debug_mem",
        "ram_main",
        "eflash"}}
    ,
    '{"cored", 1, '{
        "rom",
        "debug_mem",
        "ram_main",
        "eflash",
        "uart0",
        "uart1",
        "uart2",
        "uart3",
        "i2c0",
        "i2c1",
        "i2c2",
        "pattgen",
        "gpio",
        "spi_device",
        "rv_timer",
        "usbdev",
        "pwrmgr_aon",
        "rstmgr_aon",
        "clkmgr_aon",
        "pinmux_aon",
        "padctrl_aon",
        "ram_ret_aon",
        "otp_ctrl",
        "lc_ctrl",
        "sensor_ctrl_aon",
        "alert_handler",
        "nmi_gen",
        "ast_wrapper",
        "sram_ctrl_ret_aon",
        "flash_ctrl",
        "aes",
        "entropy_src",
        "csrng",
        "edn0",
        "edn1",
        "hmac",
        "rv_plic",
        "otbn",
        "keymgr",
        "kmac",
        "sram_ctrl_main"}}
    ,
    '{"dm_sba", 2, '{
        "rom",
        "ram_main",
        "eflash",
        "uart0",
        "uart1",
        "uart2",
        "uart3",
        "i2c0",
        "i2c1",
        "i2c2",
        "pattgen",
        "gpio",
        "spi_device",
        "rv_timer",
        "usbdev",
        "pwrmgr_aon",
        "rstmgr_aon",
        "clkmgr_aon",
        "pinmux_aon",
        "padctrl_aon",
        "ram_ret_aon",
        "otp_ctrl",
        "lc_ctrl",
        "sensor_ctrl_aon",
        "alert_handler",
        "nmi_gen",
        "ast_wrapper",
        "sram_ctrl_ret_aon",
        "flash_ctrl",
        "aes",
        "entropy_src",
        "csrng",
        "edn0",
        "edn1",
        "hmac",
        "rv_plic",
        "otbn",
        "kmac",
        "sram_ctrl_main"}}
};
