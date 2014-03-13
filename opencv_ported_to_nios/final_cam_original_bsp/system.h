/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'cpu_image_processing' in SOPC Builder design 'SOPC_SYS'
 * SOPC Builder design path: ../../SOPC_SYS.sopcinfo
 *
 * Generated: Thu Jul 05 14:03:22 EEST 2012
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x10500820
#define ALT_CPU_CPU_FREQ 77500000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x1
#define ALT_CPU_CPU_IMPLEMENTATION "fast"
#define ALT_CPU_DATA_ADDR_WIDTH 0x1d
#define ALT_CPU_DCACHE_LINE_SIZE 32
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_DCACHE_SIZE 2048
#define ALT_CPU_EXCEPTION_ADDR 0x8000020
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 77500000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 1
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 32
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_ICACHE_SIZE 4096
#define ALT_CPU_INITDA_SUPPORTED
#define ALT_CPU_INST_ADDR_WIDTH 0x1d
#define ALT_CPU_NAME "cpu_image_processing"
#define ALT_CPU_NUM_OF_SHADOW_REG_SETS 0
#define ALT_CPU_RESET_ADDR 0x8000000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x10500820
#define NIOS2_CPU_FREQ 77500000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x1
#define NIOS2_CPU_IMPLEMENTATION "fast"
#define NIOS2_DATA_ADDR_WIDTH 0x1d
#define NIOS2_DCACHE_LINE_SIZE 32
#define NIOS2_DCACHE_LINE_SIZE_LOG2 5
#define NIOS2_DCACHE_SIZE 2048
#define NIOS2_EXCEPTION_ADDR 0x8000020
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 1
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 32
#define NIOS2_ICACHE_LINE_SIZE_LOG2 5
#define NIOS2_ICACHE_SIZE 4096
#define NIOS2_INITDA_SUPPORTED
#define NIOS2_INST_ADDR_WIDTH 0x1d
#define NIOS2_NUM_OF_SHADOW_REG_SETS 0
#define NIOS2_RESET_ADDR 0x8000000


/*
 * Custom instruction macros
 *
 */

#define ALT_CI_CVINRANGE_GREEN_INST(A,B) __builtin_custom_inii(ALT_CI_CVINRANGE_GREEN_INST_N,(A),(B))
#define ALT_CI_CVINRANGE_GREEN_INST_N 0x0
#define ALT_CI_CVINRANGE_INST(A,B) __builtin_custom_inii(ALT_CI_CVINRANGE_INST_N,(A),(B))
#define ALT_CI_CVINRANGE_INST_N 0x1
#define ALT_CI_RGB2HSV_INST(A,B) __builtin_custom_inii(ALT_CI_RGB2HSV_INST_N,(A),(B))
#define ALT_CI_RGB2HSV_INST_N 0x2


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_MAILBOX
#define __ALTERA_AVALON_MUTEX
#define __ALTERA_AVALON_NEW_SDRAM_CONTROLLER
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SYSID
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2
#define __ALTPLL
#define __CVINRANGE
#define __CVINRANGE_GREEN
#define __RGB2HSV
#define __TERASIC_SRAM


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "CYCLONEIVE"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag_uart_image_processing"
#define ALT_STDERR_BASE 0x10501040
#define ALT_STDERR_DEV jtag_uart_image_processing
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart_image_processing"
#define ALT_STDIN_BASE 0x10501040
#define ALT_STDIN_DEV jtag_uart_image_processing
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart_image_processing"
#define ALT_STDOUT_BASE 0x10501040
#define ALT_STDOUT_DEV jtag_uart_image_processing
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "SOPC_SYS"


/*
 * TERASIC_SRAM_0 configuration
 *
 */

#define ALT_MODULE_CLASS_TERASIC_SRAM_0 TERASIC_SRAM
#define TERASIC_SRAM_0_BASE 0x10200000
#define TERASIC_SRAM_0_IRQ -1
#define TERASIC_SRAM_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define TERASIC_SRAM_0_NAME "/dev/TERASIC_SRAM_0"
#define TERASIC_SRAM_0_SPAN 2097152
#define TERASIC_SRAM_0_TYPE "TERASIC_SRAM"


/*
 * altpll_0 configuration
 *
 */

#define ALTPLL_0_BASE 0x10501000
#define ALTPLL_0_IRQ -1
#define ALTPLL_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ALTPLL_0_NAME "/dev/altpll_0"
#define ALTPLL_0_SPAN 16
#define ALTPLL_0_TYPE "altpll"
#define ALT_MODULE_CLASS_altpll_0 altpll


