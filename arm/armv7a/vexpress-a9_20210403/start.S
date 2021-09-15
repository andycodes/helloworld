.global   _start
_start:
	mrs  r0, cpsr
	bic  r0, #0x1f
	orr  r0, #0x12
	msr  cpsr, r0
	nop
	b  end

.end
