@maxm = global i32 0
@maxn = global i32 10
@n = global i32 zeroinitializer
@m = global i32 zeroinitializer
@u = global [0x i32] zeroinitializer
@v = global [0x i32] zeroinitializer
@c = global [0x i32] zeroinitializer
@fa = global [0x i32] zeroinitializer
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
define i32 @find(i32 %r0)
{
L1:  
    %r6 = load i32, ptr %r5
    %r6 = getelementptr [0 x i32], ptr @fa, i32 0, i32 %r5
    %r7 = load float, ptr %r6
    %r8 = icmp eq i32 %r6,%r7
    br i1 %r8, label %L12, label %L13
    ret i32 %r5
    br label %L14
L13:  
L15:  
    %r6 = alloca i32
    %r6 = getelementptr [0 x i32], ptr @fa, i32 0, i32 %r5
    %r7 = call i32 @find(i32 %r6)
    store i32 %r7, ptr %r6
    %r6 = getelementptr [0 x i32], ptr @fa, i32 0, i32 %r5
    store i32 %r6, ptr %r6
    ret i32 %r6
}
define i32 @same(i32 %r0,i32 %r7)
{
L1:  
    %r8 = call i32 @find(i32 %r7)
    store i32 %r8, ptr %r7
    %r9 = call i32 @find(i32 %r8)
    store i32 %r9, ptr %r8
    %r8 = load i32, ptr %r7
    %r9 = load i32, ptr %r8
    %r10 = icmp eq i32 %r8,%r9
    br i1 %r10, label %L15, label %L16
    ret i32 1
    br label %L17
L16:  
L18:  
    ret i32 0
}
define i32 @prim()
{
L1:  
    %r22 = alloca i32
    %r18 = alloca i32
    %r13 = alloca i32
    store i32 0, ptr %r13
    br label %L18
    %r14 = load i32, ptr %r13
    %r15 = load i32, ptr @m
    %r16 = load i32, ptr %r15
    %r17 = icmp slt i32 %r14,%r16
    br i1 %r17, label %L19, label %L20
    %r14 = load i32, ptr %r13
    %r17 = add i32 %r14,%r15
    store i32 %r17, ptr %r18
    br label %L21
    %r19 = load i32, ptr %r18
    %r20 = load i32, ptr @m
    %r21 = load i32, ptr %r20
    %r22 = icmp slt i32 %r19,%r21
    br i1 %r22, label %L22, label %L23
    %r14 = getelementptr [0 x i32], ptr @c, i32 0, i32 %r13
    %r15 = load i32, ptr %r14
    %r19 = getelementptr [0 x i32], ptr @c, i32 0, i32 %r18
    %r20 = load float, ptr %r19
    %r21 = icmp sgt i32 %r15,%r20
    br i1 %r21, label %L24, label %L25
    %r14 = getelementptr [0 x i32], ptr @u, i32 0, i32 %r13
    store i32 0, ptr %r22
    %r19 = getelementptr [0 x i32], ptr @u, i32 0, i32 %r18
    %r14 = getelementptr [0 x i32], ptr @u, i32 0, i32 %r13
    store i32 %r19, ptr %r14
    %r19 = getelementptr [0 x i32], ptr @u, i32 0, i32 %r18
    store float %r22, ptr %r19
    %r14 = getelementptr [0 x i32], ptr @v, i32 0, i32 %r13
    store i32 0, ptr %r22
    %r19 = getelementptr [0 x i32], ptr @v, i32 0, i32 %r18
    %r14 = getelementptr [0 x i32], ptr @v, i32 0, i32 %r13
    store i32 %r19, ptr %r14
    %r19 = getelementptr [0 x i32], ptr @v, i32 0, i32 %r18
    store float %r22, ptr %r19
    %r14 = getelementptr [0 x i32], ptr @c, i32 0, i32 %r13
    store i32 0, ptr %r22
    %r19 = getelementptr [0 x i32], ptr @c, i32 0, i32 %r18
    %r14 = getelementptr [0 x i32], ptr @c, i32 0, i32 %r13
    store i32 %r19, ptr %r14
    %r19 = getelementptr [0 x i32], ptr @c, i32 0, i32 %r18
    store float %r22, ptr %r19
    br label %L26
L19:  
L20:  
L21:  
    store i32 0, ptr %r13
    br label %L27
    %r14 = load i32, ptr %r13
    %r15 = load i32, ptr @n
    %r16 = load i32, ptr %r15
    %r17 = icmp sle i32 %r14,%r16
    br i1 %r17, label %L28, label %L29
    %r14 = getelementptr [0 x i32], ptr @fa, i32 0, i32 %r13
    store i32 %r13, ptr %r14
    %r14 = load i32, ptr %r13
    %r17 = add i32 %r14,%r15
    store i32 %r17, ptr %r13
    br label %L28
L22:  
L23:  
L24:  
    %r14 = load i32, ptr %r13
    %r17 = add i32 %r14,%r15
    store i32 %r17, ptr %r13
    br label %L19
L25:  
L27:  
    %r19 = load i32, ptr %r18
    %r22 = add i32 %r19,%r20
    store i32 %r22, ptr %r18
    br label %L22
L28:  
L29:  
L30:  
    %r14 = alloca i32
    store i32 0, ptr %r13
    store i32 1, ptr %r14
    br label %L30
    %r14 = load i32, ptr %r13
    %r15 = load i32, ptr @m
    %r16 = load i32, ptr %r15
    %r17 = icmp slt i32 %r14,%r16
    br i1 %r17, label %L31, label %L32
    %r14 = getelementptr [0 x i32], ptr @u, i32 0, i32 %r13
    %r14 = getelementptr [0 x i32], ptr @v, i32 0, i32 %r13
    %r15 = call i32 @same(i32 %r14,i32 %r14)
    br i1 %r15, label %L33, label %L34
    br label %L30
    br label %L35
L31:  
L32:  
L33:  
    ret i32 %r14
L34:  
L36:  
    %r15 = load i32, ptr %r14
    %r14 = getelementptr [0 x i32], ptr @c, i32 0, i32 %r13
    %r15 = load i32, ptr %r14
    %r16 = add i32 %r15,%r15
    store i32 %r16, ptr %r14
    %r14 = getelementptr [0 x i32], ptr @v, i32 0, i32 %r13
    %r14 = getelementptr [0 x i32], ptr @u, i32 0, i32 %r13
    %r15 = call i32 @find(i32 %r14)
    %r16 = getelementptr [0 x i32], ptr @fa, i32 0, i32 %r15
    store float %r14, ptr %r16
    %r14 = load i32, ptr %r13
    %r17 = add i32 %r14,%r15
    store i32 %r17, ptr %r13
    br label %L31
}
define i32 @main()
{
L1:  
    %r19 = alloca i32
    %r17 = alloca i32
    %r15 = alloca i32
    %r16 = call i32 @quick_read()
    store i32 %r16, ptr %r15
    %r18 = call i32 @quick_read()
    store i32 %r18, ptr %r17
    store i32 1, ptr %r19
    br label %L36
    %r20 = load i32, ptr %r19
    %r18 = load i32, ptr %r17
    %r19 = icmp slt i32 %r20,%r18
    br i1 %r19, label %L37, label %L38
    %r20 = call i32 @quick_read()
    %r20 = getelementptr [0 x i32], ptr @u, i32 0, i32 %r19
    store i32 1, ptr %r20
    %r21 = call i32 @quick_read()
    %r20 = getelementptr [0 x i32], ptr @v, i32 0, i32 %r19
    store i32 %r21, ptr %r20
    %r21 = call i32 @quick_read()
    %r20 = getelementptr [0 x i32], ptr @c, i32 0, i32 %r19
    store i32 %r21, ptr %r20
    %r20 = load i32, ptr %r19
    %r23 = add i32 %r20,%r21
    store i32 %r23, ptr %r19
    br label %L37
L37:  
L38:  
L39:  
    %r20 = call i32 @prim()
    ret i32 1
}
