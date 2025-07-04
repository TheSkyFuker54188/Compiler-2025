@arr1 = global [10x [2x [3x [4x [5x [6x [2x i32]]]]]]] zeroinitializer
@arr2 = global [10x [2x [3x [2x [4x [8x [7x i32]]]]]]] zeroinitializer
define float @loop1(i32 %r0,i32 %r0)
{
L1:  
    %r3 = load i32, ptr %r2
    %r1 = load i32, ptr %r0
    %r2 = icmp slt i32 %r3,%r1
    %r3 = load i32, ptr %r2
    %r3 = load i32, ptr %r2
    %r2 = load i32, ptr %r1
    %r3 = icmp slt i32 %r3,%r2
    %r4 = load i32, ptr %r3
    %r5 = and i32 %r3,%r4
    br i1 %r5, label %L1, label %L2
    store i32 0, ptr %r3
    br label %L3
    %r4 = load i32, ptr %r3
    %r7 = icmp slt i32 %r4,%r5
    br i1 %r7, label %L4, label %L5
    store i32 0, ptr %r4
    br label %L6
    %r5 = load i32, ptr %r4
    %r8 = icmp slt i32 %r5,%r6
    br i1 %r8, label %L7, label %L8
    store i32 0, ptr %r5
    br label %L9
    %r9 = icmp slt i32 %r5,%r7
    br i1 %r9, label %L10, label %L11
    store i32 0, ptr %r6
    br label %L12
    %r10 = icmp slt i32 %r6,%r8
    br i1 %r10, label %L13, label %L14
    store i32 0, ptr %r7
    br label %L15
    %r11 = icmp slt i32 %r7,%r9
    br i1 %r11, label %L16, label %L17
    store i32 0, ptr %r8
    br label %L18
    %r12 = icmp slt i32 %r8,%r10
    br i1 %r12, label %L19, label %L20
    %r3 = load i32, ptr %r2
    %r4 = load i32, ptr %r3
    %r5 = add i32 %r3,%r4
    %r5 = load i32, ptr %r4
    %r6 = add i32 %r5,%r5
    %r7 = add i32 %r6,%r5
    %r8 = add i32 %r7,%r6
    %r9 = add i32 %r8,%r7
    %r10 = add i32 %r9,%r8
    %r1 = load i32, ptr %r0
    %r2 = add i32 %r10,%r1
    %r3 = load i32, ptr %r2
    %r2 = load i32, ptr %r1
    %r3 = add i32 %r3,%r2
    %r9 = getelementptr [10 x [2 x [3 x [4 x [5 x [6 x [2 x i32]]]]]]], ptr @arr1, i32 0, i32 %r2, i32 %r3, i32 %r4, i32 %r5, i32 %r6, i32 %r7, i32 %r8
    store i32 %r3, ptr %r9
    %r12 = add i32 %r8,%r10
    store i32 0, ptr %r8
    br label %L19
L2:  
L3:  
L4:  
L5:  
L6:  
    %r3 = load i32, ptr %r2
    %r6 = add i32 %r3,%r4
    store i32 0, ptr %r2
    br label %L1
L7:  
L8:  
L9:  
    %r4 = load i32, ptr %r3
    %r7 = add i32 %r4,%r5
    store i32 4, ptr %r3
    br label %L4
L10:  
L11:  
L12:  
    %r5 = load i32, ptr %r4
    %r8 = add i32 %r5,%r6
    store i32 0, ptr %r4
    br label %L7
L13:  
L14:  
L15:  
    %r9 = add i32 %r5,%r7
    store i32 0, ptr %r5
    br label %L10
L16:  
L17:  
L18:  
    %r10 = add i32 %r6,%r8
    store i32 0, ptr %r6
    br label %L13
L19:  
L20:  
L21:  
    %r11 = add i32 %r7,%r9
    store i32 0, ptr %r7
    br label %L16
}
define i32 @main()
{
L1:  
    %r35 = alloca i32
    %r33 = alloca i32
    %r31 = alloca i32
    %r29 = alloca i32
    %r27 = alloca i32
    %r25 = alloca i32
    %r23 = alloca i32
    %r21 = alloca i32
    %r19 = alloca i32
    %r20 = call i32 @getint()
    store i32 0, ptr %r19
    %r22 = call i32 @getint()
    store i32 %r22, ptr %r21
    %r24 = call i32 @getint()
    store i32 %r24, ptr %r23
    %r26 = call i32 @getint()
    store i32 %r26, ptr %r25
    %r28 = call i32 @getint()
    store i32 %r28, ptr %r27
    %r30 = call i32 @getint()
    store i32 %r30, ptr %r29
    %r32 = call i32 @getint()
    store i32 %r32, ptr %r31
    %r34 = call i32 @getint()
    store i32 %r34, ptr %r33
    %r36 = call i32 @getint()
    store i32 %r36, ptr %r35
    %r22 = call i32 @loop1(i32 %r19,i32 %r21)
    %r23 = call i32 @loop2()
    %r36 = call i32 @loop3(i32 %r23,i32 %r25,i32 %r27,i32 %r29,i32 %r31,i32 %r33,i32 %r35)
    ret i32 %r36
}
define float @loop2()
{
L1:  
    %r9 = alloca i32
    %r8 = alloca i32
    %r7 = alloca i32
    %r6 = alloca i32
    %r5 = alloca i32
    %r4 = alloca i32
    %r3 = alloca i32
    store i32 0, ptr %r3
    br label %L21
    %r4 = load i32, ptr %r3
    %r7 = icmp slt i32 %r4,%r5
    br i1 %r7, label %L22, label %L23
    store i32 0, ptr %r4
    br label %L24
    %r5 = load i32, ptr %r4
    %r8 = icmp slt i32 %r5,%r6
    br i1 %r8, label %L25, label %L26
    store i32 0, ptr %r5
    br label %L27
    %r9 = icmp slt i32 %r5,%r7
    br i1 %r9, label %L28, label %L29
    store i32 0, ptr %r6
    br label %L30
    %r10 = icmp slt i32 %r6,%r8
    br i1 %r10, label %L31, label %L32
    store i32 0, ptr %r7
    br label %L33
    %r11 = icmp slt i32 %r7,%r9
    br i1 %r11, label %L34, label %L35
    store i32 0, ptr %r8
    br label %L36
    %r12 = icmp slt i32 %r8,%r10
    br i1 %r12, label %L37, label %L38
    store i32 0, ptr %r9
    br label %L39
    %r13 = icmp slt i32 %r9,%r11
    br i1 %r13, label %L40, label %L41
    %r4 = load i32, ptr %r3
    %r5 = load i32, ptr %r4
    %r6 = add i32 %r4,%r5
    %r8 = add i32 %r6,%r6
    %r11 = add i32 %r8,%r9
    %r10 = getelementptr [10 x [2 x [3 x [2 x [4 x [8 x [7 x i32]]]]]]], ptr @arr2, i32 0, i32 %r3, i32 %r4, i32 %r5, i32 %r6, i32 %r7, i32 %r8, i32 %r9
    store i32 0, ptr %r10
    %r13 = add i32 %r9,%r11
    store i32 0, ptr %r9
    br label %L40
L22:  
L23:  
L24:  
L25:  
L26:  
L27:  
    %r4 = load i32, ptr %r3
    %r7 = add i32 %r4,%r5
    store i32 3, ptr %r3
    br label %L22
L28:  
L29:  
L30:  
    %r5 = load i32, ptr %r4
    %r8 = add i32 %r5,%r6
    store i32 0, ptr %r4
    br label %L25
L31:  
L32:  
L33:  
    %r9 = add i32 %r5,%r7
    store i32 0, ptr %r5
    br label %L28
L34:  
L35:  
L36:  
    %r10 = add i32 %r6,%r8
    store i32 0, ptr %r6
    br label %L31
L37:  
L38:  
L39:  
    %r11 = add i32 %r7,%r9
    store i32 0, ptr %r7
    br label %L34
L40:  
L41:  
L42:  
    %r12 = add i32 %r8,%r10
    store i32 0, ptr %r8
    br label %L37
}
define i32 @loop3(i32 %r0,i32 %r4,i32 %r2,i32 %r5,i32 %r4,i32 %r6,i32 %r6)
{
L1:  
    %r18 = alloca i32
    %r17 = alloca i32
    %r16 = alloca i32
    %r15 = alloca i32
    %r14 = alloca i32
    %r13 = alloca i32
    %r12 = alloca i32
    %r11 = alloca i32
    store i32 0, ptr %r18
    store i32 0, ptr %r11
    br label %L42
    %r12 = load i32, ptr %r11
    %r15 = icmp slt i32 %r12,%r13
    br i1 %r15, label %L43, label %L44
    store i32 0, ptr %r12
    br label %L45
    %r13 = load i32, ptr %r12
    %r16 = icmp slt i32 %r13,%r14
    br i1 %r16, label %L46, label %L47
    store i32 0, ptr %r13
    br label %L48
    %r17 = icmp slt i32 %r13,%r15
    br i1 %r17, label %L49, label %L50
    store i32 0, ptr %r14
    br label %L51
    %r18 = icmp slt i32 %r14,%r16
    br i1 %r18, label %L52, label %L53
    store i32 0, ptr %r15
    br label %L54
    %r19 = icmp slt i32 %r15,%r17
    br i1 %r19, label %L55, label %L56
    store i32 0, ptr %r16
    br label %L57
    %r20 = icmp slt i32 %r16,%r18
    br i1 %r20, label %L58, label %L59
    store i32 0, ptr %r17
    br label %L60
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L61, label %L62
    %r22 = srem i32 %r18,%r20
    %r23 = load float, ptr %r22
    %r18 = getelementptr [10 x [2 x [3 x [4 x [5 x [6 x [2 x i32]]]]]]], ptr @arr1, i32 0, i32 %r11, i32 %r12, i32 %r13, i32 %r14, i32 %r15, i32 %r16, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = add i32 %r23,%r19
    %r21 = load i32, ptr %r20
    %r18 = getelementptr [10 x [2 x [3 x [2 x [4 x [8 x [7 x i32]]]]]]], ptr @arr2, i32 0, i32 %r11, i32 %r12, i32 %r13, i32 %r14, i32 %r15, i32 %r16, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = add i32 %r21,%r19
    store i32 0, ptr %r18
    %r21 = add i32 %r17,%r19
    store i32 0, ptr %r17
    %r11 = load i32, ptr %r10
    %r12 = icmp sge i32 %r17,%r11
    br i1 %r12, label %L63, label %L64
    br label %L62
    br label %L65
L43:  
L44:  
L45:  
    ret i32 0
L46:  
L47:  
L48:  
    %r12 = load i32, ptr %r11
    %r15 = add i32 %r12,%r13
    store i32 1000, ptr %r11
    %r12 = load i32, ptr %r11
    %r5 = load i32, ptr %r4
    %r6 = icmp sge i32 %r12,%r5
    br i1 %r6, label %L81, label %L82
    br label %L44
    br label %L83
L49:  
L50:  
L51:  
    %r13 = load i32, ptr %r12
    %r16 = add i32 %r13,%r14
    store i32 0, ptr %r12
    %r13 = load i32, ptr %r12
    %r6 = load i32, ptr %r5
    %r7 = icmp sge i32 %r13,%r6
    br i1 %r7, label %L78, label %L79
    br label %L47
    br label %L80
L52:  
L53:  
L54:  
    %r17 = add i32 %r13,%r15
    store i32 0, ptr %r13
    %r7 = load i32, ptr %r6
    %r8 = icmp sge i32 %r13,%r7
    br i1 %r8, label %L75, label %L76
    br label %L50
    br label %L77
L55:  
L56:  
L57:  
    %r18 = add i32 %r14,%r16
    store i32 0, ptr %r14
    %r8 = load i32, ptr %r7
    %r9 = icmp sge i32 %r14,%r8
    br i1 %r9, label %L72, label %L73
    br label %L53
    br label %L74
L58:  
L59:  
L60:  
    %r19 = add i32 %r15,%r17
    store i32 0, ptr %r15
    %r9 = load i32, ptr %r8
    %r10 = icmp sge i32 %r15,%r9
    br i1 %r10, label %L69, label %L70
    br label %L56
    br label %L71
L61:  
L62:  
L63:  
    %r20 = add i32 %r16,%r18
    store i32 0, ptr %r16
    %r10 = load i32, ptr %r9
    %r11 = icmp sge i32 %r16,%r10
    br i1 %r11, label %L66, label %L67
    br label %L59
    br label %L68
L64:  
L66:  
    br label %L61
L67:  
L69:  
    br label %L58
L70:  
L72:  
    br label %L55
L73:  
L75:  
    br label %L52
L76:  
L78:  
    br label %L49
L79:  
L81:  
    br label %L46
L82:  
L84:  
    br label %L43
}
