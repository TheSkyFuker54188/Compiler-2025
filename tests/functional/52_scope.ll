@a = global i32 7
define i32 @func()
{
L1:  
    %r4 = load i32, ptr %r3
    %r7 = add i32 %r4,%r5
    store i32 %r7, ptr %r3
    ret i32 1
    br label %L2
    ret i32 1
    br label %L2
L2:  
L3:  
}
define i32 @main()
{
L1:  
    %r8 = alloca i32
    %r6 = alloca i32
    store i32 0, ptr %r6
    store i32 0, ptr %r8
    br label %L3
    %r9 = load i32, ptr %r8
    %r12 = icmp slt i32 %r9,%r10
    br i1 %r12, label %L4, label %L5
    %r13 = call i32 @func()
    %r14 = load float, ptr %r13
    %r17 = icmp eq i32 %r14,%r15
    br i1 %r17, label %L6, label %L7
    %r7 = load i32, ptr %r6
    %r10 = add i32 %r7,%r8
    store i32 100, ptr %r6
    br label %L8
L4:  
L5:  
L6:  
    %r7 = load i32, ptr %r6
    %r10 = icmp slt i32 %r7,%r8
    br i1 %r10, label %L9, label %L10
    %r12 = call i32 @putint(i32 %r11)
    br label %L11
    %r14 = call i32 @putint(i32 %r13)
    br label %L11
L7:  
L9:  
    %r12 = add i32 %r8,%r10
    store i32 %r12, ptr %r8
    br label %L4
L10:  
L11:  
L12:  
    ret i32 1
}
