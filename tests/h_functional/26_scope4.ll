@a = global i32 zeroinitializer
@sum = global i32 zeroinitializer
@count = global i32 0
define i32 @getA()
{
L1:  
    %r1 = load i32, ptr @count
    %r2 = load i32, ptr %r1
    %r5 = add i32 %r2,%r3
    %r6 = load i32, ptr @count
    store i32 %r5, ptr %r6
    %r7 = load i32, ptr @count
    ret i32 %r7
}
define float @f2()
{
L1:  
    %r17 = alloca i32
    %r17 = load i32, ptr @sum
    %r18 = load i32, ptr %r17
    %r14 = load i32, ptr %r13
    %r15 = add i32 %r18,%r14
    %r16 = load i32, ptr @sum
    store i32 %r15, ptr %r16
    %r18 = call float @getA()
    store i32 %r18, ptr %r17
    %r19 = load i32, ptr @sum
    %r20 = load i32, ptr %r19
    %r18 = load i32, ptr %r17
    %r19 = add i32 %r20,%r18
    %r20 = load i32, ptr @sum
    store i32 %r19, ptr %r20
}
define float @f1(i32 %r0)
{
L1:  
    %r13 = alloca i32
    %r14 = call float @getA()
    store i32 %r14, ptr %r13
    %r15 = load i32, ptr @sum
    %r16 = load i32, ptr %r15
    %r14 = load i32, ptr %r13
    %r15 = add i32 %r16,%r14
    %r16 = load i32, ptr @sum
    store i32 %r15, ptr %r16
    br label %L2
L3:  
    %r17 = load i32, ptr @sum
    %r18 = load i32, ptr %r17
    %r14 = load i32, ptr %r13
    %r15 = add i32 %r18,%r14
    %r16 = load i32, ptr @sum
    store i32 %r15, ptr %r16
    %r17 = load i32, ptr @sum
    %r18 = load i32, ptr %r17
    %r14 = load i32, ptr %r13
    %r15 = add i32 %r18,%r14
    %r16 = load i32, ptr @sum
    store i32 %r15, ptr %r16
}
define float @f3()
{
L1:  
    %r25 = alloca i32
    %r21 = alloca i32
    %r22 = call float @getA()
    store i32 %r22, ptr %r21
    %r23 = load i32, ptr @sum
    %r24 = load i32, ptr %r23
    %r22 = load i32, ptr %r21
    %r23 = add i32 %r24,%r22
    %r24 = load i32, ptr @sum
    store i32 %r23, ptr %r24
    %r25 = call float @getA()
    store i32 %r25, ptr %r21
    %r22 = load i32, ptr @sum
    %r23 = load i32, ptr %r22
    %r22 = load i32, ptr %r21
    %r23 = add i32 %r23,%r22
    %r24 = load i32, ptr @sum
    store i32 %r23, ptr %r24
    %r26 = call float @getA()
    store i32 %r26, ptr %r25
    %r27 = load i32, ptr @sum
    %r28 = load i32, ptr %r27
    %r26 = load i32, ptr %r25
    %r27 = add i32 %r28,%r26
    %r28 = load i32, ptr @sum
    store i32 %r27, ptr %r28
}
define i32 @main()
{
L1:  
    %r49 = alloca i32
    %r43 = alloca i32
    %r39 = alloca i32
    %r37 = alloca i32
    %r33 = alloca i32
    %r29 = alloca i32
    %r30 = load i32, ptr @sum
    store i32 0, ptr %r30
    %r31 = call i32 @getA()
    store i32 %r31, ptr %r25
    %r26 = load i32, ptr @sum
    %r27 = load i32, ptr %r26
    %r26 = load i32, ptr %r25
    %r27 = add i32 %r27,%r26
    %r28 = load i32, ptr @sum
    store i32 %r27, ptr %r28
    %r30 = call i32 @getA()
    store i32 %r30, ptr %r29
    %r30 = call i32 @f1(i32 %r29)
    %r31 = call i32 @f2()
    %r32 = call i32 @f3()
    %r30 = call i32 @f1(i32 %r29)
    %r31 = call i32 @f2()
    %r32 = call i32 @f3()
    %r34 = call i32 @getA()
    store i32 %r34, ptr %r33
    %r34 = call i32 @f1(i32 %r33)
    %r35 = call i32 @f2()
    %r36 = call i32 @f3()
    %r38 = call i32 @getA()
    store i32 %r38, ptr %r37
    %r40 = call i32 @getA()
    store i32 %r40, ptr %r39
    %r40 = call i32 @f1(i32 %r39)
    %r41 = call i32 @f2()
    %r42 = call i32 @f3()
    %r44 = call i32 @getA()
    store i32 %r44, ptr %r43
    %r44 = call i32 @f1(i32 %r43)
    %r45 = call i32 @f2()
    %r46 = call i32 @f3()
    %r47 = call i32 @getA()
    store i32 %r47, ptr %r43
    %r44 = call i32 @f1(i32 %r43)
    %r45 = call i32 @f2()
    %r46 = call i32 @f3()
    %r44 = call i32 @f1(i32 %r43)
    %r45 = call i32 @f2()
    %r46 = call i32 @f3()
    br label %L3
    br i1 %r47, label %L4, label %L5
    br label %L6
    br i1 %r48, label %L7, label %L8
    store i32 0, ptr %r49
    br label %L9
    %r50 = load i32, ptr %r49
    %r53 = icmp slt i32 %r50,%r51
    br i1 %r53, label %L10, label %L11
    br label %L12
    br i1 %r54, label %L13, label %L14
    br i1 %r55, label %L15, label %L16
    %r44 = call i32 @f1(i32 %r43)
    %r45 = call i32 @f2()
    %r46 = call i32 @f3()
    br label %L14
    br label %L17
L4:  
L5:  
L6:  
    %r50 = load i32, ptr @sum
    %r51 = call i32 @putint(i32 %r50)
    ret i32 0
L7:  
L8:  
L9:  
    br label %L5
    br label %L4
L10:  
L11:  
L12:  
    br label %L8
    br label %L8
    br label %L7
L13:  
L14:  
L15:  
    %r54 = alloca i32
    %r50 = load i32, ptr %r49
    %r53 = icmp eq i32 %r50,%r51
    br i1 %r53, label %L18, label %L19
    %r55 = call i32 @getA()
    store i32 1, ptr %r54
    %r55 = call i32 @f1(i32 %r54)
    %r56 = call i32 @f2()
    %r57 = call i32 @f3()
    %r50 = load i32, ptr %r49
    %r53 = add i32 %r50,%r51
    store i32 %r53, ptr %r49
    br label %L9
    br label %L20
    %r55 = call i32 @f1(i32 %r54)
    %r56 = call i32 @f2()
    %r57 = call i32 @f3()
    br label %L20
L16:  
L18:  
    %r47 = call i32 @getA()
    store i32 1, ptr %r43
    br label %L13
L19:  
L20:  
L21:  
    %r58 = call i32 @getA()
    store i32 %r58, ptr %r54
    %r50 = load i32, ptr %r49
    %r53 = add i32 %r50,%r51
    store i32 %r53, ptr %r49
    br label %L10
}
