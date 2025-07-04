define i32 @ififElse()
{
L1:  
    %r2 = load i32, ptr %r1
    %r5 = icmp eq i32 %r2,%r3
    br i1 %r5, label %L3, label %L4
    store i32 25, ptr %r0
    br label %L5
    %r1 = load i32, ptr %r0
    %r4 = add i32 %r1,%r2
    store i32 %r4, ptr %r0
    br label %L5
L3:  
    ret i32 %r0
L4:  
L5:  
L6:  
    br label %L2
}
define i32 @main()
{
L1:  
    %r1 = call i32 @ififElse()
    ret i32 %r1
}
