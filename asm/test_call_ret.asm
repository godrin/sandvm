OUTPUT_STACK=0
CALL_STACK=2
pushp.b 97,0
pushs.a :ret_addr,:CALL_STACK
pushs.b 77,:CALL_STACK
pushs.b 33,:CALL_STACK
jmp :func
ret_addr:
pops.b :CALL_STACK,R0
pushs.b R0,:OUTPUT_STACK
end:
stop

func:
pops.b :CALL_STACK,R1
assert.b R1,33
pops.b :CALL_STACK,R2
assert.b R2,77
pops.a :CALL_STACK,R0
assert.a R0,:ret_addr
add.b R1,R2
pushp.b 'A',0
pushs.b R2,:CALL_STACK
jmp.a R0

