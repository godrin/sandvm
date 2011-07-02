mov R0,:string
loop:
cmp R0,:eof
jz :end
push Q0,*R0
inc R0
jmp :loop
end:
stop

string:
equ "Hello You!"
eof:
