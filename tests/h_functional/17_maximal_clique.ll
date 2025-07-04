@maxN = global i32 30
@maxM = global i32 600
@store = global [30x i32] zeroinitializer
@n = global i32 zeroinitializer
@m = global i32 zeroinitializer
@graph = global [30x [30x i32]] zeroinitializer
define i32 @is_clique(i32 %r0)
{
L1:  
    %r5 = alloca i32
    %r4 = load i32, ptr %r3
    %r3 = load i32, ptr %r2
    %r4 = icmp slt i32 %r4,%r3
    br i1 %r4, label %L1, label %L2
    %r4 = load i32, ptr %r3
    %r7 = add i32 %r4,%r5
    store i32 %r7, ptr %r5
    br label %L3
    %r3 = load i32, ptr %r2
    %r4 = icmp slt i32 %r5,%r3
    br i1 %r4, label %L4, label %L5
    %r4 = getelementptr [30 x i32], ptr @store, i32 0, i32 %r3
    %r6 = getelementptr [30 x i32], ptr @store, i32 0, i32 %r5
    %r7 = getelementptr [30 x [30 x i32]], ptr @graph, i32 0, i32 %r4, i32 %r6
    %r8 = load float, ptr %r7
    %r11 = icmp eq i32 %r8,%r9
    br i1 %r11, label %L6, label %L7
    ret i32 0
    br label %L8
L2:  
L3:  
    ret i32 1
L4:  
L5:  
L6:  
    %r4 = load i32, ptr %r3
    %r7 = add i32 %r4,%r5
    store i32 1, ptr %r3
    br label %L1
L7:  
L9:  
    %r9 = add i32 %r5,%r7
    store i32 0, ptr %r5
    br label %L4
}
define i32 @maxCliques(i32 %r0,i32 %r5)
{
L1:  
    %r9 = alloca i32
    %r7 = alloca i32
    store i32 0, ptr %r7
    store i32 1, ptr %r9
    store i32 1, ptr %r5
    br label %L9
    %r10 = load i32, ptr %r9
    %r11 = load i32, ptr @n
    %r12 = load i32, ptr %r11
    %r13 = icmp sle i32 %r10,%r12
    br i1 %r13, label %L10, label %L11
    %r7 = getelementptr [30 x i32], ptr @store, i32 0, i32 %r6
    store i32 %r9, ptr %r7
    %r7 = load i32, ptr %r6
    %r10 = add i32 %r7,%r8
    %r11 = call i32 @is_clique(i32 %r10)
    br i1 %r11, label %L12, label %L13
    %r7 = load i32, ptr %r6
    %r8 = load i32, ptr %r7
    %r9 = icmp sgt i32 %r7,%r8
    br i1 %r9, label %L15, label %L16
    store i32 %r6, ptr %r7
    br label %L17
L10:  
L11:  
L12:  
    ret i32 %r7
L13:  
L15:  
    %r10 = load i32, ptr %r9
    %r13 = add i32 %r10,%r11
    store i32 %r13, ptr %r9
    br label %L10
L16:  
L18:  
    %r8 = alloca i32
    %r7 = load i32, ptr %r6
    %r10 = add i32 %r7,%r8
    %r11 = call i32 @maxCliques(i32 %r9,i32 %r10)
    store i32 %r11, ptr %r8
    %r8 = load i32, ptr %r7
    %r9 = icmp sgt i32 %r8,%r8
    br i1 %r9, label %L18, label %L19
    store i32 1, ptr %r7
    br label %L20
L19:  
L21:  
    br label %L14
}
define i32 @main()
{
L1:  
    %r13 = alloca i32
    %r12 = alloca [600 x [2 x i32]]
    %r8 = call i32 @getint()
    %r9 = load i32, ptr @n
    store i32 1, ptr %r9
    %r10 = call i32 @getint()
    %r11 = load i32, ptr @m
    store i32 1, ptr %r11
    store i32 0, ptr %r13
    br label %L21
    %r14 = load i32, ptr %r13
    %r15 = load i32, ptr @m
    %r16 = load i32, ptr %r15
    %r17 = icmp slt i32 %r14,%r16
    br i1 %r17, label %L22, label %L23
    %r18 = call i32 @getint()
    %r15 = getelementptr [600 x [2 x i32]], ptr %r12, i32 0, i32 %r13, i32 %r14
    store i32 %r18, ptr %r15
    %r16 = call i32 @getint()
    %r15 = getelementptr [600 x [2 x i32]], ptr %r12, i32 0, i32 %r13, i32 %r14
    store i32 %r16, ptr %r15
    %r14 = load i32, ptr %r13
    %r17 = add i32 %r14,%r15
    store i32 %r17, ptr %r13
    br label %L22
L22:  
L23:  
L24:  
    store i32 0, ptr %r13
    br label %L24
    %r14 = load i32, ptr %r13
    %r15 = load i32, ptr @m
    %r16 = load i32, ptr %r15
    %r17 = icmp slt i32 %r14,%r16
    br i1 %r17, label %L25, label %L26
    %r15 = getelementptr [600 x [2 x i32]], ptr %r12, i32 0, i32 %r13, i32 %r14
    %r15 = getelementptr [600 x [2 x i32]], ptr %r12, i32 0, i32 %r13, i32 %r14
    %r16 = getelementptr [30 x [30 x i32]], ptr @graph, i32 0, i32 %r15, i32 %r15
    store float 1, ptr %r16
    %r15 = getelementptr [600 x [2 x i32]], ptr %r12, i32 0, i32 %r13, i32 %r14
    %r15 = getelementptr [600 x [2 x i32]], ptr %r12, i32 0, i32 %r13, i32 %r14
    %r16 = getelementptr [30 x [30 x i32]], ptr @graph, i32 0, i32 %r15, i32 %r15
    store float 1, ptr %r16
    %r14 = load i32, ptr %r13
    %r17 = add i32 %r14,%r15
    store i32 1, ptr %r13
    br label %L25
L25:  
L26:  
L27:  
    %r16 = call i32 @maxCliques(i32 %r14,i32 %r15)
    %r17 = call i32 @putint(float %r16)
    ret i32 1
}
