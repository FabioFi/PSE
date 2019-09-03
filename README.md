# PSE

## RTL

### What the report should contains for this lesson:

– Interface definition

– FSMD and EFSM of the device behavior

	• For the FSMD schema, it is enough to show the connections between Controller and Datapath (not the internal implementation schema)

	• The EFSM in the report has to be consistent with the SystemC implementation and the FSMD schema!

		– Remember: define the EFSM and FSMD before implementing the design!

– Organization of the processes

	• 2 or 3 processes, divide controller from datapath

	• Signals for internal communication

	• Describe process dependencies and sensitivity lists

– Describe the main features of the design

	• How do you organize and use the internal signals? What about the latency?

– Justify ALL your choices: if something is not on the specification, then write it on the report!

# Prima difare il make -> export SYSTEMC_HOME=/Users/fabiofiorio/pse_libraries/systemc
## make clean e poi make
