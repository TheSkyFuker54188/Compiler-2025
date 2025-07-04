@maxn = global i32 18
@mod = global i32 1000000007
@dp = global [18x [18x [18x [18x [18x [7x i32]]]]]] zeroinitializer
@list = global [200x i32] zeroinitializer
@cns = global [20x i32] zeroinitializer
define i32 @equal(i32 %r0,i32 %r2)
{
L1:  
    ret i32 1
    br label %L2
L3:  
    ret i32 0
}
define i32 @main()
{
L1:  
    %r42 = alloca i32
    %r37 = alloca i32
    %r32 = alloca i32
    %r27 = alloca i32
    %r22 = alloca i32
    %r17 = alloca i32
    %r15 = alloca i32
    %r16 = call i32 @getint()
    store i32 1, ptr %r15
    store i32 0, ptr %r17
    br label %L24
    %r18 = load i32, ptr %r17
    %r21 = icmp slt i32 %r18,%r19
    br i1 %r21, label %L25, label %L26
    store i32 0, ptr %r22
    br label %L27
    %r23 = load i32, ptr %r22
    %r26 = icmp slt i32 %r23,%r24
    br i1 %r26, label %L28, label %L29
    store i32 0, ptr %r27
    br label %L30
    %r28 = load i32, ptr %r27
    %r31 = icmp slt i32 %r28,%r29
    br i1 %r31, label %L31, label %L32
    store i32 0, ptr %r32
    br label %L33
    %r33 = load i32, ptr %r32
    %r36 = icmp slt i32 %r33,%r34
    br i1 %r36, label %L34, label %L35
    store i32 0, ptr %r37
    br label %L36
    %r38 = load i32, ptr %r37
    %r41 = icmp slt i32 %r38,%r39
    br i1 %r41, label %L37, label %L38
    store i32 0, ptr %r42
    br label %L39
    %r43 = load i32, ptr %r42
    %r46 = icmp slt i32 %r43,%r44
    br i1 %r46, label %L40, label %L41
    %r48 = sub i32 %r0,%r47
    %r43 = getelementptr [18 x [18 x [18 x [18 x [18 x [7 x i32]]]]]], ptr @dp, i32 0, i32 %r17, i32 %r22, i32 %r27, i32 %r32, i32 %r37, i32 %r42
    store i32 %r48, ptr %r43
    %r43 = load i32, ptr %r42
    %r46 = add i32 %r43,%r44
    store i32 %r46, ptr %r42
    br label %L40
L25:  
L26:  
L27:  
    store i32 0, ptr %r17
    br label %L42
    %r18 = load i32, ptr %r17
    %r16 = load i32, ptr %r15
    %r17 = icmp slt i32 %r18,%r16
    br i1 %r17, label %L43, label %L44
    %r18 = call i32 @getint()
    %r18 = getelementptr [200 x i32], ptr @list, i32 0, i32 %r17
    store i32 0, ptr %r18
    %r18 = getelementptr [200 x i32], ptr @list, i32 0, i32 %r17
    %r19 = getelementptr [20 x i32], ptr @cns, i32 0, i32 %r18
    %r20 = load i32, ptr %r19
    %r23 = add i32 %r20,%r21
    %r18 = getelementptr [200 x i32], ptr @list, i32 0, i32 %r17
    %r19 = getelementptr [20 x i32], ptr @cns, i32 0, i32 %r18
    store i32 0, ptr %r19
    %r18 = load i32, ptr %r17
    %r21 = add i32 %r18,%r19
    store i32 0, ptr %r17
    br label %L43
L28:  
L29:  
L30:  
    %r18 = load i32, ptr %r17
    %r21 = add i32 %r18,%r19
    store i32 0, ptr %r17
    br label %L25
L31:  
L32:  
L33:  
    %r23 = load i32, ptr %r22
    %r26 = add i32 %r23,%r24
    store i32 %r26, ptr %r22
    br label %L28
L34:  
L35:  
L36:  
    %r28 = load i32, ptr %r27
    %r31 = add i32 %r28,%r29
    store i32 %r31, ptr %r27
    br label %L31
L37:  
L38:  
L39:  
    %r33 = load i32, ptr %r32
    %r36 = add i32 %r33,%r34
    store i32 %r36, ptr %r32
    br label %L34
L40:  
L41:  
L42:  
    %r38 = load i32, ptr %r37
    %r41 = add i32 %r38,%r39
    store i32 %r41, ptr %r37
    br label %L37
L43:  
L44:  
L45:  
    %r18 = alloca i32
    %r20 = getelementptr [20 x i32], ptr @cns, i32 0, i32 %r19
    %r22 = getelementptr [20 x i32], ptr @cns, i32 0, i32 %r21
    %r24 = getelementptr [20 x i32], ptr @cns, i32 0, i32 %r23
    %r26 = getelementptr [20 x i32], ptr @cns, i32 0, i32 %r25
    %r28 = getelementptr [20 x i32], ptr @cns, i32 0, i32 %r27
    %r30 = call i32 @dfs(i32 %r20,i32 %r22,i32 %r24,float %r26,i32 %r28,i32 %r29)
    store i32 %r30, ptr %r18
    %r19 = call i32 @putint(i32 %r18)
    ret i32 %r18
}
define i32 @dfs(i32 %r0,i32 %r8,i32 %r2,i32 %r9,i32 %r4,i32 %r10)
{
L1:  
    %r14 = getelementptr [18 x [18 x [18 x [18 x [18 x [7 x i32]]]]]], ptr @dp, i32 0, i32 %r8, i32 %r9, i32 %r10, i32 %r11, i32 %r12, i32 %r13
    %r15 = load float, ptr %r14
    %r17 = sub i32 %r0,%r16
    %r18 = load float, ptr %r17
    %r19 = icmp ne i32 %r15,%r18
    br i1 %r19, label %L3, label %L4
    %r14 = getelementptr [18 x [18 x [18 x [18 x [18 x [7 x i32]]]]]], ptr @dp, i32 0, i32 %r8, i32 %r9, i32 %r10, i32 %r11, i32 %r12, i32 %r13
    ret i32 %r14
    br label %L5
L4:  
L6:  
    %r9 = load i32, ptr %r8
    %r10 = load i32, ptr %r9
    %r11 = add i32 %r9,%r10
    %r12 = load i32, ptr %r11
    %r11 = load i32, ptr %r10
    %r12 = add i32 %r12,%r11
    %r13 = load i32, ptr %r12
    %r12 = load i32, ptr %r11
    %r13 = add i32 %r13,%r12
    %r14 = load i32, ptr %r13
    %r13 = load i32, ptr %r12
    %r14 = add i32 %r14,%r13
    %r15 = load float, ptr %r14
    %r18 = icmp eq i32 %r15,%r16
    br i1 %r18, label %L6, label %L7
    ret i32 1
    br label %L8
L7:  
L9:  
    %r20 = alloca i32
    store i32 0, ptr %r20
    br i1 %r8, label %L9, label %L10
    %r21 = load i32, ptr %r20
    %r9 = load i32, ptr %r8
    %r15 = call i32 @equal(i32 %r13,i32 %r14)
    %r16 = load float, ptr %r15
    %r17 = sub i32 %r9,%r16
    %r18 = load float, ptr %r17
    %r9 = load i32, ptr %r8
    %r12 = sub i32 %r9,%r10
    %r14 = call i32 @dfs(i32 %r12,i32 %r9,i32 %r10,i32 %r11,i32 %r12,i32 %r13)
    %r16 = mul i32 %r18,%r14
    %r18 = add i32 %r21,%r16
    %r19 = load float, ptr %r18
    %r22 = srem i32 %r19,%r20
    store i32 %r22, ptr %r20
    br label %L11
L10:  
L12:  
    br i1 %r9, label %L12, label %L13
    %r10 = load i32, ptr %r9
    %r15 = call i32 @equal(i32 %r13,i32 %r14)
    %r16 = load float, ptr %r15
    %r17 = sub i32 %r10,%r16
    %r18 = load float, ptr %r17
    %r9 = load i32, ptr %r8
    %r12 = add i32 %r9,%r10
    %r10 = load i32, ptr %r9
    %r13 = sub i32 %r10,%r11
    %r14 = call i32 @dfs(i32 %r12,i32 %r13,i32 %r10,i32 %r11,i32 %r12,i32 %r13)
    %r16 = mul i32 %r18,%r14
    %r18 = add i32 %r20,%r16
    %r19 = load float, ptr %r18
    %r22 = srem i32 %r19,%r20
    store i32 %r22, ptr %r20
    br label %L14
L13:  
L15:  
    br i1 %r10, label %L15, label %L16
    %r15 = call i32 @equal(i32 %r13,i32 %r14)
    %r16 = load float, ptr %r15
    %r17 = sub i32 %r10,%r16
    %r18 = load float, ptr %r17
    %r10 = load i32, ptr %r9
    %r13 = add i32 %r10,%r11
    %r14 = sub i32 %r10,%r12
    %r14 = call i32 @dfs(i32 %r8,i32 %r13,i32 %r14,i32 %r11,i32 %r12,i32 %r13)
    %r16 = mul i32 %r18,%r14
    %r18 = add i32 %r20,%r16
    %r19 = load float, ptr %r18
    %r22 = srem i32 %r19,%r20
    store i32 %r22, ptr %r20
    br label %L17
L16:  
L18:  
    br i1 %r11, label %L18, label %L19
    %r15 = call i32 @equal(i32 %r13,i32 %r14)
    %r16 = load float, ptr %r15
    %r17 = sub i32 %r11,%r16
    %r18 = load float, ptr %r17
    %r14 = add i32 %r10,%r12
    %r15 = sub i32 %r11,%r13
    %r14 = call i32 @dfs(i32 %r8,i32 %r9,i32 %r14,float %r15,i32 %r12,i32 %r13)
    %r16 = mul i32 %r18,%r14
    %r18 = add i32 %r20,%r16
    %r19 = load float, ptr %r18
    %r22 = srem i32 %r19,%r20
    store i32 %r22, ptr %r20
    br label %L20
L19:  
L21:  
    br i1 %r12, label %L21, label %L22
    %r15 = add i32 %r11,%r13
    %r16 = sub i32 %r12,%r14
    %r18 = call i32 @dfs(i32 %r8,i32 %r9,i32 %r10,float %r15,i32 %r16,i32 %r17)
    %r19 = load float, ptr %r18
    %r20 = mul i32 %r12,%r19
    %r22 = add i32 %r20,%r20
    %r23 = load float, ptr %r22
    %r26 = srem i32 %r23,%r24
    store i32 %r26, ptr %r20
    br label %L23
L22:  
L24:  
    %r24 = srem i32 %r20,%r22
    %r14 = getelementptr [18 x [18 x [18 x [18 x [18 x [7 x i32]]]]]], ptr @dp, i32 0, i32 %r8, i32 %r9, i32 %r10, i32 %r11, i32 %r12, i32 %r13
    store i32 1000000007, ptr %r14
    %r14 = getelementptr [18 x [18 x [18 x [18 x [18 x [7 x i32]]]]]], ptr @dp, i32 0, i32 %r8, i32 %r9, i32 %r10, i32 %r11, i32 %r12, i32 %r13
    ret i32 2
}
