import numpy as np 
from pyfmi import load_fmu
from pylab import *
import random
import math
import sys
from  constants import *
import matplotlib.pyplot as plt


#------------------------------------------------------------------------------
# ACCELEROMETER VALUE NORMALIZER FUNCTION
#------------------------------------------------------------------------------
def accelerometer_normalizer(accelerometer):

	cap1 = accelerometer.get_real( ACCELEROMETER_CAP1 )
	cap2 = accelerometer.get_real( ACCELEROMETER_CAP2 )
	cap5 = accelerometer.get_real( ACCELEROMETER_CAP5 )
	cap7 = accelerometer.get_real( ACCELEROMETER_CAP7 )

	final_cap = (int(math.floor((((cap1+cap2+cap5+cap7)/4)*1e22))+20) & 0xffff)

	return final_cap

#--------------------------------------------------------------------------------
# DATA EXCHANGE BETWEEN  MODELS
#--------------------------------------------------------------------------------

def data_exchange(m6502,memory,sine1,sine2,sine3,accelerometer,gain,clk):

	#----------------------------------------------------------------------------
	# ACCELEROMETER SETTING
	#----------------------------------------------------------------------------

	accelerometer.set_boolean(ACCELEROMETER_CLK,	clk )

	#get values from the Sine Waves to the Accelerometer
	
	accelerometer.set_real(ACCELEROMETER_AVX,		sine1.get_real( SINE1_Y )	)
	accelerometer.set_real(ACCELEROMETER_AVY,		sine2.get_real( SINE2_Y )	)
	accelerometer.set_real(ACCELEROMETER_AVZ,		sine3.get_real( SINE3_Y )	)	


	#----------------------------------------------------------------------------
	# MEMORY SETTING
	#----------------------------------------------------------------------------

	memory.set_boolean(MEMORY_CLK,	clk )
	# From CPU
	memory.set_integer(MEMORY_ADDR,				m6502.get_integer(M6502_ADDR) 	)	# addr
	memory.set_integer(MEMORY_DATAO,			m6502.get_integer(M6502_DATAO)	)	# datao
	memory.set_boolean(MEMORY_OEB,				m6502.get_boolean(M6502_OEB)	)	# oeb
	memory.set_boolean(MEMORY_SYNC,				m6502.get_boolean(M6502_SYNC)	)	# sync
	memory.set_boolean(MEMORY_VPAB,				m6502.get_boolean(M6502_VPAB)	)	# vpab
	memory.set_boolean(MEMORY_WE_N,				m6502.get_boolean(M6502_WE_N)	)	# we_n
	memory.set_integer(MEMORY_ACCELEROMETER,  	accelerometer_normalizer(accelerometer)  ) # value from accelerometer
	
	# From Gain
	
	memory.set_integer(MEMORY_RESULT, gain.get_integer(RESULT))
	memory.set_boolean(MEMORY_RESULT_RDY, gain.get_boolean(RESULT_READY))


	#----------------------------------------------------------------------------
	# M6502 SETTING
	#----------------------------------------------------------------------------
	
	m6502.set_boolean(M6502_CLK,	clk 								)	# clk
	m6502.set_integer(M6502_DATAI,	memory.get_integer(MEMORY_DATAI)	)	# datai
	m6502.set_boolean(M6502_IRQ_N,	memory.get_boolean(MEMORY_IRQ_N)	)	# irq_n
	m6502.set_boolean(M6502_NMI_N,	memory.get_boolean(MEMORY_NMI_N)	)	# nmi_n
	m6502.set_boolean(M6502_RES_N,	memory.get_boolean(MEMORY_RES_N)	)	# res_n
	m6502.set_boolean(M6502_RDY,	memory.get_boolean(MEMORY_RDY)		)	# rdy
	m6502.set_boolean(M6502_SOB_N,	memory.get_boolean(MEMORY_SOB_N)	)	# sob_n
	

	#------------------------------------------------------------------------------
	# GAIN SETTING
	#------------------------------------------------------------------------------

	# From Memory
	gain.set_integer(DATA, memory.get_integer(MEMORY_DATA))
	gain.set_boolean(DATA_READY, memory.get_boolean(MEMORY_DATA_RDY))