/*
 * frame_count configuration
 *
 */

#define ALT_MODULE_CLASS_frame_count altera_avalon_pio
#define FRAME_COUNT_BASE 0x10501020
#define FRAME_COUNT_BIT_CLEARING_EDGE_REGISTER 0
#define FRAME_COUNT_BIT_MODIFYING_OUTPUT_REGISTER 0
#define FRAME_COUNT_CAPTURE 0
#define FRAME_COUNT_DATA_WIDTH 32
#define FRAME_COUNT_DO_TEST_BENCH_WIRING 0
#define FRAME_COUNT_DRIVEN_SIM_VALUE 0x0
#define FRAME_COUNT_EDGE_TYPE "NONE"
#define FRAME_COUNT_FREQ 77500000u
#define FRAME_COUNT_HAS_IN 1
#define FRAME_COUNT_HAS_OUT 0
#define FRAME_COUNT_HAS_TRI 0
#define FRAME_COUNT_IRQ -1
#define FRAME_COUNT_IRQ_INTERRUPT_CONTROLLER_ID -1
#define FRAME_COUNT_IRQ_TYPE "NONE"
#define FRAME_COUNT_NAME "/dev/frame_count"
#define FRAME_COUNT_RESET_VALUE 0x0
#define FRAME_COUNT_SPAN 16
#define FRAME_COUNT_TYPE "altera_avalon_pio"


/*
 * frame_done configuration
 *
 */

#define ALT_MODULE_CLASS_frame_done altera_avalon_pio
#define FRAME_DONE_BASE 0x10501030
#define FRAME_DONE_BIT_CLEARING_EDGE_REGISTER 0
#define FRAME_DONE_BIT_MODIFYING_OUTPUT_REGISTER 0
#define FRAME_DONE_CAPTURE 0
#define FRAME_DONE_DATA_WIDTH 1
#define FRAME_DONE_DO_TEST_BENCH_WIRING 0
#define FRAME_DONE_DRIVEN_SIM_VALUE 0x0
#define FRAME_DONE_EDGE_TYPE "NONE"
#define FRAME_DONE_FREQ 77500000u
#define FRAME_DONE_HAS_IN 1
#define FRAME_DONE_HAS_OUT 0
#define FRAME_DONE_HAS_TRI 0
#define FRAME_DONE_IRQ -1
#define FRAME_DONE_IRQ_INTERRUPT_CONTROLLER_ID -1
#define FRAME_DONE_IRQ_TYPE "NONE"
#define FRAME_DONE_NAME "/dev/frame_done"
#define FRAME_DONE_RESET_VALUE 0x0
#define FRAME_DONE_SPAN 16
#define FRAME_DONE_TYPE "altera_avalon_pio"


/*
 * frame_req configuration
 *
 */

#define ALT_MODULE_CLASS_frame_req altera_avalon_pio
#define FRAME_REQ_BASE 0x10501010
#define FRAME_REQ_BIT_CLEARING_EDGE_REGISTER 0
#define FRAME_REQ_BIT_MODIFYING_OUTPUT_REGISTER 0
#define FRAME_REQ_CAPTURE 0
#define FRAME_REQ_DATA_WIDTH 1
#define FRAME_REQ_DO_TEST_BENCH_WIRING 0
#define FRAME_REQ_DRIVEN_SIM_VALUE 0x0
#define FRAME_REQ_EDGE_TYPE "NONE"
#define FRAME_REQ_FREQ 77500000u
#define FRAME_REQ_HAS_IN 0
#define FRAME_REQ_HAS_OUT 1
#define FRAME_REQ_HAS_TRI 0
#define FRAME_REQ_IRQ -1
#define FRAME_REQ_IRQ_INTERRUPT_CONTROLLER_ID -1
#define FRAME_REQ_IRQ_TYPE "NONE"
#define FRAME_REQ_NAME "/dev/frame_req"
#define FRAME_REQ_RESET_VALUE 0x0
#define FRAME_REQ_SPAN 16
#define FRAME_REQ_TYPE "altera_avalon_pio"


/*
 * hal configuration
 *
 */

#define ALT_MAX_FD 32
#define ALT_SYS_CLK TIMER_1
#define ALT_TIMESTAMP_CLK none


