@a = global [4096x i32] zeroinitializer
define i32 @f1(i32 %r0)
{
L1:  
    %r3 = getelementptr [4096 x i32], ptr @a, i32 0, i32 %r2
    store float 4000, ptr %r3
    %r6 = getelementptr [4096 x i32], ptr @a, i32 0, i32 %r5
    store float 3, ptr %r6
    %r9 = getelementptr [4096 x i32], ptr @a, i32 0, i32 %r8
    store float 7, ptr %r9
    %r11 = getelementptr [4096 x i32], ptr @a, i32 0, i32 %r10
    %r12 = load float, ptr %r11
    %r15 = add i32 %r12,%r13
    %r17 = getelementptr [4096 x i32], ptr @a, i32 0, i32 %r16
    %r18 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r17
    store float %r15, ptr %r18
    %r20 = getelementptr [4096 x i32], ptr @a, i32 0, i32 %r19
    %r21 = getelementptr [4096 x i32], ptr @a, i32 0, i32 %r20
    ret i32 %r21
}
define i32 @main()
{
L1:  
    %r39 = alloca [1024 x [4 x i32]]
    %r22 = alloca [4 x [1024 x i32]]
    %r23 = getelementptr [4 x [1024 x i32]], ptr %r22, i32 0, i32 0
    %r24 = getelementptr [4 x [1024 x i32]], ptr %r22, i32 1, i32 0
    %r26 = getelementptr [1024 x i32], ptr %r24, i32 0, i32 0
    store i32 1, ptr %r26
    %r27 = getelementptr [4 x [1024 x i32]], ptr %r22, i32 2, i32 0
    %r29 = getelementptr [1024 x i32], ptr %r27, i32 0, i32 0
    store i32 2, ptr %r29
    %r31 = getelementptr [1024 x i32], ptr %r27, i32 0, i32 1
    store i32 3, ptr %r31
    %r32 = getelementptr [4 x [1024 x i32]], ptr %r22, i32 3, i32 0
    %r34 = getelementptr [1024 x i32], ptr %r32, i32 0, i32 0
    store i32 4, ptr %r34
    %r36 = getelementptr [1024 x i32], ptr %r32, i32 0, i32 1
    store i32 5, ptr %r36
    %r38 = getelementptr [1024 x i32], ptr %r32, i32 0, i32 2
    store i32 6, ptr %r38
    %r40 = getelementptr [1024 x [4 x i32]], ptr %r39, i32 0, i32 0
    %r42 = getelementptr [4 x i32], ptr %r40, i32 0, i32 0
    store i32 1, ptr %r42
    %r44 = getelementptr [4 x i32], ptr %r40, i32 0, i32 1
    store i32 2, ptr %r44
    %r45 = getelementptr [1024 x [4 x i32]], ptr %r39, i32 1, i32 0
    %r47 = getelementptr [4 x i32], ptr %r45, i32 0, i32 0
    store i32 3, ptr %r47
    %r49 = getelementptr [4 x i32], ptr %r45, i32 0, i32 1
    store i32 4, ptr %r49
    %r51 = getelementptr [1024 x [4 x i32]], ptr %r39, i32 0, i32 %r50
    %r52 = call i32 @f1(float %r51)
    %r53 = call i32 @putint(float %r52)
    %r55 = call i32 @putch(i32 %r54)
    %r58 = getelementptr [1024 x [4 x i32]], ptr %r39, i32 0, i32 %r56, i32 %r57
    ret i32 %r58
}
