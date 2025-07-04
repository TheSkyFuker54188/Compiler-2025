define i32 @main()
{
L1:  
    %r17 = alloca i32
    %r12 = alloca i32
    %r7 = alloca i32
    %r3 = load i32, ptr %r2
    %r6 = icmp slt i32 %r3,%r4
    br i1 %r6, label %L1, label %L2
    store i32 0, ptr %r7
    br label %L3
    %r8 = load i32, ptr %r7
    %r11 = icmp slt i32 %r8,%r9
    br i1 %r11, label %L4, label %L5
    store i32 0, ptr %r12
    br label %L6
    %r13 = load i32, ptr %r12
    %r16 = icmp slt i32 %r13,%r14
    br i1 %r16, label %L7, label %L8
    store i32 0, ptr %r17
    br label %L9
    %r18 = load i32, ptr %r17
    %r21 = icmp slt i32 %r18,%r19
    br i1 %r21, label %L10, label %L11
    %r18 = load i32, ptr %r17
    %r21 = add i32 %r18,%r19
    %r22 = load float, ptr %r21
    %r25 = icmp sge i32 %r22,%r23
    br i1 %r25, label %L12, label %L13
    br i1 %r17, label %L15, label %L16
    %r18 = load i32, ptr %r17
    %r18 = icmp eq i32 %r17,%r0
    %r20 = xor i32 %r18,%r18
    br i1 %r20, label %L18, label %L19
    %r18 = load i32, ptr %r17
    %r20 = sub i32 %r0,%r19
    %r21 = load float, ptr %r20
    %r22 = sub i32 %r18,%r21
    %r23 = load float, ptr %r22
    %r26 = icmp sge i32 %r23,%r24
    br i1 %r26, label %L21, label %L22
    br label %L11
    br label %L9
    br label %L23
L2:  
L3:  
    ret i32 %r0
L4:  
L5:  
L6:  
    %r6 = add i32 %r2,%r4
    store i32 %r6, ptr %r2
    br label %L1
L7:  
L8:  
L9:  
    %r8 = load i32, ptr %r7
    %r11 = add i32 %r8,%r9
    store i32 %r11, ptr %r7
    br label %L3
    %r8 = load i32, ptr %r7
    %r11 = add i32 %r8,%r9
    store i32 %r11, ptr %r7
    br label %L4
L10:  
L11:  
L12:  
    br label %L27
    br i1 %r1, label %L28, label %L29
    br label %L30
    br i1 %r2, label %L31, label %L32
    br label %L32
    br label %L31
L13:  
L15:  
    %r27 = alloca i32
    store i32 0, ptr %r27
    br label %L24
    %r28 = load i32, ptr %r27
    %r31 = icmp slt i32 %r28,%r29
    br i1 %r31, label %L25, label %L26
    %r28 = load i32, ptr %r27
    %r31 = add i32 %r28,%r29
    store i32 %r31, ptr %r27
    br label %L24
    br label %L26
    %r1 = load i32, ptr %r0
    %r4 = add i32 %r1,%r2
    store i32 20, ptr %r0
    br label %L25
L16:  
L18:  
    br label %L14
L19:  
L21:  
    br label %L17
L22:  
L24:  
    br label %L20
L25:  
L26:  
L27:  
    %r18 = load i32, ptr %r17
    %r21 = add i32 %r18,%r19
    store i32 %r21, ptr %r17
    %r1 = load i32, ptr %r0
    %r4 = add i32 %r1,%r2
    store i32 20, ptr %r0
    br label %L10
L28:  
L29:  
L30:  
    %r13 = load i32, ptr %r12
    %r16 = add i32 %r13,%r14
    store i32 %r16, ptr %r12
    br label %L7
L31:  
L32:  
L33:  
    br label %L29
    br label %L28
}