/*
 * jtag_uart_image_processing configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart_image_processing altera_avalon_jtag_uart
#define JTAG_UART_IMAGE_PROCESSING_BASE 0x10501040
#define JTAG_UART_IMAGE_PROCESSING_IRQ 0
#define JTAG_UART_IMAGE_PROCESSING_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_IMAGE_PROCESSING_NAME "/dev/jtag_uart_image_processing"
#define JTAG_UART_IMAGE_PROCESSING_READ_DEPTH 64
#define JTAG_UART_IMAGE_PROCESSING_READ_THRESHOLD 8
#define JTAG_UART_IMAGE_PROCESSING_SPAN 8
#define JTAG_UART_IMAGE_PROCESSING_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_IMAGE_PROCESSING_WRITE_DEPTH 64
#define JTAG_UART_IMAGE_PROCESSING_WRITE_THRESHOLD 8


/*
 * mailbox_0 configuration
 *
 */

#define ALT_MODULE_CLASS_mailbox_0 altera_avalon_mailbox
#define MAILBOX_0_BASE 0x10
#define MAILBOX_0_IRQ -1
#define MAILBOX_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define MAILBOX_0_MAILBOX_MEMORY_ADDR 0x2100
#define MAILBOX_0_MAILBOX_MEMORY_OFFSET 256u
#define MAILBOX_0_MAILBOX_MEMORY_SIZE 3840u
#define MAILBOX_0_NAME "/dev/mailbox_0"
#define MAILBOX_0_SLAVE "mailbox_memory/s1"
#define MAILBOX_0_SPAN 16
#define MAILBOX_0_TYPE "altera_avalon_mailbox"


/*
 * mailbox_memory configuration
 *
 */

#define ALT_MODULE_CLASS_mailbox_memory altera_avalon_onchip_memory2
#define MAILBOX_MEMORY_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define MAILBOX_MEMORY_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define MAILBOX_MEMORY_BASE 0x2000
#define MAILBOX_MEMORY_CONTENTS_INFO ""
#define MAILBOX_MEMORY_DUAL_PORT 0
#define MAILBOX_MEMORY_GUI_RAM_BLOCK_TYPE "Automatic"
#define MAILBOX_MEMORY_INIT_CONTENTS_FILE "mailbox_memory"
#define MAILBOX_MEMORY_INIT_MEM_CONTENT 1
#define MAILBOX_MEMORY_INSTANCE_ID "NONE"
#define MAILBOX_MEMORY_IRQ -1
#define MAILBOX_MEMORY_IRQ_INTERRUPT_CONTROLLER_ID -1
#define MAILBOX_MEMORY_NAME "/dev/mailbox_memory"
#define MAILBOX_MEMORY_NON_DEFAULT_INIT_FILE_ENABLED 0
#define MAILBOX_MEMORY_RAM_BLOCK_TYPE "Auto"
#define MAILBOX_MEMORY_READ_DURING_WRITE_MODE "DONT_CARE"
#define MAILBOX_MEMORY_SINGLE_CLOCK_OP 0
#define MAILBOX_MEMORY_SIZE_MULTIPLE 1
#define MAILBOX_MEMORY_SIZE_VALUE 4096u
#define MAILBOX_MEMORY_SPAN 4096
#define MAILBOX_MEMORY_TYPE "altera_avalon_onchip_memory2"
#define MAILBOX_MEMORY_WRITABLE 1


/*
 * mutex_0 configuration
 *
 */

#define ALT_MODULE_CLASS_mutex_0 altera_avalon_mutex
#define MUTEX_0_BASE 0x8
#define MUTEX_0_IRQ -1
#define MUTEX_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define MUTEX_0_NAME "/dev/mutex_0"
#define MUTEX_0_OWNER_INIT 0
#define MUTEX_0_OWNER_WIDTH 16
#define MUTEX_0_SPAN 8
#define MUTEX_0_TYPE "altera_avalon_mutex"
#define MUTEX_0_VALUE_INIT 0
#define MUTEX_0_VALUE_WIDTH 16


/*
 * onchip_memory2_0 configuration
 *
 */

