@V = global i32 4
@space = global i32 32
@LF = global i32 10
define float @printSolution(i32 %r0)
{
L1:  
    %r5 = load i32, ptr %r4
    %r8 = icmp slt i32 %r5,%r6
    br i1 %r8, label %L1, label %L2
    %r5 = getelementptr [0 x i32], ptr %r3, i32 0, i32 %r4
    %r6 = call float @putint(i32 %r5)
    %r8 = call float @putch(i32 %r7)
    %r5 = load i32, ptr %r4
    %r8 = add i32 %r5,%r6
    store i32 %r8, ptr %r4
    br label %L1
L2:  
L3:  
    %r6 = call float @putch(i32 %r5)
}
define i32 @isSafe(i32 %r0,i32 %r25)
{
L1:  
    %r32 = alloca i32
    %r27 = alloca i32
    store i32 0, ptr %r27
    br label %L3
    %r28 = load i32, ptr %r27
    %r31 = icmp slt i32 %r28,%r29
    br i1 %r31, label %L4, label %L5
    %r28 = load i32, ptr %r27
    %r31 = add i32 %r28,%r29
    store i32 %r31, ptr %r32
    br label %L6
    %r33 = load i32, ptr %r32
    %r36 = icmp slt i32 %r33,%r34
    br i1 %r36, label %L7, label %L8
    %r33 = getelementptr [0 x i32], ptr %r25, i32 0, i32 %r27, i32 %r32
    %r34 = load float, ptr %r33
    %r33 = getelementptr [0 x i32], ptr %r26, i32 0, i32 %r32
    %r34 = load float, ptr %r33
    %r28 = getelementptr [0 x i32], ptr %r26, i32 0, i32 %r27
    %r30 = icmp eq i32 %r34,%r28
    %r31 = load float, ptr %r30
    %r32 = and i32 %r34,%r31
    br i1 %r32, label %L9, label %L10
    ret i32 0
    br label %L11
L4:  
L5:  
L6:  
    ret i32 0
L7:  
L8:  
L9:  
    %r28 = load i32, ptr %r27
    %r31 = add i32 %r28,%r29
    store i32 %r31, ptr %r27
    br label %L4
L10:  
L12:  
    %r33 = load i32, ptr %r32
    %r36 = add i32 %r33,%r34
    store i32 %r36, ptr %r32
    br label %L7
}
define float @printMessage()
{
L1:  
    %r8 = call float @putch(i32 %r7)
    %r10 = call float @putch(i32 %r9)
    %r12 = call float @putch(i32 %r11)
    %r14 = call float @putch(i32 %r13)
    %r16 = call float @putch(i32 %r15)
    %r18 = call float @putch(i32 %r17)
    %r20 = call float @putch(i32 %r19)
    %r22 = call float @putch(i32 %r21)
    %r24 = call float @putch(i32 %r23)
}
define i32 @graphColoring(i32 %r0,i32 %r29,i32 %r2,i32 %r30)
{
L1:  
    %r32 = load i32, ptr %r31
    %r35 = icmp eq i32 %r32,%r33
    br i1 %r35, label %L12, label %L13
    %r33 = call i32 @isSafe(i32 %r29,i32 %r32)
    br i1 %r33, label %L15, label %L16
    %r33 = call i32 @printSolution(i32 %r32)
    ret i32 4
    br label %L17
L13:  
L15:  
    %r36 = alloca i32
    store i32 1, ptr %r36
    br label %L18
    %r37 = load i32, ptr %r36
    %r31 = load i32, ptr %r30
    %r32 = icmp sle i32 %r37,%r31
    br i1 %r32, label %L19, label %L20
    %r32 = getelementptr [0 x i32], ptr %r32, i32 0, i32 %r31
    store i32 %r36, ptr %r32
    %r32 = load i32, ptr %r31
    %r35 = add i32 %r32,%r33
    %r33 = call i32 @graphColoring(i32 %r29,i32 %r30,i32 %r35,i32 %r32)
    br i1 %r33, label %L21, label %L22
    ret i32 4
    br label %L23
L16:  
L18:  
    ret i32 0
    br label %L14
L19:  
L20:  
L21:  
    ret i32 1
L22:  
L24:  
    %r32 = getelementptr [0 x i32], ptr %r32, i32 0, i32 %r31
    store i32 0, ptr %r32
    %r37 = load i32, ptr %r36
    %r40 = add i32 %r37,%r38
    store i32 %r40, ptr %r36
    br label %L19
}
define i32 @main()
{
L1:  
    %r78 = alloca i32
    %r77 = alloca [4 x i32]
    %r75 = alloca i32
    %r38 = alloca [4 x [4 x i32]]
    %r39 = getelementptr [4 x [4 x i32]], ptr %r38, i32 0, i32 0
    %r41 = getelementptr [4 x i32], ptr %r39, i32 0, i32 0
    store i32 0, ptr %r41
    %r43 = getelementptr [4 x i32], ptr %r39, i32 0, i32 1
    store i32 1, ptr %r43
    %r45 = getelementptr [4 x i32], ptr %r39, i32 0, i32 2
    store i32 1, ptr %r45
    %r47 = getelementptr [4 x i32], ptr %r39, i32 0, i32 3
    store i32 1, ptr %r47
    %r48 = getelementptr [4 x [4 x i32]], ptr %r38, i32 1, i32 0
    %r50 = getelementptr [4 x i32], ptr %r48, i32 0, i32 0
    store i32 1, ptr %r50
    %r52 = getelementptr [4 x i32], ptr %r48, i32 0, i32 1
    store i32 0, ptr %r52
    %r54 = getelementptr [4 x i32], ptr %r48, i32 0, i32 2
    store i32 1, ptr %r54
    %r56 = getelementptr [4 x i32], ptr %r48, i32 0, i32 3
    store i32 0, ptr %r56
    %r57 = getelementptr [4 x [4 x i32]], ptr %r38, i32 2, i32 0
    %r59 = getelementptr [4 x i32], ptr %r57, i32 0, i32 0
    store i32 1, ptr %r59
    %r61 = getelementptr [4 x i32], ptr %r57, i32 0, i32 1
    store i32 1, ptr %r61
    %r63 = getelementptr [4 x i32], ptr %r57, i32 0, i32 2
    store i32 0, ptr %r63
    %r65 = getelementptr [4 x i32], ptr %r57, i32 0, i32 3
    store i32 1, ptr %r65
    %r66 = getelementptr [4 x [4 x i32]], ptr %r38, i32 3, i32 0
    %r68 = getelementptr [4 x i32], ptr %r66, i32 0, i32 0
    store i32 1, ptr %r68
    %r70 = getelementptr [4 x i32], ptr %r66, i32 0, i32 1
    store i32 0, ptr %r70
    %r72 = getelementptr [4 x i32], ptr %r66, i32 0, i32 2
    store i32 1, ptr %r72
    %r74 = getelementptr [4 x i32], ptr %r66, i32 0, i32 3
    store i32 0, ptr %r74
    store i32 3, ptr %r75
    store i32 0, ptr %r78
    br label %L24
    %r79 = load i32, ptr %r78
    %r82 = icmp slt i32 %r79,%r80
    br i1 %r82, label %L25, label %L26
    %r79 = getelementptr [4 x i32], ptr %r77, i32 0, i32 %r78
    store i32 0, ptr %r79
    %r79 = load i32, ptr %r78
    %r82 = add i32 %r79,%r80
    store i32 %r82, ptr %r78
    br label %L25
L25:  
L26:  
L27:  
    %r78 = call i32 @graphColoring(i32 %r38,i32 %r75,i32 %r76,i32 %r77)
    %r79 = icmp eq i32 %r78,%r0
    br i1 %r79, label %L27, label %L28
    %r80 = call i32 @printMessage()
    br label %L29
L28:  
L30:  
    ret i32 0
}
