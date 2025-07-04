define i32 @f(i32 %r0)
{
L1:  
    %r1 = load i32, ptr %r0
    %r4 = mul i32 %r1,%r2
    ret i32 %r4
}
define i32 @main()
{
L1:  
    %r6 = call i32 @f(i32 %r5)
    ret i32 %r6
}
