@M = global i32 zeroinitializer
@L = global i32 zeroinitializer
@N = global i32 zeroinitializer
define i32 @add(void %r0,void %r0,void %r2,void %r1,void %r4,void %r2,void %r6,void %r3,void %r8)
{
L1:  
    %r10 = load i32, ptr %r9
    %r11 = load i32, ptr @M
    %r12 = load i32, ptr %r11
    %r13 = icmp slt i32 %r10,%r12
    br i1 %r13, label %L1, label %L2
    %r10 = getelementptr [0 x void], ptr %r0, i32 0, i32 %r9
    %r10 = getelementptr [0 x void], ptr %r3, i32 0, i32 %r9
    %r12 = add i32 %r10,%r10
    %r10 = getelementptr [0 x void], ptr %r6, i32 0, i32 %r9
    store i32 %r12, ptr %r10
    %r10 = getelementptr [0 x void], ptr %r1, i32 0, i32 %r9
    %r10 = getelementptr [0 x void], ptr %r4, i32 0, i32 %r9
    %r12 = add i32 %r10,%r10
    %r10 = getelementptr [0 x void], ptr %r7, i32 0, i32 %r9
    store i32 %r12, ptr %r10
    %r10 = getelementptr [0 x void], ptr %r2, i32 0, i32 %r9
    %r10 = getelementptr [0 x void], ptr %r5, i32 0, i32 %r9
    %r12 = add i32 %r10,%r10
    %r10 = getelementptr [0 x void], ptr %r8, i32 0, i32 %r9
    store i32 %r12, ptr %r10
    %r10 = load i32, ptr %r9
    %r13 = add i32 %r10,%r11
    store i32 %r13, ptr %r9
    br label %L1
L2:  
L3:  
    ret i32 0
}
define i32 @main()
{
L1:  
    %r26 = alloca i32
    %r25 = alloca [3 x void]
    %r24 = alloca [3 x void]
    %r23 = alloca [6 x void]
    %r22 = alloca [3 x void]
    %r21 = alloca [3 x void]
    %r20 = alloca [3 x void]
    %r19 = alloca [3 x void]
    %r18 = alloca [3 x void]
    %r17 = alloca [3 x void]
    %r12 = load i32, ptr @N
    store i32 1, ptr %r12
    %r14 = load i32, ptr @M
    store i32 3, ptr %r14
    %r16 = load i32, ptr @L
    store i32 3, ptr %r16
    store i32 0, ptr %r26
    br label %L3
    %r27 = load i32, ptr %r26
    %r28 = load i32, ptr @M
    %r29 = load i32, ptr %r28
    %r30 = icmp slt i32 %r27,%r29
    br i1 %r30, label %L4, label %L5
    %r27 = getelementptr [3 x void], ptr %r17, i32 0, i32 %r26
    store i32 %r26, ptr %r27
    %r27 = getelementptr [3 x void], ptr %r18, i32 0, i32 %r26
    store i32 %r26, ptr %r27
    %r27 = getelementptr [3 x void], ptr %r19, i32 0, i32 %r26
    store i32 %r26, ptr %r27
    %r27 = getelementptr [3 x void], ptr %r20, i32 0, i32 %r26
    store i32 %r26, ptr %r27
    %r27 = getelementptr [3 x void], ptr %r21, i32 0, i32 %r26
    store i32 %r26, ptr %r27
    %r27 = getelementptr [3 x void], ptr %r22, i32 0, i32 %r26
    store i32 %r26, ptr %r27
    %r27 = load i32, ptr %r26
    %r30 = add i32 %r27,%r28
    store i32 %r30, ptr %r26
    br label %L4
L4:  
L5:  
L6:  
    %r27 = alloca i32
    %r26 = call i32 @add(void %r17,void %r18,void %r19,void %r20,void %r21,void %r22,void %r23,void %r24,void %r25)
    store i32 %r26, ptr %r26
    br label %L6
    %r27 = load i32, ptr %r26
    %r28 = load i32, ptr @N
    %r29 = load i32, ptr %r28
    %r30 = icmp slt i32 %r27,%r29
    br i1 %r30, label %L7, label %L8
    %r27 = getelementptr [6 x void], ptr %r23, i32 0, i32 %r26
    store i32 %r27, ptr %r27
    %r28 = call i32 @putint(i32 %r27)
    %r27 = load i32, ptr %r26
    %r30 = add i32 %r27,%r28
    store i32 %r30, ptr %r26
    br label %L7
L7:  
L8:  
L9:  
    store i32 10, ptr %r27
    %r28 = call i32 @putch(i32 %r27)
    store i32 0, ptr %r26
    br label %L9
    %r27 = load i32, ptr %r26
    %r28 = load i32, ptr @N
    %r29 = load i32, ptr %r28
    %r30 = icmp slt i32 %r27,%r29
    br i1 %r30, label %L10, label %L11
    %r27 = getelementptr [3 x void], ptr %r24, i32 0, i32 %r26
    store i32 10, ptr %r27
    %r28 = call i32 @putint(i32 %r27)
    %r27 = load i32, ptr %r26
    %r30 = add i32 %r27,%r28
    store i32 %r30, ptr %r26
    br label %L10
L10:  
L11:  
L12:  
    store i32 10, ptr %r27
    %r28 = call i32 @putch(i32 %r27)
    store i32 0, ptr %r26
    br label %L12
    %r27 = load i32, ptr %r26
    %r28 = load i32, ptr @N
    %r29 = load i32, ptr %r28
    %r30 = icmp slt i32 %r27,%r29
    br i1 %r30, label %L13, label %L14
    %r27 = getelementptr [3 x void], ptr %r25, i32 0, i32 %r26
    store i32 10, ptr %r27
    %r28 = call i32 @putint(i32 %r27)
    %r27 = load i32, ptr %r26
    %r30 = add i32 %r27,%r28
    store i32 %r30, ptr %r26
    br label %L13
L13:  
L14:  
L15:  
    store i32 10, ptr %r27
    %r28 = call i32 @putch(i32 %r27)
    ret i32 0
}
