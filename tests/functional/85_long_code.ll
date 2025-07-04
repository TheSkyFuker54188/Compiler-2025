@n = global i32 zeroinitializer
define i32 @bubblesort(i32 %r0)
{
L1:  
    %r10 = alloca i32
    %r2 = load i32, ptr %r1
    %r3 = load i32, ptr @n
    %r4 = load i32, ptr %r3
    %r7 = sub i32 %r4,%r5
    %r8 = load float, ptr %r7
    %r9 = icmp slt i32 %r2,%r8
    br i1 %r9, label %L1, label %L2
    store i32 0, ptr %r2
    br label %L3
    %r3 = load i32, ptr %r2
    %r4 = load i32, ptr @n
    %r5 = load i32, ptr %r4
    %r2 = load i32, ptr %r1
    %r3 = sub i32 %r5,%r2
    %r4 = load i32, ptr %r3
    %r7 = sub i32 %r4,%r5
    %r8 = load float, ptr %r7
    %r9 = icmp slt i32 %r3,%r8
    br i1 %r9, label %L4, label %L5
    %r3 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r2
    %r4 = load i32, ptr %r3
    %r3 = load i32, ptr %r2
    %r6 = add i32 %r3,%r4
    %r7 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r6
    %r8 = load float, ptr %r7
    %r9 = icmp sgt i32 %r4,%r8
    br i1 %r9, label %L6, label %L7
    %r3 = load i32, ptr %r2
    %r6 = add i32 %r3,%r4
    %r7 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r6
    store i32 %r7, ptr %r10
    %r3 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r2
    %r3 = load i32, ptr %r2
    %r6 = add i32 %r3,%r4
    %r7 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r6
    store float %r3, ptr %r7
    %r3 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r2
    store i32 %r10, ptr %r3
    br label %L8
L2:  
L3:  
    ret i32 0
L4:  
L5:  
L6:  
    %r2 = load i32, ptr %r1
    %r5 = add i32 %r2,%r3
    store i32 1, ptr %r1
    br label %L1
L7:  
L9:  
    %r3 = load i32, ptr %r2
    %r6 = add i32 %r3,%r4
    store i32 %r6, ptr %r2
    br label %L4
}
define i32 @getMost(i32 %r0)
{
L1:  
    %r20 = alloca i32
    %r19 = alloca [1000 x i32]
    store i32 0, ptr %r20
    br label %L36
    %r21 = load i32, ptr %r20
    %r24 = icmp slt i32 %r21,%r22
    br i1 %r24, label %L37, label %L38
    %r21 = getelementptr [1000 x i32], ptr %r19, i32 0, i32 %r20
    store i32 2, ptr %r21
    %r21 = load i32, ptr %r20
    %r24 = add i32 %r21,%r22
    store i32 %r24, ptr %r20
    br label %L37
L37:  
L38:  
L39:  
    %r25 = alloca i32
    %r22 = alloca i32
    %r21 = alloca i32
    store i32 0, ptr %r20
    store i32 0, ptr %r21
    br label %L39
    %r21 = load i32, ptr %r20
    %r22 = load i32, ptr @n
    %r23 = load i32, ptr %r22
    %r24 = icmp slt i32 %r21,%r23
    br i1 %r24, label %L40, label %L41
    %r21 = getelementptr [0 x i32], ptr %r18, i32 0, i32 %r20
    store i32 %r21, ptr %r25
    %r26 = getelementptr [1000 x i32], ptr %r19, i32 0, i32 %r25
    %r27 = load i32, ptr %r26
    %r30 = add i32 %r27,%r28
    %r26 = getelementptr [1000 x i32], ptr %r19, i32 0, i32 %r25
    store i32 2, ptr %r26
    %r26 = getelementptr [1000 x i32], ptr %r19, i32 0, i32 %r25
    %r27 = load i32, ptr %r26
    %r22 = load i32, ptr %r21
    %r23 = icmp sgt i32 %r27,%r22
    br i1 %r23, label %L42, label %L43
    %r26 = getelementptr [1000 x i32], ptr %r19, i32 0, i32 %r25
    store i32 %r26, ptr %r21
    store i32 %r25, ptr %r22
    br label %L44
L40:  
L41:  
L42:  
    ret i32 1
L43:  
L45:  
    %r21 = load i32, ptr %r20
    %r24 = add i32 %r21,%r22
    store i32 %r24, ptr %r20
    br label %L40
}
define i32 @insertsort(i32 %r0)
{
L1:  
    %r10 = alloca i32
    %r9 = alloca i32
    %r4 = alloca i32
    store i32 1, ptr %r4
    br label %L9
    %r5 = load i32, ptr %r4
    %r6 = load i32, ptr @n
    %r7 = load i32, ptr %r6
    %r8 = icmp slt i32 %r5,%r7
    br i1 %r8, label %L10, label %L11
    %r5 = getelementptr [0 x i32], ptr %r3, i32 0, i32 %r4
    store i32 1, ptr %r9
    %r5 = load i32, ptr %r4
    %r8 = sub i32 %r5,%r6
    store i32 %r8, ptr %r10
    br label %L12
    %r11 = load i32, ptr %r10
    %r13 = sub i32 %r0,%r12
    %r14 = load float, ptr %r13
    %r15 = icmp sgt i32 %r11,%r14
    %r16 = load float, ptr %r15
    %r10 = load i32, ptr %r9
    %r11 = getelementptr [0 x i32], ptr %r3, i32 0, i32 %r10
    %r12 = load float, ptr %r11
    %r13 = icmp slt i32 %r10,%r12
    %r14 = load float, ptr %r13
    %r15 = and i32 %r16,%r14
    br i1 %r15, label %L13, label %L14
    %r11 = getelementptr [0 x i32], ptr %r3, i32 0, i32 %r10
    %r11 = load i32, ptr %r10
    %r14 = add i32 %r11,%r12
    %r15 = getelementptr [0 x i32], ptr %r3, i32 0, i32 %r14
    store float %r11, ptr %r15
    %r11 = load i32, ptr %r10
    %r14 = sub i32 %r11,%r12
    store i32 %r14, ptr %r10
    br label %L13
L10:  
L11:  
L12:  
    ret i32 1
L13:  
L14:  
L15:  
    %r11 = load i32, ptr %r10
    %r14 = add i32 %r11,%r12
    %r15 = getelementptr [0 x i32], ptr %r3, i32 0, i32 %r14
    store float %r9, ptr %r15
    %r5 = load i32, ptr %r4
    %r8 = add i32 %r5,%r6
    store i32 %r8, ptr %r4
    br label %L10
}
define i32 @QuickSort(i32 %r0,i32 %r6,i32 %r2)
{
L1:  
    %r13 = alloca i32
    %r12 = alloca i32
    %r11 = alloca i32
    %r8 = load i32, ptr %r7
    %r9 = load i32, ptr %r8
    %r10 = icmp slt i32 %r8,%r9
    br i1 %r10, label %L15, label %L16
    store i32 %r7, ptr %r11
    store i32 %r8, ptr %r12
    %r8 = getelementptr [0 x i32], ptr %r6, i32 0, i32 %r7
    store i32 %r8, ptr %r13
    br label %L18
    %r12 = load i32, ptr %r11
    %r13 = load i32, ptr %r12
    %r14 = icmp slt i32 %r12,%r13
    br i1 %r14, label %L19, label %L20
    br label %L21
    %r12 = load i32, ptr %r11
    %r13 = load i32, ptr %r12
    %r14 = icmp slt i32 %r12,%r13
    %r15 = load float, ptr %r14
    %r13 = getelementptr [0 x i32], ptr %r6, i32 0, i32 %r12
    %r14 = load i32, ptr %r13
    %r14 = load i32, ptr %r13
    %r17 = sub i32 %r14,%r15
    %r18 = load float, ptr %r17
    %r19 = icmp sgt i32 %r14,%r18
    %r20 = load float, ptr %r19
    %r21 = and i32 %r15,%r20
    br i1 %r21, label %L22, label %L23
    %r13 = load i32, ptr %r12
    %r16 = sub i32 %r13,%r14
    store i32 %r16, ptr %r12
    br label %L22
L16:  
L18:  
    ret i32 1
L19:  
L20:  
L21:  
    %r13 = alloca i32
    %r12 = getelementptr [0 x i32], ptr %r6, i32 0, i32 %r11
    store i32 1, ptr %r12
    %r12 = load i32, ptr %r11
    %r15 = sub i32 %r12,%r13
    store i32 1, ptr %r13
    %r14 = call i32 @QuickSort(i32 %r6,i32 %r7,i32 %r13)
    store i32 1, ptr %r13
    %r12 = load i32, ptr %r11
    %r15 = add i32 %r12,%r13
    store i32 1, ptr %r13
    %r9 = call i32 @QuickSort(i32 %r6,i32 %r13,i32 %r8)
    store i32 %r9, ptr %r13
    br label %L17
L22:  
L23:  
L24:  
    %r12 = load i32, ptr %r11
    %r13 = load i32, ptr %r12
    %r14 = icmp slt i32 %r12,%r13
    br i1 %r14, label %L24, label %L25
    %r13 = getelementptr [0 x i32], ptr %r6, i32 0, i32 %r12
    %r12 = getelementptr [0 x i32], ptr %r6, i32 0, i32 %r11
    store i32 %r13, ptr %r12
    %r12 = load i32, ptr %r11
    %r15 = add i32 %r12,%r13
    store i32 1, ptr %r11
    br label %L26
L25:  
L27:  
    br label %L27
    %r12 = load i32, ptr %r11
    %r13 = load i32, ptr %r12
    %r14 = icmp slt i32 %r12,%r13
    %r12 = getelementptr [0 x i32], ptr %r6, i32 0, i32 %r11
    %r13 = load i32, ptr %r12
    %r15 = icmp slt i32 %r13,%r13
    %r17 = and i32 %r14,%r15
    br i1 %r17, label %L28, label %L29
    %r12 = load i32, ptr %r11
    %r15 = add i32 %r12,%r13
    store i32 1, ptr %r11
    br label %L28
L28:  
L29:  
L30:  
    %r12 = load i32, ptr %r11
    %r13 = load i32, ptr %r12
    %r14 = icmp slt i32 %r12,%r13
    br i1 %r14, label %L30, label %L31
    %r12 = getelementptr [0 x i32], ptr %r6, i32 0, i32 %r11
    %r13 = getelementptr [0 x i32], ptr %r6, i32 0, i32 %r12
    store i32 %r12, ptr %r13
    %r13 = load i32, ptr %r12
    %r16 = sub i32 %r13,%r14
    store i32 %r16, ptr %r12
    br label %L32
L31:  
L33:  
    br label %L19
}
define i32 @getMid(i32 %r0)
{
L1:  
    %r16 = alloca i32
    %r17 = load i32, ptr @n
    %r18 = load i32, ptr %r17
    %r21 = srem i32 %r18,%r19
    %r22 = load float, ptr %r21
    %r25 = icmp eq i32 %r22,%r23
    br i1 %r25, label %L33, label %L34
    %r26 = load i32, ptr @n
    %r27 = load i32, ptr %r26
    %r30 = sdiv i32 %r27,%r28
    store i32 %r30, ptr %r16
    %r17 = getelementptr [0 x i32], ptr %r15, i32 0, i32 %r16
    %r18 = load i32, ptr %r17
    %r17 = load i32, ptr %r16
    %r20 = sub i32 %r17,%r18
    %r21 = getelementptr [0 x i32], ptr %r15, i32 0, i32 %r20
    %r22 = load float, ptr %r21
    %r23 = add i32 %r18,%r22
    %r27 = sdiv i32 %r23,%r25
    ret i32 %r27
    br label %L35
    %r28 = load i32, ptr @n
    %r29 = load i32, ptr %r28
    %r32 = sdiv i32 %r29,%r30
    store i32 %r32, ptr %r16
    %r17 = getelementptr [0 x i32], ptr %r15, i32 0, i32 %r16
    ret i32 %r17
    br label %L35
L34:  
L35:  
L36:  
}
define i32 @revert(i32 %r0)
{
L1:  
    %r26 = alloca i32
    %r25 = alloca i32
    %r24 = alloca i32
    store i32 0, ptr %r25
    store i32 0, ptr %r26
    br label %L45
    %r26 = load i32, ptr %r25
    %r28 = icmp slt i32 %r26,%r26
    br i1 %r28, label %L46, label %L47
    %r26 = getelementptr [0 x i32], ptr %r23, i32 0, i32 %r25
    store i32 0, ptr %r24
    %r27 = getelementptr [0 x i32], ptr %r23, i32 0, i32 %r26
    %r26 = getelementptr [0 x i32], ptr %r23, i32 0, i32 %r25
    store i32 0, ptr %r26
    %r27 = getelementptr [0 x i32], ptr %r23, i32 0, i32 %r26
    store i32 %r24, ptr %r27
    %r26 = load i32, ptr %r25
    %r29 = add i32 %r26,%r27
    store i32 %r29, ptr %r25
    %r30 = sub i32 %r26,%r28
    store i32 2, ptr %r26
    br label %L46
L46:  
L47:  
L48:  
    ret i32 0
}
define i32 @arrCopy(i32 %r0,i32 %r28)
{
L1:  
    %r30 = alloca i32
    store i32 0, ptr %r30
    br label %L48
    %r31 = load i32, ptr %r30
    %r32 = load i32, ptr @n
    %r33 = load i32, ptr %r32
    %r34 = icmp slt i32 %r31,%r33
    br i1 %r34, label %L49, label %L50
    %r31 = getelementptr [0 x i32], ptr %r28, i32 0, i32 %r30
    %r31 = getelementptr [0 x i32], ptr %r29, i32 0, i32 %r30
    store i32 0, ptr %r31
    %r31 = load i32, ptr %r30
    %r34 = add i32 %r31,%r32
    store i32 %r34, ptr %r30
    br label %L49
L49:  
L50:  
L51:  
    ret i32 0
}
define i32 @calSum(i32 %r0,i32 %r32)
{
L1:  
    %r35 = alloca i32
    %r34 = alloca i32
    store i32 0, ptr %r34
    store i32 0, ptr %r35
    br label %L51
    %r36 = load i32, ptr %r35
    %r37 = load i32, ptr @n
    %r38 = load i32, ptr %r37
    %r39 = icmp slt i32 %r36,%r38
    br i1 %r39, label %L52, label %L53
    %r35 = load i32, ptr %r34
    %r36 = getelementptr [0 x i32], ptr %r32, i32 0, i32 %r35
    %r38 = add i32 %r35,%r36
    store i32 %r38, ptr %r34
    %r36 = load i32, ptr %r35
    %r34 = load i32, ptr %r33
    %r35 = srem i32 %r36,%r34
    %r36 = load i32, ptr %r35
    %r34 = load i32, ptr %r33
    %r37 = sub i32 %r34,%r35
    %r38 = load i32, ptr %r37
    %r39 = icmp ne i32 %r36,%r38
    br i1 %r39, label %L54, label %L55
    %r36 = getelementptr [0 x i32], ptr %r32, i32 0, i32 %r35
    store i32 0, ptr %r36
    br label %L56
    %r36 = getelementptr [0 x i32], ptr %r32, i32 0, i32 %r35
    store i32 %r34, ptr %r36
    store i32 0, ptr %r34
    br label %L56
L52:  
L53:  
L54:  
    ret i32 0
L55:  
L56:  
L57:  
    %r39 = add i32 %r35,%r37
    store i32 %r39, ptr %r35
    br label %L52
}
define i32 @avgPooling(i32 %r0,i32 %r37)
{
L1:  
    %r40 = alloca i32
    %r40 = alloca i32
    %r39 = alloca i32
    store i32 0, ptr %r40
    store i32 0, ptr %r39
    br label %L57
    %r41 = load i32, ptr %r40
    %r42 = load i32, ptr @n
    %r43 = load i32, ptr %r42
    %r44 = icmp slt i32 %r41,%r43
    br i1 %r44, label %L58, label %L59
    %r41 = load i32, ptr %r40
    %r39 = load i32, ptr %r38
    %r42 = sub i32 %r39,%r40
    %r43 = load i32, ptr %r42
    %r44 = icmp slt i32 %r41,%r43
    br i1 %r44, label %L60, label %L61
    %r40 = load i32, ptr %r39
    %r41 = getelementptr [0 x i32], ptr %r37, i32 0, i32 %r40
    %r43 = add i32 %r40,%r41
    store i32 %r43, ptr %r39
    br label %L62
    %r39 = load i32, ptr %r38
    %r42 = sub i32 %r39,%r40
    %r43 = load i32, ptr %r42
    %r44 = icmp eq i32 %r40,%r43
    br i1 %r44, label %L63, label %L64
    %r46 = getelementptr [0 x i32], ptr %r37, i32 0, i32 %r45
    store i32 %r46, ptr %r40
    %r40 = load i32, ptr %r39
    %r39 = load i32, ptr %r38
    %r40 = sdiv i32 %r40,%r39
    %r42 = getelementptr [0 x i32], ptr %r37, i32 0, i32 %r41
    store i32 1, ptr %r42
    br label %L65
    %r40 = load i32, ptr %r39
    %r41 = getelementptr [0 x i32], ptr %r37, i32 0, i32 %r40
    %r43 = add i32 %r40,%r41
    %r44 = load float, ptr %r43
    %r42 = sub i32 %r44,%r40
    store i32 %r42, ptr %r39
    %r39 = load i32, ptr %r38
    %r40 = sub i32 %r40,%r39
    %r44 = add i32 %r40,%r42
    %r45 = getelementptr [0 x i32], ptr %r37, i32 0, i32 %r44
    store i32 0, ptr %r40
    %r40 = load i32, ptr %r39
    %r39 = load i32, ptr %r38
    %r40 = sdiv i32 %r40,%r39
    %r39 = load i32, ptr %r38
    %r40 = sub i32 %r40,%r39
    %r44 = add i32 %r40,%r42
    %r45 = getelementptr [0 x i32], ptr %r37, i32 0, i32 %r44
    store i32 1, ptr %r45
    br label %L65
L58:  
L59:  
L60:  
    %r41 = load i32, ptr @n
    %r42 = load i32, ptr %r41
    %r39 = load i32, ptr %r38
    %r40 = sub i32 %r42,%r39
    %r44 = add i32 %r40,%r42
    store i32 %r44, ptr %r40
    br label %L66
    %r42 = load i32, ptr @n
    %r43 = load i32, ptr %r42
    %r44 = icmp slt i32 %r40,%r43
    br i1 %r44, label %L67, label %L68
    %r41 = getelementptr [0 x i32], ptr %r37, i32 0, i32 %r40
    store i32 0, ptr %r41
    %r44 = add i32 %r40,%r42
    store i32 %r44, ptr %r40
    br label %L67
L61:  
L62:  
L63:  
    %r44 = add i32 %r40,%r42
    store i32 %r44, ptr %r40
    br label %L58
L64:  
L65:  
L66:  
    br label %L62
L67:  
L68:  
L69:  
    ret i32 0
}
define i32 @main()
{
L1:  
    %r143 = alloca i32
    %r142 = alloca i32
    %r45 = alloca [32 x i32]
    %r44 = alloca [32 x i32]
    %r43 = load i32, ptr @n
    store i32 1, ptr %r43
    %r48 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r47
    store float 7, ptr %r48
    %r51 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r50
    store float 23, ptr %r51
    %r54 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r53
    store float 89, ptr %r54
    %r57 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r56
    store float 26, ptr %r57
    %r60 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r59
    store float 282, ptr %r60
    %r63 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r62
    store float 254, ptr %r63
    %r66 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r65
    store float 27, ptr %r66
    %r69 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r68
    store float 5, ptr %r69
    %r72 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r71
    store float 83, ptr %r72
    %r75 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r74
    store float 273, ptr %r75
    %r78 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r77
    store float 574, ptr %r78
    %r81 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r80
    store float 905, ptr %r81
    %r84 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r83
    store float 354, ptr %r84
    %r87 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r86
    store float 657, ptr %r87
    %r90 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r89
    store float 935, ptr %r90
    %r93 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r92
    store float 264, ptr %r93
    %r96 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r95
    store float 639, ptr %r96
    %r99 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r98
    store float 459, ptr %r99
    %r102 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r101
    store float 29, ptr %r102
    %r105 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r104
    store float 68, ptr %r105
    %r108 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r107
    store float 929, ptr %r108
    %r111 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r110
    store float 756, ptr %r111
    %r114 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r113
    store float 452, ptr %r114
    %r117 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r116
    store float 279, ptr %r117
    %r120 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r119
    store float 58, ptr %r120
    %r123 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r122
    store float 87, ptr %r123
    %r126 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r125
    store float 96, ptr %r126
    %r129 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r128
    store float 36, ptr %r129
    %r132 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r131
    store float 39, ptr %r132
    %r135 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r134
    store float 28, ptr %r135
    %r138 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r137
    store float 1, ptr %r138
    %r141 = getelementptr [32 x i32], ptr %r44, i32 0, i32 %r140
    store float 290, ptr %r141
    %r46 = call i32 @arrCopy(i32 %r44,i32 %r45)
    store i32 7, ptr %r142
    %r46 = call i32 @revert(i32 %r45)
    store i32 7, ptr %r142
    store i32 0, ptr %r143
    br label %L69
    %r144 = load i32, ptr %r143
    %r147 = icmp slt i32 %r144,%r145
    br i1 %r147, label %L70, label %L71
    %r144 = getelementptr [32 x i32], ptr %r45, i32 0, i32 %r143
    store i32 0, ptr %r142
    %r143 = call i32 @putint(i32 %r142)
    %r144 = load i32, ptr %r143
    %r147 = add i32 %r144,%r145
    store i32 %r147, ptr %r143
    br label %L70
L70:  
L71:  
L72:  
    %r46 = call i32 @bubblesort(i32 %r45)
    store i32 7, ptr %r142
    store i32 0, ptr %r143
    br label %L72
    %r147 = icmp slt i32 %r143,%r145
    br i1 %r147, label %L73, label %L74
    %r144 = getelementptr [32 x i32], ptr %r45, i32 0, i32 %r143
    store i32 0, ptr %r142
    %r143 = call i32 @putint(i32 %r142)
    %r147 = add i32 %r143,%r145
    store i32 %r147, ptr %r143
    br label %L73
L73:  
L74:  
L75:  
    %r46 = call i32 @getMid(i32 %r45)
    store i32 7, ptr %r142
    %r143 = call i32 @putint(i32 %r142)
    %r46 = call i32 @getMost(i32 %r45)
    store i32 7, ptr %r142
    %r143 = call i32 @putint(i32 %r142)
    %r46 = call i32 @arrCopy(i32 %r44,i32 %r45)
    store i32 7, ptr %r142
    %r46 = call i32 @bubblesort(i32 %r45)
    store i32 7, ptr %r142
    store i32 0, ptr %r143
    br label %L75
    %r147 = icmp slt i32 %r143,%r145
    br i1 %r147, label %L76, label %L77
    %r144 = getelementptr [32 x i32], ptr %r45, i32 0, i32 %r143
    store i32 0, ptr %r142
    %r143 = call i32 @putint(i32 %r142)
    %r147 = add i32 %r143,%r145
    store i32 %r147, ptr %r143
    br label %L76
L76:  
L77:  
L78:  
    %r46 = call i32 @arrCopy(i32 %r44,i32 %r45)
    store i32 7, ptr %r142
    %r46 = call i32 @insertsort(i32 %r45)
    store i32 7, ptr %r142
    store i32 0, ptr %r143
    br label %L78
    %r147 = icmp slt i32 %r143,%r145
    br i1 %r147, label %L79, label %L80
    %r144 = getelementptr [32 x i32], ptr %r45, i32 0, i32 %r143
    store i32 0, ptr %r142
    %r143 = call i32 @putint(i32 %r142)
    %r147 = add i32 %r143,%r145
    store i32 %r147, ptr %r143
    br label %L79
L79:  
L80:  
L81:  
    %r46 = call i32 @arrCopy(i32 %r44,i32 %r45)
    store i32 7, ptr %r142
    store i32 0, ptr %r143
    store i32 0, ptr %r142
    %r143 = call i32 @QuickSort(i32 %r45,i32 %r143,i32 %r142)
    store i32 0, ptr %r142
    br label %L81
    %r147 = icmp slt i32 %r143,%r145
    br i1 %r147, label %L82, label %L83
    %r144 = getelementptr [32 x i32], ptr %r45, i32 0, i32 %r143
    store i32 0, ptr %r142
    %r143 = call i32 @putint(i32 %r142)
    %r147 = add i32 %r143,%r145
    store i32 %r147, ptr %r143
    br label %L82
L82:  
L83:  
L84:  
    %r46 = call i32 @arrCopy(i32 %r44,i32 %r45)
    store i32 7, ptr %r142
    %r47 = call i32 @calSum(i32 %r45,i32 %r46)
    store i32 0, ptr %r142
    store i32 0, ptr %r143
    br label %L84
    %r147 = icmp slt i32 %r143,%r145
    br i1 %r147, label %L85, label %L86
    %r144 = getelementptr [32 x i32], ptr %r45, i32 0, i32 %r143
    store i32 0, ptr %r142
    %r143 = call i32 @putint(i32 %r142)
    %r147 = add i32 %r143,%r145
    store i32 %r147, ptr %r143
    br label %L85
L85:  
L86:  
L87:  
    %r46 = call i32 @arrCopy(i32 %r44,i32 %r45)
    store i32 7, ptr %r142
    %r47 = call i32 @avgPooling(i32 %r45,i32 %r46)
    store i32 0, ptr %r142
    store i32 0, ptr %r143
    br label %L87
    %r147 = icmp slt i32 %r143,%r145
    br i1 %r147, label %L88, label %L89
    %r144 = getelementptr [32 x i32], ptr %r45, i32 0, i32 %r143
    store i32 0, ptr %r142
    %r143 = call i32 @putint(i32 %r142)
    %r147 = add i32 %r143,%r145
    store i32 %r147, ptr %r143
    br label %L88
L88:  
L89:  
L90:  
    ret i32 0
}
