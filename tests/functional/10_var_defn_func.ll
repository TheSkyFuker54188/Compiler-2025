define i32 @main()
{
L1:  
    %r1 = alloca i32
    %r2 = call i32 @defn()
    store i32 %r2, ptr %r1
    ret i32 %r1
}
define i32 @defn()
{
L1:  
    ret i32 4
}
