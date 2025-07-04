@g = global i32 0
define i32 @func(i32 %r0)
{
L1:  
    %r2 = load i32, ptr @g
    %r3 = load i32, ptr %r2
    %r2 = load i32, ptr %r1
    %r3 = add i32 %r3,%r2
    %r4 = load i32, ptr @g
    store i32 %r3, ptr %r4
    %r5 = load i32, ptr @g
    %r6 = call i32 @putint(i32 %r5)
    %r7 = load i32, ptr @g
    ret i32 %r7
}
define i32 @main()
{
L1:  
    store i32 1, ptr %r8
    br label %L2
    store i32 0, ptr %r8
    br label %L2
L2:  
L3:  
    %r9 = call i32 @getint()
    store i32 0, ptr %r8
    %r9 = load i32, ptr %r8
    %r12 = icmp sgt i32 %r9,%r10
    %r9 = call i32 @func(i32 %r8)
    %r11 = and i32 %r12,%r9
    br i1 %r11, label %L3, label %L4
    store i32 1, ptr %r8
    br label %L5
    store i32 0, ptr %r8
    br label %L5
L4:  
L5:  
L6:  
    %r9 = call i32 @getint()
    store i32 0, ptr %r8
    %r9 = load i32, ptr %r8
    %r12 = icmp sle i32 %r9,%r10
    %r9 = call i32 @func(i32 %r8)
    %r11 = xor i32 %r12,%r9
    br i1 %r11, label %L6, label %L7
    store i32 1, ptr %r8
    br label %L8
    store i32 0, ptr %r8
    br label %L8
L7:  
L8:  
L9:  
    %r9 = call i32 @getint()
    store i32 0, ptr %r8
    %r9 = load i32, ptr %r8
    %r12 = icmp sle i32 %r9,%r10
    %r9 = call i32 @func(i32 %r8)
    %r11 = xor i32 %r12,%r9
    br i1 %r11, label %L9, label %L10
    store i32 1, ptr %r8
    br label %L11
    store i32 0, ptr %r8
    br label %L11
L10:  
L11:  
L12:  
    %r10 = call i32 @func(i32 %r9)
    %r11 = icmp eq i32 %r10,%r0
    %r12 = load float, ptr %r11
    %r14 = call i32 @func(i32 %r13)
    %r15 = load float, ptr %r14
    %r16 = and i32 %r12,%r15
    br i1 %r16, label %L12, label %L13
    store i32 1, ptr %r8
    br label %L14
    store i32 0, ptr %r8
    br label %L14
L13:  
L14:  
L15:  
    ret i32 0
}
