@n = global i32 zeroinitializer
define i32 @QuickSort(i32 %r0,i32 %r0,i32 %r2)
{
L1:  
    %r7 = alloca i32
    %r6 = alloca i32
    %r5 = alloca i32
    store i32 %r1, ptr %r5
    store i32 %r2, ptr %r6
    %r2 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r1
    store i32 %r2, ptr %r7
    br label %L3
    %r6 = load i32, ptr %r5
    %r7 = load i32, ptr %r6
    %r8 = icmp slt i32 %r6,%r7
    br i1 %r8, label %L4, label %L5
    br label %L6
    %r6 = load i32, ptr %r5
    %r7 = load i32, ptr %r6
    %r8 = icmp slt i32 %r6,%r7
    %r9 = load float, ptr %r8
    %r7 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r6
    %r8 = load i32, ptr %r7
    %r8 = load i32, ptr %r7
    %r11 = sub i32 %r8,%r9
    %r12 = load float, ptr %r11
    %r13 = icmp sgt i32 %r8,%r12
    %r14 = load float, ptr %r13
    %r15 = and i32 %r9,%r14
    br i1 %r15, label %L7, label %L8
    %r7 = load i32, ptr %r6
    %r10 = sub i32 %r7,%r8
    store i32 %r10, ptr %r6
    br label %L7
L3:  
    ret i32 1
L4:  
L5:  
L6:  
    %r7 = alloca i32
    %r6 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r5
    store i32 1, ptr %r6
    %r6 = load i32, ptr %r5
    %r9 = sub i32 %r6,%r7
    store i32 1, ptr %r7
    %r8 = call i32 @QuickSort(i32 %r0,i32 %r1,i32 %r7)
    store i32 1, ptr %r7
    %r6 = load i32, ptr %r5
    %r9 = add i32 %r6,%r7
    store i32 1, ptr %r7
    %r3 = call i32 @QuickSort(i32 %r0,i32 %r7,i32 %r2)
    store i32 %r3, ptr %r7
    br label %L2
L7:  
L8:  
L9:  
    %r6 = load i32, ptr %r5
    %r7 = load i32, ptr %r6
    %r8 = icmp slt i32 %r6,%r7
    br i1 %r8, label %L9, label %L10
    %r7 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r6
    %r6 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r5
    store i32 %r7, ptr %r6
    %r6 = load i32, ptr %r5
    %r9 = add i32 %r6,%r7
    store i32 1, ptr %r5
    br label %L11
L10:  
L12:  
    br label %L12
    %r6 = load i32, ptr %r5
    %r7 = load i32, ptr %r6
    %r8 = icmp slt i32 %r6,%r7
    %r6 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r5
    %r7 = load i32, ptr %r6
    %r9 = icmp slt i32 %r7,%r7
    %r11 = and i32 %r8,%r9
    br i1 %r11, label %L13, label %L14
    %r6 = load i32, ptr %r5
    %r9 = add i32 %r6,%r7
    store i32 1, ptr %r5
    br label %L13
L13:  
L14:  
L15:  
    %r6 = load i32, ptr %r5
    %r7 = load i32, ptr %r6
    %r8 = icmp slt i32 %r6,%r7
    br i1 %r8, label %L15, label %L16
    %r6 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r5
    %r7 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r6
    store i32 %r6, ptr %r7
    %r7 = load i32, ptr %r6
    %r10 = sub i32 %r7,%r8
    store i32 %r10, ptr %r6
    br label %L17
L16:  
L18:  
    br label %L4
}
define i32 @main()
{
L1:  
    %r47 = alloca i32
    %r43 = alloca i32
    %r42 = alloca i32
    %r11 = alloca [10 x i32]
    %r10 = load i32, ptr @n
    store i32 1, ptr %r10
    %r14 = getelementptr [10 x i32], ptr %r11, i32 0, i32 %r13
    store float 4, ptr %r14
    %r17 = getelementptr [10 x i32], ptr %r11, i32 0, i32 %r16
    store float 3, ptr %r17
    %r20 = getelementptr [10 x i32], ptr %r11, i32 0, i32 %r19
    store float 9, ptr %r20
    %r23 = getelementptr [10 x i32], ptr %r11, i32 0, i32 %r22
    store float 2, ptr %r23
    %r26 = getelementptr [10 x i32], ptr %r11, i32 0, i32 %r25
    store float 0, ptr %r26
    %r29 = getelementptr [10 x i32], ptr %r11, i32 0, i32 %r28
    store float 1, ptr %r29
    %r32 = getelementptr [10 x i32], ptr %r11, i32 0, i32 %r31
    store float 6, ptr %r32
    %r35 = getelementptr [10 x i32], ptr %r11, i32 0, i32 %r34
    store float 5, ptr %r35
    %r38 = getelementptr [10 x i32], ptr %r11, i32 0, i32 %r37
    store float 7, ptr %r38
    %r41 = getelementptr [10 x i32], ptr %r11, i32 0, i32 %r40
    store float 8, ptr %r41
    store i32 0, ptr %r42
    store i32 9, ptr %r43
    %r44 = call i32 @QuickSort(i32 %r11,i32 %r42,i32 %r43)
    store i32 9, ptr %r42
    br label %L18
    %r43 = load i32, ptr %r42
    %r44 = load i32, ptr @n
    %r45 = load i32, ptr %r44
    %r46 = icmp slt i32 %r43,%r45
    br i1 %r46, label %L19, label %L20
    %r43 = getelementptr [10 x i32], ptr %r11, i32 0, i32 %r42
    store i32 %r43, ptr %r47
    %r48 = call i32 @putint(i32 %r47)
    store i32 10, ptr %r47
    %r48 = call i32 @putch(i32 %r47)
    %r43 = load i32, ptr %r42
    %r46 = add i32 %r43,%r44
    store i32 %r46, ptr %r42
    br label %L19
L19:  
L20:  
L21:  
    ret i32 0
}
