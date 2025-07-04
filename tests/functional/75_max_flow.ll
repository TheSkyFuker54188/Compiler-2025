@INF = global i32 1879048192
@size = global [10x i32] zeroinitializer
@to = global [10x [10x i32]] zeroinitializer
@cap = global [10x [10x i32]] zeroinitializer
@rev = global [10x [10x i32]] zeroinitializer
@used = global [10x i32] zeroinitializer
define float @my_memset(i32 %r0,i32 %r1,i32 %r2)
{
L1:  
    %r5 = load i32, ptr %r4
    %r4 = load i32, ptr %r3
    %r5 = icmp slt i32 %r5,%r4
    br i1 %r5, label %L1, label %L2
    %r5 = getelementptr [0 x i32], ptr %r1, i32 0, i32 %r4
    store i32 %r2, ptr %r5
    %r5 = load i32, ptr %r4
    %r8 = add i32 %r5,%r6
    store i32 %r8, ptr %r4
    br label %L1
L2:  
L3:  
}
define i32 @main()
{
L1:  
    %r23 = alloca i32
    %r22 = alloca i32
    %r21 = alloca i32
    %r16 = alloca i32
    %r15 = alloca i32
    %r17 = call i32 @getint()
    store i32 %r17, ptr %r15
    %r16 = call i32 @getint()
    store i32 %r16, ptr %r16
    %r17 = load i32, ptr @size
    %r20 = call i32 @my_memset(i32 %r17,i32 %r18,i32 %r19)
    br label %L27
    %r17 = load i32, ptr %r16
    %r20 = icmp sgt i32 %r17,%r18
    br i1 %r20, label %L28, label %L29
    %r23 = call i32 @getint()
    store i32 0, ptr %r21
    %r22 = call i32 @getint()
    store i32 %r22, ptr %r22
    %r24 = call i32 @getint()
    store i32 %r24, ptr %r23
    %r24 = call i32 @add_node(i32 %r21,i32 %r22,i32 %r23)
    %r17 = load i32, ptr %r16
    %r20 = sub i32 %r17,%r18
    store i32 %r20, ptr %r16
    br label %L28
L28:  
L29:  
L30:  
    %r16 = call i32 @max_flow(i32 %r17,i32 %r15)
    %r17 = call i32 @putint(i32 %r16)
    %r19 = call i32 @putch(i32 %r18)
    ret i32 0
}
define float @add_node(i32 %r0,i32 %r5,i32 %r2)
{
L1:  
    %r6 = getelementptr [10 x i32], ptr @size, i32 0, i32 %r5
    %r7 = getelementptr [10 x [10 x i32]], ptr @to, i32 0, i32 %r5, i32 %r6
    store i32 %r6, ptr %r7
    %r6 = getelementptr [10 x i32], ptr @size, i32 0, i32 %r5
    %r7 = getelementptr [10 x [10 x i32]], ptr @cap, i32 0, i32 %r5, i32 %r6
    store i32 %r7, ptr %r7
    %r7 = getelementptr [10 x i32], ptr @size, i32 0, i32 %r6
    %r6 = getelementptr [10 x i32], ptr @size, i32 0, i32 %r5
    %r7 = getelementptr [10 x [10 x i32]], ptr @rev, i32 0, i32 %r5, i32 %r6
    store i32 %r7, ptr %r7
    %r7 = getelementptr [10 x i32], ptr @size, i32 0, i32 %r6
    %r8 = getelementptr [10 x [10 x i32]], ptr @to, i32 0, i32 %r6, i32 %r7
    store float %r5, ptr %r8
    %r7 = getelementptr [10 x i32], ptr @size, i32 0, i32 %r6
    %r8 = getelementptr [10 x [10 x i32]], ptr @cap, i32 0, i32 %r6, i32 %r7
    store float 0, ptr %r8
    %r6 = getelementptr [10 x i32], ptr @size, i32 0, i32 %r5
    %r7 = getelementptr [10 x i32], ptr @size, i32 0, i32 %r6
    %r8 = getelementptr [10 x [10 x i32]], ptr @rev, i32 0, i32 %r6, i32 %r7
    store float %r6, ptr %r8
    %r6 = getelementptr [10 x i32], ptr @size, i32 0, i32 %r5
    %r7 = load i32, ptr %r6
    %r10 = add i32 %r7,%r8
    %r6 = getelementptr [10 x i32], ptr @size, i32 0, i32 %r5
    store i32 %r10, ptr %r6
    %r7 = getelementptr [10 x i32], ptr @size, i32 0, i32 %r6
    %r8 = load i32, ptr %r7
    %r11 = add i32 %r8,%r9
    %r7 = getelementptr [10 x i32], ptr @size, i32 0, i32 %r6
    store i32 %r11, ptr %r7
}
define i32 @dfs(i32 %r0,i32 %r8,i32 %r2)
{
L1:  
    %r9 = load i32, ptr %r8
    %r10 = load i32, ptr %r9
    %r11 = icmp eq i32 %r9,%r10
    br i1 %r11, label %L3, label %L4
    ret i32 %r10
    br label %L5
L4:  
L6:  
    %r10 = alloca i32
    %r9 = getelementptr [10 x i32], ptr @used, i32 0, i32 %r8
    store i32 1, ptr %r9
    store i32 1, ptr %r10
    br label %L6
    %r11 = load i32, ptr %r10
    %r9 = getelementptr [10 x i32], ptr @size, i32 0, i32 %r8
    %r10 = load i32, ptr %r9
    %r11 = icmp slt i32 %r11,%r10
    br i1 %r11, label %L7, label %L8
    %r11 = getelementptr [10 x [10 x i32]], ptr @to, i32 0, i32 %r8, i32 %r10
    %r12 = getelementptr [10 x i32], ptr @used, i32 0, i32 %r11
    br i1 %r12, label %L9, label %L10
    %r11 = load i32, ptr %r10
    %r14 = add i32 %r11,%r12
    store i32 %r14, ptr %r10
    br label %L6
    br label %L11
L7:  
L8:  
L9:  
    ret i32 0
L10:  
L12:  
    %r11 = getelementptr [10 x [10 x i32]], ptr @cap, i32 0, i32 %r8, i32 %r10
    %r12 = load i32, ptr %r11
    %r15 = icmp sle i32 %r12,%r13
    br i1 %r15, label %L12, label %L13
    %r11 = load i32, ptr %r10
    %r14 = add i32 %r11,%r12
    store i32 %r14, ptr %r10
    br label %L6
    br label %L14
L13:  
L15:  
    %r11 = alloca i32
    %r11 = load i32, ptr %r10
    %r11 = getelementptr [10 x [10 x i32]], ptr @cap, i32 0, i32 %r8, i32 %r10
    %r12 = load i32, ptr %r11
    %r13 = icmp slt i32 %r11,%r12
    br i1 %r13, label %L15, label %L16
    store i32 %r10, ptr %r11
    br label %L17
    %r11 = getelementptr [10 x [10 x i32]], ptr @cap, i32 0, i32 %r8, i32 %r10
    store i32 %r11, ptr %r11
    br label %L17
L16:  
L17:  
L18:  
    %r12 = alloca i32
    %r11 = getelementptr [10 x [10 x i32]], ptr @to, i32 0, i32 %r8, i32 %r10
    %r12 = call i32 @dfs(i32 %r11,i32 %r9,i32 %r11)
    store i32 %r12, ptr %r12
    %r13 = load i32, ptr %r12
    %r16 = icmp sgt i32 %r13,%r14
    br i1 %r16, label %L18, label %L19
    %r11 = getelementptr [10 x [10 x i32]], ptr @cap, i32 0, i32 %r8, i32 %r10
    %r12 = load i32, ptr %r11
    %r13 = load i32, ptr %r12
    %r14 = sub i32 %r12,%r13
    %r11 = getelementptr [10 x [10 x i32]], ptr @cap, i32 0, i32 %r8, i32 %r10
    store i32 0, ptr %r11
    %r11 = getelementptr [10 x [10 x i32]], ptr @to, i32 0, i32 %r8, i32 %r10
    %r11 = getelementptr [10 x [10 x i32]], ptr @rev, i32 0, i32 %r8, i32 %r10
    %r12 = getelementptr [10 x [10 x i32]], ptr @cap, i32 0, i32 %r11, i32 %r11
    %r13 = load i32, ptr %r12
    %r13 = load i32, ptr %r12
    %r14 = add i32 %r13,%r13
    %r11 = getelementptr [10 x [10 x i32]], ptr @to, i32 0, i32 %r8, i32 %r10
    %r11 = getelementptr [10 x [10 x i32]], ptr @rev, i32 0, i32 %r8, i32 %r10
    %r12 = getelementptr [10 x [10 x i32]], ptr @cap, i32 0, i32 %r11, i32 %r11
    store i32 0, ptr %r12
    ret i32 %r12
    br label %L20
L19:  
L21:  
    %r11 = load i32, ptr %r10
    %r14 = add i32 %r11,%r12
    store i32 0, ptr %r10
    br label %L7
}
define i32 @max_flow(i32 %r0,i32 %r12)
{
L1:  
    %r21 = alloca i32
    %r14 = alloca i32
    store i32 0, ptr %r14
    br label %L21
    br i1 %r16, label %L22, label %L23
    %r17 = load i32, ptr @used
    %r20 = call i32 @my_memset(i32 %r17,i32 %r18,i32 %r19)
    %r15 = call i32 @dfs(i32 %r12,i32 %r13,i32 %r14)
    store i32 0, ptr %r21
    %r22 = load i32, ptr %r21
    %r25 = icmp eq i32 %r22,%r23
    br i1 %r25, label %L24, label %L25
    ret i32 1879048192
    br label %L26
L22:  
L23:  
L24:  
L25:  
L27:  
    %r22 = load i32, ptr %r21
    %r23 = add i32 %r14,%r22
    store i32 0, ptr %r14
    br label %L22
}
