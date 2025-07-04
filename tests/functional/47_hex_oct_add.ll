define i32 @main()
{
L1:  
    %r1 = alloca i32
    %r0 = alloca i32
    store i32 15, ptr %r0
    store i32 12, ptr %r1
    %r1 = load i32, ptr %r0
    %r3 = add i32 %r1,%r1
    %r4 = load float, ptr %r3
    %r7 = add i32 %r4,%r5
    ret i32 %r7
}