#----------------------------------------------------------------------------------------------------
#----------------------------------------------------------------------------------------------------
#- MAIN - MAIN - MAIN - MAIN - MAIN - MAIN - MAIN - MAIN - MAIN - MAIN - MAIN - MAIN - MAIN - MAIN --
#----------------------------------------------------------------------------------------------------
#----------------------------------------------------------------------------------------------------


#----------------------------------------------------------------------------------------------------
# 1. FMUs LOADING
#----------------------------------------------------------------------------------------------------

# log_level is used to set the fmu's  log level. 
# NOTHING: do not use log  
# VERBOSE: log everything in file. <fmuname>_log.txt


# Digital Models
memory 		= load_fmu( './fmus/memory.fmu',			log_level = NOTHING )
m6502  		= load_fmu( './fmus/m6502.fmu',				log_level = NOTHING )
accelerometer 	= load_fmu( './fmus/Accelerometer.fmu',		log_level = NOTHING )
gain = load_fmu('./fmus/gain.fmu', log_level = NOTHING)

#Continuous Models 
sine1 			= load_fmu( './fmus/Sine_1.fmu',			log_level = NOTHING )
sine2 			= load_fmu( './fmus/Sine_2.fmu',			log_level = NOTHING )
sine3 			= load_fmu( './fmus/Sine_3.fmu',			log_level = NOTHING )




#----------------------------------------------------------------------------------------------------
# 2. FMUs INITIALIZATION
#----------------------------------------------------------------------------------------------------

# Initialize method call fmi2SetupExperiment
accelerometer.initialize()
m6502.initialize()
memory.initialize()
gain.initialize()
sine1.initialize()
sine2.initialize()
sine3.initialize()


# Global time 
time=0.

#Simulation Step
step=20e-6


# Initial value of clock for digital models
clk=False


time_values = []
accelerometer_values = []
gain_values = []


#----------------------------------------------------------------------------------------------------
# 3. MAIN ROUTINE
#----------------------------------------------------------------------------------------------------

while time<1. :	# Simulate 1 second

		#----------------------------------------------------
		# 3.1 SIMULATION DIGITAL MODELS STEP
		#----------------------------------------------------

		# do_step method call fmi2DoStep

		memory.do_step(			current_t = time, step_size = step )
		m6502.do_step(			current_t = time, step_size = step )
		accelerometer.do_step(	current_t = time, step_size = step )
		gain.do_step(	current_t = time, step_size = step )


		#-------------------------------------------------
		# 3.2 SIMULATION CONTINUOUS MODELS STEP
		#-------------------------------------------------

		# Sine Waves simulation

		sine1.do_step( current_t = time, step_size = step )
		sine2.do_step( current_t = time, step_size = step )
		sine3.do_step( current_t = time, step_size = step )


		# Digital clock update
		clk = not clk		

		# Data Exchange between Digital and Continuous models
		data_exchange(m6502, memory, sine1, sine2, sine3, accelerometer, gain, clk)
		
		# Update the global time
		time = time + step

		# Tracing Time, Accelerometer and Gain
		time_values.append( time )						  			# trace Time	
		accelerometer_values.append( accelerometer.get("Cap1") )	# trace one value from the Accelerometer
		gain_values.append( gain.get("result"))


#----------------------------------------------------
# 4. PLOT ACCELEROMETER & GAIN VALUES
#----------------------------------------------------

#Plot Figure 1 ( Accelerometer )
plt.figure(1)
plt.subplot(111)
plt.title('Accelerometer')
plt.plot(time_values,accelerometer_values)
grid(True)


#Plot Figure 2 ( Gain )
plt.figure(2)
plt.subplot(111)
plt.title('Gain')
plt.plot(time_values,gain_values)
grid(True)


plt.show()
