set moduleName xtea
set isTopModule 1
set isTaskLevelControl 1
set isCombinational 0
set isDatapathOnly 0
set isFreeRunPipelineModule 0
set isPipelined 0
set pipeline_type none
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set C_modelName {xtea}
set C_modelType { void 0 }
set C_modelArgList {
	{ word0 int 32 regular  }
	{ word1 int 32 regular  }
	{ key0 int 32 regular  }
	{ key1 int 32 regular  }
	{ key2 int 32 regular  }
	{ key3 int 32 regular  }
	{ mode uint 1 regular  }
	{ result0 int 32 regular {pointer 1}  }
	{ result1 int 32 regular {pointer 1}  }
}
set C_modelArgMapList {[ 
	{ "Name" : "word0", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "word0","cData": "unsigned int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}]} , 
 	{ "Name" : "word1", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "word1","cData": "unsigned int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}]} , 
 	{ "Name" : "key0", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "key0","cData": "unsigned int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}]} , 
 	{ "Name" : "key1", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "key1","cData": "unsigned int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}]} , 
 	{ "Name" : "key2", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "key2","cData": "unsigned int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}]} , 
 	{ "Name" : "key3", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "key3","cData": "unsigned int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}]} , 
 	{ "Name" : "mode", "interface" : "wire", "bitwidth" : 1, "direction" : "READONLY", "bitSlice":[{"low":0,"up":0,"cElement": [{"cName": "mode","cData": "bool","bit_use": { "low": 0,"up": 0},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}]} , 
 	{ "Name" : "result0", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "result0","cData": "unsigned int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} , 
 	{ "Name" : "result1", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "result1","cData": "unsigned int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} ]}
# RTL Port declarations: 
set portNum 17
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ word0 sc_in sc_lv 32 signal 0 } 
	{ word1 sc_in sc_lv 32 signal 1 } 
	{ key0 sc_in sc_lv 32 signal 2 } 
	{ key1 sc_in sc_lv 32 signal 3 } 
	{ key2 sc_in sc_lv 32 signal 4 } 
	{ key3 sc_in sc_lv 32 signal 5 } 
	{ mode sc_in sc_logic 1 signal 6 } 
	{ result0 sc_out sc_lv 32 signal 7 } 
	{ result0_ap_vld sc_out sc_logic 1 outvld 7 } 
	{ result1 sc_out sc_lv 32 signal 8 } 
	{ result1_ap_vld sc_out sc_logic 1 outvld 8 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "word0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "word0", "role": "default" }} , 
 	{ "name": "word1", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "word1", "role": "default" }} , 
 	{ "name": "key0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "key0", "role": "default" }} , 
 	{ "name": "key1", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "key1", "role": "default" }} , 
 	{ "name": "key2", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "key2", "role": "default" }} , 
 	{ "name": "key3", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "key3", "role": "default" }} , 
 	{ "name": "mode", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "mode", "role": "default" }} , 
 	{ "name": "result0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "result0", "role": "default" }} , 
 	{ "name": "result0_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "result0", "role": "ap_vld" }} , 
 	{ "name": "result1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "result1", "role": "default" }} , 
 	{ "name": "result1_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "result1", "role": "ap_vld" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "",
		"CDFG" : "xtea",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "66", "EstimateLatencyMax" : "66",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "word0", "Type" : "None", "Direction" : "I"},
			{"Name" : "word1", "Type" : "None", "Direction" : "I"},
			{"Name" : "key0", "Type" : "None", "Direction" : "I"},
			{"Name" : "key1", "Type" : "None", "Direction" : "I"},
			{"Name" : "key2", "Type" : "None", "Direction" : "I"},
			{"Name" : "key3", "Type" : "None", "Direction" : "I"},
			{"Name" : "mode", "Type" : "None", "Direction" : "I"},
			{"Name" : "result0", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "result1", "Type" : "Vld", "Direction" : "O"}]}]}


set ArgLastReadFirstWriteLatency {
	xtea {
		word0 {Type I LastRead 0 FirstWrite -1}
		word1 {Type I LastRead 0 FirstWrite -1}
		key0 {Type I LastRead 0 FirstWrite -1}
		key1 {Type I LastRead 0 FirstWrite -1}
		key2 {Type I LastRead 0 FirstWrite -1}
		key3 {Type I LastRead 0 FirstWrite -1}
		mode {Type I LastRead 0 FirstWrite -1}
		result0 {Type O LastRead -1 FirstWrite 2}
		result1 {Type O LastRead -1 FirstWrite 2}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "66", "Max" : "66"}
	, {"Name" : "Interval", "Min" : "67", "Max" : "67"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	word0 { ap_none {  { word0 in_data 0 32 } } }
	word1 { ap_none {  { word1 in_data 0 32 } } }
	key0 { ap_none {  { key0 in_data 0 32 } } }
	key1 { ap_none {  { key1 in_data 0 32 } } }
	key2 { ap_none {  { key2 in_data 0 32 } } }
	key3 { ap_none {  { key3 in_data 0 32 } } }
	mode { ap_none {  { mode in_data 0 1 } } }
	result0 { ap_vld {  { result0 out_data 1 32 }  { result0_ap_vld out_vld 1 1 } } }
	result1 { ap_vld {  { result1 out_data 1 32 }  { result1_ap_vld out_vld 1 1 } } }
}

set busDeadlockParameterList { 
}

# RTL port scheduling information:
set fifoSchedulingInfoList { 
}

# RTL bus port read request latency information:
set busReadReqLatencyList { 
}

# RTL bus port write response latency information:
set busWriteResLatencyList { 
}

# RTL array port load latency information:
set memoryLoadLatencyList { 
}
