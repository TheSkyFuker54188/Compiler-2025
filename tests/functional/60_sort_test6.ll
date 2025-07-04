@n = global i32 zeroinitializer
define i32 @counting_sort(i32 %r0,i32 %r0,i32 %r2)
{
L1:  
    %r7 = load i32, ptr %r6
    %r10 = icmp slt i32 %r7,%r8
    br i1 %r10, label %L1, label %L2
    %r7 = getelementptr [10 x i32], ptr %r3, i32 0, i32 %r6
    store i32 0, ptr %r7
    %r7 = load i32, ptr %r6
    %r10 = add i32 %r7,%r8
    store i32 %r10, ptr %r6
    br label %L1
L2:  
L3:  
    br label %L3
    %r5 = load i32, ptr %r4
    %r3 = load i32, ptr %r2
    %r4 = icmp slt i32 %r5,%r3
    br i1 %r4, label %L4, label %L5
    %r5 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r4
    %r6 = getelementptr [10 x i32], ptr %r3, i32 0, i32 %r5
    %r7 = load i32, ptr %r6
    %r10 = add i32 %r7,%r8
    %r5 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r4
    %r6 = getelementptr [10 x i32], ptr %r3, i32 0, i32 %r5
    store i32 %r10, ptr %r6
    %r5 = load i32, ptr %r4
    %r8 = add i32 %r5,%r6
    store i32 10, ptr %r4
    br label %L4
L4:  
L5:  
L6:  
    store i32 0, ptr %r6
    br label %L6
    %r10 = icmp slt i32 %r6,%r8
    br i1 %r10, label %L7, label %L8
    %r7 = getelementptr [10 x i32], ptr %r3, i32 0, i32 %r6
    %r8 = load i32, ptr %r7
    %r10 = sub i32 %r6,%r8
    %r11 = getelementptr [10 x i32], ptr %r3, i32 0, i32 %r10
    %r12 = load i32, ptr %r11
    %r13 = add i32 %r8,%r12
    %r7 = getelementptr [10 x i32], ptr %r3, i32 0, i32 %r6
    store i32 %r13, ptr %r7
    %r10 = add i32 %r6,%r8
    store i32 %r10, ptr %r6
    br label %L7
L7:  
L8:  
L9:  
    store i32 %r2, ptr %r5
    br label %L9
    %r9 = icmp sgt i32 %r5,%r7
    br i1 %r9, label %L10, label %L11
    %r9 = sub i32 %r5,%r7
    %r10 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r9
    %r11 = getelementptr [10 x i32], ptr %r3, i32 0, i32 %r10
    %r12 = load i32, ptr %r11
    %r15 = sub i32 %r12,%r13
    %r9 = sub i32 %r5,%r7
    %r10 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r9
    %r11 = getelementptr [10 x i32], ptr %r3, i32 0, i32 %r10
    store i32 %r15, ptr %r11
    %r9 = sub i32 %r5,%r7
    %r10 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r9
    %r9 = sub i32 %r5,%r7
    %r10 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r9
    %r11 = getelementptr [10 x i32], ptr %r3, i32 0, i32 %r10
    %r12 = getelementptr [0 x i32], ptr %r1, i32 0, i32 %r11
    store float %r10, ptr %r12
    %r9 = sub i32 %r5,%r7
    store i32 %r9, ptr %r5
    br label %L10
L10:  
L11:  
L12:  
    ret i32 1
}
define i32 @main()
{
L1:  
    %r5 = alloca i32
    %r35 = alloca [10 x i32]
    %r34 = alloca i32
    %r3 = alloca [10 x i32]
    store i32 0, ptr %r2
    %r6 = getelementptr [10 x i32], ptr %r3, i32 0, i32 %r5
    store i32 4, ptr %r6
    %r9 = getelementptr [10 x i32], ptr %r3, i32 0, i32 %r8
    store float 0, ptr %r9
    %r12 = getelementptr [10 x i32], ptr %r3, i32 0, i32 %r11
    store float 9, ptr %r12
    %r15 = getelementptr [10 x i32], ptr %r3, i32 0, i32 %r14
    store float 1, ptr %r15
    %r18 = getelementptr [10 x i32], ptr %r3, i32 0, i32 %r17
    store float 0, ptr %r18
    %r21 = getelementptr [10 x i32], ptr %r3, i32 0, i32 %r20
    store float 1, ptr %r21
    %r24 = getelementptr [10 x i32], ptr %r3, i32 0, i32 %r23
    store float 6, ptr %r24
    %r27 = getelementptr [10 x i32], ptr %r3, i32 0, i32 %r26
    store float 5, ptr %r27
    %r30 = getelementptr [10 x i32], ptr %r3, i32 0, i32 %r29
    store float 7, ptr %r30
    %r33 = getelementptr [10 x i32], ptr %r3, i32 0, i32 %r32
    store float 8, ptr %r33
    store i32 0, ptr %r34
    %r3 = call i32 @counting_sort(i32 %r3,i32 %r35,i32 %r2)
    store i32 %r3, ptr %r34
    br label %L12
    %r35 = load i32, ptr %r34
    %r3 = load i32, ptr %r2
    %r4 = icmp slt i32 %r35,%r3
    br i1 %r4, label %L13, label %L14
    %r35 = getelementptr [10 x i32], ptr %r35, i32 0, i32 %r34
    store i32 %r35, ptr %r5
    %r6 = call i32 @putint(i32 %r5)
    store i32 0, ptr %r5
    %r6 = call i32 @putch(i32 %r5)
    %r35 = load i32, ptr %r34
    %r38 = add i32 %r35,%r36
    store i32 %r38, ptr %r34
    br label %L13
L13:  
L14:  
L15:  
    ret i32 0
}
