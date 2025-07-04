@a0 = global i32 zeroinitializer
@a1 = global i32 zeroinitializer
@a2 = global i32 zeroinitializer
@a3 = global i32 zeroinitializer
@a4 = global i32 zeroinitializer
@a5 = global i32 zeroinitializer
@a6 = global i32 zeroinitializer
@a7 = global i32 zeroinitializer
@a8 = global i32 zeroinitializer
@a9 = global i32 zeroinitializer
@a10 = global i32 zeroinitializer
@a11 = global i32 zeroinitializer
@a12 = global i32 zeroinitializer
@a13 = global i32 zeroinitializer
@a14 = global i32 zeroinitializer
@a15 = global i32 zeroinitializer
@a16 = global i32 zeroinitializer
@a17 = global i32 zeroinitializer
@a18 = global i32 zeroinitializer
@a19 = global i32 zeroinitializer
@a20 = global i32 zeroinitializer
@a21 = global i32 zeroinitializer
@a22 = global i32 zeroinitializer
@a23 = global i32 zeroinitializer
@a24 = global i32 zeroinitializer
@a25 = global i32 zeroinitializer
@a26 = global i32 zeroinitializer
@a27 = global i32 zeroinitializer
@a28 = global i32 zeroinitializer
@a29 = global i32 zeroinitializer
@a30 = global i32 zeroinitializer
@a31 = global i32 zeroinitializer
@a32 = global i32 zeroinitializer
@a33 = global i32 zeroinitializer
@a34 = global i32 zeroinitializer
@a35 = global i32 zeroinitializer
@a36 = global i32 zeroinitializer
@a37 = global i32 zeroinitializer
@a38 = global i32 zeroinitializer
@a39 = global i32 zeroinitializer
define i32 @testParam8(i32 %r0,i32 %r0,i32 %r2,i32 %r1,i32 %r4,i32 %r2,i32 %r6,i32 %r3)
{
L1:  
    %r1 = load i32, ptr %r0
    %r2 = load i32, ptr %r1
    %r3 = add i32 %r1,%r2
    %r4 = load i32, ptr %r3
    %r3 = load i32, ptr %r2
    %r4 = add i32 %r4,%r3
    %r5 = load i32, ptr %r4
    %r4 = load i32, ptr %r3
    %r5 = add i32 %r5,%r4
    %r6 = load i32, ptr %r5
    %r5 = load i32, ptr %r4
    %r6 = add i32 %r6,%r5
    %r7 = load i32, ptr %r6
    %r6 = load i32, ptr %r5
    %r7 = add i32 %r7,%r6
    %r8 = load i32, ptr %r7
    %r7 = load i32, ptr %r6
    %r8 = add i32 %r8,%r7
    %r9 = load float, ptr %r8
    %r8 = load i32, ptr %r7
    %r9 = add i32 %r9,%r8
    ret i32 %r9
}
define i32 @testParam32(i32 %r0,i32 %r28,i32 %r2,i32 %r29,i32 %r4,i32 %r30,i32 %r6,i32 %r31,i32 %r8,i32 %r32,i32 %r10,i32 %r33,i32 %r12,i32 %r34,i32 %r14,i32 %r35,i32 %r16,i32 %r36,i32 %r18,i32 %r37,i32 %r20,i32 %r38,i32 %r22,i32 %r39,i32 %r24,i32 %r40,i32 %r26,i32 %r41,i32 %r28,i32 %r42,i32 %r30,i32 %r43)
{
L1:  
    %r29 = load i32, ptr %r28
    %r30 = load i32, ptr %r29
    %r31 = add i32 %r29,%r30
    %r32 = load i32, ptr %r31
    %r31 = load i32, ptr %r30
    %r32 = add i32 %r32,%r31
    %r33 = load i32, ptr %r32
    %r32 = load i32, ptr %r31
    %r33 = add i32 %r33,%r32
    %r34 = load i32, ptr %r33
    %r33 = load i32, ptr %r32
    %r34 = add i32 %r34,%r33
    %r35 = load i32, ptr %r34
    %r34 = load i32, ptr %r33
    %r35 = add i32 %r35,%r34
    %r36 = load i32, ptr %r35
    %r35 = load i32, ptr %r34
    %r36 = add i32 %r36,%r35
    %r37 = load i32, ptr %r36
    %r36 = load i32, ptr %r35
    %r37 = add i32 %r37,%r36
    %r38 = load i32, ptr %r37
    %r37 = load i32, ptr %r36
    %r38 = add i32 %r38,%r37
    %r39 = load i32, ptr %r38
    %r38 = load i32, ptr %r37
    %r39 = add i32 %r39,%r38
    %r40 = load i32, ptr %r39
    %r39 = load i32, ptr %r38
    %r40 = add i32 %r40,%r39
    %r41 = load i32, ptr %r40
    %r40 = load i32, ptr %r39
    %r41 = add i32 %r41,%r40
    %r42 = load i32, ptr %r41
    %r41 = load i32, ptr %r40
    %r42 = add i32 %r42,%r41
    %r43 = load i32, ptr %r42
    %r42 = load i32, ptr %r41
    %r43 = add i32 %r43,%r42
    %r44 = load i32, ptr %r43
    %r43 = load i32, ptr %r42
    %r44 = add i32 %r44,%r43
    %r45 = load i32, ptr %r44
    %r44 = load i32, ptr %r43
    %r45 = add i32 %r45,%r44
    %r46 = load i32, ptr %r45
    %r45 = load i32, ptr %r44
    %r46 = add i32 %r46,%r45
    %r47 = load i32, ptr %r46
    %r46 = load i32, ptr %r45
    %r47 = add i32 %r47,%r46
    %r48 = load i32, ptr %r47
    %r47 = load i32, ptr %r46
    %r48 = sub i32 %r48,%r47
    %r49 = load i32, ptr %r48
    %r48 = load i32, ptr %r47
    %r49 = sub i32 %r49,%r48
    %r50 = load i32, ptr %r49
    %r49 = load i32, ptr %r48
    %r50 = sub i32 %r50,%r49
    %r51 = load i32, ptr %r50
    %r50 = load i32, ptr %r49
    %r51 = sub i32 %r51,%r50
    %r52 = load i32, ptr %r51
    %r51 = load i32, ptr %r50
    %r52 = sub i32 %r52,%r51
    %r53 = load i32, ptr %r52
    %r52 = load i32, ptr %r51
    %r53 = add i32 %r53,%r52
    %r54 = load i32, ptr %r53
    %r53 = load i32, ptr %r52
    %r54 = add i32 %r54,%r53
    %r55 = load i32, ptr %r54
    %r54 = load i32, ptr %r53
    %r55 = add i32 %r55,%r54
    %r56 = load i32, ptr %r55
    %r55 = load i32, ptr %r54
    %r56 = add i32 %r56,%r55
    %r57 = load i32, ptr %r56
    %r56 = load i32, ptr %r55
    %r57 = add i32 %r57,%r56
    %r58 = load i32, ptr %r57
    %r57 = load i32, ptr %r56
    %r58 = add i32 %r58,%r57
    %r59 = load i32, ptr %r58
    %r58 = load i32, ptr %r57
    %r59 = add i32 %r59,%r58
    %r60 = load i32, ptr %r59
    %r59 = load i32, ptr %r58
    %r60 = add i32 %r60,%r59
    %r61 = load float, ptr %r60
    %r60 = load i32, ptr %r59
    %r61 = add i32 %r61,%r60
    ret i32 %r61
}
define i32 @testParam16(i32 %r0,i32 %r10,i32 %r2,i32 %r11,i32 %r4,i32 %r12,i32 %r6,i32 %r13,i32 %r8,i32 %r14,i32 %r10,i32 %r15,i32 %r12,i32 %r16,i32 %r14,i32 %r17)
{
L1:  
    %r11 = load i32, ptr %r10
    %r12 = load i32, ptr %r11
    %r13 = add i32 %r11,%r12
    %r14 = load i32, ptr %r13
    %r13 = load i32, ptr %r12
    %r14 = add i32 %r14,%r13
    %r15 = load i32, ptr %r14
    %r14 = load i32, ptr %r13
    %r15 = sub i32 %r15,%r14
    %r16 = load i32, ptr %r15
    %r15 = load i32, ptr %r14
    %r16 = sub i32 %r16,%r15
    %r17 = load i32, ptr %r16
    %r16 = load i32, ptr %r15
    %r17 = sub i32 %r17,%r16
    %r18 = load i32, ptr %r17
    %r17 = load i32, ptr %r16
    %r18 = sub i32 %r18,%r17
    %r19 = load i32, ptr %r18
    %r18 = load i32, ptr %r17
    %r19 = sub i32 %r19,%r18
    %r20 = load i32, ptr %r19
    %r19 = load i32, ptr %r18
    %r20 = add i32 %r20,%r19
    %r21 = load i32, ptr %r20
    %r20 = load i32, ptr %r19
    %r21 = add i32 %r21,%r20
    %r22 = load i32, ptr %r21
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r22,%r21
    %r23 = load i32, ptr %r22
    %r22 = load i32, ptr %r21
    %r23 = add i32 %r23,%r22
    %r24 = load i32, ptr %r23
    %r23 = load i32, ptr %r22
    %r24 = add i32 %r24,%r23
    %r25 = load i32, ptr %r24
    %r24 = load i32, ptr %r23
    %r25 = add i32 %r25,%r24
    %r26 = load i32, ptr %r25
    %r25 = load i32, ptr %r24
    %r26 = add i32 %r26,%r25
    %r27 = load float, ptr %r26
    %r26 = load i32, ptr %r25
    %r27 = add i32 %r27,%r26
    ret i32 %r27
}
define i32 @main()
{
L1:  
    store i32 0, ptr %r28
    store i32 1, ptr %r29
    store i32 2, ptr %r30
    store i32 3, ptr %r31
    store i32 4, ptr %r32
    store i32 5, ptr %r33
    store i32 6, ptr %r34
    store i32 7, ptr %r35
    store i32 8, ptr %r36
    store i32 9, ptr %r37
    store i32 0, ptr %r38
    store i32 1, ptr %r39
    store i32 2, ptr %r40
    store i32 3, ptr %r41
    store i32 4, ptr %r42
    store i32 5, ptr %r43
    store i32 6, ptr %r44
    store i32 7, ptr %r45
    store i32 8, ptr %r46
    store i32 9, ptr %r47
    store i32 0, ptr %r48
    store i32 1, ptr %r49
    store i32 2, ptr %r50
    store i32 3, ptr %r51
    store i32 4, ptr %r52
    store i32 5, ptr %r53
    store i32 6, ptr %r54
    store i32 7, ptr %r55
    store i32 8, ptr %r56
    store i32 9, ptr %r57
    store i32 0, ptr %r58
    store i32 1, ptr %r59
    %r61 = load i32, ptr @a32
    store i32 4, ptr %r61
    %r63 = load i32, ptr @a33
    store i32 0, ptr %r63
    %r65 = load i32, ptr @a34
    store i32 6, ptr %r65
    %r67 = load i32, ptr @a35
    store i32 7, ptr %r67
    %r69 = load i32, ptr @a36
    store i32 8, ptr %r69
    %r71 = load i32, ptr @a37
    store i32 9, ptr %r71
    %r73 = load i32, ptr @a38
    store i32 0, ptr %r73
    %r75 = load i32, ptr @a39
    store i32 1, ptr %r75
    %r36 = call i32 @testParam8(i32 %r28,i32 %r29,i32 %r30,i32 %r31,i32 %r32,i32 %r33,i32 %r34,i32 %r35)
    store i32 8, ptr %r28
    %r29 = call i32 @putint(i32 %r28)
    %r30 = load i32, ptr @a32
    %r31 = load i32, ptr @a33
    %r32 = load i32, ptr @a34
    %r33 = load i32, ptr @a35
    %r34 = load i32, ptr @a36
    %r35 = load i32, ptr @a37
    %r36 = load i32, ptr @a38
    %r37 = load i32, ptr @a39
    %r44 = call i32 @testParam16(i32 %r30,i32 %r31,i32 %r32,i32 %r33,i32 %r34,i32 %r35,i32 %r36,i32 %r37,i32 %r36,i32 %r37,i32 %r38,i32 %r39,i32 %r40,i32 %r41,i32 %r42,i32 %r43)
    store i32 6, ptr %r28
    %r29 = call i32 @putint(i32 %r28)
    %r60 = call i32 @testParam32(i32 %r28,i32 %r29,i32 %r30,i32 %r31,i32 %r32,i32 %r33,i32 %r34,i32 %r35,i32 %r36,i32 %r37,i32 %r38,i32 %r39,i32 %r40,i32 %r41,i32 %r42,i32 %r43,i32 %r44,i32 %r45,i32 %r46,i32 %r47,i32 %r48,i32 %r49,i32 %r50,i32 %r51,i32 %r52,i32 %r53,i32 %r54,i32 %r55,i32 %r56,i32 %r57,i32 %r58,i32 %r59)
    store i32 4, ptr %r28
    %r29 = call i32 @putint(i32 %r28)
    ret i32 0
}
