@n = global i32 zeroinitializer
@m = global i32 zeroinitializer
@fa = global [100005x i32] zeroinitializer
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
define float @init()
{
L1:  
    %r3 = alloca i32
    store i32 10, ptr %r3
    br label %L12
    %r4 = load i32, ptr %r3
    %r5 = load i32, ptr @n
    %r6 = load i32, ptr %r5
    %r7 = icmp sle i32 %r4,%r6
    br i1 %r7, label %L13, label %L14
    %r4 = getelementptr [100005 x i32], ptr @fa, i32 0, i32 %r3
    store i32 %r3, ptr %r4
    %r4 = load i32, ptr %r3
    %r7 = add i32 %r4,%r5
    store i32 %r7, ptr %r3
    br label %L13
L13:  
L14:  
L15:  
}
define i32 @find(i32 %r0)
{
L1:  
    %r5 = alloca i32
    %r5 = getelementptr [100005 x i32], ptr @fa, i32 0, i32 %r4
    %r6 = load i32, ptr %r5
    %r5 = load i32, ptr %r4
    %r6 = icmp eq i32 %r6,%r5
    br i1 %r6, label %L15, label %L16
    ret i32 %r4
    br label %L17
    %r5 = getelementptr [100005 x i32], ptr @fa, i32 0, i32 %r4
    %r6 = call i32 @find(i32 %r5)
    store i32 %r6, ptr %r5
    %r5 = getelementptr [100005 x i32], ptr @fa, i32 0, i32 %r4
    store i32 %r5, ptr %r5
    ret i32 %r5
    br label %L17
L16:  
L17:  
L18:  
}
define i32 @same(i32 %r0,i32 %r6)
{
L1:  
    %r7 = call i32 @find(i32 %r6)
    %r8 = load i32, ptr %r7
    %r8 = call i32 @find(i32 %r7)
    %r9 = load float, ptr %r8
    %r10 = icmp eq i32 %r8,%r9
    br i1 %r10, label %L18, label %L19
    ret i32 1
    br label %L20
L19:  
L21:  
    ret i32 0
}
define i32 @main()
{
L1:  
    %r19 = alloca i32
    %r13 = call i32 @quick_read()
    %r14 = load i32, ptr @n
    store i32 %r13, ptr %r14
    %r15 = call i32 @quick_read()
    %r16 = load i32, ptr @m
    store i32 %r15, ptr %r16
    %r17 = call i32 @init()
    br label %L21
    %r18 = load i32, ptr @m
    br i1 %r18, label %L22, label %L23
    %r20 = call i32 @getch()
    store i32 %r20, ptr %r19
    br label %L24
    %r20 = load i32, ptr %r19
    %r23 = icmp ne i32 %r20,%r21
    %r24 = load float, ptr %r23
    %r20 = load i32, ptr %r19
    %r23 = icmp ne i32 %r20,%r21
    %r24 = load float, ptr %r23
    %r25 = and i32 %r24,%r24
    br i1 %r25, label %L25, label %L26
    %r26 = call i32 @getch()
    store i32 %r26, ptr %r19
    br label %L25
L22:  
L23:  
L24:  
    ret i32 0
L25:  
L26:  
L27:  
    %r34 = alloca i32
    %r31 = alloca i32
    %r26 = alloca i32
    %r24 = alloca i32
    %r20 = load i32, ptr %r19
    %r23 = icmp eq i32 %r20,%r21
    br i1 %r23, label %L27, label %L28
    %r25 = call i32 @quick_read()
    store i32 %r25, ptr %r24
    %r27 = call i32 @quick_read()
    store i32 %r27, ptr %r26
    %r27 = call i32 @same(i32 %r24,i32 %r26)
    %r28 = call i32 @putint(float %r27)
    %r30 = call i32 @putch(i32 %r29)
    br label %L29
    %r32 = call i32 @quick_read()
    %r33 = call i32 @find(float %r32)
    store i32 %r33, ptr %r31
    %r35 = call i32 @quick_read()
    %r36 = call i32 @find(float %r35)
    store i32 %r36, ptr %r34
    %r32 = getelementptr [100005 x i32], ptr @fa, i32 0, i32 %r31
    store float %r34, ptr %r32
    br label %L29
L28:  
L29:  
L30:  
    %r33 = load i32, ptr @m
    %r34 = load i32, ptr %r33
    %r37 = sub i32 %r34,%r35
    %r38 = load i32, ptr @m
    store i32 %r37, ptr %r38
    br label %L22
}
