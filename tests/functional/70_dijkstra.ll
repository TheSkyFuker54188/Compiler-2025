@INF = global i32 65535
@e = global [16x [16x i32]] zeroinitializer
@book = global [16x i32] zeroinitializer
@dis = global [16x i32] zeroinitializer
@n = global i32 zeroinitializer
@m = global i32 zeroinitializer
@v1 = global i32 zeroinitializer
@v2 = global i32 zeroinitializer
@w = global i32 zeroinitializer
define float @Dijkstra()
{
L1:  
    %r2 = load i32, ptr %r1
    %r3 = load i32, ptr @n
    %r4 = load i32, ptr %r3
    %r5 = icmp sle i32 %r2,%r4
    br i1 %r5, label %L1, label %L2
    %r2 = getelementptr [16 x [16 x i32]], ptr @e, i32 0, i32 %r6, i32 %r1
    %r2 = getelementptr [16 x i32], ptr @dis, i32 0, i32 %r1
    store i32 %r2, ptr %r2
    %r2 = getelementptr [16 x i32], ptr @book, i32 0, i32 %r1
    store i32 0, ptr %r2
    %r2 = load i32, ptr %r1
    %r5 = add i32 %r2,%r3
    store i32 %r5, ptr %r1
    br label %L1
L2:  
L3:  
    %r14 = alloca i32
    %r12 = alloca i32
    %r10 = alloca i32
    %r4 = getelementptr [16 x i32], ptr @book, i32 0, i32 %r3
    store float 1, ptr %r4
    store i32 1, ptr %r1
    br label %L3
    %r2 = load i32, ptr %r1
    %r3 = load i32, ptr @n
    %r4 = load i32, ptr %r3
    %r7 = sub i32 %r4,%r5
    %r8 = load float, ptr %r7
    %r9 = icmp sle i32 %r2,%r8
    br i1 %r9, label %L4, label %L5
    store i32 65535, ptr %r10
    store i32 0, ptr %r12
    store i32 1, ptr %r14
    br label %L6
    %r15 = load i32, ptr %r14
    %r16 = load i32, ptr @n
    %r17 = load i32, ptr %r16
    %r18 = icmp sle i32 %r15,%r17
    br i1 %r18, label %L7, label %L8
    %r11 = load i32, ptr %r10
    %r15 = getelementptr [16 x i32], ptr @dis, i32 0, i32 %r14
    %r16 = load i32, ptr %r15
    %r17 = icmp sgt i32 %r11,%r16
    %r18 = load float, ptr %r17
    %r15 = getelementptr [16 x i32], ptr @book, i32 0, i32 %r14
    %r16 = load i32, ptr %r15
    %r19 = icmp eq i32 %r16,%r17
    %r20 = load float, ptr %r19
    %r21 = and i32 %r18,%r20
    br i1 %r21, label %L9, label %L10
    %r15 = getelementptr [16 x i32], ptr @dis, i32 0, i32 %r14
    store i32 1, ptr %r10
    store i32 %r14, ptr %r12
    br label %L11
L4:  
L5:  
L6:  
L7:  
L8:  
L9:  
    %r14 = alloca i32
    %r13 = getelementptr [16 x i32], ptr @book, i32 0, i32 %r12
    store i32 1, ptr %r13
    store i32 1, ptr %r14
    br label %L12
    %r15 = load i32, ptr %r14
    %r16 = load i32, ptr @n
    %r17 = load i32, ptr %r16
    %r18 = icmp sle i32 %r15,%r17
    br i1 %r18, label %L13, label %L14
    %r15 = getelementptr [16 x [16 x i32]], ptr @e, i32 0, i32 %r12, i32 %r14
    %r16 = load i32, ptr %r15
    %r19 = icmp slt i32 %r16,%r17
    br i1 %r19, label %L15, label %L16
    %r15 = getelementptr [16 x i32], ptr @dis, i32 0, i32 %r14
    %r16 = load i32, ptr %r15
    %r13 = getelementptr [16 x i32], ptr @dis, i32 0, i32 %r12
    %r14 = load i32, ptr %r13
    %r15 = getelementptr [16 x [16 x i32]], ptr @e, i32 0, i32 %r12, i32 %r14
    %r16 = load i32, ptr %r15
    %r17 = add i32 %r14,%r16
    %r18 = load i32, ptr %r17
    %r19 = icmp sgt i32 %r16,%r18
    br i1 %r19, label %L18, label %L19
    %r13 = getelementptr [16 x i32], ptr @dis, i32 0, i32 %r12
    %r14 = load i32, ptr %r13
    %r15 = getelementptr [16 x [16 x i32]], ptr @e, i32 0, i32 %r12, i32 %r14
    %r16 = load i32, ptr %r15
    %r17 = add i32 %r14,%r16
    %r15 = getelementptr [16 x i32], ptr @dis, i32 0, i32 %r14
    store i32 65535, ptr %r15
    br label %L20
L10:  
L12:  
    %r15 = load i32, ptr %r14
    %r18 = add i32 %r15,%r16
    store i32 %r18, ptr %r14
    br label %L7
L13:  
L14:  
L15:  
    %r2 = load i32, ptr %r1
    %r5 = add i32 %r2,%r3
    store i32 1, ptr %r1
    br label %L4
L16:  
L18:  
    %r15 = load i32, ptr %r14
    %r18 = add i32 %r15,%r16
    store i32 %r18, ptr %r14
    br label %L13
L19:  
L21:  
    br label %L17
}
define i32 @main()
{
L1:  
    %r7 = alloca i32
    %r2 = alloca i32
    %r3 = call i32 @getint()
    %r4 = load i32, ptr @n
    store i32 1, ptr %r4
    %r5 = call i32 @getint()
    %r6 = load i32, ptr @m
    store i32 1, ptr %r6
    store i32 1, ptr %r2
    br label %L21
    %r3 = load i32, ptr %r2
    %r4 = load i32, ptr @n
    %r5 = load i32, ptr %r4
    %r6 = icmp sle i32 %r3,%r5
    br i1 %r6, label %L22, label %L23
    store i32 1, ptr %r7
    br label %L24
    %r8 = load i32, ptr %r7
    %r9 = load i32, ptr @n
    %r10 = load i32, ptr %r9
    %r11 = icmp sle i32 %r8,%r10
    br i1 %r11, label %L25, label %L26
    %r3 = load i32, ptr %r2
    %r8 = load i32, ptr %r7
    %r9 = icmp eq i32 %r3,%r8
    br i1 %r9, label %L27, label %L28
    %r8 = getelementptr [16 x [16 x i32]], ptr @e, i32 0, i32 %r2, i32 %r7
    store i32 0, ptr %r8
    br label %L29
    %r8 = getelementptr [16 x [16 x i32]], ptr @e, i32 0, i32 %r2, i32 %r7
    store i32 65535, ptr %r8
    br label %L29
L22:  
L23:  
L24:  
    %r9 = alloca i32
    %r7 = alloca i32
    store i32 1, ptr %r2
    br label %L30
    %r3 = load i32, ptr %r2
    %r4 = load i32, ptr @m
    %r5 = load i32, ptr %r4
    %r6 = icmp sle i32 %r3,%r5
    br i1 %r6, label %L31, label %L32
    %r8 = call i32 @getint()
    store i32 1, ptr %r7
    %r10 = call i32 @getint()
    store i32 0, ptr %r9
    %r11 = call i32 @getint()
    %r10 = getelementptr [16 x [16 x i32]], ptr @e, i32 0, i32 %r7, i32 %r9
    store i32 65535, ptr %r10
    %r3 = load i32, ptr %r2
    %r6 = add i32 %r3,%r4
    store i32 %r6, ptr %r2
    br label %L31
L25:  
L26:  
L27:  
    %r3 = load i32, ptr %r2
    %r6 = add i32 %r3,%r4
    store i32 %r6, ptr %r2
    br label %L22
L28:  
L29:  
L30:  
    %r8 = load i32, ptr %r7
    %r11 = add i32 %r8,%r9
    store i32 65535, ptr %r7
    br label %L25
L31:  
L32:  
L33:  
    %r3 = call i32 @Dijkstra()
    store i32 1, ptr %r2
    br label %L33
    %r3 = load i32, ptr %r2
    %r4 = load i32, ptr @n
    %r5 = load i32, ptr %r4
    %r6 = icmp sle i32 %r3,%r5
    br i1 %r6, label %L34, label %L35
    %r3 = getelementptr [16 x i32], ptr @dis, i32 0, i32 %r2
    %r4 = call i32 @putint(i32 %r3)
    %r6 = call i32 @putch(i32 %r5)
    %r3 = load i32, ptr %r2
    %r6 = add i32 %r3,%r4
    store i32 %r6, ptr %r2
    br label %L34
L34:  
L35:  
L36:  
    %r4 = call i32 @putch(i32 %r3)
    ret i32 1
}
