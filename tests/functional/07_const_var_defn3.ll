define i32 @main()
{
L1:  
    %r2 = alloca i32
    %r0 = alloca i32
    store i32 10, ptr %r0
    store i32 5, ptr %r2
    ret i32 %r2
}
