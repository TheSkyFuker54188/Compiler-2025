define i32 @main()
{
L1:  
    %r1 = icmp eq i32 %r0,%r0
    %r5 = add i32 %r1,%r3
    %r7 = xor i32 %r8,%r5
    br i1 %r7, label %L3, label %L4
    %r5 = load i32, ptr %r4
    %r8 = icmp eq i32 %r5,%r6
    %r10 = add i32 %r6,%r8
    %r11 = load i32, ptr %r10
    %r14 = icmp sgt i32 %r11,%r12
    %r15 = load float, ptr %r14
    %r16 = and i32 %r8,%r15
    br i1 %r16, label %L6, label %L7
    ret i32 3
    br label %L8
    %r11 = load i32, ptr %r10
    %r5 = load i32, ptr %r4
    %r6 = srem i32 %r11,%r5
    %r10 = and i32 %r6,%r8
    br i1 %r10, label %L9, label %L10
    ret i32 6
    br label %L11
    %r3 = load i32, ptr %r2
    %r4 = sdiv i32 %r6,%r3
    %r5 = load i32, ptr %r4
    %r1 = load i32, ptr %r0
    %r2 = add i32 %r5,%r1
    %r3 = load i32, ptr %r2
    %r6 = icmp sge i32 %r3,%r4
    br i1 %r6, label %L12, label %L13
    %r11 = load i32, ptr %r10
    %r12 = sub i32 %r8,%r11
    %r16 = icmp sge i32 %r12,%r14
    %r17 = load float, ptr %r16
    %r10 = icmp sgt i32 %r6,%r8
    %r11 = load i32, ptr %r10
    %r12 = xor i32 %r17,%r11
    br i1 %r12, label %L15, label %L16
    ret i32 6
    br label %L17
    %r11 = load i32, ptr %r10
    %r12 = icmp ne i32 %r4,%r11
    br i1 %r12, label %L18, label %L19
    %r3 = load i32, ptr %r2
    %r8 = mul i32 %r8,%r6
    %r10 = add i32 %r3,%r8
    %r11 = load i32, ptr %r10
    %r14 = icmp sgt i32 %r11,%r12
    br i1 %r14, label %L21, label %L22
    %r11 = icmp eq i32 %r10,%r0
    br i1 %r11, label %L24, label %L25
    ret i32 2
    br label %L26
    ret i32 6
    br label %L26
L2:  
L3:  
L4:  
L5:  
L6:  
    br label %L2
    ret i32 1
    br label %L2
L7:  
L8:  
L9:  
    br label %L5
    ret i32 3
    br label %L5
L10:  
L11:  
L12:  
    br label %L8
L13:  
L14:  
L15:  
    br label %L11
L16:  
L17:  
L18:  
    br label %L14
    ret i32 5
    br label %L14
L19:  
L20:  
L21:  
    br label %L17
L22:  
L23:  
L24:  
    br label %L20
    ret i32 7
    br label %L20
L25:  
L26:  
L27:  
    br label %L23
    ret i32 0
    br label %L23
}
