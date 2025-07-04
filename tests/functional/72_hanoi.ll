define float @move(i32 %r0,i32 %r0)
{
L1:  
    %r1 = call float @putint(i32 %r0)
    %r3 = call float @putch(i32 %r2)
    %r2 = call float @putint(i32 %r1)
    %r4 = call float @putch(i32 %r3)
    %r6 = call float @putch(i32 %r5)
}
define float @hanoi(i32 %r0,i32 %r7,i32 %r2,i32 %r8)
{
L1:  
    %r11 = call float @move(i32 %r8,i32 %r10)
    br label %L2
    %r8 = load i32, ptr %r7
    %r11 = sub i32 %r8,%r9
    %r10 = call float @hanoi(float %r11,i32 %r8,i32 %r10,i32 %r9)
    %r11 = call float @move(i32 %r8,i32 %r10)
    %r8 = load i32, ptr %r7
    %r11 = sub i32 %r8,%r9
    %r11 = call float @hanoi(float %r11,i32 %r9,i32 %r8,i32 %r10)
    br label %L2
L2:  
L3:  
}
define i32 @main()
{
L1:  
    %r12 = alloca i32
    %r13 = call i32 @getint()
    store i32 %r13, ptr %r12
    br label %L3
    %r13 = load i32, ptr %r12
    %r16 = icmp sgt i32 %r13,%r14
    br i1 %r16, label %L4, label %L5
    %r17 = call i32 @getint()
    %r21 = call i32 @hanoi(float %r17,i32 %r18,i32 %r19,i32 %r20)
    %r23 = call i32 @putch(i32 %r22)
    %r13 = load i32, ptr %r12
    %r16 = sub i32 %r13,%r14
    store i32 %r16, ptr %r12
    br label %L4
L4:  
L5:  
L6:  
    ret i32 0
}
