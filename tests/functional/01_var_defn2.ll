@a = global i32 3
@b = global i32 5
define i32 @main()
{
L1:  
    %r2 = alloca i32
    store i32 5, ptr %r2
    %r3 = load i32, ptr %r2
    %r4 = load i32, ptr @b
    %r5 = load i32, ptr %r4
    %r6 = add i32 %r3,%r5
    ret i32 %r6
}
