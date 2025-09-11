transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3 {C:/Users/zktok/Desktop/CSE 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3/and_gate_32.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3 {C:/Users/zktok/Desktop/CSE 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3/or_gate_32.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3 {C:/Users/zktok/Desktop/CSE 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3/xor_gate_32.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3 {C:/Users/zktok/Desktop/CSE 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3/nor_gate_32.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3 {C:/Users/zktok/Desktop/CSE 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3/mux_2x1_1bit.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3 {C:/Users/zktok/Desktop/CSE 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3/mux_4x1_1bit.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3 {C:/Users/zktok/Desktop/CSE 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3/mux_8x1_1bit.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3 {C:/Users/zktok/Desktop/CSE 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3/mux_8x1_32bit.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3 {C:/Users/zktok/Desktop/CSE 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3/CLA_4bit.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3 {C:/Users/zktok/Desktop/CSE 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3/sum_out.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3 {C:/Users/zktok/Desktop/CSE 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3/carry_out_generator.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3 {C:/Users/zktok/Desktop/CSE 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3/CLA_16bit_2level.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3 {C:/Users/zktok/Desktop/CSE 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3/generator_and_propagate_4bit.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3 {C:/Users/zktok/Desktop/CSE 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3/control_over_flow.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3 {C:/Users/zktok/Desktop/CSE 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3/mux_2x1_32bit.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3 {C:/Users/zktok/Desktop/CSE 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3/not_gate_32.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3 {C:/Users/zktok/Desktop/CSE 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3/sett_less_than.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3 {C:/Users/zktok/Desktop/CSE 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3/Basic_controller.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3 {C:/Users/zktok/Desktop/CSE 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3/adder.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3 {C:/Users/zktok/Desktop/CSE 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3/alu.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3 {C:/Users/zktok/Desktop/CSE 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3/control_unit.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3 {C:/Users/zktok/Desktop/CSE 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3/alu_control.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3 {C:/Users/zktok/Desktop/CSE 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3/sign_extend.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3 {C:/Users/zktok/Desktop/CSE 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3/shift_left_2.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3 {C:/Users/zktok/Desktop/CSE 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3/mips.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3 {C:/Users/zktok/Desktop/CSE 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3/register_block.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3 {C:/Users/zktok/Desktop/CSE 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3/instruction_block.v}
vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3 {C:/Users/zktok/Desktop/CSE 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3/memory_block.v}

vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3 {C:/Users/zktok/Desktop/CSE 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3/my_testbench.v}

vsim -t 1ps -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cyclonev_ver -L cyclonev_hssi_ver -L cyclonev_pcie_hip_ver -L rtl_work -L work -voptargs="+acc"  my_testbench

add wave *
view structure
view signals
run -all
