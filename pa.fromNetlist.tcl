
# PlanAhead Launch Script for Post-Synthesis floorplanning, created by Project Navigator

create_project -name Neorv -dir "/home/onur/Desktop/Neorv/planAhead_run_3" -part xc6slx45csg324-2
set_property design_mode GateLvl [get_property srcset [current_run -impl]]
set_property edif_top_file "/home/onur/Desktop/Neorv/neorv32_test_setup_bootloader.ngc" [ get_property srcset [ current_run ] ]
add_files -norecurse { {/home/onur/Desktop/Neorv} }
set_property target_constrs_file "neorv32_top.ucf" [current_fileset -constrset]
add_files [list {neorv32_top.ucf}] -fileset [get_property constrset [current_run]]
link_design
