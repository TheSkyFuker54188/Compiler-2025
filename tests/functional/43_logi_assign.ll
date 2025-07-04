@a = global i32 zeroinitializer
@b = global i32 zeroinitializer
define i32 @main()
{
L1:  
    store i32 1, ptr %r4
    br label %L2
    store i32 0, ptr %r4
    br label %L2
L2:  
L3:  
    ret i32 %r4
}
