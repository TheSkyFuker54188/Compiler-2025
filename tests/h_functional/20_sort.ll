@n = global i32 zeroinitializer
@maxn = global i32 0
@cnt = global [0x i32] zeroinitializer
@x = global [0x i32] zeroinitializer
@a = global [0x i32] zeroinitializer
@b = global [0x i32] zeroinitializer
@c = global [0x i32] zeroinitializer
define i32 @main()
{
L1:  
    %r12 = alloca i32
    %r10 = call i32 @quick_read()
    %r11 = load i32, ptr @n
    store i32 %r10, ptr %r11
    store i32 0, ptr %r12
    br label %L42
    %r13 = load i32, ptr %r12
    %r14 = load i32, ptr @n
    %r15 = load i32, ptr %r14
    %r16 = icmp ne i32 %r13,%r15
    br i1 %r16, label %L43, label %L44
    %r17 = call i32 @quick_read()
    %r13 = getelementptr [0 x i32], ptr %r8, i32 0, i32 %r12
    store i32 %r17, ptr %r13
    %r13 = getelementptr [0 x i32], ptr %r8, i32 0, i32 %r12
    %r13 = getelementptr [0 x i32], ptr @b, i32 0, i32 %r12
    store i32 0, ptr %r13
    %r13 = getelementptr [0 x i32], ptr @b, i32 0, i32 %r12
    %r13 = getelementptr [0 x i32], ptr @c, i32 0, i32 %r12
    store i32 0, ptr %r13
    %r13 = load i32, ptr %r12
    %r16 = add i32 %r13,%r14
    store i32 %r16, ptr %r12
    br label %L43
L43:  
L44:  
L45:  
    %r9 = call i32 @sortA(i32 %r8)
    %r10 = load i32, ptr @b
    %r11 = call i32 @sortB(i32 %r10)
    %r12 = load i32, ptr @c
    %r13 = call i32 @sortC(i32 %r12)
    store i32 1, ptr %r12
    br label %L45
    %r13 = load i32, ptr @n
    %r14 = load i32, ptr %r13
    %r13 = load i32, ptr %r12
    %r14 = sub i32 %r14,%r13
    br i1 %r14, label %L46, label %L47
    %r13 = getelementptr [0 x i32], ptr @b, i32 0, i32 %r12
    %r14 = load i32, ptr %r13
    %r13 = getelementptr [0 x i32], ptr %r8, i32 0, i32 %r12
    %r14 = load i32, ptr %r13
    %r15 = sub i32 %r14,%r14
    %r13 = getelementptr [0 x i32], ptr @b, i32 0, i32 %r12
    store i32 %r15, ptr %r13
    %r13 = getelementptr [0 x i32], ptr @c, i32 0, i32 %r12
    %r14 = load i32, ptr %r13
    %r13 = getelementptr [0 x i32], ptr @b, i32 0, i32 %r12
    %r14 = load i32, ptr %r13
    %r15 = sub i32 %r14,%r14
    %r16 = load float, ptr %r15
    %r13 = getelementptr [0 x i32], ptr %r8, i32 0, i32 %r12
    %r14 = load i32, ptr %r13
    %r15 = sub i32 %r16,%r14
    %r13 = getelementptr [0 x i32], ptr @c, i32 0, i32 %r12
    store i32 %r15, ptr %r13
    %r13 = load i32, ptr %r12
    %r16 = add i32 %r13,%r14
    store i32 %r16, ptr %r12
    br label %L46
L46:  
L47:  
L48:  
    store i32 0, ptr %r12
    br label %L48
    %r13 = load i32, ptr %r12
    %r14 = load i32, ptr @n
    %r15 = load i32, ptr %r14
    %r16 = sub i32 %r13,%r15
    br i1 %r16, label %L49, label %L50
    %r13 = getelementptr [0 x i32], ptr @b, i32 0, i32 %r12
    br i1 %r13, label %L51, label %L52
    ret i32 1
    br label %L53
L49:  
L50:  
L51:  
    %r14 = sub i32 %r0,%r13
    ret i32 1
L52:  
L54:  
    %r13 = getelementptr [0 x i32], ptr @c, i32 0, i32 %r12
    br i1 %r13, label %L54, label %L55
    ret i32 1
    br label %L56
L55:  
L57:  
    %r13 = load i32, ptr %r12
    %r16 = add i32 %r13,%r14
    store i32 %r16, ptr %r12
    br label %L49
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
define float @sortA(i32 %r0)
{
L1:  
    %r11 = alloca i32
    %r7 = alloca i32
    %r5 = alloca i32
    store i32 0, ptr %r5
    br label %L12
    %r6 = load i32, ptr %r5
    %r7 = load i32, ptr @n
    %r8 = load i32, ptr %r7
    %r9 = icmp slt i32 %r6,%r8
    br i1 %r9, label %L13, label %L14
    %r6 = load i32, ptr %r5
    %r9 = add i32 %r6,%r7
    store i32 %r9, ptr %r7
    br label %L15
    %r9 = load i32, ptr @n
    %r10 = load i32, ptr %r9
    %r11 = icmp slt i32 %r7,%r10
    br i1 %r11, label %L16, label %L17
    %r6 = getelementptr [0 x i32], ptr %r4, i32 0, i32 %r5
    %r8 = getelementptr [0 x i32], ptr %r4, i32 0, i32 %r7
    %r9 = load float, ptr %r8
    %r10 = icmp sgt i32 %r6,%r9
    br i1 %r10, label %L18, label %L19
    %r6 = getelementptr [0 x i32], ptr %r4, i32 0, i32 %r5
    store i32 0, ptr %r11
    %r8 = getelementptr [0 x i32], ptr %r4, i32 0, i32 %r7
    %r6 = getelementptr [0 x i32], ptr %r4, i32 0, i32 %r5
    store i32 %r8, ptr %r6
    %r8 = getelementptr [0 x i32], ptr %r4, i32 0, i32 %r7
    store float %r11, ptr %r8
    br label %L20
L13:  
L14:  
L15:  
L16:  
L17:  
L18:  
    %r6 = load i32, ptr %r5
    %r9 = add i32 %r6,%r7
    store i32 1, ptr %r5
    br label %L13
L19:  
L21:  
    %r11 = add i32 %r7,%r9
    store i32 %r11, ptr %r7
    br label %L16
}
define float @sortB(i32 %r0)
{
L1:  
    %r9 = alloca i32
    %r7 = alloca i32
    store i32 0, ptr %r7
    %r11 = sub i32 %r0,%r10
    store i32 %r11, ptr %r9
    br label %L21
    %r8 = load i32, ptr %r7
    %r9 = load i32, ptr @n
    %r10 = load i32, ptr %r9
    %r11 = icmp slt i32 %r8,%r10
    br i1 %r11, label %L22, label %L23
    %r8 = getelementptr [0 x i32], ptr %r6, i32 0, i32 %r7
    %r9 = getelementptr [0 x i32], ptr @cnt, i32 0, i32 %r8
    %r10 = load i32, ptr %r9
    %r13 = add i32 %r10,%r11
    %r8 = getelementptr [0 x i32], ptr %r6, i32 0, i32 %r7
    %r9 = getelementptr [0 x i32], ptr @cnt, i32 0, i32 %r8
    store i32 %r13, ptr %r9
    %r8 = getelementptr [0 x i32], ptr %r6, i32 0, i32 %r7
    %r10 = load i32, ptr %r9
    %r11 = icmp sgt i32 %r8,%r10
    br i1 %r11, label %L24, label %L25
    %r8 = getelementptr [0 x i32], ptr %r6, i32 0, i32 %r7
    store i32 0, ptr %r9
    br label %L26
L22:  
L23:  
L24:  
    %r12 = alloca i32
    %r8 = alloca i32
    store i32 0, ptr %r7
    store i32 1, ptr %r8
    br label %L27
    %r8 = load i32, ptr %r7
    %r11 = icmp sle i32 %r8,%r9
    br i1 %r11, label %L28, label %L29
    %r8 = getelementptr [0 x i32], ptr @cnt, i32 0, i32 %r7
    store i32 %r8, ptr %r12
    br label %L30
    br i1 %r12, label %L31, label %L32
    %r9 = getelementptr [0 x i32], ptr %r6, i32 0, i32 %r8
    store i32 %r7, ptr %r9
    %r9 = load i32, ptr %r8
    %r12 = add i32 %r9,%r10
    store i32 %r12, ptr %r8
    %r13 = load i32, ptr %r12
    %r16 = sub i32 %r13,%r14
    store i32 %r16, ptr %r12
    br label %L31
L25:  
L27:  
    %r8 = load i32, ptr %r7
    %r11 = add i32 %r8,%r9
    store i32 1, ptr %r7
    br label %L22
L28:  
L29:  
L30:  
L31:  
L32:  
L33:  
    %r8 = load i32, ptr %r7
    %r11 = add i32 %r8,%r9
    store i32 1, ptr %r7
    br label %L28
}
define float @sortC(i32 %r0)
{
L1:  
    %r10 = alloca i32
    %r14 = alloca i32
    %r9 = alloca i32
    store i32 100, ptr %r9
    br label %L33
    %r10 = load i32, ptr %r9
    %r11 = load i32, ptr @n
    %r12 = load i32, ptr %r11
    %r13 = icmp slt i32 %r10,%r12
    br i1 %r13, label %L34, label %L35
    store i32 %r9, ptr %r14
    %r10 = load i32, ptr %r9
    %r13 = add i32 %r10,%r11
    store i32 %r13, ptr %r10
    br label %L36
    %r11 = load i32, ptr %r10
    %r12 = load i32, ptr @n
    %r13 = load i32, ptr %r12
    %r14 = icmp slt i32 %r11,%r13
    br i1 %r14, label %L37, label %L38
    %r11 = getelementptr [0 x i32], ptr %r8, i32 0, i32 %r10
    %r15 = getelementptr [0 x i32], ptr %r8, i32 0, i32 %r14
    %r16 = load float, ptr %r15
    %r17 = icmp slt i32 %r11,%r16
    br i1 %r17, label %L39, label %L40
    store i32 %r10, ptr %r14
    br label %L41
L34:  
L35:  
L36:  
L37:  
L38:  
L39:  
    %r11 = alloca i32
    %r10 = getelementptr [0 x i32], ptr %r8, i32 0, i32 %r9
    store i32 %r10, ptr %r11
    %r15 = getelementptr [0 x i32], ptr %r8, i32 0, i32 %r14
    %r10 = getelementptr [0 x i32], ptr %r8, i32 0, i32 %r9
    store i32 %r15, ptr %r10
    %r15 = getelementptr [0 x i32], ptr %r8, i32 0, i32 %r14
    store float %r11, ptr %r15
    %r10 = load i32, ptr %r9
    %r13 = add i32 %r10,%r11
    store i32 %r13, ptr %r9
    br label %L34
L40:  
L42:  
    %r11 = load i32, ptr %r10
    %r14 = add i32 %r11,%r12
    store i32 %r14, ptr %r10
    br label %L37
}
