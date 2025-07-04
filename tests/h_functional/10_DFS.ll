@n = global i32 zeroinitializer
@m = global i32 zeroinitializer
@maxn = global i32 0
@maxm = global i32 10
@to = global [10x i32] zeroinitializer
@next = global [10x i32] zeroinitializer
@head = global [0x i32] zeroinitializer
@cnt = global i32 0
@vis = global [0x i32] zeroinitializer
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
define float @clear()
{
L1:  
    %r16 = alloca i32
    store i32 0, ptr %r16
    br label %L15
    %r17 = load i32, ptr %r16
    %r18 = load i32, ptr @n
    %r19 = load i32, ptr %r18
    %r20 = icmp sle i32 %r17,%r19
    br i1 %r20, label %L16, label %L17
    %r17 = getelementptr [0 x i32], ptr @vis, i32 0, i32 %r16
    store i32 0, ptr %r17
    %r17 = load i32, ptr %r16
    %r20 = add i32 %r17,%r18
    store i32 1, ptr %r16
    br label %L16
L16:  
L17:  
L18:  
}
define i32 @same(i32 %r0,i32 %r17)
{
L1:  
    %r18 = getelementptr [0 x i32], ptr @vis, i32 0, i32 %r17
    store i32 1, ptr %r18
    %r18 = load i32, ptr %r17
    %r19 = load i32, ptr %r18
    %r20 = icmp eq i32 %r18,%r19
    br i1 %r20, label %L18, label %L19
    ret i32 0
    br label %L20
L19:  
L21:  
    %r28 = alloca i32
    %r22 = alloca i32
    %r18 = getelementptr [0 x i32], ptr @head, i32 0, i32 %r17
    store i32 %r18, ptr %r22
    br label %L21
    %r23 = load i32, ptr %r22
    %r25 = sub i32 %r0,%r24
    %r26 = load float, ptr %r25
    %r27 = icmp ne i32 %r23,%r26
    br i1 %r27, label %L22, label %L23
    %r23 = getelementptr [10 x i32], ptr @to, i32 0, i32 %r22
    store i32 %r23, ptr %r28
    %r29 = getelementptr [0 x i32], ptr @vis, i32 0, i32 %r28
    %r30 = icmp eq i32 %r29,%r0
    %r31 = load float, ptr %r30
    %r19 = call i32 @same(i32 %r28,i32 %r18)
    %r21 = and i32 %r31,%r19
    br i1 %r21, label %L24, label %L25
    ret i32 1
    br label %L26
L22:  
L23:  
L24:  
    ret i32 0
L25:  
L27:  
    %r23 = getelementptr [10 x i32], ptr @next, i32 0, i32 %r22
    store i32 %r23, ptr %r22
    br label %L22
}
define i32 @main()
{
L1:  
    %r30 = alloca i32
    %r24 = call i32 @quick_read()
    %r25 = load i32, ptr @n
    store i32 1, ptr %r25
    %r26 = call i32 @quick_read()
    %r27 = load i32, ptr @m
    store i32 %r26, ptr %r27
    %r28 = call i32 @init()
    br label %L27
    %r29 = load i32, ptr @m
    br i1 %r29, label %L28, label %L29
    %r31 = call i32 @getch()
    store i32 %r31, ptr %r30
    br label %L30
    %r31 = load i32, ptr %r30
    %r34 = icmp ne i32 %r31,%r32
    %r35 = load float, ptr %r34
    %r31 = load i32, ptr %r30
    %r34 = icmp ne i32 %r31,%r32
    %r35 = load float, ptr %r34
    %r36 = and i32 %r35,%r35
    br i1 %r36, label %L31, label %L32
    %r37 = call i32 @getch()
    store i32 %r37, ptr %r30
    br label %L31
L28:  
L29:  
L30:  
    ret i32 0
L31:  
L32:  
L33:  
    %r44 = alloca i32
    %r42 = alloca i32
    %r37 = alloca i32
    %r35 = alloca i32
    %r31 = load i32, ptr %r30
    %r34 = icmp eq i32 %r31,%r32
    br i1 %r34, label %L33, label %L34
    %r36 = call i32 @quick_read()
    store i32 %r36, ptr %r35
    %r38 = call i32 @quick_read()
    store i32 %r38, ptr %r37
    %r39 = call i32 @clear()
    %r38 = call i32 @same(i32 %r35,i32 %r37)
    %r39 = call i32 @putint(float %r38)
    %r41 = call i32 @putch(i32 %r40)
    br label %L35
    %r43 = call i32 @quick_read()
    store i32 %r43, ptr %r42
    %r45 = call i32 @quick_read()
    store i32 %r45, ptr %r44
    %r45 = call i32 @add_edge(i32 %r42,i32 %r44)
    br label %L35
L34:  
L35:  
L36:  
    %r46 = load i32, ptr @m
    %r47 = load i32, ptr %r46
    %r50 = sub i32 %r47,%r48
    %r51 = load i32, ptr @m
    store i32 %r50, ptr %r51
    br label %L28
}
