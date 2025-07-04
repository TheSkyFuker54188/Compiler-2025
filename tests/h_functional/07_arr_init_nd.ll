define i32 @main()
{
L1:  
    %r124 = alloca [2 x [3 x [4 x i32]]]
    %r123 = alloca [3 x i32]
    %r104 = alloca [5 x [3 x i32]]
    %r103 = alloca [5 x i32]
    %r69 = alloca [5 x [3 x i32]]
    %r33 = alloca [5 x [3 x i32]]
    %r2 = alloca [5 x [3 x i32]]
    %r1 = alloca [5 x [3 x i32]]
    %r0 = alloca [5 x [3 x i32]]
    %r3 = getelementptr [5 x [3 x i32]], ptr %r2, i32 0, i32 0
    store i32 1, ptr %r3
    %r5 = getelementptr [5 x [3 x i32]], ptr %r2, i32 1, i32 0
    store i32 2, ptr %r5
    %r7 = getelementptr [5 x [3 x i32]], ptr %r2, i32 2, i32 0
    store i32 3, ptr %r7
    %r9 = getelementptr [5 x [3 x i32]], ptr %r2, i32 3, i32 0
    store i32 4, ptr %r9
    %r11 = getelementptr [5 x [3 x i32]], ptr %r2, i32 4, i32 0
    store i32 5, ptr %r11
    %r13 = getelementptr [5 x [3 x i32]], ptr %r2, i32 5, i32 0
    store i32 6, ptr %r13
    %r15 = getelementptr [5 x [3 x i32]], ptr %r2, i32 6, i32 0
    store i32 7, ptr %r15
    %r17 = getelementptr [5 x [3 x i32]], ptr %r2, i32 7, i32 0
    store i32 8, ptr %r17
    %r19 = getelementptr [5 x [3 x i32]], ptr %r2, i32 8, i32 0
    store i32 9, ptr %r19
    %r21 = getelementptr [5 x [3 x i32]], ptr %r2, i32 9, i32 0
    store i32 10, ptr %r21
    %r23 = getelementptr [5 x [3 x i32]], ptr %r2, i32 10, i32 0
    store i32 11, ptr %r23
    %r25 = getelementptr [5 x [3 x i32]], ptr %r2, i32 11, i32 0
    store i32 12, ptr %r25
    %r27 = getelementptr [5 x [3 x i32]], ptr %r2, i32 12, i32 0
    store i32 13, ptr %r27
    %r29 = getelementptr [5 x [3 x i32]], ptr %r2, i32 13, i32 0
    store i32 14, ptr %r29
    %r31 = getelementptr [5 x [3 x i32]], ptr %r2, i32 14, i32 0
    store i32 15, ptr %r31
    %r34 = getelementptr [5 x [3 x i32]], ptr %r33, i32 0, i32 0
    %r36 = getelementptr [3 x i32], ptr %r34, i32 0, i32 0
    store i32 1, ptr %r36
    %r38 = getelementptr [3 x i32], ptr %r34, i32 0, i32 1
    store i32 2, ptr %r38
    %r40 = getelementptr [3 x i32], ptr %r34, i32 0, i32 2
    store i32 3, ptr %r40
    %r41 = getelementptr [5 x [3 x i32]], ptr %r33, i32 1, i32 0
    %r43 = getelementptr [3 x i32], ptr %r41, i32 0, i32 0
    store i32 4, ptr %r43
    %r45 = getelementptr [3 x i32], ptr %r41, i32 0, i32 1
    store i32 5, ptr %r45
    %r47 = getelementptr [3 x i32], ptr %r41, i32 0, i32 2
    store i32 6, ptr %r47
    %r48 = getelementptr [5 x [3 x i32]], ptr %r33, i32 2, i32 0
    %r50 = getelementptr [3 x i32], ptr %r48, i32 0, i32 0
    store i32 7, ptr %r50
    %r52 = getelementptr [3 x i32], ptr %r48, i32 0, i32 1
    store i32 8, ptr %r52
    %r54 = getelementptr [3 x i32], ptr %r48, i32 0, i32 2
    store i32 9, ptr %r54
    %r55 = getelementptr [5 x [3 x i32]], ptr %r33, i32 3, i32 0
    %r57 = getelementptr [3 x i32], ptr %r55, i32 0, i32 0
    store i32 10, ptr %r57
    %r59 = getelementptr [3 x i32], ptr %r55, i32 0, i32 1
    store i32 11, ptr %r59
    %r61 = getelementptr [3 x i32], ptr %r55, i32 0, i32 2
    store i32 12, ptr %r61
    %r62 = getelementptr [5 x [3 x i32]], ptr %r33, i32 4, i32 0
    %r64 = getelementptr [3 x i32], ptr %r62, i32 0, i32 0
    store i32 13, ptr %r64
    %r66 = getelementptr [3 x i32], ptr %r62, i32 0, i32 1
    store i32 14, ptr %r66
    %r68 = getelementptr [3 x i32], ptr %r62, i32 0, i32 2
    store i32 15, ptr %r68
    %r70 = getelementptr [5 x [3 x i32]], ptr %r69, i32 0, i32 0
    %r72 = getelementptr [3 x i32], ptr %r70, i32 0, i32 0
    store i32 1, ptr %r72
    %r74 = getelementptr [3 x i32], ptr %r70, i32 0, i32 1
    store i32 2, ptr %r74
    %r76 = getelementptr [3 x i32], ptr %r70, i32 0, i32 2
    store i32 3, ptr %r76
    %r77 = getelementptr [5 x [3 x i32]], ptr %r69, i32 1, i32 0
    %r79 = getelementptr [3 x i32], ptr %r77, i32 0, i32 0
    store i32 4, ptr %r79
    %r81 = getelementptr [3 x i32], ptr %r77, i32 0, i32 1
    store i32 5, ptr %r81
    %r83 = getelementptr [3 x i32], ptr %r77, i32 0, i32 2
    store i32 6, ptr %r83
    %r84 = getelementptr [5 x [3 x i32]], ptr %r69, i32 2, i32 0
    %r86 = getelementptr [3 x i32], ptr %r84, i32 0, i32 0
    store i32 7, ptr %r86
    %r88 = getelementptr [3 x i32], ptr %r84, i32 0, i32 1
    store i32 8, ptr %r88
    %r90 = getelementptr [3 x i32], ptr %r84, i32 0, i32 2
    store i32 9, ptr %r90
    %r91 = getelementptr [5 x [3 x i32]], ptr %r69, i32 3, i32 0
    store i32 10, ptr %r91
    %r93 = getelementptr [5 x [3 x i32]], ptr %r69, i32 4, i32 0
    store i32 11, ptr %r93
    %r95 = getelementptr [5 x [3 x i32]], ptr %r69, i32 5, i32 0
    store i32 12, ptr %r95
    %r97 = getelementptr [5 x [3 x i32]], ptr %r69, i32 6, i32 0
    store i32 13, ptr %r97
    %r99 = getelementptr [5 x [3 x i32]], ptr %r69, i32 7, i32 0
    store i32 14, ptr %r99
    %r101 = getelementptr [5 x [3 x i32]], ptr %r69, i32 8, i32 0
    store i32 15, ptr %r101
    %r105 = getelementptr [5 x [3 x i32]], ptr %r104, i32 0, i32 0
    store i32 1, ptr %r105
    %r107 = getelementptr [5 x [3 x i32]], ptr %r104, i32 1, i32 0
    store i32 2, ptr %r107
    %r109 = getelementptr [5 x [3 x i32]], ptr %r104, i32 2, i32 0
    store i32 3, ptr %r109
    %r111 = getelementptr [5 x [3 x i32]], ptr %r104, i32 3, i32 0
    %r113 = getelementptr [3 x i32], ptr %r111, i32 0, i32 0
    store i32 4, ptr %r113
    %r114 = getelementptr [5 x [3 x i32]], ptr %r104, i32 4, i32 0
    %r116 = getelementptr [3 x i32], ptr %r114, i32 0, i32 0
    store i32 7, ptr %r116
    %r117 = getelementptr [5 x [3 x i32]], ptr %r104, i32 5, i32 0
    store i32 10, ptr %r117
    %r119 = getelementptr [5 x [3 x i32]], ptr %r104, i32 6, i32 0
    store i32 11, ptr %r119
    %r121 = getelementptr [5 x [3 x i32]], ptr %r104, i32 7, i32 0
    store i32 12, ptr %r121
    %r125 = getelementptr [2 x [3 x [4 x i32]]], ptr %r124, i32 0, i32 0
    store i32 1, ptr %r125
    %r127 = getelementptr [2 x [3 x [4 x i32]]], ptr %r124, i32 1, i32 0
    store i32 2, ptr %r127
    %r129 = getelementptr [2 x [3 x [4 x i32]]], ptr %r124, i32 2, i32 0
    store i32 3, ptr %r129
    %r131 = getelementptr [2 x [3 x [4 x i32]]], ptr %r124, i32 3, i32 0
    store i32 4, ptr %r131
    %r133 = getelementptr [2 x [3 x [4 x i32]]], ptr %r124, i32 4, i32 0
    %r135 = getelementptr [3 x [4 x i32]], ptr %r133, i32 0, i32 0
    store i32 5, ptr %r135
    %r136 = getelementptr [2 x [3 x [4 x i32]]], ptr %r124, i32 5, i32 0
    ret i32 4
}
