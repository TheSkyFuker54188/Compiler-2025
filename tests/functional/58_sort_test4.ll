@n = global i32 zeroinitializer
define i32 @select_sort(i32 %r0,i32 %r0)
{
L1:  
    %r3 = load i32, ptr %r2
    %r2 = load i32, ptr %r1
    %r5 = sub i32 %r2,%r3
    %r7 = icmp slt i32 %r3,%r5
    br i1 %r7, label %L1, label %L2
    store i32 %r2, ptr %r4
    %r3 = load i32, ptr %r2
    %r6 = add i32 %r3,%r4
    store i32 %r6, ptr %r3
    br label %L3
    %r2 = load i32, ptr %r1
    %r3 = icmp slt i32 %r3,%r2
    br i1 %r3, label %L4, label %L5
    %r5 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r4
    %r4 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r3
    %r6 = icmp sgt i32 %r5,%r4
    br i1 %r6, label %L6, label %L7
    store i32 1, ptr %r4
    br label %L8
L2:  
L3:  
    ret i32 1
L4:  
L5:  
L6:  
    %r5 = alloca i32
    %r3 = load i32, ptr %r2
    %r4 = icmp ne i32 %r4,%r3
    br i1 %r4, label %L9, label %L10
    %r5 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r4
    store i32 %r5, ptr %r5
    %r3 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r2
    %r5 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r4
    store i32 1, ptr %r5
    %r3 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r2
    store i32 %r5, ptr %r3
    br label %L11
L7:  
L9:  
    %r7 = add i32 %r3,%r5
    store i32 %r7, ptr %r3
    br label %L4
L10:  
L12:  
    %r3 = load i32, ptr %r2
    %r6 = add i32 %r3,%r4
    store i32 %r6, ptr %r2
    br label %L1
}
define i32 @main()
{
L1:  
    %r4 = alloca i32
    %r33 = alloca i32
    %r2 = alloca [10 x i32]
    store i32 1, ptr %r1
    %r5 = getelementptr [10 x i32], ptr %r2, i32 0, i32 %r4
    store i32 1, ptr %r5
    %r8 = getelementptr [10 x i32], ptr %r2, i32 0, i32 %r7
    store float 3, ptr %r8
    %r11 = getelementptr [10 x i32], ptr %r2, i32 0, i32 %r10
    store float 9, ptr %r11
    %r14 = getelementptr [10 x i32], ptr %r2, i32 0, i32 %r13
    store float 2, ptr %r14
    %r17 = getelementptr [10 x i32], ptr %r2, i32 0, i32 %r16
    store float 0, ptr %r17
    %r20 = getelementptr [10 x i32], ptr %r2, i32 0, i32 %r19
    store float 1, ptr %r20
    %r23 = getelementptr [10 x i32], ptr %r2, i32 0, i32 %r22
    store float 6, ptr %r23
    %r26 = getelementptr [10 x i32], ptr %r2, i32 0, i32 %r25
    store float 5, ptr %r26
    %r29 = getelementptr [10 x i32], ptr %r2, i32 0, i32 %r28
    store float 7, ptr %r29
    %r32 = getelementptr [10 x i32], ptr %r2, i32 0, i32 %r31
    store float 8, ptr %r32
    store i32 0, ptr %r33
    %r2 = call i32 @select_sort(i32 %r2,i32 %r1)
    store i32 %r2, ptr %r33
    br label %L12
    %r34 = load i32, ptr %r33
    %r2 = load i32, ptr %r1
    %r3 = icmp slt i32 %r34,%r2
    br i1 %r3, label %L13, label %L14
    %r34 = getelementptr [10 x i32], ptr %r2, i32 0, i32 %r33
    store i32 0, ptr %r4
    %r5 = call i32 @putint(i32 %r4)
    store i32 3, ptr %r4
    %r5 = call i32 @putch(i32 %r4)
    %r34 = load i32, ptr %r33
    %r37 = add i32 %r34,%r35
    store i32 %r37, ptr %r33
    br label %L13
L13:  
L14:  
L15:  
    ret i32 0
}
