define i32 @ifElseIf()
{
L1:  
    ret i32 %r0
    br label %L2
    %r2 = load i32, ptr %r1
    %r5 = icmp eq i32 %r2,%r3
    %r6 = load float, ptr %r5
    %r1 = load i32, ptr %r0
    %r4 = icmp eq i32 %r1,%r2
    %r5 = load float, ptr %r4
    %r6 = and i32 %r6,%r5
    br i1 %r6, label %L3, label %L4
    store i32 25, ptr %r0
    br label %L5
    %r2 = load i32, ptr %r1
    %r5 = icmp eq i32 %r2,%r3
    %r6 = load float, ptr %r5
    %r1 = load i32, ptr %r0
    %r3 = sub i32 %r0,%r2
    %r5 = icmp eq i32 %r1,%r3
    %r6 = load float, ptr %r5
    %r7 = and i32 %r6,%r6
    br i1 %r7, label %L6, label %L7
    %r1 = load i32, ptr %r0
    %r4 = add i32 %r1,%r2
    store i32 %r4, ptr %r0
    br label %L8
    %r1 = sub i32 %r0,%r0
    store i32 %r1, ptr %r0
    br label %L8
L2:  
L3:  
    ret i32 %r0
L4:  
L5:  
L6:  
    br label %L2
L7:  
L8:  
L9:  
    br label %L5
}
define i32 @main()
{
L1:  
    %r1 = call i32 @ifElseIf()
    %r2 = call i32 @putint(i32 %r1)
    ret i32 11
}
