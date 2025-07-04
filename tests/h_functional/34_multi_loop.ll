define i32 @main()
{
L1:  
    %r72 = alloca i32
    %r67 = alloca i32
    %r62 = alloca i32
    %r57 = alloca i32
    %r52 = alloca i32
    %r47 = alloca i32
    %r42 = alloca i32
    %r37 = alloca i32
    %r32 = alloca i32
    %r27 = alloca i32
    %r22 = alloca i32
    %r17 = alloca i32
    %r12 = alloca i32
    %r7 = alloca i32
    %r3 = load i32, ptr %r2
    %r6 = icmp slt i32 %r3,%r4
    br i1 %r6, label %L1, label %L2
    store i32 0, ptr %r7
    br label %L3
    %r8 = load i32, ptr %r7
    %r11 = icmp slt i32 %r8,%r9
    br i1 %r11, label %L4, label %L5
    store i32 0, ptr %r12
    br label %L6
    %r13 = load i32, ptr %r12
    %r16 = icmp slt i32 %r13,%r14
    br i1 %r16, label %L7, label %L8
    store i32 0, ptr %r17
    br label %L9
    %r18 = load i32, ptr %r17
    %r21 = icmp slt i32 %r18,%r19
    br i1 %r21, label %L10, label %L11
    store i32 0, ptr %r22
    br label %L12
    %r23 = load i32, ptr %r22
    %r26 = icmp slt i32 %r23,%r24
    br i1 %r26, label %L13, label %L14
    store i32 0, ptr %r27
    br label %L15
    %r28 = load i32, ptr %r27
    %r31 = icmp slt i32 %r28,%r29
    br i1 %r31, label %L16, label %L17
    store i32 0, ptr %r32
    br label %L18
    %r33 = load i32, ptr %r32
    %r36 = icmp slt i32 %r33,%r34
    br i1 %r36, label %L19, label %L20
    store i32 0, ptr %r37
    br label %L21
    %r38 = load i32, ptr %r37
    %r41 = icmp slt i32 %r38,%r39
    br i1 %r41, label %L22, label %L23
    store i32 0, ptr %r42
    br label %L24
    %r43 = load i32, ptr %r42
    %r46 = icmp slt i32 %r43,%r44
    br i1 %r46, label %L25, label %L26
    store i32 0, ptr %r47
    br label %L27
    %r48 = load i32, ptr %r47
    %r51 = icmp slt i32 %r48,%r49
    br i1 %r51, label %L28, label %L29
    store i32 0, ptr %r52
    br label %L30
    %r53 = load i32, ptr %r52
    %r56 = icmp slt i32 %r53,%r54
    br i1 %r56, label %L31, label %L32
    store i32 0, ptr %r57
    br label %L33
    %r58 = load i32, ptr %r57
    %r61 = icmp slt i32 %r58,%r59
    br i1 %r61, label %L34, label %L35
    store i32 0, ptr %r62
    br label %L36
    %r63 = load i32, ptr %r62
    %r66 = icmp slt i32 %r63,%r64
    br i1 %r66, label %L37, label %L38
    store i32 0, ptr %r67
    br label %L39
    %r68 = load i32, ptr %r67
    %r71 = icmp slt i32 %r68,%r69
    br i1 %r71, label %L40, label %L41
    store i32 0, ptr %r72
    br label %L42
    %r73 = load i32, ptr %r72
    %r76 = icmp slt i32 %r73,%r74
    br i1 %r76, label %L43, label %L44
    %r1 = load i32, ptr %r0
    %r4 = add i32 %r1,%r2
    %r8 = srem i32 %r4,%r6
    store i32 0, ptr %r0
    %r73 = load i32, ptr %r72
    %r76 = add i32 %r73,%r74
    store i32 %r76, ptr %r72
    br label %L43
L2:  
L3:  
    ret i32 %r0
L4:  
L5:  
L6:  
    %r6 = add i32 %r2,%r4
    store i32 999, ptr %r2
    br label %L1
L7:  
L8:  
L9:  
    %r8 = load i32, ptr %r7
    %r11 = add i32 %r8,%r9
    store i32 %r11, ptr %r7
    br label %L4
L10:  
L11:  
L12:  
    %r13 = load i32, ptr %r12
    %r16 = add i32 %r13,%r14
    store i32 %r16, ptr %r12
    br label %L7
L13:  
L14:  
L15:  
    %r18 = load i32, ptr %r17
    %r21 = add i32 %r18,%r19
    store i32 %r21, ptr %r17
    br label %L10
L16:  
L17:  
L18:  
    %r23 = load i32, ptr %r22
    %r26 = add i32 %r23,%r24
    store i32 %r26, ptr %r22
    br label %L13
L19:  
L20:  
L21:  
    %r28 = load i32, ptr %r27
    %r31 = add i32 %r28,%r29
    store i32 %r31, ptr %r27
    br label %L16
L22:  
L23:  
L24:  
    %r33 = load i32, ptr %r32
    %r36 = add i32 %r33,%r34
    store i32 %r36, ptr %r32
    br label %L19
L25:  
L26:  
L27:  
    %r38 = load i32, ptr %r37
    %r41 = add i32 %r38,%r39
    store i32 %r41, ptr %r37
    br label %L22
L28:  
L29:  
L30:  
    %r43 = load i32, ptr %r42
    %r46 = add i32 %r43,%r44
    store i32 %r46, ptr %r42
    br label %L25
L31:  
L32:  
L33:  
    %r48 = load i32, ptr %r47
    %r51 = add i32 %r48,%r49
    store i32 %r51, ptr %r47
    br label %L28
L34:  
L35:  
L36:  
    %r53 = load i32, ptr %r52
    %r56 = add i32 %r53,%r54
    store i32 %r56, ptr %r52
    br label %L31
L37:  
L38:  
L39:  
    %r58 = load i32, ptr %r57
    %r61 = add i32 %r58,%r59
    store i32 %r61, ptr %r57
    br label %L34
L40:  
L41:  
L42:  
    %r63 = load i32, ptr %r62
    %r66 = add i32 %r63,%r64
    store i32 %r66, ptr %r62
    br label %L37
L43:  
L44:  
L45:  
    %r68 = load i32, ptr %r67
    %r71 = add i32 %r68,%r69
    store i32 %r71, ptr %r67
    br label %L40
}
