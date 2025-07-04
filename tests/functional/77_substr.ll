define i32 @main()
{
L1:  
    %r73 = alloca i32
    %r72 = alloca i32
    %r45 = alloca [13 x i32]
    %r14 = alloca [15 x i32]
    %r16 = getelementptr [15 x i32], ptr %r14, i32 0, i32 0
    store i32 8, ptr %r16
    %r18 = getelementptr [15 x i32], ptr %r14, i32 0, i32 1
    store i32 2, ptr %r18
    %r20 = getelementptr [15 x i32], ptr %r14, i32 0, i32 2
    store i32 4, ptr %r20
    %r22 = getelementptr [15 x i32], ptr %r14, i32 0, i32 3
    store i32 1, ptr %r22
    %r24 = getelementptr [15 x i32], ptr %r14, i32 0, i32 4
    store i32 2, ptr %r24
    %r26 = getelementptr [15 x i32], ptr %r14, i32 0, i32 5
    store i32 7, ptr %r26
    %r28 = getelementptr [15 x i32], ptr %r14, i32 0, i32 6
    store i32 0, ptr %r28
    %r30 = getelementptr [15 x i32], ptr %r14, i32 0, i32 7
    store i32 1, ptr %r30
    %r32 = getelementptr [15 x i32], ptr %r14, i32 0, i32 8
    store i32 9, ptr %r32
    %r34 = getelementptr [15 x i32], ptr %r14, i32 0, i32 9
    store i32 3, ptr %r34
    %r36 = getelementptr [15 x i32], ptr %r14, i32 0, i32 10
    store i32 4, ptr %r36
    %r38 = getelementptr [15 x i32], ptr %r14, i32 0, i32 11
    store i32 8, ptr %r38
    %r40 = getelementptr [15 x i32], ptr %r14, i32 0, i32 12
    store i32 3, ptr %r40
    %r42 = getelementptr [15 x i32], ptr %r14, i32 0, i32 13
    store i32 7, ptr %r42
    %r44 = getelementptr [15 x i32], ptr %r14, i32 0, i32 14
    store i32 0, ptr %r44
    %r47 = getelementptr [13 x i32], ptr %r45, i32 0, i32 0
    store i32 3, ptr %r47
    %r49 = getelementptr [13 x i32], ptr %r45, i32 0, i32 1
    store i32 9, ptr %r49
    %r51 = getelementptr [13 x i32], ptr %r45, i32 0, i32 2
    store i32 7, ptr %r51
    %r53 = getelementptr [13 x i32], ptr %r45, i32 0, i32 3
    store i32 1, ptr %r53
    %r55 = getelementptr [13 x i32], ptr %r45, i32 0, i32 4
    store i32 4, ptr %r55
    %r57 = getelementptr [13 x i32], ptr %r45, i32 0, i32 5
    store i32 2, ptr %r57
    %r59 = getelementptr [13 x i32], ptr %r45, i32 0, i32 6
    store i32 4, ptr %r59
    %r61 = getelementptr [13 x i32], ptr %r45, i32 0, i32 7
    store i32 3, ptr %r61
    %r63 = getelementptr [13 x i32], ptr %r45, i32 0, i32 8
    store i32 6, ptr %r63
    %r65 = getelementptr [13 x i32], ptr %r45, i32 0, i32 9
    store i32 8, ptr %r65
    %r67 = getelementptr [13 x i32], ptr %r45, i32 0, i32 10
    store i32 0, ptr %r67
    %r69 = getelementptr [13 x i32], ptr %r45, i32 0, i32 11
    store i32 1, ptr %r69
    %r71 = getelementptr [13 x i32], ptr %r45, i32 0, i32 12
    store i32 5, ptr %r71
    %r16 = call i32 @max_sum_nonadjacent(i32 %r14,i32 %r15)
    %r17 = call i32 @putint(i32 %r16)
    %r19 = call i32 @putch(i32 %r18)
    %r47 = call i32 @longest_common_subseq(i32 %r14,i32 %r15,i32 %r45,i32 %r46)
    %r48 = call i32 @putint(float %r47)
    %r50 = call i32 @putch(i32 %r49)
    ret i32 0
}
define i32 @MAX(i32 %r0,i32 %r0)
{
L1:  
    ret i32 %r0
    br label %L2
    %r1 = load i32, ptr %r0
    %r2 = load i32, ptr %r1
    %r3 = icmp sgt i32 %r1,%r2
    br i1 %r3, label %L3, label %L4
    ret i32 %r0
    br label %L5
    ret i32 %r1
    br label %L5
L2:  
L3:  
L4:  
L5:  
L6:  
    br label %L2
}
define i32 @max_sum_nonadjacent(i32 %r0,i32 %r2)
{
L1:  
    %r16 = alloca i32
    %r4 = alloca [16 x i32]
    %r6 = getelementptr [0 x i32], ptr %r2, i32 0, i32 %r5
    %r8 = getelementptr [16 x i32], ptr %r4, i32 0, i32 %r7
    store float %r6, ptr %r8
    %r10 = getelementptr [0 x i32], ptr %r2, i32 0, i32 %r9
    %r12 = getelementptr [0 x i32], ptr %r2, i32 0, i32 %r11
    %r13 = call i32 @MAX(float %r10,float %r12)
    %r15 = getelementptr [16 x i32], ptr %r4, i32 0, i32 %r14
    store float %r13, ptr %r15
    store i32 2, ptr %r16
    br label %L6
    %r17 = load i32, ptr %r16
    %r4 = load i32, ptr %r3
    %r5 = icmp slt i32 %r17,%r4
    br i1 %r5, label %L7, label %L8
    %r17 = load i32, ptr %r16
    %r20 = sub i32 %r17,%r18
    %r21 = getelementptr [16 x i32], ptr %r4, i32 0, i32 %r20
    %r22 = load float, ptr %r21
    %r17 = getelementptr [0 x i32], ptr %r2, i32 0, i32 %r16
    %r19 = add i32 %r22,%r17
    %r17 = load i32, ptr %r16
    %r20 = sub i32 %r17,%r18
    %r21 = getelementptr [16 x i32], ptr %r4, i32 0, i32 %r20
    %r22 = call i32 @MAX(float %r19,float %r21)
    %r17 = getelementptr [16 x i32], ptr %r4, i32 0, i32 %r16
    store i32 %r22, ptr %r17
    %r17 = load i32, ptr %r16
    %r20 = add i32 %r17,%r18
    store i32 %r20, ptr %r16
    br label %L7
L7:  
L8:  
L9:  
    %r4 = load i32, ptr %r3
    %r7 = sub i32 %r4,%r5
    %r8 = getelementptr [16 x i32], ptr %r4, i32 0, i32 %r7
    ret i32 %r8
}
define i32 @longest_common_subseq(i32 %r0,i32 %r9,i32 %r2,i32 %r10)
{
L1:  
    %r15 = alloca i32
    %r14 = alloca i32
    %r13 = alloca [16 x [16 x i32]]
    store i32 1, ptr %r14
    br label %L9
    %r15 = load i32, ptr %r14
    %r11 = load i32, ptr %r10
    %r12 = icmp sle i32 %r15,%r11
    br i1 %r12, label %L10, label %L11
    store i32 1, ptr %r15
    br label %L12
    %r16 = load i32, ptr %r15
    %r13 = load i32, ptr %r12
    %r14 = icmp sle i32 %r16,%r13
    br i1 %r14, label %L13, label %L14
    %r15 = load i32, ptr %r14
    %r18 = sub i32 %r15,%r16
    %r19 = getelementptr [0 x i32], ptr %r9, i32 0, i32 %r18
    %r20 = load float, ptr %r19
    %r16 = load i32, ptr %r15
    %r19 = sub i32 %r16,%r17
    %r20 = getelementptr [0 x i32], ptr %r11, i32 0, i32 %r19
    %r21 = load float, ptr %r20
    %r22 = icmp eq i32 %r20,%r21
    br i1 %r22, label %L15, label %L16
    %r15 = load i32, ptr %r14
    %r18 = sub i32 %r15,%r16
    %r16 = load i32, ptr %r15
    %r19 = sub i32 %r16,%r17
    %r20 = getelementptr [16 x [16 x i32]], ptr %r13, i32 0, i32 %r18, i32 %r19
    %r21 = load float, ptr %r20
    %r24 = add i32 %r21,%r22
    %r16 = getelementptr [16 x [16 x i32]], ptr %r13, i32 0, i32 %r14, i32 %r15
    store i32 %r24, ptr %r16
    br label %L17
    %r15 = load i32, ptr %r14
    %r18 = sub i32 %r15,%r16
    %r16 = getelementptr [16 x [16 x i32]], ptr %r13, i32 0, i32 %r18, i32 %r15
    %r16 = load i32, ptr %r15
    %r19 = sub i32 %r16,%r17
    %r20 = getelementptr [16 x [16 x i32]], ptr %r13, i32 0, i32 %r14, i32 %r19
    %r21 = call i32 @MAX(i32 %r16,float %r20)
    %r16 = getelementptr [16 x [16 x i32]], ptr %r13, i32 0, i32 %r14, i32 %r15
    store i32 %r21, ptr %r16
    br label %L17
L10:  
L11:  
L12:  
    %r13 = getelementptr [16 x [16 x i32]], ptr %r13, i32 0, i32 %r10, i32 %r12
    ret i32 1
L13:  
L14:  
L15:  
    %r15 = load i32, ptr %r14
    %r18 = add i32 %r15,%r16
    store i32 2, ptr %r14
    br label %L10
L16:  
L17:  
L18:  
    %r16 = load i32, ptr %r15
    %r19 = add i32 %r16,%r17
    store i32 %r19, ptr %r15
    br label %L13
}
