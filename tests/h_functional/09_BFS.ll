@n = global i32 zeroinitializer
@m = global i32 zeroinitializer
@maxn = global i32 0
@maxm = global i32 10
@to = global [10x i32] zeroinitializer
@next = global [10x i32] zeroinitializer
@head = global [0x i32] zeroinitializer
@cnt = global i32 0
@que = global [0x i32] zeroinitializer
@h = global i32 zeroinitializer
@tail = global i32 zeroinitializer
@inq = global [0x i32] zeroinitializer
define float @init()
{
L1:  
    %r15 = alloca i32
    store i32 0, ptr %r15
    br label %L12
    %r16 = load i32, ptr %r15
    %r19 = icmp slt i32 %r16,%r17
    br i1 %r19, label %L13, label %L14
    %r21 = sub i32 %r0,%r20
    %r16 = getelementptr [0 x i32], ptr @head, i32 0, i32 %r15
    store i32 %r21, ptr %r16
    %r16 = load i32, ptr %r15
    %r19 = add i32 %r16,%r17
    store i32 %r19, ptr %r15
    br label %L13
L13:  
L14:  
L15:  
}
define i32 @quick_read()
{
L1:  
    %r1 = load i32, ptr %r0
    %r4 = icmp slt i32 %r1,%r2
    %r5 = load i32, ptr %r4
    %r1 = load i32, ptr %r0
    %r4 = icmp sgt i32 %r1,%r2
    %r5 = load i32, ptr %r4
    %r6 = xor i32 %r5,%r5
    br i1 %r6, label %L1, label %L2
    %r1 = load i32, ptr %r0
    %r4 = icmp eq i32 %r1,%r2
    br i1 %r4, label %L3, label %L4
    store i32 0, ptr %r4
    br label %L5
L2:  
L3:  
    br label %L6
    %r1 = load i32, ptr %r0
    %r4 = icmp sge i32 %r1,%r2
    %r5 = load i32, ptr %r4
    %r1 = load i32, ptr %r0
    %r4 = icmp sle i32 %r1,%r2
    %r5 = load i32, ptr %r4
    %r6 = and i32 %r5,%r5
    br i1 %r6, label %L7, label %L8
    %r6 = mul i32 %r2,%r4
    %r7 = load float, ptr %r6
    %r1 = load i32, ptr %r0
    %r2 = add i32 %r7,%r1
    %r6 = sub i32 %r2,%r4
    store i32 %r6, ptr %r2
    %r3 = call i32 @getch()
    store i32 0, ptr %r0
    br label %L7
L4:  
L6:  
    %r5 = call i32 @getch()
    store i32 0, ptr %r0
    br label %L1
L7:  
L8:  
L9:  
    br i1 %r4, label %L9, label %L10
    %r3 = sub i32 %r0,%r2
    ret i32 0
    br label %L11
    ret i32 48
    br label %L11
L10:  
L11:  
L12:  
}
define float @add_edge(i32 %r0,i32 %r6)
{
L1:  
    %r8 = load i32, ptr @cnt
    %r9 = getelementptr [10 x i32], ptr @to, i32 0, i32 %r8
    store float %r7, ptr %r9
    %r7 = getelementptr [0 x i32], ptr @head, i32 0, i32 %r6
    %r8 = load i32, ptr @cnt
    %r9 = getelementptr [10 x i32], ptr @next, i32 0, i32 %r8
    store float %r7, ptr %r9
    %r10 = load i32, ptr @cnt
    %r7 = getelementptr [0 x i32], ptr @head, i32 0, i32 %r6
    store i32 %r10, ptr %r7
    %r8 = load i32, ptr @cnt
    %r9 = load i32, ptr %r8
    %r12 = add i32 %r9,%r10
    %r13 = load i32, ptr @cnt
    store i32 %r12, ptr %r13
    %r7 = load i32, ptr @cnt
    %r8 = getelementptr [10 x i32], ptr @to, i32 0, i32 %r7
    store i32 %r6, ptr %r8
    %r8 = getelementptr [0 x i32], ptr @head, i32 0, i32 %r7
    %r9 = load i32, ptr @cnt
    %r10 = getelementptr [10 x i32], ptr @next, i32 0, i32 %r9
    store i32 %r8, ptr %r10
    %r11 = load i32, ptr @cnt
    %r8 = getelementptr [0 x i32], ptr @head, i32 0, i32 %r7
    store i32 %r11, ptr %r8
    %r9 = load i32, ptr @cnt
    %r10 = load i32, ptr %r9
    %r13 = add i32 %r10,%r11
    %r14 = load i32, ptr @cnt
    store i32 %r13, ptr %r14
}
define float @inqueue(i32 %r0)
{
L1:  
    %r17 = getelementptr [0 x i32], ptr @inq, i32 0, i32 %r16
    store i32 0, ptr %r17
    %r18 = load i32, ptr @tail
    %r19 = load i32, ptr %r18
    %r22 = add i32 %r19,%r20
    %r23 = load i32, ptr @tail
    store i32 %r22, ptr %r23
    %r17 = load i32, ptr @tail
    %r18 = getelementptr [0 x i32], ptr @que, i32 0, i32 %r17
    store i32 %r16, ptr %r18
}
define i32 @pop_queue()
{
L1:  
    %r25 = alloca i32
    %r19 = load i32, ptr @h
    %r20 = load i32, ptr %r19
    %r23 = add i32 %r20,%r21
    %r24 = load i32, ptr @h
    store i32 %r23, ptr %r24
    %r26 = load i32, ptr @h
    %r27 = getelementptr [0 x i32], ptr @que, i32 0, i32 %r26
    store i32 %r27, ptr %r25
    %r28 = load i32, ptr @h
    %r29 = getelementptr [0 x i32], ptr @que, i32 0, i32 %r28
    ret i32 %r29
}
define i32 @same(i32 %r0,i32 %r30)
{
L1:  
    %r39 = alloca i32
    %r32 = alloca i32
    %r33 = load i32, ptr @h
    store i32 0, ptr %r33
    %r35 = load i32, ptr @tail
    store i32 0, ptr %r35
    %r31 = call i32 @inqueue(i32 %r30)
    store i32 0, ptr %r32
    br label %L15
    %r34 = load i32, ptr @h
    %r35 = load i32, ptr %r34
    %r36 = load i32, ptr @tail
    %r37 = load i32, ptr %r36
    %r38 = icmp slt i32 %r35,%r37
    br i1 %r38, label %L16, label %L17
    %r40 = call i32 @pop_queue()
    store i32 %r40, ptr %r39
    %r40 = load i32, ptr %r39
    %r32 = load i32, ptr %r31
    %r33 = icmp eq i32 %r40,%r32
    br i1 %r33, label %L18, label %L19
    store i32 1, ptr %r32
    br label %L20
L16:  
L17:  
L18:  
    %r34 = alloca i32
    store i32 1, ptr %r34
    br label %L27
    %r35 = load i32, ptr %r34
    %r36 = load i32, ptr @tail
    %r37 = load i32, ptr %r36
    %r38 = icmp sle i32 %r35,%r37
    br i1 %r38, label %L28, label %L29
    %r35 = getelementptr [0 x i32], ptr @que, i32 0, i32 %r34
    %r36 = getelementptr [0 x i32], ptr @inq, i32 0, i32 %r35
    store i32 0, ptr %r36
    %r35 = load i32, ptr %r34
    %r38 = add i32 %r35,%r36
    store i32 %r38, ptr %r34
    br label %L28
L19:  
L21:  
    %r33 = alloca i32
    %r40 = getelementptr [0 x i32], ptr @head, i32 0, i32 %r39
    store i32 %r40, ptr %r33
    br label %L21
    %r34 = load i32, ptr %r33
    %r36 = sub i32 %r0,%r35
    %r37 = load i32, ptr %r36
    %r38 = icmp ne i32 %r34,%r37
    br i1 %r38, label %L22, label %L23
    %r34 = getelementptr [10 x i32], ptr @to, i32 0, i32 %r33
    %r35 = getelementptr [0 x i32], ptr @inq, i32 0, i32 %r34
    %r36 = icmp eq i32 %r35,%r0
    br i1 %r36, label %L24, label %L25
    %r34 = getelementptr [10 x i32], ptr @to, i32 0, i32 %r33
    %r35 = call i32 @inqueue(i32 %r34)
    br label %L26
L22:  
L23:  
L24:  
    br label %L16
L25:  
L27:  
    %r34 = getelementptr [10 x i32], ptr @next, i32 0, i32 %r33
    store i32 1, ptr %r33
    br label %L22
L28:  
L29:  
L30:  
    ret i32 %r32
}
define i32 @main()
{
L1:  
    %r39 = alloca i32
    %r33 = call i32 @quick_read()
    %r34 = load i32, ptr @n
    store i32 %r33, ptr %r34
    %r35 = call i32 @quick_read()
    %r36 = load i32, ptr @m
    store i32 1, ptr %r36
    %r37 = call i32 @init()
    br label %L30
    %r38 = load i32, ptr @m
    br i1 %r38, label %L31, label %L32
    %r40 = call i32 @getch()
    store i32 %r40, ptr %r39
    br label %L33
    %r40 = load i32, ptr %r39
    %r43 = icmp ne i32 %r40,%r41
    %r44 = load float, ptr %r43
    %r40 = load i32, ptr %r39
    %r43 = icmp ne i32 %r40,%r41
    %r44 = load float, ptr %r43
    %r45 = and i32 %r44,%r44
    br i1 %r45, label %L34, label %L35
    %r46 = call i32 @getch()
    store i32 %r46, ptr %r39
    br label %L34
L31:  
L32:  
L33:  
    ret i32 0
L34:  
L35:  
L36:  
    %r53 = alloca i32
    %r51 = alloca i32
    %r46 = alloca i32
    %r44 = alloca i32
    %r40 = load i32, ptr %r39
    %r43 = icmp eq i32 %r40,%r41
    br i1 %r43, label %L36, label %L37
    %r45 = call i32 @quick_read()
    store i32 %r45, ptr %r44
    %r47 = call i32 @quick_read()
    store i32 %r47, ptr %r46
    %r47 = call i32 @same(i32 %r44,i32 %r46)
    %r48 = call i32 @putint(float %r47)
    %r50 = call i32 @putch(i32 %r49)
    br label %L38
    %r52 = call i32 @quick_read()
    store i32 %r52, ptr %r51
    %r54 = call i32 @quick_read()
    store i32 %r54, ptr %r53
    %r54 = call i32 @add_edge(i32 %r51,i32 %r53)
    br label %L38
L37:  
L38:  
L39:  
    %r55 = load i32, ptr @m
    %r56 = load i32, ptr %r55
    %r59 = sub i32 %r56,%r57
    %r60 = load i32, ptr @m
    store i32 %r59, ptr %r60
    br label %L31
}
