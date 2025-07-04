define i32 @main()
{
L1:  
    %r1 = alloca i32
    store i32 20, ptr %r1
    ret i32 %r1
}
define i32 @f()
{
L1:  
    ret i32 10
}
