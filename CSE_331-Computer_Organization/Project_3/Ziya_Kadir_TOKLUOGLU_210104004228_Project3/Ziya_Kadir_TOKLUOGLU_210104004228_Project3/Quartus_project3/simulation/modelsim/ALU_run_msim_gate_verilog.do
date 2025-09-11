transcript on
if {[file exists gate_work]} {
	vdel -lib gate_work -all
}
vlib gate_work
vmap work gate_work

vlog -vlog01compat -work work +incdir+. {ALU.vo}

vlog -vlog01compat -work work +incdir+C:/Users/zktok/Desktop/CSE\ 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3 {C:/Users/zktok/Desktop/CSE 331/Ziya_Kadir_TOKLUOGLU_210104004228_Project3/Quartus_project3/my_testbench.v}

vsim -t 1ps -L altera_ver -L altera_lnsim_ver -L cyclonev_ver -L lpm_ver -L sgate_ver -L cyclonev_hssi_ver -L altera_mf_ver -L cyclonev_pcie_hip_ver -L gate_work -L work -voptargs="+acc"  my_testbench

add wave *
view structure
view signals
run -all
