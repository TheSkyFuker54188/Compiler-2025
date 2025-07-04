@ascii_0 = global i32 48
define i32 @my_getint()
{
L1:  
    br i1 %r4, label %L1, label %L2
    %r5 = call i32 @getch()
    %r6 = load float, ptr %r5
    %r9 = sub i32 %r6,%r7
    store i32 %r9, ptr %r3
    %r4 = load i32, ptr %r3
    %r7 = icmp slt i32 %r4,%r5
    %r4 = load i32, ptr %r3
    %r7 = icmp sgt i32 %r4,%r5
    %r9 = xor i32 %r7,%r7
    br i1 %r9, label %L3, label %L4
    br label %L0
    br label %L5
    br label %L2
    br label %L5
L2:  
L3:  
    store i32 %r3, ptr %r1
    br label %L6
    br i1 %r2, label %L7, label %L8
    %r3 = call i32 @getch()
    %r4 = load i32, ptr %r3
    %r7 = sub i32 %r4,%r5
    store i32 48, ptr %r3
    %r4 = load i32, ptr %r3
    %r7 = icmp sge i32 %r4,%r5
    %r4 = load i32, ptr %r3
    %r7 = icmp sle i32 %r4,%r5
    %r9 = and i32 %r7,%r7
    br i1 %r9, label %L9, label %L10
    %r2 = load i32, ptr %r1
    %r5 = mul i32 %r2,%r3
    %r5 = add i32 %r5,%r3
    store i32 48, ptr %r1
    br label %L11
    br label %L8
    br label %L11
L4:  
L5:  
L6:  
    br label %L1
L7:  
L8:  
L9:  
    ret i32 %r1
L10:  
L11:  
L12:  
    br label %L7
}
define float @my_putint(i32 %r0)
{
L1:  
    %r4 = alloca i32
    %r3 = alloca [16 x i32]
    store i32 48, ptr %r4
    br label %L12
    %r3 = load i32, ptr %r2
    %r6 = icmp sgt i32 %r3,%r4
    br i1 %r6, label %L13, label %L14
    %r3 = load i32, ptr %r2
    %r6 = srem i32 %r3,%r4
    %r7 = load float, ptr %r6
    %r10 = add i32 %r7,%r8
    %r5 = getelementptr [16 x i32], ptr %r3, i32 0, i32 %r4
    store i32 %r10, ptr %r5
    %r3 = load i32, ptr %r2
    %r6 = sdiv i32 %r3,%r4
    store i32 %r6, ptr %r2
    %r8 = add i32 %r4,%r6
    store i32 48, ptr %r4
    br label %L13
L13:  
L14:  
L15:  
    br label %L15
    %r8 = icmp sgt i32 %r4,%r6
    br i1 %r8, label %L16, label %L17
    %r8 = sub i32 %r4,%r6
    store i32 48, ptr %r4
    %r5 = getelementptr [16 x i32], ptr %r3, i32 0, i32 %r4
    %r6 = call float @putch(i32 %r5)
    br label %L16
L16:  
L17:  
L18:  
}
define i32 @main()
{
L1:  
    %r12 = alloca i32
    %r7 = alloca i32
    %r8 = call i32 @my_getint()
    store i32 48, ptr %r7
    br label %L18
    %r8 = load i32, ptr %r7
    %r11 = icmp sgt i32 %r8,%r9
    br i1 %r11, label %L19, label %L20
    %r13 = call i32 @my_getint()
    store i32 %r13, ptr %r12
    %r13 = call i32 @my_putint(i32 %r12)
    %r15 = call i32 @putch(i32 %r14)
    %r8 = load i32, ptr %r7
    %r11 = sub i32 %r8,%r9
    store i32 %r11, ptr %r7
    br label %L19
L19:  
L20:  
L21:  
    ret i32 48
}
