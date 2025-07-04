@M = global i32 zeroinitializer
@L = global i32 zeroinitializer
@N = global i32 zeroinitializer
define i32 @tran(void %r0,void %r0,void %r2,void %r1,void %r4,void %r2,void %r6,void %r3,void %r8)
{
L1:  
    %r9 = alloca i32
    store i32 0, ptr %r9
    %r11 = getelementptr [0 x void], ptr %r2, i32 0, i32 %r10
    %r13 = getelementptr [0 x void], ptr %r7, i32 0, i32 %r12
    store float %r11, ptr %r13
    %r15 = getelementptr [0 x void], ptr %r1, i32 0, i32 %r14
    %r17 = getelementptr [0 x void], ptr %r8, i32 0, i32 %r16
    store float %r15, ptr %r17
    %r19 = getelementptr [0 x void], ptr %r1, i32 0, i32 %r18
    %r21 = getelementptr [0 x void], ptr %r6, i32 0, i32 %r20
    store float %r19, ptr %r21
    %r23 = getelementptr [0 x void], ptr %r2, i32 0, i32 %r22
    %r25 = getelementptr [0 x void], ptr %r6, i32 0, i32 %r24
    store float %r23, ptr %r25
    %r27 = getelementptr [0 x void], ptr %r0, i32 0, i32 %r26
    %r29 = getelementptr [0 x void], ptr %r7, i32 0, i32 %r28
    store float %r27, ptr %r29
    %r31 = getelementptr [0 x void], ptr %r0, i32 0, i32 %r30
    %r33 = getelementptr [0 x void], ptr %r8, i32 0, i32 %r32
    store float %r31, ptr %r33
    %r35 = getelementptr [0 x void], ptr %r1, i32 0, i32 %r34
    %r37 = getelementptr [0 x void], ptr %r7, i32 0, i32 %r36
    store float %r35, ptr %r37
    %r39 = getelementptr [0 x void], ptr %r2, i32 0, i32 %r38
    %r41 = getelementptr [0 x void], ptr %r8, i32 0, i32 %r40
    store float %r39, ptr %r41
    %r43 = getelementptr [0 x void], ptr %r0, i32 0, i32 %r42
    %r45 = getelementptr [0 x void], ptr %r6, i32 0, i32 %r44
    store float %r43, ptr %r45
    ret i32 0
}
define i32 @main()
{
L1:  
    %r63 = load i32, ptr %r62
    %r64 = load i32, ptr @M
    %r65 = load i32, ptr %r64
    %r66 = icmp slt i32 %r63,%r65
    br i1 %r66, label %L1, label %L2
    %r63 = getelementptr [3 x void], ptr %r53, i32 0, i32 %r62
    store i32 %r62, ptr %r63
    %r63 = getelementptr [3 x void], ptr %r54, i32 0, i32 %r62
    store i32 %r62, ptr %r63
    %r63 = getelementptr [3 x void], ptr %r55, i32 0, i32 %r62
    store i32 %r62, ptr %r63
    %r63 = getelementptr [3 x void], ptr %r56, i32 0, i32 %r62
    store i32 %r62, ptr %r63
    %r63 = getelementptr [3 x void], ptr %r57, i32 0, i32 %r62
    store i32 %r62, ptr %r63
    %r63 = getelementptr [3 x void], ptr %r58, i32 0, i32 %r62
    store i32 %r62, ptr %r63
    %r63 = load i32, ptr %r62
    %r66 = add i32 %r63,%r64
    store i32 %r66, ptr %r62
    br label %L1
L2:  
L3:  
    %r63 = alloca i32
    %r62 = call i32 @tran(void %r53,void %r54,void %r55,void %r56,void %r57,void %r58,void %r59,void %r60,void %r61)
    store i32 %r62, ptr %r62
    br label %L3
    %r63 = load i32, ptr %r62
    %r64 = load i32, ptr @N
    %r65 = load i32, ptr %r64
    %r66 = icmp slt i32 %r63,%r65
    br i1 %r66, label %L4, label %L5
    %r63 = getelementptr [6 x void], ptr %r59, i32 0, i32 %r62
    store i32 %r63, ptr %r63
    %r64 = call i32 @putint(i32 %r63)
    %r63 = load i32, ptr %r62
    %r66 = add i32 %r63,%r64
    store i32 %r66, ptr %r62
    br label %L4
L4:  
L5:  
L6:  
    store i32 10, ptr %r63
    %r64 = call i32 @putch(i32 %r63)
    store i32 0, ptr %r62
    br label %L6
    %r63 = load i32, ptr %r62
    %r64 = load i32, ptr @N
    %r65 = load i32, ptr %r64
    %r66 = icmp slt i32 %r63,%r65
    br i1 %r66, label %L7, label %L8
    %r63 = getelementptr [3 x void], ptr %r60, i32 0, i32 %r62
    store i32 10, ptr %r63
    %r64 = call i32 @putint(i32 %r63)
    %r63 = load i32, ptr %r62
    %r66 = add i32 %r63,%r64
    store i32 %r66, ptr %r62
    br label %L7
L7:  
L8:  
L9:  
    store i32 10, ptr %r63
    store i32 1, ptr %r62
    %r64 = call i32 @putch(i32 %r63)
    br label %L9
    %r63 = load i32, ptr %r62
    %r64 = load i32, ptr @N
    %r65 = load i32, ptr %r64
    %r66 = icmp slt i32 %r63,%r65
    br i1 %r66, label %L10, label %L11
    %r63 = getelementptr [3 x void], ptr %r61, i32 0, i32 %r62
    store i32 10, ptr %r63
    %r64 = call i32 @putint(i32 %r63)
    %r63 = load i32, ptr %r62
    %r66 = add i32 %r63,%r64
    store i32 %r66, ptr %r62
    br label %L10
L10:  
L11:  
L12:  
    store i32 10, ptr %r63
    %r64 = call i32 @putch(i32 %r63)
    ret i32 0
}
