@sum = global i32 0
@array = global [20x i32] zeroinitializer
define i32 @f(i32 %r0,i32 %r1)
{
L1:  
    ret i32 0
    br label %L2
L3:  
    %r2 = getelementptr [20 x i32], ptr @array, i32 0, i32 %r1
    store i32 1, ptr %r2
    %r2 = load i32, ptr %r1
    %r5 = icmp eq i32 %r2,%r3
    br i1 %r5, label %L3, label %L4
    %r7 = getelementptr [20 x i32], ptr @array, i32 0, i32 %r6
    ret i32 %r7
    br label %L5
    %r2 = load i32, ptr %r1
    %r5 = sub i32 %r2,%r3
    %r6 = getelementptr [20 x i32], ptr @array, i32 0, i32 %r5
    ret i32 0
    br label %L5
L4:  
L5:  
L6:  
}
define i32 @h(i32 %r0)
{
L1:  
    %r14 = load i32, ptr @sum
    %r15 = load i32, ptr %r14
    %r18 = add i32 %r15,%r16
    %r19 = load i32, ptr @sum
    store i32 %r18, ptr %r19
    %r14 = load i32, ptr %r13
    %r17 = icmp slt i32 %r14,%r15
    %r18 = load float, ptr %r17
    %r14 = load i32, ptr %r13
    %r17 = icmp sge i32 %r14,%r15
    %r18 = load float, ptr %r17
    %r19 = xor i32 %r18,%r18
    br i1 %r19, label %L12, label %L13
    ret i32 0
    br label %L14
L13:  
L15:  
    %r14 = getelementptr [20 x i32], ptr @array, i32 0, i32 %r13
    ret i32 %r14
}
define i32 @g(i32 %r0,i32 %r7)
{
L1:  
    %r9 = load i32, ptr @sum
    %r10 = load i32, ptr %r9
    %r13 = add i32 %r10,%r11
    %r14 = load i32, ptr @sum
    store i32 %r13, ptr %r14
    %r8 = load i32, ptr %r7
    %r9 = load i32, ptr %r8
    %r10 = icmp sge i32 %r8,%r9
    %r11 = load float, ptr %r10
    %r8 = load i32, ptr %r7
    %r11 = icmp sge i32 %r8,%r9
    %r13 = xor i32 %r11,%r11
    br i1 %r13, label %L6, label %L7
    ret i32 1
    br label %L8
L7:  
L9:  
    %r8 = getelementptr [20 x i32], ptr @array, i32 0, i32 %r7
    store i32 0, ptr %r8
    %r8 = load i32, ptr %r7
    %r11 = icmp eq i32 %r8,%r9
    br i1 %r11, label %L9, label %L10
    %r13 = getelementptr [20 x i32], ptr @array, i32 0, i32 %r12
    ret i32 %r13
    br label %L11
    %r8 = load i32, ptr %r7
    %r11 = sub i32 %r8,%r9
    %r12 = getelementptr [20 x i32], ptr @array, i32 0, i32 %r11
    ret i32 0
    br label %L11
L10:  
L11:  
L12:  
}
define i32 @main()
{
L1:  
    %r15 = alloca i32
    store i32 3, ptr %r15
    br label %L15
    %r16 = load i32, ptr %r15
    %r19 = icmp slt i32 %r16,%r17
    br i1 %r19, label %L16, label %L17
    %r16 = call i32 @f(i32 %r20,i32 %r15)
    %r16 = call i32 @f(i32 %r18,i32 %r15)
    %r18 = and i32 %r16,%r16
    %r16 = call i32 @f(i32 %r20,i32 %r15)
    %r18 = and i32 %r18,%r16
    %r16 = call i32 @f(i32 %r20,i32 %r15)
    %r18 = and i32 %r18,%r16
    %r16 = call i32 @f(i32 %r20,i32 %r15)
    %r18 = and i32 %r18,%r16
    %r16 = call i32 @f(i32 %r20,i32 %r15)
    %r18 = and i32 %r18,%r16
    %r16 = call i32 @f(i32 %r20,i32 %r15)
    %r18 = and i32 %r18,%r16
    %r16 = call i32 @f(i32 %r20,i32 %r15)
    %r18 = and i32 %r18,%r16
    %r16 = call i32 @f(i32 %r20,i32 %r15)
    %r18 = and i32 %r18,%r16
    %r16 = call i32 @f(i32 %r20,i32 %r15)
    %r18 = and i32 %r18,%r16
    %r16 = call i32 @f(i32 %r20,i32 %r15)
    %r18 = and i32 %r18,%r16
    %r16 = call i32 @f(i32 %r20,i32 %r15)
    %r18 = and i32 %r18,%r16
    %r16 = call i32 @f(i32 %r20,i32 %r15)
    %r18 = and i32 %r18,%r16
    %r16 = call i32 @f(i32 %r20,i32 %r15)
    %r18 = and i32 %r18,%r16
    %r16 = call i32 @f(i32 %r20,i32 %r15)
    %r18 = and i32 %r18,%r16
    %r16 = call i32 @f(i32 %r20,i32 %r15)
    %r18 = and i32 %r18,%r16
    %r16 = call i32 @f(i32 %r20,i32 %r15)
    %r18 = and i32 %r18,%r16
    %r16 = call i32 @f(i32 %r20,i32 %r15)
    %r18 = and i32 %r18,%r16
    %r16 = call i32 @f(i32 %r20,i32 %r15)
    %r18 = and i32 %r18,%r16
    %r16 = call i32 @f(i32 %r20,i32 %r15)
    %r18 = and i32 %r18,%r16
    br i1 %r18, label %L18, label %L19
    br label %L20
L16:  
L17:  
L18:  
    store i32 3, ptr %r15
    br label %L21
    %r16 = load i32, ptr %r15
    %r19 = icmp slt i32 %r16,%r17
    br i1 %r19, label %L22, label %L23
    %r16 = call i32 @g(i32 %r20,i32 %r15)
    %r16 = call i32 @g(i32 %r18,i32 %r15)
    %r18 = xor i32 %r16,%r16
    %r16 = call i32 @g(i32 %r20,i32 %r15)
    %r18 = xor i32 %r18,%r16
    %r16 = call i32 @g(i32 %r20,i32 %r15)
    %r18 = xor i32 %r18,%r16
    %r16 = call i32 @g(i32 %r20,i32 %r15)
    %r18 = xor i32 %r18,%r16
    %r16 = call i32 @g(i32 %r20,i32 %r15)
    %r18 = xor i32 %r18,%r16
    %r16 = call i32 @g(i32 %r20,i32 %r15)
    %r18 = xor i32 %r18,%r16
    %r16 = call i32 @g(i32 %r20,i32 %r15)
    %r18 = xor i32 %r18,%r16
    %r16 = call i32 @g(i32 %r20,i32 %r15)
    %r18 = xor i32 %r18,%r16
    %r16 = call i32 @g(i32 %r20,i32 %r15)
    %r18 = xor i32 %r18,%r16
    %r16 = call i32 @g(i32 %r20,i32 %r15)
    %r18 = xor i32 %r18,%r16
    %r16 = call i32 @g(i32 %r20,i32 %r15)
    %r18 = xor i32 %r18,%r16
    %r16 = call i32 @g(i32 %r20,i32 %r15)
    %r18 = xor i32 %r18,%r16
    %r16 = call i32 @g(i32 %r20,i32 %r15)
    %r18 = xor i32 %r18,%r16
    %r16 = call i32 @g(i32 %r20,i32 %r15)
    %r18 = xor i32 %r18,%r16
    %r16 = call i32 @g(i32 %r20,i32 %r15)
    %r18 = xor i32 %r18,%r16
    %r16 = call i32 @g(i32 %r20,i32 %r15)
    %r18 = xor i32 %r18,%r16
    %r16 = call i32 @g(i32 %r20,i32 %r15)
    %r18 = xor i32 %r18,%r16
    %r16 = call i32 @g(i32 %r20,i32 %r15)
    %r18 = xor i32 %r18,%r16
    %r16 = call i32 @g(i32 %r20,i32 %r15)
    %r18 = xor i32 %r18,%r16
    br i1 %r18, label %L24, label %L25
    br label %L26
L19:  
L21:  
    %r16 = load i32, ptr %r15
    %r19 = add i32 %r16,%r17
    store i32 %r19, ptr %r15
    br label %L16
L22:  
L23:  
L24:  
    store i32 3, ptr %r15
    br label %L27
    %r16 = load i32, ptr %r15
    %r19 = icmp slt i32 %r16,%r17
    %r20 = load i32, ptr %r19
    %r16 = load i32, ptr %r15
    %r19 = sub i32 %r16,%r17
    %r16 = call i32 @f(i32 %r19,i32 %r15)
    %r18 = and i32 %r20,%r16
    br i1 %r18, label %L28, label %L29
    %r16 = load i32, ptr %r15
    %r19 = add i32 %r16,%r17
    store i32 %r19, ptr %r15
    br label %L28
L25:  
L27:  
    %r16 = load i32, ptr %r15
    %r19 = add i32 %r16,%r17
    store i32 %r19, ptr %r15
    br label %L22
L28:  
L29:  
L30:  
    %r16 = alloca i32
    store i32 20, ptr %r16
    %r18 = call i32 @h(i32 %r17)
    %r21 = call i32 @h(i32 %r20)
    %r22 = load float, ptr %r21
    %r23 = and i32 %r18,%r22
    %r24 = load float, ptr %r23
    %r26 = call i32 @h(i32 %r25)
    %r27 = icmp eq i32 %r26,%r0
    %r28 = load float, ptr %r27
    %r29 = xor i32 %r24,%r28
    %r30 = load float, ptr %r29
    %r32 = call i32 @h(i32 %r31)
    %r33 = load float, ptr %r32
    %r34 = xor i32 %r30,%r33
    br i1 %r34, label %L30, label %L31
    store i32 1, ptr %r16
    br label %L32
L31:  
L33:  
    %r17 = load i32, ptr @sum
    %r18 = load i32, ptr %r17
    %r17 = load i32, ptr %r16
    %r18 = add i32 %r18,%r17
    store i32 0, ptr %r16
    %r18 = call i32 @h(i32 %r17)
    %r19 = icmp eq i32 %r18,%r0
    %r22 = call i32 @h(i32 %r21)
    %r23 = load float, ptr %r22
    %r25 = call i32 @h(i32 %r24)
    %r26 = icmp eq i32 %r25,%r0
    %r27 = load float, ptr %r26
    %r28 = and i32 %r23,%r27
    %r29 = load float, ptr %r28
    %r31 = call i32 @h(i32 %r30)
    %r33 = and i32 %r29,%r31
    %r34 = load float, ptr %r33
    %r35 = xor i32 %r19,%r34
    %r38 = call i32 @h(i32 %r37)
    %r39 = icmp eq i32 %r38,%r0
    %r40 = load float, ptr %r39
    %r41 = xor i32 %r35,%r40
    br i1 %r41, label %L33, label %L34
    store i32 1, ptr %r16
    br label %L35
L34:  
L36:  
    %r17 = load i32, ptr @sum
    %r18 = load i32, ptr %r17
    %r17 = load i32, ptr %r16
    %r18 = mul i32 %r18,%r17
    store i32 0, ptr %r16
    %r18 = call i32 @h(i32 %r17)
    %r21 = call i32 @h(i32 %r20)
    %r22 = icmp eq i32 %r21,%r0
    %r23 = load float, ptr %r22
    %r24 = and i32 %r18,%r23
    %r27 = call i32 @h(i32 %r26)
    %r28 = icmp eq i32 %r27,%r0
    %r29 = load float, ptr %r28
    %r30 = xor i32 %r24,%r29
    %r33 = call i32 @h(i32 %r32)
    %r34 = icmp eq i32 %r33,%r0
    %r35 = load float, ptr %r34
    %r36 = xor i32 %r30,%r35
    %r37 = load float, ptr %r36
    %r39 = call i32 @h(i32 %r38)
    %r40 = icmp eq i32 %r39,%r0
    %r41 = load float, ptr %r40
    %r42 = xor i32 %r37,%r41
    %r45 = call i32 @h(i32 %r44)
    %r46 = load float, ptr %r45
    %r48 = call i32 @h(i32 %r47)
    %r49 = load float, ptr %r48
    %r50 = and i32 %r46,%r49
    %r51 = load float, ptr %r50
    %r52 = xor i32 %r42,%r51
    br i1 %r52, label %L36, label %L37
    store i32 1, ptr %r16
    br label %L38
L37:  
L39:  
    %r17 = load i32, ptr @sum
    %r18 = load i32, ptr %r17
    %r17 = load i32, ptr %r16
    %r18 = sub i32 %r18,%r17
    store i32 0, ptr %r16
    %r18 = call i32 @h(i32 %r17)
    %r21 = call i32 @h(i32 %r20)
    %r23 = and i32 %r18,%r21
    %r24 = load float, ptr %r23
    %r26 = call i32 @h(i32 %r25)
    %r27 = icmp eq i32 %r26,%r0
    %r28 = load float, ptr %r27
    %r29 = and i32 %r24,%r28
    %r30 = load float, ptr %r29
    %r32 = call i32 @h(i32 %r31)
    %r33 = icmp eq i32 %r32,%r0
    %r34 = load float, ptr %r33
    %r35 = and i32 %r30,%r34
    %r38 = call i32 @h(i32 %r37)
    %r40 = xor i32 %r35,%r38
    %r41 = load float, ptr %r40
    %r43 = call i32 @h(i32 %r42)
    %r44 = load float, ptr %r43
    %r46 = call i32 @h(i32 %r45)
    %r47 = icmp eq i32 %r46,%r0
    %r49 = and i32 %r44,%r47
    %r50 = load float, ptr %r49
    %r51 = xor i32 %r41,%r50
    %r52 = load float, ptr %r51
    %r54 = call i32 @h(i32 %r53)
    %r55 = load float, ptr %r54
    %r56 = xor i32 %r52,%r55
    br i1 %r56, label %L39, label %L40
    store i32 1, ptr %r16
    br label %L41
L40:  
L42:  
    %r17 = load i32, ptr @sum
    %r18 = load i32, ptr %r17
    %r17 = load i32, ptr %r16
    %r18 = add i32 %r18,%r17
    %r19 = call i32 @putint(i32 %r18)
    ret i32 0
}
