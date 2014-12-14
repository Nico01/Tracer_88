    _EXIT = 1

.SECT .TEXT

start:
    MOV AX, 8
    MOV BX, 3
    ADD AX, BX
    PUSH _EXIT
	SYS
