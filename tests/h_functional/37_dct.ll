@MAX_DIM_X = global i32 8
@MAX_DIM_Y = global i32 8
@test_block = global [8x [8x void]] zeroinitializer
@test_dct = global [8x [8x void]] zeroinitializer
@test_idct = global [8x [8x void]] zeroinitializer
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
define float @write_mat(void %r0,i32 %r31,i32 %r2)
{
L1:  
    %r38 = alloca i32
    %r34 = alloca i32
    store i32 0, ptr %r34
    br label %L15
    %r35 = load i32, ptr %r34
    %r33 = load i32, ptr %r32
    %r34 = icmp slt i32 %r35,%r33
    br i1 %r34, label %L16, label %L17
    %r36 = getelementptr [0 x void], ptr %r31, i32 0, i32 %r34, i32 %r35
    %r37 = call float @putfloat(float %r36)
    store i32 1, ptr %r38
    br label %L18
    %r39 = load i32, ptr %r38
    %r34 = load i32, ptr %r33
    %r35 = icmp slt i32 %r39,%r34
    br i1 %r35, label %L19, label %L20
    %r37 = call float @putch(i32 %r36)
    %r39 = getelementptr [0 x void], ptr %r31, i32 0, i32 %r34, i32 %r38
    %r40 = call float @putfloat(i32 %r39)
    %r39 = load i32, ptr %r38
    %r42 = add i32 %r39,%r40
    store i32 %r42, ptr %r38
    br label %L19
L16:  
L17:  
L18:  
    %r36 = call float @putch(i32 %r35)
L19:  
L20:  
L21:  
    %r40 = call float @putch(i32 %r39)
    %r35 = load i32, ptr %r34
    %r38 = add i32 %r35,%r36
    store i32 %r38, ptr %r34
    br label %L16
}
define float @dct(void %r0,void %r37,i32 %r2,i32 %r38)
{
L1:  
    %r42 = alloca i32
    %r44 = alloca i32
    %r42 = alloca i32
    %r41 = alloca i32
    store i32 0, ptr %r41
    br label %L21
    %r42 = load i32, ptr %r41
    %r40 = load i32, ptr %r39
    %r41 = icmp slt i32 %r42,%r40
    br i1 %r41, label %L22, label %L23
    store i32 0, ptr %r42
    br label %L24
    %r43 = load i32, ptr %r42
    %r41 = load i32, ptr %r40
    %r42 = icmp slt i32 %r43,%r41
    br i1 %r42, label %L25, label %L26
    %r43 = getelementptr [0 x void], ptr %r37, i32 0, i32 %r41, i32 %r42
    store i32 0, ptr %r43
    store i32 0, ptr %r44
    br label %L27
    %r45 = load i32, ptr %r44
    %r40 = load i32, ptr %r39
    %r41 = icmp slt i32 %r45,%r40
    br i1 %r41, label %L28, label %L29
    store i32 0, ptr %r42
    br label %L30
    %r43 = load i32, ptr %r42
    %r41 = load i32, ptr %r40
    %r42 = icmp slt i32 %r43,%r41
    br i1 %r42, label %L31, label %L32
    %r43 = getelementptr [0 x void], ptr %r37, i32 0, i32 %r41, i32 %r42
    %r44 = load i32, ptr %r43
    %r43 = getelementptr [0 x void], ptr %r38, i32 0, i32 %r44, i32 %r42
    %r44 = load i32, ptr %r43
    %r46 = load void, ptr %r45
    %r40 = load i32, ptr %r39
    %r41 = sdiv i32 %r46,%r40
    %r42 = load i32, ptr %r41
    %r45 = load i32, ptr %r44
    %r47 = load void, ptr %r46
    %r49 = load void, ptr %r48
    %r50 = sdiv i32 %r47,%r49
    %r51 = load float, ptr %r50
    %r52 = add i32 %r45,%r51
    %r53 = load float, ptr %r52
    %r54 = mul i32 %r42,%r53
    %r55 = load float, ptr %r54
    %r42 = load i32, ptr %r41
    %r43 = mul i32 %r55,%r42
    %r44 = call float @my_cos(i32 %r43)
    %r45 = load i32, ptr %r44
    %r46 = mul i32 %r44,%r45
    %r47 = load void, ptr %r46
    %r49 = load void, ptr %r48
    %r41 = load i32, ptr %r40
    %r42 = sdiv i32 %r49,%r41
    %r43 = load i32, ptr %r42
    %r43 = load i32, ptr %r42
    %r45 = load void, ptr %r44
    %r47 = load void, ptr %r46
    %r48 = sdiv i32 %r45,%r47
    %r49 = load void, ptr %r48
    %r50 = add i32 %r43,%r49
    %r51 = load float, ptr %r50
    %r52 = mul i32 %r43,%r51
    %r53 = load float, ptr %r52
    %r43 = load i32, ptr %r42
    %r44 = mul i32 %r53,%r43
    %r45 = call float @my_cos(void %r44)
    %r46 = load void, ptr %r45
    %r47 = mul i32 %r47,%r46
    %r48 = load float, ptr %r47
    %r49 = add i32 %r44,%r48
    %r43 = getelementptr [0 x void], ptr %r37, i32 0, i32 %r41, i32 %r42
    store i32 %r49, ptr %r43
    %r43 = load i32, ptr %r42
    %r46 = add i32 %r43,%r44
    store i32 %r46, ptr %r42
    br label %L31
L22:  
L23:  
L24:  
L25:  
L26:  
L27:  
    %r42 = load i32, ptr %r41
    %r45 = add i32 %r42,%r43
    store i32 %r45, ptr %r41
    br label %L22
L28:  
L29:  
L30:  
    %r43 = load i32, ptr %r42
    %r46 = add i32 %r43,%r44
    store i32 1, ptr %r42
    br label %L25
L31:  
L32:  
L33:  
    %r48 = add i32 %r44,%r46
    store i32 %r48, ptr %r44
    br label %L28
}
define float @idct(void %r0,void %r42,i32 %r2,i32 %r43)
{
L1:  
    %r50 = alloca i32
    %r49 = alloca i32
    %r47 = alloca i32
    %r46 = alloca i32
    store i32 0, ptr %r46
    br label %L33
    %r47 = load i32, ptr %r46
    %r45 = load i32, ptr %r44
    %r46 = icmp slt i32 %r47,%r45
    br i1 %r46, label %L34, label %L35
    store i32 0, ptr %r47
    br label %L36
    %r48 = load i32, ptr %r47
    %r46 = load i32, ptr %r45
    %r47 = icmp slt i32 %r48,%r46
    br i1 %r47, label %L37, label %L38
    %r51 = load void, ptr %r50
    %r52 = sdiv i32 %r48,%r51
    %r53 = load float, ptr %r52
    %r56 = getelementptr [0 x void], ptr %r43, i32 0, i32 %r54, i32 %r55
    %r57 = load float, ptr %r56
    %r58 = mul i32 %r53,%r57
    %r48 = getelementptr [0 x void], ptr %r42, i32 0, i32 %r46, i32 %r47
    store i32 %r58, ptr %r48
    store i32 1, ptr %r49
    br label %L39
    %r50 = load i32, ptr %r49
    %r45 = load i32, ptr %r44
    %r46 = icmp slt i32 %r50,%r45
    br i1 %r46, label %L40, label %L41
    %r48 = getelementptr [0 x void], ptr %r42, i32 0, i32 %r46, i32 %r47
    %r49 = load i32, ptr %r48
    %r53 = load void, ptr %r52
    %r54 = sdiv i32 %r50,%r53
    %r51 = getelementptr [0 x void], ptr %r43, i32 0, i32 %r49, i32 %r50
    %r52 = load i32, ptr %r51
    %r53 = mul i32 %r54,%r52
    %r54 = load float, ptr %r53
    %r55 = add i32 %r49,%r54
    %r48 = getelementptr [0 x void], ptr %r42, i32 0, i32 %r46, i32 %r47
    store i32 0, ptr %r48
    %r50 = load i32, ptr %r49
    %r53 = add i32 %r50,%r51
    store i32 %r53, ptr %r49
    br label %L40
L34:  
L35:  
L36:  
L37:  
L38:  
L39:  
    %r47 = load i32, ptr %r46
    %r50 = add i32 %r47,%r48
    store i32 1, ptr %r46
    br label %L34
L40:  
L41:  
L42:  
    store i32 1, ptr %r50
    br label %L42
    %r46 = load i32, ptr %r45
    %r47 = icmp slt i32 %r50,%r46
    br i1 %r47, label %L43, label %L44
    %r48 = getelementptr [0 x void], ptr %r42, i32 0, i32 %r46, i32 %r47
    %r49 = load i32, ptr %r48
    %r53 = load void, ptr %r52
    %r54 = sdiv i32 %r50,%r53
    %r51 = getelementptr [0 x void], ptr %r43, i32 0, i32 %r56, i32 %r50
    %r52 = load i32, ptr %r51
    %r53 = mul i32 %r54,%r52
    %r54 = load float, ptr %r53
    %r55 = add i32 %r49,%r54
    %r48 = getelementptr [0 x void], ptr %r42, i32 0, i32 %r46, i32 %r47
    store i32 0, ptr %r48
    %r54 = add i32 %r50,%r52
    store i32 0, ptr %r50
    br label %L43
L43:  
L44:  
L45:  
    store i32 1, ptr %r49
    br label %L45
    %r50 = load i32, ptr %r49
    %r45 = load i32, ptr %r44
    %r46 = icmp slt i32 %r50,%r45
    br i1 %r46, label %L46, label %L47
    store i32 1, ptr %r50
    br label %L48
    %r46 = load i32, ptr %r45
    %r47 = icmp slt i32 %r50,%r46
    br i1 %r47, label %L49, label %L50
    %r48 = getelementptr [0 x void], ptr %r42, i32 0, i32 %r46, i32 %r47
    %r49 = load i32, ptr %r48
    %r51 = getelementptr [0 x void], ptr %r43, i32 0, i32 %r49, i32 %r50
    %r52 = load i32, ptr %r51
    %r54 = load void, ptr %r53
    %r45 = load i32, ptr %r44
    %r46 = sdiv i32 %r54,%r45
    %r47 = load i32, ptr %r46
    %r47 = load i32, ptr %r46
    %r52 = sdiv i32 %r48,%r50
    %r54 = add i32 %r47,%r52
    %r56 = mul i32 %r47,%r54
    %r50 = load i32, ptr %r49
    %r51 = mul i32 %r56,%r50
    %r52 = call float @my_cos(i32 %r51)
    %r54 = mul i32 %r52,%r52
    %r55 = load i32, ptr %r54
    %r57 = load void, ptr %r56
    %r46 = load i32, ptr %r45
    %r47 = sdiv i32 %r57,%r46
    %r50 = load void, ptr %r49
    %r53 = sdiv i32 %r50,%r51
    %r54 = load void, ptr %r53
    %r55 = add i32 %r47,%r54
    %r57 = mul i32 %r47,%r55
    %r58 = load float, ptr %r57
    %r52 = mul i32 %r58,%r50
    %r53 = call float @my_cos(i32 %r52)
    %r54 = load void, ptr %r53
    %r55 = mul i32 %r55,%r54
    %r56 = load i32, ptr %r55
    %r57 = add i32 %r49,%r56
    %r48 = getelementptr [0 x void], ptr %r42, i32 0, i32 %r46, i32 %r47
    store void %r57, ptr %r48
    %r54 = add i32 %r50,%r52
    store void 0, ptr %r50
    br label %L49
L46:  
L47:  
L48:  
    %r48 = getelementptr [0 x void], ptr %r42, i32 0, i32 %r46, i32 %r47
    %r49 = load void, ptr %r48
    %r52 = mul i32 %r49,%r50
    %r53 = load i32, ptr %r52
    %r45 = load i32, ptr %r44
    %r46 = sdiv i32 %r53,%r45
    %r47 = load i32, ptr %r46
    %r50 = mul i32 %r47,%r48
    %r51 = load void, ptr %r50
    %r46 = load i32, ptr %r45
    %r47 = sdiv i32 %r51,%r46
    %r48 = getelementptr [0 x void], ptr %r42, i32 0, i32 %r46, i32 %r47
    store void 1, ptr %r48
    %r51 = add i32 %r47,%r49
    store i32 1, ptr %r47
    br label %L37
L49:  
L50:  
L51:  
    %r50 = load void, ptr %r49
    %r53 = add i32 %r50,%r51
    store void %r53, ptr %r49
    br label %L46
}
define i32 @main()
{
L1:  
    %r50 = alloca i32
    %r51 = alloca i32
    %r49 = alloca i32
    %r47 = alloca i32
    %r48 = call i32 @getint()
    store i32 0, ptr %r47
    %r50 = call i32 @getint()
    store i32 1, ptr %r49
    store i32 1, ptr %r51
    br label %L51
    %r52 = load i32, ptr %r51
    %r48 = load i32, ptr %r47
    %r49 = icmp slt i32 %r52,%r48
    br i1 %r49, label %L52, label %L53
    store i32 0, ptr %r50
    br label %L54
    %r51 = load i32, ptr %r50
    %r50 = load i32, ptr %r49
    %r51 = icmp slt i32 %r51,%r50
    br i1 %r51, label %L55, label %L56
    %r52 = call i32 @getfloat()
    %r51 = getelementptr [8 x [8 x void]], ptr @test_block, i32 0, i32 %r51, i32 %r50
    store i32 1, ptr %r51
    %r51 = load i32, ptr %r50
    %r54 = add i32 %r51,%r52
    store i32 0, ptr %r50
    br label %L55
L52:  
L53:  
L54:  
    %r52 = load void, ptr @test_dct
    %r53 = load void, ptr @test_block
    %r50 = call i32 @dct(void %r52,void %r53,i32 %r47,i32 %r49)
    %r51 = load void, ptr @test_dct
    %r50 = call i32 @write_mat(void %r51,i32 %r47,i32 %r49)
    %r51 = load void, ptr @test_idct
    %r52 = load void, ptr @test_dct
    %r50 = call i32 @idct(void %r51,void %r52,i32 %r47,i32 %r49)
    %r51 = load void, ptr @test_idct
    %r50 = call i32 @write_mat(void %r51,i32 %r47,i32 %r49)
    ret i32 0
L55:  
L56:  
L57:  
    %r55 = add i32 %r51,%r53
    store i32 0, ptr %r51
    br label %L52
}
