define i32 @func4(i32 %r0,i32 %r14,i32 %r2)
{
L1:  
    br i1 %r14, label %L9, label %L10
    ret i32 %r15
    br label %L11
    ret i32 %r16
    br label %L11
L10:  
L11:  
L12:  
}
define i32 @func1(i32 %r0,i32 %r0,i32 %r2)
{
L1:  
    %r1 = load i32, ptr %r0
    %r2 = load i32, ptr %r1
    %r3 = mul i32 %r1,%r2
    ret i32 %r3
    br label %L2
    %r2 = load i32, ptr %r1
    %r3 = load i32, ptr %r2
    %r4 = sub i32 %r2,%r3
    %r6 = call i32 @func1(i32 %r0,i32 %r4,i32 %r5)
    ret i32 %r6
    br label %L2
L2:  
L3:  
}
define i32 @func2(i32 %r0,i32 %r7)
{
L1:  
    br i1 %r8, label %L3, label %L4
    %r8 = load i32, ptr %r7
    %r9 = load i32, ptr %r8
    %r10 = srem i32 %r8,%r9
    %r12 = call i32 @func2(float %r10,i32 %r11)
    ret i32 %r12
    br label %L5
    ret i32 %r7
    br label %L5
L4:  
L5:  
L6:  
}
define i32 @func3(i32 %r0,i32 %r8)
{
L1:  
    %r10 = load i32, ptr %r9
    %r13 = icmp eq i32 %r10,%r11
    br i1 %r13, label %L6, label %L7
    %r9 = load i32, ptr %r8
    %r12 = add i32 %r9,%r10
    ret i32 %r12
    br label %L8
    %r9 = load i32, ptr %r8
    %r10 = load i32, ptr %r9
    %r11 = add i32 %r9,%r10
    %r13 = call i32 @func3(i32 %r11,i32 %r12)
    ret i32 %r13
    br label %L8
L7:  
L8:  
L9:  
}
define i32 @func5(i32 %r0)
{
L1:  
    %r18 = sub i32 %r0,%r17
    ret i32 %r18
}
define i32 @func6(i32 %r0,i32 %r19)
{
L1:  
    %r20 = load i32, ptr %r19
    %r21 = load i32, ptr %r20
    %r22 = and i32 %r20,%r21
    br i1 %r22, label %L12, label %L13
    ret i32 1
    br label %L14
    ret i32 0
    br label %L14
L13:  
L14:  
L15:  
}
define i32 @func7(i32 %r0)
{
L1:  
    %r26 = icmp eq i32 %r25,%r0
    br i1 %r26, label %L15, label %L16
    ret i32 1
    br label %L17
    ret i32 0
    br label %L17
L16:  
L17:  
L18:  
}
define i32 @main()
{
L1:  
    %r38 = alloca i32
    %r37 = alloca [10 x i32]
    %r35 = alloca i32
    %r33 = alloca i32
    %r31 = alloca i32
    %r29 = alloca i32
    %r30 = call i32 @getint()
    store i32 %r30, ptr %r29
    %r32 = call i32 @getint()
    store i32 %r32, ptr %r31
    %r34 = call i32 @getint()
    store i32 %r34, ptr %r33
    %r36 = call i32 @getint()
    store i32 %r36, ptr %r35
    store i32 0, ptr %r38
    br label %L18
    %r39 = load i32, ptr %r38
    %r42 = icmp slt i32 %r39,%r40
    br i1 %r42, label %L19, label %L20
    %r43 = call i32 @getint()
    %r39 = getelementptr [10 x i32], ptr %r37, i32 0, i32 %r38
    store i32 %r43, ptr %r39
    %r39 = load i32, ptr %r38
    %r42 = add i32 %r39,%r40
    store i32 %r42, ptr %r38
    br label %L19
L19:  
L20:  
L21:  
    %r39 = alloca i32
    %r30 = call i32 @func7(i32 %r29)
    %r32 = call i32 @func5(i32 %r31)
    %r33 = call i32 @func6(float %r30,float %r32)
    %r34 = call i32 @func2(i32 %r33,i32 %r33)
    %r36 = call i32 @func3(float %r34,i32 %r35)
    %r37 = call i32 @func5(float %r36)
    %r39 = getelementptr [10 x i32], ptr %r37, i32 0, i32 %r38
    %r41 = getelementptr [10 x i32], ptr %r37, i32 0, i32 %r40
    %r42 = call i32 @func5(float %r41)
    %r44 = getelementptr [10 x i32], ptr %r37, i32 0, i32 %r43
    %r46 = getelementptr [10 x i32], ptr %r37, i32 0, i32 %r45
    %r47 = call i32 @func7(float %r46)
    %r48 = call i32 @func6(float %r44,float %r47)
    %r50 = getelementptr [10 x i32], ptr %r37, i32 0, i32 %r49
    %r52 = getelementptr [10 x i32], ptr %r37, i32 0, i32 %r51
    %r53 = call i32 @func7(float %r52)
    %r54 = call i32 @func2(float %r50,float %r53)
    %r55 = call i32 @func4(float %r42,float %r48,float %r54)
    %r57 = getelementptr [10 x i32], ptr %r37, i32 0, i32 %r56
    %r58 = call i32 @func3(float %r55,float %r57)
    %r60 = getelementptr [10 x i32], ptr %r37, i32 0, i32 %r59
    %r61 = call i32 @func2(float %r58,float %r60)
    %r63 = getelementptr [10 x i32], ptr %r37, i32 0, i32 %r62
    %r65 = getelementptr [10 x i32], ptr %r37, i32 0, i32 %r64
    %r66 = call i32 @func7(float %r65)
    %r67 = call i32 @func3(float %r63,float %r66)
    %r30 = call i32 @func1(float %r61,float %r67,i32 %r29)
    %r31 = call i32 @func4(i32 %r37,i32 %r39,float %r30)
    %r34 = call i32 @func7(i32 %r33)
    %r36 = call i32 @func3(float %r34,i32 %r35)
    %r37 = call i32 @func2(i32 %r31,float %r36)
    %r38 = call i32 @func3(i32 %r31,i32 %r37)
    %r40 = getelementptr [10 x i32], ptr %r37, i32 0, i32 %r39
    %r42 = getelementptr [10 x i32], ptr %r37, i32 0, i32 %r41
    %r43 = call i32 @func1(i32 %r38,i32 %r40,float %r42)
    %r45 = getelementptr [10 x i32], ptr %r37, i32 0, i32 %r44
    %r46 = call i32 @func2(i32 %r43,i32 %r45)
    %r48 = getelementptr [10 x i32], ptr %r37, i32 0, i32 %r47
    %r50 = getelementptr [10 x i32], ptr %r37, i32 0, i32 %r49
    %r52 = getelementptr [10 x i32], ptr %r37, i32 0, i32 %r51
    %r53 = call i32 @func5(float %r52)
    %r54 = call i32 @func3(float %r50,float %r53)
    %r56 = getelementptr [10 x i32], ptr %r37, i32 0, i32 %r55
    %r57 = call i32 @func5(i32 %r56)
    %r58 = call i32 @func2(float %r54,float %r57)
    %r60 = getelementptr [10 x i32], ptr %r37, i32 0, i32 %r59
    %r62 = getelementptr [10 x i32], ptr %r37, i32 0, i32 %r61
    %r63 = call i32 @func7(i32 %r62)
    %r64 = call i32 @func1(float %r58,float %r60,float %r63)
    %r66 = getelementptr [10 x i32], ptr %r37, i32 0, i32 %r65
    %r67 = call i32 @func5(float %r66)
    %r68 = call i32 @func2(i32 %r64,float %r67)
    %r30 = call i32 @func3(float %r68,i32 %r29)
    %r31 = call i32 @func1(float %r46,float %r48,float %r30)
    store i32 %r31, ptr %r39
    ret i32 0
}
