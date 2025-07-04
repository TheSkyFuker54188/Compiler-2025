@a = global i32 zeroinitializer
define i32 @func(i32 %r0)
{
L1:  
    %r1 = load i32, ptr %r0
    %r4 = sub i32 %r1,%r2
    store i32 %r4, ptr %r0
    ret i32 %r0
}
define i32 @main()
{
L1:  
    %r1 = alloca i32
    %r3 = load i32, ptr @a
    store i32 1, ptr %r3
    %r4 = load i32, ptr @a
    %r5 = call i32 @func(i32 %r4)
    store i32 %r5, ptr %r1
    ret i32 %r1
}
