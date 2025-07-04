@a = global i32 1
@b = global i32 0
@c = global i32 1
@d = global i32 2
@e = global i32 4
define i32 @main()
{
L1:  
    store i32 1, ptr %r5
    br label %L2
L3:  
    %r6 = call i32 @putint(i32 %r5)
    ret i32 %r5
}
