; first line comment
mov.a :string,R0 ; after comment
mov.b 0,R1
loop:
cmp.a R0,:eof
jz.a :end
push.a *R0,0
add.a 1,R0
add.b 1,R1
jmp.a :loop
end:
stop

string:
equ "Hello You!"
eof:
