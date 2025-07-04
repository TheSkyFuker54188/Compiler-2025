define i32 @main()
{
L1:  
    %r87 = alloca i32
    %r52 = alloca i32
    %r84 = alloca i32
    %r82 = alloca i32
    %r80 = alloca i32
    %r78 = alloca i32
    %r76 = alloca i32
    %r74 = alloca i32
    %r72 = alloca i32
    %r70 = alloca i32
    %r54 = alloca i32
    %r69 = alloca i32
    %r67 = alloca i32
    %r65 = alloca i32
    %r63 = alloca i32
    %r61 = alloca i32
    %r59 = alloca i32
    %r57 = alloca i32
    %r55 = alloca i32
    %r53 = alloca i32
    %r51 = alloca i32
    %r49 = alloca i32
    %r47 = alloca i32
    %r45 = alloca i32
    %r43 = alloca i32
    %r41 = alloca i32
    %r39 = alloca i32
    %r37 = alloca i32
    store i32 5, ptr %r37
    store i32 6, ptr %r39
    store i32 1, ptr %r41
    store i32 0, ptr %r43
    store i32 3, ptr %r45
    store i32 5, ptr %r47
    store i32 3, ptr %r49
    store i32 2, ptr %r51
    store i32 7, ptr %r53
    store i32 9, ptr %r55
    store i32 8, ptr %r57
    store i32 1, ptr %r59
    store i32 4, ptr %r61
    store i32 6, ptr %r63
    store i32 4, ptr %r65
    store i32 6, ptr %r67
    %r38 = load i32, ptr %r37
    %r40 = load i32, ptr %r39
    %r41 = add i32 %r38,%r40
    %r42 = load i32, ptr %r41
    %r42 = load i32, ptr %r41
    %r43 = add i32 %r42,%r42
    %r44 = load i32, ptr %r43
    %r44 = load i32, ptr %r43
    %r45 = add i32 %r44,%r44
    %r46 = load i32, ptr %r45
    %r46 = load i32, ptr %r45
    %r47 = add i32 %r46,%r46
    %r48 = load i32, ptr %r47
    %r48 = load i32, ptr %r47
    %r49 = add i32 %r48,%r48
    %r50 = load i32, ptr %r49
    %r50 = load i32, ptr %r49
    %r51 = add i32 %r50,%r50
    %r52 = load i32, ptr %r51
    %r52 = load i32, ptr %r51
    %r53 = add i32 %r52,%r52
    store i32 %r53, ptr %r69
    %r54 = load i32, ptr %r53
    %r56 = load i32, ptr %r55
    %r57 = add i32 %r54,%r56
    %r58 = load i32, ptr %r57
    %r58 = load i32, ptr %r57
    %r59 = add i32 %r58,%r58
    %r60 = load i32, ptr %r59
    %r60 = load i32, ptr %r59
    %r61 = add i32 %r60,%r60
    %r62 = load i32, ptr %r61
    %r62 = load i32, ptr %r61
    %r63 = add i32 %r62,%r62
    %r64 = load i32, ptr %r63
    %r64 = load i32, ptr %r63
    %r65 = add i32 %r64,%r64
    %r66 = load i32, ptr %r65
    %r66 = load i32, ptr %r65
    %r67 = add i32 %r66,%r66
    %r68 = load i32, ptr %r67
    %r68 = load i32, ptr %r67
    %r69 = add i32 %r68,%r68
    store i32 %r69, ptr %r54
    %r70 = load i32, ptr %r69
    %r71 = call i32 @foo()
    %r72 = load float, ptr %r71
    %r73 = add i32 %r70,%r72
    store i32 %r73, ptr %r69
    store i32 4, ptr %r70
    store i32 7, ptr %r72
    store i32 2, ptr %r74
    store i32 5, ptr %r76
    store i32 8, ptr %r78
    store i32 0, ptr %r80
    store i32 6, ptr %r82
    store i32 3, ptr %r84
    %r55 = load i32, ptr %r54
    %r56 = call i32 @foo()
    %r58 = add i32 %r55,%r56
    store i32 8, ptr %r54
    store i32 %r53, ptr %r37
    store i32 %r55, ptr %r39
    store i32 %r57, ptr %r41
    store i32 %r59, ptr %r43
    store i32 %r61, ptr %r45
    store i32 %r63, ptr %r47
    store i32 %r65, ptr %r49
    store i32 %r67, ptr %r51
    %r71 = load i32, ptr %r70
    %r73 = load i32, ptr %r72
    %r74 = add i32 %r71,%r73
    %r75 = load i32, ptr %r74
    %r75 = load i32, ptr %r74
    %r76 = add i32 %r75,%r75
    %r77 = load i32, ptr %r76
    %r77 = load i32, ptr %r76
    %r78 = add i32 %r77,%r77
    %r79 = load i32, ptr %r78
    %r79 = load i32, ptr %r78
    %r80 = add i32 %r79,%r79
    %r81 = load i32, ptr %r80
    %r81 = load i32, ptr %r80
    %r82 = add i32 %r81,%r81
    %r83 = load i32, ptr %r82
    %r83 = load i32, ptr %r82
    %r84 = add i32 %r83,%r83
    %r85 = load i32, ptr %r84
    %r85 = load i32, ptr %r84
    %r86 = add i32 %r85,%r85
    store i32 %r86, ptr %r52
    %r70 = load i32, ptr %r69
    %r55 = load i32, ptr %r54
    %r56 = add i32 %r70,%r55
    %r53 = load i32, ptr %r52
    %r54 = add i32 %r56,%r53
    store i32 %r54, ptr %r87
    %r88 = call i32 @putint(i32 %r87)
    %r90 = call i32 @putch(i32 %r89)
    ret i32 0
}
define i32 @foo()
{
L1:  
    %r50 = alloca i32
    %r65 = alloca i32
    %r63 = alloca i32
    %r61 = alloca i32
    %r59 = alloca i32
    %r57 = alloca i32
    %r55 = alloca i32
    %r53 = alloca i32
    %r51 = alloca i32
    %r49 = alloca i32
    %r47 = alloca i32
    %r45 = alloca i32
    %r43 = alloca i32
    %r41 = alloca i32
    %r39 = alloca i32
    %r37 = alloca i32
    %r35 = alloca i32
    %r33 = alloca i32
    %r0 = alloca [16 x i32]
    %r2 = getelementptr [16 x i32], ptr %r0, i32 0, i32 0
    store i32 0, ptr %r2
    %r4 = getelementptr [16 x i32], ptr %r0, i32 0, i32 1
    store i32 1, ptr %r4
    %r6 = getelementptr [16 x i32], ptr %r0, i32 0, i32 2
    store i32 2, ptr %r6
    %r8 = getelementptr [16 x i32], ptr %r0, i32 0, i32 3
    store i32 3, ptr %r8
    %r10 = getelementptr [16 x i32], ptr %r0, i32 0, i32 4
    store i32 0, ptr %r10
    %r12 = getelementptr [16 x i32], ptr %r0, i32 0, i32 5
    store i32 1, ptr %r12
    %r14 = getelementptr [16 x i32], ptr %r0, i32 0, i32 6
    store i32 2, ptr %r14
    %r16 = getelementptr [16 x i32], ptr %r0, i32 0, i32 7
    store i32 3, ptr %r16
    %r18 = getelementptr [16 x i32], ptr %r0, i32 0, i32 8
    store i32 0, ptr %r18
    %r20 = getelementptr [16 x i32], ptr %r0, i32 0, i32 9
    store i32 1, ptr %r20
    %r22 = getelementptr [16 x i32], ptr %r0, i32 0, i32 10
    store i32 2, ptr %r22
    %r24 = getelementptr [16 x i32], ptr %r0, i32 0, i32 11
    store i32 3, ptr %r24
    %r26 = getelementptr [16 x i32], ptr %r0, i32 0, i32 12
    store i32 0, ptr %r26
    %r28 = getelementptr [16 x i32], ptr %r0, i32 0, i32 13
    store i32 1, ptr %r28
    %r30 = getelementptr [16 x i32], ptr %r0, i32 0, i32 14
    store i32 2, ptr %r30
    %r32 = getelementptr [16 x i32], ptr %r0, i32 0, i32 15
    store i32 3, ptr %r32
    store i32 3, ptr %r33
    store i32 7, ptr %r35
    store i32 5, ptr %r37
    store i32 6, ptr %r39
    store i32 1, ptr %r41
    store i32 0, ptr %r43
    store i32 3, ptr %r45
    store i32 5, ptr %r47
    store i32 4, ptr %r49
    store i32 2, ptr %r51
    store i32 7, ptr %r53
    store i32 9, ptr %r55
    store i32 8, ptr %r57
    store i32 1, ptr %r59
    store i32 4, ptr %r61
    store i32 6, ptr %r63
    %r34 = load i32, ptr %r33
    %r36 = load i32, ptr %r35
    %r37 = add i32 %r34,%r36
    %r38 = load i32, ptr %r37
    %r38 = load i32, ptr %r37
    %r39 = add i32 %r38,%r38
    %r40 = load i32, ptr %r39
    %r40 = load i32, ptr %r39
    %r41 = add i32 %r40,%r40
    %r42 = load i32, ptr %r41
    %r42 = load i32, ptr %r41
    %r43 = add i32 %r42,%r42
    %r44 = load i32, ptr %r43
    %r44 = load i32, ptr %r43
    %r45 = add i32 %r44,%r44
    %r46 = load i32, ptr %r45
    %r46 = load i32, ptr %r45
    %r47 = add i32 %r46,%r46
    %r48 = load i32, ptr %r47
    %r48 = load i32, ptr %r47
    %r49 = add i32 %r48,%r48
    store i32 %r49, ptr %r65
    %r50 = load i32, ptr %r49
    %r52 = load i32, ptr %r51
    %r53 = add i32 %r50,%r52
    %r54 = load i32, ptr %r53
    %r54 = load i32, ptr %r53
    %r55 = add i32 %r54,%r54
    %r56 = load i32, ptr %r55
    %r56 = load i32, ptr %r55
    %r57 = add i32 %r56,%r56
    %r58 = load i32, ptr %r57
    %r58 = load i32, ptr %r57
    %r59 = add i32 %r58,%r58
    %r60 = load i32, ptr %r59
    %r60 = load i32, ptr %r59
    %r61 = add i32 %r60,%r60
    %r62 = load i32, ptr %r61
    %r62 = load i32, ptr %r61
    %r63 = add i32 %r62,%r62
    %r64 = load i32, ptr %r63
    %r64 = load i32, ptr %r63
    %r65 = add i32 %r64,%r64
    store i32 %r65, ptr %r50
    %r66 = load i32, ptr %r65
    %r51 = load i32, ptr %r50
    %r52 = add i32 %r66,%r51
    %r34 = getelementptr [16 x i32], ptr %r0, i32 0, i32 %r33
    %r35 = load i32, ptr %r34
    %r36 = add i32 %r52,%r35
    ret i32 7
}
