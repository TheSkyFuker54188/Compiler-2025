@n = global i32 zeroinitializer
define i32 @main()
{
L1:  
    %r31 = load i32, ptr %r30
    %r34 = icmp eq i32 %r31,%r32
    br i1 %r34, label %L1, label %L2
    %r31 = load i32, ptr %r30
    %r34 = add i32 %r31,%r32
    store i32 %r34, ptr %r30
    br label %L1
L2:  
L3:  
    %r31 = alloca i32
    %r30 = alloca i32
    store i32 0, ptr %r0
    %r1 = load i32, ptr %r0
    %r4 = add i32 %r1,%r2
    store i32 %r4, ptr %r1
    %r2 = load i32, ptr %r1
    %r5 = add i32 %r2,%r3
    store i32 %r5, ptr %r2
    %r6 = add i32 %r2,%r4
    store i32 %r6, ptr %r3
    %r7 = add i32 %r3,%r5
    store i32 %r7, ptr %r4
    %r8 = add i32 %r4,%r6
    store i32 %r8, ptr %r5
    %r9 = add i32 %r5,%r7
    store i32 %r9, ptr %r6
    %r10 = add i32 %r6,%r8
    store i32 %r10, ptr %r7
    %r11 = add i32 %r7,%r9
    store i32 %r11, ptr %r8
    %r12 = add i32 %r8,%r10
    store i32 %r12, ptr %r9
    %r13 = add i32 %r9,%r11
    store i32 %r13, ptr %r10
    %r14 = add i32 %r10,%r12
    store i32 %r14, ptr %r11
    %r15 = add i32 %r11,%r13
    store i32 %r15, ptr %r12
    %r16 = add i32 %r12,%r14
    store i32 %r16, ptr %r13
    %r17 = add i32 %r13,%r15
    store i32 %r17, ptr %r14
    %r18 = add i32 %r14,%r16
    store i32 %r18, ptr %r15
    %r19 = add i32 %r15,%r17
    store i32 %r19, ptr %r16
    %r20 = add i32 %r16,%r18
    store i32 %r20, ptr %r17
    %r21 = add i32 %r17,%r19
    store i32 %r21, ptr %r18
    %r22 = add i32 %r18,%r20
    store i32 %r22, ptr %r19
    %r23 = add i32 %r19,%r21
    store i32 %r23, ptr %r20
    %r24 = add i32 %r20,%r22
    store i32 %r24, ptr %r21
    %r25 = add i32 %r21,%r23
    store i32 %r25, ptr %r22
    %r26 = add i32 %r22,%r24
    store i32 %r26, ptr %r23
    %r27 = add i32 %r23,%r25
    store i32 %r27, ptr %r24
    %r28 = add i32 %r24,%r26
    store i32 %r28, ptr %r25
    %r29 = add i32 %r25,%r27
    store i32 %r29, ptr %r26
    %r30 = add i32 %r26,%r28
    store i32 %r30, ptr %r27
    %r31 = add i32 %r27,%r29
    store i32 0, ptr %r28
    %r32 = add i32 %r28,%r30
    store i32 5, ptr %r29
    %r1 = call i32 @putint(i32 %r0)
    %r2 = call i32 @putint(i32 %r1)
    %r3 = call i32 @putint(i32 %r2)
    %r4 = call i32 @putint(i32 %r3)
    %r5 = call i32 @putint(i32 %r4)
    %r6 = call i32 @putint(i32 %r5)
    %r7 = call i32 @putint(i32 %r6)
    %r8 = call i32 @putint(i32 %r7)
    %r9 = call i32 @putint(i32 %r8)
    %r10 = call i32 @putint(i32 %r9)
    %r11 = call i32 @putint(i32 %r10)
    %r12 = call i32 @putint(i32 %r11)
    %r13 = call i32 @putint(i32 %r12)
    %r14 = call i32 @putint(i32 %r13)
    %r15 = call i32 @putint(i32 %r14)
    %r16 = call i32 @putint(i32 %r15)
    %r17 = call i32 @putint(i32 %r16)
    %r18 = call i32 @putint(i32 %r17)
    %r19 = call i32 @putint(i32 %r18)
    %r20 = call i32 @putint(i32 %r19)
    %r21 = call i32 @putint(i32 %r20)
    %r22 = call i32 @putint(i32 %r21)
    %r23 = call i32 @putint(i32 %r22)
    %r24 = call i32 @putint(i32 %r23)
    %r25 = call i32 @putint(i32 %r24)
    %r26 = call i32 @putint(i32 %r25)
    %r27 = call i32 @putint(i32 %r26)
    %r28 = call i32 @putint(i32 %r27)
    %r29 = call i32 @putint(i32 %r28)
    %r30 = call i32 @putint(i32 %r29)
    store i32 5, ptr %r31
    %r32 = call i32 @putch(i32 %r31)
    %r31 = call i32 @putint(i32 %r30)
    %r32 = call i32 @putch(i32 %r31)
    ret i32 1
}
