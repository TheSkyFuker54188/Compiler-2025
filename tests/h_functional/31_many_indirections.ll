@N = global i32 100
@M = global i32 20
@array = global [20x [100x i32]] zeroinitializer
define i32 @main()
{
L1:  
    %r7 = alloca i32
    %r3 = load i32, ptr %r2
    %r6 = icmp slt i32 %r3,%r4
    br i1 %r6, label %L1, label %L2
    store i32 0, ptr %r7
    br label %L3
    %r8 = load i32, ptr %r7
    %r11 = icmp slt i32 %r8,%r9
    br i1 %r11, label %L4, label %L5
    %r8 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r2, i32 %r7
    store i32 %r7, ptr %r8
    %r8 = load i32, ptr %r7
    %r11 = add i32 %r8,%r9
    store i32 %r11, ptr %r7
    br label %L4
L2:  
L3:  
    %r24 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r22, i32 %r23
    %r25 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r21, i32 %r24
    %r26 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r20, i32 %r25
    %r27 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r19, i32 %r26
    %r28 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r18, i32 %r27
    %r29 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r17, i32 %r28
    %r30 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r16, i32 %r29
    %r31 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r15, i32 %r30
    %r32 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r14, i32 %r31
    %r33 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r13, i32 %r32
    %r34 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r12, i32 %r33
    %r35 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r11, i32 %r34
    %r36 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r10, i32 %r35
    %r37 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r9, i32 %r36
    %r38 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r8, i32 %r37
    %r39 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r7, i32 %r38
    %r40 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r6, i32 %r39
    %r41 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r5, i32 %r40
    %r42 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r4, i32 %r41
    %r43 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r3, i32 %r42
    %r44 = load float, ptr %r43
    %r47 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r45, i32 %r46
    %r49 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r47, i32 %r48
    %r51 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r49, i32 %r50
    %r53 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r51, i32 %r52
    %r55 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r53, i32 %r54
    %r57 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r55, i32 %r56
    %r59 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r57, i32 %r58
    %r61 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r59, i32 %r60
    %r63 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r61, i32 %r62
    %r65 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r63, i32 %r64
    %r67 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r65, i32 %r66
    %r69 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r67, i32 %r68
    %r71 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r69, i32 %r70
    %r73 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r71, i32 %r72
    %r75 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r73, i32 %r74
    %r77 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r75, i32 %r76
    %r79 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r77, i32 %r78
    %r81 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r79, i32 %r80
    %r83 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r81, i32 %r82
    %r85 = getelementptr [20 x [100 x i32]], ptr @array, i32 0, i32 %r83, i32 %r84
    %r86 = load float, ptr %r85
    %r87 = add i32 %r44,%r86
    store i32 %r87, ptr %r4
    %r5 = call i32 @putint(i32 %r4)
    ret i32 3
L4:  
L5:  
L6:  
    %r3 = load i32, ptr %r2
    %r6 = add i32 %r3,%r4
    store i32 %r6, ptr %r2
    br label %L1
}
