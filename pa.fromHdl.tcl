
# PlanAhead Launch Script for Pre-Synthesis Floorplanning, created by Project Navigator

create_project -name Neorv -dir "/home/onur/Desktop/Neorv/planAhead_run_2" -part xc6slx45csg324-2
set_param project.pinAheadLayout yes
set srcset [get_property srcset [current_run -impl]]
set_property target_constrs_file "neorv32_top.ucf" [current_fileset -constrset]
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_package.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_fifo.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_cpu_decompressor.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_cpu_cp_shifter.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_cpu_cp_muldiv.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_cpu_cp_fpu.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_cpu_cp_crypto.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_cpu_cp_cond.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_cpu_cp_cfu.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_cpu_cp_bitmanip.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_debug_auth.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_cpu_regfile.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_cpu_pmp.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_cpu_lsu.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_cpu_icc.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_cpu_control.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_cpu_alu.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_clockgate.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_bus.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_bootloader_image.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_application_image.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_xbus.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_wdt.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_uart.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_twi.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_twd.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_trng.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_sysinfo.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_sys.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_spi.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_slink.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_sdi.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_pwm.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_onewire.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_neoled.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_imem.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_gptmr.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_gpio.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_dmem.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_dma.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_debug_dtm.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_debug_dm.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_crc.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_cpu.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_clint.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_cfs.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_cache.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_boot_rom.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set hdlfile [add_files [list {../neorv32-main/rtl/core/neorv32_top.vhd}]]
set_property file_type VHDL $hdlfile
set_property library neorv32 $hdlfile
set_property top neorv32_top $srcset
add_files [list {neorv32_top.ucf}] -fileset [get_property constrset [current_run]]
open_rtl_design -part xc6slx45csg324-2
