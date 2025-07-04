define i32 @main()
{
L1:  
    %r0 = alloca i32
    store i32 15, ptr %r0
    ret i32 %r0
}
