define i32 @read_str(i32 %r0)
{
L1:  
    %r19 = alloca i32
    store i32 0, ptr %r19
    br label %L18
    br i1 %r21, label %L19, label %L20
    %r22 = call i32 @getch()
    %r20 = getelementptr [0 x i32], ptr %r18, i32 0, i32 %r19
    store i32 %r22, ptr %r20
    %r20 = getelementptr [0 x i32], ptr %r18, i32 0, i32 %r19
    %r24 = icmp eq i32 %r20,%r22
    br i1 %r24, label %L21, label %L22
    br label %L20
    br label %L23
L19:  
L20:  
L21:  
    %r20 = getelementptr [0 x i32], ptr %r18, i32 0, i32 %r19
    store i32 0, ptr %r20
    ret i32 %r19
L22:  
L24:  
    %r20 = load i32, ptr %r19
    %r23 = add i32 %r20,%r21
    store i32 %r23, ptr %r19
    br label %L19
}
define float @get_next(i32 %r0,i32 %r0)
{
L1:  
    %r7 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r6
    br i1 %r7, label %L1, label %L2
    %r9 = load i32, ptr %r8
    %r11 = sub i32 %r0,%r10
    %r12 = load float, ptr %r11
    %r13 = icmp eq i32 %r9,%r12
    %r14 = load float, ptr %r13
    %r7 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r6
    %r9 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r8
    %r11 = icmp eq i32 %r7,%r9
    %r12 = load float, ptr %r11
    %r13 = xor i32 %r14,%r12
    br i1 %r13, label %L3, label %L4
    %r9 = load i32, ptr %r8
    %r12 = add i32 %r9,%r10
    store i32 %r12, ptr %r8
    %r7 = load i32, ptr %r6
    %r10 = add i32 %r7,%r8
    store i32 1, ptr %r6
    %r7 = getelementptr [0 x i32], ptr %r1, i32 0, i32 %r6
    store i32 1, ptr %r7
    br label %L5
    %r9 = getelementptr [0 x i32], ptr %r1, i32 0, i32 %r8
    store i32 1, ptr %r8
    br label %L5
L2:  
L3:  
L4:  
L5:  
L6:  
    br label %L1
}
define i32 @KMP(i32 %r0,i32 %r9)
{
L1:  
    %r15 = alloca i32
    %r13 = alloca i32
    %r11 = alloca [4096 x i32]
    %r12 = call i32 @get_next(i32 %r9,i32 %r11)
    store i32 0, ptr %r13
    store i32 0, ptr %r15
    br label %L6
    %r16 = getelementptr [0 x i32], ptr %r10, i32 0, i32 %r15
    br i1 %r16, label %L7, label %L8
    %r14 = getelementptr [0 x i32], ptr %r9, i32 0, i32 %r13
    %r16 = getelementptr [0 x i32], ptr %r10, i32 0, i32 %r15
    %r18 = icmp eq i32 %r14,%r16
    br i1 %r18, label %L9, label %L10
    %r14 = load i32, ptr %r13
    %r17 = add i32 %r14,%r15
    store i32 %r17, ptr %r13
    %r19 = add i32 %r15,%r17
    store i32 %r19, ptr %r15
    %r14 = getelementptr [0 x i32], ptr %r9, i32 0, i32 %r13
    %r15 = icmp eq i32 %r14,%r0
    br i1 %r15, label %L12, label %L13
    ret i32 1
    br label %L14
L7:  
L8:  
L9:  
    %r17 = sub i32 %r0,%r16
    ret i32 1
L10:  
L11:  
L12:  
    br label %L7
L13:  
L15:  
    br label %L11
    %r14 = getelementptr [4096 x i32], ptr %r11, i32 0, i32 %r13
    store i32 0, ptr %r13
    %r14 = load i32, ptr %r13
    %r16 = sub i32 %r0,%r15
    %r18 = icmp eq i32 %r14,%r16
    br i1 %r18, label %L15, label %L16
    %r14 = load i32, ptr %r13
    %r17 = add i32 %r14,%r15
    store i32 1, ptr %r13
    %r19 = add i32 %r15,%r17
    store i32 %r19, ptr %r15
    br label %L17
L16:  
L18:  
    br label %L11
}
define i32 @main()
{
L1:  
    %r21 = alloca [4096 x i32]
    %r20 = alloca [4096 x i32]
    %r21 = call i32 @read_str(i32 %r20)
    %r22 = call i32 @read_str(i32 %r21)
    %r22 = call i32 @KMP(i32 %r20,i32 %r21)
    %r23 = call i32 @putint(i32 %r22)
    %r25 = call i32 @putch(i32 %r24)
    ret i32 0
}
