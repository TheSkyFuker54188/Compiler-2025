define i32 @main()
{
L1:  
    %r1 = load i32, ptr %r0
    %r4 = icmp slt i32 %r1,%r2
    br i1 %r4, label %L1, label %L2
    %r1 = load i32, ptr %r0
    %r4 = icmp eq i32 %r1,%r2
    br i1 %r4, label %L3, label %L4
    br label %L2
    br label %L5
L2:  
L3:  
    ret i32 %r1
L4:  
L6:  
    %r2 = load i32, ptr %r1
    %r1 = load i32, ptr %r0
    %r2 = add i32 %r2,%r1
    store i32 0, ptr %r1
    %r1 = load i32, ptr %r0
    %r4 = add i32 %r1,%r2
    store i32 %r4, ptr %r0
    br label %L1
}
