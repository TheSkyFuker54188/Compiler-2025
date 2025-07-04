define i32 @main()
{
L1:  
    %r4 = alloca i32
    %r3 = alloca i32
    %r2 = alloca i32
    %r1 = alloca i32
    %r0 = alloca i32
    store i32 5, ptr %r0
    store i32 5, ptr %r1
    store i32 1, ptr %r2
    %r4 = sub i32 %r0,%r3
    store i32 %r4, ptr %r3
    %r7 = mul i32 %r3,%r5
    %r8 = load float, ptr %r7
    %r11 = sdiv i32 %r8,%r9
    %r12 = load float, ptr %r11
    %r1 = load i32, ptr %r0
    %r3 = sub i32 %r1,%r1
    %r5 = add i32 %r12,%r3
    %r6 = add i32 %r2,%r4
    %r7 = sub i32 %r0,%r6
    %r8 = load float, ptr %r7
    %r11 = srem i32 %r8,%r9
    %r12 = load float, ptr %r11
    %r13 = sub i32 %r5,%r12
    store i32 %r13, ptr %r4
    %r5 = call i32 @putint(i32 %r4)
    %r7 = srem i32 %r3,%r5
    %r8 = load float, ptr %r7
    %r11 = add i32 %r8,%r9
    %r12 = load float, ptr %r11
    %r1 = load i32, ptr %r0
    %r3 = sub i32 %r1,%r1
    %r4 = sub i32 %r0,%r3
    %r6 = add i32 %r12,%r4
    %r7 = load float, ptr %r6
    %r6 = add i32 %r2,%r4
    %r7 = load float, ptr %r6
    %r10 = srem i32 %r7,%r8
    %r11 = sub i32 %r0,%r10
    %r12 = load float, ptr %r11
    %r13 = sub i32 %r7,%r12
    store i32 %r13, ptr %r4
    %r8 = add i32 %r4,%r6
    store i32 2, ptr %r4
    %r5 = call i32 @putint(i32 %r4)
    ret i32 3
}
