define i32 @deepWhileBr(i32 %r0,i32 %r0)
{
L1:  
    %r7 = alloca i32
    %r7 = alloca i32
    %r3 = load i32, ptr %r2
    %r6 = icmp slt i32 %r3,%r4
    br i1 %r6, label %L1, label %L2
    store i32 42, ptr %r7
    %r3 = load i32, ptr %r2
    %r6 = icmp slt i32 %r3,%r4
    br i1 %r6, label %L3, label %L4
    %r3 = load i32, ptr %r2
    %r8 = load i32, ptr %r7
    %r9 = add i32 %r3,%r8
    store i32 %r9, ptr %r2
    %r3 = load i32, ptr %r2
    %r6 = icmp sgt i32 %r3,%r4
    br i1 %r6, label %L6, label %L7
    %r8 = load i32, ptr %r7
    %r11 = mul i32 %r8,%r9
    store i32 %r11, ptr %r7
    %r12 = icmp eq i32 %r8,%r10
    br i1 %r12, label %L9, label %L10
    %r8 = load i32, ptr %r7
    %r11 = mul i32 %r8,%r9
    store i32 %r11, ptr %r2
    br label %L11
L2:  
L3:  
    ret i32 %r2
L4:  
L6:  
    br label %L1
L7:  
L9:  
    br label %L5
L10:  
L12:  
    br label %L8
}
define i32 @main()
{
L1:  
    %r3 = alloca i32
    store i32 75, ptr %r3
    %r4 = call i32 @deepWhileBr(i32 %r3,i32 %r3)
    ret i32 75
}
