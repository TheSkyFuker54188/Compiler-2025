@a = global i32 10
define i32 @main()
{
L1:  
    %r1 = alloca i32
    store i32 2, ptr %r1
    %r2 = load i32, ptr %r1
    %r5 = sub i32 %r2,%r3
    ret i32 %r5
}
