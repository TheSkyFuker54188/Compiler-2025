@buf = global [2x [100x i32]] zeroinitializer
define float @merge_sort(i32 %r0,i32 %r0)
{
L1:  
    ret void
    br label %L2
L3:  
    %r5 = alloca i32
    %r1 = alloca i32
    %r3 = alloca i32
    %r4 = alloca i32
    %r1 = load i32, ptr %r0
    %r2 = load i32, ptr %r1
    %r3 = add i32 %r1,%r2
    %r4 = load float, ptr %r3
    %r7 = sdiv i32 %r4,%r5
    store i32 %r7, ptr %r4
    %r5 = call float @merge_sort(i32 %r0,i32 %r4)
    %r2 = call float @merge_sort(i32 %r4,i32 %r1)
    store i32 %r0, ptr %r3
    store i32 %r4, ptr %r1
    store i32 %r0, ptr %r5
    br label %L3
    %r4 = load i32, ptr %r3
    %r5 = load i32, ptr %r4
    %r6 = icmp slt i32 %r4,%r5
    %r7 = load float, ptr %r6
    %r2 = load i32, ptr %r1
    %r2 = load i32, ptr %r1
    %r3 = icmp slt i32 %r2,%r2
    %r4 = load i32, ptr %r3
    %r5 = and i32 %r7,%r4
    br i1 %r5, label %L4, label %L5
    %r4 = getelementptr [2 x [100 x i32]], ptr @buf, i32 0, i32 %r6, i32 %r3
    %r5 = load i32, ptr %r4
    %r2 = getelementptr [2 x [100 x i32]], ptr @buf, i32 0, i32 %r6, i32 %r1
    %r3 = load i32, ptr %r2
    %r4 = icmp slt i32 %r5,%r3
    br i1 %r4, label %L6, label %L7
    %r4 = getelementptr [2 x [100 x i32]], ptr @buf, i32 0, i32 %r5, i32 %r3
    %r6 = getelementptr [2 x [100 x i32]], ptr @buf, i32 0, i32 %r5, i32 %r5
    store i32 %r4, ptr %r6
    %r4 = load i32, ptr %r3
    %r7 = add i32 %r4,%r5
    store i32 %r7, ptr %r3
    br label %L8
    %r2 = getelementptr [2 x [100 x i32]], ptr @buf, i32 0, i32 %r4, i32 %r1
    %r6 = getelementptr [2 x [100 x i32]], ptr @buf, i32 0, i32 %r3, i32 %r5
    store i32 1, ptr %r6
    %r2 = load i32, ptr %r1
    %r5 = add i32 %r2,%r3
    store i32 0, ptr %r1
    br label %L8
L4:  
L5:  
L6:  
    br label %L9
    %r6 = icmp slt i32 %r3,%r4
    br i1 %r6, label %L10, label %L11
    %r4 = getelementptr [2 x [100 x i32]], ptr @buf, i32 0, i32 %r7, i32 %r3
    %r6 = getelementptr [2 x [100 x i32]], ptr @buf, i32 0, i32 %r5, i32 %r5
    store i32 0, ptr %r6
    %r7 = add i32 %r3,%r5
    store i32 1, ptr %r3
    %r9 = add i32 %r5,%r7
    store i32 %r9, ptr %r5
    br label %L10
L7:  
L8:  
L9:  
    %r9 = add i32 %r5,%r7
    store i32 %r9, ptr %r5
    br label %L4
L10:  
L11:  
L12:  
    br label %L12
    %r2 = load i32, ptr %r1
    %r2 = load i32, ptr %r1
    %r3 = icmp slt i32 %r2,%r2
    br i1 %r3, label %L13, label %L14
    %r2 = getelementptr [2 x [100 x i32]], ptr @buf, i32 0, i32 %r4, i32 %r1
    %r6 = getelementptr [2 x [100 x i32]], ptr @buf, i32 0, i32 %r3, i32 %r5
    store i32 1, ptr %r6
    %r2 = load i32, ptr %r1
    %r5 = add i32 %r2,%r3
    store i32 0, ptr %r1
    %r9 = add i32 %r5,%r7
    store i32 %r9, ptr %r5
    br label %L13
L13:  
L14:  
L15:  
    br label %L15
    %r1 = load i32, ptr %r0
    %r2 = load i32, ptr %r1
    %r3 = icmp slt i32 %r1,%r2
    br i1 %r3, label %L16, label %L17
    %r1 = getelementptr [2 x [100 x i32]], ptr @buf, i32 0, i32 %r4, i32 %r0
    %r1 = getelementptr [2 x [100 x i32]], ptr @buf, i32 0, i32 %r2, i32 %r0
    store i32 %r1, ptr %r1
    %r1 = load i32, ptr %r0
    %r4 = add i32 %r1,%r2
    store i32 0, ptr %r0
    br label %L16
L16:  
L17:  
L18:  
}
define i32 @main()
{
L1:  
    %r1 = alloca i32
    %r3 = getelementptr [2 x [100 x i32]], ptr @buf, i32 0, i32 %r2
    %r4 = call i32 @getarray(i32 %r3)
    store i32 0, ptr %r1
    %r2 = call i32 @merge_sort(i32 %r5,i32 %r1)
    %r3 = getelementptr [2 x [100 x i32]], ptr @buf, i32 0, i32 %r2
    %r4 = call i32 @putarray(i32 %r1,i32 %r3)
    ret i32 0
}
