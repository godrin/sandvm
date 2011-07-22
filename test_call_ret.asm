OUTPUT_STACK=0
CALL_STACK=2
push.a :ret_addr,:CALL_STACK
push.b 77,:CALL_STACK
push.b 33,:CALL_STACK
jmp :func
ret_addr:
pop.b :CALL_STACK,R0
push.b R0,:OUTPUT_STACK
end:
stop

func:
pop.b :CALL_STACK,R1
pop.b :CALL_STACK,R2
pop.a :CALL_STACK,R0
add.b R1,R2
push.b R2,:CALL_STACK
jmp.a R0

