define i32 @main()
{
L1:  
    %r54 = alloca [4 x [2 x i32]]
    %r39 = alloca [4 x [2 x i32]]
    %r18 = alloca [4 x [2 x i32]]
    %r1 = alloca [4 x [2 x i32]]
    %r0 = alloca [4 x [2 x i32]]
    %r2 = getelementptr [4 x [2 x i32]], ptr %r1, i32 0, i32 0
    store i32 1, ptr %r2
    %r4 = getelementptr [4 x [2 x i32]], ptr %r1, i32 1, i32 0
    store i32 2, ptr %r4
    %r6 = getelementptr [4 x [2 x i32]], ptr %r1, i32 2, i32 0
    store i32 3, ptr %r6
    %r8 = getelementptr [4 x [2 x i32]], ptr %r1, i32 3, i32 0
    store i32 4, ptr %r8
    %r10 = getelementptr [4 x [2 x i32]], ptr %r1, i32 4, i32 0
    store i32 5, ptr %r10
    %r12 = getelementptr [4 x [2 x i32]], ptr %r1, i32 5, i32 0
    store i32 6, ptr %r12
    %r14 = getelementptr [4 x [2 x i32]], ptr %r1, i32 6, i32 0
    store i32 7, ptr %r14
    %r16 = getelementptr [4 x [2 x i32]], ptr %r1, i32 7, i32 0
    store i32 8, ptr %r16
    %r19 = getelementptr [4 x [2 x i32]], ptr %r18, i32 0, i32 0
    %r21 = getelementptr [2 x i32], ptr %r19, i32 0, i32 0
    store i32 1, ptr %r21
    %r23 = getelementptr [2 x i32], ptr %r19, i32 0, i32 1
    store i32 2, ptr %r23
    %r24 = getelementptr [4 x [2 x i32]], ptr %r18, i32 1, i32 0
    %r26 = getelementptr [2 x i32], ptr %r24, i32 0, i32 0
    store i32 3, ptr %r26
    %r28 = getelementptr [2 x i32], ptr %r24, i32 0, i32 1
    store i32 4, ptr %r28
    %r29 = getelementptr [4 x [2 x i32]], ptr %r18, i32 2, i32 0
    %r31 = getelementptr [2 x i32], ptr %r29, i32 0, i32 0
    store i32 5, ptr %r31
    %r33 = getelementptr [2 x i32], ptr %r29, i32 0, i32 1
    store i32 6, ptr %r33
    %r34 = getelementptr [4 x [2 x i32]], ptr %r18, i32 3, i32 0
    %r36 = getelementptr [2 x i32], ptr %r34, i32 0, i32 0
    store i32 7, ptr %r36
    %r38 = getelementptr [2 x i32], ptr %r34, i32 0, i32 1
    store i32 8, ptr %r38
    %r40 = getelementptr [4 x [2 x i32]], ptr %r39, i32 0, i32 0
    store i32 1, ptr %r40
    %r42 = getelementptr [4 x [2 x i32]], ptr %r39, i32 1, i32 0
    store i32 2, ptr %r42
    %r44 = getelementptr [4 x [2 x i32]], ptr %r39, i32 2, i32 0
    %r46 = getelementptr [2 x i32], ptr %r44, i32 0, i32 0
    store i32 3, ptr %r46
    %r47 = getelementptr [4 x [2 x i32]], ptr %r39, i32 3, i32 0
    %r49 = getelementptr [2 x i32], ptr %r47, i32 0, i32 0
    store i32 5, ptr %r49
    %r50 = getelementptr [4 x [2 x i32]], ptr %r39, i32 4, i32 0
    store i32 7, ptr %r50
    %r52 = getelementptr [4 x [2 x i32]], ptr %r39, i32 5, i32 0
    store i32 8, ptr %r52
    %r55 = getelementptr [4 x [2 x i32]], ptr %r54, i32 0, i32 0
    %r58 = getelementptr [4 x [2 x i32]], ptr %r39, i32 0, i32 %r56, i32 %r57
    %r59 = getelementptr [2 x i32], ptr %r55, i32 0, i32 0
    store i32 %r58, ptr %r59
    %r62 = getelementptr [4 x [2 x i32]], ptr %r18, i32 0, i32 %r60, i32 %r61
    %r63 = getelementptr [2 x i32], ptr %r55, i32 0, i32 1
    store i32 %r62, ptr %r63
    %r64 = getelementptr [4 x [2 x i32]], ptr %r54, i32 1, i32 0
    %r66 = getelementptr [2 x i32], ptr %r64, i32 0, i32 0
    store i32 3, ptr %r66
    %r68 = getelementptr [2 x i32], ptr %r64, i32 0, i32 1
    store i32 4, ptr %r68
    %r69 = getelementptr [4 x [2 x i32]], ptr %r54, i32 2, i32 0
    %r71 = getelementptr [2 x i32], ptr %r69, i32 0, i32 0
    store i32 5, ptr %r71
    %r73 = getelementptr [2 x i32], ptr %r69, i32 0, i32 1
    store i32 6, ptr %r73
    %r74 = getelementptr [4 x [2 x i32]], ptr %r54, i32 3, i32 0
    %r76 = getelementptr [2 x i32], ptr %r74, i32 0, i32 0
    store i32 7, ptr %r76
    %r78 = getelementptr [2 x i32], ptr %r74, i32 0, i32 1
    store i32 8, ptr %r78
    %r81 = getelementptr [4 x [2 x i32]], ptr %r54, i32 0, i32 %r79, i32 %r80
    %r82 = load float, ptr %r81
    %r85 = getelementptr [4 x [2 x i32]], ptr %r54, i32 0, i32 %r83, i32 %r84
    %r86 = load float, ptr %r85
    %r87 = add i32 %r82,%r86
    %r88 = load float, ptr %r87
    %r91 = getelementptr [4 x [2 x i32]], ptr %r54, i32 0, i32 %r89, i32 %r90
    %r92 = load float, ptr %r91
    %r93 = add i32 %r88,%r92
    %r94 = load float, ptr %r93
    %r97 = getelementptr [4 x [2 x i32]], ptr %r0, i32 0, i32 %r95, i32 %r96
    %r98 = load float, ptr %r97
    %r99 = add i32 %r94,%r98
    ret i32 %r99
}
