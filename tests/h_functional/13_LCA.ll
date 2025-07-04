@maxn = global i32 0
@n = global i32 zeroinitializer
@m = global i32 zeroinitializer
@f = global [0x [20x i32]] zeroinitializer
@dep = global [0x i32] zeroinitializer
@to = global [0x i32] zeroinitializer
@next = global [0x i32] zeroinitializer
@head = global [0x i32] zeroinitializer
@cnt = global i32 10
define i32 @LCA(i32 %r0,i32 %r16)
{
L1:  
    %r21 = alloca i32
    %r17 = getelementptr [0 x i32], ptr @dep, i32 0, i32 %r16
    %r18 = load i32, ptr %r17
    %r18 = getelementptr [0 x i32], ptr @dep, i32 0, i32 %r17
    %r19 = load float, ptr %r18
    %r20 = icmp slt i32 %r18,%r19
    br i1 %r20, label %L21, label %L22
    store i32 %r16, ptr %r21
    store i32 %r17, ptr %r16
    store i32 %r21, ptr %r17
    br label %L23
L22:  
L24:  
    %r18 = alloca i32
    store i32 19, ptr %r18
    br label %L24
    %r17 = getelementptr [0 x i32], ptr @dep, i32 0, i32 %r16
    %r18 = load i32, ptr %r17
    %r18 = getelementptr [0 x i32], ptr @dep, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = icmp sgt i32 %r18,%r19
    br i1 %r20, label %L25, label %L26
    %r19 = getelementptr i32, ptr %r4, i32 0, i32 %r16, i32 %r18
    %r20 = load i32, ptr %r19
    %r19 = getelementptr i32, ptr %r4, i32 0, i32 %r16, i32 %r18
    %r20 = getelementptr [0 x i32], ptr @dep, i32 0, i32 %r19
    %r21 = load float, ptr %r20
    %r18 = getelementptr [0 x i32], ptr @dep, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = icmp sge i32 %r21,%r19
    %r21 = load float, ptr %r20
    %r22 = and i32 %r20,%r21
    br i1 %r22, label %L27, label %L28
    %r19 = getelementptr i32, ptr %r4, i32 0, i32 %r16, i32 %r18
    store i32 19, ptr %r16
    br label %L29
L25:  
L26:  
L27:  
    %r17 = load i32, ptr %r16
    %r18 = load i32, ptr %r17
    %r19 = icmp eq i32 %r17,%r18
    br i1 %r19, label %L30, label %L31
    ret i32 %r16
    br label %L32
L28:  
L30:  
    %r19 = load i32, ptr %r18
    %r22 = sub i32 %r19,%r20
    store i32 %r22, ptr %r18
    br label %L25
L31:  
L33:  
    store i32 19, ptr %r18
    br label %L33
    %r19 = load i32, ptr %r18
    %r22 = icmp sge i32 %r19,%r20
    br i1 %r22, label %L34, label %L35
    %r19 = getelementptr i32, ptr %r4, i32 0, i32 %r16, i32 %r18
    %r20 = load i32, ptr %r19
    %r19 = getelementptr i32, ptr %r4, i32 0, i32 %r17, i32 %r18
    %r20 = load i32, ptr %r19
    %r21 = icmp ne i32 %r20,%r20
    br i1 %r21, label %L36, label %L37
    %r19 = getelementptr i32, ptr %r4, i32 0, i32 %r16, i32 %r18
    store i32 19, ptr %r16
    %r19 = getelementptr i32, ptr %r4, i32 0, i32 %r17, i32 %r18
    store i32 19, ptr %r17
    br label %L38
L34:  
L35:  
L36:  
    %r18 = getelementptr i32, ptr %r4, i32 0, i32 %r16, i32 %r17
    ret i32 %r18
L37:  
L39:  
    %r19 = load i32, ptr %r18
    %r22 = sub i32 %r19,%r20
    store i32 %r22, ptr %r18
    br label %L34
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
define float @add_edge(i32 %r0,i32 %r5)
{
L1:  
    %r7 = load i32, ptr @cnt
    %r8 = getelementptr [0 x i32], ptr @to, i32 0, i32 %r7
    store float %r6, ptr %r8
    %r6 = getelementptr [0 x i32], ptr @head, i32 0, i32 %r5
    %r7 = load i32, ptr @cnt
    %r8 = getelementptr [0 x i32], ptr @next, i32 0, i32 %r7
    store float %r6, ptr %r8
    %r9 = load i32, ptr @cnt
    %r6 = getelementptr [0 x i32], ptr @head, i32 0, i32 %r5
    store i32 %r9, ptr %r6
    %r7 = load i32, ptr @cnt
    %r8 = load i32, ptr %r7
    %r11 = add i32 %r8,%r9
    %r12 = load i32, ptr @cnt
    store i32 %r11, ptr %r12
    %r8 = getelementptr i32, ptr %r4, i32 0, i32 %r6, i32 %r7
    store float %r5, ptr %r8
}
define float @init()
{
L1:  
    %r12 = alloca i32
    %r11 = getelementptr [0 x i32], ptr @dep, i32 0, i32 %r10
    store float 1, ptr %r11
    store i32 1, ptr %r12
    br label %L12
    %r13 = load i32, ptr %r12
    %r14 = load i32, ptr @n
    %r15 = load i32, ptr %r14
    %r16 = icmp sle i32 %r13,%r15
    br i1 %r16, label %L13, label %L14
    %r18 = sub i32 %r0,%r17
    %r13 = getelementptr [0 x i32], ptr @head, i32 0, i32 %r12
    store i32 %r18, ptr %r13
    %r13 = load i32, ptr %r12
    %r16 = add i32 %r13,%r14
    store i32 %r16, ptr %r12
    br label %L13
L13:  
L14:  
L15:  
}
define float @tree(i32 %r0,i32 %r13)
{
L1:  
    %r15 = alloca i32
    %r14 = getelementptr [0 x i32], ptr @dep, i32 0, i32 %r13
    store i32 %r14, ptr %r14
    store i32 0, ptr %r15
    br label %L15
    %r16 = getelementptr i32, ptr %r4, i32 0, i32 %r13, i32 %r15
    br i1 %r16, label %L16, label %L17
    %r16 = getelementptr i32, ptr %r4, i32 0, i32 %r13, i32 %r15
    %r16 = getelementptr i32, ptr %r4, i32 0, i32 %r16, i32 %r15
    %r16 = load i32, ptr %r15
    %r19 = add i32 %r16,%r17
    %r20 = getelementptr i32, ptr %r4, i32 0, i32 %r13, i32 %r19
    store float 0, ptr %r20
    %r16 = load i32, ptr %r15
    %r19 = add i32 %r16,%r17
    store i32 %r19, ptr %r15
    br label %L16
L16:  
L17:  
L18:  
    %r21 = alloca i32
    %r14 = getelementptr [0 x i32], ptr @head, i32 0, i32 %r13
    store i32 %r14, ptr %r15
    br label %L18
    %r16 = load i32, ptr %r15
    %r18 = sub i32 %r0,%r17
    %r19 = load float, ptr %r18
    %r20 = icmp ne i32 %r16,%r19
    br i1 %r20, label %L19, label %L20
    %r16 = getelementptr [0 x i32], ptr @to, i32 0, i32 %r15
    store i32 0, ptr %r21
    %r15 = load i32, ptr %r14
    %r18 = add i32 %r15,%r16
    %r19 = call float @tree(i32 %r21,float %r18)
    %r16 = getelementptr [0 x i32], ptr @next, i32 0, i32 %r15
    store i32 0, ptr %r15
    br label %L19
L19:  
L20:  
L21:  
}
define i32 @main()
{
L1:  
    %r31 = alloca i32
    %r29 = alloca i32
    %r24 = alloca i32
    %r19 = call i32 @quick_read()
    %r20 = load i32, ptr @n
    store i32 19, ptr %r20
    %r21 = call i32 @quick_read()
    %r22 = load i32, ptr @m
    store i32 %r21, ptr %r22
    %r23 = call i32 @init()
    store i32 1, ptr %r24
    br label %L39
    %r25 = load i32, ptr %r24
    %r26 = load i32, ptr @n
    %r27 = load i32, ptr %r26
    %r28 = icmp ne i32 %r25,%r27
    br i1 %r28, label %L40, label %L41
    %r30 = call i32 @quick_read()
    store i32 %r30, ptr %r29
    %r32 = call i32 @quick_read()
    store i32 %r32, ptr %r31
    %r32 = call i32 @add_edge(i32 %r29,i32 %r31)
    %r25 = load i32, ptr %r24
    %r28 = add i32 %r25,%r26
    store i32 %r28, ptr %r24
    br label %L40
L40:  
L41:  
L42:  
    %r31 = alloca i32
    %r29 = alloca i32
    %r27 = call i32 @tree(i32 %r25,i32 %r26)
    br label %L42
    %r28 = load i32, ptr @m
    br i1 %r28, label %L43, label %L44
    %r30 = call i32 @quick_read()
    store i32 %r30, ptr %r29
    %r32 = call i32 @quick_read()
    store i32 %r32, ptr %r31
    %r32 = call i32 @LCA(i32 %r29,i32 %r31)
    %r33 = call i32 @putint(float %r32)
    %r35 = call i32 @putch(i32 %r34)
    %r36 = load i32, ptr @m
    %r37 = load i32, ptr %r36
    %r40 = sub i32 %r37,%r38
    %r41 = load i32, ptr @m
    store i32 %r40, ptr %r41
    br label %L43
L43:  
L44:  
L45:  
    ret i32 0
}
