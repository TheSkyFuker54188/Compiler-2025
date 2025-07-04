define i32 @ifWhile()
{
L1:  
    br label %L3
    %r2 = load i32, ptr %r1
    %r5 = icmp eq i32 %r2,%r3
    br i1 %r5, label %L4, label %L5
    %r2 = load i32, ptr %r1
    %r5 = add i32 %r2,%r3
    store i32 %r5, ptr %r1
    br label %L4
L2:  
L3:  
    ret i32 %r1
L4:  
L5:  
L6:  
    %r2 = load i32, ptr %r1
    %r5 = add i32 %r2,%r3
    store i32 %r5, ptr %r1
    br label %L2
    br label %L6
    %r1 = load i32, ptr %r0
    %r4 = icmp slt i32 %r1,%r2
    br i1 %r4, label %L7, label %L8
    %r2 = load i32, ptr %r1
    %r5 = mul i32 %r2,%r3
    store i32 %r5, ptr %r1
    %r1 = load i32, ptr %r0
    %r4 = add i32 %r1,%r2
    store i32 %r4, ptr %r0
    br label %L7
L7:  
L8:  
L9:  
    br label %L2
}
define i32 @main()
{
L1:  
    %r2 = call i32 @ifWhile()
    ret i32 3
}
