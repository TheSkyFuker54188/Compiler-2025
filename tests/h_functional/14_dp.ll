@t = global [1005x [2x i32]] zeroinitializer
@dp = global [1005x [35x i32]] zeroinitializer
define i32 @main()
{
L1:  
    %r6 = load i32, ptr %r5
    %r3 = load i32, ptr %r2
    %r4 = icmp sle i32 %r6,%r3
    br i1 %r4, label %L1, label %L2
    %r5 = call i32 @getint()
    store i32 %r5, ptr %r4
    %r8 = srem i32 %r4,%r6
    %r9 = getelementptr [1005 x [2 x i32]], ptr @t, i32 0, i32 %r5, i32 %r8
    store float 1, ptr %r9
    %r9 = sub i32 %r5,%r7
    %r11 = getelementptr [1005 x [35 x i32]], ptr @dp, i32 0, i32 %r9, i32 %r10
    %r12 = load float, ptr %r11
    %r7 = getelementptr [1005 x [2 x i32]], ptr @t, i32 0, i32 %r5, i32 %r6
    %r8 = load i32, ptr %r7
    %r9 = add i32 %r12,%r8
    %r7 = getelementptr [1005 x [35 x i32]], ptr @dp, i32 0, i32 %r5, i32 %r6
    store i32 %r9, ptr %r7
    %r9 = add i32 %r5,%r7
    store i32 %r9, ptr %r5
    br label %L1
L2:  
L3:  
    store i32 2, ptr %r5
    br label %L3
    %r3 = load i32, ptr %r2
    %r4 = icmp sle i32 %r5,%r3
    br i1 %r4, label %L4, label %L5
    store i32 1, ptr %r6
    br label %L6
    %r4 = load i32, ptr %r3
    %r5 = icmp sle i32 %r6,%r4
    br i1 %r5, label %L7, label %L8
    %r9 = sub i32 %r5,%r7
    %r7 = getelementptr [1005 x [35 x i32]], ptr @dp, i32 0, i32 %r9, i32 %r6
    %r8 = load i32, ptr %r7
    %r10 = add i32 %r6,%r8
    %r14 = srem i32 %r10,%r12
    %r15 = getelementptr [1005 x [2 x i32]], ptr @t, i32 0, i32 %r5, i32 %r14
    %r16 = load float, ptr %r15
    %r17 = add i32 %r8,%r16
    %r18 = load float, ptr %r17
    %r9 = sub i32 %r5,%r7
    %r10 = sub i32 %r6,%r8
    %r11 = getelementptr [1005 x [35 x i32]], ptr @dp, i32 0, i32 %r9, i32 %r10
    %r12 = load float, ptr %r11
    %r10 = add i32 %r6,%r8
    %r14 = srem i32 %r10,%r12
    %r15 = getelementptr [1005 x [2 x i32]], ptr @t, i32 0, i32 %r5, i32 %r14
    %r16 = load float, ptr %r15
    %r17 = add i32 %r12,%r16
    %r18 = load float, ptr %r17
    %r19 = icmp sgt i32 %r18,%r18
    br i1 %r19, label %L9, label %L10
    %r9 = sub i32 %r5,%r7
    %r7 = getelementptr [1005 x [35 x i32]], ptr @dp, i32 0, i32 %r9, i32 %r6
    %r8 = load i32, ptr %r7
    %r10 = add i32 %r6,%r8
    %r14 = srem i32 %r10,%r12
    %r15 = getelementptr [1005 x [2 x i32]], ptr @t, i32 0, i32 %r5, i32 %r14
    %r16 = load float, ptr %r15
    %r17 = add i32 %r8,%r16
    %r7 = getelementptr [1005 x [35 x i32]], ptr @dp, i32 0, i32 %r5, i32 %r6
    store i32 %r17, ptr %r7
    br label %L11
    %r9 = sub i32 %r5,%r7
    %r10 = sub i32 %r6,%r8
    %r11 = getelementptr [1005 x [35 x i32]], ptr @dp, i32 0, i32 %r9, i32 %r10
    %r12 = load float, ptr %r11
    %r10 = add i32 %r6,%r8
    %r14 = srem i32 %r10,%r12
    %r15 = getelementptr [1005 x [2 x i32]], ptr @t, i32 0, i32 %r5, i32 %r14
    %r16 = load float, ptr %r15
    %r17 = add i32 %r12,%r16
    %r7 = getelementptr [1005 x [35 x i32]], ptr @dp, i32 0, i32 %r5, i32 %r6
    store i32 %r17, ptr %r7
    br label %L11
L4:  
L5:  
L6:  
    %r6 = alloca i32
    store i32 1, ptr %r6
    store i32 1, ptr %r6
    br label %L12
    %r7 = load i32, ptr %r6
    %r4 = load i32, ptr %r3
    %r5 = icmp sle i32 %r7,%r4
    br i1 %r5, label %L13, label %L14
    %r7 = load i32, ptr %r6
    %r7 = getelementptr [1005 x [35 x i32]], ptr @dp, i32 0, i32 %r2, i32 %r6
    %r8 = load i32, ptr %r7
    %r9 = icmp slt i32 %r7,%r8
    br i1 %r9, label %L15, label %L16
    %r7 = getelementptr [1005 x [35 x i32]], ptr @dp, i32 0, i32 %r2, i32 %r6
    store i32 1, ptr %r6
    br label %L17
L7:  
L8:  
L9:  
    %r9 = add i32 %r5,%r7
    store i32 %r9, ptr %r5
    br label %L4
L10:  
L11:  
L12:  
    %r10 = add i32 %r6,%r8
    store i32 0, ptr %r6
    br label %L7
L13:  
L14:  
L15:  
    ret i32 %r6
L16:  
L18:  
    %r7 = load i32, ptr %r6
    %r10 = add i32 %r7,%r8
    store i32 0, ptr %r6
    br label %L13
}
