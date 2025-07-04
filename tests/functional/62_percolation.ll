@array = global [110x i32] zeroinitializer
@n = global i32 zeroinitializer
define float @init(i32 %r0)
{
L1:  
    %r2 = load i32, ptr %r1
    %r1 = load i32, ptr %r0
    %r1 = load i32, ptr %r0
    %r2 = mul i32 %r1,%r1
    %r6 = add i32 %r2,%r4
    %r7 = load float, ptr %r6
    %r8 = icmp sle i32 %r2,%r7
    br i1 %r8, label %L1, label %L2
    %r10 = sub i32 %r0,%r9
    %r2 = getelementptr [110 x i32], ptr @array, i32 0, i32 %r1
    store i32 %r10, ptr %r2
    %r2 = load i32, ptr %r1
    %r5 = add i32 %r2,%r3
    store i32 %r5, ptr %r1
    br label %L1
L2:  
L3:  
}
define i32 @findfa(i32 %r0)
{
L1:  
    %r3 = getelementptr [110 x i32], ptr @array, i32 0, i32 %r2
    %r4 = load i32, ptr %r3
    %r3 = load i32, ptr %r2
    %r4 = icmp eq i32 %r4,%r3
    br i1 %r4, label %L3, label %L4
    ret i32 %r2
    br label %L5
    %r3 = getelementptr [110 x i32], ptr @array, i32 0, i32 %r2
    %r4 = call i32 @findfa(i32 %r3)
    %r3 = getelementptr [110 x i32], ptr @array, i32 0, i32 %r2
    store i32 1, ptr %r3
    %r3 = getelementptr [110 x i32], ptr @array, i32 0, i32 %r2
    ret i32 1
    br label %L5
L4:  
L5:  
L6:  
}
define float @mmerge(i32 %r0,i32 %r4)
{
L1:  
    %r6 = alloca i32
    %r6 = alloca i32
    %r5 = call float @findfa(i32 %r4)
    store i32 %r5, ptr %r6
    %r6 = call float @findfa(i32 %r5)
    store i32 %r6, ptr %r6
    %r7 = load i32, ptr %r6
    %r7 = load i32, ptr %r6
    %r8 = icmp ne i32 %r7,%r7
    br i1 %r8, label %L6, label %L7
    %r7 = getelementptr [110 x i32], ptr @array, i32 0, i32 %r6
    store float %r6, ptr %r7
    br label %L8
L7:  
L9:  
}
define i32 @main()
{
L1:  
    %r14 = alloca i32
    %r8 = alloca i32
    %r12 = alloca i32
    %r10 = alloca i32
    %r11 = alloca i32
    %r10 = alloca i32
    %r9 = alloca i32
    %r8 = alloca i32
    store i32 1, ptr %r8
    br label %L9
    br i1 %r8, label %L10, label %L11
    %r9 = load i32, ptr %r8
    %r12 = sub i32 %r9,%r10
    store i32 1, ptr %r8
    store i32 4, ptr %r6
    store i32 10, ptr %r9
    store i32 0, ptr %r10
    store i32 0, ptr %r12
    %r7 = call i32 @init(i32 %r6)
    %r7 = load i32, ptr %r6
    %r7 = load i32, ptr %r6
    %r8 = mul i32 %r7,%r7
    %r9 = load i32, ptr %r8
    %r12 = add i32 %r9,%r10
    store i32 %r12, ptr %r8
    br label %L12
    %r11 = icmp slt i32 %r10,%r9
    br i1 %r11, label %L13, label %L14
    %r12 = call i32 @getint()
    store i32 %r12, ptr %r10
    %r11 = call i32 @getint()
    store i32 0, ptr %r11
    %r13 = icmp eq i32 %r12,%r0
    br i1 %r13, label %L15, label %L16
    %r7 = load i32, ptr %r6
    %r14 = sub i32 %r10,%r12
    %r15 = load i32, ptr %r14
    %r16 = mul i32 %r7,%r15
    %r17 = load float, ptr %r16
    %r13 = add i32 %r17,%r11
    store i32 0, ptr %r14
    %r15 = getelementptr [110 x i32], ptr @array, i32 0, i32 %r14
    store float %r14, ptr %r15
    %r14 = icmp eq i32 %r10,%r12
    br i1 %r14, label %L18, label %L19
    %r17 = getelementptr [110 x i32], ptr @array, i32 0, i32 %r16
    store float 0, ptr %r17
    %r16 = call i32 @mmerge(i32 %r14,i32 %r15)
    br label %L20
L10:  
L11:  
L12:  
    ret i32 0
L13:  
L14:  
L15:  
    %r13 = icmp eq i32 %r12,%r0
    br i1 %r13, label %L39, label %L40
    %r15 = sub i32 %r0,%r14
    %r16 = call i32 @putint(i32 %r15)
    %r18 = call i32 @putch(i32 %r17)
    br label %L41
L16:  
L18:  
    %r14 = add i32 %r10,%r12
    store i32 1, ptr %r10
    br label %L13
L19:  
L21:  
    %r7 = load i32, ptr %r6
    %r8 = icmp eq i32 %r10,%r7
    br i1 %r8, label %L21, label %L22
    %r9 = getelementptr [110 x i32], ptr @array, i32 0, i32 %r8
    store i32 %r8, ptr %r9
    %r9 = call i32 @mmerge(i32 %r14,i32 %r8)
    br label %L23
L22:  
L24:  
    %r7 = load i32, ptr %r6
    %r8 = icmp slt i32 %r11,%r7
    %r9 = load i32, ptr %r8
    %r15 = load i32, ptr %r14
    %r18 = add i32 %r15,%r16
    %r19 = getelementptr [110 x i32], ptr @array, i32 0, i32 %r18
    %r20 = load float, ptr %r19
    %r22 = sub i32 %r0,%r21
    %r23 = load float, ptr %r22
    %r24 = icmp ne i32 %r20,%r23
    %r25 = load float, ptr %r24
    %r26 = and i32 %r9,%r25
    br i1 %r26, label %L24, label %L25
    %r15 = load i32, ptr %r14
    %r18 = add i32 %r15,%r16
    %r19 = call i32 @mmerge(i32 %r14,float %r18)
    br label %L26
L25:  
L27:  
    %r15 = icmp sgt i32 %r11,%r13
    %r15 = load i32, ptr %r14
    %r18 = sub i32 %r15,%r16
    %r19 = getelementptr [110 x i32], ptr @array, i32 0, i32 %r18
    %r20 = load float, ptr %r19
    %r22 = sub i32 %r0,%r21
    %r23 = load float, ptr %r22
    %r24 = icmp ne i32 %r20,%r23
    %r25 = load float, ptr %r24
    %r26 = and i32 %r15,%r25
    br i1 %r26, label %L27, label %L28
    %r15 = load i32, ptr %r14
    %r18 = sub i32 %r15,%r16
    %r19 = call i32 @mmerge(i32 %r14,float %r18)
    br label %L29
L28:  
L30:  
    %r7 = load i32, ptr %r6
    %r8 = icmp slt i32 %r10,%r7
    %r9 = load i32, ptr %r8
    %r15 = load i32, ptr %r14
    %r7 = load i32, ptr %r6
    %r8 = add i32 %r15,%r7
    %r9 = getelementptr [110 x i32], ptr @array, i32 0, i32 %r8
    %r10 = load i32, ptr %r9
    %r12 = sub i32 %r0,%r11
    %r14 = icmp ne i32 %r10,%r12
    %r15 = load i32, ptr %r14
    %r16 = and i32 %r9,%r15
    br i1 %r16, label %L30, label %L31
    %r15 = load i32, ptr %r14
    %r7 = load i32, ptr %r6
    %r8 = add i32 %r15,%r7
    %r9 = call i32 @mmerge(i32 %r14,i32 %r8)
    br label %L32
L31:  
L33:  
    %r14 = icmp sgt i32 %r10,%r12
    %r15 = load i32, ptr %r14
    %r15 = load i32, ptr %r14
    %r7 = load i32, ptr %r6
    %r8 = sub i32 %r15,%r7
    %r9 = getelementptr [110 x i32], ptr @array, i32 0, i32 %r8
    %r10 = load i32, ptr %r9
    %r12 = sub i32 %r0,%r11
    %r14 = icmp ne i32 %r10,%r12
    %r15 = load i32, ptr %r14
    %r16 = and i32 %r15,%r15
    br i1 %r16, label %L33, label %L34
    %r15 = load i32, ptr %r14
    %r7 = load i32, ptr %r6
    %r8 = sub i32 %r15,%r7
    %r9 = call i32 @mmerge(i32 %r14,i32 %r8)
    br label %L35
L34:  
L36:  
    %r13 = alloca i32
    %r11 = getelementptr [110 x i32], ptr @array, i32 0, i32 %r10
    %r12 = load i32, ptr %r11
    %r14 = sub i32 %r0,%r13
    %r15 = load i32, ptr %r14
    %r16 = icmp ne i32 %r12,%r15
    %r17 = load i32, ptr %r16
    %r9 = getelementptr [110 x i32], ptr @array, i32 0, i32 %r8
    %r10 = load i32, ptr %r9
    %r12 = sub i32 %r0,%r11
    %r14 = icmp ne i32 %r10,%r12
    %r15 = load i32, ptr %r14
    %r16 = and i32 %r17,%r15
    %r17 = load i32, ptr %r16
    %r19 = call i32 @findfa(i32 %r18)
    %r20 = load float, ptr %r19
    %r9 = call i32 @findfa(i32 %r8)
    %r11 = icmp eq i32 %r20,%r9
    %r13 = and i32 %r17,%r11
    br i1 %r13, label %L36, label %L37
    store i32 1, ptr %r12
    %r14 = add i32 %r10,%r12
    store i32 1, ptr %r13
    %r14 = call i32 @putint(i32 %r13)
    %r16 = call i32 @putch(i32 %r15)
    br label %L38
L37:  
L39:  
    br label %L17
L40:  
L42:  
    br label %L10
}
