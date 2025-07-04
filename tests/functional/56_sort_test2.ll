@n = global i32 zeroinitializer
define i32 @insertsort(i32 %r0)
{
L1:  
    %r7 = alloca i32
    %r6 = alloca i32
    %r2 = load i32, ptr %r1
    %r3 = load i32, ptr @n
    %r4 = load i32, ptr %r3
    %r5 = icmp slt i32 %r2,%r4
    br i1 %r5, label %L1, label %L2
    %r2 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r1
    store i32 1, ptr %r6
    %r2 = load i32, ptr %r1
    %r5 = sub i32 %r2,%r3
    store i32 %r5, ptr %r7
    br label %L3
    %r8 = load i32, ptr %r7
    %r10 = sub i32 %r0,%r9
    %r11 = load float, ptr %r10
    %r12 = icmp sgt i32 %r8,%r11
    %r13 = load float, ptr %r12
    %r7 = load i32, ptr %r6
    %r8 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r7
    %r9 = load float, ptr %r8
    %r10 = icmp slt i32 %r7,%r9
    %r11 = load float, ptr %r10
    %r12 = and i32 %r13,%r11
    br i1 %r12, label %L4, label %L5
    %r8 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r7
    %r8 = load i32, ptr %r7
    %r11 = add i32 %r8,%r9
    %r12 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r11
    store float %r8, ptr %r12
    %r8 = load i32, ptr %r7
    %r11 = sub i32 %r8,%r9
    store i32 %r11, ptr %r7
    br label %L4
L2:  
L3:  
    ret i32 1
L4:  
L5:  
L6:  
    %r8 = load i32, ptr %r7
    %r11 = add i32 %r8,%r9
    %r12 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r11
    store float %r6, ptr %r12
    %r2 = load i32, ptr %r1
    %r5 = add i32 %r2,%r3
    store i32 %r5, ptr %r1
    br label %L1
}
define i32 @main()
{
L1:  
    %r41 = alloca i32
    %r36 = alloca i32
    %r5 = alloca [10 x i32]
    %r4 = load i32, ptr @n
    store i32 1, ptr %r4
    %r8 = getelementptr [10 x i32], ptr %r5, i32 0, i32 %r7
    store float 4, ptr %r8
    %r11 = getelementptr [10 x i32], ptr %r5, i32 0, i32 %r10
    store float 1, ptr %r11
    %r14 = getelementptr [10 x i32], ptr %r5, i32 0, i32 %r13
    store float 9, ptr %r14
    %r17 = getelementptr [10 x i32], ptr %r5, i32 0, i32 %r16
    store float 2, ptr %r17
    %r20 = getelementptr [10 x i32], ptr %r5, i32 0, i32 %r19
    store float 0, ptr %r20
    %r23 = getelementptr [10 x i32], ptr %r5, i32 0, i32 %r22
    store float 1, ptr %r23
    %r26 = getelementptr [10 x i32], ptr %r5, i32 0, i32 %r25
    store float 6, ptr %r26
    %r29 = getelementptr [10 x i32], ptr %r5, i32 0, i32 %r28
    store float 5, ptr %r29
    %r32 = getelementptr [10 x i32], ptr %r5, i32 0, i32 %r31
    store float 7, ptr %r32
    %r35 = getelementptr [10 x i32], ptr %r5, i32 0, i32 %r34
    store float 8, ptr %r35
    %r6 = call i32 @insertsort(i32 %r5)
    store i32 4, ptr %r36
    br label %L6
    %r37 = load i32, ptr %r36
    %r38 = load i32, ptr @n
    %r39 = load i32, ptr %r38
    %r40 = icmp slt i32 %r37,%r39
    br i1 %r40, label %L7, label %L8
    %r37 = getelementptr [10 x i32], ptr %r5, i32 0, i32 %r36
    store i32 %r37, ptr %r41
    %r42 = call i32 @putint(i32 %r41)
    store i32 10, ptr %r41
    %r42 = call i32 @putch(i32 %r41)
    %r37 = load i32, ptr %r36
    %r40 = add i32 %r37,%r38
    store i32 %r40, ptr %r36
    br label %L7
L7:  
L8:  
L9:  
    ret i32 0
}
