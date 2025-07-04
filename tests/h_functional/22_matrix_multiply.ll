@MAX_SIZE = global i32 100
@a = global [100x [100x i32]] zeroinitializer
@b = global [100x [100x i32]] zeroinitializer
@res = global [100x [100x i32]] zeroinitializer
@n1 = global i32 zeroinitializer
@m1 = global i32 zeroinitializer
@n2 = global i32 zeroinitializer
@m2 = global i32 zeroinitializer
define float @matrix_multiply()
{
L1:  
    %r11 = alloca i32
    %r6 = alloca i32
    %r2 = load i32, ptr %r1
    %r3 = load i32, ptr @m1
    %r4 = load i32, ptr %r3
    %r5 = icmp slt i32 %r2,%r4
    br i1 %r5, label %L1, label %L2
    store i32 0, ptr %r6
    br label %L3
    %r7 = load i32, ptr %r6
    %r8 = load i32, ptr @n2
    %r9 = load i32, ptr %r8
    %r10 = icmp slt i32 %r7,%r9
    br i1 %r10, label %L4, label %L5
    store i32 0, ptr %r11
    br label %L6
    %r12 = load i32, ptr %r11
    %r13 = load i32, ptr @n1
    %r14 = load i32, ptr %r13
    %r15 = icmp slt i32 %r12,%r14
    br i1 %r15, label %L7, label %L8
    %r7 = getelementptr [100 x [100 x i32]], ptr @res, i32 0, i32 %r1, i32 %r6
    %r8 = load i32, ptr %r7
    %r12 = getelementptr [100 x [100 x i32]], ptr @a, i32 0, i32 %r1, i32 %r11
    %r13 = load i32, ptr %r12
    %r7 = getelementptr [100 x [100 x i32]], ptr @b, i32 0, i32 %r11, i32 %r6
    %r8 = load i32, ptr %r7
    %r9 = mul i32 %r13,%r8
    %r10 = load float, ptr %r9
    %r11 = add i32 %r8,%r10
    %r7 = getelementptr [100 x [100 x i32]], ptr @res, i32 0, i32 %r1, i32 %r6
    store i32 %r11, ptr %r7
    %r12 = load i32, ptr %r11
    %r15 = add i32 %r12,%r13
    store i32 %r15, ptr %r11
    br label %L7
L2:  
L3:  
L4:  
L5:  
L6:  
    %r2 = load i32, ptr %r1
    %r5 = add i32 %r2,%r3
    store i32 %r5, ptr %r1
    br label %L1
L7:  
L8:  
L9:  
    %r7 = load i32, ptr %r6
    %r10 = add i32 %r7,%r8
    store i32 %r10, ptr %r6
    br label %L4
}
define i32 @main()
{
L1:  
    %r3 = alloca i32
    %r2 = alloca i32
    %r4 = call i32 @getint()
    %r5 = load i32, ptr @m1
    store i32 %r4, ptr %r5
    %r6 = call i32 @getint()
    %r7 = load i32, ptr @n1
    store i32 %r6, ptr %r7
    store i32 1, ptr %r2
    br label %L9
    %r3 = load i32, ptr %r2
    %r4 = load i32, ptr @m1
    %r5 = load i32, ptr %r4
    %r6 = icmp slt i32 %r3,%r5
    br i1 %r6, label %L10, label %L11
    store i32 0, ptr %r3
    br label %L12
    %r4 = load i32, ptr %r3
    %r5 = load i32, ptr @n1
    %r6 = load i32, ptr %r5
    %r7 = icmp slt i32 %r4,%r6
    br i1 %r7, label %L13, label %L14
    %r8 = call i32 @getint()
    %r4 = getelementptr [100 x [100 x i32]], ptr @a, i32 0, i32 %r2, i32 %r3
    store i32 1, ptr %r4
    %r4 = load i32, ptr %r3
    %r7 = add i32 %r4,%r5
    store i32 0, ptr %r3
    br label %L13
L10:  
L11:  
L12:  
    %r3 = call i32 @getint()
    %r4 = load i32, ptr @m2
    store i32 %r3, ptr %r4
    %r5 = call i32 @getint()
    %r6 = load i32, ptr @n2
    store i32 1, ptr %r6
    store i32 0, ptr %r2
    br label %L15
    %r3 = load i32, ptr %r2
    %r4 = load i32, ptr @m2
    %r5 = load i32, ptr %r4
    %r6 = icmp slt i32 %r3,%r5
    br i1 %r6, label %L16, label %L17
    store i32 0, ptr %r3
    br label %L18
    %r4 = load i32, ptr %r3
    %r5 = load i32, ptr @n2
    %r6 = load i32, ptr %r5
    %r7 = icmp slt i32 %r4,%r6
    br i1 %r7, label %L19, label %L20
    %r8 = call i32 @getint()
    %r4 = getelementptr [100 x [100 x i32]], ptr @b, i32 0, i32 %r2, i32 %r3
    store i32 1, ptr %r4
    %r4 = load i32, ptr %r3
    %r7 = add i32 %r4,%r5
    store i32 0, ptr %r3
    br label %L19
L13:  
L14:  
L15:  
    %r3 = load i32, ptr %r2
    %r6 = add i32 %r3,%r4
    store i32 %r6, ptr %r2
    br label %L10
L16:  
L17:  
L18:  
    %r3 = call i32 @matrix_multiply()
    store i32 1, ptr %r2
    br label %L21
    %r3 = load i32, ptr %r2
    %r4 = load i32, ptr @m1
    %r5 = load i32, ptr %r4
    %r6 = icmp slt i32 %r3,%r5
    br i1 %r6, label %L22, label %L23
    store i32 0, ptr %r3
    br label %L24
    %r4 = load i32, ptr %r3
    %r5 = load i32, ptr @n2
    %r6 = load i32, ptr %r5
    %r7 = icmp slt i32 %r4,%r6
    br i1 %r7, label %L25, label %L26
    %r4 = getelementptr [100 x [100 x i32]], ptr @res, i32 0, i32 %r2, i32 %r3
    %r5 = call i32 @putint(i32 %r4)
    %r7 = call i32 @putch(i32 %r6)
    %r4 = load i32, ptr %r3
    %r7 = add i32 %r4,%r5
    store i32 0, ptr %r3
    br label %L25
L19:  
L20:  
L21:  
    %r3 = load i32, ptr %r2
    %r6 = add i32 %r3,%r4
    store i32 %r6, ptr %r2
    br label %L16
L22:  
L23:  
L24:  
    ret i32 0
L25:  
L26:  
L27:  
    %r5 = call i32 @putch(i32 %r4)
    %r3 = load i32, ptr %r2
    %r6 = add i32 %r3,%r4
    store i32 32, ptr %r2
    br label %L22
}
