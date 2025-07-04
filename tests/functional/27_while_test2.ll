define i32 @FourWhile()
{
L1:  
    %r1 = load i32, ptr %r0
    %r4 = icmp slt i32 %r1,%r2
    br i1 %r4, label %L1, label %L2
    %r1 = load i32, ptr %r0
    %r4 = add i32 %r1,%r2
    store i32 10, ptr %r0
    br label %L3
    %r2 = load i32, ptr %r1
    %r5 = icmp slt i32 %r2,%r3
    br i1 %r5, label %L4, label %L5
    %r2 = load i32, ptr %r1
    %r5 = add i32 %r2,%r3
    store i32 %r5, ptr %r1
    br label %L6
    %r6 = icmp eq i32 %r2,%r4
    br i1 %r6, label %L7, label %L8
    %r6 = sub i32 %r2,%r4
    store i32 %r6, ptr %r2
    br label %L9
    %r7 = icmp slt i32 %r3,%r5
    br i1 %r7, label %L10, label %L11
    %r7 = add i32 %r3,%r5
    store i32 %r7, ptr %r3
    br label %L10
L2:  
L3:  
    %r1 = load i32, ptr %r0
    %r2 = load i32, ptr %r1
    %r5 = add i32 %r2,%r3
    %r7 = add i32 %r1,%r5
    %r8 = load float, ptr %r7
    %r4 = add i32 %r8,%r2
    ret i32 10
L4:  
L5:  
L6:  
    %r2 = load i32, ptr %r1
    %r5 = sub i32 %r2,%r3
    store i32 20, ptr %r1
    br label %L1
L7:  
L8:  
L9:  
    %r6 = add i32 %r2,%r4
    store i32 %r6, ptr %r2
    br label %L4
L10:  
L11:  
L12:  
    %r7 = sub i32 %r3,%r5
    store i32 %r7, ptr %r3
    br label %L7
}
define i32 @main()
{
L1:  
    %r5 = call i32 @FourWhile()
    ret i32 20
}