#define ALT_MODULE_CLASS_onchip_memory2_0 altera_avalon_onchip_memory2
#define ONCHIP_MEMORY2_0_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define ONCHIP_MEMORY2_0_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define ONCHIP_MEMORY2_0_BASE 0x10480000
#define ONCHIP_MEMORY2_0_CONTENTS_INFO ""
#define ONCHIP_MEMORY2_0_DUAL_PORT 0
#define ONCHIP_MEMORY2_0_GUI_RAM_BLOCK_TYPE "Automatic"
#define ONCHIP_MEMORY2_0_INIT_CONTENTS_FILE "onchip_memory2_0"
#define ONCHIP_MEMORY2_0_INIT_MEM_CONTENT 1
#define ONCHIP_MEMORY2_0_INSTANCE_ID "NONE"
#define ONCHIP_MEMORY2_0_IRQ -1
#define ONCHIP_MEMORY2_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ONCHIP_MEMORY2_0_NAME "/dev/onchip_memory2_0"
#define ONCHIP_MEMORY2_0_NON_DEFAULT_INIT_FILE_ENABLED 0
#define ONCHIP_MEMORY2_0_RAM_BLOCK_TYPE "Auto"
#define ONCHIP_MEMORY2_0_READ_DURING_WRITE_MODE "DONT_CARE"
#define ONCHIP_MEMORY2_0_SINGLE_CLOCK_OP 0
#define ONCHIP_MEMORY2_0_SIZE_MULTIPLE 1
#define ONCHIP_MEMORY2_0_SIZE_VALUE 375200u
#define ONCHIP_MEMORY2_0_SPAN 375200
#define ONCHIP_MEMORY2_0_TYPE "altera_avalon_onchip_memory2"
#define ONCHIP_MEMORY2_0_WRITABLE 1


/*
 * sdram_0 configuration
 *
 */

#define ALT_MODULE_CLASS_sdram_0 altera_avalon_new_sdram_controller
#define SDRAM_0_BASE 0x8000000
#define SDRAM_0_CAS_LATENCY 3
#define SDRAM_0_CONTENTS_INFO ""
#define SDRAM_0_INIT_NOP_DELAY 0.0
#define SDRAM_0_INIT_REFRESH_COMMANDS 2
#define SDRAM_0_IRQ -1
#define SDRAM_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SDRAM_0_IS_INITIALIZED 1
#define SDRAM_0_NAME "/dev/sdram_0"
#define SDRAM_0_POWERUP_DELAY 100.0
#define SDRAM_0_REFRESH_PERIOD 15.625
#define SDRAM_0_REGISTER_DATA_IN 1
#define SDRAM_0_SDRAM_ADDR_WIDTH 0x19
#define SDRAM_0_SDRAM_BANK_WIDTH 2
#define SDRAM_0_SDRAM_COL_WIDTH 10
#define SDRAM_0_SDRAM_DATA_WIDTH 32
#define SDRAM_0_SDRAM_NUM_BANKS 4
#define SDRAM_0_SDRAM_NUM_CHIPSELECTS 1
#define SDRAM_0_SDRAM_ROW_WIDTH 13
#define SDRAM_0_SHARED_DATA 0
#define SDRAM_0_SIM_MODEL_BASE 0
#define SDRAM_0_SPAN 134217728
#define SDRAM_0_STARVATION_INDICATOR 0
#define SDRAM_0_TRISTATE_BRIDGE_SLAVE ""
#define SDRAM_0_TYPE "altera_avalon_new_sdram_controller"
#define SDRAM_0_T_AC 5.5
#define SDRAM_0_T_MRD 3
#define SDRAM_0_T_RCD 20.0
#define SDRAM_0_T_RFC 70.0
#define SDRAM_0_T_RP 20.0
#define SDRAM_0_T_WR 14.0


/*
 * sysid configuration
 *
 */

#define ALT_MODULE_CLASS_sysid altera_avalon_sysid
#define SYSID_BASE 0x40
#define SYSID_ID 0u
#define SYSID_IRQ -1
#define SYSID_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSID_NAME "/dev/sysid"
#define SYSID_SPAN 8
#define SYSID_TIMESTAMP 1341483308u
#define SYSID_TYPE "altera_avalon_sysid"


/*
 * timer_1 configuration
 *
 */

#define ALT_MODULE_CLASS_timer_1 altera_avalon_timer
#define TIMER_1_ALWAYS_RUN 0
#define TIMER_1_BASE 0x60
#define TIMER_1_COUNTER_SIZE 32
#define TIMER_1_FIXED_PERIOD 0
#define TIMER_1_FREQ 50000000u
#define TIMER_1_IRQ 5
#define TIMER_1_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_1_LOAD_VALUE 49999ull
#define TIMER_1_MULT 0.0010
#define TIMER_1_NAME "/dev/timer_1"
#define TIMER_1_PERIOD 1
#define TIMER_1_PERIOD_UNITS "ms"
#define TIMER_1_RESET_OUTPUT 0
#define TIMER_1_SNAPSHOT 1
#define TIMER_1_SPAN 32
#define TIMER_1_TICKS_PER_SEC 1000u
#define TIMER_1_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_1_TYPE "altera_avalon_timer"

#endif /* __SYSTEM_H_ */
