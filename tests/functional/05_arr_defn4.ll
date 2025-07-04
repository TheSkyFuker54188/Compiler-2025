define i32 @main()
{
L1:  
    %r41 = alloca [4 x [2 x [1 x i32]]]
    %r24 = alloca [4 x [2 x i32]]
    %r7 = alloca [4 x [2 x i32]]
    %r6 = alloca [4 x [2 x i32]]
    %r0 = alloca i32
    store i32 1, ptr %r0
    %r8 = getelementptr [4 x [2 x i32]], ptr %r7, i32 0, i32 0
    store i32 1, ptr %r8
    %r10 = getelementptr [4 x [2 x i32]], ptr %r7, i32 1, i32 0
    store i32 2, ptr %r10
    %r12 = getelementptr [4 x [2 x i32]], ptr %r7, i32 2, i32 0
    store i32 3, ptr %r12
    %r14 = getelementptr [4 x [2 x i32]], ptr %r7, i32 3, i32 0
    store i32 4, ptr %r14
    %r16 = getelementptr [4 x [2 x i32]], ptr %r7, i32 4, i32 0
    store i32 5, ptr %r16
    %r18 = getelementptr [4 x [2 x i32]], ptr %r7, i32 5, i32 0
    store i32 6, ptr %r18
    %r20 = getelementptr [4 x [2 x i32]], ptr %r7, i32 6, i32 0
    store i32 7, ptr %r20
    %r22 = getelementptr [4 x [2 x i32]], ptr %r7, i32 7, i32 0
    store i32 8, ptr %r22
    %r25 = getelementptr [4 x [2 x i32]], ptr %r24, i32 0, i32 0
    store i32 1, ptr %r25
    %r27 = getelementptr [4 x [2 x i32]], ptr %r24, i32 1, i32 0
    store i32 2, ptr %r27
    %r29 = getelementptr [4 x [2 x i32]], ptr %r24, i32 2, i32 0
    %r31 = getelementptr [2 x i32], ptr %r29, i32 0, i32 0
    store i32 3, ptr %r31
    %r32 = getelementptr [4 x [2 x i32]], ptr %r24, i32 3, i32 0
    %r34 = getelementptr [2 x i32], ptr %r32, i32 0, i32 0
    store i32 5, ptr %r34
    %r35 = getelementptr [4 x [2 x i32]], ptr %r24, i32 4, i32 0
    %r38 = getelementptr i32, ptr %r0, i32 0, i32 %r36, i32 %r37
    store i32 %r38, ptr %r35
    %r39 = getelementptr [4 x [2 x i32]], ptr %r24, i32 5, i32 0
    store i32 8, ptr %r39
    %r42 = getelementptr [4 x [2 x [1 x i32]]], ptr %r41, i32 0, i32 0
    %r45 = getelementptr [4 x [2 x i32]], ptr %r24, i32 0, i32 %r43, i32 %r44
    %r46 = getelementptr [2 x [1 x i32]], ptr %r42, i32 0, i32 0
    store i32 %r45, ptr %r46
    %r49 = getelementptr [4 x [2 x i32]], ptr %r7, i32 0, i32 %r47, i32 %r48
    %r50 = getelementptr [2 x [1 x i32]], ptr %r42, i32 0, i32 1
    store i32 %r49, ptr %r50
    %r51 = getelementptr [4 x [2 x [1 x i32]]], ptr %r41, i32 1, i32 0
    %r53 = getelementptr [2 x [1 x i32]], ptr %r51, i32 0, i32 0
    store i32 3, ptr %r53
    %r55 = getelementptr [2 x [1 x i32]], ptr %r51, i32 0, i32 1
    store i32 4, ptr %r55
    %r56 = getelementptr [4 x [2 x [1 x i32]]], ptr %r41, i32 2, i32 0
    %r58 = getelementptr [2 x [1 x i32]], ptr %r56, i32 0, i32 0
    store i32 5, ptr %r58
    %r60 = getelementptr [2 x [1 x i32]], ptr %r56, i32 0, i32 1
    store i32 6, ptr %r60
    %r61 = getelementptr [4 x [2 x [1 x i32]]], ptr %r41, i32 3, i32 0
    %r63 = getelementptr [2 x [1 x i32]], ptr %r61, i32 0, i32 0
    store i32 7, ptr %r63
    %r65 = getelementptr [2 x [1 x i32]], ptr %r61, i32 0, i32 1
    store i32 8, ptr %r65
    %r69 = getelementptr [4 x [2 x [1 x i32]]], ptr %r41, i32 0, i32 %r66, i32 %r67, i32 %r68
    %r70 = load float, ptr %r69
    %r74 = getelementptr [4 x [2 x [1 x i32]]], ptr %r41, i32 0, i32 %r71, i32 %r72, i32 %r73
    %r75 = load float, ptr %r74
    %r76 = add i32 %r70,%r75
    %r77 = load float, ptr %r76
    %r81 = getelementptr [4 x [2 x [1 x i32]]], ptr %r41, i32 0, i32 %r78, i32 %r79, i32 %r80
    %r82 = load float, ptr %r81
    %r83 = add i32 %r77,%r82
    %r84 = load float, ptr %r83
    %r87 = getelementptr [4 x [2 x i32]], ptr %r24, i32 0, i32 %r85, i32 %r86
    %r88 = load float, ptr %r87
    %r89 = add i32 %r84,%r88
    ret i32 %r89
}
