@g = global i32 zeroinitializer
@h = global i32 zeroinitializer
@f = global i32 zeroinitializer
@e = global i32 zeroinitializer
define i32 @EightWhile()
{
L1:  
    %r1 = load i32, ptr %r0
    %r4 = icmp slt i32 %r1,%r2
    br i1 %r4, label %L1, label %L2
    %r1 = load i32, ptr %r0
    %r4 = add i32 %r1,%r2
    store i32 10, ptr %r0
    br label %L3
    %r2 = load i32, ptr %r1
    %r5 = icmp slt i32 %r2,%r3
    br i1 %r5, label %L4, label %L5
    %r2 = load i32, ptr %r1
    %r5 = add i32 %r2,%r3
    store i32 %r5, ptr %r1
    br label %L6
    %r6 = icmp eq i32 %r2,%r4
    br i1 %r6, label %L7, label %L8
    %r6 = sub i32 %r2,%r4
    store i32 %r6, ptr %r2
    br label %L9
    %r7 = icmp slt i32 %r3,%r5
    br i1 %r7, label %L10, label %L11
    %r7 = add i32 %r3,%r5
    store i32 %r7, ptr %r3
    br label %L12
    %r4 = load i32, ptr @e
    %r5 = load i32, ptr %r4
    %r8 = icmp sgt i32 %r5,%r6
    br i1 %r8, label %L13, label %L14
    %r9 = load i32, ptr @e
    %r10 = load i32, ptr %r9
    %r13 = sub i32 %r10,%r11
    %r14 = load i32, ptr @e
    store i32 %r13, ptr %r14
    br label %L15
    %r15 = load i32, ptr @f
    %r16 = load i32, ptr %r15
    %r19 = icmp sgt i32 %r16,%r17
    br i1 %r19, label %L16, label %L17
    %r20 = load i32, ptr @f
    %r21 = load i32, ptr %r20
    %r24 = sub i32 %r21,%r22
    %r25 = load i32, ptr @f
    store i32 %r24, ptr %r25
    br label %L18
    %r26 = load i32, ptr @g
    %r27 = load i32, ptr %r26
    %r30 = icmp slt i32 %r27,%r28
    br i1 %r30, label %L19, label %L20
    %r31 = load i32, ptr @g
    %r32 = load i32, ptr %r31
    %r35 = add i32 %r32,%r33
    %r36 = load i32, ptr @g
    store i32 %r35, ptr %r36
    br label %L21
    %r37 = load i32, ptr @h
    %r38 = load i32, ptr %r37
    %r41 = icmp slt i32 %r38,%r39
    br i1 %r41, label %L22, label %L23
    %r42 = load i32, ptr @h
    %r43 = load i32, ptr %r42
    %r46 = add i32 %r43,%r44
    %r47 = load i32, ptr @h
    store i32 %r46, ptr %r47
    br label %L22
L2:  
L3:  
    %r1 = load i32, ptr %r0
    %r2 = load i32, ptr %r1
    %r5 = add i32 %r2,%r3
    %r7 = add i32 %r1,%r5
    %r8 = load float, ptr %r7
    %r4 = add i32 %r8,%r2
    %r6 = load i32, ptr @e
    %r7 = load i32, ptr %r6
    %r5 = add i32 %r7,%r3
    %r7 = load i32, ptr @g
    %r8 = load i32, ptr %r7
    %r9 = sub i32 %r5,%r8
    %r10 = load i32, ptr %r9
    %r11 = load i32, ptr @h
    %r12 = load i32, ptr %r11
    %r13 = add i32 %r10,%r12
    %r14 = load float, ptr %r13
    %r15 = sub i32 %r4,%r14
    ret i32 %r15
L4:  
L5:  
L6:  
    %r2 = load i32, ptr %r1
    %r5 = sub i32 %r2,%r3
    store i32 20, ptr %r1
    br label %L1
L7:  
L8:  
L9:  
    %r6 = add i32 %r2,%r4
    store i32 1, ptr %r2
    br label %L4
L10:  
L11:  
L12:  
    %r7 = sub i32 %r3,%r5
    store i32 %r7, ptr %r3
    br label %L7
L13:  
L14:  
L15:  
    %r66 = load i32, ptr @e
    %r67 = load i32, ptr %r66
    %r70 = add i32 %r67,%r68
    %r71 = load i32, ptr @e
    store i32 %r70, ptr %r71
    br label %L10
L16:  
L17:  
L18:  
    %r60 = load i32, ptr @f
    %r61 = load i32, ptr %r60
    %r64 = add i32 %r61,%r62
    %r65 = load i32, ptr @f
    store i32 %r64, ptr %r65
    br label %L13
L19:  
L20:  
L21:  
    %r54 = load i32, ptr @g
    %r55 = load i32, ptr %r54
    %r58 = sub i32 %r55,%r56
    %r59 = load i32, ptr @g
    store i32 %r58, ptr %r59
    br label %L16
L22:  
L23:  
L24:  
    %r48 = load i32, ptr @h
    %r49 = load i32, ptr %r48
    %r52 = sub i32 %r49,%r50
    %r53 = load i32, ptr @h
    store i32 %r52, ptr %r53
    br label %L19
}
define i32 @main()
{
L1:  
    %r17 = load i32, ptr @g
    store i32 1, ptr %r17
    %r19 = load i32, ptr @h
    store i32 2, ptr %r19
    %r21 = load i32, ptr @e
    store i32 4, ptr %r21
    %r23 = load i32, ptr @f
    store i32 2, ptr %r23
    %r24 = call i32 @EightWhile()
    ret i32 %r24
}
