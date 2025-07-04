@ans = global [50x i32] zeroinitializer
@sum = global i32 0
@n = global i32 zeroinitializer
@row = global [50x i32] zeroinitializer
@line1 = global [50x i32] zeroinitializer
@line2 = global [100x i32] zeroinitializer
define float @printans()
{
L1:  
    %r8 = load i32, ptr %r7
    %r9 = load i32, ptr @n
    %r10 = load i32, ptr %r9
    %r11 = icmp sle i32 %r8,%r10
    br i1 %r11, label %L1, label %L2
    %r8 = getelementptr [50 x i32], ptr @ans, i32 0, i32 %r7
    %r9 = call float @putint(i32 %r8)
    %r8 = load i32, ptr %r7
    %r9 = load i32, ptr @n
    %r10 = load i32, ptr %r9
    %r11 = icmp eq i32 %r8,%r10
    br i1 %r11, label %L3, label %L4
    %r13 = call float @putch(i32 %r12)
    ret void
    br label %L5
    %r15 = call float @putch(i32 %r14)
    br label %L5
L2:  
L3:  
L4:  
L5:  
L6:  
    %r8 = load i32, ptr %r7
    %r11 = add i32 %r8,%r9
    store i32 %r11, ptr %r7
    br label %L1
}
define i32 @main()
{
L1:  
    %r10 = alloca i32
    %r11 = call i32 @getint()
    store i32 1, ptr %r10
    br label %L15
    %r11 = load i32, ptr %r10
    %r14 = icmp sgt i32 %r11,%r12
    br i1 %r14, label %L16, label %L17
    %r15 = call i32 @getint()
    %r16 = load i32, ptr @n
    store i32 %r15, ptr %r16
    %r18 = call i32 @f(i32 %r17)
    %r11 = load i32, ptr %r10
    %r14 = sub i32 %r11,%r12
    store i32 %r14, ptr %r10
    br label %L16
L16:  
L17:  
L18:  
    %r11 = load i32, ptr @sum
    ret i32 %r11
}
define float @f(i32 %r0)
{
L1:  
    %r9 = alloca i32
    store i32 1, ptr %r9
    br label %L6
    %r10 = load i32, ptr %r9
    %r11 = load i32, ptr @n
    %r12 = load i32, ptr %r11
    %r13 = icmp sle i32 %r10,%r12
    br i1 %r13, label %L7, label %L8
    %r10 = getelementptr [50 x i32], ptr @row, i32 0, i32 %r9
    %r11 = load i32, ptr %r10
    %r14 = icmp ne i32 %r11,%r12
    %r15 = load i32, ptr %r14
    %r9 = load i32, ptr %r8
    %r10 = load i32, ptr %r9
    %r11 = add i32 %r9,%r10
    %r12 = getelementptr [50 x i32], ptr @line1, i32 0, i32 %r11
    %r13 = load i32, ptr %r12
    %r16 = icmp eq i32 %r13,%r14
    %r17 = load float, ptr %r16
    %r18 = and i32 %r15,%r17
    %r19 = load float, ptr %r18
    %r20 = load i32, ptr @n
    %r21 = load i32, ptr %r20
    %r9 = load i32, ptr %r8
    %r10 = add i32 %r21,%r9
    %r10 = load i32, ptr %r9
    %r11 = sub i32 %r10,%r10
    %r12 = getelementptr [100 x i32], ptr @line2, i32 0, i32 %r11
    %r13 = icmp eq i32 %r12,%r0
    %r14 = load float, ptr %r13
    %r15 = and i32 %r19,%r14
    br i1 %r15, label %L9, label %L10
    %r9 = getelementptr [50 x i32], ptr @ans, i32 0, i32 %r8
    store i32 %r9, ptr %r9
    %r9 = load i32, ptr %r8
    %r10 = load i32, ptr @n
    %r11 = load i32, ptr %r10
    %r12 = icmp eq i32 %r9,%r11
    br i1 %r12, label %L12, label %L13
    %r13 = call float @printans()
    br label %L14
L7:  
L8:  
L9:  
L10:  
L12:  
    %r10 = load i32, ptr %r9
    %r13 = add i32 %r10,%r11
    store i32 1, ptr %r9
    br label %L7
L13:  
L15:  
    %r10 = getelementptr [50 x i32], ptr @row, i32 0, i32 %r9
    store i32 32, ptr %r10
    %r9 = load i32, ptr %r8
    %r10 = load i32, ptr %r9
    %r11 = add i32 %r9,%r10
    %r12 = getelementptr [50 x i32], ptr @line1, i32 0, i32 %r11
    store i32 1, ptr %r12
    %r14 = load i32, ptr @n
    %r15 = load i32, ptr %r14
    %r9 = load i32, ptr %r8
    %r10 = add i32 %r15,%r9
    %r11 = load i32, ptr %r10
    %r10 = load i32, ptr %r9
    %r11 = sub i32 %r11,%r10
    %r12 = getelementptr [100 x i32], ptr @line2, i32 0, i32 %r11
    store i32 1, ptr %r12
    %r9 = load i32, ptr %r8
    %r12 = add i32 %r9,%r10
    %r13 = call float @f(i32 %r12)
    %r10 = getelementptr [50 x i32], ptr @row, i32 0, i32 %r9
    store i32 0, ptr %r10
    %r9 = load i32, ptr %r8
    %r10 = load i32, ptr %r9
    %r11 = add i32 %r9,%r10
    %r12 = getelementptr [50 x i32], ptr @line1, i32 0, i32 %r11
    store i32 1, ptr %r12
    %r14 = load i32, ptr @n
    %r15 = load i32, ptr %r14
    %r9 = load i32, ptr %r8
    %r10 = add i32 %r15,%r9
    %r10 = load i32, ptr %r9
    %r11 = sub i32 %r10,%r10
    %r12 = getelementptr [100 x i32], ptr @line2, i32 0, i32 %r11
    store i32 1, ptr %r12
    br label %L11
}
