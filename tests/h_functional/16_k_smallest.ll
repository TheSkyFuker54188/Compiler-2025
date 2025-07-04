@maxN = global i32 1000
@space = global i32 32
@array = global [1000x i32] zeroinitializer
define float @swap(i32 %r0,i32 %r2)
{
L1:  
    %r4 = alloca i32
    %r3 = getelementptr [1000 x i32], ptr @array, i32 0, i32 %r2
    store i32 %r3, ptr %r4
    %r4 = getelementptr [1000 x i32], ptr @array, i32 0, i32 %r3
    %r3 = getelementptr [1000 x i32], ptr @array, i32 0, i32 %r2
    store i32 %r4, ptr %r3
    %r4 = getelementptr [1000 x i32], ptr @array, i32 0, i32 %r3
    store i32 %r4, ptr %r4
}
define i32 @findPivot(i32 %r0,i32 %r5)
{
L1:  
    %r7 = load i32, ptr %r6
    %r7 = load i32, ptr %r6
    %r8 = icmp slt i32 %r7,%r7
    br i1 %r8, label %L1, label %L2
    %r7 = getelementptr [1000 x i32], ptr @array, i32 0, i32 %r6
    %r8 = load i32, ptr %r7
    %r8 = load i32, ptr %r7
    %r9 = icmp sle i32 %r8,%r8
    br i1 %r9, label %L3, label %L4
    %r9 = call i32 @swap(i32 %r6,i32 %r8)
    %r9 = load i32, ptr %r8
    %r12 = add i32 %r9,%r10
    store i32 %r12, ptr %r8
    br label %L5
L2:  
L3:  
    %r7 = call i32 @swap(i32 %r8,i32 %r6)
    ret i32 1
L4:  
L6:  
    %r7 = load i32, ptr %r6
    %r10 = add i32 %r7,%r8
    store i32 1, ptr %r6
    br label %L1
}
define float @findSmallest(i32 %r0,i32 %r9,i32 %r2,i32 %r10)
{
L1:  
    %r16 = alloca i32
    %r13 = alloca i32
    %r10 = load i32, ptr %r9
    %r11 = load i32, ptr %r10
    %r12 = icmp eq i32 %r10,%r11
    br i1 %r12, label %L6, label %L7
    ret void
    br label %L8
    %r11 = call float @findPivot(i32 %r9,i32 %r10)
    store i32 %r11, ptr %r13
    %r12 = load i32, ptr %r11
    %r14 = load i32, ptr %r13
    %r15 = icmp eq i32 %r12,%r14
    br i1 %r15, label %L9, label %L10
    store i32 0, ptr %r16
    br label %L12
    %r17 = load i32, ptr %r16
    %r14 = load i32, ptr %r13
    %r15 = icmp slt i32 %r17,%r14
    br i1 %r15, label %L13, label %L14
    %r17 = getelementptr [1000 x i32], ptr @array, i32 0, i32 %r16
    %r18 = call float @putint(i32 %r17)
    %r20 = call float @putch(i32 %r19)
    %r17 = load i32, ptr %r16
    %r20 = add i32 %r17,%r18
    store i32 %r20, ptr %r16
    br label %L13
L7:  
L8:  
L9:  
L10:  
L11:  
L12:  
    br label %L8
L13:  
L14:  
L15:  
    br label %L11
    %r12 = load i32, ptr %r11
    %r14 = load i32, ptr %r13
    %r15 = icmp slt i32 %r12,%r14
    br i1 %r15, label %L15, label %L16
    %r14 = load i32, ptr %r13
    %r17 = sub i32 %r14,%r15
    %r13 = call float @findSmallest(i32 %r9,i32 %r17,i32 %r11,i32 %r12)
    br label %L17
    %r14 = load i32, ptr %r13
    %r17 = add i32 %r14,%r15
    %r13 = call float @findSmallest(i32 %r17,i32 %r10,i32 %r11,i32 %r12)
    br label %L17
L16:  
L17:  
L18:  
    br label %L11
}
define i32 @main()
{
L1:  
    %r18 = alloca i32
    %r16 = alloca i32
    %r14 = alloca i32
    %r15 = call i32 @getint()
    store i32 1, ptr %r14
    %r17 = call i32 @getint()
    store i32 0, ptr %r16
    store i32 32, ptr %r18
    br label %L18
    %r19 = load i32, ptr %r18
    %r15 = load i32, ptr %r14
    %r16 = icmp slt i32 %r19,%r15
    br i1 %r16, label %L19, label %L20
    %r17 = call i32 @getint()
    %r19 = getelementptr [1000 x i32], ptr @array, i32 0, i32 %r18
    store i32 0, ptr %r19
    %r19 = load i32, ptr %r18
    %r22 = add i32 %r19,%r20
    store i32 %r22, ptr %r18
    br label %L19
L19:  
L20:  
L21:  
    %r21 = alloca i32
    %r19 = alloca i32
    store i32 1, ptr %r19
    %r15 = load i32, ptr %r14
    %r18 = sub i32 %r15,%r16
    store i32 %r18, ptr %r21
    %r15 = call i32 @findSmallest(i32 %r19,i32 %r21,i32 %r16,i32 %r14)
    ret i32 1
}
