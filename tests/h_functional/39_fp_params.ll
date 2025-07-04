@k = global i32 zeroinitializer
define void @params_f40(void %r0,void %r0,void %r2,void %r1,void %r4,void %r2,void %r6,void %r3,void %r8,void %r4,void %r10,void %r5,void %r12,void %r6,void %r14,void %r7,void %r16,void %r8,void %r18,void %r9,void %r20,void %r10,void %r22,void %r11,void %r24,void %r12,void %r26,void %r13,void %r28,void %r14,void %r30,void %r15,void %r32,void %r16,void %r34,void %r17,void %r36,void %r18,void %r38,void %r19)
{
L1:  
    %r44 = alloca [10 x void]
    %r1 = load void, ptr %r0
    %r2 = load void, ptr %r1
    %r3 = add i32 %r1,%r2
    %r4 = load void, ptr %r3
    %r3 = load void, ptr %r2
    %r4 = add i32 %r4,%r3
    %r5 = load void, ptr %r4
    %r4 = load void, ptr %r3
    %r5 = add i32 %r5,%r4
    %r6 = getelementptr [10 x void], ptr %r44, i32 0, i32 0
    store void %r5, ptr %r6
    %r5 = load void, ptr %r4
    %r6 = load void, ptr %r5
    %r7 = add i32 %r5,%r6
    %r8 = load void, ptr %r7
    %r7 = load void, ptr %r6
    %r8 = add i32 %r8,%r7
    %r9 = load void, ptr %r8
    %r8 = load void, ptr %r7
    %r9 = add i32 %r9,%r8
    %r10 = getelementptr [10 x void], ptr %r44, i32 0, i32 1
    store void %r9, ptr %r10
    %r9 = load void, ptr %r8
    %r10 = load void, ptr %r9
    %r11 = add i32 %r9,%r10
    %r12 = load void, ptr %r11
    %r11 = load void, ptr %r10
    %r12 = add i32 %r12,%r11
    %r13 = load void, ptr %r12
    %r12 = load void, ptr %r11
    %r13 = add i32 %r13,%r12
    %r14 = getelementptr [10 x void], ptr %r44, i32 0, i32 2
    store void %r13, ptr %r14
    %r13 = load void, ptr %r12
    %r14 = load void, ptr %r13
    %r15 = add i32 %r13,%r14
    %r16 = load void, ptr %r15
    %r15 = load void, ptr %r14
    %r16 = add i32 %r16,%r15
    %r17 = load void, ptr %r16
    %r16 = load void, ptr %r15
    %r17 = add i32 %r17,%r16
    %r18 = getelementptr [10 x void], ptr %r44, i32 0, i32 3
    store void %r17, ptr %r18
    %r17 = load void, ptr %r16
    %r18 = load void, ptr %r17
    %r19 = add i32 %r17,%r18
    %r20 = load void, ptr %r19
    %r19 = load void, ptr %r18
    %r20 = add i32 %r20,%r19
    %r21 = load void, ptr %r20
    %r20 = load void, ptr %r19
    %r21 = add i32 %r21,%r20
    %r22 = getelementptr [10 x void], ptr %r44, i32 0, i32 4
    store void %r21, ptr %r22
    %r21 = load void, ptr %r20
    %r22 = load void, ptr %r21
    %r23 = add i32 %r21,%r22
    %r24 = load void, ptr %r23
    %r23 = load void, ptr %r22
    %r24 = add i32 %r24,%r23
    %r25 = load void, ptr %r24
    %r24 = load void, ptr %r23
    %r25 = add i32 %r25,%r24
    %r26 = getelementptr [10 x void], ptr %r44, i32 0, i32 5
    store void %r25, ptr %r26
    %r25 = load void, ptr %r24
    %r26 = load void, ptr %r25
    %r27 = add i32 %r25,%r26
    %r28 = load void, ptr %r27
    %r27 = load void, ptr %r26
    %r28 = add i32 %r28,%r27
    %r29 = load void, ptr %r28
    %r28 = load void, ptr %r27
    %r29 = add i32 %r29,%r28
    %r30 = getelementptr [10 x void], ptr %r44, i32 0, i32 6
    store void %r29, ptr %r30
    %r29 = load void, ptr %r28
    %r30 = load void, ptr %r29
    %r31 = add i32 %r29,%r30
    %r32 = load void, ptr %r31
    %r31 = load void, ptr %r30
    %r32 = add i32 %r32,%r31
    %r33 = load void, ptr %r32
    %r32 = load void, ptr %r31
    %r33 = add i32 %r33,%r32
    %r34 = getelementptr [10 x void], ptr %r44, i32 0, i32 7
    store void %r33, ptr %r34
    %r33 = load void, ptr %r32
    %r34 = load void, ptr %r33
    %r35 = add i32 %r33,%r34
    %r36 = load void, ptr %r35
    %r35 = load void, ptr %r34
    %r36 = add i32 %r36,%r35
    %r37 = load void, ptr %r36
    %r36 = load void, ptr %r35
    %r37 = add i32 %r37,%r36
    %r38 = getelementptr [10 x void], ptr %r44, i32 0, i32 8
    store void %r37, ptr %r38
    %r37 = load void, ptr %r36
    %r38 = load void, ptr %r37
    %r39 = add i32 %r37,%r38
    %r40 = load void, ptr %r39
    %r39 = load void, ptr %r38
    %r40 = add i32 %r40,%r39
    %r41 = load float, ptr %r40
    %r40 = load void, ptr %r39
    %r41 = add i32 %r41,%r40
    %r42 = getelementptr [10 x void], ptr %r44, i32 0, i32 9
    store void 0, ptr %r42
    call void @putfarray(i32 %r43,void %r44)
    %r46 = load i32, ptr @k
    %r47 = getelementptr [10 x void], ptr %r44, i32 0, i32 %r46
    ret void %r47
    br label %L2
    %r1 = load void, ptr %r0
    %r2 = load void, ptr %r1
    %r3 = add i32 %r1,%r2
    %r4 = load void, ptr %r3
    %r3 = load void, ptr %r2
    %r4 = add i32 %r4,%r3
    call void @params_f40(void %r1,void %r2,void %r3,void %r4,void %r5,void %r6,void %r7,void %r8,void %r9,void %r10,void %r11,void %r12,void %r13,void %r14,void %r15,void %r16,void %r17,void %r18,void %r19,void %r20,void %r21,void %r22,void %r23,void %r24,void %r25,void %r26,void %r27,void %r28,void %r29,void %r30,void %r31,void %r32,void %r33,void %r34,void %r35,void %r36,void %r37,void %r38,void %r39,void %r4)
    ret void %r5
    br label %L2
L2:  
L3:  
}
define void @params_f40_i24(i32 %r0,i32 %r6,i32 %r2,void %r7,i32 %r4,i32 %r8,i32 %r6,void %r9,void %r8,void %r10,i32 %r10,void %r11,void %r12,i32 %r12,void %r14,i32 %r13,void %r16,void %r14,void %r18,void %r15,void %r20,void %r16,i32 %r22,void %r17,i32 %r24,i32 %r18,void %r26,void %r19,void %r28,void %r20,void %r30,i32 %r21,void %r32,i32 %r22,void %r34,void %r23,void %r36,void %r24,i32 %r38,i32 %r25,void %r40,void %r26,void %r42,i32 %r27,void %r44,i32 %r28,i32 %r46,void %r29,void %r48,void %r30,void %r50,i32 %r31,i32 %r52,i32 %r32,void %r54,void %r33,void %r56,void %r34,void %r58,void %r35,i32 %r60,void %r36,i32 %r62,void %r37)
{
L1:  
    %r44 = alloca i32
    %r42 = alloca [8 x i32]
    %r11 = alloca [10 x void]
    %r7 = load i32, ptr %r6
    %r10 = icmp ne i32 %r7,%r8
    br i1 %r10, label %L3, label %L4
    %r49 = load void, ptr %r48
    %r25 = load void, ptr %r24
    %r26 = add i32 %r49,%r25
    %r27 = load void, ptr %r26
    %r68 = load void, ptr %r67
    %r69 = add i32 %r27,%r68
    %r70 = load void, ptr %r69
    %r18 = load void, ptr %r17
    %r19 = add i32 %r70,%r18
    %r20 = getelementptr [10 x void], ptr %r11, i32 0, i32 0
    store void %r19, ptr %r20
    %r10 = load void, ptr %r9
    %r43 = load void, ptr %r42
    %r44 = add i32 %r10,%r43
    %r45 = load i32, ptr %r44
    %r28 = load void, ptr %r27
    %r29 = add i32 %r45,%r28
    %r30 = load void, ptr %r29
    %r16 = load void, ptr %r15
    %r17 = add i32 %r30,%r16
    %r18 = getelementptr [10 x void], ptr %r11, i32 0, i32 1
    store void %r17, ptr %r18
    %r14 = load void, ptr %r13
    %r36 = load void, ptr %r35
    %r37 = add i32 %r14,%r36
    %r38 = load i32, ptr %r37
    %r48 = load void, ptr %r47
    %r49 = add i32 %r38,%r48
    %r50 = load i32, ptr %r49
    %r26 = load void, ptr %r25
    %r27 = add i32 %r50,%r26
    %r28 = getelementptr [10 x void], ptr %r11, i32 0, i32 2
    store void %r27, ptr %r28
    %r24 = load void, ptr %r23
    %r56 = load void, ptr %r55
    %r57 = add i32 %r24,%r56
    %r58 = load i32, ptr %r57
    %r47 = load void, ptr %r46
    %r48 = add i32 %r58,%r47
    %r49 = load void, ptr %r48
    %r15 = load void, ptr %r14
    %r16 = add i32 %r49,%r15
    %r17 = getelementptr [10 x void], ptr %r11, i32 0, i32 3
    store void %r16, ptr %r17
    %r42 = load void, ptr %r41
    %r66 = load void, ptr %r65
    %r67 = add i32 %r42,%r66
    %r68 = load void, ptr %r67
    %r61 = load void, ptr %r60
    %r62 = add i32 %r68,%r61
    %r63 = load void, ptr %r62
    %r62 = load void, ptr %r61
    %r63 = add i32 %r63,%r62
    %r64 = getelementptr [10 x void], ptr %r11, i32 0, i32 4
    store void %r63, ptr %r64
    %r33 = load void, ptr %r32
    %r41 = load void, ptr %r40
    %r42 = add i32 %r33,%r41
    %r43 = load void, ptr %r42
    %r63 = load void, ptr %r62
    %r64 = add i32 %r43,%r63
    %r65 = load void, ptr %r64
    %r35 = load void, ptr %r34
    %r36 = add i32 %r65,%r35
    %r37 = getelementptr [10 x void], ptr %r11, i32 0, i32 5
    store void %r36, ptr %r37
    %r55 = load void, ptr %r54
    %r37 = load void, ptr %r36
    %r38 = add i32 %r55,%r37
    %r39 = load void, ptr %r38
    %r64 = load void, ptr %r63
    %r65 = add i32 %r39,%r64
    %r66 = load void, ptr %r65
    %r54 = load void, ptr %r53
    %r55 = add i32 %r66,%r54
    %r56 = getelementptr [10 x void], ptr %r11, i32 0, i32 6
    store void %r55, ptr %r56
    %r19 = load void, ptr %r18
    %r57 = load void, ptr %r56
    %r58 = add i32 %r19,%r57
    %r59 = load i32, ptr %r58
    %r23 = load void, ptr %r22
    %r24 = add i32 %r59,%r23
    %r25 = load void, ptr %r24
    %r51 = load void, ptr %r50
    %r52 = add i32 %r25,%r51
    %r53 = getelementptr [10 x void], ptr %r11, i32 0, i32 7
    store void %r52, ptr %r53
    %r30 = load void, ptr %r29
    %r34 = load void, ptr %r33
    %r35 = add i32 %r30,%r34
    %r36 = load void, ptr %r35
    %r44 = load void, ptr %r43
    %r45 = add i32 %r36,%r44
    %r46 = load i32, ptr %r45
    %r70 = load void, ptr %r69
    %r71 = add i32 %r46,%r70
    %r72 = getelementptr [10 x void], ptr %r11, i32 0, i32 8
    store void %r71, ptr %r72
    %r65 = load void, ptr %r64
    %r21 = load void, ptr %r20
    %r22 = add i32 %r65,%r21
    %r23 = load void, ptr %r22
    %r27 = load void, ptr %r26
    %r28 = add i32 %r23,%r27
    %r29 = load i32, ptr %r28
    %r39 = load void, ptr %r38
    %r40 = add i32 %r29,%r39
    %r41 = getelementptr [10 x void], ptr %r11, i32 0, i32 9
    store void %r40, ptr %r41
    %r20 = load i32, ptr %r19
    %r11 = load i32, ptr %r10
    %r12 = add i32 %r20,%r11
    %r13 = load i32, ptr %r12
    %r8 = load i32, ptr %r7
    %r9 = add i32 %r13,%r8
    %r10 = getelementptr [8 x i32], ptr %r42, i32 0, i32 0
    store i32 %r9, ptr %r10
    %r58 = load i32, ptr %r57
    %r12 = load void, ptr %r11
    %r13 = add i32 %r58,%r12
    %r14 = load void, ptr %r13
    %r13 = load i32, ptr %r12
    %r14 = add i32 %r14,%r13
    %r15 = getelementptr [8 x i32], ptr %r42, i32 0, i32 1
    store i32 %r14, ptr %r15
    %r29 = load i32, ptr %r28
    %r30 = add i32 %r8,%r29
    %r31 = load i32, ptr %r30
    %r38 = load i32, ptr %r37
    %r39 = add i32 %r31,%r38
    %r40 = getelementptr [8 x i32], ptr %r42, i32 0, i32 2
    store i32 %r39, ptr %r40
    %r46 = load i32, ptr %r45
    %r31 = load i32, ptr %r30
    %r32 = add i32 %r46,%r31
    %r33 = load void, ptr %r32
    %r52 = load i32, ptr %r51
    %r53 = add i32 %r33,%r52
    %r54 = getelementptr [8 x i32], ptr %r42, i32 0, i32 3
    store i32 %r53, ptr %r54
    %r50 = load i32, ptr %r49
    %r32 = load i32, ptr %r31
    %r33 = add i32 %r50,%r32
    %r34 = load void, ptr %r33
    %r69 = load i32, ptr %r68
    %r70 = add i32 %r34,%r69
    %r71 = getelementptr [8 x i32], ptr %r42, i32 0, i32 4
    store i32 %r70, ptr %r71
    %r67 = load i32, ptr %r66
    %r53 = load i32, ptr %r52
    %r54 = add i32 %r67,%r53
    %r55 = load void, ptr %r54
    %r40 = load i32, ptr %r39
    %r41 = add i32 %r55,%r40
    %r42 = getelementptr [8 x i32], ptr %r42, i32 0, i32 5
    store i32 %r41, ptr %r42
    %r45 = load i32, ptr %r44
    %r22 = load i32, ptr %r21
    %r23 = add i32 %r45,%r22
    %r24 = load void, ptr %r23
    %r60 = load i32, ptr %r59
    %r61 = add i32 %r24,%r60
    %r62 = getelementptr [8 x i32], ptr %r42, i32 0, i32 6
    store i32 %r61, ptr %r62
    %r59 = load i32, ptr %r58
    %r17 = load i32, ptr %r16
    %r18 = add i32 %r59,%r17
    %r19 = load void, ptr %r18
    %r7 = load i32, ptr %r6
    %r8 = add i32 %r19,%r7
    %r9 = getelementptr [8 x i32], ptr %r42, i32 0, i32 7
    store i32 0, ptr %r9
    call void @putfarray(i32 %r10,void %r11)
    call void @putarray(i32 %r13,i32 %r42)
    store i32 0, ptr %r44
    br label %L6
    %r45 = load i32, ptr %r44
    %r48 = icmp slt i32 %r45,%r46
    br i1 %r48, label %L7, label %L8
    %r45 = getelementptr [8 x i32], ptr %r42, i32 0, i32 %r44
    %r46 = load i32, ptr %r45
    %r45 = getelementptr [10 x void], ptr %r11, i32 0, i32 %r44
    %r46 = load i32, ptr %r45
    %r47 = sub i32 %r46,%r46
    %r45 = getelementptr [8 x i32], ptr %r42, i32 0, i32 %r44
    store i32 %r47, ptr %r45
    %r45 = load i32, ptr %r44
    %r48 = add i32 %r45,%r46
    store i32 %r48, ptr %r44
    br label %L7
L4:  
L5:  
L6:  
L7:  
L8:  
L9:  
    %r45 = load i32, ptr @k
    %r46 = getelementptr [8 x i32], ptr %r42, i32 0, i32 %r45
    ret void 8
    br label %L5
    call void @params_f40_i24(i32 %r10,i32 %r7,i32 %r8,void %r9,i32 %r10,void %r11,i32 %r12,i32 %r13,void %r14,void %r15,i32 %r16,void %r17,void %r18,i32 %r19,void %r20,i32 %r21,void %r22,void %r23,void %r24,void %r25,void %r26,void %r27,i32 %r28,void %r29,i32 %r30,i32 %r31,void %r32,void %r33,void %r34,void %r35,void %r36,i32 %r37,void %r38,i32 %r39,void %r40,void %r41,i32 %r42,void %r43,i32 %r44,i32 %r45,i32 %r46,void %r47,void %r48,i32 %r49,void %r50,i32 %r51,i32 %r52,void %r53,void %r54,void %r55,void %r56,i32 %r57,i32 %r58,i32 %r59,void %r60,void %r61,void %r62,void %r63,void %r64,void %r65,i32 %r66,void %r67,i32 %r68,void %r69)
    ret void %r70
    br label %L5
}
define void @params_fa40(void %r0,void %r71,void %r2,void %r72,void %r4,void %r73,void %r6,void %r74,void %r8,void %r75,void %r10,void %r76,void %r12,void %r77,void %r14,void %r78,void %r16,void %r79,void %r18,void %r80,void %r20,void %r81,void %r22,void %r82,void %r24,void %r83,void %r26,void %r84,void %r28,void %r85,void %r30,void %r86,void %r32,void %r87,void %r34,void %r88,void %r36,void %r89,void %r38,void %r90)
{
L1:  
    %r111 = alloca [10 x void]
    %r112 = load i32, ptr @k
    %r113 = getelementptr [0 x void], ptr %r71, i32 0, i32 %r112
    %r114 = load float, ptr %r113
    %r115 = load i32, ptr @k
    %r116 = getelementptr [0 x void], ptr %r72, i32 0, i32 %r115
    %r117 = load float, ptr %r116
    %r118 = add i32 %r114,%r117
    %r119 = load float, ptr %r118
    %r120 = load i32, ptr @k
    %r121 = getelementptr [0 x void], ptr %r73, i32 0, i32 %r120
    %r122 = load float, ptr %r121
    %r123 = add i32 %r119,%r122
    %r124 = load float, ptr %r123
    %r125 = load i32, ptr @k
    %r126 = getelementptr [0 x void], ptr %r74, i32 0, i32 %r125
    %r127 = load float, ptr %r126
    %r128 = add i32 %r124,%r127
    %r129 = getelementptr [10 x void], ptr %r111, i32 0, i32 0
    store void %r128, ptr %r129
    %r130 = load i32, ptr @k
    %r131 = getelementptr [0 x void], ptr %r75, i32 0, i32 %r130
    %r132 = load float, ptr %r131
    %r133 = load i32, ptr @k
    %r134 = getelementptr [0 x void], ptr %r76, i32 0, i32 %r133
    %r135 = load float, ptr %r134
    %r136 = add i32 %r132,%r135
    %r137 = load float, ptr %r136
    %r138 = load i32, ptr @k
    %r139 = getelementptr [0 x void], ptr %r77, i32 0, i32 %r138
    %r140 = load float, ptr %r139
    %r141 = add i32 %r137,%r140
    %r142 = load float, ptr %r141
    %r143 = load i32, ptr @k
    %r144 = getelementptr [0 x void], ptr %r78, i32 0, i32 %r143
    %r145 = load float, ptr %r144
    %r146 = add i32 %r142,%r145
    %r147 = getelementptr [10 x void], ptr %r111, i32 0, i32 1
    store void %r146, ptr %r147
    %r148 = load i32, ptr @k
    %r149 = getelementptr [0 x void], ptr %r79, i32 0, i32 %r148
    %r150 = load float, ptr %r149
    %r151 = load i32, ptr @k
    %r152 = getelementptr [0 x void], ptr %r80, i32 0, i32 %r151
    %r153 = load float, ptr %r152
    %r154 = add i32 %r150,%r153
    %r155 = load float, ptr %r154
    %r156 = load i32, ptr @k
    %r157 = getelementptr [0 x void], ptr %r81, i32 0, i32 %r156
    %r158 = load float, ptr %r157
    %r159 = add i32 %r155,%r158
    %r160 = load float, ptr %r159
    %r161 = load i32, ptr @k
    %r162 = getelementptr [0 x void], ptr %r82, i32 0, i32 %r161
    %r163 = load float, ptr %r162
    %r164 = add i32 %r160,%r163
    %r165 = getelementptr [10 x void], ptr %r111, i32 0, i32 2
    store void %r164, ptr %r165
    %r166 = load i32, ptr @k
    %r167 = getelementptr [0 x void], ptr %r83, i32 0, i32 %r166
    %r168 = load float, ptr %r167
    %r169 = load i32, ptr @k
    %r170 = getelementptr [0 x void], ptr %r84, i32 0, i32 %r169
    %r171 = load float, ptr %r170
    %r172 = add i32 %r168,%r171
    %r173 = load float, ptr %r172
    %r174 = load i32, ptr @k
    %r175 = getelementptr [0 x void], ptr %r85, i32 0, i32 %r174
    %r176 = load float, ptr %r175
    %r177 = add i32 %r173,%r176
    %r178 = load float, ptr %r177
    %r179 = load i32, ptr @k
    %r180 = getelementptr [0 x void], ptr %r86, i32 0, i32 %r179
    %r181 = load float, ptr %r180
    %r182 = add i32 %r178,%r181
    %r183 = getelementptr [10 x void], ptr %r111, i32 0, i32 3
    store void %r182, ptr %r183
    %r184 = load i32, ptr @k
    %r185 = getelementptr [0 x void], ptr %r87, i32 0, i32 %r184
    %r186 = load float, ptr %r185
    %r187 = load i32, ptr @k
    %r188 = getelementptr [0 x void], ptr %r88, i32 0, i32 %r187
    %r189 = load float, ptr %r188
    %r190 = add i32 %r186,%r189
    %r191 = load float, ptr %r190
    %r192 = load i32, ptr @k
    %r193 = getelementptr [0 x void], ptr %r89, i32 0, i32 %r192
    %r194 = load float, ptr %r193
    %r195 = add i32 %r191,%r194
    %r196 = load float, ptr %r195
    %r197 = load i32, ptr @k
    %r198 = getelementptr [0 x void], ptr %r90, i32 0, i32 %r197
    %r199 = load float, ptr %r198
    %r200 = add i32 %r196,%r199
    %r201 = getelementptr [10 x void], ptr %r111, i32 0, i32 4
    store void %r200, ptr %r201
    %r202 = load i32, ptr @k
    %r203 = getelementptr [0 x void], ptr %r91, i32 0, i32 %r202
    %r204 = load float, ptr %r203
    %r205 = load i32, ptr @k
    %r206 = getelementptr [0 x void], ptr %r92, i32 0, i32 %r205
    %r207 = load float, ptr %r206
    %r208 = add i32 %r204,%r207
    %r209 = load float, ptr %r208
    %r210 = load i32, ptr @k
    %r211 = getelementptr [0 x void], ptr %r93, i32 0, i32 %r210
    %r212 = load float, ptr %r211
    %r213 = add i32 %r209,%r212
    %r214 = load float, ptr %r213
    %r215 = load i32, ptr @k
    %r216 = getelementptr [0 x void], ptr %r94, i32 0, i32 %r215
    %r217 = load float, ptr %r216
    %r218 = add i32 %r214,%r217
    %r219 = getelementptr [10 x void], ptr %r111, i32 0, i32 5
    store void %r218, ptr %r219
    %r220 = load i32, ptr @k
    %r221 = getelementptr [0 x void], ptr %r95, i32 0, i32 %r220
    %r222 = load float, ptr %r221
    %r223 = load i32, ptr @k
    %r224 = getelementptr [0 x void], ptr %r96, i32 0, i32 %r223
    %r225 = load float, ptr %r224
    %r226 = add i32 %r222,%r225
    %r227 = load float, ptr %r226
    %r228 = load i32, ptr @k
    %r229 = getelementptr [0 x void], ptr %r97, i32 0, i32 %r228
    %r230 = load float, ptr %r229
    %r231 = add i32 %r227,%r230
    %r232 = load float, ptr %r231
    %r233 = load i32, ptr @k
    %r234 = getelementptr [0 x void], ptr %r98, i32 0, i32 %r233
    %r235 = load float, ptr %r234
    %r236 = add i32 %r232,%r235
    %r237 = getelementptr [10 x void], ptr %r111, i32 0, i32 6
    store void %r236, ptr %r237
    %r238 = load i32, ptr @k
    %r239 = getelementptr [0 x void], ptr %r99, i32 0, i32 %r238
    %r240 = load float, ptr %r239
    %r241 = load i32, ptr @k
    %r242 = getelementptr [0 x void], ptr %r100, i32 0, i32 %r241
    %r243 = load float, ptr %r242
    %r244 = add i32 %r240,%r243
    %r245 = load float, ptr %r244
    %r246 = load i32, ptr @k
    %r247 = getelementptr [0 x void], ptr %r101, i32 0, i32 %r246
    %r248 = load float, ptr %r247
    %r249 = add i32 %r245,%r248
    %r250 = load float, ptr %r249
    %r251 = load i32, ptr @k
    %r252 = getelementptr [0 x void], ptr %r102, i32 0, i32 %r251
    %r253 = load float, ptr %r252
    %r254 = add i32 %r250,%r253
    %r255 = getelementptr [10 x void], ptr %r111, i32 0, i32 7
    store void %r254, ptr %r255
    %r256 = load i32, ptr @k
    %r257 = getelementptr [0 x void], ptr %r103, i32 0, i32 %r256
    %r258 = load float, ptr %r257
    %r259 = load i32, ptr @k
    %r260 = getelementptr [0 x void], ptr %r104, i32 0, i32 %r259
    %r261 = load float, ptr %r260
    %r262 = add i32 %r258,%r261
    %r263 = load float, ptr %r262
    %r264 = load i32, ptr @k
    %r265 = getelementptr [0 x void], ptr %r105, i32 0, i32 %r264
    %r266 = load float, ptr %r265
    %r267 = add i32 %r263,%r266
    %r268 = load float, ptr %r267
    %r269 = load i32, ptr @k
    %r270 = getelementptr [0 x void], ptr %r106, i32 0, i32 %r269
    %r271 = load float, ptr %r270
    %r272 = add i32 %r268,%r271
    %r273 = getelementptr [10 x void], ptr %r111, i32 0, i32 8
    store void %r272, ptr %r273
    %r274 = load i32, ptr @k
    %r275 = getelementptr [0 x void], ptr %r107, i32 0, i32 %r274
    %r276 = load float, ptr %r275
    %r277 = load i32, ptr @k
    %r278 = getelementptr [0 x void], ptr %r108, i32 0, i32 %r277
    %r279 = load float, ptr %r278
    %r280 = add i32 %r276,%r279
    %r281 = load float, ptr %r280
    %r282 = load i32, ptr @k
    %r283 = getelementptr [0 x void], ptr %r109, i32 0, i32 %r282
    %r284 = load float, ptr %r283
    %r285 = add i32 %r281,%r284
    %r286 = load float, ptr %r285
    %r287 = load i32, ptr @k
    %r288 = getelementptr [0 x void], ptr %r110, i32 0, i32 %r287
    %r289 = load float, ptr %r288
    %r290 = add i32 %r286,%r289
    %r291 = getelementptr [10 x void], ptr %r111, i32 0, i32 9
    store void %r290, ptr %r291
    %r292 = load i32, ptr @k
    %r293 = getelementptr [0 x void], ptr %r110, i32 0, i32 %r292
    %r294 = load float, ptr %r293
    %r297 = icmp ne i32 %r294,%r295
    %r298 = load float, ptr %r297
    %r301 = icmp ne i32 %r298,%r299
    %r302 = load float, ptr %r301
    %r304 = load void, ptr %r303
    %r305 = icmp ne i32 %r302,%r304
    %r306 = load float, ptr %r305
    %r308 = load void, ptr %r307
    %r309 = icmp ne i32 %r306,%r308
    br i1 %r309, label %L9, label %L10
    call void @putfarray(i32 %r310,void %r111)
    %r113 = load i32, ptr @k
    %r114 = getelementptr [10 x void], ptr %r111, i32 0, i32 %r113
    ret void %r114
    br label %L11
    call void @params_fa40(void %r72,void %r73,void %r74,void %r75,void %r76,void %r77,void %r78,void %r79,void %r80,void %r81,void %r82,void %r83,void %r84,void %r85,void %r86,void %r87,void %r88,void %r89,void %r90,void %r91,void %r92,void %r93,void %r94,void %r95,void %r96,void %r97,void %r98,void %r99,void %r100,void %r101,void %r102,void %r103,void %r104,void %r105,void %r106,void %r107,void %r108,void %r109,void %r110,void %r111)
    ret void %r112
    br label %L11
L10:  
L11:  
L12:  
}
define i32 @params_mix(void %r0,i32 %r113,i32 %r2,void %r114,void %r4,i32 %r115,void %r6,void %r116,void %r8,i32 %r117,i32 %r10,i32 %r118,void %r12,i32 %r119,i32 %r14,i32 %r120,void %r16,void %r121,void %r18,void %r122,void %r20,void %r123,i32 %r22,void %r124,void %r24,void %r125,i32 %r26,void %r126,i32 %r28,i32 %r127,void %r30,void %r128,void %r32,i32 %r129,i32 %r34,void %r130,void %r36,void %r131,void %r38,i32 %r132,i32 %r40,i32 %r133,i32 %r42,void %r134,void %r44,i32 %r135,i32 %r46,void %r136,i32 %r48,i32 %r137,i32 %r50,void %r138,void %r52,void %r139,i32 %r54,i32 %r140,void %r56,void %r141,i32 %r58,void %r142,void %r60,void %r143,void %r62,i32 %r144)
{
L1:  
    %r181 = alloca i32
    %r179 = alloca [10 x i32]
    %r177 = alloca [10 x void]
    %r114 = load void, ptr %r113
    %r115 = load i32, ptr @k
    %r116 = getelementptr [0 x void], ptr %r116, i32 0, i32 %r115
    %r117 = load void, ptr %r116
    %r118 = add i32 %r114,%r117
    %r119 = load i32, ptr %r118
    %r118 = load void, ptr %r117
    %r119 = add i32 %r119,%r118
    %r120 = load void, ptr %r119
    %r120 = load void, ptr %r119
    %r121 = add i32 %r120,%r120
    %r122 = getelementptr [10 x void], ptr %r177, i32 0, i32 0
    store void %r121, ptr %r122
    %r121 = load void, ptr %r120
    %r122 = load i32, ptr @k
    %r123 = getelementptr [0 x void], ptr %r121, i32 0, i32 %r122
    %r124 = load i32, ptr %r123
    %r125 = add i32 %r121,%r124
    %r126 = load void, ptr %r125
    %r127 = load i32, ptr @k
    %r128 = getelementptr [0 x void], ptr %r125, i32 0, i32 %r127
    %r129 = load i32, ptr %r128
    %r130 = add i32 %r126,%r129
    %r131 = load void, ptr %r130
    %r132 = load i32, ptr @k
    %r133 = getelementptr [0 x void], ptr %r129, i32 0, i32 %r132
    %r134 = load void, ptr %r133
    %r135 = add i32 %r131,%r134
    %r136 = getelementptr [10 x void], ptr %r177, i32 0, i32 1
    store void %r135, ptr %r136
    %r137 = load i32, ptr @k
    %r138 = getelementptr [0 x void], ptr %r130, i32 0, i32 %r137
    %r139 = load void, ptr %r138
    %r132 = load void, ptr %r131
    %r133 = add i32 %r139,%r132
    %r134 = load void, ptr %r133
    %r133 = load i32, ptr %r132
    %r134 = add i32 %r134,%r133
    %r135 = load void, ptr %r134
    %r134 = load void, ptr %r133
    %r135 = add i32 %r135,%r134
    %r136 = getelementptr [10 x void], ptr %r177, i32 0, i32 2
    store void %r135, ptr %r136
    %r137 = load i32, ptr @k
    %r138 = getelementptr [0 x void], ptr %r134, i32 0, i32 %r137
    %r139 = load void, ptr %r138
    %r137 = load void, ptr %r136
    %r138 = add i32 %r139,%r137
    %r139 = load void, ptr %r138
    %r138 = load i32, ptr %r137
    %r139 = add i32 %r139,%r138
    %r140 = load i32, ptr %r139
    %r139 = load void, ptr %r138
    %r140 = add i32 %r140,%r139
    %r141 = getelementptr [10 x void], ptr %r177, i32 0, i32 3
    store void %r140, ptr %r141
    %r142 = load i32, ptr @k
    %r143 = getelementptr [0 x void], ptr %r140, i32 0, i32 %r142
    %r144 = load void, ptr %r143
    %r145 = load i32, ptr @k
    %r146 = getelementptr [0 x void], ptr %r143, i32 0, i32 %r145
    %r147 = load i32, ptr %r146
    %r148 = add i32 %r144,%r147
    %r149 = load void, ptr %r148
    %r145 = load void, ptr %r144
    %r146 = add i32 %r149,%r145
    %r147 = load i32, ptr %r146
    %r146 = load i32, ptr %r145
    %r147 = add i32 %r147,%r146
    %r148 = getelementptr [10 x void], ptr %r177, i32 0, i32 4
    store void %r147, ptr %r148
    %r149 = load i32, ptr @k
    %r150 = getelementptr [0 x void], ptr %r148, i32 0, i32 %r149
    %r151 = load void, ptr %r150
    %r152 = load i32, ptr @k
    %r153 = getelementptr i32, ptr %r149, i32 0, i32 %r152
    %r154 = load i32, ptr %r153
    %r155 = add i32 %r151,%r154
    %r156 = load i32, ptr %r155
    %r151 = load void, ptr %r150
    %r152 = add i32 %r156,%r151
    %r153 = load i32, ptr %r152
    %r152 = load void, ptr %r151
    %r153 = add i32 %r153,%r152
    %r154 = getelementptr [10 x void], ptr %r177, i32 0, i32 5
    store void %r153, ptr %r154
    %r157 = load void, ptr %r156
    %r158 = load void, ptr %r157
    %r159 = add i32 %r157,%r158
    %r160 = load i32, ptr %r159
    %r161 = load i32, ptr @k
    %r162 = getelementptr [0 x void], ptr %r160, i32 0, i32 %r161
    %r163 = load i32, ptr %r162
    %r164 = add i32 %r160,%r163
    %r165 = load void, ptr %r164
    %r165 = load void, ptr %r164
    %r166 = add i32 %r165,%r165
    %r167 = getelementptr [10 x void], ptr %r177, i32 0, i32 6
    store void %r166, ptr %r167
    %r166 = load void, ptr %r165
    %r167 = load i32, ptr @k
    %r168 = getelementptr [0 x void], ptr %r166, i32 0, i32 %r167
    %r169 = load i32, ptr %r168
    %r170 = add i32 %r166,%r169
    %r171 = load void, ptr %r170
    %r172 = load i32, ptr @k
    %r173 = getelementptr [0 x void], ptr %r169, i32 0, i32 %r172
    %r174 = load void, ptr %r173
    %r175 = add i32 %r171,%r174
    %r176 = load void, ptr %r175
    %r171 = load void, ptr %r170
    %r172 = add i32 %r176,%r171
    %r173 = getelementptr [10 x void], ptr %r177, i32 0, i32 7
    store void %r172, ptr %r173
    %r173 = load i32, ptr %r172
    %r174 = load i32, ptr @k
    %r175 = getelementptr [0 x void], ptr %r173, i32 0, i32 %r174
    %r176 = load void, ptr %r175
    %r177 = add i32 %r173,%r176
    %r178 = load void, ptr %r177
    %r179 = load i32, ptr @k
    %r180 = getelementptr i32, ptr %r174, i32 0, i32 %r179
    %r181 = load float, ptr %r180
    %r182 = add i32 %r178,%r181
    %r183 = load float, ptr %r182
    %r176 = load void, ptr %r175
    %r177 = add i32 %r183,%r176
    %r178 = getelementptr [10 x void], ptr %r177, i32 0, i32 8
    store void %r177, ptr %r178
    %r180 = load i32, ptr @k
    %r181 = getelementptr [0 x i32], ptr %r114, i32 0, i32 %r180
    %r182 = load float, ptr %r181
    %r116 = load i32, ptr %r115
    %r117 = add i32 %r182,%r116
    %r118 = load void, ptr %r117
    %r119 = load i32, ptr %r118
    %r120 = add i32 %r118,%r119
    %r121 = getelementptr [10 x i32], ptr %r179, i32 0, i32 0
    store i32 %r120, ptr %r121
    %r122 = load i32, ptr @k
    %r123 = getelementptr i32, ptr %r122, i32 0, i32 %r122
    %r124 = load i32, ptr %r123
    %r124 = load i32, ptr %r123
    %r125 = add i32 %r124,%r124
    %r126 = load void, ptr %r125
    %r125 = load i32, ptr %r124
    %r126 = add i32 %r126,%r125
    %r127 = getelementptr [10 x i32], ptr %r179, i32 0, i32 1
    store i32 %r126, ptr %r127
    %r128 = load i32, ptr @k
    %r129 = getelementptr [0 x i32], ptr %r126, i32 0, i32 %r128
    %r130 = load void, ptr %r129
    %r131 = load i32, ptr @k
    %r132 = getelementptr i32, ptr %r127, i32 0, i32 %r131
    %r133 = load i32, ptr %r132
    %r134 = add i32 %r130,%r133
    %r135 = load void, ptr %r134
    %r129 = load i32, ptr %r128
    %r130 = add i32 %r135,%r129
    %r131 = getelementptr [10 x i32], ptr %r179, i32 0, i32 2
    store i32 %r130, ptr %r131
    %r136 = load i32, ptr %r135
    %r137 = load i32, ptr @k
    %r138 = getelementptr [0 x i32], ptr %r139, i32 0, i32 %r137
    %r139 = load void, ptr %r138
    %r140 = add i32 %r136,%r139
    %r141 = load void, ptr %r140
    %r142 = load i32, ptr @k
    %r143 = getelementptr [0 x i32], ptr %r141, i32 0, i32 %r142
    %r144 = load void, ptr %r143
    %r145 = add i32 %r141,%r144
    %r146 = getelementptr [10 x i32], ptr %r179, i32 0, i32 3
    store i32 %r145, ptr %r146
    %r147 = load i32, ptr @k
    %r148 = getelementptr i32, ptr %r142, i32 0, i32 %r147
    %r149 = load void, ptr %r148
    %r150 = load i32, ptr @k
    %r151 = getelementptr [0 x i32], ptr %r146, i32 0, i32 %r150
    %r152 = load void, ptr %r151
    %r153 = add i32 %r149,%r152
    %r154 = load i32, ptr %r153
    %r148 = load i32, ptr %r147
    %r149 = add i32 %r154,%r148
    %r150 = getelementptr [10 x i32], ptr %r179, i32 0, i32 4
    store i32 %r149, ptr %r150
    %r151 = load i32, ptr @k
    %r152 = getelementptr i32, ptr %r152, i32 0, i32 %r151
    %r153 = load i32, ptr %r152
    %r154 = load i32, ptr @k
    %r155 = getelementptr [0 x i32], ptr %r153, i32 0, i32 %r154
    %r156 = load i32, ptr %r155
    %r157 = add i32 %r153,%r156
    %r158 = load void, ptr %r157
    %r155 = load i32, ptr %r154
    %r156 = add i32 %r158,%r155
    %r157 = getelementptr [10 x i32], ptr %r179, i32 0, i32 5
    store i32 %r156, ptr %r157
    %r156 = load i32, ptr %r155
    %r157 = load i32, ptr @k
    %r158 = getelementptr [0 x i32], ptr %r158, i32 0, i32 %r157
    %r159 = load i32, ptr %r158
    %r160 = add i32 %r156,%r159
    %r161 = load void, ptr %r160
    %r160 = load i32, ptr %r159
    %r161 = add i32 %r161,%r160
    %r162 = getelementptr [10 x i32], ptr %r179, i32 0, i32 6
    store i32 %r161, ptr %r162
    %r162 = load i32, ptr %r161
    %r163 = load i32, ptr @k
    %r164 = getelementptr [0 x i32], ptr %r162, i32 0, i32 %r163
    %r165 = load void, ptr %r164
    %r166 = add i32 %r162,%r165
    %r167 = load void, ptr %r166
    %r168 = load i32, ptr @k
    %r169 = getelementptr i32, ptr %r163, i32 0, i32 %r168
    %r170 = load void, ptr %r169
    %r171 = add i32 %r167,%r170
    %r172 = getelementptr [10 x i32], ptr %r179, i32 0, i32 7
    store i32 %r171, ptr %r172
    %r168 = load i32, ptr %r167
    %r169 = load i32, ptr @k
    %r170 = getelementptr i32, ptr %r168, i32 0, i32 %r169
    %r171 = load void, ptr %r170
    %r172 = add i32 %r168,%r171
    %r173 = load i32, ptr %r172
    %r172 = load i32, ptr %r171
    %r173 = add i32 %r173,%r172
    %r174 = load void, ptr %r173
    %r177 = load i32, ptr %r176
    %r178 = add i32 %r174,%r177
    %r179 = getelementptr [10 x i32], ptr %r179, i32 0, i32 8
    store i32 %r178, ptr %r179
    %r177 = load i32, ptr %r176
    %r180 = icmp ne i32 %r177,%r178
    br i1 %r180, label %L12, label %L13
    %r178 = call i32 @putfarray(i32 %r181,void %r177)
    %r180 = call i32 @putarray(i32 %r179,i32 %r179)
    store i32 0, ptr %r181
    br label %L15
    %r182 = load i32, ptr %r181
    %r185 = icmp slt i32 %r182,%r183
    br i1 %r185, label %L16, label %L17
    %r182 = getelementptr [10 x i32], ptr %r179, i32 0, i32 %r181
    %r183 = load i32, ptr %r182
    %r182 = getelementptr [10 x void], ptr %r177, i32 0, i32 %r181
    %r183 = load i32, ptr %r182
    %r184 = sub i32 %r183,%r183
    %r182 = getelementptr [10 x i32], ptr %r179, i32 0, i32 %r181
    store i32 %r184, ptr %r182
    %r182 = load i32, ptr %r181
    %r185 = add i32 %r182,%r183
    store i32 %r185, ptr %r181
    br label %L16
L13:  
L14:  
L15:  
L16:  
L17:  
L18:  
    %r182 = load i32, ptr @k
    %r183 = getelementptr [10 x i32], ptr %r179, i32 0, i32 %r182
    %r184 = load i32, ptr %r183
    %r186 = getelementptr [10 x void], ptr %r177, i32 0, i32 %r185
    %r187 = load float, ptr %r186
    %r188 = mul i32 %r184,%r187
    ret i32 %r188
    br label %L14
    %r176 = call i32 @params_mix(void %r113,i32 %r179,i32 %r115,void %r177,void %r117,i32 %r118,void %r119,void %r120,void %r121,i32 %r122,i32 %r123,i32 %r124,void %r125,i32 %r126,i32 %r127,i32 %r128,void %r129,void %r130,i32 %r131,i32 %r132,void %r133,void %r134,i32 %r135,void %r136,i32 %r137,void %r138,i32 %r139,void %r140,i32 %r141,i32 %r142,void %r143,void %r144,i32 %r145,i32 %r146,i32 %r147,void %r148,i32 %r149,i32 %r150,i32 %r151,i32 %r152,i32 %r153,i32 %r154,i32 %r155,void %r156,i32 %r157,i32 %r158,i32 %r159,void %r160,i32 %r161,i32 %r162,i32 %r163,void %r164,void %r165,void %r166,i32 %r167,i32 %r168,i32 %r169,void %r170,i32 %r171,i32 %r172,void %r173,i32 %r174,i32 %r176,void %r175)
    ret i32 %r176
    br label %L14
}
define i32 @main()
{
L1:  
    %r179 = alloca i32
    %r178 = alloca [24 x [3 x i32]]
    %r177 = alloca [40 x [3 x void]]
    %r180 = call i32 @getint()
    %r181 = load i32, ptr @k
    store i32 %r180, ptr %r181
    store i32 0, ptr %r179
    br label %L18
    %r180 = load i32, ptr %r179
    %r183 = icmp slt i32 %r180,%r181
    br i1 %r183, label %L19, label %L20
    %r180 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r179
    %r181 = call i32 @getfarray(i32 %r180)
    %r180 = load i32, ptr %r179
    %r183 = add i32 %r180,%r181
    store i32 10, ptr %r179
    br label %L19
L19:  
L20:  
L21:  
    store i32 0, ptr %r179
    br label %L21
    %r180 = load i32, ptr %r179
    %r183 = icmp slt i32 %r180,%r181
    br i1 %r183, label %L22, label %L23
    %r180 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r179
    %r181 = call i32 @getarray(i32 %r180)
    %r180 = load i32, ptr %r179
    %r183 = add i32 %r180,%r181
    store i32 10, ptr %r179
    br label %L22
L22:  
L23:  
L24:  
    %r578 = alloca i32
    %r496 = alloca void
    %r302 = alloca void
    %r180 = alloca void
    %r182 = load i32, ptr @k
    %r183 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r181, i32 %r182
    %r185 = load i32, ptr @k
    %r186 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r184, i32 %r185
    %r188 = load i32, ptr @k
    %r189 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r187, i32 %r188
    %r191 = load i32, ptr @k
    %r192 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r190, i32 %r191
    %r194 = load i32, ptr @k
    %r195 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r193, i32 %r194
    %r197 = load i32, ptr @k
    %r198 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r196, i32 %r197
    %r200 = load i32, ptr @k
    %r201 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r199, i32 %r200
    %r203 = load i32, ptr @k
    %r204 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r202, i32 %r203
    %r206 = load i32, ptr @k
    %r207 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r205, i32 %r206
    %r209 = load i32, ptr @k
    %r210 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r208, i32 %r209
    %r212 = load i32, ptr @k
    %r213 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r211, i32 %r212
    %r215 = load i32, ptr @k
    %r216 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r214, i32 %r215
    %r218 = load i32, ptr @k
    %r219 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r217, i32 %r218
    %r221 = load i32, ptr @k
    %r222 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r220, i32 %r221
    %r224 = load i32, ptr @k
    %r225 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r223, i32 %r224
    %r227 = load i32, ptr @k
    %r228 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r226, i32 %r227
    %r230 = load i32, ptr @k
    %r231 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r229, i32 %r230
    %r233 = load i32, ptr @k
    %r234 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r232, i32 %r233
    %r236 = load i32, ptr @k
    %r237 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r235, i32 %r236
    %r239 = load i32, ptr @k
    %r240 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r238, i32 %r239
    %r242 = load i32, ptr @k
    %r243 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r241, i32 %r242
    %r245 = load i32, ptr @k
    %r246 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r244, i32 %r245
    %r248 = load i32, ptr @k
    %r249 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r247, i32 %r248
    %r251 = load i32, ptr @k
    %r252 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r250, i32 %r251
    %r254 = load i32, ptr @k
    %r255 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r253, i32 %r254
    %r257 = load i32, ptr @k
    %r258 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r256, i32 %r257
    %r260 = load i32, ptr @k
    %r261 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r259, i32 %r260
    %r263 = load i32, ptr @k
    %r264 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r262, i32 %r263
    %r266 = load i32, ptr @k
    %r267 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r265, i32 %r266
    %r269 = load i32, ptr @k
    %r270 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r268, i32 %r269
    %r272 = load i32, ptr @k
    %r273 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r271, i32 %r272
    %r275 = load i32, ptr @k
    %r276 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r274, i32 %r275
    %r278 = load i32, ptr @k
    %r279 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r277, i32 %r278
    %r281 = load i32, ptr @k
    %r282 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r280, i32 %r281
    %r284 = load i32, ptr @k
    %r285 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r283, i32 %r284
    %r287 = load i32, ptr @k
    %r288 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r286, i32 %r287
    %r290 = load i32, ptr @k
    %r291 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r289, i32 %r290
    %r293 = load i32, ptr @k
    %r294 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r292, i32 %r293
    %r296 = load i32, ptr @k
    %r297 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r295, i32 %r296
    %r299 = load i32, ptr @k
    %r300 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r298, i32 %r299
    %r301 = call i32 @params_f40(i32 %r183,float %r186,float %r189,i32 %r192,float %r195,float %r198,float %r201,float %r204,float %r207,i32 %r210,float %r213,float %r216,float %r219,float %r222,float %r225,i32 %r228,float %r231,float %r234,float %r237,float %r240,float %r243,i32 %r246,float %r249,float %r252,float %r255,float %r258,float %r261,i32 %r264,float %r267,float %r270,float %r273,float %r276,float %r279,i32 %r282,float %r285,float %r288,float %r291,float %r294,float %r297,float %r300)
    store void %r301, ptr %r180
    %r304 = load i32, ptr @k
    %r305 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r303, i32 %r304
    %r307 = load i32, ptr @k
    %r308 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r306, i32 %r307
    %r310 = load i32, ptr @k
    %r311 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r309, i32 %r310
    %r313 = load i32, ptr @k
    %r314 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r312, i32 %r313
    %r316 = load i32, ptr @k
    %r317 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r315, i32 %r316
    %r319 = load i32, ptr @k
    %r320 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r318, i32 %r319
    %r322 = load i32, ptr @k
    %r323 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r321, i32 %r322
    %r325 = load i32, ptr @k
    %r326 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r324, i32 %r325
    %r328 = load i32, ptr @k
    %r329 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r327, i32 %r328
    %r331 = load i32, ptr @k
    %r332 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r330, i32 %r331
    %r334 = load i32, ptr @k
    %r335 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r333, i32 %r334
    %r337 = load i32, ptr @k
    %r338 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r336, i32 %r337
    %r340 = load i32, ptr @k
    %r341 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r339, i32 %r340
    %r343 = load i32, ptr @k
    %r344 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r342, i32 %r343
    %r346 = load i32, ptr @k
    %r347 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r345, i32 %r346
    %r349 = load i32, ptr @k
    %r350 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r348, i32 %r349
    %r352 = load i32, ptr @k
    %r353 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r351, i32 %r352
    %r355 = load i32, ptr @k
    %r356 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r354, i32 %r355
    %r358 = load i32, ptr @k
    %r359 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r357, i32 %r358
    %r361 = load i32, ptr @k
    %r362 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r360, i32 %r361
    %r364 = load i32, ptr @k
    %r365 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r363, i32 %r364
    %r367 = load i32, ptr @k
    %r368 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r366, i32 %r367
    %r370 = load i32, ptr @k
    %r371 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r369, i32 %r370
    %r373 = load i32, ptr @k
    %r374 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r372, i32 %r373
    %r376 = load i32, ptr @k
    %r377 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r375, i32 %r376
    %r379 = load i32, ptr @k
    %r380 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r378, i32 %r379
    %r382 = load i32, ptr @k
    %r383 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r381, i32 %r382
    %r385 = load i32, ptr @k
    %r386 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r384, i32 %r385
    %r388 = load i32, ptr @k
    %r389 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r387, i32 %r388
    %r391 = load i32, ptr @k
    %r392 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r390, i32 %r391
    %r394 = load i32, ptr @k
    %r395 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r393, i32 %r394
    %r397 = load i32, ptr @k
    %r398 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r396, i32 %r397
    %r400 = load i32, ptr @k
    %r401 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r399, i32 %r400
    %r403 = load i32, ptr @k
    %r404 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r402, i32 %r403
    %r406 = load i32, ptr @k
    %r407 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r405, i32 %r406
    %r409 = load i32, ptr @k
    %r410 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r408, i32 %r409
    %r412 = load i32, ptr @k
    %r413 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r411, i32 %r412
    %r415 = load i32, ptr @k
    %r416 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r414, i32 %r415
    %r418 = load i32, ptr @k
    %r419 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r417, i32 %r418
    %r421 = load i32, ptr @k
    %r422 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r420, i32 %r421
    %r424 = load i32, ptr @k
    %r425 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r423, i32 %r424
    %r427 = load i32, ptr @k
    %r428 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r426, i32 %r427
    %r430 = load i32, ptr @k
    %r431 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r429, i32 %r430
    %r433 = load i32, ptr @k
    %r434 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r432, i32 %r433
    %r436 = load i32, ptr @k
    %r437 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r435, i32 %r436
    %r439 = load i32, ptr @k
    %r440 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r438, i32 %r439
    %r442 = load i32, ptr @k
    %r443 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r441, i32 %r442
    %r445 = load i32, ptr @k
    %r446 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r444, i32 %r445
    %r448 = load i32, ptr @k
    %r449 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r447, i32 %r448
    %r451 = load i32, ptr @k
    %r452 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r450, i32 %r451
    %r454 = load i32, ptr @k
    %r455 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r453, i32 %r454
    %r457 = load i32, ptr @k
    %r458 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r456, i32 %r457
    %r460 = load i32, ptr @k
    %r461 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r459, i32 %r460
    %r463 = load i32, ptr @k
    %r464 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r462, i32 %r463
    %r466 = load i32, ptr @k
    %r467 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r465, i32 %r466
    %r469 = load i32, ptr @k
    %r470 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r468, i32 %r469
    %r472 = load i32, ptr @k
    %r473 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r471, i32 %r472
    %r475 = load i32, ptr @k
    %r476 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r474, i32 %r475
    %r478 = load i32, ptr @k
    %r479 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r477, i32 %r478
    %r481 = load i32, ptr @k
    %r482 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r480, i32 %r481
    %r484 = load i32, ptr @k
    %r485 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r483, i32 %r484
    %r487 = load i32, ptr @k
    %r488 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r486, i32 %r487
    %r490 = load i32, ptr @k
    %r491 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r489, i32 %r490
    %r493 = load i32, ptr @k
    %r494 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r492, i32 %r493
    %r495 = call i32 @params_f40_i24(float %r305,float %r308,float %r311,float %r314,float %r317,float %r320,float %r323,float %r326,float %r329,float %r332,float %r335,float %r338,float %r341,float %r344,float %r347,float %r350,float %r353,float %r356,float %r359,float %r362,float %r365,float %r368,float %r371,float %r374,float %r377,float %r380,float %r383,float %r386,float %r389,float %r392,float %r395,float %r398,float %r401,float %r404,float %r407,float %r410,float %r413,float %r416,float %r419,float %r422,float %r425,float %r428,float %r431,float %r434,float %r437,float %r440,float %r443,float %r446,float %r449,float %r452,float %r455,float %r458,float %r461,float %r464,float %r467,float %r470,float %r473,float %r476,float %r479,float %r482,float %r485,float %r488,float %r491,float %r494)
    store void %r495, ptr %r302
    %r498 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r497
    %r500 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r499
    %r502 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r501
    %r504 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r503
    %r506 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r505
    %r508 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r507
    %r510 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r509
    %r512 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r511
    %r514 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r513
    %r516 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r515
    %r518 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r517
    %r520 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r519
    %r522 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r521
    %r524 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r523
    %r526 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r525
    %r528 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r527
    %r530 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r529
    %r532 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r531
    %r534 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r533
    %r536 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r535
    %r538 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r537
    %r540 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r539
    %r542 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r541
    %r544 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r543
    %r546 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r545
    %r548 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r547
    %r550 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r549
    %r552 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r551
    %r554 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r553
    %r556 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r555
    %r558 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r557
    %r560 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r559
    %r562 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r561
    %r564 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r563
    %r566 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r565
    %r568 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r567
    %r570 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r569
    %r572 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r571
    %r574 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r573
    %r576 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r575
    %r577 = call i32 @params_fa40(float %r498,float %r500,float %r502,float %r504,float %r506,float %r508,float %r510,float %r512,float %r514,float %r516,float %r518,float %r520,float %r522,float %r524,float %r526,float %r528,float %r530,float %r532,float %r534,float %r536,float %r538,float %r540,float %r542,float %r544,float %r546,float %r548,float %r550,float %r552,float %r554,float %r556,float %r558,float %r560,float %r562,float %r564,float %r566,float %r568,float %r570,float %r572,float %r574,float %r576)
    store void %r577, ptr %r496
    %r580 = load i32, ptr @k
    %r581 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r579, i32 %r580
    %r583 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r582
    %r585 = load i32, ptr @k
    %r586 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r584, i32 %r585
    %r588 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r587
    %r590 = load i32, ptr @k
    %r591 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r589, i32 %r590
    %r593 = load i32, ptr @k
    %r594 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r592, i32 %r593
    %r596 = load i32, ptr @k
    %r597 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r595, i32 %r596
    %r599 = load i32, ptr @k
    %r600 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r598, i32 %r599
    %r602 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r601
    %r604 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r603
    %r606 = load i32, ptr @k
    %r607 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r605, i32 %r606
    %r609 = load i32, ptr @k
    %r610 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r608, i32 %r609
    %r612 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r611
    %r614 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r613
    %r616 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r615
    %r618 = load i32, ptr @k
    %r619 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r617, i32 %r618
    %r621 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r620
    %r623 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r622
    %r625 = load i32, ptr @k
    %r626 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r624, i32 %r625
    %r628 = load i32, ptr @k
    %r629 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r627, i32 %r628
    %r631 = load i32, ptr @k
    %r632 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r630, i32 %r631
    %r634 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r633
    %r636 = load i32, ptr @k
    %r637 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r635, i32 %r636
    %r639 = load i32, ptr @k
    %r640 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r638, i32 %r639
    %r642 = load i32, ptr @k
    %r643 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r641, i32 %r642
    %r645 = load i32, ptr @k
    %r646 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r644, i32 %r645
    %r648 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r647
    %r650 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r649
    %r652 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r651
    %r654 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r653
    %r656 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r655
    %r658 = load i32, ptr @k
    %r659 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r657, i32 %r658
    %r661 = load i32, ptr @k
    %r662 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r660, i32 %r661
    %r664 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r663
    %r666 = load i32, ptr @k
    %r667 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r665, i32 %r666
    %r669 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r668
    %r671 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r670
    %r673 = load i32, ptr @k
    %r674 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r672, i32 %r673
    %r676 = load i32, ptr @k
    %r677 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r675, i32 %r676
    %r679 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r678
    %r681 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r680
    %r683 = load i32, ptr @k
    %r684 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r682, i32 %r683
    %r686 = load i32, ptr @k
    %r687 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r685, i32 %r686
    %r689 = load i32, ptr @k
    %r690 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r688, i32 %r689
    %r692 = load i32, ptr @k
    %r693 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r691, i32 %r692
    %r695 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r694
    %r697 = load i32, ptr @k
    %r698 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r696, i32 %r697
    %r700 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r699
    %r702 = load i32, ptr @k
    %r703 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r701, i32 %r702
    %r705 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r704
    %r707 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r706
    %r709 = load i32, ptr @k
    %r710 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r708, i32 %r709
    %r712 = load i32, ptr @k
    %r713 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r711, i32 %r712
    %r715 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r714
    %r717 = load i32, ptr @k
    %r718 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r716, i32 %r717
    %r720 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r719
    %r722 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r721
    %r724 = load i32, ptr @k
    %r725 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r723, i32 %r724
    %r727 = load i32, ptr @k
    %r728 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r726, i32 %r727
    %r730 = load i32, ptr @k
    %r731 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r729, i32 %r730
    %r733 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r732
    %r735 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r734
    %r737 = load i32, ptr @k
    %r738 = getelementptr [40 x [3 x void]], ptr %r177, i32 0, i32 %r736, i32 %r737
    %r740 = load i32, ptr @k
    %r741 = getelementptr [24 x [3 x i32]], ptr %r178, i32 0, i32 %r739, i32 %r740
    %r742 = call i32 @params_mix(float %r581,float %r583,float %r586,float %r588,float %r591,float %r594,float %r597,float %r600,float %r602,float %r604,float %r607,float %r610,float %r612,float %r614,float %r616,float %r619,float %r621,float %r623,float %r626,float %r629,float %r632,float %r634,float %r637,float %r640,float %r643,float %r646,float %r648,float %r650,float %r652,float %r654,float %r656,float %r659,float %r662,float %r664,float %r667,float %r669,float %r671,float %r674,float %r677,float %r679,float %r681,float %r684,float %r687,float %r690,float %r693,float %r695,float %r698,float %r700,float %r703,float %r705,float %r707,float %r710,float %r713,float %r715,float %r718,float %r720,float %r722,float %r725,float %r728,float %r731,float %r733,float %r735,float %r738,float %r741)
    store i32 %r742, ptr %r578
    %r181 = call i32 @putfloat(void %r180)
    %r183 = call i32 @putch(i32 %r182)
    %r303 = call i32 @putfloat(void %r302)
    %r305 = call i32 @putch(i32 %r304)
    %r497 = call i32 @putfloat(void %r496)
    %r499 = call i32 @putch(i32 %r498)
    %r579 = call i32 @putint(i32 %r578)
    %r581 = call i32 @putch(i32 %r580)
    ret i32 0
}
