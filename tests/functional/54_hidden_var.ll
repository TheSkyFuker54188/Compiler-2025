@b = global i32 5
@c = global [4 x i32] [i32 6,i32 7,i32 8,i32 9]
define i32 @main()
{
L1:  
    %r11 = alloca i32
    %r7 = load i32, ptr %r6
    %r10 = icmp slt i32 %r7,%r8
    br i1 %r10, label %L1, label %L2
    store i32 0, ptr %r11
    %r12 = load i32, ptr %r11
    %r15 = add i32 %r12,%r13
    store i32 %r15, ptr %r11
    br i1 %r11, label %L3, label %L4
    br label %L2
    br label %L5
L2:  
L3:  
    %r32 = alloca [7 x [1 x [5 x i32]]]
    %r28 = alloca i32
    %r18 = alloca [2 x [8 x i32]]
    %r12 = call i32 @putint(i32 %r11)
    %r14 = call i32 @putch(i32 %r13)
    %r17 = getelementptr [4 x i32], ptr @c, i32 0, i32 %r16
    store float 1, ptr %r17
    %r19 = getelementptr [2 x [8 x i32]], ptr %r18, i32 0, i32 0
    %r21 = getelementptr [8 x i32], ptr %r19, i32 0, i32 0
    store i32 0, ptr %r21
    %r23 = getelementptr [8 x i32], ptr %r19, i32 0, i32 1
    store i32 9, ptr %r23
    %r24 = getelementptr [2 x [8 x i32]], ptr %r18, i32 1, i32 0
    store i32 8, ptr %r24
    %r26 = getelementptr [2 x [8 x i32]], ptr %r18, i32 2, i32 0
    store i32 3, ptr %r26
    store i32 2, ptr %r28
    %r31 = getelementptr [2 x [8 x i32]], ptr %r18, i32 0, i32 %r30
    br i1 %r31, label %L6, label %L7
    %r33 = getelementptr [7 x [1 x [5 x i32]]], ptr %r32, i32 0, i32 0
    %r34 = getelementptr [7 x [1 x [5 x i32]]], ptr %r32, i32 1, i32 0
    %r35 = getelementptr [7 x [1 x [5 x i32]]], ptr %r32, i32 2, i32 0
    %r37 = getelementptr [1 x [5 x i32]], ptr %r35, i32 0, i32 0
    store i32 2, ptr %r37
    %r38 = getelementptr [7 x [1 x [5 x i32]]], ptr %r32, i32 3, i32 0
    %r39 = getelementptr [1 x [5 x i32]], ptr %r38, i32 0, i32 0
    store i32 %r38, ptr %r39
    %r31 = getelementptr [7 x [1 x [5 x i32]]], ptr %r32, i32 0, i32 %r28, i32 %r29, i32 %r30
    %r32 = call i32 @putint(float %r31)
    %r31 = getelementptr [7 x [1 x [5 x i32]]], ptr %r32, i32 0, i32 %r28, i32 %r29, i32 %r30
    %r32 = call i32 @putint(float %r31)
    %r31 = getelementptr [7 x [1 x [5 x i32]]], ptr %r32, i32 0, i32 %r28, i32 %r29, i32 %r30
    %r32 = call i32 @putint(float %r31)
    br label %L8
L4:  
L6:  
    br label %L1
L7:  
L9:  
    %r34 = call i32 @putch(i32 %r33)
    %r29 = call i32 @putint(i32 %r28)
    %r31 = call i32 @putch(i32 %r30)
    %r33 = getelementptr [7 x [1 x [5 x i32]]], ptr %r32, i32 0, i32 %r32
    %r34 = call i32 @putint(i32 %r33)
    %r36 = getelementptr [7 x [1 x [5 x i32]]], ptr %r32, i32 0, i32 %r35
    %r37 = call i32 @putint(i32 %r36)
    %r39 = getelementptr [7 x [1 x [5 x i32]]], ptr %r32, i32 0, i32 %r38
    %r40 = call i32 @putint(float %r39)
    %r42 = getelementptr [7 x [1 x [5 x i32]]], ptr %r32, i32 0, i32 %r41
    %r43 = call i32 @putint(float %r42)
    %r45 = call i32 @putch(i32 %r44)
    ret i32 0
}
