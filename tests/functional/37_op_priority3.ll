define i32 @main()
{
L1:  
    %r1 = alloca i32
    %r0 = alloca i32
    store i32 10, ptr %r0
    store i32 30, ptr %r1
    %r1 = load i32, ptr %r0
    %r3 = sub i32 %r0,%r2
    %r4 = load float, ptr %r3
    %r5 = sub i32 %r1,%r4
    %r6 = load float, ptr %r5
    %r3 = add i32 %r6,%r1
    %r4 = load float, ptr %r3
    %r6 = sub i32 %r0,%r5
    %r7 = load float, ptr %r6
    %r8 = add i32 %r4,%r7
    ret i32 %r8
}
