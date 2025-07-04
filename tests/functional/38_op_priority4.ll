@a = global i32 zeroinitializer
@b = global i32 zeroinitializer
@c = global i32 zeroinitializer
@d = global i32 zeroinitializer
@e = global i32 zeroinitializer
define i32 @main()
{
L1:  
    store i32 1, ptr %r10
    br label %L2
L3:  
    ret i32 %r10
}
