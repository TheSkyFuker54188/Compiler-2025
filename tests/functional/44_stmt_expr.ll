@k = global i32 zeroinitializer
@n = global i32 10
define i32 @main()
{
L1:  
    %r2 = load i32, ptr %r1
    %r7 = sub i32 %r3,%r5
    %r8 = load float, ptr %r7
    %r9 = icmp sle i32 %r2,%r8
    br i1 %r9, label %L1, label %L2
    %r2 = load i32, ptr %r1
    %r5 = add i32 %r2,%r3
    store i32 1, ptr %r1
    %r2 = load i32, ptr @k
    %r3 = load i32, ptr %r2
    %r6 = add i32 %r3,%r4
    %r7 = load i32, ptr @k
    %r8 = load i32, ptr %r7
    %r9 = load i32, ptr @k
    %r10 = load i32, ptr %r9
    %r11 = add i32 %r8,%r10
    %r12 = load i32, ptr @k
    store i32 %r11, ptr %r12
    br label %L1
L2:  
L3:  
    %r13 = load i32, ptr @k
    %r14 = call i32 @putint(i32 %r13)
    %r15 = load i32, ptr @k
    ret i32 %r15
}
