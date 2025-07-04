@k = global i32 zeroinitializer
define i32 @main()
{
L1:  
    %r14 = alloca i32
    %r20 = alloca i32
    %r18 = alloca i32
    %r13 = alloca i32
    %r7 = load i32, ptr @k
    %r8 = load i32, ptr %r7
    %r11 = add i32 %r8,%r9
    %r12 = load i32, ptr @k
    store i32 %r11, ptr %r12
    store i32 112, ptr %r13
    br label %L3
    %r14 = load i32, ptr %r13
    %r17 = icmp sgt i32 %r14,%r15
    br i1 %r17, label %L4, label %L5
    %r14 = load i32, ptr %r13
    %r17 = sub i32 %r14,%r15
    store i32 %r17, ptr %r13
    %r14 = load i32, ptr %r13
    %r17 = icmp slt i32 %r14,%r15
    br i1 %r17, label %L6, label %L7
    store i32 9, ptr %r18
    store i32 11, ptr %r20
    store i32 10, ptr %r18
    %r14 = load i32, ptr %r13
    %r19 = load i32, ptr %r18
    %r20 = sub i32 %r14,%r19
    store i32 %r20, ptr %r13
    store i32 10, ptr %r14
    %r14 = load i32, ptr %r13
    %r15 = load i32, ptr %r14
    %r16 = add i32 %r14,%r15
    %r17 = load float, ptr %r16
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 10, ptr %r13
    br label %L8
L3:  
    ret i32 %r13
L4:  
L5:  
L6:  
    %r14 = call i32 @putint(i32 %r13)
    br label %L2
L7:  
L9:  
    br label %L4
}
