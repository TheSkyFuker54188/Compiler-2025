@e = global void zeroinitializer
define void @my_fabs(void %r0)
{
L1:  
    ret void %r1
    br label %L2
L3:  
    %r2 = sub i32 %r0,%r1
    ret void %r2
}
define void @F1(void %r0)
{
L1:  
    %r20 = load void, ptr %r19
    %r21 = sdiv i32 %r20,%r20
    ret void %r21
}
define void @my_pow(void %r0,i32 %r3)
{
L1:  
    %r5 = load i32, ptr %r4
    %r8 = icmp slt i32 %r5,%r6
    br i1 %r8, label %L3, label %L4
    %r5 = sub i32 %r0,%r4
    call void @my_pow(void %r3,float %r5)
    %r8 = sdiv i32 %r9,%r6
    ret void %r8
    br label %L5
L4:  
L6:  
    %r9 = alloca void
    store void %r10, ptr %r9
    br label %L6
    br i1 %r4, label %L7, label %L8
    %r5 = load i32, ptr %r4
    %r8 = srem i32 %r5,%r6
    br i1 %r8, label %L9, label %L10
    %r10 = load void, ptr %r9
    %r4 = load void, ptr %r3
    %r5 = mul i32 %r10,%r4
    store void %r5, ptr %r9
    br label %L11
L7:  
L8:  
L9:  
    ret void %r9
L10:  
L12:  
    %r4 = load void, ptr %r3
    %r4 = load void, ptr %r3
    %r5 = mul i32 %r4,%r4
    store void %r5, ptr %r3
    %r5 = load i32, ptr %r4
    %r8 = sdiv i32 %r5,%r6
    store i32 %r8, ptr %r4
    br label %L7
}
define void @my_sqrt(void %r0)
{
L1:  
    %r11 = load void, ptr %r10
    %r14 = icmp sgt i32 %r11,%r12
    br i1 %r14, label %L12, label %L13
    %r16 = load void, ptr %r15
    %r11 = load void, ptr %r10
    %r14 = sdiv i32 %r11,%r12
    call void @my_sqrt(float %r14)
    %r16 = load void, ptr %r15
    %r17 = mul i32 %r16,%r16
    ret void %r17
    br label %L14
L13:  
L15:  
    %r17 = alloca i32
    %r18 = alloca void
    %r11 = load void, ptr %r10
    %r14 = sdiv i32 %r11,%r12
    %r15 = load float, ptr %r14
    %r17 = load void, ptr %r16
    %r18 = add i32 %r15,%r17
    %r19 = load void, ptr %r18
    %r11 = load void, ptr %r10
    %r12 = mul i32 %r20,%r11
    %r11 = load void, ptr %r10
    %r12 = add i32 %r14,%r11
    %r14 = sdiv i32 %r12,%r12
    %r16 = add i32 %r19,%r14
    store void %r16, ptr %r18
    store i32 10, ptr %r17
    br label %L15
    br i1 %r17, label %L16, label %L17
    %r11 = load void, ptr %r10
    %r20 = sdiv i32 %r11,%r18
    %r22 = add i32 %r18,%r20
    %r23 = load float, ptr %r22
    %r26 = sdiv i32 %r23,%r24
    store i32 %r26, ptr %r18
    %r18 = load i32, ptr %r17
    %r21 = sub i32 %r18,%r19
    store i32 %r21, ptr %r17
    br label %L16
L16:  
L17:  
L18:  
    ret void 10
}
define void @F2(void %r0)
{
L1:  
    %r23 = load void, ptr %r22
    %r23 = load void, ptr %r22
    %r24 = mul i32 %r23,%r23
    %r26 = sub i32 %r25,%r24
    call void @my_sqrt(float %r26)
    %r28 = load float, ptr %r27
    %r29 = sdiv i32 %r23,%r28
    ret void %r29
}
define void @simpson(void %r0,void %r30,i32 %r2)
{
L1:  
    %r33 = alloca void
    %r31 = load void, ptr %r30
    %r32 = load void, ptr %r31
    %r31 = load void, ptr %r30
    %r32 = sub i32 %r32,%r31
    %r33 = load i32, ptr %r32
    %r36 = sdiv i32 %r33,%r34
    %r37 = load float, ptr %r36
    %r38 = add i32 %r31,%r37
    store void %r38, ptr %r33
    %r33 = load i32, ptr %r32
    %r36 = icmp eq i32 %r33,%r34
    br i1 %r36, label %L18, label %L19
    call void @F1(void %r30)
    %r32 = load void, ptr %r31
    call void @F1(i32 %r33)
    %r36 = mul i32 %r33,%r34
    %r37 = load float, ptr %r36
    %r38 = add i32 %r32,%r37
    %r39 = load float, ptr %r38
    call void @F1(void %r31)
    %r33 = load i32, ptr %r32
    %r34 = add i32 %r39,%r33
    %r32 = load void, ptr %r31
    %r31 = load void, ptr %r30
    %r32 = sub i32 %r32,%r31
    %r33 = load i32, ptr %r32
    %r34 = mul i32 %r34,%r33
    %r38 = sdiv i32 %r34,%r36
    ret void %r38
    br label %L20
L19:  
L21:  
    %r33 = load i32, ptr %r32
    %r36 = icmp eq i32 %r33,%r34
    br i1 %r36, label %L21, label %L22
    call void @F2(void %r30)
    %r32 = load void, ptr %r31
    call void @F2(i32 %r33)
    %r36 = mul i32 %r33,%r34
    %r38 = add i32 %r32,%r36
    %r39 = load float, ptr %r38
    call void @F2(void %r31)
    %r33 = load i32, ptr %r32
    %r34 = add i32 %r39,%r33
    %r32 = load void, ptr %r31
    %r31 = load void, ptr %r30
    %r32 = sub i32 %r32,%r31
    %r33 = load i32, ptr %r32
    %r34 = mul i32 %r34,%r33
    %r38 = sdiv i32 %r34,%r36
    ret void %r38
    br label %L23
L22:  
L24:  
    ret void 0
}
define void @asr5(void %r0,void %r40,void %r2,void %r41,i32 %r4)
{
L1:  
    %r46 = alloca void
    %r49 = alloca void
    %r45 = alloca void
    %r41 = load void, ptr %r40
    %r42 = load void, ptr %r41
    %r41 = load void, ptr %r40
    %r42 = sub i32 %r42,%r41
    %r43 = load void, ptr %r42
    %r46 = sdiv i32 %r43,%r44
    %r47 = load float, ptr %r46
    %r48 = add i32 %r41,%r47
    store void %r48, ptr %r45
    call void @simpson(void %r40,void %r45,i32 %r44)
    store void %r45, ptr %r49
    call void @simpson(void %r45,void %r41,i32 %r44)
    store void %r45, ptr %r46
    %r50 = load void, ptr %r49
    %r47 = load void, ptr %r46
    %r48 = add i32 %r50,%r47
    %r49 = load float, ptr %r48
    %r44 = load void, ptr %r43
    %r45 = sub i32 %r49,%r44
    call void @my_fabs(void %r45)
    %r47 = load void, ptr %r46
    %r43 = load void, ptr %r42
    %r44 = mul i32 %r48,%r43
    %r46 = icmp sle i32 %r47,%r44
    br i1 %r46, label %L24, label %L25
    %r50 = load void, ptr %r49
    %r47 = load void, ptr %r46
    %r48 = add i32 %r50,%r47
    %r50 = load void, ptr %r49
    %r47 = load void, ptr %r46
    %r48 = add i32 %r50,%r47
    %r44 = load void, ptr %r43
    %r45 = sub i32 %r48,%r44
    %r46 = load void, ptr %r45
    %r48 = load void, ptr %r47
    %r49 = sdiv i32 %r46,%r48
    %r50 = load void, ptr %r49
    %r51 = add i32 %r48,%r50
    ret void %r51
    br label %L26
L25:  
L27:  
    %r43 = load void, ptr %r42
    %r46 = sdiv i32 %r43,%r44
    call void @asr5(void %r40,void %r45,void %r46,void %r49,i32 %r44)
    %r46 = load void, ptr %r45
    %r43 = load void, ptr %r42
    %r46 = sdiv i32 %r43,%r44
    call void @asr5(void %r45,void %r41,void %r46,void %r46,i32 %r44)
    %r46 = load void, ptr %r45
    %r47 = add i32 %r46,%r46
    ret void 15.000000
}
define void @asr4(void %r0,void %r48,void %r2,i32 %r49)
{
L1:  
    call void @simpson(void %r48,void %r49,i32 %r51)
    call void @asr5(void %r48,void %r49,void %r50,float %r52,i32 %r51)
    ret void %r52
}
define void @eee(void %r0)
{
L1:  
    %r58 = alloca void
    %r54 = load void, ptr %r53
    %r56 = load void, ptr %r55
    %r57 = icmp sgt i32 %r54,%r56
    br i1 %r57, label %L27, label %L28
    %r54 = load void, ptr %r53
    %r57 = sdiv i32 %r54,%r55
    call void @eee(float %r57)
    store void %r58, ptr %r58
    %r59 = load void, ptr %r58
    %r59 = load void, ptr %r58
    %r60 = mul i32 %r59,%r59
    ret void %r60
    br label %L29
L28:  
L30:  
    %r54 = load void, ptr %r53
    %r55 = add i32 %r61,%r54
    %r54 = load void, ptr %r53
    %r54 = load void, ptr %r53
    %r55 = mul i32 %r54,%r54
    %r59 = sdiv i32 %r55,%r57
    %r60 = load float, ptr %r59
    %r61 = add i32 %r55,%r60
    call void @my_pow(void %r53,i32 %r54)
    %r59 = sdiv i32 %r55,%r57
    %r60 = load float, ptr %r59
    %r61 = add i32 %r61,%r60
    call void @my_pow(void %r53,i32 %r54)
    %r59 = sdiv i32 %r55,%r57
    %r60 = load float, ptr %r59
    %r61 = add i32 %r61,%r60
    call void @my_pow(void %r53,i32 %r54)
    %r59 = sdiv i32 %r55,%r57
    %r60 = load float, ptr %r59
    %r61 = add i32 %r61,%r60
    ret void 1
}
define void @my_exp(void %r0)
{
L1:  
    %r63 = load void, ptr %r62
    %r66 = icmp slt i32 %r63,%r64
    br i1 %r66, label %L30, label %L31
    %r63 = sub i32 %r0,%r62
    call void @my_exp(float %r63)
    %r66 = sdiv i32 %r67,%r64
    ret void %r66
    br label %L32
L31:  
L33:  
    %r69 = alloca void
    %r63 = alloca void
    %r67 = alloca i32
    store i32 %r62, ptr %r67
    %r63 = load void, ptr %r62
    %r68 = load i32, ptr %r67
    %r69 = sub i32 %r63,%r68
    store void %r69, ptr %r62
    call void @my_pow(void %r64,i32 %r67)
    store void %r68, ptr %r63
    call void @eee(void %r62)
    store void %r63, ptr %r69
    %r64 = load void, ptr %r63
    %r70 = load void, ptr %r69
    %r71 = mul i32 %r64,%r70
    ret void %r71
}
define void @my_ln(void %r0)
{
L1:  
    call void @asr4(i32 %r73,void %r72,void %r73,i32 %r74)
    ret void %r75
}
define void @my_log(void %r0,void %r76)
{
L1:  
    call void @my_ln(void %r77)
    %r79 = load float, ptr %r78
    call void @my_ln(void %r76)
    %r78 = load void, ptr %r77
    %r79 = sdiv i32 %r79,%r78
    ret void %r79
}
define void @my_powf(void %r0,void %r80)
{
L1:  
    %r82 = load void, ptr %r81
    call void @my_ln(void %r80)
    %r82 = load void, ptr %r81
    %r83 = mul i32 %r82,%r82
    call void @my_exp(float %r83)
    ret void %r84
}
define i32 @main()
{
L1:  
    %r88 = alloca void
    %r86 = alloca void
    %r85 = alloca i32
    %r86 = call i32 @getint()
    store i32 %r86, ptr %r85
    br label %L33
    br i1 %r85, label %L34, label %L35
    %r87 = call i32 @getfloat()
    store void %r87, ptr %r86
    %r89 = call i32 @getfloat()
    store void %r89, ptr %r88
    %r87 = call i32 @my_fabs(void %r86)
    %r88 = call i32 @putfloat(float %r87)
    %r90 = call i32 @putch(i32 %r89)
    %r88 = call i32 @my_pow(void %r86,i32 %r87)
    %r89 = call i32 @putfloat(void %r88)
    %r91 = call i32 @putch(i32 %r90)
    %r87 = call i32 @my_sqrt(void %r86)
    %r88 = call i32 @putfloat(i32 %r87)
    %r90 = call i32 @putch(i32 %r89)
    %r87 = call i32 @my_exp(void %r86)
    %r88 = call i32 @putfloat(i32 %r87)
    %r90 = call i32 @putch(i32 %r89)
    %r87 = load void, ptr %r86
    %r90 = icmp sgt i32 %r87,%r88
    br i1 %r90, label %L36, label %L37
    %r87 = call i32 @my_ln(void %r86)
    %r88 = call i32 @putfloat(i32 %r87)
    br label %L38
    %r90 = call i32 @putch(i32 %r89)
    br label %L38
L34:  
L35:  
L36:  
    ret i32 0
L37:  
L38:  
L39:  
    %r92 = call i32 @putch(i32 %r91)
    %r87 = load void, ptr %r86
    %r90 = icmp sgt i32 %r87,%r88
    %r92 = icmp sgt i32 %r88,%r90
    %r93 = load float, ptr %r92
    %r94 = and i32 %r90,%r93
    br i1 %r94, label %L39, label %L40
    %r89 = call i32 @my_log(void %r86,i32 %r88)
    %r90 = call i32 @putfloat(i32 %r89)
    br label %L41
    %r92 = call i32 @putch(i32 %r91)
    br label %L41
L40:  
L41:  
L42:  
    %r94 = call i32 @putch(i32 %r93)
    %r87 = load void, ptr %r86
    %r90 = icmp sgt i32 %r87,%r88
    br i1 %r90, label %L42, label %L43
    %r89 = call i32 @my_powf(void %r86,i32 %r88)
    %r90 = call i32 @putfloat(i32 %r89)
    br label %L44
    %r92 = call i32 @putch(i32 %r91)
    br label %L44
L43:  
L44:  
L45:  
    %r94 = call i32 @putch(i32 %r93)
    %r86 = load i32, ptr %r85
    %r89 = sub i32 %r86,%r87
    store i32 32, ptr %r85
    br label %L34
}
