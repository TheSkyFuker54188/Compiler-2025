@space = global i32 32
@LF = global i32 10
@maxNode = global i32 10000
@value = global [10000x i32] zeroinitializer
@left_child = global [10000x i32] zeroinitializer
@right_child = global [10000x i32] zeroinitializer
@now = global i32 zeroinitializer
define i32 @search(i32 %r0,i32 %r3)
{
L1:  
    ret i32 %r3
    br label %L2
    %r5 = load i32, ptr %r4
    %r4 = getelementptr [10000 x i32], ptr @value, i32 0, i32 %r3
    %r5 = load i32, ptr %r4
    %r6 = icmp sgt i32 %r5,%r5
    br i1 %r6, label %L3, label %L4
    %r4 = getelementptr [10000 x i32], ptr @right_child, i32 0, i32 %r3
    %r5 = call i32 @search(i32 %r4,i32 %r4)
    ret i32 1
    br label %L5
    %r4 = getelementptr [10000 x i32], ptr @left_child, i32 0, i32 %r3
    %r5 = call i32 @search(i32 %r4,i32 %r4)
    ret i32 1
    br label %L5
L2:  
L3:  
L4:  
L5:  
L6:  
    br label %L2
}
define i32 @insert(i32 %r0,i32 %r29)
{
L1:  
    %r30 = load i32, ptr %r29
    %r32 = sub i32 %r0,%r31
    %r33 = load float, ptr %r32
    %r34 = icmp eq i32 %r30,%r33
    br i1 %r34, label %L12, label %L13
    %r31 = call i32 @new_node(i32 %r30)
    ret i32 1
    br label %L14
    %r31 = load i32, ptr %r30
    %r30 = getelementptr [10000 x i32], ptr @value, i32 0, i32 %r29
    %r31 = load i32, ptr %r30
    %r32 = icmp sgt i32 %r31,%r31
    br i1 %r32, label %L15, label %L16
    %r30 = getelementptr [10000 x i32], ptr @right_child, i32 0, i32 %r29
    %r31 = call i32 @insert(i32 %r30,i32 %r30)
    %r30 = getelementptr [10000 x i32], ptr @right_child, i32 0, i32 %r29
    store i32 1, ptr %r30
    br label %L17
    %r30 = getelementptr [10000 x i32], ptr @left_child, i32 0, i32 %r29
    %r31 = call i32 @insert(i32 %r30,i32 %r30)
    %r30 = getelementptr [10000 x i32], ptr @left_child, i32 0, i32 %r29
    store i32 1, ptr %r30
    br label %L17
L13:  
L14:  
L15:  
    ret i32 %r29
L16:  
L17:  
L18:  
    br label %L14
}
define i32 @find_minimum(i32 %r0)
{
L1:  
    %r7 = load i32, ptr %r6
    %r9 = sub i32 %r0,%r8
    %r10 = load float, ptr %r9
    %r11 = icmp eq i32 %r7,%r10
    br i1 %r11, label %L6, label %L7
    %r13 = sub i32 %r0,%r12
    ret i32 %r13
    br label %L8
    %r7 = getelementptr [10000 x i32], ptr @left_child, i32 0, i32 %r6
    %r8 = load float, ptr %r7
    %r10 = sub i32 %r0,%r9
    %r11 = load float, ptr %r10
    %r12 = icmp ne i32 %r8,%r11
    br i1 %r12, label %L9, label %L10
    %r7 = getelementptr [10000 x i32], ptr @left_child, i32 0, i32 %r6
    %r8 = call i32 @find_minimum(float %r7)
    ret i32 1
    br label %L11
L7:  
L8:  
L9:  
    ret i32 %r6
L10:  
L12:  
    br label %L8
}
define i32 @new_node(i32 %r0)
{
L1:  
    %r8 = load i32, ptr @now
    %r9 = getelementptr [10000 x i32], ptr @value, i32 0, i32 %r8
    store i32 %r7, ptr %r9
    %r11 = sub i32 %r0,%r10
    %r12 = load i32, ptr @now
    %r13 = getelementptr [10000 x i32], ptr @left_child, i32 0, i32 %r12
    store float %r11, ptr %r13
    %r15 = sub i32 %r0,%r14
    %r16 = load i32, ptr @now
    %r17 = getelementptr [10000 x i32], ptr @right_child, i32 0, i32 %r16
    store float %r15, ptr %r17
    %r18 = load i32, ptr @now
    %r19 = load i32, ptr %r18
    %r22 = add i32 %r19,%r20
    %r23 = load i32, ptr @now
    store i32 %r22, ptr %r23
    %r24 = load i32, ptr @now
    %r25 = load i32, ptr %r24
    %r28 = sub i32 %r25,%r26
    ret i32 %r28
}
define i32 @delete(i32 %r0,i32 %r30)
{
L1:  
    %r31 = load i32, ptr %r30
    %r33 = sub i32 %r0,%r32
    %r34 = load float, ptr %r33
    %r35 = icmp eq i32 %r31,%r34
    br i1 %r35, label %L18, label %L19
    %r37 = sub i32 %r0,%r36
    ret i32 %r37
    br label %L20
L19:  
L21:  
    %r32 = load i32, ptr %r31
    %r31 = getelementptr [10000 x i32], ptr @value, i32 0, i32 %r30
    %r32 = load i32, ptr %r31
    %r33 = icmp sgt i32 %r32,%r32
    br i1 %r33, label %L21, label %L22
    %r31 = getelementptr [10000 x i32], ptr @right_child, i32 0, i32 %r30
    %r32 = call i32 @delete(i32 %r31,i32 %r31)
    %r31 = getelementptr [10000 x i32], ptr @right_child, i32 0, i32 %r30
    store i32 1, ptr %r31
    br label %L23
    %r32 = load i32, ptr %r31
    %r31 = getelementptr [10000 x i32], ptr @value, i32 0, i32 %r30
    %r32 = load i32, ptr %r31
    %r33 = icmp slt i32 %r32,%r32
    br i1 %r33, label %L24, label %L25
    %r31 = getelementptr [10000 x i32], ptr @left_child, i32 0, i32 %r30
    %r32 = call i32 @delete(i32 %r31,i32 %r31)
    %r31 = getelementptr [10000 x i32], ptr @left_child, i32 0, i32 %r30
    store i32 1, ptr %r31
    br label %L26
    %r31 = getelementptr [10000 x i32], ptr @left_child, i32 0, i32 %r30
    %r32 = load i32, ptr %r31
    %r34 = sub i32 %r0,%r33
    %r35 = load float, ptr %r34
    %r36 = icmp eq i32 %r32,%r35
    %r37 = load i32, ptr %r36
    %r31 = getelementptr [10000 x i32], ptr @right_child, i32 0, i32 %r30
    %r32 = load i32, ptr %r31
    %r34 = sub i32 %r0,%r33
    %r35 = load float, ptr %r34
    %r36 = icmp eq i32 %r32,%r35
    %r37 = load i32, ptr %r36
    %r38 = and i32 %r37,%r37
    br i1 %r38, label %L27, label %L28
    %r40 = sub i32 %r0,%r39
    ret i32 %r40
    br label %L29
    %r31 = getelementptr [10000 x i32], ptr @left_child, i32 0, i32 %r30
    %r32 = load i32, ptr %r31
    %r34 = sub i32 %r0,%r33
    %r35 = load float, ptr %r34
    %r36 = icmp eq i32 %r32,%r35
    %r37 = load i32, ptr %r36
    %r31 = getelementptr [10000 x i32], ptr @right_child, i32 0, i32 %r30
    %r32 = load i32, ptr %r31
    %r34 = sub i32 %r0,%r33
    %r35 = load float, ptr %r34
    %r36 = icmp eq i32 %r32,%r35
    %r37 = load i32, ptr %r36
    %r38 = xor i32 %r37,%r37
    br i1 %r38, label %L30, label %L31
    %r31 = getelementptr [10000 x i32], ptr @left_child, i32 0, i32 %r30
    %r32 = load i32, ptr %r31
    %r34 = sub i32 %r0,%r33
    %r35 = load float, ptr %r34
    %r36 = icmp eq i32 %r32,%r35
    br i1 %r36, label %L33, label %L34
    %r31 = getelementptr [10000 x i32], ptr @right_child, i32 0, i32 %r30
    ret i32 %r31
    br label %L35
    %r31 = getelementptr [10000 x i32], ptr @left_child, i32 0, i32 %r30
    ret i32 %r31
    br label %L35
L22:  
L23:  
L24:  
    ret i32 %r30
L25:  
L26:  
L27:  
    br label %L23
L28:  
L29:  
L30:  
    br label %L26
L31:  
L32:  
L33:  
    br label %L29
L34:  
L35:  
L36:  
    %r32 = alloca i32
    br label %L32
    %r31 = getelementptr [10000 x i32], ptr @right_child, i32 0, i32 %r30
    %r32 = call i32 @find_minimum(i32 %r31)
    store i32 %r32, ptr %r32
    %r33 = getelementptr [10000 x i32], ptr @value, i32 0, i32 %r32
    %r31 = getelementptr [10000 x i32], ptr @value, i32 0, i32 %r30
    store i32 1, ptr %r31
    %r31 = getelementptr [10000 x i32], ptr @right_child, i32 0, i32 %r30
    %r33 = getelementptr [10000 x i32], ptr @value, i32 0, i32 %r32
    %r34 = call i32 @delete(i32 %r31,i32 %r33)
    %r31 = getelementptr [10000 x i32], ptr @right_child, i32 0, i32 %r30
    store i32 %r34, ptr %r31
    br label %L32
}
define float @inorder(i32 %r0)
{
L1:  
    %r32 = load i32, ptr %r31
    %r34 = sub i32 %r0,%r33
    %r35 = load float, ptr %r34
    %r36 = icmp ne i32 %r32,%r35
    br i1 %r36, label %L36, label %L37
    %r32 = getelementptr [10000 x i32], ptr @left_child, i32 0, i32 %r31
    %r33 = call float @inorder(i32 %r32)
    %r32 = getelementptr [10000 x i32], ptr @value, i32 0, i32 %r31
    %r33 = call float @putint(i32 %r32)
    %r35 = call float @putch(i32 %r34)
    %r32 = getelementptr [10000 x i32], ptr @right_child, i32 0, i32 %r31
    %r33 = call float @inorder(i32 %r32)
    br label %L38
L37:  
L39:  
}
define i32 @main()
{
L1:  
    %r36 = alloca i32
    %r35 = load i32, ptr @now
    store i32 32, ptr %r35
    %r37 = call i32 @getint()
    store i32 %r37, ptr %r36
    %r37 = icmp eq i32 %r36,%r0
    br i1 %r37, label %L39, label %L40
    ret i32 0
    br label %L41
L40:  
L42:  
    %r42 = alloca i32
    %r39 = alloca i32
    %r40 = call i32 @getint()
    %r41 = call i32 @new_node(float %r40)
    store i32 %r41, ptr %r39
    store i32 1, ptr %r42
    br label %L42
    %r43 = load i32, ptr %r42
    %r37 = load i32, ptr %r36
    %r38 = icmp slt i32 %r43,%r37
    br i1 %r38, label %L43, label %L44
    %r40 = call i32 @getint()
    %r41 = call i32 @insert(i32 %r39,float %r40)
    %r43 = load i32, ptr %r42
    %r46 = add i32 %r43,%r44
    store i32 %r46, ptr %r42
    br label %L43
L43:  
L44:  
L45:  
    %r40 = call i32 @inorder(i32 %r39)
    %r42 = call i32 @putch(i32 %r41)
    %r43 = call i32 @getint()
    store i32 1, ptr %r36
    store i32 0, ptr %r42
    br label %L45
    %r43 = load i32, ptr %r42
    %r37 = load i32, ptr %r36
    %r38 = icmp slt i32 %r43,%r37
    br i1 %r38, label %L46, label %L47
    %r40 = call i32 @getint()
    %r41 = call i32 @delete(i32 %r39,float %r40)
    store i32 10, ptr %r39
    %r43 = load i32, ptr %r42
    %r46 = add i32 %r43,%r44
    store i32 %r46, ptr %r42
    br label %L46
L46:  
L47:  
L48:  
    %r40 = call i32 @inorder(i32 %r39)
    %r42 = call i32 @putch(i32 %r41)
    ret i32 1
}
