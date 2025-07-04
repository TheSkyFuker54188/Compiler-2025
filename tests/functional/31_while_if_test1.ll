define i32 @whileIf()
{
L1:  
    %r1 = load i32, ptr %r0
    %r4 = icmp slt i32 %r1,%r2
    br i1 %r4, label %L1, label %L2
    %r1 = load i32, ptr %r0
    %r4 = icmp eq i32 %r1,%r2
    br i1 %r4, label %L3, label %L4
    store i32 25, ptr %r1
    br label %L5
    %r1 = load i32, ptr %r0
    %r4 = icmp eq i32 %r1,%r2
    br i1 %r4, label %L6, label %L7
    store i32 25, ptr %r1
    br label %L8
    %r1 = load i32, ptr %r0
    %r4 = mul i32 %r1,%r2
    store i32 %r4, ptr %r1
    br label %L8
L2:  
L3:  
    ret i32 %r1
L4:  
L5:  
L6:  
    %r1 = load i32, ptr %r0
    %r4 = add i32 %r1,%r2
    store i32 %r4, ptr %r0
    br label %L1
L7:  
L8:  
L9:  
    br label %L5
}
define i32 @main()
{
L1:  
    %r2 = call i32 @whileIf()
    ret i32 0
}
