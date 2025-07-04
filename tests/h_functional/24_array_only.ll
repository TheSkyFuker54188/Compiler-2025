@i = global [1x i32] zeroinitializer
@k = global [1x i32] zeroinitializer
define float @inc_impl(i32 %r0,i32 %r0)
{
L1:  
    %r7 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r6
    %r8 = load float, ptr %r7
    %r11 = add i32 %r8,%r9
    %r13 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r12
    store float %r11, ptr %r13
    br label %L2
    %r15 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r14
    %r16 = load float, ptr %r15
    %r19 = mul i32 %r16,%r17
    %r21 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r20
    store float %r19, ptr %r21
    %r2 = load i32, ptr %r1
    %r5 = sub i32 %r2,%r3
    %r6 = call float @inc_impl(i32 %r0,float %r5)
    br label %L2
L2:  
L3:  
}
define float @inc(i32 %r0)
{
L1:  
    %r9 = getelementptr [1 x i32], ptr @k, i32 0, i32 %r8
    %r10 = call float @inc_impl(i32 %r7,i32 %r9)
}
define float @add_impl(i32 %r0,i32 %r11,i32 %r2)
{
L1:  
    %r14 = load i32, ptr %r13
    %r17 = icmp eq i32 %r14,%r15
    br i1 %r17, label %L3, label %L4
    %r19 = getelementptr [0 x i32], ptr %r11, i32 0, i32 %r18
    %r20 = load float, ptr %r19
    %r22 = getelementptr [0 x i32], ptr %r12, i32 0, i32 %r21
    %r23 = load float, ptr %r22
    %r24 = add i32 %r20,%r23
    %r26 = getelementptr [0 x i32], ptr %r11, i32 0, i32 %r25
    store float %r24, ptr %r26
    br label %L5
    %r28 = getelementptr [0 x i32], ptr %r11, i32 0, i32 %r27
    %r29 = load float, ptr %r28
    %r32 = mul i32 %r29,%r30
    %r34 = getelementptr [0 x i32], ptr %r11, i32 0, i32 %r33
    store float %r32, ptr %r34
    %r14 = load i32, ptr %r13
    %r17 = sub i32 %r14,%r15
    %r18 = call float @add_impl(i32 %r11,i32 %r12,i32 %r17)
    br label %L5
L4:  
L5:  
L6:  
}
define float @add(i32 %r0,i32 %r19)
{
L1:  
    %r22 = getelementptr [1 x i32], ptr @k, i32 0, i32 %r21
    %r23 = call float @add_impl(i32 %r19,i32 %r20,float %r22)
}
define float @sub_impl(i32 %r0,i32 %r24,i32 %r2)
{
L1:  
    %r27 = load i32, ptr %r26
    %r30 = icmp eq i32 %r27,%r28
    br i1 %r30, label %L6, label %L7
    %r32 = getelementptr [0 x i32], ptr %r24, i32 0, i32 %r31
    %r33 = load float, ptr %r32
    %r35 = getelementptr [0 x i32], ptr %r25, i32 0, i32 %r34
    %r36 = load float, ptr %r35
    %r37 = sub i32 %r33,%r36
    %r39 = getelementptr [0 x i32], ptr %r24, i32 0, i32 %r38
    store float %r37, ptr %r39
    br label %L8
    %r41 = getelementptr [0 x i32], ptr %r24, i32 0, i32 %r40
    %r42 = load float, ptr %r41
    %r45 = mul i32 %r42,%r43
    %r47 = getelementptr [0 x i32], ptr %r24, i32 0, i32 %r46
    store float %r45, ptr %r47
    %r27 = load i32, ptr %r26
    %r30 = sub i32 %r27,%r28
    %r31 = call float @sub_impl(i32 %r24,i32 %r25,i32 %r30)
    br label %L8
L7:  
L8:  
L9:  
}
define float @sub(i32 %r0,i32 %r32)
{
L1:  
    %r35 = getelementptr [1 x i32], ptr @k, i32 0, i32 %r34
    %r36 = call float @sub_impl(i32 %r32,i32 %r33,float %r35)
}
define i32 @main()
{
L1:  
    %r39 = alloca [1 x [2 x i32]]
    %r38 = alloca [1 x i32]
    %r37 = alloca [1 x i32]
    %r40 = getelementptr [1 x [2 x i32]], ptr %r39, i32 0, i32 0
    %r42 = sub i32 %r0,%r41
    store i32 %r42, ptr %r40
    %r43 = call i32 @getint()
    %r45 = getelementptr [1 x i32], ptr @k, i32 0, i32 %r44
    store float 2, ptr %r45
    %r46 = call i32 @getint()
    %r48 = getelementptr [1 x i32], ptr %r38, i32 0, i32 %r47
    store float 0, ptr %r48
    %r50 = getelementptr [1 x [2 x i32]], ptr %r39, i32 0, i32 %r49
    %r51 = call i32 @getarray(float %r50)
    br label %L9
    %r53 = getelementptr [1 x i32], ptr %r38, i32 0, i32 %r52
    br i1 %r53, label %L10, label %L11
    %r56 = getelementptr [1 x [2 x i32]], ptr %r39, i32 0, i32 %r54, i32 %r55
    %r58 = getelementptr [1 x i32], ptr %r37, i32 0, i32 %r57
    store float %r56, ptr %r58
    br label %L12
    %r60 = getelementptr [1 x i32], ptr %r37, i32 0, i32 %r59
    %r61 = load float, ptr %r60
    %r64 = icmp slt i32 %r61,%r62
    br i1 %r64, label %L13, label %L14
    %r66 = getelementptr [1 x i32], ptr @i, i32 0, i32 %r65
    %r67 = call i32 @putint(float %r66)
    %r69 = getelementptr [1 x i32], ptr %r37, i32 0, i32 %r68
    %r70 = call i32 @putint(float %r69)
    %r72 = getelementptr [1 x i32], ptr %r38, i32 0, i32 %r71
    %r73 = call i32 @putint(float %r72)
    %r76 = getelementptr [1 x [2 x i32]], ptr %r39, i32 0, i32 %r74, i32 %r75
    %r77 = call i32 @putint(float %r76)
    %r79 = getelementptr [1 x [2 x i32]], ptr %r39, i32 0, i32 %r78
    %r39 = call i32 @add(float %r79,i32 %r38)
    %r39 = call i32 @add(i32 %r37,i32 %r38)
    %r41 = getelementptr [1 x [2 x i32]], ptr %r39, i32 0, i32 %r40
    %r39 = call i32 @sub(i32 %r41,i32 %r38)
    br label %L13
L10:  
L11:  
L12:  
    %r55 = call i32 @putch(i32 %r54)
    ret i32 0
L13:  
L14:  
L15:  
    %r40 = load i32, ptr @i
    %r41 = call i32 @inc(i32 %r40)
    %r42 = load i32, ptr @i
    %r44 = getelementptr [1 x [2 x i32]], ptr %r39, i32 0, i32 %r43
    %r45 = call i32 @add(i32 %r42,i32 %r44)
    %r47 = getelementptr [1 x i32], ptr @i, i32 0, i32 %r46
    %r48 = load i32, ptr %r47
    %r51 = getelementptr [1 x [2 x i32]], ptr %r39, i32 0, i32 %r49, i32 %r50
    %r52 = load float, ptr %r51
    %r53 = icmp eq i32 %r48,%r52
    br i1 %r53, label %L15, label %L16
    br label %L11
    br label %L17
L16:  
L18:  
    br label %L10
}
