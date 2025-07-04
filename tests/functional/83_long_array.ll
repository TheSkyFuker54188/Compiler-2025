@N = global i32 10000
define i32 @long_array(i32 %r0)
{
L1:  
    %r6 = load i32, ptr %r5
    %r9 = icmp slt i32 %r6,%r7
    br i1 %r9, label %L1, label %L2
    %r6 = load i32, ptr %r5
    %r6 = load i32, ptr %r5
    %r7 = mul i32 %r6,%r6
    %r11 = srem i32 %r7,%r9
    %r6 = getelementptr [10000 x i32], ptr %r2, i32 0, i32 %r5
    store i32 %r11, ptr %r6
    %r6 = load i32, ptr %r5
    %r9 = add i32 %r6,%r7
    store i32 10, ptr %r5
    br label %L1
L2:  
L3:  
    store i32 0, ptr %r5
    br label %L3
    %r6 = load i32, ptr %r5
    %r9 = icmp slt i32 %r6,%r7
    br i1 %r9, label %L4, label %L5
    %r6 = getelementptr [10000 x i32], ptr %r2, i32 0, i32 %r5
    %r7 = load i32, ptr %r6
    %r6 = getelementptr [10000 x i32], ptr %r2, i32 0, i32 %r5
    %r7 = load i32, ptr %r6
    %r8 = mul i32 %r7,%r7
    %r9 = load float, ptr %r8
    %r12 = srem i32 %r9,%r10
    %r6 = getelementptr [10000 x i32], ptr %r3, i32 0, i32 %r5
    store i32 %r12, ptr %r6
    %r6 = load i32, ptr %r5
    %r9 = add i32 %r6,%r7
    store i32 10, ptr %r5
    br label %L4
L4:  
L5:  
L6:  
    store i32 0, ptr %r5
    br label %L6
    %r6 = load i32, ptr %r5
    %r9 = icmp slt i32 %r6,%r7
    br i1 %r9, label %L7, label %L8
    %r6 = getelementptr [10000 x i32], ptr %r3, i32 0, i32 %r5
    %r7 = load i32, ptr %r6
    %r6 = getelementptr [10000 x i32], ptr %r3, i32 0, i32 %r5
    %r7 = load i32, ptr %r6
    %r8 = mul i32 %r7,%r7
    %r9 = load float, ptr %r8
    %r12 = srem i32 %r9,%r10
    %r13 = load float, ptr %r12
    %r6 = getelementptr [10000 x i32], ptr %r2, i32 0, i32 %r5
    %r7 = load i32, ptr %r6
    %r8 = add i32 %r13,%r7
    %r6 = getelementptr [10000 x i32], ptr %r4, i32 0, i32 %r5
    store i32 %r8, ptr %r6
    %r6 = load i32, ptr %r5
    %r9 = add i32 %r6,%r7
    store i32 10, ptr %r5
    br label %L7
L7:  
L8:  
L9:  
    %r10 = alloca i32
    %r6 = alloca i32
    store i32 10000, ptr %r6
    store i32 0, ptr %r5
    br label %L9
    %r6 = load i32, ptr %r5
    %r9 = icmp slt i32 %r6,%r7
    br i1 %r9, label %L10, label %L11
    %r6 = load i32, ptr %r5
    %r9 = icmp slt i32 %r6,%r7
    br i1 %r9, label %L12, label %L13
    %r7 = load i32, ptr %r6
    %r6 = getelementptr [10000 x i32], ptr %r4, i32 0, i32 %r5
    %r7 = load i32, ptr %r6
    %r8 = add i32 %r7,%r7
    %r9 = load i32, ptr %r8
    %r12 = srem i32 %r9,%r10
    store i32 %r12, ptr %r6
    %r7 = call i32 @putint(i32 %r6)
    br label %L14
    %r6 = load i32, ptr %r5
    %r9 = icmp slt i32 %r6,%r7
    br i1 %r9, label %L15, label %L16
    %r15 = sdiv i32 %r11,%r13
    store i32 %r15, ptr %r10
    br label %L18
    %r11 = load i32, ptr %r10
    %r14 = icmp slt i32 %r11,%r12
    br i1 %r14, label %L19, label %L20
    %r7 = load i32, ptr %r6
    %r6 = getelementptr [10000 x i32], ptr %r4, i32 0, i32 %r5
    %r7 = load i32, ptr %r6
    %r8 = add i32 %r7,%r7
    %r9 = load i32, ptr %r8
    %r11 = getelementptr [10000 x i32], ptr %r2, i32 0, i32 %r10
    %r12 = load i32, ptr %r11
    %r13 = sub i32 %r9,%r12
    store i32 2, ptr %r6
    %r11 = load i32, ptr %r10
    %r14 = add i32 %r11,%r12
    store i32 %r14, ptr %r10
    br label %L19
L10:  
L11:  
L12:  
    ret i32 %r6
L13:  
L14:  
L15:  
    %r6 = load i32, ptr %r5
    %r9 = add i32 %r6,%r7
    store i32 10, ptr %r5
    br label %L10
L16:  
L17:  
L18:  
    br label %L14
L19:  
L20:  
L21:  
    %r10 = alloca i32
    %r7 = call i32 @putint(i32 %r6)
    br label %L17
    %r6 = load i32, ptr %r5
    %r9 = icmp slt i32 %r6,%r7
    br i1 %r9, label %L21, label %L22
    %r15 = sdiv i32 %r11,%r13
    store i32 %r15, ptr %r10
    br label %L24
    %r11 = load i32, ptr %r10
    %r14 = icmp slt i32 %r11,%r12
    br i1 %r14, label %L25, label %L26
    %r11 = load i32, ptr %r10
    %r14 = icmp sgt i32 %r11,%r12
    br i1 %r14, label %L27, label %L28
    %r7 = load i32, ptr %r6
    %r6 = getelementptr [10000 x i32], ptr %r3, i32 0, i32 %r5
    %r7 = load i32, ptr %r6
    %r8 = add i32 %r7,%r7
    %r9 = load i32, ptr %r8
    %r11 = getelementptr [10000 x i32], ptr %r2, i32 0, i32 %r10
    %r12 = load i32, ptr %r11
    %r13 = sub i32 %r9,%r12
    store i32 2, ptr %r6
    %r11 = load i32, ptr %r10
    %r14 = add i32 %r11,%r12
    store i32 %r14, ptr %r10
    br label %L29
    %r7 = load i32, ptr %r6
    %r6 = getelementptr [10000 x i32], ptr %r2, i32 0, i32 %r5
    %r7 = load i32, ptr %r6
    %r8 = add i32 %r7,%r7
    %r9 = load i32, ptr %r8
    %r11 = getelementptr [10000 x i32], ptr %r4, i32 0, i32 %r10
    %r12 = load i32, ptr %r11
    %r13 = add i32 %r9,%r12
    %r14 = load i32, ptr %r13
    %r17 = srem i32 %r14,%r15
    store i32 %r17, ptr %r6
    %r11 = load i32, ptr %r10
    %r14 = add i32 %r11,%r12
    store i32 %r14, ptr %r10
    br label %L29
L22:  
L23:  
L24:  
    br label %L17
L25:  
L26:  
L27:  
    %r7 = call i32 @putint(i32 %r6)
    br label %L23
    %r7 = load i32, ptr %r6
    %r6 = getelementptr [10000 x i32], ptr %r4, i32 0, i32 %r5
    %r7 = load i32, ptr %r6
    %r2 = load i32, ptr %r1
    %r3 = mul i32 %r7,%r2
    %r4 = load i32, ptr %r3
    %r5 = add i32 %r7,%r4
    %r6 = load i32, ptr %r5
    %r9 = srem i32 %r6,%r7
    store i32 10, ptr %r6
    br label %L23
L28:  
L29:  
L30:  
    br label %L25
}
define i32 @main()
{
L1:  
    %r8 = call i32 @long_array(i32 %r7)
    ret i32 0
}
