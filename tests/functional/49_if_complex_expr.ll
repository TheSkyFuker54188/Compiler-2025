define i32 @main()
{
L1:  
    %r5 = call i32 @putint(i32 %r4)
    br label %L2
L3:  
    %r7 = srem i32 %r3,%r5
    %r8 = load float, ptr %r7
    %r11 = add i32 %r8,%r9
    %r12 = load float, ptr %r11
    %r15 = icmp slt i32 %r12,%r13
    %r16 = load float, ptr %r15
    %r1 = load i32, ptr %r0
    %r3 = sub i32 %r1,%r1
    %r7 = icmp ne i32 %r3,%r5
    %r8 = load float, ptr %r7
    %r6 = add i32 %r2,%r4
    %r7 = load float, ptr %r6
    %r10 = srem i32 %r7,%r8
    %r11 = load float, ptr %r10
    %r14 = icmp ne i32 %r11,%r12
    %r15 = load float, ptr %r14
    %r16 = and i32 %r8,%r15
    %r17 = load float, ptr %r16
    %r18 = xor i32 %r16,%r17
    br i1 %r18, label %L3, label %L4
    store i32 4, ptr %r4
    %r5 = call i32 @putint(i32 %r4)
    br label %L5
L4:  
L6:  
    ret i32 0
}
