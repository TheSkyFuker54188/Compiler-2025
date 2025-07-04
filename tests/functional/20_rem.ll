define i32 @main()
{
L1:  
    %r0 = alloca i32
    store i32 10, ptr %r0
    %r1 = load i32, ptr %r0
    %r4 = srem i32 %r1,%r2
    ret i32 %r4
}
