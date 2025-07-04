@MAX_WIDTH = global i32 1024
@MAX_HEIGHT = global i32 1024
@image = global [1048576x i32] zeroinitializer
@width = global i32 zeroinitializer
@height = global i32 zeroinitializer
@PI = global void zeroinitializer
@TWO_PI = global void zeroinitializer
@EPSILON = global void zeroinitializer
define void @my_fabs(void %r0)
{
L1:  
    ret void %r5
    br label %L2
L3:  
    %r6 = sub i32 %r0,%r5
    ret void %r6
}
define void @my_sin(void %r0)
{
L1:  
    %r27 = alloca i32
    %r20 = load void, ptr %r19
    %r22 = load void, ptr %r21
    %r23 = icmp sgt i32 %r20,%r22
    %r24 = load float, ptr %r23
    %r20 = load void, ptr %r19
    %r22 = sub i32 %r0,%r21
    %r23 = load float, ptr %r22
    %r24 = icmp slt i32 %r20,%r23
    %r25 = load float, ptr %r24
    %r26 = xor i32 %r24,%r25
    br i1 %r26, label %L6, label %L7
    %r20 = load void, ptr %r19
    %r22 = load void, ptr %r21
    %r23 = sdiv i32 %r20,%r22
    store i32 %r23, ptr %r27
    %r20 = load void, ptr %r19
    %r28 = load i32, ptr %r27
    %r30 = load void, ptr %r29
    %r31 = mul i32 %r28,%r30
    %r32 = load float, ptr %r31
    %r33 = sub i32 %r20,%r32
    store void %r33, ptr %r19
    br label %L8
L7:  
L9:  
    %r20 = load void, ptr %r19
    %r22 = load void, ptr %r21
    %r23 = icmp sgt i32 %r20,%r22
    br i1 %r23, label %L9, label %L10
    %r20 = load void, ptr %r19
    %r22 = load void, ptr %r21
    %r23 = sub i32 %r20,%r22
    store void %r23, ptr %r19
    br label %L11
L10:  
L12:  
    %r20 = load void, ptr %r19
    %r22 = sub i32 %r0,%r21
    %r23 = load float, ptr %r22
    %r24 = icmp slt i32 %r20,%r23
    br i1 %r24, label %L12, label %L13
    %r20 = load void, ptr %r19
    %r22 = load void, ptr %r21
    %r23 = add i32 %r20,%r22
    store void %r23, ptr %r19
    br label %L14
L13:  
L15:  
    call void @my_sin_impl(void %r19)
    ret void %r20
}
define void @p(void %r0)
{
L1:  
    %r8 = load void, ptr %r7
    %r9 = mul i32 %r8,%r8
    %r10 = load float, ptr %r9
    %r8 = load void, ptr %r7
    %r9 = mul i32 %r11,%r8
    %r10 = load float, ptr %r9
    %r8 = load void, ptr %r7
    %r9 = mul i32 %r10,%r8
    %r10 = load float, ptr %r9
    %r8 = load void, ptr %r7
    %r9 = mul i32 %r10,%r8
    %r10 = load float, ptr %r9
    %r11 = sub i32 %r10,%r10
    ret void 4
}
define void @my_sin_impl(void %r0)
{
L1:  
    call void @my_fabs(void %r12)
    %r14 = load float, ptr %r13
    %r16 = load void, ptr %r15
    %r17 = icmp sle i32 %r14,%r16
    br i1 %r17, label %L3, label %L4
    ret void %r12
    br label %L5
L4:  
L6:  
    %r13 = load void, ptr %r12
    %r15 = load void, ptr %r14
    %r16 = sdiv i32 %r13,%r15
    call void @my_sin_impl(float %r16)
    call void @p(float %r17)
    ret void %r18
}
define void @my_cos(void %r0)
{
L1:  
    %r22 = load void, ptr %r21
    %r24 = load void, ptr %r23
    %r27 = sdiv i32 %r24,%r25
    %r28 = load i32, ptr %r27
    %r29 = add i32 %r22,%r28
    call void @my_sin(void %r29)
    ret void %r30
}
define i32 @read_image()
{
L1:  
    %r31 = call i32 @getch()
    %r32 = load float, ptr %r31
    %r35 = icmp ne i32 %r32,%r33
    %r36 = load float, ptr %r35
    %r37 = call i32 @getch()
    %r38 = load float, ptr %r37
    %r41 = icmp ne i32 %r38,%r39
    %r42 = load float, ptr %r41
    %r43 = xor i32 %r36,%r42
    br i1 %r43, label %L15, label %L16
    %r45 = sub i32 %r0,%r44
    ret i32 %r45
    br label %L17
L16:  
L18:  
    %r46 = call i32 @getint()
    %r47 = load i32, ptr @width
    store i32 %r46, ptr %r47
    %r48 = call i32 @getint()
    %r49 = load i32, ptr @height
    store i32 %r48, ptr %r49
    %r50 = load i32, ptr @width
    %r51 = load i32, ptr %r50
    %r54 = icmp sgt i32 %r51,%r52
    %r55 = load float, ptr %r54
    %r56 = load i32, ptr @height
    %r57 = load i32, ptr %r56
    %r60 = icmp sgt i32 %r57,%r58
    %r61 = load float, ptr %r60
    %r62 = xor i32 %r55,%r61
    %r63 = load float, ptr %r62
    %r64 = call i32 @getint()
    %r65 = load float, ptr %r64
    %r68 = icmp ne i32 %r65,%r66
    %r69 = load float, ptr %r68
    %r70 = xor i32 %r63,%r69
    br i1 %r70, label %L18, label %L19
    %r72 = sub i32 %r0,%r71
    ret i32 %r72
    br label %L20
L19:  
L21:  
    %r78 = alloca i32
    %r73 = alloca i32
    store i32 0, ptr %r73
    br label %L21
    %r74 = load i32, ptr %r73
    %r75 = load i32, ptr @height
    %r76 = load i32, ptr %r75
    %r77 = icmp slt i32 %r74,%r76
    br i1 %r77, label %L22, label %L23
    store i32 0, ptr %r78
    br label %L24
    %r79 = load i32, ptr %r78
    %r80 = load i32, ptr @width
    %r81 = load i32, ptr %r80
    %r82 = icmp slt i32 %r79,%r81
    br i1 %r82, label %L25, label %L26
    %r83 = call i32 @getint()
    %r74 = load i32, ptr %r73
    %r75 = load i32, ptr @width
    %r76 = load i32, ptr %r75
    %r77 = mul i32 %r74,%r76
    %r78 = load float, ptr %r77
    %r79 = load i32, ptr %r78
    %r80 = add i32 %r78,%r79
    %r81 = getelementptr [1048576 x i32], ptr @image, i32 0, i32 %r80
    store float %r83, ptr %r81
    %r79 = load i32, ptr %r78
    %r82 = add i32 %r79,%r80
    store i32 %r82, ptr %r78
    br label %L25
L22:  
L23:  
L24:  
    ret i32 0
L25:  
L26:  
L27:  
    %r74 = load i32, ptr %r73
    %r77 = add i32 %r74,%r75
    store i32 %r77, ptr %r73
    br label %L22
}
define i32 @rotate(i32 %r0,i32 %r75,void %r2)
{
L1:  
    %r82 = alloca i32
    %r88 = alloca i32
    %r82 = alloca i32
    %r91 = alloca i32
    %r85 = alloca i32
    %r79 = alloca i32
    %r79 = alloca void
    %r78 = alloca void
    %r78 = call i32 @my_sin(void %r77)
    store void %r78, ptr %r78
    %r78 = call i32 @my_cos(void %r77)
    store void %r78, ptr %r79
    %r80 = load i32, ptr @width
    %r81 = load i32, ptr %r80
    %r84 = sdiv i32 %r81,%r82
    store i32 %r84, ptr %r79
    %r86 = load i32, ptr @height
    %r87 = load i32, ptr %r86
    %r90 = sdiv i32 %r87,%r88
    store i32 %r90, ptr %r85
    %r76 = load i32, ptr %r75
    %r80 = load i32, ptr %r79
    %r81 = sub i32 %r76,%r80
    store i32 %r81, ptr %r91
    %r77 = load i32, ptr %r76
    %r86 = load i32, ptr %r85
    %r87 = sub i32 %r77,%r86
    store i32 %r87, ptr %r82
    %r92 = load i32, ptr %r91
    %r80 = load i32, ptr %r79
    %r81 = mul i32 %r92,%r80
    %r82 = load float, ptr %r81
    %r83 = load i32, ptr %r82
    %r79 = load void, ptr %r78
    %r80 = mul i32 %r83,%r79
    %r81 = load i32, ptr %r80
    %r82 = sub i32 %r82,%r81
    %r83 = load i32, ptr %r82
    %r80 = load i32, ptr %r79
    %r81 = add i32 %r83,%r80
    store i32 %r81, ptr %r88
    %r92 = load i32, ptr %r91
    %r79 = load void, ptr %r78
    %r80 = mul i32 %r92,%r79
    %r81 = load i32, ptr %r80
    %r83 = load i32, ptr %r82
    %r80 = load i32, ptr %r79
    %r81 = mul i32 %r83,%r80
    %r82 = load float, ptr %r81
    %r83 = add i32 %r81,%r82
    %r84 = load float, ptr %r83
    %r86 = load i32, ptr %r85
    %r87 = add i32 %r84,%r86
    store i32 %r87, ptr %r82
    %r89 = load i32, ptr %r88
    %r92 = icmp slt i32 %r89,%r90
    %r93 = load float, ptr %r92
    %r89 = load i32, ptr %r88
    %r90 = load i32, ptr @width
    %r91 = load i32, ptr %r90
    %r92 = icmp sge i32 %r89,%r91
    %r93 = load float, ptr %r92
    %r94 = xor i32 %r93,%r93
    %r95 = load float, ptr %r94
    %r83 = load i32, ptr %r82
    %r86 = icmp slt i32 %r83,%r84
    %r87 = load i32, ptr %r86
    %r88 = xor i32 %r95,%r87
    %r89 = load i32, ptr %r88
    %r83 = load i32, ptr %r82
    %r84 = load i32, ptr @height
    %r85 = load i32, ptr %r84
    %r86 = icmp sge i32 %r83,%r85
    %r87 = load i32, ptr %r86
    %r88 = xor i32 %r89,%r87
    br i1 %r88, label %L27, label %L28
    ret i32 0
    br label %L29
L28:  
L30:  
    %r83 = load i32, ptr %r82
    %r84 = load i32, ptr @width
    %r85 = load i32, ptr %r84
    %r86 = mul i32 %r83,%r85
    %r87 = load i32, ptr %r86
    %r89 = load i32, ptr %r88
    %r90 = add i32 %r87,%r89
    %r91 = getelementptr [1048576 x i32], ptr @image, i32 0, i32 %r90
    ret i32 %r91
}
define float @write_pgm(void %r0)
{
L1:  
    %r116 = alloca i32
    %r111 = alloca i32
    %r94 = call float @putch(i32 %r93)
    %r96 = call float @putch(i32 %r95)
    %r98 = call float @putch(i32 %r97)
    %r99 = load i32, ptr @width
    %r100 = call float @putint(i32 %r99)
    %r102 = call float @putch(i32 %r101)
    %r103 = load i32, ptr @height
    %r104 = call float @putint(i32 %r103)
    %r106 = call float @putch(i32 %r105)
    %r108 = call float @putint(i32 %r107)
    %r110 = call float @putch(i32 %r109)
    store i32 0, ptr %r111
    br label %L30
    %r112 = load i32, ptr %r111
    %r113 = load i32, ptr @height
    %r114 = load i32, ptr %r113
    %r115 = icmp slt i32 %r112,%r114
    br i1 %r115, label %L31, label %L32
    store i32 0, ptr %r116
    br label %L33
    %r117 = load i32, ptr %r116
    %r118 = load i32, ptr @width
    %r119 = load i32, ptr %r118
    %r120 = icmp slt i32 %r117,%r119
    br i1 %r120, label %L34, label %L35
    %r93 = call float @rotate(i32 %r116,i32 %r111,void %r92)
    %r94 = call float @putint(i32 %r93)
    %r96 = call float @putch(i32 %r95)
    %r117 = load i32, ptr %r116
    %r120 = add i32 %r117,%r118
    store i32 %r120, ptr %r116
    br label %L34
L31:  
L32:  
L33:  
L34:  
L35:  
L36:  
    %r118 = call float @putch(i32 %r117)
    %r112 = load i32, ptr %r111
    %r115 = add i32 %r112,%r113
    store i32 %r115, ptr %r111
    br label %L31
}
define i32 @main()
{
L1:  
    %r112 = alloca void
    %r113 = call i32 @getfloat()
    store void 1, ptr %r112
    %r114 = call i32 @getch()
    %r115 = call i32 @read_image()
    %r116 = load float, ptr %r115
    %r119 = icmp slt i32 %r116,%r117
    br i1 %r119, label %L36, label %L37
    %r121 = sub i32 %r0,%r120
    ret i32 %r121
    br label %L38
L37:  
L39:  
    %r113 = call i32 @write_pgm(void %r112)
    ret i32 0
}
