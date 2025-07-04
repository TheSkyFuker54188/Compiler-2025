define i32 @main()
{
L1:  
    %r1 = alloca void
    %r0 = alloca i32
    store i32 %r1, ptr %r0
    ret i32 3
}
