define i32 @main()
{
L1:  
    %r2 = alloca i32
    %r1 = alloca i32
    %r0 = alloca i32
    store i32 1, ptr %r0
    store i32 2, ptr %r1
    store i32 3, ptr %r2
    %r4 = add i32 %r1,%r2
    ret i32 %r4
}
