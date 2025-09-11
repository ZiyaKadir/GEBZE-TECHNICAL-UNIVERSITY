transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Quartus_project2 {C:/Users/zktok/Desktop/CSE 331/Quartus_project2/and_gate_32.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Quartus_project2 {C:/Users/zktok/Desktop/CSE 331/Quartus_project2/or_gate_32.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Quartus_project2 {C:/Users/zktok/Desktop/CSE 331/Quartus_project2/xor_gate_32.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Quartus_project2 {C:/Users/zktok/Desktop/CSE 331/Quartus_project2/nor_gate_32.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Quartus_project2 {C:/Users/zktok/Desktop/CSE 331/Quartus_project2/mux_2x1_1bit.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Quartus_project2 {C:/Users/zktok/Desktop/CSE 331/Quartus_project2/mux_4x1_1bit.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Quartus_project2 {C:/Users/zktok/Desktop/CSE 331/Quartus_project2/mux_8x1_1bit.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Quartus_project2 {C:/Users/zktok/Desktop/CSE 331/Quartus_project2/mux_8x1_32bit.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Quartus_project2 {C:/Users/zktok/Desktop/CSE 331/Quartus_project2/CLA_4bit.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Quartus_project2 {C:/Users/zktok/Desktop/CSE 331/Quartus_project2/sum_out.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Quartus_project2 {C:/Users/zktok/Desktop/CSE 331/Quartus_project2/carry_out_generator.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Quartus_project2 {C:/Users/zktok/Desktop/CSE 331/Quartus_project2/CLA_16bit_2level.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Quartus_project2 {C:/Users/zktok/Desktop/CSE 331/Quartus_project2/generator_and_propagate_4bit.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Quartus_project2 {C:/Users/zktok/Desktop/CSE 331/Quartus_project2/control_over_flow.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Quartus_project2 {C:/Users/zktok/Desktop/CSE 331/Quartus_project2/mux_2x1_32bit.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Quartus_project2 {C:/Users/zktok/Desktop/CSE 331/Quartus_project2/not_gate_32.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Quartus_project2 {C:/Users/zktok/Desktop/CSE 331/Quartus_project2/sett_less_than.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Quartus_project2 {C:/Users/zktok/Desktop/CSE 331/Quartus_project2/Basic_controller.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Quartus_project2 {C:/Users/zktok/Desktop/CSE 331/Quartus_project2/mod.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Quartus_project2 {C:/Users/zktok/Desktop/CSE 331/Quartus_project2/mod_cu.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Quartus_project2 {C:/Users/zktok/Desktop/CSE 331/Quartus_project2/mod_dp.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Quartus_project2 {C:/Users/zktok/Desktop/CSE 331/Quartus_project2/adder.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Quartus_project2 {C:/Users/zktok/Desktop/CSE 331/Quartus_project2/alu.v}

vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Quartus_project2 {C:/Users/zktok/Desktop/CSE 331/Quartus_project2/my_testbench.v}

vsim -t 1ps -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cyclonev_ver -L cyclonev_hssi_ver -L cyclonev_pcie_hip_ver -L rtl_work -L work -voptargs="+acc"  my_testbench

add wave *
view structure
view signals
run -all
