

STP X1, X0, [SP, #-0x10]; push x1,x0 to stack to protect x0 (x1 just Alignment 16bytes)
LDR X0, 8; new func address
BR X0; jump func

[TARGET_ADDRESS] (64bit)
LDR X0, [SP, -0x8]; backup x0

