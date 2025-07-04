define i32 @main()
{
L1:  
    %r46 = alloca i32
    %r9 = alloca [53 x [59 x i32]]
    %r8 = alloca [61 x [67 x i32]]
    %r13 = getelementptr [61 x [67 x i32]], ptr %r8, i32 0, i32 %r11, i32 %r12
    store i32 0, ptr %r13
    %r17 = getelementptr [61 x [67 x i32]], ptr %r8, i32 0, i32 %r15, i32 %r16
    store float 7, ptr %r17
    %r21 = getelementptr [61 x [67 x i32]], ptr %r8, i32 0, i32 %r19, i32 %r20
    store float 4, ptr %r21
    %r25 = getelementptr [61 x [67 x i32]], ptr %r8, i32 0, i32 %r23, i32 %r24
    store float 9, ptr %r25
    %r29 = getelementptr [61 x [67 x i32]], ptr %r8, i32 0, i32 %r27, i32 %r28
    store float 11, ptr %r29
    %r33 = getelementptr [53 x [59 x i32]], ptr %r9, i32 0, i32 %r31, i32 %r32
    store float 1, ptr %r33
    %r37 = getelementptr [53 x [59 x i32]], ptr %r9, i32 0, i32 %r35, i32 %r36
    store float 2, ptr %r37
    %r41 = getelementptr [53 x [59 x i32]], ptr %r9, i32 0, i32 %r39, i32 %r40
    store float 3, ptr %r41
    %r45 = getelementptr [53 x [59 x i32]], ptr %r9, i32 0, i32 %r43, i32 %r44
    store float 9, ptr %r45
    %r49 = getelementptr [61 x [67 x i32]], ptr %r8, i32 0, i32 %r47, i32 %r48
    %r12 = getelementptr [61 x [67 x i32]], ptr %r8, i32 0, i32 %r10, i32 %r11
    %r14 = getelementptr [61 x [67 x i32]], ptr %r8, i32 0, i32 %r13
    %r17 = getelementptr [53 x [59 x i32]], ptr %r9, i32 0, i32 %r15, i32 %r16
    %r20 = getelementptr [53 x [59 x i32]], ptr %r9, i32 0, i32 %r18, i32 %r19
    %r22 = getelementptr [53 x [59 x i32]], ptr %r9, i32 0, i32 %r21
    %r25 = getelementptr [53 x [59 x i32]], ptr %r9, i32 0, i32 %r23, i32 %r24
    %r28 = getelementptr [53 x [59 x i32]], ptr %r9, i32 0, i32 %r26, i32 %r27
    %r29 = call i32 @func(float %r49,i32 %r9,i32 %r12,i32 %r14,float %r17,i32 %r20,i32 %r22,float %r25,i32 %r28)
    %r30 = load float, ptr %r29
    %r33 = mul i32 %r30,%r31
    store i32 %r33, ptr %r46
    br label %L6
    %r47 = load i32, ptr %r46
    %r50 = icmp sge i32 %r47,%r48
    br i1 %r50, label %L7, label %L8
    %r47 = getelementptr [53 x [59 x i32]], ptr %r9, i32 0, i32 %r51, i32 %r46
    %r48 = call i32 @putint(i32 %r47)
    %r50 = call i32 @putch(i32 %r49)
    %r47 = load i32, ptr %r46
    %r50 = sub i32 %r47,%r48
    store i32 %r50, ptr %r46
    br label %L7
L7:  
L8:  
L9:  
    %r48 = call i32 @putch(i32 %r47)
    ret i32 32
}
define i32 @func(i32 %r0,i32 %r0,i32 %r2,i32 %r1,i32 %r4,i32 %r2,i32 %r6,i32 %r3,i32 %r8)
{
L1:  
    %r10 = load i32, ptr %r9
    %r13 = icmp slt i32 %r10,%r11
    br i1 %r13, label %L1, label %L2
    %r10 = getelementptr [0 x i32], ptr %r1, i32 0, i32 %r0, i32 %r9
    %r11 = call i32 @putint(i32 %r10)
    %r10 = load i32, ptr %r9
    %r13 = add i32 %r10,%r11
    store i32 %r13, ptr %r9
    br label %L1
L2:  
L3:  
    %r11 = call i32 @putch(i32 %r10)
    %r3 = getelementptr [0 x i32], ptr %r3, i32 0, i32 %r2
    %r4 = call i32 @putint(i32 %r3)
    %r6 = call i32 @putch(i32 %r5)
    br label %L3
    %r9 = load i32, ptr %r8
    %r12 = icmp slt i32 %r9,%r10
    br i1 %r12, label %L4, label %L5
    %r8 = load i32, ptr %r7
    %r11 = mul i32 %r8,%r9
    %r15 = srem i32 %r11,%r13
    %r9 = getelementptr [0 x i32], ptr %r6, i32 0, i32 %r8
    store i32 %r15, ptr %r9
    %r9 = load i32, ptr %r8
    %r12 = add i32 %r9,%r10
    store i32 %r12, ptr %r8
    %r8 = load i32, ptr %r7
    %r11 = add i32 %r8,%r9
    store i32 10, ptr %r7
    br label %L4
L4:  
L5:  
L6:  
    %r5 = load i32, ptr %r4
    %r7 = add i32 %r5,%r5
    ret i32 %r7
}
