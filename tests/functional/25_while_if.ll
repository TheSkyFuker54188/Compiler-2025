define i32 @get_one(i32 %r0)
{
L1:  
    ret i32 1
}
define i32 @deepWhileBr(i32 %r0,i32 %r2)
{
L1:  
    %r9 = alloca i32
    %r9 = alloca i32
    %r5 = load i32, ptr %r4
    %r8 = icmp slt i32 %r5,%r6
    br i1 %r8, label %L1, label %L2
    store i32 42, ptr %r9
    %r5 = load i32, ptr %r4
    %r8 = icmp slt i32 %r5,%r6
    br i1 %r8, label %L3, label %L4
    %r5 = load i32, ptr %r4
    %r10 = load i32, ptr %r9
    %r11 = add i32 %r5,%r10
    store i32 %r11, ptr %r4
    %r5 = load i32, ptr %r4
    %r8 = icmp sgt i32 %r5,%r6
    br i1 %r8, label %L6, label %L7
    %r10 = load i32, ptr %r9
    %r13 = mul i32 %r10,%r11
    store i32 %r13, ptr %r9
    %r11 = call i32 @get_one(i32 %r10)
    %r15 = icmp eq i32 %r11,%r13
    br i1 %r15, label %L9, label %L10
    %r10 = load i32, ptr %r9
    %r13 = mul i32 %r10,%r11
    store i32 1, ptr %r4
    br label %L11
L2:  
L3:  
    ret i32 %r4
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
    %r5 = alloca i32
    store i32 75, ptr %r5
    %r6 = call i32 @deepWhileBr(i32 %r5,i32 %r5)
    store i32 75, ptr %r5
    %r6 = call i32 @putint(i32 %r5)
    ret i32 0
}
