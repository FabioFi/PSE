# 
# Report generation script generated by Vivado
# 

proc create_report { reportName command } {
  set status "."
  append status $reportName ".fail"
  if { [file exists $status] } {
    eval file delete [glob $status]
  }
  send_msg_id runtcl-4 info "Executing : $command"
  set retval [eval catch { $command } msg]
  if { $retval != 0 } {
    set fp [open $status w]
    close $fp
    send_msg_id runtcl-5 warning "$msg"
  }
}
proc start_step { step } {
  set stopFile ".stop.rst"
  if {[file isfile .stop.rst]} {
    puts ""
    puts "*** Halting run - EA reset detected ***"
    puts ""
    puts ""
    return -code error
  }
  set beginFile ".$step.begin.rst"
  set platform "$::tcl_platform(platform)"
  set user "$::tcl_platform(user)"
  set pid [pid]
  set host ""
  if { [string equal $platform unix] } {
    if { [info exist ::env(HOSTNAME)] } {
      set host $::env(HOSTNAME)
    }
  } else {
    if { [info exist ::env(COMPUTERNAME)] } {
      set host $::env(COMPUTERNAME)
    }
  }
  set ch [open $beginFile w]
  puts $ch "<?xml version=\"1.0\"?>"
  puts $ch "<ProcessHandle Version=\"1\" Minor=\"0\">"
  puts $ch "    <Process Command=\".planAhead.\" Owner=\"$user\" Host=\"$host\" Pid=\"$pid\">"
  puts $ch "    </Process>"
  puts $ch "</ProcessHandle>"
  close $ch
}

proc end_step { step } {
  set endFile ".$step.end.rst"
  set ch [open $endFile w]
  close $ch
}

proc step_failed { step } {
  set endFile ".$step.error.rst"
  set ch [open $endFile w]
  close $ch
}

set_msg_config -id {Synth 8-256} -limit 10000
set_msg_config -id {Synth 8-638} -limit 10000

start_step place_design
set ACTIVE_STEP place_design
set rc [catch {
  create_msg_db place_design.pb
  set_param chipscope.maxJobs 3
  set_param synth.incrementalSynthesisCache C:/Users/fabio.fiorio/AppData/Roaming/Xilinx/Vivado/.Xil/Vivado-13152-IT-FFIORIO/incrSyn
  open_checkpoint XTEA_opt.dcp
  set_property webtalk.parent_dir C:/Users/fabio.fiorio/Downloads/VIVADO/project_1/project_1.cache/wt [current_project]
  if { [llength [get_debug_cores -quiet] ] > 0 }  { 
    implement_debug_core 
  } 
  place_design 
  write_checkpoint -force XTEA_placed.dcp
  create_report "impl_1_place_report_io_0" "report_io -file XTEA_io_placed.rpt"
  create_report "impl_1_place_report_utilization_0" "report_utilization -file XTEA_utilization_placed.rpt -pb XTEA_utilization_placed.pb"
  create_report "impl_1_place_report_control_sets_0" "report_control_sets -verbose -file XTEA_control_sets_placed.rpt"
  close_msg_db -file place_design.pb
} RESULT]
if {$rc} {
  step_failed place_design
  return -code error $RESULT
} else {
  end_step place_design
  unset ACTIVE_STEP 
}

start_step route_design
set ACTIVE_STEP route_design
set rc [catch {
  create_msg_db route_design.pb
  route_design 
  write_checkpoint -force XTEA_routed.dcp
  create_report "impl_1_route_report_drc_0" "report_drc -file XTEA_drc_routed.rpt -pb XTEA_drc_routed.pb -rpx XTEA_drc_routed.rpx"
  create_report "impl_1_route_report_methodology_0" "report_methodology -file XTEA_methodology_drc_routed.rpt -pb XTEA_methodology_drc_routed.pb -rpx XTEA_methodology_drc_routed.rpx"
  create_report "impl_1_route_report_power_0" "report_power -file XTEA_power_routed.rpt -pb XTEA_power_summary_routed.pb -rpx XTEA_power_routed.rpx"
  create_report "impl_1_route_report_route_status_0" "report_route_status -file XTEA_route_status.rpt -pb XTEA_route_status.pb"
  create_report "impl_1_route_report_timing_summary_0" "report_timing_summary -max_paths 10 -file XTEA_timing_summary_routed.rpt -pb XTEA_timing_summary_routed.pb -rpx XTEA_timing_summary_routed.rpx -warn_on_violation "
  create_report "impl_1_route_report_incremental_reuse_0" "report_incremental_reuse -file XTEA_incremental_reuse_routed.rpt"
  create_report "impl_1_route_report_clock_utilization_0" "report_clock_utilization -file XTEA_clock_utilization_routed.rpt"
  create_report "impl_1_route_report_bus_skew_0" "report_bus_skew -warn_on_violation -file XTEA_bus_skew_routed.rpt -pb XTEA_bus_skew_routed.pb -rpx XTEA_bus_skew_routed.rpx"
  close_msg_db -file route_design.pb
} RESULT]
if {$rc} {
  write_checkpoint -force XTEA_routed_error.dcp
  step_failed route_design
  return -code error $RESULT
} else {
  end_step route_design
  unset ACTIVE_STEP 
}

start_step write_bitstream
set ACTIVE_STEP write_bitstream
set rc [catch {
  create_msg_db write_bitstream.pb
  catch { write_mem_info -force XTEA.mmi }
  write_bitstream -force XTEA.bit 
  catch {write_debug_probes -quiet -force XTEA}
  catch {file copy -force XTEA.ltx debug_nets.ltx}
  close_msg_db -file write_bitstream.pb
} RESULT]
if {$rc} {
  step_failed write_bitstream
  return -code error $RESULT
} else {
  end_step write_bitstream
  unset ACTIVE_STEP 
}

