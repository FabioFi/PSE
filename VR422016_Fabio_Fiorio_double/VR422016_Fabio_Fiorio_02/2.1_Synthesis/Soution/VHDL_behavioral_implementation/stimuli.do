vsim work.xtea

add wave clk
add wave rst
add wave input_ready
add wave output_ready
add wave mode
add wave -radix hexadecimal -color yellow word0
add wave -radix hexadecimal -color yellow word1
add wave -radix hexadecimal -color yellow result0
add wave -radix hexadecimal -color yellow result1

add wave -radix hexadecimal -color red v0
add wave -radix hexadecimal -color red v1
add wave -radix unsigned -color blue status
add wave -radix unsigned -color blue COUNTER

add wave -radix hexadecimal -color yellow KEY0
add wave -radix hexadecimal -color yellow KEY1
add wave -radix hexadecimal -color yellow KEY2
add wave -radix hexadecimal -color yellow KEY3

# Set up 100mhz clock
force clk 0 0, 1 5ns -r 10ns

force rst 0 0
force mode 0 0

force word0 16#12345678 0
force word1 16#9abcdeff 0
force KEY0 16#6a1d78c8 0
force KEY1 16#8c86d67f 0
force KEY2 16#2a65bfbe 0
force KEY3 16#b4bd6e46 0

force rst 1 0
force clk 1 0
force input_ready 1 0

run 1000

## START DECRYPTION

force rst 0 0
force mode 1 0

force word0 16#8c86d67f 0
force word1 16#6a1d78c8 0
force KEY0 16#6a1d78c8 0
force KEY1 16#8c86d67f 0
force KEY2 16#2a65bfbe 0
force KEY3 16#b4bd6e46 0

force rst 1 0
force clk 1 0
force input_ready 1 0

run 1000
