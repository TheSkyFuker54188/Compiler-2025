@n = global i32 zeroinitializer
define i32 @swap(i32 %r0,i32 %r0,i32 %r2)
{
L1:  
    %r3 = alloca i32
    %r2 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r1
    store i32 %r2, ptr %r3
    %r3 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r2
    %r2 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r1
    store i32 %r3, ptr %r2
    %r3 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r2
    store i32 %r3, ptr %r3
    ret i32 0
}
define i32 @main()
{
L1:  
    %r53 = alloca i32
    %r48 = alloca i32
    %r17 = alloca [10 x i32]
    %r16 = load i32, ptr @n
    store i32 1, ptr %r16
    %r20 = getelementptr [10 x i32], ptr %r17, i32 0, i32 %r19
    store float 4, ptr %r20
    %r23 = getelementptr [10 x i32], ptr %r17, i32 0, i32 %r22
    store float 3, ptr %r23
    %r26 = getelementptr [10 x i32], ptr %r17, i32 0, i32 %r25
    store float 9, ptr %r26
    %r29 = getelementptr [10 x i32], ptr %r17, i32 0, i32 %r28
    store float 2, ptr %r29
    %r32 = getelementptr [10 x i32], ptr %r17, i32 0, i32 %r31
    store float 0, ptr %r32
    %r35 = getelementptr [10 x i32], ptr %r17, i32 0, i32 %r34
    store float 1, ptr %r35
    %r38 = getelementptr [10 x i32], ptr %r17, i32 0, i32 %r37
    store float 6, ptr %r38
    %r41 = getelementptr [10 x i32], ptr %r17, i32 0, i32 %r40
    store float 5, ptr %r41
    %r44 = getelementptr [10 x i32], ptr %r17, i32 0, i32 %r43
    store float 7, ptr %r44
    %r47 = getelementptr [10 x i32], ptr %r17, i32 0, i32 %r46
    store float 8, ptr %r47
    store i32 0, ptr %r48
    %r18 = load i32, ptr @n
    %r19 = call i32 @heap_sort(i32 %r17,i32 %r18)
    store i32 0, ptr %r48
    br label %L15
    %r49 = load i32, ptr %r48
    %r50 = load i32, ptr @n
    %r51 = load i32, ptr %r50
    %r52 = icmp slt i32 %r49,%r51
    br i1 %r52, label %L16, label %L17
    %r49 = getelementptr [10 x i32], ptr %r17, i32 0, i32 %r48
    store i32 0, ptr %r53
    %r54 = call i32 @putint(i32 %r53)
    store i32 10, ptr %r53
    %r54 = call i32 @putch(i32 %r53)
    %r49 = load i32, ptr %r48
    %r52 = add i32 %r49,%r50
    store i32 %r52, ptr %r48
    br label %L16
L16:  
L17:  
L18:  
    ret i32 0
}
define i32 @heap_ajust(i32 %r0,i32 %r5,i32 %r2)
{
L1:  
    %r10 = load i32, ptr %r9
    %r8 = load i32, ptr %r7
    %r11 = add i32 %r8,%r9
    %r12 = load float, ptr %r11
    %r13 = icmp slt i32 %r10,%r12
    br i1 %r13, label %L1, label %L2
    %r8 = load i32, ptr %r7
    %r9 = icmp slt i32 %r9,%r8
    %r10 = getelementptr [0 x i32], ptr %r5, i32 0, i32 %r9
    %r13 = add i32 %r9,%r11
    %r14 = getelementptr [0 x i32], ptr %r5, i32 0, i32 %r13
    %r16 = icmp slt i32 %r10,%r14
    %r17 = load float, ptr %r16
    %r18 = and i32 %r9,%r17
    br i1 %r18, label %L3, label %L4
    %r13 = add i32 %r9,%r11
    store i32 %r13, ptr %r9
    br label %L5
L2:  
L3:  
    ret i32 2
L4:  
L6:  
    %r9 = getelementptr [0 x i32], ptr %r5, i32 0, i32 %r8
    %r10 = getelementptr [0 x i32], ptr %r5, i32 0, i32 %r9
    %r12 = icmp sgt i32 %r9,%r10
    br i1 %r12, label %L6, label %L7
    ret i32 0
    br label %L8
    %r10 = call i32 @swap(i32 %r5,i32 %r8,i32 %r9)
    store i32 2, ptr %r8
    store i32 1, ptr %r8
    %r9 = load i32, ptr %r8
    %r12 = mul i32 %r9,%r10
    %r13 = load float, ptr %r12
    %r16 = add i32 %r13,%r14
    store i32 %r16, ptr %r9
    br label %L8
L7:  
L8:  
L9:  
    br label %L1
}
define i32 @heap_sort(i32 %r0,i32 %r11)
{
L1:  
    %r14 = alloca i32
    %r13 = alloca i32
    %r13 = load i32, ptr %r12
    %r16 = sdiv i32 %r13,%r14
    %r17 = load float, ptr %r16
    %r20 = sub i32 %r17,%r18
    store i32 %r20, ptr %r13
    br label %L9
    %r14 = load i32, ptr %r13
    %r16 = sub i32 %r0,%r15
    %r17 = load float, ptr %r16
    %r18 = icmp sgt i32 %r14,%r17
    br i1 %r18, label %L10, label %L11
    %r13 = load i32, ptr %r12
    %r16 = sub i32 %r13,%r14
    store i32 %r16, ptr %r14
    %r15 = call i32 @heap_ajust(i32 %r11,i32 %r13,i32 %r14)
    store i32 1, ptr %r14
    %r14 = load i32, ptr %r13
    %r17 = sub i32 %r14,%r15
    store i32 %r17, ptr %r13
    br label %L10
L10:  
L11:  
L12:  
    %r18 = alloca i32
    %r13 = load i32, ptr %r12
    %r16 = sub i32 %r13,%r14
    store i32 %r16, ptr %r13
    br label %L12
    %r14 = load i32, ptr %r13
    %r17 = icmp sgt i32 %r14,%r15
    br i1 %r17, label %L13, label %L14
    store i32 0, ptr %r18
    %r14 = call i32 @swap(i32 %r11,i32 %r18,i32 %r13)
    store i32 2, ptr %r14
    %r14 = load i32, ptr %r13
    %r17 = sub i32 %r14,%r15
    store i32 %r17, ptr %r14
    %r15 = call i32 @heap_ajust(i32 %r11,i32 %r18,i32 %r14)
    store i32 1, ptr %r14
    %r14 = load i32, ptr %r13
    %r17 = sub i32 %r14,%r15
    store i32 %r17, ptr %r13
    br label %L13
L13:  
L14:  
L15:  
    ret i32 2
}
