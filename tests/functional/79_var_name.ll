define i32 @main()
{
L1:  
    %r1 = load i32, ptr %r0
    %r3 = load i32, ptr %r2
    %r4 = icmp slt i32 %r1,%r3
    br i1 %r4, label %L1, label %L2
    %r1 = getelementptr [20 x i32], ptr %r4, i32 0, i32 %r0
    %r2 = load i32, ptr %r1
    %r1 = load i32, ptr %r0
    %r4 = sub i32 %r1,%r2
    %r5 = getelementptr [20 x i32], ptr %r4, i32 0, i32 %r4
    %r6 = load i32, ptr %r5
    %r7 = add i32 %r2,%r6
    %r8 = load i32, ptr %r7
    %r1 = load i32, ptr %r0
    %r4 = sub i32 %r1,%r2
    %r5 = getelementptr [20 x i32], ptr %r4, i32 0, i32 %r4
    %r6 = load i32, ptr %r5
    %r7 = add i32 %r8,%r6
    %r1 = getelementptr [20 x i32], ptr %r4, i32 0, i32 %r0
    store i32 2, ptr %r1
    %r10 = load i32, ptr %r9
    %r1 = getelementptr [20 x i32], ptr %r4, i32 0, i32 %r0
    %r2 = load i32, ptr %r1
    %r3 = add i32 %r10,%r2
    store i32 20, ptr %r9
    %r1 = getelementptr [20 x i32], ptr %r4, i32 0, i32 %r0
    %r2 = call i32 @putint(i32 %r1)
    %r4 = call i32 @putch(i32 %r3)
    %r1 = load i32, ptr %r0
    %r4 = add i32 %r1,%r2
    store i32 %r4, ptr %r0
    br label %L1
L2:  
L3:  
    ret i32 %r9
}
