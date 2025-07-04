define i32 @main()
{
L1:  
    %r0 = alloca i32
    store i32 10, ptr %r0
    %r1 = load i32, ptr %r0
    %r4 = mul i32 %r1,%r2
    %r5 = load float, ptr %r4
    %r8 = add i32 %r5,%r6
    ret i32 %r8
}
