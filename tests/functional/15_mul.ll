define i32 @main()
{
L1:  
    %r1 = alloca i32
    %r0 = alloca i32
    store i32 10, ptr %r0
    store i32 5, ptr %r1
    %r1 = load i32, ptr %r0
    %r3 = mul i32 %r1,%r1
    ret i32 %r3
}
